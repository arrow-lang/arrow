// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"

using arrow::pass::Build;

auto Build::handle_expression_statement(ptr<ast::ExpressionStatement> x) -> ptr<ir::Value> {
  // Build the expression
  auto ref = Build(_ctx).run(x->expression);
  if (!ref) return nullptr;

  // Force generation of the expression
  // We normally wait until the last possible minute to generate
  // assembly; this is that minute.
  ref->handle(_ctx);
  return ref;
}
