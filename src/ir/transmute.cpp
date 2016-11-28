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
    auto src = ir::type_canonical(value->type);
    auto dst = ir::type_canonical(type);
    auto dst_handle = dst->handle(ctx);

    // fmt::print("transmute {} ({}) -> {} ({})\n", src->name, src->size(), dst->name, dst->size());

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
      auto src_size = src->size() == 0 ? 64 : src->size();
      auto dst_size = dst->size() == 0 ? 64 : dst->size();

      if (src->is_signed()) {
        if (src_size > dst_size) {
          _handle = LLVMBuildTrunc(ctx.irb, value_handle, dst_handle, "");
        } else {
          _handle = LLVMBuildSExt(ctx.irb, value_handle, dst_handle, "");
        }
      } else {
        if (src_size > dst_size) {
          _handle = LLVMBuildTrunc(ctx.irb, value_handle, dst_handle, "");
        } else {
          _handle = LLVMBuildZExt(ctx.irb, value_handle, dst_handle, "");
        }
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
    } else if (src->is_integer() && dst->is_pointer()) {
      _handle = LLVMBuildIntToPtr(ctx.irb, value_handle, dst_handle, "");
    } else if (src->is_pointer() && dst->is_integer()) {
      _handle = LLVMBuildPtrToInt(ctx.irb, value_handle, dst_handle, "");
    } else if (src->is_pointer() && dst->is_pointer()) {
      _handle = LLVMBuildBitCast(ctx.irb, value_handle, dst_handle, "");
    } else {
      throw std::runtime_error(fmt::format(
        "not implemented: transmute: {} -> {}", src->name, dst->name));
    }
  }

  return _handle;
}
