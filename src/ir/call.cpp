// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Call;

LLVMValueRef Call::handle(GContext &ctx) noexcept {
  // Get the operand's type.. cast to a function type
  // TODO: Handle a non-function call (error) ?
  auto op_type = operand->type;
  auto op_type_f = cast<ir::TypeFunction>(op_type);
  if (!op_type_f) return nullptr;

  // Realize the operand
  auto op_handle = operand->value_of(ctx);
  if (!op_handle) return nullptr;

  // Realize argument handles
  std::vector<LLVMValueRef> args;
  auto arg_index = 0;
  for (auto& argument : arguments) {
    auto arg_type = op_type_f->parameters.at(arg_index++);
    auto arg_handle = Transmute(argument, arg_type).value_of(ctx);
    if (!arg_handle) return nullptr;

    args.push_back(arg_handle);
  }

  auto result = LLVMBuildCall(ctx.irb, op_handle, args.data(), args.size(), "");
  return result;
}
