// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_REAL_H
#define ARROW_IR_TYPE_REAL_H

#include <memory>
#include <string>
#include <sstream>

#include "arrow/ir/type.hpp"

namespace arrow {
namespace ir {

struct TypeReal : Type {
  TypeReal(unsigned bits)
    : Node(nullptr), Type(TypeReal::_name(bits)),
      _bits(bits) {
  }

  virtual ~TypeReal() noexcept;

  virtual LLVMTypeRef handle(GContext&) noexcept {
    if (_bits == 32) return LLVMFloatType();
    else if (_bits == 64) return LLVMDoubleType();

    throw std::runtime_error("real types may only be 32 or 64 bits");
  }

  virtual bool is_equal(ptr<Type> other) const {
    auto other_r = cast<TypeReal>(other);
    if (!other_r) return false;

    return other_r->_bits == _bits;
  }

  virtual bool is_real() const { return true; }
  virtual unsigned size() const { return _bits; }

  // Number of bits this real type is constrained to.
  unsigned _bits;

 private:
  static std::string _name(unsigned bits) {
    std::stringstream stream;
    stream << "float";
    stream << bits;

    return stream.str();
  }
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_REAL_H
