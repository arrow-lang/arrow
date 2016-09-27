// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/pass/type_build.hpp"

using arrow::pass::Build;

auto Build::handle_function(ptr<ast::Function> x) -> ptr<ir::Value> {
  // Make: Function Type
  auto type = make<ir::TypeFunction>(x);

  // Resolve: Result type
  if (x->result_type) {
    type->result = TypeBuild(_ctx).run(x->result_type);
    if (!type->result) return nullptr;
  }

  // Resolve: Parameter types
  for (auto& param : x->parameters) {
    auto param_type = TypeBuild(_ctx).run(param->type);
    if (!param_type) return nullptr;

    type->parameters.push_back(param_type);
  }

  // Make: Function
  auto item = make<ir::Function>(x, _ctx.modules.back(), x->name, type);

  // Scope: emplace
  _ctx.scope_b.emplace(item->name, item);

  // Stack: push
  _ctx.function_s.push(item.get());

  // Handle: Block
  item->block = handle_block(x->block);

  // Stack: pop
  _ctx.function_s.pop();

  return item;
}

auto Build::handle_extern_function(ptr<ast::ExternFunction> x) -> ptr<ir::Value> {
  // Make: Extern Function Type
  auto type = make<ir::TypeExternFunction>(x, x->is_varidac);

  // Resolve: Result type
  if (x->result_type) {
    type->result = TypeBuild(_ctx).run(x->result_type);
    if (!type->result) return nullptr;
  }

  // Resolve: Parameter types
  for (auto& param : x->parameters) {
    auto param_type = TypeBuild(_ctx).run(param->type);
    if (!param_type) return nullptr;

    type->parameters.push_back(param_type);
  }

  // Make: Extern Function
  auto item = make<ir::ExternFunction>(x, _ctx.modules.back(), x->name, type);

  // Scope: emplace
  _ctx.scope_b.emplace(item->name, item);

  return item;
}
