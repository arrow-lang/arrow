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
    : Node(nullptr), Type(TypeInteger::_name(is_signed, bits)),
      _is_signed(is_signed), _bits(bits) {
  }

  virtual ~TypeInteger() noexcept;

  virtual LLVMTypeRef handle(GContext&) noexcept {
    return LLVMIntType(_bits);
  }

  virtual bool is_equal(ptr<Type> other) const {
    auto other_i = cast<TypeInteger>(other);
    if (!other_i) return false;

    return other_i->_is_signed == _is_signed && other_i->_bits == _bits;
  }

  virtual bool is_integer() const { return true; }
  virtual unsigned size() const { return _bits; }
  virtual bool is_signed() const { return _is_signed; }

  // Is this a signed integer type (or not).
  bool _is_signed;

  // Number of bits this integer type is constrained to.
  unsigned _bits;

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
