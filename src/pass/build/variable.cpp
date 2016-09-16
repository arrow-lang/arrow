// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/log.hpp"
#include "arrow/pass/build.hpp"
#include "arrow/pass/type_resolve.hpp"

using arrow::pass::Build;

auto Build::handle_variable(ptr<ast::Variable> x) -> ptr<ir::Value> {
  // TODO(mehcode): Type deduction

  // Are we in scope of a function (aka. do we have a parent_function) ?
  bool is_global = (_ctx.function_s.size() == 0);

  // Declare
  auto item = make<ir::Variable>(x, x->name, is_global);

  // Resolve the type annotation (if present)
  if (x->type) {
    item->type = TypeResolve(_ctx).run(x->type);
    if (!item->type) return nullptr;
  }

  // Define the initializer expression (if present)
  if (x->initializer) {
    item->initializer = run(x->initializer);
    if (!item->initializer) return nullptr;

    if (item->type) {
      // Assignment must be type equivalent
      if (!ir::type_is_assignable(item->type, item->initializer->type)) {
        Log::get().error(x->span, "mismatched types: expected `{}`, found `{}`",
          item->type->name, item->initializer->type->name);

        return nullptr;
      }
    }
  }

  // Emplace to scope
  _ctx.scope_b.emplace(x->name, item);

  return item;
}
