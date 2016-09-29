// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"
#include "mach7.hpp"

using arrow::pass::TypeResolve;

void TypeResolve::visit_id(ptr<ast::Identifier> x) {
  auto id_text = x->text;
  auto item = _ctx.scope->get(id_text);
  if (!item) return;

  Match(*item) {
    Case(mch::C<ir::Variable>()) {
      // Add a `use`
      if (_type_s.size() > 0) {
        _uses[cast<ir::Variable>(item).get()].push_back(Use{_type_s.top()});
      }
    } break;

    Otherwise() {
      // Unhandled
    }
  } EndMatch;
}
