// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_build.hpp"
#include "arrow/log.hpp"

using arrow::pass::TypeBuild;

auto TypeBuild::handle_type_pointer(ptr<ast::TypePointer> x) -> ptr<ir::TypePointer> {
  auto element_t = run(x->element);
  if (!element_t) return nullptr;

  return make<ir::TypePointer>(x, element_t);
}
