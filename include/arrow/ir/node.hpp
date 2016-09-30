// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_NODE_H
#define ARROW_IR_NODE_H

#include "llvm.hpp"
#include "arrow/ptr.hpp"
#include "arrow/ast.hpp"

namespace arrow {

struct GContext;

namespace ir {

struct Node {
  Node(ptr<ast::Node> source) : source(source) {
  }

  virtual ~Node() noexcept;

  /// Source (in file) of the item
  ptr<ast::Node> source;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_NODE_H
