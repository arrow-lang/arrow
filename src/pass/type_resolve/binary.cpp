// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"
#include "arrow/pass/type_deduce.hpp"

using arrow::pass::TypeResolve;

void TypeResolve::visit_binary(ptr<ast::Binary> x) {
  auto type = TypeDeduce(_ctx).run(x);
  if (!type) { _incomplete = true; }

  auto lhs_t = TypeDeduce(_ctx).run(x->lhs);
  auto rhs_t = TypeDeduce(_ctx).run(x->rhs);

  bool push = false;

  if (rhs_t && (_type_s.size() == 0 || rhs_t->size() != 0)) {
    _type_s.push(rhs_t);
    push = true;
  }

  accept(x->lhs);

  if (push) {
    _type_s.pop();
    push = false;
  }

  if (lhs_t && (_type_s.size() == 0 || lhs_t->size() != 0)) {
    _type_s.push(lhs_t);
    push = true;
  }

  accept(x->rhs);

  if (push) {
    _type_s.pop();
    push = false;
  }
}
