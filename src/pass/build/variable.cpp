// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/log.hpp"
#include "arrow/pass/build.hpp"
#include "arrow/pass/type_build.hpp"

using arrow::pass::Build;

auto Build::handle_variable(ptr<ast::Variable> x) -> ptr<ir::Value> {
  // TODO(mehcode): Type deduction

  // Are we in scope of a function (aka. do we have a parent_function) ?
  // bool is_global = (_ctx.function_s.size() == 0);

  // Get: Function
  auto var = _ctx.scope->get<ir::Variable>(x);
  if (!var) return nullptr;

  // Declare
  // auto var = make<ir::Variable>(x, x->name, is_global);

  // Resolve the type annotation (if present)
  // if (x->type) {
  //   var->type = TypeBuild(_ctx).run(x->type);
  //   if (!var->type) return nullptr;
  // }

  // Define the initializer expression (if present)
  if (x->initializer) {
    var->initializer = run(x->initializer);
    if (!var->initializer) return nullptr;

    if (var->type) {
      // Assignment must be type equivalent
      if (!ir::type_is_assignable(var->type, var->initializer->type)) {
        Log::get().error(x->span, "mismatched types: expected `{}`, found `{}`",
          var->type->name, var->initializer->type->name);

        return nullptr;
      }
    }
  }

  // Emplace to scope
  // _ctx.scope_b.emplace(x->name, var);

  return var;
}
