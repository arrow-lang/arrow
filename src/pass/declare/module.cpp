// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/declare.hpp"

using arrow::pass::Declare;

void Declare::visit_module(ptr<ast::Module> x) {
  // Make: Module
  auto module = make<ir::Module>(x, x->name);

  // Add module to modules orderable
  _ctx.modules.push_back(module);

  // Add module to (top-level) scope
  _ctx.scope->put(x, module, "");

  // Block
  accept(x->block);
  module->block = _ctx.scope->get<ir::Block>(x->block);
}
