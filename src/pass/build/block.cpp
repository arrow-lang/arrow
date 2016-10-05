// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"

using arrow::pass::Build;

auto Build::handle_block(ptr<ast::Block> x) -> ptr<ir::Block> {
  ptr<ir::Block> bl = _ctx.scope->get<ir::Block>(x);
  if (!bl) return nullptr;

  // Check if this block is an expression 
  auto is_expression = x->is_expression || (!_expression_c.empty() && _expression_c.top());
  bl->is_expression = is_expression;

  // Scope: Enter
  auto sb = ir::Scope::enter(bl->scope, _ctx);

  // Iterate through each statement ..
  // Push that the statement is being treated like an expression 
  // IF we are also an expression and on the last node
  for (std::size_t i = 0; i < x->statements.size(); ++i) {
    auto &statement = x->statements[i];
    auto ec = _expression_c.enter((i == (x->statements.size() - 1) && is_expression));
    auto node = run(statement);
    ec->exit();
    if (node) {
      bl->statements.push_back(node);

      // The type of a block is the type of the final statement
      bl->type = node->type;
    }
  }

  // Scope: Exit
  sb.exit();

  return bl;
}
