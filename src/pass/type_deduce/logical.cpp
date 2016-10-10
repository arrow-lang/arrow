// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::visit_not(ptr<ast::Not> x) -> ptr<ir::Type> {
  return make<ir::TypeBoolean>();
}

auto TypeDeduce::handle_combinator(ptr<ast::Binary> x) -> ptr<ir::Type> {
  auto lhs_t = run(x->lhs);
  auto rhs_t = run(x->rhs);
  if (!lhs_t || !rhs_t) return nullptr;

  ptr<ir::Type> type = make<ir::TypeBoolean>();
  if (lhs_t->is_divergent() || rhs_t->is_divergent()) {
  	type = make<ir::TypeDivergent>(type);
  }

  return type;
}

auto TypeDeduce::visit_and(ptr<ast::And> x) -> ptr<ir::Type> {
  return handle_combinator(x);
}

auto TypeDeduce::visit_or(ptr<ast::Or> x) -> ptr<ir::Type> {
  return handle_combinator(x);
}
