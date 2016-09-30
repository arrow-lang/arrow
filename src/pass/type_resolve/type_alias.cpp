// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"
#include "arrow/pass/type_build.hpp"

using arrow::pass::TypeResolve;

void TypeResolve::visit_type_alias(ptr<ast::TypeAlias> x) {
  // Get: TypeAlias
  auto alias = _ctx.scope->get<ir::TypeAlias>(x);
  if (!alias) return;

  // Resolve: target type
  alias->target = TypeBuild(_ctx).run(x->target);
  if (!alias->target) {
    _incomplete = true;
    return;
  }
}
