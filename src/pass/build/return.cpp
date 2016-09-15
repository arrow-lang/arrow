// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_return(ptr<ast::Return> x) -> ptr<ir::Value> {
  // Test: Inside function
  if (_ctx.function_s.size() == 0) {
    Log::get().error(x->span, "unexpected `return` outside function");

    return nullptr;
  }

  // Build: Operand
  ptr<ir::Value> operand = nullptr;
  if (x->operand) {
    operand = run(x->operand);
    if (!operand) return nullptr;
  }

  // Test: Type equality
  auto res_t = cast<ir::TypeFunction>(_ctx.function_s.top()->type)->result;
  if (res_t && operand && !_type_is_assignable(res_t, operand->type)) {
    Log::get().error(x->span, "mismatched types: expected `{}`, found `{}`",
      res_t->name, operand->type->name);

    return nullptr;
  } else if (!res_t && operand) {
    Log::get().error(x->span, "mismatched types: expected nothing, found `{}`",
      operand->type->name);

    return nullptr;
  } else if (res_t && !operand) {
    Log::get().error(x->span, "mismatched types: expected `{}`, found nothing",
      res_t->name);

    return nullptr;
  }

  // Make: Return
  return make<ir::Return>(x, operand);
}
