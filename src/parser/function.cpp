// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_function() -> ptr<ast::Function> {
  // Expect: `def`
  auto begin_tok = expect(token::Type::Def);
  if (!begin_tok) return nullptr;

  // Parse: identifier (name of function)
  auto id = parse_id();
  if (!id) return nullptr;

  // Make: Function
  auto result = make<ast::Function>(begin_tok->span, id->text);

  // Expect: `(`
  if (!expect(token::Type::LeftParenthesis)) return nullptr;

  // Parse: parameters
  handle_sequence<ast::Parameter>(
    &(result->parameters),
    std::bind(&Parser::parse_parameter, this)
  );

  // Expect: `)`
  if (!expect(token::Type::RightParenthesis)) return nullptr;

  // Check for `:` to indicate return type (and parse it)
  if (_t.peek()->type == token::Type::Colon) {
    _t.pop();

    result->result_type = parse_type();
    if (!result->result_type) return nullptr;
  }

  // Expect: `{`
  if (!expect(token::Type::LeftBrace)) return nullptr;

  while (
    (_t.peek()->type != token::Type::RightBrace) &&
    (_t.peek()->type != token::Type::End)
  ) {
    // Parse a statement
    auto statement = parse_statement();
    if (!statement) return nullptr;

    // Add it to the function
    result->statements.push_back(statement);
  }

  // Expect: `}`
  auto end_tok = expect(token::Type::RightBrace);
  if (!end_tok) return nullptr;

  // Extend span for whole function
  result->span = result->span.extend(end_tok->span);

  return result;
}

auto Parser::parse_parameter() -> ptr<ast::Parameter> {
  // Parse: identifier (name of param)
  auto id = parse_id();
  if (!id) return nullptr;

  // Expect `:`
  if (!expect(token::Type::Colon)) return nullptr;

  // Parse: type
  auto type = parse_type();
  if (!type) return nullptr;

  // Check for default value and parse
  ptr<ast::Expression> default_value = nullptr;
  if (_t.peek()->type == token::Type::Equals) {
    _t.pop();

    default_value = parse_expression();
    if (!default_value) return nullptr;
  }

  return make<ast::Parameter>(
    id->span.extend(type->span), id->text, type, default_value);
}
