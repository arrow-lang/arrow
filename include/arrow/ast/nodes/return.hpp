// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_RETURN_H
#define ARROW_AST_RETURN_H

#include "arrow/ptr.hpp"
#include "arrow/ast/nodes/expression.hpp"

namespace arrow {
namespace ast {

struct Return : Expression {
  Return(Span span, ptr<Expression> operand)
  : Expression(span), operand(operand) {
  }

  virtual ~Return() noexcept;

  ptr<Expression> operand;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_RETURN_H
