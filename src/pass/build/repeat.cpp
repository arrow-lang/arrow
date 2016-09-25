// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_repeat(ptr<ast::Repeat> x) -> ptr<ir::Value> {
  // Build: condition
  auto cond = run(x->condition);
  if (!cond) return nullptr;

  // Assert: typeof(condition) == bool
  if (!cond->type->is_boolean()) {
    Log::get().error(x->span, "mismatched types: expected `bool`, found `{}`",
      cond->type->name);

    return nullptr;
  }

  // Build: block (of statements)
  auto bl = run(x->block);
  if (!bl) return nullptr;

  return make<ir::Repeat>(x, cond, cast<ir::Block>(bl));
}
