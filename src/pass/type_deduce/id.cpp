// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"
#include "mach7.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::visit_id(ptr<ast::Identifier> x) -> ptr<ir::Type> {
  auto item = _ctx.scope->get(x->text);
  if (!item) return nullptr;

  Match(*item) {
    Case(mch::C<ir::Variable>()) {
      return cast<ir::Variable>(item)->type;
    }

    Case(mch::C<ir::Function>()) {
      return cast<ir::Function>(item)->type;
    }

    Case(mch::C<ir::ExternFunction>()) {
      return cast<ir::ExternFunction>(item)->type;
    }
  } EndMatch

  return nullptr;
}
