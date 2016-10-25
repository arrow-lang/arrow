// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_TUPLE_H
#define ARROW_AST_TUPLE_H

#include <string>
#include <vector>

#include "arrow/ptr.hpp"
#include "arrow/ast/nodes/expression.hpp"

namespace arrow {
namespace ast {

struct Tuple : Expression {
  Tuple(Span span, std::vector<ptr<Expression>> elements)
    : Expression(span), elements(elements) {
  }

  virtual ~Tuple() noexcept;

  /// Elements
  std::vector<ptr<Expression>> elements;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_TUPLE_H
