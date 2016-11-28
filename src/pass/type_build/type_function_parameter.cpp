// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_build.hpp"
#include "arrow/log.hpp"

using arrow::pass::TypeBuild;

auto TypeBuild::handle_type_function_parameter(ptr<ast::TypeFunctionParameter> x) -> ptr<ir::Type> {
  auto type = run(x->type);

  if (type->is_record() || x->is_mutable) {
    type = make<ir::TypeReference>(type->source, type);
  }

  return type;
}
