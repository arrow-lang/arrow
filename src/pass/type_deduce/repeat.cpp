// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::visit_break(ptr<ast::Break> x) -> ptr<ir::Type> {
  return make<ir::TypeDivergent>(make<ir::TypeUnit>());
}

auto TypeDeduce::visit_continue(ptr<ast::Continue> x) -> ptr<ir::Type> {
  return make<ir::TypeDivergent>(make<ir::TypeUnit>());
}
