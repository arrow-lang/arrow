// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"
#include "arrow/pass/type_deduce.hpp"

using arrow::pass::TypeResolve;

void TypeResolve::visit_binary(ptr<ast::Binary> x) {
  auto type = TypeDeduce(_ctx).run(x);
  if (!type) { _incomplete = true; return; }

  _type_s.push(type);

  accept(x->lhs);
  accept(x->rhs);

  _type_s.pop();
}
