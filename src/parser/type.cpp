// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_type() -> ptr<ast::Type> {
  switch (_t.peek()->type) {
  case token::Type::Identifier:
    return parse_type_name();

  case token::Type::Asterisk:
    return parse_type_pointer();

  case token::Type::LeftParenthesis: {
    auto begin_tok = _t.pop();
    auto end_tok = expect(token::Type::RightParenthesis);
    if (!end_tok) return nullptr;

    return make<ast::TypeUnit>(begin_tok->span.extend(end_tok->span));
  }

  default:
    Log::get().error(_t.pop()->span, "expected type");
    return nullptr;
  }
}
