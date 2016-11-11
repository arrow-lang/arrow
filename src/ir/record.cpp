// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::RecordMember;

LLVMValueRef RecordMember::handle(GContext& ctx) noexcept {
  if (!_handle) {
    _handle = LLVMBuildStructGEP(ctx.irb, operand->address_of(ctx), index, "");
  }

  return _handle;
}
