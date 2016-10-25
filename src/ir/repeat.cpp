// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Repeat;
using arrow::ir::Break;
using arrow::ir::Continue;

LLVMValueRef Repeat::handle(GContext& ctx) noexcept {
  if (!_handle) {
    // Launchpad
    auto current = LLVMGetInsertBlock(ctx.irb);
    auto parent_fn = LLVMGetBasicBlockParent(current);
    auto b_condition = LLVMAppendBasicBlock(parent_fn, "loop:condition");
    auto b_loop = LLVMAppendBasicBlock(parent_fn, "loop:body");
    auto b_merge = LLVMAppendBasicBlock(parent_fn, "loop:merge");

    // Add terminator to current to move to the condition block
    LLVMBuildBr(ctx.irb, b_condition);

    // Move to the condition block and realize the condition
    LLVMPositionBuilderAtEnd(ctx.irb, b_condition);
    auto cond_handle = condition->value_of(ctx);
    if (!cond_handle) return nullptr;
    LLVMBuildCondBr(ctx.irb, cond_handle, b_loop, b_merge);

    // Push a loop frame
    ctx.loop_s.push({b_condition, b_merge});

    // Move to the loop block
    LLVMMoveBasicBlockAfter(b_loop, LLVMGetInsertBlock(ctx.irb));
    LLVMPositionBuilderAtEnd(ctx.irb, b_loop);
    body->handle(ctx);
    if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx.irb))) {
      // Add terminator to jump back to the condition block
      LLVMBuildBr(ctx.irb, b_condition);
    }

    // Pop the loop frame
    ctx.loop_s.pop();

    // Move to the merge block
    LLVMMoveBasicBlockAfter(b_merge, LLVMGetInsertBlock(ctx.irb));
    LLVMPositionBuilderAtEnd(ctx.irb, b_merge);

    // No value (for a loop)
    _handle = LLVMGetUndef(LLVMVoidType());
  }

  return nullptr;
}

LLVMValueRef Break::handle(GContext& ctx) noexcept {
  if (!_handle) {
    // Jump immediately to the `merge` after the loop
    auto& loop = ctx.loop_s.top();
    LLVMBuildBr(ctx.irb, loop.second);

    // No value (for a loop)
    _handle = LLVMGetUndef(LLVMVoidType());
  }

  return nullptr;
}

LLVMValueRef Continue::handle(GContext& ctx) noexcept {
  if (!_handle) {
    // Jump immediately to the `condition` in the loop
    auto& loop = ctx.loop_s.top();
    LLVMBuildBr(ctx.irb, loop.first);

    // No value (for a loop)
    _handle = LLVMGetUndef(LLVMVoidType());
  }

  return nullptr;
}
