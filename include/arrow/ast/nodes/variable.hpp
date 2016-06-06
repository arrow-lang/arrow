// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_VARIABLE_H
#define ARROW_AST_VARIABLE_H

#include <string>

#include "arrow/ast/nodes/statement.hpp"

namespace arrow {
namespace ast {

/// Variable declaration.
struct Variable : Statement {
  virtual ~Variable() noexcept;

  Variable(Span span, std::string name) :
    Statement(span), name(name) {
  }

  /// Name of the variable.
  std::string name;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_VARIABLE_H
