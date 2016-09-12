// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Transmute;

LLVMValueRef Transmute::handle(GContext& ctx) noexcept {
  if (!_handle) {
    auto src = value->type;
    auto dst = type;
    auto dst_handle = type->handle(ctx);

    auto value_handle = value->value_of(ctx);
    if (!value_handle) return nullptr;

    auto is_real = (isa<ir::TypeReal>(dst) || isa<ir::TypeLiteralReal>(dst));
    auto is_int = (isa<ir::TypeInteger>(dst) || isa<ir::TypeLiteralInteger>(dst));

    if (is_real) {
      _handle = LLVMBuildFPCast(ctx.irb, value_handle, dst_handle, "");
    } else if (is_int) {
      _handle = LLVMBuildIntCast(ctx.irb, value_handle, type->handle(ctx), "");
    } else {
      // TODO: Say what types
      throw std::runtime_error("transmute not implemented");
    }
  }

  return _handle;
}
