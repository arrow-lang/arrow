// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_TYPENAME_H
#define ARROW_AST_TYPENAME_H

#include <string>

#include "arrow/ast/nodes/type.hpp"
#include "arrow/ast/nodes/identifier.hpp"
#include "arrow/ptr.hpp"

namespace arrow {
namespace ast {

struct TypeName : Type {
  TypeName(Span span, ptr<ast::Name> name)
    : Type(span), name(name) {
  }

  virtual ~TypeName() noexcept;

  /// Name of the type.
  ptr<ast::Name> name;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_TYPENAME_H
