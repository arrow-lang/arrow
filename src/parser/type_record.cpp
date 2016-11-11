// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_type_record() -> ptr<ast::TypeRecord> {
  // Expect: `struct`
  auto begin_tok = expect(token::Type::Struct);
  if (!begin_tok) return nullptr;

  // Expect: identifier
  auto id = parse_id();
  if (!id) return nullptr;

  // Expect: `{`
  if (!expect(token::Type::LeftBrace)) return nullptr;

  // Parse members in sequence
  std::vector<ptr<ast::TypeRecordMember>> members;
  while (
    (_t.peek()->type != token::Type::RightBrace) &&
    (_t.peek()->type != token::Type::End)
  ) {
    // Parse
    auto m = parse_type_record_member();
    if (!m) return nullptr;
    members.push_back(m);

    // Check for a sequence continuation token
    auto tok = _t.peek();
    bool continue_ = false;
    while (tok->type == token::Type::Semicolon) {
      _t.pop();
      tok = _t.peek();
      continue_ = true;
    }
    if (continue_) continue;

    // Done
    break;
  }

  // Expect: `}`
  auto end_tok = expect(token::Type::RightBrace);
  if (!end_tok) return nullptr;

  return std::make_shared<ast::TypeRecord>(
    begin_tok->span.extend(end_tok->span), id->text, members);
}

auto Parser::parse_type_record_member() -> ptr<ast::TypeRecordMember> {
  // Expect: identifier
  auto id = parse_id();
  if (!id) return nullptr;

  // Expect: `:`
  if (!expect(token::Type::Colon)) return nullptr;

  // Expect: type
  auto type = parse_type();
  if (!type) return nullptr;

  return std::make_shared<ast::TypeRecordMember>(
    id->span.extend(type->span), id->text, type);
}
