// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "fmt.hpp"

#include "arrow/generator.hpp"
#include "arrow/log.hpp"
#include "arrow/pass/build.hpp"
#include "arrow/pass/declare.hpp"
#include "arrow/pass/type_resolve.hpp"
#include "mach7.hpp"

using arrow::Generator;

Generator::Generator()
  : _ctx() {
  initialize();
}

Generator::~Generator() noexcept {
  // Dispose of the LLVM module
  if (_ctx.mod) LLVMDisposeModule(_ctx.mod);

  // Dispose of the instruction builder
  if (_ctx.irb) LLVMDisposeBuilder(_ctx.irb);

  // Dispose of the target machine
  if (_ctx.target) LLVMDisposeTargetMachine(_ctx.target);
}

void Generator::initialize() {
  // LLVM: Initialize target and printer
  LLVMInitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();

  // LLVM: Construct instruction builder
  _ctx.irb = LLVMCreateBuilder();

  // Discern the triple for our target machine.
  // TODO(mehcode): Allow client to specify architecture here
  auto triple = LLVMGetDefaultTargetTriple();
  LLVMTargetRef target = nullptr;
  char* error = nullptr;
  if (LLVMGetTargetFromTriple(triple, &target, &error) != 0) {
    // Failed to get a valid target; shouldn't be able to happen
    // TODO(mehcode): error message of some kind
    return;
  }

  // Construct the target machine
  _ctx.target = LLVMCreateTargetMachine(
    target, triple, "", "",
    LLVMCodeGenLevelDefault,
    LLVMRelocDefault,
    LLVMCodeModelDefault);

  _ctx.target_data = LLVMGetTargetMachineData(_ctx.target);
  LLVMDisposeMessage(triple);

  // Initialize top scope
  _ctx.scope = make<ir::Scope>(nullptr);

  // Register built-in types
  // Boolean
  _ctx.scope->put("bool", make<ir::TypeBoolean>());

  // Integer, Signed
  _ctx.scope->put("int8", make<ir::TypeInteger>(true, 8));
  _ctx.scope->put("int16", make<ir::TypeInteger>(true, 16));
  _ctx.scope->put("int32", make<ir::TypeInteger>(true, 32));
  _ctx.scope->put("int64", make<ir::TypeInteger>(true, 64));
  _ctx.scope->put("int128", make<ir::TypeInteger>(true, 128));

  // Integer, Unsigned
  _ctx.scope->put("uint8", make<ir::TypeInteger>(false, 8));
  _ctx.scope->put("uint16", make<ir::TypeInteger>(false, 16));
  _ctx.scope->put("uint32", make<ir::TypeInteger>(false, 32));
  _ctx.scope->put("uint64", make<ir::TypeInteger>(false, 64));
  _ctx.scope->put("uint128", make<ir::TypeInteger>(false, 128));

  // Real
  _ctx.scope->put("float32", make<ir::TypeReal>(32));
  _ctx.scope->put("float64", make<ir::TypeReal>(64));

  // String
  _ctx.scope->put("str", make<ir::TypeString>());
}

// TODO(mehcode): How do imports work with regards to ir::Module and LLVMModule
Generator& Generator::run(ptr<ast::Module> module) {
  // LLVM: Construct module context
  _ctx.mod = LLVMModuleCreateWithName(module->name.c_str());

  // Set the target on the module
  auto triple = LLVMGetTargetMachineTriple(_ctx.target);
  LLVMSetTarget(_ctx.mod, triple);
  LLVMDisposeMessage(triple);

  // Set the data layout on the module
  auto data = LLVMCopyStringRepOfTargetData(_ctx.target_data);
  LLVMSetDataLayout(_ctx.mod, data);
  LLVMDisposeMessage(data);

  // Declare
  pass::Declare(_ctx).run(module);
  if (Log::get().count(LOG_ERROR) > 0) return *this;

  // TypeResolve
  pass::TypeResolve(_ctx).run(module);
  if (Log::get().count(LOG_ERROR) > 0) return *this;

  // Build
  pass::Build(_ctx).run(module);
  if (Log::get().count(LOG_ERROR) > 0) return *this;

  // Generate modules
  for (auto& mod : _ctx.modules) mod->handle(_ctx);

  // Declare main parameters
  // FIXME(mehcode): Get proper size of C INT here
  std::vector<LLVMTypeRef> main_params;
  main_params.push_back(LLVMInt32Type());
  main_params.push_back(LLVMPointerType(LLVMPointerType(LLVMInt8Type(), 0), 0));
  main_params.push_back(LLVMPointerType(LLVMPointerType(LLVMInt8Type(), 0), 0));

  // Declare main
  auto main = LLVMAddFunction(_ctx.mod, "main", LLVMFunctionType(
    LLVMInt32Type(),
    main_params.data(),
    main_params.size(),
    false
  ));

  LLVMPositionBuilderAtEnd(_ctx.irb,
    LLVMAppendBasicBlock(main, ""));

  // Call each module initializer (in reverse order for now)
  // TODO(mehcode): Resolve order
  for (auto m = _ctx.modules.rbegin(); m < _ctx.modules.rend(); ++m) {
    LLVMBuildCall(_ctx.irb, (*m)->initializer, nullptr, 0, "");
  }

  // HACK: Which module is the top-level module?
  // TODO(mehcode): Call the top-level module main function (if present)
  auto mod = _ctx.modules.back();
  auto main_ = mod->block->scope->get("main");
  if (main_) {
    auto main_fn = cast<ir::Function>(main_);
    auto main_t = cast<ir::TypeFunction>(main_fn->type);
    auto m_ctx = cast<ast::Function>(main_->source);

    if (!isa<ir::Function>(main_) || isa<ir::ExternFunction>(main_)) {
      Log::get().error(m_ctx->span, "'main' must be a function");
      return *this;
    }

    // Check result
    if (!(main_t->result->is_unit() || (main_t->result->is_integer() && main_t->result->size() == 32))) {
      Log::get().error(
        m_ctx->result_type->span, "result of `main` must be `()` or `int32`");
    }

    // Check parameters
    auto pcount = main_t->parameters.size();

    if (pcount > 3) {
      Log::get().error(
        m_ctx->span,
        "too many parameters (%d) for 'main': must be 0, 2, or 3",
        pcount);
    }

    if (pcount == 1) {
      Log::get().error(m_ctx->span,
        "only one parameter for 'main': must be 0, 2, or 3");
    }

    if (pcount >= 1) {
      if (!(main_t->parameters[0]->is_integer() &&
            main_t->parameters[0]->size() == 32)) {
        Log::get().error(
          m_ctx->parameters[0]->span,
          "first parameter of 'main' (argc) must be of type 'int32'");
      }
    }

    if (pcount >= 2) {
      if (!(main_t->parameters[1]->is_pointer() &&
            isa<ir::TypeString>(cast<ir::TypePointer>(main_t->parameters[1])->element))) {
        Log::get().error(
          m_ctx->parameters[0]->span,
          "second parameter of 'main' (argv) must be of type '*str'");
      }
    }

    if (pcount >= 3) {
      if (!(main_t->parameters[2]->is_pointer() &&
            isa<ir::TypeString>(cast<ir::TypePointer>(main_t->parameters[2])->element))) {
        Log::get().error(
          m_ctx->parameters[0]->span,
          "third parameter of 'main' (envrion) must be of type '*str'");
      }
    }

    // Build arguments
    std::vector<LLVMValueRef> arguments;
    for (unsigned i = 0; i < pcount; ++i) {
      arguments.push_back(LLVMGetParam(main, i));
    }

    // Build Call
    auto res = LLVMBuildCall(_ctx.irb,
      main_fn->handle(_ctx), arguments.data(), arguments.size(), "");

    if (!main_t->result->is_unit()) {
      LLVMBuildRet(_ctx.irb, res);
    }
  }

  if (Log::get().count(LOG_ERROR) > 0) return *this;

  // Terminate main (if needed)
  if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(_ctx.irb))) {
    LLVMBuildRet(_ctx.irb, LLVMConstInt(LLVMInt32Type(), 0, false));
  }

  return *this;
}

Generator& Generator::print() {
  auto bytes = LLVMPrintModuleToString(_ctx.mod);
  fmt::print("{}\n", bytes);
  LLVMDisposeMessage(bytes);

  return *this;
}
