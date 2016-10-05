// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_UNIT_H
#define ARROW_AST_UNIT_H

#include <string>

#include "arrow/ast/nodes/type.hpp"

namespace arrow {
namespace ast {

struct Unit : Expression {
  Unit(Span span)
    : Expression(span) {
  }

  virtual ~Unit() noexcept;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_UNIT_H
