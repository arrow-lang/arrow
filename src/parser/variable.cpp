// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_variable() -> std::shared_ptr<ast::Variable> {
  // Expect: `let`
  auto tok = _t.pop();
  if (tok->type != token::Type::Let) {
    Log::get().error(tok->span, "expected `let`");
    return nullptr;
  }

  // Expect: identifier
  auto id_tok = _t.pop();
  if (id_tok->type != token::Type::Identifier) {
    Log::get().error(id_tok->span, "expected identifier");
    return nullptr;
  }

  auto id = std::dynamic_pointer_cast<token::Identifier>(id_tok);

  // Expect: `;`
  auto last_tok = _t.pop();
  if (last_tok->type != token::Type::Semicolon) {
    Log::get().error(last_tok->span, "expected `;`");
    return nullptr;
  }

  return std::make_shared<ast::Variable>(
    tok->span.extend(last_tok->span), id->text);
}
