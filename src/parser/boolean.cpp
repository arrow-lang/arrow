// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_bool() -> std::shared_ptr<ast::Boolean> {
  // Expect: integer
  auto tok = expect({token::Type::True, token::Type::False});
  if (!tok) return nullptr;

  return std::make_shared<ast::Boolean>(
    tok->span, tok->type == token::Type::True);
}
