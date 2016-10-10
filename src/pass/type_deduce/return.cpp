// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::visit_return(ptr<ast::Return>) -> ptr<ir::Type> {
  return make<ir::TypeDivergent>(make<ir::TypeUnit>());
}
