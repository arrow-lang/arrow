// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_INTEGER_H
#define ARROW_IR_TYPE_INTEGER_H

#include <memory>
#include <string>

#include "arrow/ir/type.hpp"

namespace arrow {
namespace ir {

struct TypeInteger : Type {
  TypeInteger(bool is_signed, unsigned bits)
    : Type(), is_signed(is_signed), bits(bits) {
  }

  virtual ~TypeInteger() noexcept;

  // Is this a signed integer type (or not).
  bool is_signed;

  // Number of bits this integer type is constrained to.
  unsigned bits;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_INTEGER_H
