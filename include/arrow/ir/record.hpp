// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_RECORD_H
#define ARROW_IR_RECORD_H

#include "arrow/ir/value.hpp"
#include "arrow/ir/type_literal_real.hpp"

namespace arrow {
namespace ir {

struct RecordMember : Value {
  // Type of an integer literal is the exact bit-size of the value
  RecordMember(ptr<ast::Node> source, ptr<Type> type, ptr<Value> operand, unsigned index)
  : Node(source), Value(type), operand(operand), index(index) {
  }

  virtual ~RecordMember() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  virtual bool is_addressable() const {
    return true;
  }

  // Operand (record)
  ptr<Value> operand;

  // Member index
  unsigned index;

 private:
  LLVMValueRef _handle = nullptr;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_RECORD_H
