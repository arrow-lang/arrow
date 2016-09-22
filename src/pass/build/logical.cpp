// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_not(ptr<ast::Not> x) -> ptr<ir::Value> {
  auto operand = run(x->operand);
  if (!operand) return nullptr;

  if (!(operand->type->is_boolean())) {
    Log::get().error(x->span,
      "unsupported operand type for `not`: `{}`",
      operand->type->name);

    return nullptr;
  }

  return make<ir::Not>(x, operand->type, operand);
}

auto Build::handle_and(ptr<ast::And> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  if (!(lhs->type->is_boolean() && rhs->type->is_boolean())) {
    Log::get().error(x->span,
      "unsupported operand types for `and`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::And>(x, lhs->type, lhs, rhs);
}

auto Build::handle_or(ptr<ast::Or> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  if (!(lhs->type->is_boolean() && rhs->type->is_boolean())) {
    Log::get().error(x->span,
      "unsupported operand types for `or`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::Or>(x, lhs->type, lhs, rhs);
}
