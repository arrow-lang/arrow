// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_VALUE_H
#define ARROW_IR_VALUE_H

#include "arrow/ptr.hpp"
#include "arrow/ir/node.hpp"

namespace arrow {

struct GContext;

namespace ir {

struct Type;

struct Value : Node {
  explicit Value(ptr<Type> type)
  : type(type) {
  }

  virtual ~Value() noexcept;

  // Get LLVM handle
  virtual LLVMValueRef handle(GContext&) noexcept = 0;

  // IR type of this value
  ptr<Type> type;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_VALUE_H
