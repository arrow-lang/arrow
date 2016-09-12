// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Add;
using arrow::ir::Sub;
using arrow::ir::Mul;
using arrow::ir::Div;
using arrow::ir::Mod;

LLVMValueRef Add::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = Transmute(lhs, type).value_of(ctx);
    auto rhs_handle = Transmute(rhs, type).value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    if (type->is_integer()) {
      _handle = LLVMBuildAdd(ctx.irb, lhs_handle, rhs_handle, "");
    } else if (type->is_real()) {
      _handle = LLVMBuildFAdd(ctx.irb, lhs_handle, rhs_handle, "");
    } else {
      throw std::runtime_error(fmt::format(
        "not implemented: add: {} + {}", lhs->type->name, rhs->type->name));
    }
  }

  return _handle;
}

LLVMValueRef Sub::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = Transmute(lhs, type).value_of(ctx);
    auto rhs_handle = Transmute(rhs, type).value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    _handle = LLVMBuildSub(ctx.irb, lhs_handle, rhs_handle, "");
  }

  return _handle;
}

LLVMValueRef Mul::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = Transmute(lhs, type).value_of(ctx);
    auto rhs_handle = Transmute(rhs, type).value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    _handle = LLVMBuildMul(ctx.irb, lhs_handle, rhs_handle, "");
  }

  return _handle;
}

LLVMValueRef Div::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = Transmute(lhs, type).value_of(ctx);
    auto rhs_handle = Transmute(rhs, type).value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    // TODO(mehcode): Handle UDiv vs SDiv

    _handle = LLVMBuildSDiv(ctx.irb, lhs_handle, rhs_handle, "");
  }

  return _handle;
}

LLVMValueRef Mod::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = Transmute(lhs, type).value_of(ctx);
    auto rhs_handle = Transmute(rhs, type).value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    // TODO(mehcode): Handle URem vs SRem

    _handle = LLVMBuildSRem(ctx.irb, lhs_handle, rhs_handle, "");
  }

  return _handle;
}
