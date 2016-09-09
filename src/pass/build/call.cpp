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
  auto type = cast<ir::TypeFunction>(operand->type);
  if (!type) {
    Log::get().error(
      x->span, "expected function, found `{}`", operand->type->name);

    return nullptr;
  }

  // Make: Call
  auto item = make<ir::Call>(x, operand, type->result);

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
