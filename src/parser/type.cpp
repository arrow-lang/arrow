// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_type() -> std::shared_ptr<ast::Type> {
  switch (_t.peek()->type) {
  case token::Type::Identifier:
    return parse_type_name();

  default:
    Log::get().error(_t.pop()->span, "expected type");
    return nullptr;
  }
}
