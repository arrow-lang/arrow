// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_ITEM_H
#define ARROW_IR_ITEM_H

#include <string>

#include "arrow/ir/node.hpp"

namespace arrow {
namespace ir {

struct Type;

/// An item is a named, possibly exported, construct.
///  - Variable
///  - Function
///  - Module
///  - Type
struct Item : virtual Node {
  Item(std::string name)
    : name(name) {
  }

  virtual ~Item() noexcept;

  /// Referencable name of the item
  std::string name;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_ITEM_H
