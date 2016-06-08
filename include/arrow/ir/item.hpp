// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_ITEM_H
#define ARROW_IR_ITEM_H

#include <memory>
#include <string>

namespace arrow {
namespace ir {

struct Type;

/// An item is a named, possibly exported, construct.
///  - Variable
///  - Function
///  - Module
///  - Type
struct Item {
  Item() {
  }

  virtual ~Item() noexcept;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_ITEM_H
