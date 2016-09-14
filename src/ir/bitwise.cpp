// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::BitNot;
using arrow::ir::BitAnd;
using arrow::ir::BitOr;
using arrow::ir::BitXor;

LLVMValueRef BitNot::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto op_handle = Transmute(operand, type).value_of(ctx);
    if (!op_handle) return nullptr;

    _handle = LLVMBuildNot(ctx.irb, op_handle, "");
  }

  return _handle;
}

LLVMValueRef BitAnd::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = Transmute(lhs, type).value_of(ctx);
    auto rhs_handle = Transmute(rhs, type).value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    _handle = LLVMBuildAnd(ctx.irb, lhs_handle, rhs_handle, "");
  }

  return _handle;
}

LLVMValueRef BitOr::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = Transmute(lhs, type).value_of(ctx);
    auto rhs_handle = Transmute(rhs, type).value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    _handle = LLVMBuildOr(ctx.irb, lhs_handle, rhs_handle, "");
  }

  return _handle;
}

LLVMValueRef BitXor::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = Transmute(lhs, type).value_of(ctx);
    auto rhs_handle = Transmute(rhs, type).value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    _handle = LLVMBuildXor(ctx.irb, lhs_handle, rhs_handle, "");
  }

  return _handle;
}
