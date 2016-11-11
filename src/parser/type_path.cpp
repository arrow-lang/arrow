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

auto Parser::parse_type_path() -> ptr<ast::TypePath> {
  // Parse: Names
  auto path = make<ast::TypePath>(Span(_t._filename));
  do {
    // Parse: Name
    auto elem = parse_name();
    if (!elem) return nullptr;

    if (path->segments.size() == 0) {
      path->span = elem->span;
    } else {
      path->span = path->span.extend(elem->span);
    }

    path->segments.push_back(elem);

    // Check for a sequence continuation token
    auto tok = _t.peek();
    if (tok->type == token::Type::Period) {
      _t.pop();
      continue;
    }

    // Done
    break;
  } while (true);

  return path;
}
