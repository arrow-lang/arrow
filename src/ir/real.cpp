// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Real;

LLVMValueRef Real::handle(GContext& ctx) noexcept {
  auto type_handle = type->handle(ctx);

  return LLVMConstReal(type_handle, value);
}
