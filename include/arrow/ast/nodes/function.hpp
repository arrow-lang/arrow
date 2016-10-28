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
#include "arrow/ast/nodes/block.hpp"

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

struct TypeParameter : Node {
  TypeParameter(
    Span span, std::string name
  )
  : Node(span), name(name) {
  }

  virtual ~TypeParameter() noexcept;

  /// Name of the parameter.
  std::string name;
};

// TODO: Make an abstract base as ExternFunction is only a part of function

struct Function : Statement {
  Function(Span span, std::string name)
  : Statement(span), name(name), result_type(nullptr), parameters(),
    type_parameters(), block(nullptr) {
  }

  virtual ~Function() noexcept;

  /// Name of the function.
  std::string name;

  /// Result type annotation of the function (required).
  ptr<Type> result_type;

  /// Parameters.
  std::vector<ptr<Parameter>> parameters;

  /// Type Parameters.
  std::vector<ptr<TypeParameter>> type_parameters;

  /// Sequence of statements in the function.
  ptr<Block> block;
};

struct ExternFunction : Function {
  ExternFunction(Span span, std::string name, std::string abi)
  : Function(span, name), is_varidac(false), abi(abi) {
  }

  virtual ~ExternFunction() noexcept;

  /// Allows additional, varidac parameters
  bool is_varidac;

  /// Function ABI
  std::string abi;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_FUNCTION_H
