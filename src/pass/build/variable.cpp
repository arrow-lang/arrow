// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/log.hpp"
#include "arrow/pass/build.hpp"
#include "arrow/pass/type_build.hpp"

using arrow::pass::Build;

auto Build::handle_variable(ptr<ast::Variable> x) -> ptr<ir::Value> {
  // Get: Function
  auto var = _ctx.scope->get<ir::Variable>(x);
  if (!var) return nullptr;

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

  return var;
}
