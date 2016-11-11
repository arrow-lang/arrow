// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_PATH_H
#define ARROW_AST_PATH_H

#include <string>
#include <vector>

#include "arrow/ast/nodes/expression.hpp"
#include "arrow/ast/nodes/name.hpp"

namespace arrow {
namespace ast {

/// A member access operation (commonly referred to as the "dot" operator).
struct Path : Expression {
  Path(Span span, ptr<Expression> operand, ptr<Name> member)
  : Expression(span), operand(operand), member(member) {
  }

  virtual ~Path() noexcept;

  ptr<Expression> operand;

  ptr<Name> member;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_PATH_H
