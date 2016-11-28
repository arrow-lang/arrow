// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"
#include "arrow/log.hpp"

using arrow::ir::Indirect;
using arrow::ir::AddressOf;

LLVMValueRef Indirect::handle(GContext& ctx) noexcept {
  if (operand->type->is_reference()) return LLVMBuildLoad(ctx.irb, operand->handle(ctx), "");
  return operand->value_of(ctx);
}

LLVMValueRef AddressOf::handle(GContext& ctx) noexcept {
  if (!operand->is_addressable()) {
    // TODO(mehcode): More descriptive error message?
    Log::get().error(source->span, "cannot take the address of the operand");

    return nullptr;
  }

  return operand->address_of(ctx);
}
