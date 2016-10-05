// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"
#include "arrow/pass/type_deduce.hpp"

using arrow::pass::TypeResolve;

void TypeResolve::visit_call(ptr<ast::Call> x) {
  accept(x->operand);

  // Deduce the functional type in reference
  auto operand_t = TypeDeduce(_ctx).run(x->operand);
  if (!operand_t) { _incomplete = true; return; }

  if (operand_t->is_function()) {
    // Function
    std::vector<ptr<ir::Type>>* parameter_types;
    if (isa<ir::TypeFunction>(operand_t)) {
      auto fn_t = cast<ir::TypeFunction>(operand_t);

      parameter_types = &(fn_t->parameters);
    } else if (isa<ir::TypeExternFunction>(operand_t)) {
      auto fn_t = cast<ir::TypeExternFunction>(operand_t);

      parameter_types = &(fn_t->parameters);
    } else {
      return;
    }

    // Iterate through arguments (pushing the parameter type)
    unsigned param_index = 0;
    for (auto& arg : x->arguments) {
      if (param_index < parameter_types->size()) {
        auto param_t = parameter_types->at(param_index++);

        _type_s.push(param_t);
        accept(arg);
        _type_s.pop();
      }
    }
  } else {
    // Type Conversion
    _type_s.push(operand_t);
    accept(x->arguments[0]);
    _type_s.pop();
  }
}
