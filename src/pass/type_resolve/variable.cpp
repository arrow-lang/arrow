// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"
#include "arrow/pass/type_deduce.hpp"
#include "arrow/pass/type_build.hpp"

using arrow::pass::TypeResolve;

void TypeResolve::visit_variable(ptr<ast::Variable> x) {
  // Get: Variable
  auto var = _ctx.scope->get<ir::Variable>(x);
  if (!var) return;

  // Resolve the type annotation (if present)
  if (x->type) {
    var->type = TypeBuild(_ctx).run(x->type);
    if (!var->type) return;
  } else {
    // TypeResolve: Record the declaration (and re-initialize the storage)
    _declare.insert(var);
    _assigns[var.get()] = {};
    _uses[var.get()] = {};

    // Check for an initializer expression (and record as an assignment)
    if (x->initializer) {
      // NOTE: If deduction fails; we want to record the null
      auto type = TypeDeduce(_ctx).run(x->initializer);
      _assigns[var.get()].push_back(Assign{type});
    }
  }
}
