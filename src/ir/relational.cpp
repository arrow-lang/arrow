// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::EqualTo;
using arrow::ir::NotEqualTo;
using arrow::ir::LessThan;
using arrow::ir::LessThanOrEqualTo;
using arrow::ir::GreaterThan;
using arrow::ir::GreaterThanOrEqualTo;

LLVMValueRef EqualTo::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = Transmute(lhs, type).value_of(ctx);
    auto rhs_handle = Transmute(rhs, type).value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    if (type->is_integer()) {
      _handle = LLVMBuildICmp(ctx.irb, LLVMIntEQ, lhs_handle, rhs_handle, "");
    } else if (type->is_real()) {
      _handle = LLVMBuildFCmp(ctx.irb, LLVMRealOEQ, lhs_handle, rhs_handle, "");
    } else {
      throw std::runtime_error(fmt::format(
        "not implemented: eq: {} == {}", lhs->type->name, rhs->type->name));
    }
  }

  return _handle;
}

LLVMValueRef NotEqualTo::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = Transmute(lhs, type).value_of(ctx);
    auto rhs_handle = Transmute(rhs, type).value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    if (type->is_integer()) {
      _handle = LLVMBuildICmp(ctx.irb, LLVMIntNE, lhs_handle, rhs_handle, "");
    } else if (type->is_real()) {
      _handle = LLVMBuildFCmp(ctx.irb, LLVMRealONE, lhs_handle, rhs_handle, "");
    } else {
      throw std::runtime_error(fmt::format(
        "not implemented: ne: {} != {}", lhs->type->name, rhs->type->name));
    }
  }

  return _handle;
}

LLVMValueRef LessThan::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = Transmute(lhs, type).value_of(ctx);
    auto rhs_handle = Transmute(rhs, type).value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    if (type->is_integer()) {
      if (type->is_signed()) {
        _handle = LLVMBuildICmp(ctx.irb, LLVMIntSLT, lhs_handle, rhs_handle, "");
      } else {
        _handle = LLVMBuildICmp(ctx.irb, LLVMIntULT, lhs_handle, rhs_handle, "");
      }
    } else if (type->is_real()) {
      _handle = LLVMBuildFCmp(ctx.irb, LLVMRealOLT, lhs_handle, rhs_handle, "");
    } else {
      throw std::runtime_error(fmt::format(
        "not implemented: lt: {} < {}", lhs->type->name, rhs->type->name));
    }
  }

  return _handle;
}

LLVMValueRef LessThanOrEqualTo::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = Transmute(lhs, type).value_of(ctx);
    auto rhs_handle = Transmute(rhs, type).value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    if (type->is_integer()) {
      if (type->is_signed()) {
        _handle = LLVMBuildICmp(ctx.irb, LLVMIntSLE, lhs_handle, rhs_handle, "");
      } else {
        _handle = LLVMBuildICmp(ctx.irb, LLVMIntULE, lhs_handle, rhs_handle, "");
      }
    } else if (type->is_real()) {
      _handle = LLVMBuildFCmp(ctx.irb, LLVMRealOLE, lhs_handle, rhs_handle, "");
    } else {
      throw std::runtime_error(fmt::format(
        "not implemented: le: {} <= {}", lhs->type->name, rhs->type->name));
    }
  }

  return _handle;
}

LLVMValueRef GreaterThan::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = Transmute(lhs, type).value_of(ctx);
    auto rhs_handle = Transmute(rhs, type).value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    if (type->is_integer()) {
      if (type->is_signed()) {
        _handle = LLVMBuildICmp(ctx.irb, LLVMIntSGT, lhs_handle, rhs_handle, "");
      } else {
        _handle = LLVMBuildICmp(ctx.irb, LLVMIntUGT, lhs_handle, rhs_handle, "");
      }
    } else if (type->is_real()) {
      _handle = LLVMBuildFCmp(ctx.irb, LLVMRealOGT, lhs_handle, rhs_handle, "");
    } else {
      throw std::runtime_error(fmt::format(
        "not implemented: gt: {} > {}", lhs->type->name, rhs->type->name));
    }
  }

  return _handle;
}

LLVMValueRef GreaterThanOrEqualTo::handle(GContext &ctx) noexcept {
  if (!_handle) {
    auto lhs_handle = Transmute(lhs, type).value_of(ctx);
    auto rhs_handle = Transmute(rhs, type).value_of(ctx);
    if (!lhs_handle || !rhs_handle) return nullptr;

    if (type->is_integer()) {
      if (type->is_signed()) {
        _handle = LLVMBuildICmp(ctx.irb, LLVMIntSGE, lhs_handle, rhs_handle, "");
      } else {
        _handle = LLVMBuildICmp(ctx.irb, LLVMIntUGE, lhs_handle, rhs_handle, "");
      }
    } else if (type->is_real()) {
      _handle = LLVMBuildFCmp(ctx.irb, LLVMRealOGE, lhs_handle, rhs_handle, "");
    } else {
      throw std::runtime_error(fmt::format(
        "not implemented: ge: {} >= {}", lhs->type->name, rhs->type->name));
    }
  }

  return _handle;
}
