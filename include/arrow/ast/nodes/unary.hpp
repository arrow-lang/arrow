// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_UNARY_H
#define ARROW_AST_UNARY_H

#include "arrow/ptr.hpp"
#include "arrow/ast/nodes/expression.hpp"

namespace arrow {
namespace ast {

struct Unary : Expression {
  Unary(Span span, ptr<Expression> operand)
  : Expression(span), operand(operand) {
  }

  virtual ~Unary() noexcept;

  ptr<Expression> operand;
};

#define DEF_UNARY(Name) \
  struct Name : Unary { \
    using Unary::Unary; \
    virtual ~Name() noexcept; \
  };

DEF_UNARY(Identity);
DEF_UNARY(Negate);

DEF_UNARY(BitNot);

DEF_UNARY(Not);

#undef DEF_UNARY

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_UNARY_H
