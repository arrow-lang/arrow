// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Conditional;

// TODO: Value

unsigned conditional_index = 0;

LLVMValueRef Conditional::handle(GContext& ctx) noexcept {
  // Realize condition
  auto condition_handle = condition->value_of(ctx);

  // Launchpad
  conditional_index++;
  auto current = LLVMGetInsertBlock(ctx.irb);
  auto parent_fn = LLVMGetBasicBlockParent(current);
  auto b_then = LLVMAppendBasicBlock(parent_fn, (std::to_string(conditional_index) + "-then").c_str());
  auto b_otherwise = LLVMAppendBasicBlock(parent_fn, (std::to_string(conditional_index) + "-otherwise").c_str());
  auto b_merge = LLVMAppendBasicBlock(parent_fn, (std::to_string(conditional_index) + "-merge").c_str());
  auto divergent_then = false;
  auto divergent_otherwise = false;

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
  } else {
    divergent_then = true;
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
	  } else {
      divergent_otherwise = true;
    }
	} else {
		// Terminate directly
		// NOTE: Easier then adjusting the algorithm
		LLVMBuildBr(ctx.irb, b_merge);
	}

  // Is the conditional divergent?
  if (divergent_then && divergent_otherwise) {
    // Remove the merge block
    LLVMDeleteBasicBlock(b_merge);
  } else {
    // Realize the merge block
    LLVMMoveBasicBlockAfter(b_merge, LLVMGetInsertBlock(ctx.irb));
    LLVMPositionBuilderAtEnd(ctx.irb, b_merge);
  }

  return nullptr;
}
