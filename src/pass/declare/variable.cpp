// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/declare.hpp"

using arrow::pass::Declare;

void Declare::handle_variable(ptr<ast::Variable> x) {
  // Make: Variable
  auto item = make<ir::Variable>(
    x, x->name,
    /*is_global=*/!isa<ir::Function>(_ctx.scope->owner),
  );

  // Scope: put
  _ctx.scope.put(x, item, item->name);
}
