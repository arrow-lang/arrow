// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Not;
using arrow::ir::And;
using arrow::ir::Or;
using arrow::ir::Value;
using arrow::ptr;

static LLVMValueRef _logical(arrow::GContext &ctx, ptr<Value> lhs, ptr<Value> rhs, bool is_and) {
  // Realize LHS
  auto lhs_handle = lhs->value_of(ctx);
  if (!lhs_handle) return nullptr;

  // Launchpad
  auto current = LLVMGetInsertBlock(ctx.irb);
  auto parent_fn = LLVMGetBasicBlockParent(current);
  auto next = LLVMAppendBasicBlock(parent_fn, "");
  auto merge = LLVMAppendBasicBlock(parent_fn, "");

  // Test
  if (is_and) {
    LLVMBuildCondBr(ctx.irb, lhs_handle, next, merge);
  } else {
    LLVMBuildCondBr(ctx.irb, lhs_handle, merge, next);
  }

  // Realize RHS
  LLVMMoveBasicBlockAfter(next, LLVMGetInsertBlock(ctx.irb));
  LLVMPositionBuilderAtEnd(ctx.irb, next);
  auto rhs_handle = rhs->value_of(ctx);
  if (!rhs_handle) return nullptr;
  if (is_and) {
    rhs_handle = LLVMBuildAnd(ctx.irb, lhs_handle, rhs_handle, "");
  } else {
    rhs_handle = LLVMBuildOr(ctx.irb, lhs_handle, rhs_handle, "");
  }
  next = LLVMGetInsertBlock(ctx.irb);

  // Close
  LLVMBuildBr(ctx.irb, merge);

  // Result
  LLVMMoveBasicBlockAfter(merge, LLVMGetInsertBlock(ctx.irb));
  LLVMPositionBuilderAtEnd(ctx.irb, merge);
  auto result = LLVMBuildPhi(ctx.irb, lhs->type->handle(ctx), "");
  LLVMAddIncoming(result, &lhs_handle, &current, 1);
  LLVMAddIncoming(result, &rhs_handle, &next, 1);

  return result;
}

LLVMValueRef Not::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto op_handle = Transmute(operand->source, operand, type).value_of(ctx);
    if (!op_handle) return nullptr;

    _handle = LLVMBuildNot(ctx.irb, op_handle, "");
  }

  return _handle;
}

LLVMValueRef And::handle(GContext &ctx) noexcept {
  if (!_handle) _handle = _logical(ctx, lhs, rhs, true);
  return _handle;
}

LLVMValueRef Or::handle(GContext &ctx) noexcept {
  if (!_handle) _handle = _logical(ctx, lhs, rhs, false);
  return _handle;
}
