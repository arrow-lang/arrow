// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_block(bool top_level) -> ptr<ast::Block> {
  // Expect `{` (if top-level)
  auto sp = Span(_t._filename);
  if (!top_level) {
    auto tok = expect(token::Type::LeftBrace);
    if (!tok) return nullptr;

    sp = tok->span;
  }

  // Make
  auto result = make<ast::Block>(sp);

  while (
    (!_t.empty()) &&
    (top_level || _t.peek()->type != token::Type::RightBrace) &&
    (_t.peek()->type != token::Type::End)
  ) {
    // Parse a statement
    auto statement = parse_statement();
    if (statement) {
      // Add it to the function
      result->statements.push_back(statement);

      // Extend
      result->span = result->span.extend(statement->span);
    }
  }

  if (!top_level) {
    // Expect `}` (if top-level)
    auto tok = expect(token::Type::RightBrace);
    result->span = result->span.extend(tok->span);
  }

  return result;
}
