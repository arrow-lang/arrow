// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"
#include "mach7.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::visit_id(ptr<ast::Identifier> x) -> ptr<ir::Type> {
  auto item = _ctx.scope->get(x->text);
  if (!item) return nullptr;

  // Check if we have a type directly
  auto type_item = cast<ir::Type>(item);
  if (type_item) {
    return type_item;
  }

  // Pull a type out from something
  Match(*item) {
    Case(mch::C<ir::Variable>()) {
      return cast<ir::Variable>(item)->type;
    }

    Case(mch::C<ir::Parameter>()) {
      return cast<ir::Parameter>(item)->type;
    }

    Case(mch::C<ir::TypeAlias>()) {
      return cast<ir::TypeAlias>(item);
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
