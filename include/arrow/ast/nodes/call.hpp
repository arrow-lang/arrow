// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_CALL_H
#define ARROW_AST_CALL_H

#include <string>

#include "arrow/ast/nodes/expression.hpp"

namespace arrow {
namespace ast {

struct Argument : Node {
  Argument(Span span, ptr<Expression> value)
  : Node(span), value(value) {
  }

  virtual ~Argument() noexcept;

  /// Value of the argument.
  ptr<Expression> value;

};

struct NamedArgument : Argument {
  NamedArgument(Span span, ptr<Expression> value, std::string name)
  : Argument(span, value), name(name) {
  }

  virtual ~NamedArgument() noexcept;

  /// Name of the argument.
  std::string name;
};

struct Call : Expression {
  Call(Span span, ptr<Expression> operand)
  : Expression(span), operand(operand), p_arguments(), n_arguments() {
  }

  virtual ~Call() noexcept;

  /// Operand expression to be invoked.
  ptr<Expression> operand;

  /// Positional arguments.
  std::vector<ptr<Argument>> p_arguments;

  /// Named arguments.
  std::vector<ptr<NamedArgument>> n_arguments;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_CALL_H
