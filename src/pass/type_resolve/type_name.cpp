// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"
#include "arrow/log.hpp"

using arrow::pass::TypeResolve;

auto TypeResolve::handle_type_name(ptr<ast::TypeName> x) -> ptr<ir::Type> {
  auto iter = _types.find(x->name);
  if (iter == _types.end()) {
    // No type found
    Log::get().error(x->span, "use of undeclared type name `{}`", x->name);
    return nullptr;
  }

  return iter->second;
}
