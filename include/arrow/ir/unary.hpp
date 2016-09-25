// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_UNARY_H
#define ARROW_IR_UNARY_H

#include "arrow/ir/value.hpp"

namespace arrow {
namespace ir {

struct Unary : Value {
  Unary(ptr<Type> type, ptr<Value> operand)
    : Node(nullptr), Value(type), operand(operand) {
  }

  virtual ~Unary() noexcept;

  ptr<Value> operand;

 protected:
  LLVMValueRef _handle = nullptr;
};

#define DEF_UNARY(Name) \
  struct Name : Unary { \
    Name(ptr<ast::Node> source, ptr<Type> type, ptr<Value> operand) \
      : Node(source), Unary(type, operand) { \
    } \
    virtual ~Name() noexcept; \
    virtual LLVMValueRef handle(GContext&) noexcept; \
  };

DEF_UNARY(Negate)
DEF_UNARY(BitNot)
DEF_UNARY(Not)

#undef DEF_UNARY

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_UNARY_H
