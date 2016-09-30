// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/pass/type_deduce.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_identity(ptr<ast::Identity> x) -> ptr<ir::Value> {
  auto operand = run(x->operand);
  if (!operand) return nullptr;

  auto type = TypeDeduce(_ctx).run(x);
  if (!type) {
    Log::get().error(x->span,
      "unsupported operand type for `+`: `{}`",
      operand->type->name);

    return nullptr;
  }

  return operand;
}

auto Build::handle_negate(ptr<ast::Negate> x) -> ptr<ir::Value> {
  auto operand = run(x->operand);
  if (!operand) return nullptr;

  auto type = TypeDeduce(_ctx).run(x);
  if (!type) {
    Log::get().error(x->span,
      "unsupported operand type for `-`: `{}`",
      operand->type->name);

    return nullptr;
  }

  return make<ir::Negate>(x, operand->type, operand);
}

auto Build::handle_add(ptr<ast::Add> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  auto type = TypeDeduce(_ctx).run(x);
  if (!type) {
    Log::get().error(x->span,
      "unsupported operand types for `+`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::Add>(x, type, lhs, rhs);
}

auto Build::handle_sub(ptr<ast::Sub> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  auto type = TypeDeduce(_ctx).run(x);
  if (!type) {
    Log::get().error(x->span,
      "unsupported operand types for `-`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::Sub>(x, type, lhs, rhs);
}

auto Build::handle_mul(ptr<ast::Mul> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  auto type = TypeDeduce(_ctx).run(x);
  if (!type) {
    Log::get().error(x->span,
      "unsupported operand types for `*`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::Mul>(x, type, lhs, rhs);
}

auto Build::handle_div(ptr<ast::Div> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // Determine the appropriate type
  auto type = TypeDeduce(_ctx).run(x);
  if (!type) {
    return nullptr;
  }

  return make<ir::Div>(x, type, lhs, rhs);
}

auto Build::handle_mod(ptr<ast::Mod> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // Determine the appropriate type
  auto type = TypeDeduce(_ctx).run(x);
  if (!type) {
    Log::get().error(x->span,
      "unsupported operand types for `%`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::Mod>(x, type, lhs, rhs);
}
