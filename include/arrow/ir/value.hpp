// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_VALUE_H
#define ARROW_IR_VALUE_H

#include "arrow/ptr.hpp"

namespace arrow {
namespace ir {

struct Type;

struct Value {
  explicit Value(ptr<Type> type) : type(type) {
  }

  virtual ~Value() noexcept;

  ptr<Type> type;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_VALUE_H
