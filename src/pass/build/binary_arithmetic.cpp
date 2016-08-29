// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"

using arrow::pass::Build;

auto Build::handle_add(ptr<ast::Add> x) -> ptr<ir::Value> {
  auto lhs = Build(_ctx).run(x->lhs);
  auto rhs = Build(_ctx).run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // TODO(mehcode): Determine the appropriate type
  // TODO(mehcode): TypeCheck (ensure that operator exists)

  return make<ir::Add>(lhs->type, lhs, rhs);
}

auto Build::handle_sub(ptr<ast::Sub> x) -> ptr<ir::Value> {
  auto lhs = Build(_ctx).run(x->lhs);
  auto rhs = Build(_ctx).run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // TODO(mehcode): Determine the appropriate type
  // TODO(mehcode): TypeCheck (ensure that operator exists)

  return make<ir::Sub>(lhs->type, lhs, rhs);
}

auto Build::handle_mul(ptr<ast::Mul> x) -> ptr<ir::Value> {
  auto lhs = Build(_ctx).run(x->lhs);
  auto rhs = Build(_ctx).run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // TODO(mehcode): Determine the appropriate type
  // TODO(mehcode): TypeCheck (ensure that operator exists)

  return make<ir::Mul>(lhs->type, lhs, rhs);
}

auto Build::handle_div(ptr<ast::Div> x) -> ptr<ir::Value> {
  auto lhs = Build(_ctx).run(x->lhs);
  auto rhs = Build(_ctx).run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // TODO(mehcode): Determine the appropriate type
  // TODO(mehcode): TypeCheck (ensure that operator exists)

  return make<ir::Div>(lhs->type, lhs, rhs);
}

auto Build::handle_mod(ptr<ast::Mod> x) -> ptr<ir::Value> {
  auto lhs = Build(_ctx).run(x->lhs);
  auto rhs = Build(_ctx).run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // TODO(mehcode): Determine the appropriate type
  // TODO(mehcode): TypeCheck (ensure that operator exists)

  return make<ir::Mod>(lhs->type, lhs, rhs);
}
