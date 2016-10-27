// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_BINARY_H
#define ARROW_IR_BINARY_H

#include "arrow/ir/value.hpp"

namespace arrow {
namespace ir {

struct Binary : Value {
  Binary(ptr<Type> type, ptr<Value> lhs, ptr<Value> rhs)
    : Node(nullptr), Value(type), lhs(lhs), rhs(rhs) {
  }

  virtual ~Binary() noexcept;

  ptr<Value> lhs;
  ptr<Value> rhs;

 protected:
  LLVMValueRef _handle = nullptr;
};

#define DEF_BINARY(Name) \
  struct Name : Binary { \
    Name(ptr<ast::Node> source, ptr<Type> type, ptr<Value> lhs, ptr<Value> rhs) \
      : Node(source), Binary(type, lhs, rhs) { \
    } \
    virtual ~Name() noexcept; \
    virtual LLVMValueRef handle(GContext&) noexcept; \
  };

DEF_BINARY(Add)
DEF_BINARY(Sub)
DEF_BINARY(Mul)
DEF_BINARY(Div)
DEF_BINARY(Mod)

DEF_BINARY(BitAnd)
DEF_BINARY(BitOr)
DEF_BINARY(BitXor)
DEF_BINARY(BitLeftShift)
DEF_BINARY(BitRightShift)

DEF_BINARY(And)
DEF_BINARY(Or)

DEF_BINARY(EqualTo)
DEF_BINARY(NotEqualTo)
DEF_BINARY(LessThan)
DEF_BINARY(LessThanOrEqualTo)
DEF_BINARY(GreaterThan)
DEF_BINARY(GreaterThanOrEqualTo)

DEF_BINARY(Assign)

DEF_BINARY(AssignAdd)
DEF_BINARY(AssignSub)
DEF_BINARY(AssignMul)
DEF_BINARY(AssignDiv)
DEF_BINARY(AssignMod)

DEF_BINARY(AssignBitAnd)
DEF_BINARY(AssignBitOr)
DEF_BINARY(AssignBitXor)

#undef DEF_BINARY

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_BINARY_H
