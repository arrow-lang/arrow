// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_INTEGER_H
#define ARROW_IR_TYPE_INTEGER_H

#include <memory>
#include <string>
#include <sstream>

#include "arrow/ir/type.hpp"

namespace arrow {
namespace ir {

struct TypeInteger : Type {
  TypeInteger(bool is_signed, unsigned bits)
    : Type(TypeInteger::_name(is_signed, bits)),
      is_signed(is_signed), bits(bits) {
  }

  virtual ~TypeInteger() noexcept;

  // Is this a signed integer type (or not).
  bool is_signed;

  // Number of bits this integer type is constrained to.
  unsigned bits;

 private:
  static std::string _name(bool is_signed, unsigned bits) {
    std::stringstream stream;
    if (!is_signed) stream << "u";
    stream << "int";
    stream << bits;
    return stream.str();
  }
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_INTEGER_H
