// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"

using arrow::pass::Build;

auto Build::handle_assign(ptr<ast::Assign> x) -> ptr<ir::Value> {
  auto lhs = Build(_ctx).run(x->lhs);
  auto rhs = Build(_ctx).run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // The type of the assignment is always the type of the LHS
  return make<ir::Assign>(lhs->type, lhs, rhs);
}
