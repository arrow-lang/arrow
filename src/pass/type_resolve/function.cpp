// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <string>
#include <sstream>

#include "arrow/pass/type_resolve.hpp"
#include "arrow/pass/type_build.hpp"

using arrow::pass::TypeResolve;
using arrow::pass::TypeBuild;

namespace arrow {
namespace ir {

static ptr<ir::Type> do_result(GContext& ctx, ptr<ast::Function> x) {
  ptr<ir::Type> result = nullptr;
  if (x->result_type) {
    result = TypeBuild(ctx).run(x->result_type);
  } else {
    result = make<ir::TypeUnit>();
  }

  return result;
}

static bool do_parameters(GContext& ctx, ptr<ast::Function> x, std::vector<ptr<Type>> *parameters) {
  // Resolve: Parameter types
  for (std::size_t i = 0; i < x->parameters.size(); ++i) {
    auto param = x->parameters[i];

    auto param_type = TypeBuild(ctx).run(param->type);
    if (!param_type) {
      return false;
    }

    // Push parameter type to function type
    parameters->push_back(param_type);
  }

  return true;
}

}  // namespace ir
}  // namespace arrow

void TypeResolve::visit_function(ptr<ast::Function> x) {
  // Get: Function
  auto fn = _ctx.scope->get<ir::Function>(x);
  if (!fn) return;

  // Scope: Enter
  auto sb = ir::Scope::enter(fn->block->scope, _ctx);

  // Resolve: Result type
  auto result = ir::do_result(_ctx, x);
  if (!result) {
    _incomplete = true;
    return;
  }

  // Resolve: Parameter types
  std::vector<ptr<ir::Type>> parameters;
  if (!ir::do_parameters(_ctx, x, &parameters)) {
    _incomplete = true;
    return;
  }

  // Mark parameter on function item
  for (unsigned i = 0; i < parameters.size(); ++i) {
    if (fn->parameters.size() > i) {
      fn->parameters[i]->type = parameters[i];
    }
  }

  // Make: Function Type
  auto type = make<ir::TypeFunction>(x, parameters, result);
  fn->type = type;

  // Scope: Exit
  sb.exit();

  // Block
  accept(x->block);
}

void TypeResolve::visit_extern_function(ptr<ast::ExternFunction> x) {
  // Get: Function
  auto fn = _ctx.scope->get<ir::ExternFunction>(x);
  if (!fn) return;

  // Resolve: Result type
  auto result = ir::do_result(_ctx, x);
  if (!result) {
    _incomplete = true;
    return;
  }

  // Resolve: Parameter types
  std::vector<ptr<ir::Type>> parameters;
  if (!ir::do_parameters(_ctx, x, &parameters)) {
    _incomplete = true;
    return;
  }

  // Make: Extern Function Type
  auto type = make<ir::TypeExternFunction>(x, x->is_varidac, x->abi, parameters, result);
  fn->type = type;
}
