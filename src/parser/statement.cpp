// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"

using arrow::Parser;

auto Parser::parse_statement() -> std::shared_ptr<ast::Statement> {
  switch (_t.peek()->type) {
  case token::Type::Let:
    return parse_variable();

  default:
    return nullptr;
  }
}
