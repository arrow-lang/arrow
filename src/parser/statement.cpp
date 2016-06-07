// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_statement() -> std::shared_ptr<ast::Statement> {
  switch (_t.peek()->type) {
  case token::Type::Let:
    return parse_variable();

  case token::Type::Semicolon:
    // Ignore spurious semicolons
    _t.pop();
    return nullptr;

  default:
    Log::get().error(_t.pop()->span, "expected statement");
    return nullptr;
  }
}
