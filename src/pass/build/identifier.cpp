// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_id(ptr<ast::Identifier> x) -> ptr<ir::Value> {
  // Does this identifier exist
  if (!_ctx.scope.contains(x->text)) {
    Log::get().error(x->span, "unresolved name `{}`", x->text);
    return nullptr;
  }

  // Get the item in reference
  auto item = _ctx.scope.get(x->text);

  // Return
  return cast<ir::Value>(item);
}
