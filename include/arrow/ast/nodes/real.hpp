// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_REAL_H
#define ARROW_AST_REAL_H

#include "arrow/ast/nodes/expression.hpp"

namespace arrow {
namespace ast {

struct Real : Expression {
  Real(Span span, long double value)
  : Expression(span), value(value) {
  }

  virtual ~Real() noexcept;

  long double value;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_REAL_H
