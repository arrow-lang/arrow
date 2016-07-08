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

  case token::Type::Semicolon:
    // Ignore spurious semicolons
    _t.pop();
    return nullptr;

  default:
    // Expression statement
    auto expr = parse_expression();
    if (!expr) return nullptr;

    return std::make_shared<ast::ExpressionStatement>(expr);
  }
}
