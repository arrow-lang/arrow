// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_VALUE_H
#define ARROW_IR_VALUE_H

#include "llvm.hpp"
#include "arrow/ptr.hpp"
#include "arrow/ir/node.hpp"
#include "arrow/ir/type.hpp"

namespace arrow {

struct GContext;

namespace ir {

struct Value : virtual Node {
  explicit Value(ptr<Type> type)
  : Node(nullptr), type(type ? (type->is_reference() ? type->get_element() : type) : nullptr) {
  }

  virtual ~Value() noexcept;

  // IR type of this value
  ptr<Type> type;

  // Is Addressable
  virtual bool is_addressable() const {
    return false;
  }

  // Get LLVM handle
  virtual LLVMValueRef handle(GContext&) noexcept = 0;

  // Value Of
  virtual LLVMValueRef value_of(GContext& ctx) noexcept;

  // Address Of
  virtual LLVMValueRef address_of(GContext& ctx) noexcept;

};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_VALUE_H
