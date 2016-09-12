// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_LITERAL_INTEGER_H
#define ARROW_IR_TYPE_LITERAL_INTEGER_H

#include <memory>
#include <string>
#include <sstream>

#include "arrow/ir/type.hpp"

namespace arrow {
namespace ir {

struct TypeLiteralInteger : Type {
  TypeLiteralInteger() : Type(nullptr, "_") {
  }

  virtual ~TypeLiteralInteger() noexcept;

  virtual LLVMTypeRef handle(GContext&) noexcept {
    return LLVMInt64Type();
  }

  virtual bool is_integer() const { return true; }
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_LITERAL_INTEGER_H
