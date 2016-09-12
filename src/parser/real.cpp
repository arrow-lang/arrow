// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_real() -> ptr<ast::Real> {
  // Expect: real
  auto tok = expect<token::Real>(token::Type::Real);
  if (!tok) return nullptr;

  return std::make_shared<ast::Real>(tok->span, tok->value);
}
