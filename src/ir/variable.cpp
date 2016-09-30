// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Variable;

LLVMValueRef Variable::handle(GContext& ctx) noexcept {
  if (!_handle) {
    auto type_handle = type->handle(ctx);

    // Generate handle for the initializer expression (if present or needed)
    LLVMValueRef initializer_handle = nullptr;
    if (initializer) {
      initializer_handle = Transmute(
        initializer->source, initializer, type).value_of(ctx);
    }

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
      // Allocate space on the stack for the local variable
      _handle = LLVMBuildAlloca(ctx.irb, type_handle, name.c_str());

      // Set initializer (if present)
      if (initializer_handle) {
        LLVMBuildStore(ctx.irb, initializer_handle, _handle);
      }
    }
  }

  return _handle;
}
