// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_EXPRESSION_H
#define ARROW_AST_EXPRESSION_H

#include "arrow/ast/nodes/node.hpp"

namespace arrow {
namespace ast {

/// An expression statement is a statement that consists of a single
/// expression. This serves as a bridge to allow more than 1 expression
/// in a construct that accepts statements.
struct ExpressionStatement : Statement {
  ExpressionStatement(std::shared_ptr<Expression> expression)
    : expression(expression) {
  }

  virtual ~Statement() noexcept;

  std::shared_ptr<Expression> expression;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_EXPRESSION_H
