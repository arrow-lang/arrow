// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/pass/type_build.hpp"

using arrow::pass::Build;

auto Build::handle_function(ptr<ast::Function> x) -> ptr<ir::Value> {
  // Get: Function
  auto fn = _ctx.scope->get<ir::Function>(x);
  if (!fn) return nullptr;

  // Stack: push
  _ctx.function_s.push(fn.get());

  // Run: Block
  run(x->block);

  // Stack: pop
  _ctx.function_s.pop();

  return fn;
}

auto Build::handle_extern_function(ptr<ast::ExternFunction> x) -> ptr<ir::Value> {
  // Do nothing (it was all done in prior passes)
  return nullptr;
}
