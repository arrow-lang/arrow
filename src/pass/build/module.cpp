// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"

using arrow::pass::Build;

auto Build::handle_module(ptr<ast::Module> x) -> ptr<ir::Value> {
  // Get: Module
  auto module = _ctx.scope->get<ir::Module>(x);
  if (!module) return nullptr;

  // Stack: push
  _ctx.module_s.push(module);

  // Block
  run(x->block);

  // Stack: pop
  _ctx.module_s.pop();

  // Has no value
  return nullptr;
}
