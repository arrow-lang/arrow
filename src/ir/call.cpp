// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Call;

LLVMValueRef Call::handle(GContext &ctx) noexcept {
  // Get the operand's type.. cast to a function type
  // TODO(mehcode): Handle a non-function call (error) ?
  auto op_type = operand->type;

  // Realize the (function) operand
  auto op_handle = operand->value_of(ctx);
  if (!op_handle) return nullptr;

  // Get reference to parameter types
  std::vector<ptr<ir::Type>>& params =
    isa<ir::TypeFunction>(op_type) ?
    cast<ir::TypeFunction>(op_type)->parameters :
    cast<ir::TypeExternFunction>(op_type)->parameters;

  // Realize argument handles
  std::vector<LLVMValueRef> args;
  unsigned arg_i = 0;
  for (; arg_i < arguments.size() && arg_i < params.size(); ++arg_i) {
    auto arg_type = params.at(arg_i);
    auto arg_handle = Transmute(arguments[arg_i]->source, arguments[arg_i], arg_type).value_of(ctx);
    if (!arg_handle) return nullptr;

    args.push_back(arg_handle);
  }

  // Realize varidac arguments (extern)
  if (isa<ir::TypeExternFunction>(op_type) &&
      cast<ir::TypeExternFunction>(op_type)->is_varidac) {
    for (; arg_i < arguments.size(); ++arg_i) {
      auto& arg = arguments[arg_i];
      auto target_t = arg->type;

      // Perform C type promotion
      // FIXME(mehcode): Get proper size of C INT here
      if ((target_t->is_boolean() || target_t->is_integer()) && target_t->size() < 32) {
        target_t = make<ir::TypeInteger>(target_t->is_signed(), 32);
      } else if (target_t->is_real() && target_t->size() < 64) {
        target_t = make<ir::TypeReal>(64);
      }

      auto arg_handle = Transmute(arg->source, arg, target_t).value_of(ctx);
      if (!arg_handle) return nullptr;

      args.push_back(arg_handle);
    }
  }

  auto result = LLVMBuildCall(ctx.irb, op_handle, args.data(), args.size(), "");
  return result;
}
