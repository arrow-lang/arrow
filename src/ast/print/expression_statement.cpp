// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_expression_statement(
  ptr<ExpressionStatement> n
) {
  print(n->expression);
}
