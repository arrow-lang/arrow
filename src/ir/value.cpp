// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Value;

LLVMValueRef Value::value_of(GContext& ctx) noexcept {
  if (is_addressable()) {
    return LLVMBuildLoad(ctx.irb, handle(ctx), "");
  }

  return handle(ctx);
}

LLVMValueRef Value::address_of(GContext& ctx) noexcept {
  if (is_addressable()) {
    return handle(ctx);
  }

  // TODO(mehcode): Error message

  return nullptr;
}
