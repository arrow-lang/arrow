// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_build.hpp"
#include "arrow/log.hpp"

using arrow::pass::TypeBuild;

// FIXME: type_build/type_function.cpp AND type_resolve/function.cpp are very similar functions
auto TypeBuild::handle_type_function(ptr<ast::TypeFunction> x) -> ptr<ir::TypeFunction> {
  // Build: Result type
  ptr<ir::Type> result = nullptr;
  if (x->result) {
    result = run(x->result);
  } else {
    result = make<ir::TypeUnit>();
  }
  if (!result) return nullptr;

  // Build: Parameter types
  std::vector<ptr<ir::Type>> parameters;
  for (std::size_t i = 0; i < x->parameters.size(); ++i) {
    auto param = x->parameters[i];
    auto param_type = run(param);
    if (!param_type) {
      return nullptr;
    }

    // Push parameter type to function type
    parameters.push_back(param_type);
  }

  return make<ir::TypeFunction>(x, parameters, result);
}
