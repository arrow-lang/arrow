// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/middle/declare.hpp"
#include "arrow/middle/type_resolve.hpp"

using arrow::middle::Declare;

auto Declare::handle_variable(ptr<ast::Variable> x) -> ptr<ir::Variable> {
  auto result = make<ir::Variable>(x, x->name);

  // Resolve type now if we have an explicit type annotation
  if (x->type) {
    result->type = TypeResolve(_ctx).run(x->type);
    if (!result->type) return nullptr;
  }

  // Emplace to scope
  _ctx.scope.emplace(x->name, result);

  return result;
}
