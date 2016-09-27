// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"

using arrow::pass::Build;

auto Build::handle_module(ptr<ast::Module> x) -> ptr<ir::Value> {
  // Get: Module
  auto module = _ctx.scope.get(x);
  if (!module) return nullptr;

  // Block
  module->block = run(x->block);

  // Has no value
  return nullptr;
}
