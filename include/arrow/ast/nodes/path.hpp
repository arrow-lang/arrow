// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_PATH_H
#define ARROW_AST_PATH_H

#include <string>
#include <vector>

#include "arrow/ast/nodes/expression.hpp"
#include "arrow/ast/nodes/name.hpp"

namespace arrow {
namespace ast {

struct Path : Expression {
  Path(Span span)
  : Expression(span), segments() {
  }

  virtual ~Path() noexcept;

  // Segments in the path (Names)
  std::vector<ptr<Name>> segments;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_PATH_H
