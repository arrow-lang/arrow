// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::visit_not(ptr<ast::Not> x) -> ptr<ir::Type> {
  return make<ir::TypeBoolean>();
}

auto TypeDeduce::visit_and(ptr<ast::And> x) -> ptr<ir::Type> {
  return make<ir::TypeBoolean>();
}

auto TypeDeduce::visit_or(ptr<ast::Or> x) -> ptr<ir::Type> {
  return make<ir::TypeBoolean>();
}
