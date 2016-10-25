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

struct TypeFunction : Type {
  TypeFunction(Span span, std::vector<ptr<Type>> parameters, ptr<Type> result)
    : Type(span), parameters(parameters), result(result) {
  }

  virtual ~TypeFunction() noexcept;

  /// Elements
  std::vector<ptr<Type>> parameters;

  /// Result
  ptr<Type> result;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_TYPE_FUNCTION_H
