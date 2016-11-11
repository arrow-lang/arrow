// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Assign;
using arrow::ir::AssignAdd;
using arrow::ir::AssignSub;
using arrow::ir::AssignMul;
using arrow::ir::AssignDiv;
using arrow::ir::AssignMod;
using arrow::ir::AssignBitAnd;
using arrow::ir::AssignBitOr;
using arrow::ir::AssignBitXor;
using arrow::ir::AssignBitLeftShift;
using arrow::ir::AssignBitRightShift;

LLVMValueRef Assign::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = lhs->address_of(ctx);
    auto rhs_handle = transmute(rhs, lhs->type)->value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    // Store
    LLVMBuildStore(ctx.irb, rhs_handle, lhs_handle);

    // Value is the RHS
    _handle = rhs_handle;
  }

  return _handle;
}

LLVMValueRef AssignAdd::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_value_handle = lhs->value_of(ctx);
    auto lhs_handle = lhs->address_of(ctx);

    // Add
    auto rhs_handle = transmute(
      make<ir::Add>(source, type, lhs, rhs), lhs->type)->value_of(ctx);

    if (!lhs_value_handle || !lhs_handle || !rhs_handle) return nullptr;

    // Store
    LLVMBuildStore(ctx.irb, rhs_handle, lhs_handle);

    // Value is the RHS
    _handle = rhs_handle;
  }

  return _handle;
}

LLVMValueRef AssignSub::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_value_handle = lhs->value_of(ctx);
    auto lhs_handle = lhs->address_of(ctx);

    // Sub
    auto rhs_handle = transmute(
      make<ir::Sub>(source, type, lhs, rhs), lhs->type)->value_of(ctx);

    if (!lhs_value_handle || !lhs_handle || !rhs_handle) return nullptr;

    // Store
    LLVMBuildStore(ctx.irb, rhs_handle, lhs_handle);

    // Value is the RHS
    _handle = rhs_handle;
  }

  return _handle;
}

LLVMValueRef AssignMul::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_value_handle = lhs->value_of(ctx);
    auto lhs_handle = lhs->address_of(ctx);

    // Mul
    auto rhs_handle = transmute(
      make<ir::Mul>(source, type, lhs, rhs), lhs->type)->value_of(ctx);

    if (!lhs_value_handle || !lhs_handle || !rhs_handle) return nullptr;

    // Store
    LLVMBuildStore(ctx.irb, rhs_handle, lhs_handle);

    // Value is the RHS
    _handle = rhs_handle;
  }

  return _handle;
}

LLVMValueRef AssignDiv::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_value_handle = lhs->value_of(ctx);
    auto lhs_handle = lhs->address_of(ctx);

    // Div
    auto rhs_handle = transmute(
      make<ir::Div>(source, type, lhs, rhs), lhs->type)->value_of(ctx);

    if (!lhs_value_handle || !lhs_handle || !rhs_handle) return nullptr;

    // Store
    LLVMBuildStore(ctx.irb, rhs_handle, lhs_handle);

    // Value is the RHS
    _handle = rhs_handle;
  }

  return _handle;
}

LLVMValueRef AssignMod::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_value_handle = lhs->value_of(ctx);
    auto lhs_handle = lhs->address_of(ctx);

    // Mod
    auto rhs_handle = transmute(
      make<ir::Mod>(source, type, lhs, rhs), lhs->type)->value_of(ctx);

    if (!lhs_value_handle || !lhs_handle || !rhs_handle) return nullptr;

    // Store
    LLVMBuildStore(ctx.irb, rhs_handle, lhs_handle);

    // Value is the RHS
    _handle = rhs_handle;
  }

  return _handle;
}

LLVMValueRef AssignBitAnd::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_value_handle = lhs->value_of(ctx);
    auto lhs_handle = lhs->address_of(ctx);

    // BitAnd
    auto rhs_handle = transmute(
      make<ir::BitAnd>(source, type, lhs, rhs), lhs->type)->value_of(ctx);

    if (!lhs_value_handle || !lhs_handle || !rhs_handle) return nullptr;

    // Store
    LLVMBuildStore(ctx.irb, rhs_handle, lhs_handle);

    // Value is the RHS
    _handle = rhs_handle;
  }

  return _handle;
}

LLVMValueRef AssignBitOr::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_value_handle = lhs->value_of(ctx);
    auto lhs_handle = lhs->address_of(ctx);

    // BitOr
    auto rhs_handle = transmute(
      make<ir::BitOr>(source, type, lhs, rhs), lhs->type)->value_of(ctx);

    if (!lhs_value_handle || !lhs_handle || !rhs_handle) return nullptr;

    // Store
    LLVMBuildStore(ctx.irb, rhs_handle, lhs_handle);

    // Value is the RHS
    _handle = rhs_handle;
  }

  return _handle;
}

LLVMValueRef AssignBitXor::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_value_handle = lhs->value_of(ctx);
    auto lhs_handle = lhs->address_of(ctx);

    // BitXor
    auto rhs_handle = transmute(
      make<ir::BitXor>(source, type, lhs, rhs), lhs->type)->value_of(ctx);

    if (!lhs_value_handle || !lhs_handle || !rhs_handle) return nullptr;

    // Store
    LLVMBuildStore(ctx.irb, rhs_handle, lhs_handle);

    // Value is the RHS
    _handle = rhs_handle;
  }

  return _handle;
}

LLVMValueRef AssignBitLeftShift::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_value_handle = lhs->value_of(ctx);
    auto lhs_handle = lhs->address_of(ctx);

    // BitLeftShift
    auto rhs_handle = transmute(
      make<ir::BitLeftShift>(source, type, lhs, rhs), lhs->type)->value_of(ctx);

    if (!lhs_value_handle || !lhs_handle || !rhs_handle) return nullptr;

    // Store
    LLVMBuildStore(ctx.irb, rhs_handle, lhs_handle);

    // Value is the RHS
    _handle = rhs_handle;
  }

  return _handle;
}

LLVMValueRef AssignBitRightShift::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_value_handle = lhs->value_of(ctx);
    auto lhs_handle = lhs->address_of(ctx);

    // BitRightShift
    auto rhs_handle = transmute(
      make<ir::BitRightShift>(source, type, lhs, rhs), lhs->type)->value_of(ctx);

    if (!lhs_value_handle || !lhs_handle || !rhs_handle) return nullptr;

    // Store
    LLVMBuildStore(ctx.irb, rhs_handle, lhs_handle);

    // Value is the RHS
    _handle = rhs_handle;
  }

  return _handle;
}
