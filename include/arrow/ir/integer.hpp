// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_INTEGER_H
#define ARROW_IR_INTEGER_H

#include <gmpxx.h>

#include "arrow/ir/value.hpp"

namespace arrow {
namespace ir {

struct Integer : Value {
  explicit Integer(mpz_class value) : Value(nullptr), value(value) {
  }

  virtual ~Integer() noexcept;

  mpz_class value;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_INTEGER_H
