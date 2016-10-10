// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_UNIT_H
#define ARROW_IR_UNIT_H

#include "arrow/ir/value.hpp"
#include "arrow/ir/type_unit.hpp"

namespace arrow {
namespace ir {

struct Unit : Value {
  explicit Unit()
  : Node(nullptr), Value(make<ir::TypeUnit>()) {
  }

  virtual ~Unit() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept {
  	return LLVMGetUndef(LLVMVoidType());
  }
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_UNIT_H
