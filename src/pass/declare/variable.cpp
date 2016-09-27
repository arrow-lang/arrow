// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/declare.hpp"

using arrow::pass::Declare;

void Declare::handle_variable(ptr<ast::Variable> x) {
  // Make: Variable
  bool is_global = (_ctx.function_s.size() == 0);
  auto item = make<ir::Variable>(x, x->name, is_global);

  // Scope: put
  _ctx.scope->put(x, item, item->name);
}
