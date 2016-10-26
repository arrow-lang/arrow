// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/declare.hpp"

using arrow::pass::Declare;

void Declare::visit_variable(ptr<ast::Variable> x) {
  // Make: Variable
  bool is_global = (_ctx.function_s.size() == 0);
  auto item = make<ir::Variable>(x, x->name, is_global);

  // Scope: put
  _ctx.scope->put(x, item, item->name);

  // Visit initializer (if present)
  if (x->initializer) accept(x->initializer);
}

void Declare::visit_extern_variable(ptr<ast::ExternVariable> x) {
  // Make: ExternVariable
  auto item = make<ir::ExternVariable>(x, x->name);

  // Scope: put
  _ctx.scope->put(x, item, item->name);
}
