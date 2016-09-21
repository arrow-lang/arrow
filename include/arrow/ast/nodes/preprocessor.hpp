// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_PREPROCESSOR_H
#define ARROW_AST_PREPROCESSOR_H

#include <string>

#include "arrow/ast/nodes/statement.hpp"

namespace arrow {
namespace ast {

struct CInclude : Statement {
  CInclude(Span span, std::string source)
  : Statement(span), source(source) {
  }

  virtual ~CInclude() noexcept;

  /// Source
  std::string source;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_PREPROCESSOR_H
