// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_deduce.hpp"

using arrow::pass::TypeDeduce;

auto TypeDeduce::visit_call(ptr<ast::Call> x) -> ptr<ir::Type> {
  auto const& operand_t = run(x->operand);
  if (operand_t->is_function()) {
    // Function Call
    if (isa<ir::TypeFunction>(operand_t)) {
      return cast<ir::TypeFunction>(operand_t)->result;
    } else if (isa<ir::TypeExternFunction>(operand_t)) {
      return cast<ir::TypeExternFunction>(operand_t)->result;
    }
  } else {
    // Type Conversion
    return operand_t;
  }

  return nullptr;
}
