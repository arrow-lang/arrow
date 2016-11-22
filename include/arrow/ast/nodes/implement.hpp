// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_IMPLEMENT_H
#define ARROW_AST_IMPLEMENT_H

#include <string>

#include "arrow/ptr.hpp"
#include "arrow/ast/nodes/name.hpp"
#include "arrow/ast/nodes/function.hpp"
#include "arrow/ast/nodes/statement.hpp"

namespace arrow {
namespace ast {

struct Implement : Statement {
  Implement(Span span, ptr<Name> target, ptr<Name> interface, std::vector<ptr<ast::TypeParameter>> type_parameters, std::vector<ptr<Function>> functions)
    : Statement(span), target(target), interface(interface), type_parameters(type_parameters), functions(functions) {
  }

  virtual ~Implement() noexcept;

  /// Target
  ptr<Name> target;

  /// Interface
  ptr<Name> interface;

  /// Type Parameters
  std::vector<ptr<TypeParameter>> type_parameters;

  /// Functions
  std::vector<ptr<Function>> functions;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_IMPLEMENT_H
