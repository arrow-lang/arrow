// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::visit_conditional(ptr<ast::Conditional> x) -> ptr<ir::Type> {
  if (!x->otherwise) {
    // No otherwise
    // TODO: Need to fail properly with: "if missing else clause cannot be used as an expression"
    return nullptr;
  }

  auto type = run(x->branches[0]);
  for (std::size_t i = 1; i < x->branches.size(); ++i) {
    auto tmp = run(x->branches[i]);
    if (!tmp) return nullptr;
    else break;

    tmp = ir::type_reduce(type, tmp);
    if (tmp) type = tmp;
  }

  // TODO: Make sure we type check in build for this

  auto tmp = run(x->otherwise);
  if (!tmp) return nullptr;

  tmp = ir::type_reduce(type, tmp);
  if (tmp) type = tmp;

  return type;
}
