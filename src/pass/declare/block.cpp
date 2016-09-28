// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/declare.hpp"

using arrow::pass::Declare;

void Declare::visit_block(ptr<ast::Block> x) {
  // Declaring a block just creates it
  auto bl = make<ir::Block>(x, _ctx.scope);

  // Add block to scope for later get
  _ctx.scope->put(x, bl, "");

  // Scope: Enter
  auto sb = ir::Scope::enter(bl->scope, _ctx);

  // Iterate through each statement ..
  for (auto& statement : x->statements) run(statement);

  // Scope: Exit
  sb.exit();
}
