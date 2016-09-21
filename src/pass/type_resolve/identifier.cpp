// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"
#include "arrow/log.hpp"

using arrow::pass::TypeResolve;

auto TypeResolve::handle_id(ptr<ast::Identifier> x) -> ptr<ir::Type> {
  // Does this identifier exist
  if (!_ctx.scope_b.contains(x->text)) {
    Log::get().error(x->span, "unresolved name `{}`", x->text);
    return nullptr;
  }

  // Get the item in reference
  auto item = _ctx.scope_b.get(x->text);

  auto item_t = cast<ir::Type>(item);
  if (item_t == nullptr) {
    Log::get().error(x->span, "`{}` is not a type", x->text);

    return nullptr;
  }

  return item_t;
}
