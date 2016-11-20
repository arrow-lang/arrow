// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_function(bool require_block) -> ptr<ast::Function> {
  // Expect: `def`
  auto begin_tok = expect(token::Type::Def);
  if (!begin_tok) return nullptr;

  // Parse: identifier (name of function)
  auto id = parse_id();
  if (!id) return nullptr;

  // Make: Function
  auto result = make<ast::Function>(begin_tok->span, id->text);

  // Check for `<` .. `>` to indicate a generic function
  if (_t.peek()->type == token::Type::LessThan) {
    _t.pop();

    if (!handle_sequence<ast::TypeParameter>(
      &(result->type_parameters),
      std::bind(&Parser::parse_type_parameter, this),
      token::Type::GreaterThan
    )) return nullptr;

    // Expect: `>`
    if (!expect(token::Type::GreaterThan)) return nullptr;
  }

  // Expect: `(`
  if (!expect(token::Type::LeftParenthesis)) return nullptr;

  // Parse: parameters
  if (!handle_sequence<ast::Parameter>(
    &(result->parameters),
    std::bind(&Parser::parse_parameter, this)
  )) return nullptr;

  // Expect: `)`
  if (!expect(token::Type::RightParenthesis)) return nullptr;

  // Check for `:` to indicate return type (and parse it)
  if (_t.peek()->type == token::Type::Colon) {
    _t.pop();

    result->result_type = parse_type();
    if (!result->result_type) return nullptr;
  }

  // Check for `{` to indicate a block or force the block
  if (require_block || _t.peek()->type == token::Type::LeftBrace) {
    // Parse: block
    result->block = parse_block(false);
    if (!result->block) return nullptr;

    // Extend span for whole function
    result->span = result->span.extend(result->block->span);
  } else {
    // Check for (and require) a `;`
    auto tok_end = expect(token::Type::Semicolon);
    if (!tok_end) return nullptr;

    result->span = result->span.extend(tok_end->span);
  }

  return result;
}

auto Parser::parse_extern_function() -> ptr<ast::ExternFunction> {
  // Expect: `extern`
  auto begin_tok = expect(token::Type::Extern);
  if (!begin_tok) return nullptr;

  // Check for string (ABI)
  std::string abi = "cdecl";
  if (_t.peek()->type == token::Type::String) {
    abi = parse_str()->value;
  }

  // Expect: `def`
  if (!expect(token::Type::Def)) return nullptr;

  // Parse: identifier (name of function)
  auto id = parse_id();
  if (!id) return nullptr;

  // Make: Function
  auto result = make<ast::ExternFunction>(begin_tok->span, id->text, abi);

  // Expect: `(`
  if (!expect(token::Type::LeftParenthesis)) return nullptr;

  // Parse: parameters
  // TODO: Figure out how to normalize
  while (
    (_t.peek()->type != token::Type::RightParenthesis) &&
    (_t.peek()->type != token::Type::End)
  ) {
    // Check for `...` (varidac)
    if (_t.peek()->type == token::Type::Ellipsis) {
      _t.pop();
      result->is_varidac = true;
      break;
    }

    // Parse
    auto elem = parse_parameter();
    if (!elem) return nullptr;
    result->parameters.push_back(elem);

    // Check for a sequence continuation token
    auto tok = _t.peek();
    if (tok->type == token::Type::Comma) {
      _t.pop();
      continue;
    }

    // Done
    break;
  }

  // Expect: `)`
  auto end_tok = expect(token::Type::RightParenthesis);
  if (!end_tok) return nullptr;

  // Extend..
  result->span = result->span.extend(end_tok->span);

  // Check for `:` to indicate return type (and parse it)
  if (_t.peek()->type == token::Type::Colon) {
    _t.pop();

    result->result_type = parse_type();
    if (!result->result_type) return nullptr;

    // Extend..
    result->span = result->span.extend(result->result_type->span);
  }

  return result;
}

auto Parser::parse_parameter() -> ptr<ast::Parameter> {
  // Parse: identifier (name of param)
  auto id = parse_id();
  if (!id) return nullptr;

  // Expect `:`
  if (!expect(token::Type::Colon)) return nullptr;

  // Parse: type
  auto type = parse_type();
  if (!type) return nullptr;

  return make<ast::Parameter>(
    id->span.extend(type->span), id->text, type);
}

auto Parser::parse_type_parameter() -> ptr<ast::TypeParameter> {
  // NOTE: This will probably do more eventually ..

  // Parse: identifier (name of param)
  auto id = parse_id();
  if (!id) return nullptr;

  return make<ast::TypeParameter>(id->span, id->text);
}
