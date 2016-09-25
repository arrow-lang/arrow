// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_REPEAT_H
#define ARROW_IR_REPEAT_H

#include <gmpxx.h>

#include "arrow/ir/value.hpp"
#include "arrow/ir/block.hpp"

namespace arrow {
namespace ir {

struct Repeat : Value {
  Repeat(ptr<ast::Node> source, ptr<Value> condition, ptr<Block> body)
  : Node(source), Value(nullptr), condition(condition), body(body) {
  }

  virtual ~Repeat() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  ptr<Value> condition;
  ptr<Block> body;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_REPEAT_H
