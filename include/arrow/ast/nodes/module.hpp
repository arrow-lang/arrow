// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_MODULE_H
#define ARROW_AST_MODULE_H

#include <string>
#include <vector>

#include "arrow/ptr.hpp"
#include "arrow/ast/nodes/statement.hpp"

namespace arrow {
namespace ast {

struct Module : Statement {
  Module(Span span, std::string name)
  : Statement(span), name(name), statements() {
  }

  virtual ~Module() noexcept;

  /// Name of the module.
  /// This is inferred from the filename in case of an automatic module, but
  /// is speicifed directly for an explicitly declared module.
  std::string name;

  /// Sequence of statements in the module.
  /// A module is made up of 0..n statements.
  std::vector<ptr<Statement>> statements;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_MODULE_H
