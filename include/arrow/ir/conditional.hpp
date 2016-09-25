// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_CONDITIONAL_H
#define ARROW_IR_CONDITIONAL_H

#include <gmpxx.h>

#include "arrow/ir/value.hpp"
#include "arrow/ir/block.hpp"

namespace arrow {
namespace ir {

struct Conditional : Value {
  Conditional(
    ptr<ast::Node> source, ptr<Type> type, ptr<Value> condition,
    ptr<Value> then, ptr<Value> else_
  )
  : Node(source), Value(type), condition(condition),
    then(then), otherwise(else_) {
  }

  virtual ~Conditional() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  ptr<Value> condition;
  ptr<Value> then;
  ptr<Value> otherwise;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_CONDITIONAL_H
