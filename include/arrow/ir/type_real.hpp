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
    : Type(nullptr, TypeReal::_name(bits)),
      bits(bits) {
  }

  virtual ~TypeReal() noexcept;

  virtual LLVMTypeRef handle(GContext&) noexcept {
    if (bits == 32) return LLVMFloatType();
    else if (bits == 64) return LLVMDoubleType();

    throw std::runtime_error("real types may only be 32 or 64 bits");
  }

  // Number of bits this real type is constrained to.
  unsigned bits;

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
