// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_FLOAT_H
#define ARROW_AST_FLOAT_H

#include "arrow/ast/nodes/expression.hpp"

namespace arrow {
namespace ast {

struct Float : Expression {
  Float(Span span, long double value)
  : Expression(span), value(value) {
  }

  virtual ~Float() noexcept;

  long double value;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_FLOAT_H
