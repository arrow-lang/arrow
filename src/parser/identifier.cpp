// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_id() -> ptr<ast::Identifier> {
  // Expect: integer
  auto tok = expect<token::Identifier>(token::Type::Identifier);
  if (!tok) return nullptr;

  return std::make_shared<ast::Identifier>(tok->span, tok->text);
}
