// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"
#include "arrow/log.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::handle_assign(ptr<ast::Binary> x) -> ptr<ir::Type> {
  auto lhs = run(x->lhs);
  if (!lhs) return nullptr;

  return lhs;
}

auto TypeDeduce::visit_assign(ptr<ast::Assign> x) -> ptr<ir::Type> {
  return handle_assign(x);
}

auto TypeDeduce::visit_assign_add(ptr<ast::AssignAdd> x) -> ptr<ir::Type> {
  return handle_assign(x);
}

auto TypeDeduce::visit_assign_sub(ptr<ast::AssignSub> x) -> ptr<ir::Type> {
  return handle_assign(x);
}

auto TypeDeduce::visit_assign_mul(ptr<ast::AssignMul> x) -> ptr<ir::Type> {
  return handle_assign(x);
}

auto TypeDeduce::visit_assign_div(ptr<ast::AssignDiv> x) -> ptr<ir::Type> {
  return handle_assign(x);
}

auto TypeDeduce::visit_assign_mod(ptr<ast::AssignMod> x) -> ptr<ir::Type> {
  return handle_assign(x);
}

auto TypeDeduce::visit_assign_bit_or(ptr<ast::AssignBitOr> x) -> ptr<ir::Type> {
  return handle_assign(x);
}

auto TypeDeduce::visit_assign_bit_and(ptr<ast::AssignBitAnd> x) -> ptr<ir::Type> {
  return handle_assign(x);
}

auto TypeDeduce::visit_assign_bit_xor(ptr<ast::AssignBitXor> x) -> ptr<ir::Type> {
  return handle_assign(x);
}
