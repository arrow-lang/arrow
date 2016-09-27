// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/pass/type_build.hpp"

using arrow::pass::Build;
using arrow::pass::TypeBuild;

auto Build::handle_type_alias(ptr<ast::TypeAlias> x) -> ptr<ir::Value> {
  // TODO: Declare!

  // Resolve: target type
  auto target_t = TypeBuild(_ctx).run(x->target);
  if (!target_t) return nullptr;

  // Make: alias
  auto alias = make<ir::TypeAlias>(x, x->name, target_t);

  // TODO(mehcode): Add to module items
  // HACK: Emplace in scope
  _ctx.scope->put(x, alias, x->name);

  // No intrinsic value (nil statement)
  return nullptr;
}
