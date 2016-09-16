// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_call(ptr<ast::Call> x) -> ptr<ir::Value> {
  // Build: Operand
  auto operand = run(x->operand);
  if (!operand) return nullptr;

  // Assert: Operand is indeed a function
  if (!operand->type->is_function()) {
    Log::get().error(
      x->span, "expected function, found `{}`", operand->type->name);

    return nullptr;
  }

  // Get result type (of call)
  ptr<ir::Type> result_type = nullptr;
  if (isa<ir::TypeFunction>(operand->type)) {
    result_type = cast<ir::TypeFunction>(operand->type)->result;
  } else if (isa<ir::TypeExternFunction>(operand->type)) {
    result_type = cast<ir::TypeExternFunction>(operand->type)->result;
  } else {
    return nullptr;
  }

  // Make: Call
  auto item = make<ir::Call>(x, operand, result_type);

  // Build: Arguments
  for (auto& argument : x->arguments) {
    auto arg = run(argument);
    if (!arg) return nullptr;

    item->arguments.push_back(arg);
  }

  return item;
}

auto Build::handle_argument(ptr<ast::Argument> x) -> ptr<ir::Value> {
  return run(x->value);
}
