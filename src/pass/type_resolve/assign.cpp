// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"
#include "arrow/pass/type_deduce.hpp"
#include "mach7.hpp"

using arrow::pass::TypeResolve;

void TypeResolve::visit_assign(ptr<ast::Assign> x) {
  // TODO: Ensure that assignments can't be against anything complicated
  Match(*(x->lhs)) {
    Case(mch::C<ast::Identifier>()) {
      // <identifier> = <..>

      // Get a reference to the _variable_ being assigned
      auto id = cast<ast::Identifier>(x->lhs);
      auto id_text = id->text;
      auto item = _ctx.scope->get<ir::Variable>(id_text);
      if (!item) return;

      // Deduce the type of the assignment
      // NOTE: If deduction fails; we want to record the null
      auto type = TypeDeduce(_ctx).run(x->rhs);
      _assigns[item.get()].push_back(Assign{type});
    } break;

    Otherwise() {
      // Unhandled
    }
  } EndMatch;
}
