// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Transmute;
using arrow::ptr;
using arrow::isa;
namespace ir = arrow::ir;

LLVMValueRef Transmute::handle(GContext& ctx) noexcept {
  if (!_handle) {
    auto src = value->type;
    auto dst = type;
    auto dst_handle = type->handle(ctx);

    auto value_handle = value->value_of(ctx);
    if (!value_handle) return nullptr;

    if (dst->is_equal(src)) {
      // If same type .. no cast is needed
      _handle = value_handle;
    } else if (dst->is_real() && src->is_real()) {
      // Real -> Real
      _handle = LLVMBuildFPCast(ctx.irb, value_handle, dst_handle, "");
    } else if (dst->is_integer() && (src->is_integer() || src->is_boolean())) {
      // Integer -> Integer
      if (src->is_signed() && src->size() > 0) {
        if (src->size() > dst->size()) {
          _handle = LLVMBuildTrunc(ctx.irb, value_handle, dst_handle, "");
        } else {
          _handle = LLVMBuildSExt(ctx.irb, value_handle, dst_handle, "");
        }
      } else if (src->size() > 0) {
        if (src->size() > dst->size()) {
          _handle = LLVMBuildTrunc(ctx.irb, value_handle, dst_handle, "");
        } else {
          _handle = LLVMBuildZExt(ctx.irb, value_handle, dst_handle, "");
        }
      } else {
        _handle = LLVMBuildIntCast(ctx.irb, value_handle, dst_handle, "");
      }
    } else if (dst->is_real() && src->is_integer()) {
      // Integer -> Real
      if (src->is_signed()) {
        _handle = LLVMBuildSIToFP(ctx.irb, value_handle, dst_handle, "");
      } else {
        _handle = LLVMBuildUIToFP(ctx.irb, value_handle, dst_handle, "");
      }
    } else if (dst->is_integer() && src->is_real()) {
      // Real -> Integer
      if (dst->is_signed()) {
        _handle = LLVMBuildFPToSI(ctx.irb, value_handle, dst_handle, "");
      } else {
        _handle = LLVMBuildFPToUI(ctx.irb, value_handle, dst_handle, "");
      }
    } else {
      throw std::runtime_error(fmt::format(
        "not implemented: transmute: {} -> {}", src->name, dst->name));
    }
  }

  return _handle;
}
