// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_repeat() -> ptr<ast::Repeat> {
  // Expect: `while`
  auto begin_tok = expect(token::Type::While);
  if (!begin_tok) return nullptr;

  // Parse: expression (condition)
  auto cond = parse_expression();
  if (!cond) return nullptr;

  // Parse: block
  auto block = parse_block(false);
  if (!block) return nullptr;

  return std::make_shared<ast::Repeat>(
    begin_tok->span.extend(block->span), cond, block);
}

auto Parser::parse_break() -> ptr<ast::Break> {
  // Expect: `break`
  auto tok = expect(token::Type::Break);
  if (!tok) return nullptr;

  return std::make_shared<ast::Break>(tok->span);
}

auto Parser::parse_continue() -> ptr<ast::Continue> {
  // Expect: `continue`
  auto tok = expect(token::Type::Continue);
  if (!tok) return nullptr;

  return std::make_shared<ast::Continue>(tok->span);
}
