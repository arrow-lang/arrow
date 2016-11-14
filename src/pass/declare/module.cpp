// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/declare.hpp"

using arrow::pass::Declare;

void Declare::visit_module(ptr<ast::Module> x) {
  // Get: Module
  auto module = _ctx.scope->get<ir::Module>(x);
  if (!module) {
    // Make: Module
    module = make<ir::Module>(x, x->name);

    // Add module to (top-level) scope
    ir::Scope::top(_ctx.scope)->put(x, module, "");
  }

  // Add module to modules orderable
  _ctx.modules.push_back(module);

  // Stack: push
  _ctx.module_s.push(module);

  // Scope (Top): Enter
  auto sb = ir::Scope::enter(ir::Scope::top(_ctx.scope), _ctx);

  // Block
  accept(x->block);
  module->block = _ctx.scope->get<ir::Block>(x->block);

  // Scope: Exit
  sb.exit();

  // Stack: pop
  _ctx.module_s.pop();
}
