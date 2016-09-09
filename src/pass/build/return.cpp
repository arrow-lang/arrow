// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_return(ptr<ast::Return> x) -> ptr<ir::Value> {
  // Build: Operand
  ptr<ir::Value> operand = nullptr;
  if (x->operand) {
    operand = run(x->operand);
    if (!operand) return nullptr;
  }

  // Make: Return
  return make<ir::Return>(x, operand);
}
