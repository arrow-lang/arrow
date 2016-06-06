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
  std::shared_ptr<ast::Statement> parse_statement();
  std::shared_ptr<ast::Variable> parse_variable();

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
