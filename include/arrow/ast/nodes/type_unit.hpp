// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_TYPE_UNIT_H
#define ARROW_AST_TYPE_UNIT_H

#include <string>

#include "arrow/ast/nodes/type.hpp"

namespace arrow {
namespace ast {

struct TypeUnit : Type {
  TypeUnit(Span span)
    : Type(span) {
  }

  virtual ~TypeUnit() noexcept;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_TYPE_UNIT_H
