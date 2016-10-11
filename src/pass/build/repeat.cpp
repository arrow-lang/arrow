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
  // Push a NIL loop frame (for error checking)
  _ctx.loop_s.push({nullptr, nullptr});
  auto bl = run(x->block);
  _ctx.loop_s.pop();
  if (!bl) {
    return nullptr;
  }

  return make<ir::Repeat>(x, cond, cast<ir::Block>(bl));
}

auto Build::handle_break(ptr<ast::Break> x) -> ptr<ir::Value> {
  if (_ctx.loop_s.empty()) {
    Log::get().error(x->span, "unexpected `break` outside loop");

    return nullptr;
  }

  return make<ir::Break>(x);
}

auto Build::handle_continue(ptr<ast::Continue> x) -> ptr<ir::Value> {
  if (_ctx.loop_s.empty()) {
    Log::get().error(x->span, "unexpected `continue` outside loop");

    return nullptr;
  }

  return make<ir::Continue>(x);
}
