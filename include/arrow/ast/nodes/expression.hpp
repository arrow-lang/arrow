// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_EXPRESSION_H
#define ARROW_AST_EXPRESSION_H

#include "arrow/ast/nodes/node.hpp"

namespace arrow {
namespace ast {

/// An expression has a result.
struct Expression : Node {
  virtual ~Expression() noexcept;

  using Node::Node;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_EXPRESSION_H
