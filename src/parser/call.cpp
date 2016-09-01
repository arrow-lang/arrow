// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_call(ptr<ast::Expression> operand) -> ptr<ast::Call> {
  // Expect: `(`
  auto begin_tok = expect(token::Type::LeftParenthesis);
  if (!begin_tok) return nullptr;

  // Make: Call
  auto result = make<ast::Call>(begin_tok->span, operand);

  // Parse: arguments
  handle_sequence<ast::Argument>(
    &(result->arguments),
    std::bind(&Parser::parse_argument, this)
  );

  // Expect: `)`
  auto end_tok = expect(token::Type::RightParenthesis);
  if (!end_tok) return nullptr;

  // Extend span for whole call
  result->span = result->span.extend(end_tok->span);

  return result;
}

auto Parser::parse_argument() -> ptr<ast::Argument> {
  // TODO: Named argument

  // Parse: value
  auto value = parse_expression();
  if (!value) return nullptr;

  return make<ast::Argument>(value->span, value);
}
