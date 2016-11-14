// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Variable;
using arrow::ir::ExternVariable;

LLVMValueRef Variable::handle(GContext& ctx) noexcept {
  if (!_handle) {
    // Generate handle for the initializer expression (if present or needed)
    LLVMValueRef initializer_handle = nullptr;
    if (initializer) {
      if (!type || type->is_unit()) {
        initializer->handle(ctx);
      } else {
        initializer_handle = ir::transmute(initializer, type)->value_of(ctx);
      }

      // An initializer that is divergent does not create a variable
      if (initializer->type->is_divergent()) return nullptr;
    }

    // A variable of type unit does not exist
    if (!type || type->is_unit()) return nullptr;

    auto type_handle = type->handle(ctx);
    if (_is_global) {
      // Add global variable to module
      _handle = LLVMAddGlobal(ctx.mod, type_handle, name.c_str());

      // Set constant initializer
      LLVMSetInitializer(_handle, LLVMConstNull(type_handle));

      // Set linkage to private
      LLVMSetLinkage(_handle, LLVMLinkerPrivateLinkage);

      if (initializer_handle) {
        if (LLVMIsConstant(initializer_handle)) {
          // Set initializer
          LLVMSetInitializer(_handle, initializer_handle);
        } else {
          // Set store
          LLVMBuildStore(ctx.irb, initializer_handle, _handle);
        }
      }
    } else {
      // Find the function prelude where the stack allocations reside
      auto current = LLVMGetInsertBlock(ctx.irb);
      auto fn_handle = LLVMGetBasicBlockParent(current);
      auto top = LLVMGetEntryBasicBlock(fn_handle);
      auto instr = LLVMGetFirstInstruction(top);
      if (instr != nullptr) {
        while (
          (LLVMGetInstructionOpcode(instr) == LLVMAlloca) &&
          (LLVMGetLastInstruction(top) != instr)
        ) {
          instr = LLVMGetNextInstruction(instr);
        }

        LLVMPositionBuilderBefore(ctx.irb, instr);
      } else {
        LLVMPositionBuilderAtEnd(ctx.irb, top);
      }

      // Allocate space on the stack for the local variable
      _handle = LLVMBuildAlloca(ctx.irb, type_handle, name.c_str());

      // Go back
      LLVMPositionBuilderAtEnd(ctx.irb, current);

      // Set initializer (if present)
      if (initializer_handle) {
        LLVMBuildStore(ctx.irb, initializer_handle, _handle);
      }
    }
  }

  return _handle;
}

LLVMValueRef ExternVariable::handle(GContext& ctx) noexcept {
  if (!_handle) {
    // Attempt to find global first (extern cache)
    _handle = LLVMGetNamedGlobal(ctx.mod, name.c_str());
    if (!_handle) {
      auto type_handle = type->handle(ctx);

      // Add global variable to module
      _handle = LLVMAddGlobal(ctx.mod, type_handle, name.c_str());

      // Set linkage to private
      LLVMSetLinkage(_handle, LLVMExternalLinkage);
    }
  }

  return _handle;
}
