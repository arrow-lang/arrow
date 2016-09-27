// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"

using arrow::pass::Build;

auto Build::handle_block(ptr<ast::Block> x) -> ptr<ir::Block> {
  ptr<ir::Block> bl = _ctx.scope->get<ir::Block>(x);
  if (!bl) return nullptr;

  // Scope: Enter
  auto sb = ir::Scope::enter(bl->scope, _ctx);

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
  sb.exit();

  return bl;
}
