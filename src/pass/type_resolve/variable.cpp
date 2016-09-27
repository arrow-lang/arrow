// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"
#include "arrow/pass/type_build.hpp"

using arrow::pass::TypeResolve;

void TypeResolve::handle_variable(ptr<ast::Variable> x) {
  // Get: Variable
  auto var = _ctx.scope->get<ir::Variable>(x);
  if (!var) return;

  // Resolve the type annotation (if present)
  if (x->type) {
    var->type = TypeBuild(_ctx).run(x->type);
    if (!var->type) return;
  }
}
