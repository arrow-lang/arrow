// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Call;
using arrow::ir::Function;
using arrow::ir::ExternFunction;
using arrow::ir::Method;

LLVMValueRef Call::handle(GContext &ctx) noexcept {
  if (!_handle) {
    // Get the operand's type.. cast to a function type
    if (isa<ir::IFunction>(operand)) {
      _handle = cast<ir::IFunction>(operand)->invoke(ctx, arguments);
    } else {
      // TODO(mehcode): Handle a non-function call (error) ?
      // FIXME: Code dupe from Function::invoke
      // Realize the (function) type
      auto op_t = cast<ir::TypeFunction>(operand->type);
      if (!op_t) return nullptr;

      // Realize the (function) operand
      auto op = operand->value_of(ctx);
      if (!op) return nullptr;

      // Realize argument handles
      std::vector<LLVMValueRef> args;
      unsigned arg_i = 0;
      for (; arg_i < arguments.size() && arg_i < op_t->parameters.size(); ++arg_i) {
        auto arg_type = op_t->parameters.at(arg_i);
        LLVMValueRef arg_handle = nullptr;
        if (arg_type->is_reference()) {
          if (arguments[arg_i]->type->is_reference()) {
            arg_handle = LLVMBuildLoad(ctx.irb, arguments[arg_i]->handle(ctx), "");
          } else {
            arg_handle = arguments[arg_i]->address_of(ctx);
          }
        } else {
          arg_handle = Transmute(arguments[arg_i]->source, arguments[arg_i], arg_type).value_of(ctx);
        }
        if (!arg_handle) return nullptr;

        // Unit-typed arguments do not materialize
        if (!arg_type->is_unit()) {
          args.push_back(arg_handle);
        }
      }

      _handle = LLVMBuildCall(ctx.irb, op, args.data(), args.size(), "");
    }
  }

  return _handle;
}

LLVMValueRef Function::invoke(GContext& ctx, std::vector<ptr<Value>>& arguments) {
  // Realize the (function) type
  auto op_t = cast<ir::TypeFunction>(type);
  if (!op_t) return nullptr;

  // Realize the (function) operand
  auto op = this->value_of(ctx);
  if (!op) return nullptr;

  // Realize argument handles
  std::vector<LLVMValueRef> args;
  unsigned arg_i = 0;
  for (; arg_i < arguments.size() && arg_i < op_t->parameters.size(); ++arg_i) {
    auto arg_type = op_t->parameters.at(arg_i);
    LLVMValueRef arg_handle = nullptr;
    if (arg_type->is_reference()) {
      if (arguments[arg_i]->type->is_reference()) {
        arg_handle = LLVMBuildLoad(ctx.irb, arguments[arg_i]->handle(ctx), "");
      } else {
        arg_handle = arguments[arg_i]->address_of(ctx);
      }
    } else {
      arg_handle = Transmute(arguments[arg_i]->source, arguments[arg_i], arg_type).value_of(ctx);
    }
    if (!arg_handle) return nullptr;

    // Unit-typed arguments do not materialize
    if (!arg_type->is_unit()) {
      args.push_back(arg_handle);
    }
  }

  return LLVMBuildCall(ctx.irb, op, args.data(), args.size(), "");
}

LLVMValueRef ExternFunction::invoke(GContext& ctx, std::vector<ptr<Value>>& arguments) {
  // Realize the (function) type
  auto op_t = cast<ir::TypeExternFunction>(type);
  if (!op_t) return nullptr;

  // Realize the (function) operand
  auto op = this->value_of(ctx);
  if (!op) return nullptr;

  // Realize argument handles
  std::vector<LLVMValueRef> args;
  unsigned arg_i = 0;
  for (; arg_i < arguments.size() && arg_i < op_t->parameters.size(); ++arg_i) {
    auto arg_type = op_t->parameters.at(arg_i);
    auto arg_handle = Transmute(arguments[arg_i]->source, arguments[arg_i], arg_type).value_of(ctx);
    if (!arg_handle) return nullptr;

    // Unit-typed arguments do not materialize
    if (!arg_type->is_unit()) {
      args.push_back(arg_handle);
    }
  }

  // Realize varidac arguments (extern)
  if (op_t->is_varidac) {
    for (; arg_i < arguments.size(); ++arg_i) {
      auto& arg = arguments[arg_i];
      auto target_t = arg->type;

      // Perform C type promotion
      if ((target_t->is_boolean() || target_t->is_integer()) && target_t->size() < ctx.target_int_size) {
        target_t = make<ir::TypeInteger>(target_t->is_signed(), ctx.target_int_size);
      } else if (target_t->is_real() && target_t->size() < 64) {
        target_t = make<ir::TypeReal>(64);
      }

      auto arg_handle = Transmute(arg->source, arg, target_t).value_of(ctx);
      if (!arg_handle) return nullptr;

      args.push_back(arg_handle);
    }
  }

  auto result = LLVMBuildCall(ctx.irb, op, args.data(), args.size(), "");

  // Set calling convention (if external)
  auto cc = ir::parse_call_conv(source ? source->span : Span(""), op_t->abi);
  if (cc < 0) return nullptr;
  LLVMSetInstructionCallConv(result, cc);

  return result;
}

LLVMValueRef Method::invoke(GContext& ctx, std::vector<ptr<Value>>& arguments_) {
  std::vector<ptr<Value>> arguments = arguments_;
  arguments.insert(arguments.begin(), _self);

  return _function->invoke(ctx, arguments);
}
