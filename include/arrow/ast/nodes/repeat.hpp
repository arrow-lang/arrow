// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_REPEAT_H
#define ARROW_AST_REPEAT_H

#include <string>
#include <vector>

#include "arrow/ptr.hpp"
#include "arrow/ast/nodes/expression.hpp"
#include "arrow/ast/nodes/statement.hpp"
#include "arrow/ast/nodes/block.hpp"

namespace arrow {
namespace ast {

struct Repeat : Statement {
  explicit Repeat(Span span, ptr<Expression> condition, ptr<Block> block)
  : Statement(span), condition(condition), block(block) {
  }

  virtual ~Repeat() noexcept;

  ptr<Expression> condition;
  ptr<Block> block;
};

struct Break : Statement {
  explicit Break(Span span)
  : Statement(span) {
  }

  virtual ~Break() noexcept;
};

struct Continue : Statement {
  explicit Continue(Span span)
  : Statement(span) {
  }

  virtual ~Continue() noexcept;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_REPEAT_H
