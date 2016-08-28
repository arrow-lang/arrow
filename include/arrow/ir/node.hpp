// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_NODE_H
#define ARROW_IR_NODE_H

namespace arrow {
namespace ir {

struct Node {
  Node() {
  }

  virtual ~Node() noexcept;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_NODE_H
