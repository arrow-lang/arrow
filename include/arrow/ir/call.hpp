// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_CALL_H
#define ARROW_IR_CALL_H

#include "arrow/ir/value.hpp"
#include "arrow/ir/type.hpp"

namespace arrow {
namespace ir {

struct Call : Value {
  Call(ptr<ast::Call> source, ptr<Value> operand, ptr<Type> result_type)
    : Value(result_type), operand(operand), arguments() {
  }

  virtual ~Call() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  // Operand that is being invoked
  ptr<Value> operand;

  // Arguments to the call
  std::vector<ptr<Value>> arguments;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_CALL_H
