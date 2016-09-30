// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Module;

LLVMValueRef Module::handle(GContext& ctx) {
  if (_initialized) return nullptr;
  _initialized = true;

  // Declare module initializer
  initializer = LLVMAddFunction(ctx.mod, "$init", LLVMFunctionType(
    LLVMVoidType(),
    nullptr,
    0,
    false));

  LLVMSetLinkage(initializer, LLVMLinkerPrivateLinkage);

  LLVMPositionBuilderAtEnd(ctx.irb,
    LLVMAppendBasicBlock(initializer, ""));

  // Generate each statement ..
  block->handle(ctx);

  // Terminate module initializer
  LLVMBuildRetVoid(ctx.irb);

  return nullptr;
}
