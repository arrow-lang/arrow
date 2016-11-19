// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"

using arrow::Parser;

auto Parser::parse_type_tuple() -> ptr<ast::Type> {
  // Expect: `(`
  auto begin_tok = expect(token::Type::LeftParenthesis);
  if (!begin_tok) return nullptr;

  bool is_tuple = false;
  bool is_unit = false;
  std::vector<ptr<ast::Type>> elements;
  if (_t.peek()->type == token::Type::RightParenthesis) {
    // Check for an immediate `)` to signal unit
    is_unit = true;
    elements.push_back(
      make<ast::TypeUnit>(begin_tok->span.extend(_t.peek()->span)));
  } else {
    // Parse elements in sequence
    while (
      (_t.peek()->type != token::Type::RightParenthesis) &&
      (_t.peek()->type != token::Type::End)
    ) {
      // Parse
      auto elem = parse_type();
      if (!elem) return nullptr;
      elements.push_back(elem);

      // Check for a sequence continuation token
      auto tok = _t.peek();
      if (tok->type == token::Type::Comma) {
        is_tuple = true;
        _t.pop();
        continue;
      }

      // Done
      break;
    }
  }

  // Expect: `)`
  auto end_tok = expect(token::Type::RightParenthesis);
  if (!end_tok) return nullptr;

  // Check for `->` which turns this into a functor type
  if (_t.peek()->type == token::Type::LeftArrow) {
    _t.pop();

    // Remove our unit type (if present) and become 0-parameter
    if (elements.size() == 1 && is_unit) {
      elements.clear();
    }

    auto result = parse_type();
    if (!result) return nullptr;

    return make<ast::TypeFunction>(
      begin_tok->span.extend(result->span),
      elements,
      result
    );
  }

  // IIF we have a single type and its not a tuple; we are nothing but the type
  if (elements.size() == 1 && !is_tuple) return elements[0];

  return std::make_shared<ast::TypeTuple>(
    begin_tok->span.extend(end_tok->span), elements);
}
