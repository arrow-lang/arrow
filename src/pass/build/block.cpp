// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"

using arrow::pass::Build;

auto Build::handle_block(ptr<ast::Block> x) -> ptr<ir::Block> {
  // A block should be there for module/functions but it won't for
  // expression blocks
  ptr<ir::Block> bl = _ctx.scope->get(x);
  if (!bl) bl = make<ir::Block>(x, nullptr)

  // Scope: Enter
  bl->scope->enter(_ctx);

  // Iterate through each statement ..
  for (auto& statement : x->statements) {
    auto node = run(statement);
    if (node) {
      bl->statements.push_back(node);

      // The type of a block is the type of the final statement
      bl->type = node->type;
    }
  }

  // Scope: Exit
  bl->scope->exit(_ctx);

  return bl;
}
