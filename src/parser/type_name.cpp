// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"

using arrow::Parser;

auto Parser::parse_type_name() -> ptr<ast::TypeName> {
  // Expect: identifier
  auto tok = expect<token::Identifier>(token::Type::Identifier);
  if (!tok) return nullptr;

  return std::make_shared<ast::TypeName>(tok->span, tok->text);
}
