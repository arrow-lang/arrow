// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Transmute;

LLVMValueRef Transmute::handle(GContext& ctx) noexcept {
  if (!_handle) {
    // TODO(mehcode): Type determination rather than hard-coding an intcast in here

    auto value_handle = value->value_of(ctx);
    if (!value_handle) return nullptr;

    _handle = LLVMBuildIntCast(ctx.irb, value_handle, type->handle(ctx), "");
  }

  return _handle;
}
