// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_return() -> ptr<ast::Return> {
  // Expect: return
  auto tok_begin = expect(token::Type::Return);
  if (!tok_begin) return nullptr;

  // Check for expression (or `;`)
  auto span = tok_begin->span;
  ptr<ast::Expression> operand;
  if (_t.peek()->type != token::Type::Semicolon) {
    operand = parse_expression();
    if (!operand) return nullptr;

    span = span.extend(operand->span);
  }

  return std::make_shared<ast::Return>(span, operand);
}
