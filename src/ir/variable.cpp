// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Variable;

LLVMValueRef Variable::handle(GContext& ctx) noexcept {
  // TODO(mehcode): Local variables

  if (!_handle) {
    // Add global variable to module
    auto type_handle = type->handle(ctx);
    _handle = LLVMAddGlobal(ctx.mod, type_handle, name.c_str());

    // Set linkage to private
    LLVMSetLinkage(_handle, LLVMLinkerPrivateLinkage);

    // Set initializer (if present)
    if (initializer) {
      LLVMSetInitializer(_handle, initializer->value_of(ctx));
    } else {
      // Initialize to nil (for globals)
      LLVMSetInitializer(_handle, LLVMConstNull(type_handle));
    }
  }

  return _handle;
}
