// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"
#include "mach7.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::visit_name(ptr<ast::Name> x) -> ptr<ir::Type> {
  // TODO: Error when not a type-able expression (eg. module)
  return ir::type_of(ir::resolve_name(_ctx, x));
}

auto TypeDeduce::visit_path(ptr<ast::Path> x) -> ptr<ir::Type> {
  // TODO: Error when not a type-able expression (eg. module)
  return ir::type_of(ir::resolve_path(_ctx, x));
}
