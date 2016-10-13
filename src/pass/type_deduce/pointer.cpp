// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"
#include "arrow/pass/type_build.hpp"
#include "arrow/log.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::visit_indirect(ptr<ast::Indirect> x) -> ptr<ir::Type> {
  auto operand = run(x->operand);
  if (!operand) return nullptr;

  ptr<ir::Type> type = nullptr;
  if (isa<ir::TypePointer>(operand)) {
    type = cast<ir::TypePointer>(operand)->element;
  }

  return type;
}

auto TypeDeduce::visit_address_of(ptr<ast::AddressOf> x) -> ptr<ir::Type> {
  auto operand = run(x->operand);
  if (!operand) return nullptr;

  return make<ir::TypePointer>(x, operand);
}

auto TypeDeduce::visit_transmute(ptr<ast::Transmute> x) -> ptr<ir::Type> {
  auto target = TypeBuild(_ctx).run(x->target);
  if (!target) return nullptr;

  return target;
}
