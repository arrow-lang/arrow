// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_POINTER_H
#define ARROW_AST_POINTER_H

#include <string>

#include "arrow/ptr.hpp"
#include "arrow/ast/nodes/type.hpp"

namespace arrow {
namespace ast {

struct TypePointer : Type {
  TypePointer(Span span, ptr<Type> element)
    : Type(span), element(element) {
  }

  virtual ~TypePointer() noexcept;

  /// Element (pointee)
  ptr<Type> element;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_POINTER_H
