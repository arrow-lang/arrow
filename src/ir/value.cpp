// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Value;

LLVMValueRef Value::value_of(GContext& ctx) noexcept {
  auto res = handle(ctx);

  if (type->is_reference()) {
    res = LLVMBuildLoad(ctx.irb, res, "");
  }

  if (is_addressable()) {
    res = LLVMBuildLoad(ctx.irb, res, "");
  }

  return res;
}

LLVMValueRef Value::address_of(GContext& ctx) noexcept {
  if (is_addressable()) {
    return handle(ctx);
  }

  // TODO(mehcode): Error message

  return nullptr;
}
