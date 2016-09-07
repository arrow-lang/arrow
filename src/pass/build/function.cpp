// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/pass/type_resolve.hpp"

using arrow::pass::Build;

auto Build::handle_function(ptr<ast::Function> x) -> ptr<ir::Value> {
  // Make: Function Type
  auto type = make<ir::TypeFunction>(x);

  // Resolve: Result type
  type->result = TypeResolve(_ctx).run(x->result_type);
  if (!type->result) return nullptr;

  // Resolve: Parameter types
  for (auto& param : x->parameters) {
    auto param_type = TypeResolve(_ctx).run(param->type);
    if (!param_type) return nullptr;

    type->parameters.push_back(param_type);
  }

  // Make: Function
  auto item = make<ir::Function>(x, x->name, type);

  // DEBUG!
  item->handle(_ctx);

  return item;
}