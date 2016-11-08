// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_id() -> ptr<ast::Identifier> {
  // Expect: integer
  auto tok = expect<token::Identifier>(token::Type::Identifier);
  if (!tok) return nullptr;

  return std::make_shared<ast::Identifier>(tok->span, tok->text);
}

auto Parser::parse_name() -> ptr<ast::Name> {
  // Parse: identifier
  auto id = parse_id();
  if (!id) return nullptr;

  // Check for `<..>` (type arguments)
  Span end_span = id->span;
  std::vector<ptr<ast::Type>> type_arguments;
  if (_t.peek()->type == token::Type::LessThan) {
    // NOTE: A IDENTIFIER `<` is only taken as a name if the `<` is immediately
    //       adjacent to the IDENTIFIER
    // Yes this is a hack.. we'll think of a better way to parse it later
    auto sp = _t.peek()->span;
    if (
      (sp.filename == id->span.filename) &&
      (sp.begin.row == id->span.end.row) &&
      (sp.begin.column == id->span.end.column)
    ) {
      _t.pop();

      while (
        (_t.peek()->type != token::Type::GreaterThan) &&
        (_t.peek()->type != token::Type::GreaterThan_GreaterThan) &&
        (_t.peek()->type != token::Type::End)
      ) {
        // Parse
        auto elem = parse_type();
        if (!elem) return nullptr;

        type_arguments.push_back(elem);

        // Check for a sequence continuation token
        auto tok = _t.peek();
        if (tok->type == token::Type::Comma) {
          _t.pop();
          continue;
        }

        // Done
        break;
      }

      // Expect: `>` (or `>>`)
      if (_t.peek()->type == token::Type::GreaterThan) {
        auto end_tok = _t.pop();
        end_span = end_tok->span;
      } else if (_t.peek()->type == token::Type::GreaterThan_GreaterThan) {
        auto end_tok = _t.pop();
        end_span = end_tok->span;

        // Push a `>` token back on the tokenizer
        _t.push(make<token::Symbol>(token::Type::GreaterThan, end_tok->span));
      } else {
        expect(token::Type::GreaterThan);
        return nullptr;
      }
    }
  }

  return std::make_shared<ast::Name>(
    id->span.extend(end_span), id->text, type_arguments);
}
