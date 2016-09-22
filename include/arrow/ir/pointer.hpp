// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_INDIRECT_H
#define ARROW_IR_INDIRECT_H

#include "arrow/ir/value.hpp"

namespace arrow {
namespace ir {

struct Indirect : Value {
  Indirect(ptr<ast::Node> source, ptr<Type> type, ptr<Value> operand)
    : Node(source), Value(type), operand(operand) {
  }

  virtual ~Indirect() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  virtual bool is_addressable() const {
    return true;
  }

  ptr<Value> operand;

 protected:
  LLVMValueRef _handle = nullptr;
};

struct AddressOf : Value {
  AddressOf(ptr<ast::Node> source, ptr<Type> type, ptr<Value> operand)
    : Node(source), Value(type), operand(operand) {
  }

  virtual ~AddressOf() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  ptr<Value> operand;

 protected:
  LLVMValueRef _handle = nullptr;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_INDIRECT_H
