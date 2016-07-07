// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/middle/declare.hpp"

using arrow::middle::Declare;

auto Declare::handle_module(ptr<ast::Module> x) -> ptr<ir::Module> {
  auto module = make<ir::Module>(x, x->name);

  for (auto& statement : x->statements) {
    auto item = run(statement);
    if (!item) continue;

    module->items.push_back(item);
  }

  return module;
}
