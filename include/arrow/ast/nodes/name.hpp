// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_AST_NAME_H
#define ARROW_AST_NAME_H

#include <string>
#include <vector>

#include "arrow/ast/nodes/expression.hpp"
#include "arrow/ast/nodes/identifier.hpp"
#include "arrow/ast/nodes/type.hpp"
#include "arrow/ptr.hpp"

namespace arrow {
namespace ast {

struct Name : Identifier {
  Name(Span span, std::string text, std::vector<ptr<ast::Type>> type_arguments)
  : Identifier(span, text), type_arguments(type_arguments) {
  }

  virtual ~Name() noexcept;

  std::vector<ptr<Type>> type_arguments;
};

}  // namespace ast
}  // namespace arrow

#endif  // ARROW_AST_NAME_H
