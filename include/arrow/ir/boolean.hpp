// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_BOOLEAN_H
#define ARROW_IR_BOOLEAN_H

#include "arrow/ir/value.hpp"
#include "arrow/ir/type_boolean.hpp"

namespace arrow {
namespace ir {

struct Boolean : Value {
  explicit Boolean(bool value) : Value(make<TypeBoolean>()), value(value) {
  }

  virtual ~Boolean() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  bool value;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_BOOLEAN_H
