// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_IMPORT_H
#define ARROW_AST_IMPORT_H

#include <string>

#include "arrow/ast/nodes/statement.hpp"

namespace arrow {
namespace ast {

struct Import : Statement {
  Import(Span span, std::string source, std::string alias)
  : Statement(span), source(source), alias(alias) {
  }

  virtual ~Import() noexcept;

  /// Source
  std::string source;

  /// Alias: `as ...` (optional)
  std::string alias;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_IMPORT_H
