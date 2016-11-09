// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"
#include "arrow/pass/type_deduce.hpp"

using arrow::pass::TypeResolve;

void TypeResolve::visit_unary(ptr<ast::Unary> x) {
  auto type = TypeDeduce(_ctx).run(x);
  if (!type) { _incomplete = true; }

  _type_s.push(type);

  accept(x->operand);

  _type_s.pop();
}

void TypeResolve::visit_address_of(ptr<ast::AddressOf> x) {
  auto type = TypeDeduce(_ctx).run(x);

  if (type && isa<ir::TypePointer>(type)) {
    // Resolve to the pointee
    type = cast<ir::TypePointer>(type)->element;
  }

  // IF in a context already.. reduce
  if (_type_s.size() > 0 && isa<ir::TypePointer>(_type_s.top())) {
    auto tmp = cast<ir::TypePointer>(_type_s.top())->element;
    if (tmp) {
      if (type) {
        tmp = ir::type_reduce(tmp, type);
        if (tmp) type = tmp;
      } else {
        type = tmp;
      }
    }
  }

  if (type) _type_s.push(type);

  accept(x->operand);

  if (type) _type_s.pop();
}

void TypeResolve::visit_indirect(ptr<ast::Indirect> x) {
  auto type = TypeDeduce(_ctx).run(x);
  if (!type) { _incomplete = true; }

  decltype(_type_s) type_s_cp;
  type_s_cp.swap(_type_s);

  accept(x->operand);

  _type_s.swap(type_s_cp);
}
