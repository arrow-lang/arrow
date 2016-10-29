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

auto Parser::parse_name() -> ptr<ast::Name> {
  // Parse: identifier
  auto id = parse_id();
  if (!id) return nullptr;

  // Check for `[..]` (type arguments)
  Span end_span = id->span;
  std::vector<ptr<ast::Type>> type_arguments;
  if (_t.peek()->type == token::Type::LeftBracket) {
    _t.pop();

    if (!handle_sequence<ast::Type>(
      &(type_arguments),
      std::bind(&Parser::parse_type, this),
      token::Type::RightBracket
    )) return nullptr;

    // Expect: `]`
    auto end_tok = expect(token::Type::RightBracket);
    if (!end_tok) return nullptr;
    end_span = end_tok->span;
  }

  return std::make_shared<ast::Name>(
    id->span.extend(end_span), id->text, type_arguments);
}
