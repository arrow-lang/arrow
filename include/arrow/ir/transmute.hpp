// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TRANSMUTE_H
#define ARROW_IR_TRANSMUTE_H

#include <gmpxx.h>

#include "arrow/ir/value.hpp"
#include "arrow/ir/type_integer.hpp"

namespace arrow {
namespace ir {

struct Transmute : Value {
  explicit Transmute(ptr<ast::Node> source, ptr<Value> value, ptr<Type> type)
  : Node(source), Value(type), value(value), _handle(nullptr) {
  }

  virtual ~Transmute() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  ptr<Value> value;

 private:
  LLVMValueRef _handle;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TRANSMUTE_H
