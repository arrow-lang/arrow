// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_BINARY_H
#define ARROW_AST_BINARY_H

#include "arrow/ptr.hpp"
#include "arrow/ast/nodes/expression.hpp"

namespace arrow {
namespace ast {

struct Binary : Expression {
  Binary(Span span, ptr<Expression> lhs, ptr<Expression> rhs)
  : Expression(span), lhs(lhs), rhs(rhs) {
  }

  virtual ~Binary() noexcept;

  ptr<Expression> lhs;
  ptr<Expression> rhs;
};

#define DEF_BINARY(Name) \
  struct Name : Binary { \
    using Binary::Binary; \
    virtual ~Name() noexcept; \
  };

DEF_BINARY(Add)
DEF_BINARY(Sub)
DEF_BINARY(Mul)
DEF_BINARY(Div)
DEF_BINARY(Mod)

DEF_BINARY(BitOr)
DEF_BINARY(BitXor)
DEF_BINARY(BitAnd)

DEF_BINARY(EqualTo)
DEF_BINARY(NotEqualTo)
DEF_BINARY(GreaterThanOrEqualTo)
DEF_BINARY(GreaterThan)
DEF_BINARY(LessThanOrEqualTo)
DEF_BINARY(LessThan)

DEF_BINARY(And)
DEF_BINARY(Or)

DEF_BINARY(Assign)

DEF_BINARY(AssignAdd)
DEF_BINARY(AssignSub)
DEF_BINARY(AssignMul)
DEF_BINARY(AssignDiv)
DEF_BINARY(AssignMod)
DEF_BINARY(AssignBitOr)
DEF_BINARY(AssignBitXor)
DEF_BINARY(AssignBitAnd)

#undef DEF_BINARY

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_BINARY_H
