// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_BLOCK_H
#define ARROW_AST_BLOCK_H

#include <string>
#include <vector>

#include "arrow/ptr.hpp"
#include "arrow/ast/nodes/statement.hpp"
#include "arrow/ast/nodes/expression.hpp"

namespace arrow {
namespace ast {

struct Block : Expression {
  explicit Block(Span span, bool is_expression)
  : Expression(span), statements(), is_expression(is_expression) {
  }

  virtual ~Block() noexcept;

  /// Sequence of statements in the block.
  std::vector<ptr<Statement>> statements;

  /// Statement OR Expression
  bool is_expression;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_BLOCK_H
