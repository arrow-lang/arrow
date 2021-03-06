// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_TYPE_H
#define ARROW_AST_TYPE_H

#include <string>

#include "arrow/ast/nodes/node.hpp"

namespace arrow {
namespace ast {

struct Type : Node {
  using Node::Node;

  virtual ~Type() noexcept;
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

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_TYPE_H
