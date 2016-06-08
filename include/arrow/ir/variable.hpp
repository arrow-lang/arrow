// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_VARIABLE_H
#define ARROW_IR_VARIABLE_H

#include <memory>
#include <string>

#include "arrow/ir/item.hpp"
#include "arrow/ptr.hpp"

namespace arrow {
namespace ir {

struct Variable : Item {
  explicit Variable(ptr<ir::Type> type)
    : Item(), type(type) {
  }

  virtual ~Variable() noexcept;

  // Type of the variable.
  // This _can_ be null before type inference has taken place.
  ptr<ir::Type> type;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_VARIABLE_H
