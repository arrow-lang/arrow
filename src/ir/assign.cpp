// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Assign;

LLVMValueRef Assign::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = lhs->address_of(ctx);
    auto rhs_handle = transmute(rhs, lhs->type)->value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    // Store
    LLVMBuildStore(ctx.irb, rhs_handle, lhs_handle);

    // Value is the RHS
    _handle = rhs_handle;
  }

  return _handle;
}
