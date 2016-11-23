// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/pass/type_build.hpp"

using arrow::pass::Build;

auto Build::handle_implement(ptr<ast::Implement> x) -> ptr<ir::Value> {
  // Get: Implement
  auto impl = _ctx.scope->get<ir::Implement>(x);
  if (!impl) return nullptr;

  // Scope: Enter
  auto sb = ir::Scope::enter(impl->scope, _ctx);

  // Iterate through each function ..
  for (auto& fn : x->functions) run(fn);

  // Scope: Exit
  sb.exit();

  return nullptr;
}
