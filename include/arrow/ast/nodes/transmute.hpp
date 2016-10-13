// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_TRANSMUTE_H
#define ARROW_AST_TRANSMUTE_H

#include <string>

#include "arrow/ptr.hpp"
#include "arrow/ast/nodes/expression.hpp"
#include "arrow/ast/nodes/type.hpp"

namespace arrow {
namespace ast {

struct Transmute : Expression {
  Transmute(Span span, ptr<Expression> operand, ptr<Type> target)
    : Expression(span), operand(operand), target(target) {
  }

  virtual ~Transmute() noexcept;

  /// Operand
  ptr<Expression> operand;

  /// Target
  ptr<Type> target;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_TRANSMUTE_H
