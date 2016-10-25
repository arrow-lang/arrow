// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_TYPE_TUPLE_H
#define ARROW_AST_TYPE_TUPLE_H

#include <string>
#include <vector>

#include "arrow/ptr.hpp"
#include "arrow/ast/nodes/type.hpp"

namespace arrow {
namespace ast {

struct TypeTuple : Type {
  TypeTuple(Span span, std::vector<ptr<Type>> elements)
    : Type(span), elements(elements) {
  }

  virtual ~TypeTuple() noexcept;

  /// Elements
  std::vector<ptr<Type>> elements;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_TYPE_TUPLE_H
