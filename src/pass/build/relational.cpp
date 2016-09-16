// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_eq(ptr<ast::EqualTo> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  auto type = ir::type_reduce(lhs->type, rhs->type);
  if (!type) {
    Log::get().error(x->span,
      "unsupported operand types for `==`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::EqualTo>(make<ir::TypeBoolean>(), lhs, rhs);
}

auto Build::handle_ne(ptr<ast::NotEqualTo> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  auto type = ir::type_reduce(lhs->type, rhs->type);
  if (!type) {
    Log::get().error(x->span,
      "unsupported operand types for `!=`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::NotEqualTo>(make<ir::TypeBoolean>(), lhs, rhs);
}

auto Build::handle_lt(ptr<ast::LessThan> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  auto type = ir::type_reduce(lhs->type, rhs->type);
  if (!type) {
    Log::get().error(x->span,
      "unsupported operand types for `<`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::LessThan>(make<ir::TypeBoolean>(), lhs, rhs);
}

auto Build::handle_le(ptr<ast::LessThanOrEqualTo> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  auto type = ir::type_reduce(lhs->type, rhs->type);
  if (!type) {
    Log::get().error(x->span,
      "unsupported operand types for `<=`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::LessThanOrEqualTo>(make<ir::TypeBoolean>(), lhs, rhs);
}

auto Build::handle_gt(ptr<ast::GreaterThan> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  auto type = ir::type_reduce(lhs->type, rhs->type);
  if (!type) {
    Log::get().error(x->span,
      "unsupported operand types for `>`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::GreaterThan>(make<ir::TypeBoolean>(), lhs, rhs);
}

auto Build::handle_ge(ptr<ast::GreaterThanOrEqualTo> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  auto type = ir::type_reduce(lhs->type, rhs->type);
  if (!type) {
    Log::get().error(x->span,
      "unsupported operand types for `>=`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::GreaterThanOrEqualTo>(make<ir::TypeBoolean>(), lhs, rhs);
}
