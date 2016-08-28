// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/pass/type_resolve.hpp"

using arrow::pass::Build;

auto Build::handle_variable(ptr<ast::Variable> x) -> ptr<ir::Value> {
  // TODO(mehcode): Type deduction

  // Declare
  auto item = make<ir::Variable>(x, x->name);

  // Resolve the type annotation (if present)
  if (x->type) {
    item->type = TypeResolve(_ctx).run(x->type);
  }

  // Define the initializer expression (if present)
  if (x->initializer) {
    item->initializer = Build(_ctx).run(x->initializer);
  }

  // Emplace to scope
  _ctx.scope.emplace(x->name, item);

  return item;
}
