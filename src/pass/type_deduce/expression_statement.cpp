// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::visit_expression_statement(ptr<ast::ExpressionStatement> x) -> ptr<ir::Type> {
  return run(x->expression);
}
