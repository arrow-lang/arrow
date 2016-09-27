// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/pass/type_build.hpp"

using arrow::pass::Build;

auto Build::handle_function(ptr<ast::Function> x) -> ptr<ir::Value> {
  // // Make: Function Type
  // auto type = make<ir::TypeFunction>(x);
  //
  // // Resolve: Result type
  // if (x->result_type) {
  //   type->result = TypeBuild(_ctx).run(x->result_type);
  //   if (!type->result) return nullptr;
  // }
  //
  // // Resolve: Parameter types
  // for (auto& param : x->parameters) {
  //   auto param_type = TypeBuild(_ctx).run(param->type);
  //   if (!param_type) return nullptr;
  //
  //   type->parameters.push_back(param_type);
  // }

  // Make: Function
  // auto item = make<ir::Function>(x, _ctx.modules.back(), x->name, type);

  // Get: Function
  auto fn = _ctx.scope->get<ir::Function>(x);
  if (!fn) return nullptr;

  // // Scope: emplace
  // _ctx.scope_b.emplace(item->name, item);

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

  // Make: Extern Function Type
  // auto type = make<ir::TypeExternFunction>(x, x->is_varidac);

  // Resolve: Result type
  // if (x->result_type) {
  //   type->result = TypeBuild(_ctx).run(x->result_type);
  //   if (!type->result) return nullptr;
  // }

  // Resolve: Parameter types
  // for (auto& param : x->parameters) {
  //   auto param_type = TypeBuild(_ctx).run(param->type);
  //   if (!param_type) return nullptr;
  //
  //   type->parameters.push_back(param_type);
  // }

  // Make: Extern Function
  // auto item = make<ir::ExternFunction>(x, _ctx.modules.back(), x->name, type);

  // Scope: emplace
  // _ctx.scope_b.emplace(item->name, item);

  // return item;
}
