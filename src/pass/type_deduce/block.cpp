// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::visit_block(ptr<ast::Block> x) -> ptr<ir::Type> {
  ptr<ir::Type> result = nullptr;
  for (auto& stmt : x->statements) {
    result = run(stmt);
  }

  return result;
}
