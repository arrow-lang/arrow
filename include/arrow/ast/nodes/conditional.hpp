// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_CONDITIONAL_H
#define ARROW_AST_CONDITIONAL_H

#include <string>
#include <vector>

#include "arrow/ptr.hpp"
#include "arrow/ast/nodes/expression.hpp"
#include "arrow/ast/nodes/block.hpp"

namespace arrow {
namespace ast {

struct Branch : Node {
  Branch(Span span, ptr<Expression> condition, ptr<Block> block)
  : Node(span), condition(condition), block(block) {
  }

  virtual ~Branch() noexcept;

  ptr<Expression> condition;
  ptr<Block> block;
};

struct Conditional : Expression {
  Conditional(Span span, std::vector<ptr<Branch>> brs, ptr<Block> otherwise)
  : Expression(span), branches(brs), otherwise(otherwise) {
  }

  virtual ~Conditional() noexcept;

  // Conditional branches
  std::vector<ptr<Branch>> branches;

  // Otherwise (optional)
  ptr<Block> otherwise;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_CONDITIONAL_H
