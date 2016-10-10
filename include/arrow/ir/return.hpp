// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_RETURN_H
#define ARROW_IR_RETURN_H

#include "arrow/ir/value.hpp"
#include "arrow/ir/type.hpp"
#include "arrow/ir/type_unit.hpp"
#include "arrow/ir/type_divergent.hpp"

namespace arrow {
namespace ir {

struct Return : Value {
  Return(ptr<ast::Return> source, ptr<Value> operand)
    : Node(source), Value(make<TypeDivergent>(make<TypeUnit>())), operand(operand) {
  }

  virtual ~Return() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  // Operand that is being returned
  ptr<Value> operand;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_RETURN_H
