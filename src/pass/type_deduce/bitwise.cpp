// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"
#include "arrow/log.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::visit_bit_not(ptr<ast::BitNot> x) -> ptr<ir::Type> {
  auto operand = run(x->operand);
  if (!operand) return nullptr;

  if (!(operand->is_integer())) {
    return nullptr;
  }

  return operand;
}

auto TypeDeduce::visit_bit_and(ptr<ast::BitAnd> x) -> ptr<ir::Type> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  auto type = ir::type_reduce(lhs, rhs);
  if (!type || !(type->is_integer() || type->is_boolean())) {
    return nullptr;
  }

  return type;
}

auto TypeDeduce::visit_bit_or(ptr<ast::BitOr> x) -> ptr<ir::Type> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  auto type = ir::type_reduce(lhs, rhs);
  if (!type || !(type->is_integer() || type->is_boolean())) {
    return nullptr;
  }

  return type;
}

auto TypeDeduce::visit_bit_xor(ptr<ast::BitXor> x) -> ptr<ir::Type> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  auto type = ir::type_reduce(lhs, rhs);
  if (!type || !(type->is_integer() || type->is_boolean())) {
    return nullptr;
  }

  return type;
}

auto TypeDeduce::visit_bit_left_shift(ptr<ast::BitLeftShift> x) -> ptr<ir::Type> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // Must be integer
  if (!(lhs->is_integer() && rhs->is_integer())) return nullptr;

  // LHS must be >= in size from RHS
  if (!(lhs->size() == 0 || lhs->size() >= rhs->size())) return nullptr;

  return lhs;
}

auto TypeDeduce::visit_bit_right_shift(ptr<ast::BitRightShift> x) -> ptr<ir::Type> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // Must be integer
  if (!(lhs->is_integer() && rhs->is_integer())) return nullptr;

  // LHS must be >= in size from RHS
  if (!(lhs->size() == 0 || lhs->size() >= rhs->size())) return nullptr;

  return lhs;
}
