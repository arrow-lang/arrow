// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_identity(ptr<ast::Identity> x) -> ptr<ir::Value> {
  auto operand = run(x->operand);
  if (!operand) return nullptr;

  if (!(operand->type->is_integer() || operand->type->is_real())) {
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

  if (!(operand->type->is_integer() || operand->type->is_real())) {
    Log::get().error(x->span,
      "unsupported operand type for `-`: `{}`",
      operand->type->name);

    return nullptr;
  }

  return make<ir::Negate>(operand->type, operand);
}

auto Build::handle_add(ptr<ast::Add> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // Determine the appropriate type
  auto type = _type_reduce_a(lhs->type, rhs->type);
  if (!type) {
    // TODO: <pointer> + <integer>
    // TODO: <integer> + <pointer>

    Log::get().error(x->span,
      "unsupported operand types for `+`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::Add>(type, lhs, rhs);
}

auto Build::handle_sub(ptr<ast::Sub> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // Determine the appropriate type
  auto type = _type_reduce_a(lhs->type, rhs->type);
  if (!type) {
    // TODO: <pointer> - <integer>
    // TODO: <integer> - <pointer>
    // TODO: <pointer> - <pointer> (difference)

    Log::get().error(x->span,
      "unsupported operand types for `-`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::Sub>(lhs->type, lhs, rhs);
}

auto Build::handle_mul(ptr<ast::Mul> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // Determine the appropriate type
  auto type = _type_reduce_a(lhs->type, rhs->type);
  if (!type) {
    Log::get().error(x->span,
      "unsupported operand types for `*`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::Mul>(lhs->type, lhs, rhs);
}

auto Build::handle_div(ptr<ast::Div> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // Determine the appropriate type
  auto type = _type_reduce_a(lhs->type, rhs->type);
  if (!type) {
    Log::get().error(x->span,
      "unsupported operand types for `/`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::Div>(lhs->type, lhs, rhs);
}

auto Build::handle_mod(ptr<ast::Mod> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // Determine the appropriate type
  auto type = _type_reduce_a(lhs->type, rhs->type);
  if (!type) {
    Log::get().error(x->span,
      "unsupported operand types for `%`: `{}` and `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  return make<ir::Mod>(lhs->type, lhs, rhs);
}

// Reduce 2 types following simple rules
auto Build::_type_reduce_a(ptr<ir::Type> a, ptr<ir::Type> b) -> ptr<ir::Type> {
  // Integer + Integer OR Real + Real
  if (
    (a->is_real() && b->is_real()) ||
    (a->is_integer() && b->is_integer())
  ) {
    // Handle is_equal
    if (a->is_equal(b)) return a;

    // Handle a (Literal) on either side; the type should go
    // to the other side
    if (a->size() == 0 && b->size() > 0) {
      return b;
    }

    if (b->size() == 0 && a->size() > 0) {
      return a;
    }
  }

  // Real + Literal Integer
  if (
    a->is_real() && b->is_integer() &&
    b->size() == 0
  ) {
    return a;
  }

  // Literal Integer + Real
  if (
    b->is_real() && a->is_integer() &&
    a->size() == 0
  ) {
    return b;
  }

  return nullptr;
}
