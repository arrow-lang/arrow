// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_type_alias() -> ptr<ast::TypeAlias> {
  // Expect: `type`
  auto begin_tok = expect(token::Type::Type);
  if (!begin_tok) return nullptr;

  // Expect: identifier
  auto id = parse_id();
  if (!id) return nullptr;

  // Expect: `=`
  if (!expect(token::Type::Equals)) return nullptr;

  // Expect: type
  auto type = parse_type();
  if (!type) return nullptr;

  return std::make_shared<ast::TypeAlias>(
    begin_tok->span.extend(type->span), id->text, type);
}
