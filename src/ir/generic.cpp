// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/log.hpp"
#include "arrow/generator.hpp"
#include "arrow/pass/build.hpp"
#include "arrow/pass/declare.hpp"
#include "arrow/pass/type_resolve.hpp"
#include "arrow/pass/type_build.hpp"

using arrow::ir::GenericFunction;

auto GenericFunction::instantiate(GContext& ctx, std::vector<ptr<ast::Type>>& type_arguments) -> ptr<Value> {
  // Realize type arguments
  std::vector<ptr<ir::Type>> type_args;
  for (auto const& type_arg_ast : type_arguments) {
    auto type = pass::TypeBuild(ctx).run(type_arg_ast);
    if (!type) return nullptr;

    type_args.push_back(type);
  }

  // Build a concrete name for this generic function
  std::stringstream stream;
  stream << "!";
  stream << name;

  for (auto& a : type_args) {
    stream << "!";
    stream << a->name;
  }

  // Make a non-generic function AST
  // TODO: Only make one if we have to
  auto src = cast<ast::Function>(source);
  auto x = make<ast::Function>(src->span, stream.str());
  x->block = src->block;
  x->result_type = src->result_type;
  x->parameters = src->parameters;

  // Declare
  pass::Declare(ctx).run(x);

  auto fn = ctx.scope->get<ir::Function>(x);
  if (!fn) return nullptr;
  auto sb = ir::Scope::enter(fn->block->scope, ctx);

  for (unsigned i = 0; i < type_parameters.size(); ++i) {
    auto const& type_p = type_parameters[i];
    auto const& type_a = type_args[i];

    ctx.scope->put(
      type_p->source, type_a, type_p->name);
  }

  sb.exit();

  // Resolve
  auto err_cnt = Log::get().count(LOG_ERROR);
  pass::TypeResolve(ctx).run(x);
  if (Log::get().count(LOG_ERROR) != err_cnt) return nullptr;

  // Build
  err_cnt = Log::get().count(LOG_ERROR);
  auto result = pass::Build(ctx).run(x);
  if (Log::get().count(LOG_ERROR) != err_cnt) return nullptr;

  return result;
}
