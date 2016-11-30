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

using arrow::ir::Generic;
using arrow::ptr;
using arrow::GContext;
using arrow::ir::GenericFunction;
using arrow::ir::GenericTypeRecord;
using arrow::ir::GenericImplement;
namespace ir = arrow::ir;

void Generic::update_cache(std::vector<ptr<ir::Type>>& type_arguments, ptr<Node> node) {
  // Make (cache) name
  std::stringstream stream;
  for (auto& a : type_arguments) {
    stream << a->name;
  }

  auto cache_key = stream.str();
  _cache[cache_key] = node;
}

auto Generic::instantiate(GContext& ctx, std::vector<ptr<ir::Type>>& type_arguments, Span span) -> ptr<Node> {
  // Check type_parameters against type_arguments
  if (type_arguments.size() == 0) {
    // None
    Log::get().error(span, "use of generic `{}` requires type arguments",
      get_base_name());

    return nullptr;
  } else if (type_parameters.size() > type_arguments.size()) {
    // Too few
    Log::get().error(span, "too few type arguments, expected {}, have {}",
      type_parameters.size(), type_arguments.size());

    return nullptr;
  } else if (type_arguments.size() > type_parameters.size()) {
    // Too many
    Log::get().error(span, "too many type arguments, expected {}, have {}",
      type_parameters.size(), type_arguments.size());

    return nullptr;
  }

  // Make (cache) name
  std::stringstream stream;
  for (auto& a : type_arguments) {
    stream << a->name;
  }

  // Check cache
  auto cache_key = stream.str();
  if (_cache.find(cache_key) != _cache.end()) {
    return _cache[cache_key];
  }

  // Instantiate
  _cache[cache_key] = do_instantiate(ctx, type_arguments);
  return _cache[cache_key];
}

auto Generic::instantiate(GContext& ctx, std::vector<ptr<ast::Type>>& type_arguments, Span span) -> ptr<Node> {
  // Realize type arguments
  std::vector<ptr<ir::Type>> type_args;
  for (auto const& type_arg_ast : type_arguments) {
    auto type = pass::TypeBuild(ctx).run(type_arg_ast);
    if (!type) return nullptr;

    type_args.push_back(type);
  }

  return instantiate(ctx, type_args, span);
}

static std::string make_generic_name(std::string name, std::vector<arrow::ptr<arrow::ir::Type>>& type_args) {
  std::stringstream stream;
  stream << name;
  stream << "<";

  for (unsigned i = 0; i < type_args.size(); ++i) {
    if (i > 0) stream << ",";
    stream << type_args[i]->name;
  }

  stream << ">";
  return stream.str();
}

static void declare_type_parameters(
  GContext& ctx,
  ptr<ir::Scope>& scope,
  std::vector<ptr<ir::GenericTypeParameter>> type_parameters,
  std::vector<ptr<ir::Type>> type_arguments
) {
  auto sb = ir::Scope::enter(scope, ctx);

  for (unsigned i = 0; i < type_parameters.size(); ++i) {
    auto const& type_p = type_parameters[i];
    auto const& type_a = type_arguments[i];

    ctx.scope->put(
      type_p->source, type_a, type_p->name);
  }

  sb.exit();
}

auto GenericFunction::do_instantiate(GContext& ctx, std::vector<ptr<ir::Type>>& type_args) -> ptr<Node> {
  // Make a non-generic AST
  auto src = cast<ast::Function>(source);
  auto x = make<ast::Function>(src->span, make_generic_name(name, type_args));
  x->block = src->block;
  x->result_type = src->result_type;
  x->parameters = src->parameters;

  // Declare
  pass::Declare(ctx).run(x);

  // Declare: Type Parameters
  auto i = ctx.scope->get<ir::Function>(x);
  if (!i) return nullptr;
  update_cache(type_args, i);
  declare_type_parameters(ctx, i->block->scope, type_parameters, type_args);

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

auto GenericTypeRecord::do_instantiate(GContext& ctx, std::vector<ptr<ir::Type>>& type_args) -> ptr<Node> {
  // Make a non-generic AST
  auto src = cast<ast::TypeRecord>(source);
  auto x = make<ast::TypeRecord>(src->span, make_generic_name(name, type_args), src->members,
    std::vector<ptr<ast::TypeParameter>>());

  // Declare
  pass::Declare(ctx).run(x);

  // Declare: Type Parameters
  auto i = ctx.scope->get<ir::TypeRecord>(x);
  if (!i) return nullptr;
  update_cache(type_args, i);
  declare_type_parameters(ctx, i->scope, type_parameters, type_args);

  // Resolve
  auto err_cnt = Log::get().count(LOG_ERROR);
  pass::TypeResolve(ctx).run(x);
  if (Log::get().count(LOG_ERROR) != err_cnt) return nullptr;

  // Mark instantiation with base information
  i->base_generic = this;
  i->type_arguments = type_args;

  return i;
}

auto GenericImplement::do_instantiate(GContext& ctx, std::vector<ptr<ir::Type>>& type_args) -> ptr<Node> {
  // Make a non-generic AST
  auto src = cast<ast::Implement>(source);
  auto x = make<ast::Implement>(src->span, src->target, src->interface,
    std::vector<ptr<ast::TypeParameter>>(), src->functions);

  // Add new type-parameter scope
  auto scope = make<ir::Scope>(parent_scope);
  auto sb = ir::Scope::enter(scope, ctx);

  // Declare
  declare_type_parameters(ctx, scope, type_parameters, type_args);
  pass::Declare(ctx).run(x);

  // Declare: Type Parameters
  auto i = ctx.scope->get<ir::Implement>(x);
  if (!i) return nullptr;
  update_cache(type_args, i);

  // Resolve
  auto err_cnt = Log::get().count(LOG_ERROR);
  pass::TypeResolve(ctx).run(x);
  if (Log::get().count(LOG_ERROR) != err_cnt) return nullptr;

  // Build
  err_cnt = Log::get().count(LOG_ERROR);
  pass::Build(ctx).run(x);
  if (Log::get().count(LOG_ERROR) != err_cnt) return nullptr;

  // Leave: Type-parameter scope
  sb.exit();

  return i;
}
