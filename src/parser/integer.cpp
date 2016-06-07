// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_integer() -> std::shared_ptr<ast::Integer> {
  // Expect: integer
  auto tok = expect<token::Integer>(token::Type::Integer);
  if (!tok) return nullptr;

  return std::make_shared<ast::Integer>(tok->span, tok->value);
}
