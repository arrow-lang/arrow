// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Conditional;

// TODO: Value

LLVMValueRef Conditional::handle(GContext& ctx) noexcept {
  // Realize condition
  auto condition_handle = condition->value_of(ctx);
  
  // Launchpad
  auto current = LLVMGetInsertBlock(ctx.irb);
  auto parent_fn = LLVMGetBasicBlockParent(current);
  auto b_then = LLVMAppendBasicBlock(parent_fn, "");
  auto b_otherwise = LLVMAppendBasicBlock(parent_fn, "");
  auto b_merge = LLVMAppendBasicBlock(parent_fn, "");

  // Test and Branch
  LLVMBuildCondBr(ctx.irb, condition_handle, b_then, b_otherwise);

  // Realize THEN
  LLVMMoveBasicBlockAfter(b_then, LLVMGetInsertBlock(ctx.irb));
  LLVMPositionBuilderAtEnd(ctx.irb, b_then);
  auto then_handle = then->value_of(ctx);
  b_then = LLVMGetInsertBlock(ctx.irb);

  // Terminate THEN (if needed)
  if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx.irb))) {
  	LLVMBuildBr(ctx.irb, b_merge);
  }

	// Realize OTHERWISE
  LLVMMoveBasicBlockAfter(b_otherwise, LLVMGetInsertBlock(ctx.irb));
  LLVMPositionBuilderAtEnd(ctx.irb, b_otherwise);
  if (otherwise) {
	  auto otherwise_handle = otherwise->value_of(ctx);
	  b_otherwise = LLVMGetInsertBlock(ctx.irb);

	  // Terminate OTHERWISE (if needed)
	  if (!LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx.irb))) {
	  	LLVMBuildBr(ctx.irb, b_merge);
	  }
	} else {
		// Terminate directly
		// NOTE: Easier then adjusting the algorithm 
		LLVMBuildBr(ctx.irb, b_merge);
	}

  // Result
  LLVMMoveBasicBlockAfter(b_merge, LLVMGetInsertBlock(ctx.irb));
  LLVMPositionBuilderAtEnd(ctx.irb, b_merge);

  return nullptr;
}
