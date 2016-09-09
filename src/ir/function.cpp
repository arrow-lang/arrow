// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Function;

LLVMValueRef Function::handle(GContext& ctx) noexcept {
  if (!_handle) {
    // Add global variable to module
    auto type_handle = type->handle(ctx);
    _handle = LLVMAddFunction(ctx.mod, name.c_str(), type_handle);

    // Set linkage to private
    LLVMSetLinkage(_handle, LLVMLinkerPrivateLinkage);
  }

  return _handle;
}

void Function::generate(GContext& ctx) {
  // Realize handle (if not already)
  auto fn = handle(ctx);

  // Prepare builder
  auto old_block = LLVMGetInsertBlock(ctx.irb);
  LLVMPositionBuilderAtEnd(ctx.irb, LLVMAppendBasicBlock(fn, ""));

  // Generate each statement ..
  for (auto& stmt : statements) stmt->generate(ctx);

  // Terminate
  LLVMBuildRetVoid(ctx.irb);

  // Restore builder
  LLVMPositionBuilderAtEnd(ctx.irb, old_block);
}
