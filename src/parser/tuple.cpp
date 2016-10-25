// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_tuple() -> ptr<ast::Expression> {
  // Expect: `(`
  auto begin_tok = expect(token::Type::LeftParenthesis);
  if (!begin_tok) return nullptr;

  bool is_tuple = false;
  std::vector<ptr<ast::Expression>> elements;
  if (_t.peek()->type == token::Type::RightParenthesis) {
    // Check for an immediate `)` to signal unit
    elements.push_back(
      make<ast::Unit>(begin_tok->span.extend(_t.peek()->span)));
  } else {
    // Parse elements in sequence
    while (
      (_t.peek()->type != token::Type::RightParenthesis) &&
      (_t.peek()->type != token::Type::End)
    ) {
      // Parse
      auto elem = parse_expression();
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

  // IIF we have a single type and its not a tuple; we are nothing but the type
  if (elements.size() == 1 && !is_tuple) return elements[0];

  return std::make_shared<ast::Tuple>(
    begin_tok->span.extend(end_tok->span), elements);
}
