// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"

using arrow::Parser;

auto Parser::parse_type_name() -> ptr<ast::TypeName> {
  // Parse: Name
  auto name = parse_name();
  if (!name) return nullptr;

  return std::make_shared<ast::TypeName>(name->span, name);
}
