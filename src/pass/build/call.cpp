// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/pass/type_build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;
using arrow::pass::TypeBuild;

auto Build::handle_call(ptr<ast::Call> x) -> ptr<ir::Value> {
  // Build: Operand
  auto error_cnt = Log::get().count(LOG_ERROR);
  auto operand = run(x->operand);
  if (!operand && (error_cnt == Log::get().count(LOG_ERROR))) {
    // Is this a type?
    auto operand_t = TypeBuild(_ctx).run(x->operand);
    if (!operand_t) return nullptr;

    // Yes; assert we have a single argument
    if (x->arguments.size() != 1) {
      // TODO(mehcode): pluralize
      Log::get().error(
        x->span, "expected 1 parameter, found {} parameter(s)",
        x->arguments.size());

      return nullptr;
    }

    auto value = run(x->arguments[0]->value);
    if (!value) return nullptr;

    return make<ir::Transmute>(x, value, operand_t);
  } else if (!operand) {
    return nullptr;
  }

  // Assert: Operand is indeed a function
  if (!operand->type->is_function()) {
    Log::get().error(
      x->span, "expected function, found `{}`", operand->type->name);

    return nullptr;
  }

  // Get result type (of call)
  ptr<ir::Type> result_type = nullptr;
  std::vector<ptr<ir::Type>>* parameter_types;
  bool is_varidac = false;
  if (isa<ir::TypeExternFunction>(operand->type)) {
    auto fn_t = cast<ir::TypeExternFunction>(operand->type);

    result_type = fn_t->result;
    parameter_types = &(fn_t->parameters);
    is_varidac = fn_t->is_varidac;
  } else if (isa<ir::TypeFunction>(operand->type)) {
    result_type = cast<ir::TypeFunction>(operand->type)->result;
    parameter_types = &(cast<ir::TypeFunction>(operand->type)->parameters);
  } else {
    return nullptr;
  }

  // Make: Call
  auto item = make<ir::Call>(x, operand, result_type);
  auto operand_fn = cast<ir::IFunction>(operand);

  // Build: Arguments
  unsigned param_index = isa<ir::Method>(operand_fn) ? 1 : 0;
  unsigned param_sz = parameter_types->size() + (isa<ir::Method>(operand_fn) ? -1 : 0);
  for (auto& argument : x->arguments) {
    auto arg = run(argument);
    if (!arg) return nullptr;

    if (param_index < parameter_types->size()) {
      // Assignment must be type equivalent
      auto param_t = parameter_types->at(param_index++);
      if (!ir::type_is_assignable(param_t, arg->type)) {
        Log::get().error(argument->span,
          "mismatched types: expected `{}`, found `{}`",
          param_t->name, arg->type->name);

        // TODO: Perhaps attempt to check all parameters before dying
        return nullptr;
      }
    } else if (!is_varidac) {
      // Error: too many parameters
      Log::get().error(x->span,
        "too many arguments to function call, expected {}, have {}",
        param_sz, x->arguments.size());

      return nullptr;
    }

    item->arguments.push_back(arg);
  }

  if (param_index < parameter_types->size()) {
    // Error: too few parameters
    Log::get().error(x->span,
      "too few arguments to function call, expected {}, have {}",
      param_sz, x->arguments.size());

    return nullptr;
  }

  return item;
}

auto Build::handle_argument(ptr<ast::Argument> x) -> ptr<ir::Value> {
  return run(x->value);
}
