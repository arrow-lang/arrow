// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_PARSER_H
#define ARROW_PARSER_H

#include <memory>
#include <string>
#include <iostream>

#include "arrow/ast.hpp"
#include "arrow/token.hpp"
#include "arrow/tokenizer.hpp"

namespace arrow {

class Parser {
 public:
  Parser(std::shared_ptr<std::istream> is, const std::string& filename);

  Parser(const Parser&) = delete;
  Parser(Parser&&) = delete;

  Parser& operator=(const Parser&) = delete;
  Parser& operator=(Parser&&) = delete;

  std::shared_ptr<ast::Node> parse();

 private:
  // Expect a token of a specific type
  // Handle the proper error message on failure
  std::shared_ptr<token::Token> expect(token::Type type);

  // Expect a token of a specific type (...)
  template <typename T>
  std::shared_ptr<T> expect(token::Type type) {
    return std::dynamic_pointer_cast<T>(expect(type));
  }

  std::shared_ptr<ast::Statement> parse_statement();
  std::shared_ptr<ast::Variable> parse_variable();

  std::shared_ptr<ast::Expression> parse_expression();
  std::shared_ptr<ast::Integer> parse_integer();
  std::shared_ptr<ast::Boolean> parse_bool();
  std::shared_ptr<ast::Float> parse_float();
  std::shared_ptr<ast::String> parse_str();

  std::shared_ptr<ast::Type> parse_type();
  std::shared_ptr<ast::TypeName> parse_type_name();

  Tokenizer _t;
};

/// Helper function to construct and use an AST Parser.
inline std::shared_ptr<ast::Node> parse(
  std::shared_ptr<std::istream> is, const std::string& filename
) {
  return Parser(is, filename).parse();
}

}  // namespace arrow

#endif  // ARROW_PARSER_H
