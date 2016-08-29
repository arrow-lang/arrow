// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Assign;

LLVMValueRef Assign::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = lhs->address_of(ctx);
    auto rhs_handle = rhs->value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    // Cast RHS to the type of the LHS
    // TODO(mehcode): Extract into util
    rhs_handle = LLVMBuildIntCast(
      ctx.irb, rhs_handle, lhs->type->handle(ctx), "");

    // Store
    LLVMBuildStore(ctx.irb, rhs_handle, lhs_handle);

    // Value is the RHS
    _handle = rhs_handle;
  }

  return _handle;
}
