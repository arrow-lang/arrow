// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_statement() -> ptr<ast::Statement> {
  switch (_t.peek()->type) {
  case token::Type::Let:
    return parse_variable();

  case token::Type::Def:
    return parse_function();

  case token::Type::Octothorpe:
    return parse_preprocessor();

  case token::Type::Import:
    return parse_import();

  case token::Type::While:
    return parse_repeat();

  case token::Type::Break:
    return parse_break();

  case token::Type::Continue:
    return parse_continue();

  case token::Type::Type:
    return parse_type_alias();

  case token::Type::If: {
    // Consume IF expression as a statement
    auto expr = parse_conditional();
    if (!expr) return nullptr;

    return std::make_shared<ast::ExpressionStatement>(expr);
  }

  case token::Type::LeftBrace: {
    // Consume BLOCK expression as a statement
    auto expr = parse_block(false);
    if (!expr) return nullptr;

    return std::make_shared<ast::ExpressionStatement>(expr);
  }

  case token::Type::Extern: {
    unsigned peek = 1;
    if (_t.peek(peek)->type == token::Type::String) peek++;
    if (_t.peek(peek)->type == token::Type::Def) {
      return parse_extern_function();
    }

    // Failed to match extern ..
    _t.pop();
    if (_t.peek()->type == token::Type::String) _t.pop();
    expect({token::Type::Def});
    return nullptr;
  }

  case token::Type::Return:
    return parse_return();

  case token::Type::Semicolon:
    // Ignore spurious semicolons
    _t.pop();
    return nullptr;

  default:
    // Expression statement
    auto expr = parse_expression();
    if (!expr) return nullptr;

    // Expect a `;` to close the expression statement
    if (!expect(token::Type::Semicolon)) return nullptr;

    return std::make_shared<ast::ExpressionStatement>(expr);
  }
}
