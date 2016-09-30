// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/declare.hpp"

using arrow::pass::Declare;

void Declare::visit_type_alias(ptr<ast::TypeAlias> x) {
  // Make: TypeAlias
  auto alias = make<ir::TypeAlias>(x, x->name, nullptr);

  // Scope: put
  _ctx.scope->put(x, alias, alias->name);
}
