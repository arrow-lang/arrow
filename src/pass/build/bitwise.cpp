// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_bit_not(ptr<ast::BitNot> x) -> ptr<ir::Value> {
  auto operand = run(x->operand);
  if (!operand) return nullptr;

  if (!(operand->type->is_integer())) {
    Log::get().error(x->span,
      "unsupported operand type for `~`: `{}`",
      operand->type->name);

    return nullptr;
  }

  return make<ir::BitNot>(x, operand->type, operand);
}

auto Build::handle_bit_and(ptr<ast::BitAnd> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  auto type = ir::type_reduce(lhs->type, rhs->type);
  if (!type || !(type->is_integer() || type->is_boolean())) {
    Log::get().error(x->span,
      "unsupported operand types for `&`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::BitAnd>(x, type, lhs, rhs);
}

auto Build::handle_bit_or(ptr<ast::BitOr> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  auto type = ir::type_reduce(lhs->type, rhs->type);
  if (!type || !(type->is_integer() || type->is_boolean())) {
    Log::get().error(x->span,
      "unsupported operand types for `|`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::BitOr>(x, type, lhs, rhs);
}

auto Build::handle_bit_xor(ptr<ast::BitXor> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  auto type = ir::type_reduce(lhs->type, rhs->type);
  if (!type || !(type->is_integer() || type->is_boolean())) {
    Log::get().error(x->span,
      "unsupported operand types for `^`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::BitXor>(x, type, lhs, rhs);
}
