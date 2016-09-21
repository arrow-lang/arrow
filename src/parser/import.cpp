// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_import() -> ptr<ast::Import> {
  // Expect: `import`
  auto tok_begin = expect(token::Type::Import);
  if (!tok_begin) return nullptr;

  // Expect: string (source)
  auto src = parse_str();
  if (!src) return nullptr;

  // Check for `as ...` (for alias)
  auto span = tok_begin->span.extend(src->span);
  std::string alias;
  if (_t.peek()->type == token::Type::As) {
    _t.pop();
    auto aliasN = parse_id();
    if (!aliasN) return nullptr;

    span = span.extend(aliasN->span);
    alias = aliasN->text;
  }

  return std::make_shared<ast::Import>(span, src->value, alias);
}
