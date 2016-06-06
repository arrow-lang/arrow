// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_INTEGER_H
#define ARROW_AST_INTEGER_H

#include <gmpxx.h>

#include "arrow/ast/nodes/expression.hpp"

namespace arrow {
namespace ast {

struct Integer : Expression {
  Integer(Span span, mpz_class value)
  : Expression(span), value(value) {
  }

  virtual ~Integer() noexcept;

  /// Value of the integer expression.
  mpz_class value;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_INTEGER_H
