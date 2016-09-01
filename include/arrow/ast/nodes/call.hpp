// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_CALL_H
#define ARROW_AST_CALL_H

#include <string>
#include <vector>

#include "arrow/ptr.hpp"
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
  : Expression(span), operand(operand), arguments() {
  }

  virtual ~Call() noexcept;

  /// Operand expression to be invoked.
  ptr<Expression> operand;

  /// Arguments.
  std::vector<ptr<Argument>> arguments;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_CALL_H
