// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_REAL_H
#define ARROW_IR_REAL_H

#include "arrow/ir/value.hpp"
#include "arrow/ir/type_literal_real.hpp"

namespace arrow {
namespace ir {

struct Real : Value {
  // Type of an integer literal is the exact bit-size of the value
  explicit Real(long double value)
  : Value(make<TypeLiteralReal>()),
    value(value) {
  }

  virtual ~Real() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  // Real value
  long double value;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_REAL_H
