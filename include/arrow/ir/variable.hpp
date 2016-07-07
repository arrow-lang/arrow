// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_VARIABLE_H
#define ARROW_IR_VARIABLE_H

#include <string>

#include "arrow/ir/item.hpp"
#include "arrow/ir/value.hpp"

namespace arrow {
namespace ir {

struct Variable : Item {
  Variable(ptr<ast::Variable> source, std::string name)
    : Item(source, name), type(nullptr), initializer(nullptr) {
  }

  virtual ~Variable() noexcept;

  // Type of the variable.
  // This _can_ be null before type inference has taken place.
  ptr<ir::Type> type;

  // Initializer
  ptr<ir::Value> initializer;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_VARIABLE_H
