// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/pass/type_build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_indirect(ptr<ast::Indirect> x) -> ptr<ir::Value> {
  auto operand = run(x->operand);
  if (!operand) return nullptr;

  ptr<ir::Type> type = nullptr;
  if (isa<ir::TypePointer>(operand->type)) {
    type = cast<ir::TypePointer>(operand->type)->element;
  } else {
    Log::get().error(
      x->span, "indirection requires pointer operand");

    return nullptr;
  }

  return make<ir::Indirect>(x, type, operand);
}

auto Build::handle_address_of(ptr<ast::AddressOf> x) -> ptr<ir::Value> {
  auto operand = run(x->operand);
  if (!operand) return nullptr;

  return make<ir::AddressOf>(x, make<ir::TypePointer>(x, operand->type), operand);
}

auto Build::handle_transmute(ptr<ast::Transmute> x) -> ptr<ir::Value> {
  auto operand = run(x->operand);
  if (!operand) return nullptr;

  auto type = TypeBuild(_ctx).run(x->target);
  if (!type) return nullptr;

  if (!(type->is_pointer() || (
    type->is_integer() && operand->type->is_pointer()
  ))) {
    Log::get().error(x->target->span,
      "destination type must be an integer or pointer");

    return nullptr;
  }

  if (!(operand->type->is_integer() || operand->type->is_pointer())) {
    Log::get().error(x->operand->span,
      "source expression must be of an integer or pointer type");

    return nullptr;
  }

  return make<ir::Transmute>(x, operand, type);
}
