// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"

using arrow::pass::Build;

auto Build::handle_module(ptr<ast::Module> x) -> ptr<ir::Value> {
  // Make: Module
  auto module = make<ir::Module>(x, x->name);

  // Add module to modules orderable
  _ctx.modules.push_back(module);

  // Iterate through each statement ..
  for (auto& statement : x->statements) {
    auto node = run(statement);
    if (node) {
      module->statements.push_back(node);
    }
  }

  // Has no value
  return nullptr;
}
