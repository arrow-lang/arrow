// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"
#include "arrow/log.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::visit_identity(ptr<ast::Identity> x) -> ptr<ir::Type> {
  auto operand = run(x->operand);
  if (!operand) return nullptr;

  if (!(operand->is_integer() || operand->is_real())) {
    return nullptr;
  }

  return operand;
}

auto TypeDeduce::visit_negate(ptr<ast::Negate> x) -> ptr<ir::Type> {
  auto operand = run(x->operand);
  if (!operand) return nullptr;

  if (!(operand->is_integer() || operand->is_real())) {
    return nullptr;
  }

  return operand;
}

auto TypeDeduce::visit_add(ptr<ast::Add> x) -> ptr<ir::Type> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // Determine the appropriate type
  auto type = ir::type_reduce(lhs, rhs);
  if (!type || !(type->is_integer() || type->is_real())) {
    // TODO: <pointer> + <integer>
    // TODO: <integer> + <pointer>

    return nullptr;
  }

  return type;
}

auto TypeDeduce::visit_sub(ptr<ast::Sub> x) -> ptr<ir::Type> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // Determine the appropriate type
  auto type = ir::type_reduce(lhs, rhs);
  if (!type || !(type->is_integer() || type->is_real())) {
    // TODO: <pointer> - <integer>
    // TODO: <integer> - <pointer>
    // TODO: <pointer> - <pointer> (difference)

    return nullptr;
  }

  return type;
}

auto TypeDeduce::visit_mul(ptr<ast::Mul> x) -> ptr<ir::Type> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // Determine the appropriate type
  auto type = ir::type_reduce(lhs, rhs);
  if (!type || !(type->is_integer() || type->is_real())) {
    return nullptr;
  }

  return type;
}

auto TypeDeduce::visit_div(ptr<ast::Div> x) -> ptr<ir::Type> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // Determine the appropriate type
  auto type = ir::type_reduce(lhs, rhs);
  if (!type || !(type->is_integer() || type->is_real())) {
    return nullptr;
  }

  return type;
}

auto TypeDeduce::visit_mod(ptr<ast::Mod> x) -> ptr<ir::Type> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // Determine the appropriate type
  auto type = ir::type_reduce(lhs, rhs);
  if (!type || !(type->is_integer() || type->is_real())) {
    return nullptr;
  }

  return type;
}
