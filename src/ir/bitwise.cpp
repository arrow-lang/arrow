// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::BitNot;
using arrow::ir::BitAnd;
using arrow::ir::BitOr;
using arrow::ir::BitXor;
using arrow::ir::BitLeftShift;
using arrow::ir::BitRightShift;

LLVMValueRef BitNot::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto op_handle = transmute(operand, type)->value_of(ctx);
    if (!op_handle) return nullptr;

    _handle = LLVMBuildNot(ctx.irb, op_handle, "");
  }

  return _handle;
}

LLVMValueRef BitAnd::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = transmute(lhs, type)->value_of(ctx);
    auto rhs_handle = transmute(rhs, type)->value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    _handle = LLVMBuildAnd(ctx.irb, lhs_handle, rhs_handle, "");
  }

  return _handle;
}

LLVMValueRef BitOr::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = transmute(lhs, type)->value_of(ctx);
    auto rhs_handle = transmute(rhs, type)->value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    _handle = LLVMBuildOr(ctx.irb, lhs_handle, rhs_handle, "");
  }

  return _handle;
}

LLVMValueRef BitXor::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = transmute(lhs, type)->value_of(ctx);
    auto rhs_handle = transmute(rhs, type)->value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    _handle = LLVMBuildXor(ctx.irb, lhs_handle, rhs_handle, "");
  }

  return _handle;
}

// TODO: Handle << / >> by negative

LLVMValueRef BitLeftShift::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = lhs->value_of(ctx);
    auto rhs_handle = transmute(rhs, lhs->type)->value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    _handle = LLVMBuildShl(ctx.irb, lhs_handle, rhs_handle, "");
  }

  return _handle;
}

LLVMValueRef BitRightShift::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = lhs->value_of(ctx);
    auto rhs_handle = transmute(rhs, lhs->type)->value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    if (lhs->type->is_signed()) {
      _handle = LLVMBuildAShr(ctx.irb, lhs_handle, rhs_handle, "");
    } else {
      _handle = LLVMBuildLShr(ctx.irb, lhs_handle, rhs_handle, "");
    }
  }

  return _handle;
}
