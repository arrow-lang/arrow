// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_NODE_H
#define ARROW_AST_NODE_H

#include "arrow/span.hpp"

namespace arrow {
namespace ast {

struct Node {
  explicit Node(Span span) : span(span) {
  }

  virtual ~Node() noexcept;

  /// Location of AST node in the source file.
  Span span;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_NODE_H
