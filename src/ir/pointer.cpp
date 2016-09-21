// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Indirect;
using arrow::ir::AddressOf;

LLVMValueRef Indirect::handle(GContext& ctx) noexcept {
  return operand->value_of(ctx);
}

LLVMValueRef AddressOf::handle(GContext& ctx) noexcept {
  return operand->address_of(ctx);
}
