// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Return;

LLVMValueRef Return::handle(GContext &ctx) noexcept {
  // Build terminating ret ..
  if (operand) {
    // Value return
    auto op_handle = operand->value_of(ctx);
    LLVMBuildRet(ctx.irb, op_handle);
  } else {
    // Void return
    LLVMBuildRetVoid(ctx.irb);
  }

  // No (value-able) result
  return nullptr;
}
