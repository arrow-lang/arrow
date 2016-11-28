// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_TYPE_FUNCTION_H
#define ARROW_AST_TYPE_FUNCTION_H

#include <string>
#include <vector>

#include "arrow/ptr.hpp"
#include "arrow/ast/nodes/type.hpp"

namespace arrow {
namespace ast {

struct TypeFunctionParameter : Node {
  TypeFunctionParameter(Span span, ptr<Type> type, bool is_mutable)
    : Node(span), type(type), is_mutable(is_mutable) {
  }

  /// Type (of parameter)
  ptr<Type> type;

  /// Mutable
  bool is_mutable;
};

struct TypeFunction : Type {
  TypeFunction(Span span, std::vector<ptr<TypeFunctionParameter>> parameters, ptr<Type> result)
    : Type(span), parameters(parameters), result(result) {
  }

  virtual ~TypeFunction() noexcept;

  /// Elements
  std::vector<ptr<TypeFunctionParameter>> parameters;

  /// Result
  ptr<Type> result;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_TYPE_FUNCTION_H
