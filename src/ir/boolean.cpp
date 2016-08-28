// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Boolean;

LLVMValueRef Boolean::handle(GContext& ctx) noexcept {
  return LLVMConstInt(type->handle(ctx), value ? 1 : 0, false);
}
