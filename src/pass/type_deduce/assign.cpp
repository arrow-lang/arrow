// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"
#include "arrow/log.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::visit_assign(ptr<ast::Assign> x) -> ptr<ir::Type> {
  auto lhs = run(x->lhs);
  if (!lhs) return nullptr;

  return lhs;
}
