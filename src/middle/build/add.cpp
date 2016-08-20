// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/middle/build.hpp"

using arrow::middle::Build;

auto Build::handle_add(ptr<ast::Add> x) -> ptr<ir::Value> {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);
  if (!lhs || !rhs) return nullptr;

  // TODO: Figure out the right type
  return make<ir::Add>(lhs->type, lhs, rhs);
}
