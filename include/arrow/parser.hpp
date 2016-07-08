// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_PARSER_H
#define ARROW_PARSER_H

#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "arrow/ast.hpp"
#include "arrow/token.hpp"
#include "arrow/tokenizer.hpp"

namespace arrow {

class Parser {
 public:
  Parser(ptr<std::istream> is, const std::string& filename);

  Parser(const Parser&) = delete;
  Parser(Parser&&) = delete;

  Parser& operator=(const Parser&) = delete;
  Parser& operator=(Parser&&) = delete;

  ptr<ast::Module> parse();

 private:
  // Expect a token of a specific type
  // Handle the proper error message on failure
  ptr<token::Token> expect(token::Type type);

  // Expect a token of one of the passed types
  ptr<token::Token> expect(
    std::initializer_list<token::Type> types);

  // Expect a token of a specific type (...)
  template <typename T>
  ptr<T> expect(token::Type type) {
    return std::dynamic_pointer_cast<T>(expect(type));
  }

  ptr<ast::Statement> parse_statement();
  ptr<ast::Variable> parse_variable();

  ptr<ast::Expression> parse_expression();
  ptr<ast::Integer> parse_integer();
  ptr<ast::Boolean> parse_bool();
  ptr<ast::Float> parse_float();
  ptr<ast::String> parse_str();
  ptr<ast::Identifier> parse_id();

  ptr<ast::Type> parse_type();
  ptr<ast::TypeName> parse_type_name();

  Tokenizer _t;
};

/// Helper function to construct and use an AST Parser.
inline ptr<ast::Node> parse(
  ptr<std::istream> is, const std::string& filename
) {
  return Parser(is, filename).parse();
}

}  // namespace arrow

#endif  // ARROW_PARSER_H
