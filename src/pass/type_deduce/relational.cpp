// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::visit_eq(ptr<ast::EqualTo> x) -> ptr<ir::Type> {
  return make<ir::TypeBoolean>();
}

auto TypeDeduce::visit_ne(ptr<ast::NotEqualTo> x) -> ptr<ir::Type> {
  return make<ir::TypeBoolean>();
}

auto TypeDeduce::visit_lt(ptr<ast::LessThan> x) -> ptr<ir::Type> {
  return make<ir::TypeBoolean>();
}

auto TypeDeduce::visit_le(ptr<ast::LessThanOrEqualTo> x) -> ptr<ir::Type> {
  return make<ir::TypeBoolean>();
}

auto TypeDeduce::visit_gt(ptr<ast::GreaterThan> x) -> ptr<ir::Type> {
  return make<ir::TypeBoolean>();
}

auto TypeDeduce::visit_ge(ptr<ast::GreaterThanOrEqualTo> x) -> ptr<ir::Type> {
  return make<ir::TypeBoolean>();
}
