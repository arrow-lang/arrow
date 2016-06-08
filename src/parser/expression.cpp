// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_expression() -> std::shared_ptr<ast::Expression> {
  switch (_t.peek()->type) {
  case token::Type::Integer:
    return parse_integer();

  case token::Type::True:
  case token::Type::False:
    return parse_bool();

  case token::Type::Float:
    return parse_float();

  case token::Type::String:
    return parse_str();

  default:
    Log::get().error(_t.pop()->span, "expected expression");
    return nullptr;
  }
}
