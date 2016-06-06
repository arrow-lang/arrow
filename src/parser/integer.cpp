// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_integer() -> std::shared_ptr<ast::Integer> {
  // Expect: integer
  auto tok = _t.pop();
  if (tok->type != token::Type::Integer) {
    Log::get().error(tok->span, "expected integer");
    return nullptr;
  }

  auto integer = std::dynamic_pointer_cast<token::Integer>(tok);

  return std::make_shared<ast::Integer>(tok->span, integer->value);
}
