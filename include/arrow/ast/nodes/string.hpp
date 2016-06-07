// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_STRING_H
#define ARROW_AST_STRING_H

#include <string>

#include "arrow/ast/nodes/expression.hpp"

namespace arrow {
namespace ast {

struct String : Expression {
  String(Span span, std::string value)
  : Expression(span), value(value) {
  }

  virtual ~String() noexcept;

  std::string value;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_STRING_H
