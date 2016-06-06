// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_STATEMENT_H
#define ARROW_AST_STATEMENT_H

#include "arrow/ast/nodes/node.hpp"

namespace arrow {
namespace ast {

/// A statement does not have a result; only a side-effect.
/// Most concepts in the language are expressions. However expressions cannot
/// be sequentially combined without side-effect without first wrapping
/// in a statement.
struct Statement : Node {
  virtual ~Statement() noexcept;

  using Node::Node;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_STATEMENT_H
