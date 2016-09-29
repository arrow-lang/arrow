// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"
#include "arrow/pass/type_build.hpp"

using arrow::pass::TypeResolve;

void TypeResolve::visit_function(ptr<ast::Function> x) {
  // Get: Function
  auto fn = _ctx.scope->get<ir::Function>(x);
  if (!fn) return;

  // Make: Function Type
  auto type = make<ir::TypeFunction>(x);
  fn->type = type;

  // Resolve: Result type
  if (x->result_type) {
    type->result = TypeBuild(_ctx).run(x->result_type);
    if (!type->result) {
      _incomplete = true;
      return;
    }
  }

  // Resolve: Parameter types
  for (auto& param : x->parameters) {
    auto param_type = TypeBuild(_ctx).run(param->type);
    if (!param_type) {
      _incomplete = true;
      return;
    }

    type->parameters.push_back(param_type);
  }

  // Block
  accept(x->block);
}
