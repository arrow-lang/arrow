// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_TYPEPATH_H
#define ARROW_AST_TYPEPATH_H

#include <string>

#include "arrow/ast/nodes/type.hpp"
#include "arrow/ast/nodes/identifier.hpp"
#include "arrow/ast/nodes/path.hpp"
#include "arrow/ptr.hpp"

namespace arrow {
namespace ast {

struct TypePath : Type {
  TypePath(Span span)
  : Type(span), segments() {
  }

  virtual ~TypePath() noexcept;

  // Segments in the path (Names)
  std::vector<ptr<Name>> segments;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_TYPEPATH_H
