// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_INTEGER_H
#define ARROW_IR_INTEGER_H

#include <gmpxx.h>

#include "arrow/ir/value.hpp"
#include "arrow/ir/type_literal_integer.hpp"

namespace arrow {
namespace ir {

struct Integer : Value {
  // Type of an integer literal is the exact bit-size of the value
  explicit Integer(mpz_class value)
  : Value(make<TypeLiteralInteger>()),
    value(value) {
  }

  virtual ~Integer() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  // Integral value
  mpz_class value;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_INTEGER_H
