// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"

using arrow::Parser;

auto Parser::parse_type_pointer() -> ptr<ast::TypePointer> {
  // Expect: `*`
  auto begin_tok = expect(token::Type::Asterisk);
  if (!begin_tok) return nullptr;

  // Expect: type
  auto type = parse_type();
  if (!type) return nullptr;

  return std::make_shared<ast::TypePointer>(
    begin_tok->span.extend(type->span), type);
}
