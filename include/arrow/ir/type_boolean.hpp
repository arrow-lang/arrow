// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_BOOLEAN_H
#define ARROW_IR_TYPE_BOOLEAN_H

#include <memory>
#include <string>

#include "arrow/ir/type.hpp"

#define ARROW_TTAG_BOOLEAN __COUNTER__

namespace arrow {
namespace ir {

struct TypeBoolean : Type {
  TypeBoolean() : Node(nullptr), Type("bool") {
  }

  virtual ~TypeBoolean() noexcept;

  virtual unsigned tag() const noexcept {
    return ARROW_TTAG_BOOLEAN;
  }

  virtual LLVMTypeRef handle(GContext&) noexcept {
    return LLVMInt1Type();
  }

  virtual unsigned size() const {
    return 1;
  }

  virtual bool is_boolean() const {
    return true;
  }
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_BOOLEAN_H
