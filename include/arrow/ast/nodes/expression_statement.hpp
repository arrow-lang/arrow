// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_EXPRESSION_STATEMENT_H
#define ARROW_AST_EXPRESSION_STATEMENT_H

#include <memory>

#include "arrow/ast/nodes/statement.hpp"
#include "arrow/ast/nodes/expression.hpp"

namespace arrow {
namespace ast {

/// An expression statement is a statement that consists of a single
/// expression. This serves as a bridge to allow more than 1 expression
/// in a construct that accepts statements.
struct ExpressionStatement : Statement {
  explicit ExpressionStatement(ptr<Expression> expression)
    : Statement(expression->span), expression(expression) {
  }

  virtual ~ExpressionStatement() noexcept;

  ptr<Expression> expression;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_EXPRESSION_STATEMENT_H
