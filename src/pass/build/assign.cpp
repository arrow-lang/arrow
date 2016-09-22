// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_assign(ptr<ast::Assign> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // Assignment must be type equivalent
  if (!ir::type_is_assignable(lhs->type, rhs->type)) {
    Log::get().error(x->span, "mismatched types: expected `{}`, found `{}`",
      lhs->type->name, rhs->type->name);

    return nullptr;
  }

  // The type of the assignment is always the type of the LHS
  return make<ir::Assign>(x, lhs->type, lhs, rhs);
}
