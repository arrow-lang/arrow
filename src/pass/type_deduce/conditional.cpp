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

  ptr<ir::Type> type = nullptr;
  unsigned divergent_cnt = 0;
  auto handle = [&, this](ptr<ast::Block> &block){
    auto tmp = run(block);
    if (!tmp) return false;

    if (!tmp->is_divergent()) {
      if (type == nullptr) type = tmp;
      else {
        tmp = ir::type_reduce(type, tmp);
        if (tmp) type = tmp;
      }
    } else {
      divergent_cnt += 1;
    }

    return true;
  };

  // Branches
  for (std::size_t i = 0; i < x->branches.size(); ++i) {
    if (!handle(x->branches[i]->block)) return nullptr;
  }

  // Otherwise
  if (!handle(x->otherwise)) return nullptr;

  // Unit
  if (!type) {
    type = make<ir::TypeUnit>();
    if (divergent_cnt >= x->branches.size() + 1) {
      type = make<ir::TypeDivergent>(type);
    }
  }

  return type;
}

auto TypeDeduce::visit_branch(ptr<ast::Branch> x) -> ptr<ir::Type> {
  return run(x->block);
}
