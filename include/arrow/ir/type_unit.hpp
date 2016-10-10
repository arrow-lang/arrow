// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_UNIT_H
#define ARROW_IR_TYPE_UNIT_H

#include <memory>
#include <string>

#include "arrow/ir/type.hpp"

#define ARROW_TTAG_UNIT __COUNTER__

namespace arrow {
namespace ir {

struct TypeUnit : Type {
  TypeUnit()
  : Node(nullptr), Type("()") {
  }

  virtual ~TypeUnit() noexcept;

  virtual unsigned tag() const noexcept {
    return ARROW_TTAG_UNIT;
  }

  virtual LLVMTypeRef handle(GContext&) noexcept {
    return LLVMVoidType();
  }

  virtual bool is_unit() const {
  	return true;
  }
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_UNIT_H
