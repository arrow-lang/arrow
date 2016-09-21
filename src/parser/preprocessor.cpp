// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_preprocessor() -> ptr<ast::Statement> {
  // Expect: `#`
  if (_t.peek()->type != token::Type::Octothorpe) {
    expect(token::Type::Octothorpe);
    return nullptr;
  }

  // Expect: identifier
  auto id_tok = _t.peek(1);
  if (id_tok->type != token::Type::Identifier) {
    expect(token::Type::Identifier);
    return nullptr;
  }

  auto id_str = cast<token::Identifier>(id_tok)->text;

  if (id_str == "include") {
    return parse_cinclude();
  }

  Log::get().error(
    id_tok->span, "invalid preprocessing directive: #{}", id_str);

  return nullptr;
}

auto Parser::parse_cinclude() -> ptr<ast::CInclude> {
  // Expect: `#`
  auto tok_begin = expect(token::Type::Octothorpe);
  if (!tok_begin) return nullptr;

  // Expect: identifier
  // TODO(mehcode): Test to ensure its `include`
  if (!expect(token::Type::Identifier)) return nullptr;

  // Expect: string (source)
  auto src = parse_str();
  if (!src) return nullptr;

  return make<ast::CInclude>(tok_begin->span.extend(src->span), src->value);
}
