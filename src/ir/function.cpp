// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <sstream>

#include "arrow/ir.hpp"
#include "arrow/log.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Function;
using arrow::ir::ExternFunction;

LLVMValueRef Function::handle(GContext& ctx) noexcept {
  if (!_handle) {
    auto type_handle = type->handle(ctx);
    _handle = LLVMAddFunction(ctx.mod, name_mangle().c_str(), type_handle);

    // Set linkage to private
    LLVMSetLinkage(_handle, LLVMLinkerPrivateLinkage);

    // Prepare builder
    auto old_block = LLVMGetInsertBlock(ctx.irb);
    LLVMPositionBuilderAtEnd(ctx.irb, LLVMAppendBasicBlock(_handle, ""));

    // Realize parameter handles
    unsigned param_index = 0;
    for (auto& param : parameters) {
      if (!param->type->is_unit()) {
        auto param_type_handle = param->type->handle(ctx);
        param->_handle = LLVMBuildAlloca(
          ctx.irb, param_type_handle, param->name.c_str());

        LLVMBuildStore(
          ctx.irb, LLVMGetParam(_handle, param_index++), param->_handle);
      }
    }

    // Stack: push
    ctx.function_s.push(this);

    // Realize block
    block->handle(ctx);

    // Stack: pop
    ctx.function_s.pop();

    if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx.irb))) {
      // Not terminated; Terminate
      auto result_type = cast<TypeFunction>(type)->result;
      if (!result_type->is_unit()) {
        // Expected a return but none found
        Log::get().error(source->span, "not all control paths return a value");
      } else {
        LLVMBuildRetVoid(ctx.irb);
      }
    }

    // Restore builder
    LLVMPositionBuilderAtEnd(ctx.irb, old_block);
  }

  return _handle;
}

std::string Function::name_mangle() const {
  // Encode the signature

  auto type_f = cast<TypeFunction>(type);

  std::stringstream stream;
  stream << _module->name;
  stream << "_";
  stream << name;

  for (auto& param : type_f->parameters) {
    stream << "$";
    stream << param->name;
  }

  if (type_f->result) {
    stream << "$$";
    stream << type_f->result->name;
  }

  return stream.str();
}

LLVMValueRef ExternFunction::handle(GContext& ctx) noexcept {
  if (!_handle) {
    auto type_handle = type->handle(ctx);
    _handle = LLVMAddFunction(ctx.mod, name.c_str(), type_handle);
  }

  return _handle;
}
