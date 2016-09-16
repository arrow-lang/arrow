// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_FUNCTION_H
#define ARROW_AST_FUNCTION_H

#include <string>
#include <vector>

#include "arrow/ptr.hpp"
#include "arrow/ast/nodes/statement.hpp"
#include "arrow/ast/nodes/type.hpp"
#include "arrow/ast/nodes/expression.hpp"

namespace arrow {
namespace ast {

struct Parameter : Node {
  Parameter(
    Span span, std::string name, ptr<Type> type
  )
  : Node(span), name(name), type(type) {
  }

  virtual ~Parameter() noexcept;

  /// Name of the parameter.
  // TODO: Pattern
  std::string name;

  /// Type annotation of the parameter (required).
  ptr<Type> type;
};

struct Function : Statement {
  Function(Span span, std::string name)
  : Statement(span), name(name), result_type(nullptr), parameters() {
  }

  virtual ~Function() noexcept;

  /// Name of the function.
  std::string name;

  /// Result type annotation of the function (required).
  ptr<Type> result_type;

  /// Parameters.
  std::vector<ptr<Parameter>> parameters;

  /// Sequence of statements in the function.
  std::vector<ptr<Statement>> statements;
};

struct ExternFunction : Statement {
  ExternFunction(Span span, std::string name)
  : Statement(span), name(name), result_type(nullptr), parameters(),
    is_varidac(false) {
  }

  virtual ~ExternFunction() noexcept;

  /// Name of the function.
  std::string name;

  /// Result type annotation of the function (required).
  ptr<Type> result_type;

  /// Parameters.
  std::vector<ptr<Parameter>> parameters;

  /// Allows additional, varidac parameters
  bool is_varidac;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_FUNCTION_H
