// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_id(ptr<ast::Identifier> x) -> ptr<ir::Value> {
  // Does this identifier exist
  if (!_ctx.scope->contains(x->text)) {
    Log::get().error(x->span, "unresolved name `{}`", x->text);
    return nullptr;
  }

  // Get the item in reference
  auto item = _ctx.scope->get(x->text);

  // Return
  return cast<ir::Value>(item);
}

auto Build::handle_name(ptr<ast::Name> x) -> ptr<ir::Value> {
  // Does this identifier exist
  if (!_ctx.scope->contains(x->text)) {
    Log::get().error(x->span, "unresolved name `{}`", x->text);
    return nullptr;
  }

  // Get the item in reference
  auto item = _ctx.scope->get(x->text);

  // IF we have a generic item
  auto gitem = cast<ir::Generic>(item);
  if (gitem) {
    // Instantiate and return the concrete item
    item = gitem->instantiate(_ctx, x->type_arguments);
  }

  // if (item->is_generic()) {
  //   auto generic = cast<ir::Generic>(item);
  //   auto& type_parameters = generic->type_parameters;
  //   auto& type_arguments = x->type_arguments;
  //
  // }
  //
  // fmt::print("{}: [type_arguments: {}]\n", x->text, x->type_arguments.size());

  // Return
  return cast<ir::Value>(item);
}
