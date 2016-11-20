// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_TYPE_ALIAS_H
#define ARROW_AST_TYPE_ALIAS_H

#include <string>

#include "arrow/ptr.hpp"
#include "arrow/ast/nodes/type.hpp"
#include "arrow/ast/nodes/statement.hpp"

namespace arrow {
namespace ast {

struct TypeAlias : Statement {
  TypeAlias(Span span, std::string name, ptr<Type> target)
    : Statement(span), name(name), target(target) {
  }

  virtual ~TypeAlias() noexcept;

  /// Name
  std::string name;

  /// Target
  ptr<Type> target;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_TYPE_ALIAS_H
