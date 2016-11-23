// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"

using arrow::pass::TypeResolve;

void TypeResolve::visit_implement(ptr<ast::Implement> x) {
  // Get: Implement
  auto impl = _ctx.scope->get<ir::Implement>(x);
  if (!impl) return;

  // Scope: Enter
  auto sb = ir::Scope::enter(impl->scope, _ctx);

  // Iterate through each function ..
  for (auto& fn : x->functions) accept(fn);

  // Scope: Exit
  sb.exit();
}
