// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"

using arrow::pass::TypeResolve;

void TypeResolve::handle_block(ptr<ast::Block> x) {
  auto bl = _ctx.scope->get<ir::Block>(x);
  if (!bl) return;

  // Scope: Enter
  auto sb = ir::Scope::enter(bl->scope, _ctx);

  // Iterate through each statement ..
  for (auto& statement : x->statements) run(statement);

  // Scope: Exit
  sb.exit();
}
