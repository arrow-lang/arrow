// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_VARIABLE_H
#define ARROW_AST_VARIABLE_H

#include <string>

#include "arrow/ast/nodes/statement.hpp"
#include "arrow/ast/nodes/type.hpp"
#include "arrow/ast/nodes/expression.hpp"

namespace arrow {
namespace ast {

/// Variable declaration.
struct Variable : Statement {
  virtual ~Variable() noexcept;

  Variable(
    Span span,
    std::string name,
    std::shared_ptr<Type> type,
    std::shared_ptr<Expression> initializer
  )
  : Statement(span), name(name), type(type), initializer(initializer) {
  }

  /// Name of the variable.
  std::string name;

  /// Type annotation of the variable (optional).
  std::shared_ptr<Type> type;

  /// Initializer expression for the variable (optional).
  std::shared_ptr<Expression> initializer;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_VARIABLE_H
