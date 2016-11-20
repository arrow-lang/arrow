// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_implement() -> ptr<ast::Implement> {
  // Expect: `implement`
  auto tok_begin = expect(token::Type::Implement);
  if (!tok_begin) return nullptr;

  // Check for `<` .. `>` to indicate a generic implement
  std::vector<ptr<ast::TypeParameter>> type_parameters;
  if (_t.peek()->type == token::Type::LessThan) {
    _t.pop();

    if (!handle_sequence<ast::TypeParameter>(
      &(type_parameters),
      std::bind(&Parser::parse_type_parameter, this),
      token::Type::GreaterThan
    )) return nullptr;

    // Expect: `>`
    if (!expect(token::Type::GreaterThan)) return nullptr;
  }

  // Expect: name
  auto target = parse_name();
  if (!target) return nullptr;

  // Expect: `{`
  if (!expect(token::Type::LeftBrace)) return nullptr;

  // Iterate and attempt to parse member functions ..
  std::vector<ptr<ast::Function>> functions;
  while (
    (_t.peek()->type != token::Type::RightBrace) &&
    (_t.peek()->type != token::Type::End)
  ) {
    // Parse: Function
    auto fn = parse_function();
    if (!fn) return nullptr;
    functions.push_back(fn);
  }

  // Expect: `}`
  auto tok_end = expect(token::Type::RightBrace);
  if (!tok_end) return nullptr;

  return std::make_shared<ast::Implement>(
    tok_begin->span.extend(tok_end->span), target, type_parameters, functions);
}
