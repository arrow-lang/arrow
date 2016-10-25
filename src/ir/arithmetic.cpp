// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Negate;
using arrow::ir::Add;
using arrow::ir::Sub;
using arrow::ir::Mul;
using arrow::ir::Div;
using arrow::ir::Mod;

LLVMValueRef Negate::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto op_handle = transmute(operand, type)->value_of(ctx);
    if (!op_handle) return nullptr;

    if (type->is_integer()) {
      _handle = LLVMBuildNeg(ctx.irb, op_handle, "");
    } else if (type->is_real()) {
      _handle = LLVMBuildFNeg(ctx.irb, op_handle, "");
    } else {
      throw std::runtime_error(fmt::format(
        "not implemented: negate: {}", operand->type->name));
    }
  }

  return _handle;
}

LLVMValueRef Add::handle(GContext &ctx) noexcept {
  if (!_handle) {
    if (type->is_pointer()) {
      // <pointer> + integer
      if (lhs->type->is_pointer() && !rhs->type->is_pointer()) {
        auto intptr_t = make<ir::TypeInteger>(
          rhs->type->is_signed(), LLVMPointerSize(ctx.target_data) * 8);

        auto lhs_handle = lhs->value_of(ctx);
        auto rhs_handle = ir::transmute(rhs, intptr_t)->value_of(ctx);

        _handle = LLVMBuildGEP(ctx.irb, lhs_handle, &rhs_handle, 1, "");
      } else if (rhs->type->is_pointer()) {
        auto intptr_t = make<ir::TypeInteger>(
          lhs->type->is_signed(), LLVMPointerSize(ctx.target_data) * 8);

        auto lhs_handle = ir::transmute(lhs, intptr_t)->value_of(ctx);
        auto rhs_handle = rhs->value_of(ctx);

        _handle = LLVMBuildGEP(ctx.irb, rhs_handle, &lhs_handle, 1, "");
      }

      if (_handle) return _handle;
    }

    auto lhs_handle = transmute(lhs, type)->value_of(ctx);
    auto rhs_handle = transmute(rhs, type)->value_of(ctx);
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
    if (type->is_pointer()) {
      // <pointer> - integer
      if (lhs->type->is_pointer() && rhs->type->is_integer()) {
        auto intptr_t = make<ir::TypeInteger>(
          rhs->type->is_signed(), LLVMPointerSize(ctx.target_data) * 8);

        auto lhs_handle = lhs->value_of(ctx);
        auto rhs_handle = ir::transmute(rhs, intptr_t)->value_of(ctx);

        rhs_handle = LLVMBuildNeg(ctx.irb, rhs_handle, "");
        _handle = LLVMBuildGEP(ctx.irb, lhs_handle, &rhs_handle, 1, "");

        return _handle;
      }
    } else if (
        lhs->type->is_pointer() && rhs->type->is_pointer() &&
        type->is_integer()) {
      // <pointer> - <pointer>
      // Run PtrToInt on both pointers
      auto intptr_t = LLVMIntPtrType(ctx.target_data);
      auto lhs_handle = LLVMBuildPtrToInt(
        ctx.irb, lhs->value_of(ctx), intptr_t, "");
      auto rhs_handle = LLVMBuildPtrToInt(
        ctx.irb, rhs->value_of(ctx), intptr_t, "");

      // Find the length
      _handle = LLVMBuildSub(ctx.irb, lhs_handle, rhs_handle, "");

      // Get the size (in bytes) of the underlying type
      auto sizeb = LLVMSizeOf(
        cast<ir::TypePointer>(lhs->type)->element->handle(ctx));

      // Perform an integral division to find the -number- of elements.
      _handle = LLVMBuildExactSDiv(ctx.irb, _handle, sizeb, "");

      return _handle;
    }

    auto lhs_handle = transmute(lhs, type)->value_of(ctx);
    auto rhs_handle = transmute(rhs, type)->value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    if (type->is_integer()) {
      _handle = LLVMBuildSub(ctx.irb, lhs_handle, rhs_handle, "");
    } else if (type->is_real()) {
      _handle = LLVMBuildFSub(ctx.irb, lhs_handle, rhs_handle, "");
    } else {
      throw std::runtime_error(fmt::format(
        "not implemented: sub: {} - {}", lhs->type->name, rhs->type->name));
    }
  }

  return _handle;
}

LLVMValueRef Mul::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = transmute(lhs, type)->value_of(ctx);
    auto rhs_handle = transmute(rhs, type)->value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    if (type->is_integer()) {
      _handle = LLVMBuildMul(ctx.irb, lhs_handle, rhs_handle, "");
    } else if (type->is_real()) {
      _handle = LLVMBuildFMul(ctx.irb, lhs_handle, rhs_handle, "");
    } else {
      throw std::runtime_error(fmt::format(
        "not implemented: mul: {} * {}", lhs->type->name, rhs->type->name));
    }
  }

  return _handle;
}

LLVMValueRef Div::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = transmute(lhs, type)->value_of(ctx);
    auto rhs_handle = transmute(rhs, type)->value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    if (type->is_integer()) {
      if (type->is_signed()) {
        _handle = LLVMBuildSDiv(ctx.irb, lhs_handle, rhs_handle, "");
      } else {
        _handle = LLVMBuildUDiv(ctx.irb, lhs_handle, rhs_handle, "");
      }
    } else if (type->is_real()) {
      _handle = LLVMBuildFDiv(ctx.irb, lhs_handle, rhs_handle, "");
    } else {
      throw std::runtime_error(fmt::format(
        "not implemented: div: {} / {}", lhs->type->name, rhs->type->name));
    }
  }

  return _handle;
}

LLVMValueRef Mod::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = transmute(lhs, type)->value_of(ctx);
    auto rhs_handle = transmute(rhs, type)->value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    if (type->is_integer()) {
      if (type->is_signed()) {
        _handle = LLVMBuildSRem(ctx.irb, lhs_handle, rhs_handle, "");
      } else {
        _handle = LLVMBuildURem(ctx.irb, lhs_handle, rhs_handle, "");
      }
    } else if (type->is_real()) {
      _handle = LLVMBuildFRem(ctx.irb, lhs_handle, rhs_handle, "");
    } else {
      throw std::runtime_error(fmt::format(
        "not implemented: mod: {} % {}", lhs->type->name, rhs->type->name));
    }
  }

  return _handle;
}
