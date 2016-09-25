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
    ptr<Block> then, ptr<Block> else_
  )
  : Node(source), Value(type), condition(condition),
    b_then(then), b_else(else_) {
  }

  virtual ~Conditional() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  ptr<Value> condition;
  ptr<Block> b_then;
  ptr<Block> b_else;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_CONDITIONAL_H
