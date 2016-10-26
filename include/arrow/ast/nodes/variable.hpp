// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_VARIABLE_H
#define ARROW_AST_VARIABLE_H

#include <string>

#include "arrow/ptr.hpp"
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
    ptr<Type> type,
    ptr<Expression> initializer,
    bool is_mutable
  )
  : Statement(span), name(name), type(type), initializer(initializer),
    is_mutable(is_mutable) {
  }

  /// Name of the variable.
  std::string name;

  /// Type annotation of the variable (optional).
  ptr<Type> type;

  /// Initializer expression for the variable (optional).
  ptr<Expression> initializer;

  /// Mutable
  bool is_mutable;
};

/// External Variable declaration.
struct ExternVariable : Statement {
  virtual ~ExternVariable() noexcept;

  ExternVariable(
    Span span,
    std::string name,
    ptr<Type> type,
    bool is_mutable
  )
  : Statement(span), name(name), type(type),
    is_mutable(is_mutable) {
  }

  /// Name of the variable.
  std::string name;

  /// Type annotation of the variable (optional).
  ptr<Type> type;

  /// Mutable
  bool is_mutable;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_VARIABLE_H
