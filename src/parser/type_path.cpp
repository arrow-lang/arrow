// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_type_path() -> ptr<ast::Type> {
  ptr<ast::Node> result;

  // Parse: Name
  result = parse_name();
  if (!result) return nullptr;

  // Check for `.` to indicate a type path
  if (_t.peek()->type == token::Type::Period) {
    while (_t.peek()->type == token::Type::Period) {
      _t.pop();

      // Parse: Name (segment)
      auto name = parse_name();
      if (!name) return nullptr;

      // Make: Path
      result = make<ast::Path>(
        result->span.extend(name->span), cast<ast::Expression>(result), name);
    }
  } else {
    // Still a name
    return make<ast::TypeName>(result->span, cast<ast::Name>(result));
  }

  // Now a path
  return make<ast::TypePath>(result->span, cast<ast::Path>(result));
}
