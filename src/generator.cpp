// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "fmt.hpp"

#include "arrow/generator.hpp"
#include "arrow/log.hpp"
#include "arrow/pass/build.hpp"
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

  LLVMDisposeMessage(triple);

  // Register built-in types
  // Boolean
  _ctx.scope_b.emplace("bool", make<ir::TypeBoolean>());

  // Integer, Signed
  _ctx.scope_b.emplace("int8", make<ir::TypeInteger>(true, 8));
  _ctx.scope_b.emplace("int16", make<ir::TypeInteger>(true, 16));
  _ctx.scope_b.emplace("int32", make<ir::TypeInteger>(true, 32));
  _ctx.scope_b.emplace("int64", make<ir::TypeInteger>(true, 64));
  _ctx.scope_b.emplace("int128", make<ir::TypeInteger>(true, 128));

  // Integer, Unsigned
  _ctx.scope_b.emplace("uint8", make<ir::TypeInteger>(false, 8));
  _ctx.scope_b.emplace("uint16", make<ir::TypeInteger>(false, 16));
  _ctx.scope_b.emplace("uint32", make<ir::TypeInteger>(false, 32));
  _ctx.scope_b.emplace("uint64", make<ir::TypeInteger>(false, 64));
  _ctx.scope_b.emplace("uint128", make<ir::TypeInteger>(false, 128));

  // Real
  _ctx.scope_b.emplace("float32", make<ir::TypeReal>(32));
  _ctx.scope_b.emplace("float64", make<ir::TypeReal>(64));

  // String
  _ctx.scope_b.emplace("str", make<ir::TypeString>());
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
  auto data = LLVMCopyStringRepOfTargetData(LLVMGetTargetMachineData(
    _ctx.target));
  LLVMSetDataLayout(_ctx.mod, data);
  LLVMDisposeMessage(data);

  // Build
  pass::Build(_ctx).run(module);
  if (Log::get().count(LOG_ERROR) > 0) return *this;

  // Generate modules
  for (auto& mod : _ctx.modules) mod->generate(_ctx);

  // Declare main
  // TODO(mehcode): Full (all parameters)
  auto main = LLVMAddFunction(_ctx.mod, "main", LLVMFunctionType(
    LLVMVoidType(),
    nullptr,
    0,
    false
  ));

  LLVMPositionBuilderAtEnd(_ctx.irb,
    LLVMAppendBasicBlock(main, ""));

  // HACK: Call top-level module initializer
  // auto init = LLVMGetNamedFunction(_ctx.mod, "#init");
  // LLVMBuildCall(_ctx.irb, init, nullptr, 0, "");

  // Call each module initializer (in reverse order for now)
  // TODO(mehcode): Resolve order
  for (auto m = _ctx.modules.rbegin(); m < _ctx.modules.rend(); ++m) {
    LLVMBuildCall(_ctx.irb, (*m)->initializer, nullptr, 0, "");
  }

  // TODO(mehcode): Call the top-level module main function (if present)

  // Terminate main
  LLVMBuildRetVoid(_ctx.irb);

  return *this;
}

Generator& Generator::print() {
  auto bytes = LLVMPrintModuleToString(_ctx.mod);
  fmt::print("{}\n", bytes);
  LLVMDisposeMessage(bytes);

  return *this;
}
