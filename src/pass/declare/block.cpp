// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/declare.hpp"

using arrow::pass::Declare;

auto Declare::handle_block(ptr<ast::Block> x) -> ptr<ir::Block> {
  // Declaring a block just creates it
  auto bl = make<ir::Block>(x, nullptr);

  // Add block to scope for later get
  _ctx.scope.put(x, bl);

  // Scope: Enter
  bl->scope->enter(_ctx);

  // Iterate through each statement ..
  for (auto& statement : x->statements) run(statement);

  // Scope: Exit
  bl->scope->exit(_ctx);

  return bl;
}
