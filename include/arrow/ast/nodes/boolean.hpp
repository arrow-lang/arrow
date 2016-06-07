// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_BOOL_H
#define ARROW_AST_BOOL_H

#include "arrow/ast/nodes/expression.hpp"

namespace arrow {
namespace ast {

struct Boolean : Expression {
  Boolean(Span span, bool value)
  : Expression(span), value(value) {
  }

  virtual ~Boolean() noexcept;

  bool value;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_BOOL_H
