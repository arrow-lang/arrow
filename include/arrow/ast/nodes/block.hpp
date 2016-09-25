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
  explicit Block(Span span)
  : Expression(span), statements() {
  }

  virtual ~Block() noexcept;

  /// Sequence of statements in the block.
  std::vector<ptr<Statement>> statements;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_BLOCK_H
