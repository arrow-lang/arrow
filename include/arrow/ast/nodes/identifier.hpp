// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_IDENTIFIER_H
#define ARROW_AST_IDENTIFIER_H

#include <string>

#include "arrow/ast/nodes/expression.hpp"

namespace arrow {
namespace ast {

struct Identifier : Expression {
  Identifier(Span span, std::string text)
  : Expression(span), text(text) {
  }

  virtual ~Identifier() noexcept;

  std::string text;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_IDENTIFIER_H
