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
  ptr<token::Token> expect(token::Type type, bool consume = true);

  // Expect a token of one of the passed types
  ptr<token::Token> expect(
    std::initializer_list<token::Type> types, bool consume = true);

  // Expect a token of one of the passed types
  ptr<token::Token> expect(
    std::vector<token::Type> types, bool consume = true);

  // Expect a token of a specific type (...)
  template <typename T>
  ptr<T> expect(token::Type type, bool consume = true) {
    return std::dynamic_pointer_cast<T>(expect(type, consume));
  }

  // Handle sequence (call arguments, function params, tuple, etc.)
  template <typename T>
  bool handle_sequence(
    std::vector<ptr<T>> *dst, std::function<ptr<T>()> cb,
    token::Type end = token::Type::RightParenthesis
  ) {
    while (
      (_t.peek()->type != end) &&
      (_t.peek()->type != token::Type::End)
    ) {
      // Parse
      auto elem = cb();
      if (!elem) return false;
      dst->push_back(elem);

      // Check for a sequence continuation token
      auto tok = _t.peek();
      if (tok->type == token::Type::Comma) {
        _t.pop();
        continue;
      }

      // Done
      break;
    }

    return true;
  }

  ptr<ast::Statement> parse_statement();
  ptr<ast::Variable> parse_variable();
  ptr<ast::Return> parse_return();

  ptr<ast::Block> parse_block(bool top_level, bool is_expression = false);

  ptr<ast::Expression> parse_expression(unsigned power = 0);
  ptr<ast::Expression> parse_unary_expression();
  ptr<ast::Expression> parse_postfix_expression();
  ptr<ast::Expression> parse_primary_expression();
  ptr<ast::Expression> parse_binary_expression(
    ptr<ast::Expression> lhs, unsigned power, int *result);

  ptr<ast::Integer> parse_integer();
  ptr<ast::Boolean> parse_bool();
  ptr<ast::Real> parse_real();
  ptr<ast::String> parse_str();
  ptr<ast::Identifier> parse_id();
  ptr<ast::Name> parse_name();
  ptr<ast::Expression> parse_tuple();

  ptr<ast::Type> parse_type();
  ptr<ast::TypeName> parse_type_name();
  ptr<ast::TypePointer> parse_type_pointer();
  ptr<ast::TypeAlias> parse_type_alias();
  ptr<ast::Type> parse_type_tuple();

  ptr<ast::Function> parse_function();
  ptr<ast::ExternFunction> parse_extern_function();
  ptr<ast::ExternVariable> parse_extern_variable();
  ptr<ast::Import> parse_import();
  ptr<ast::Parameter> parse_parameter();
  ptr<ast::TypeParameter> parse_type_parameter();

  ptr<ast::Call> parse_call(ptr<ast::Expression>);
  ptr<ast::Argument> parse_argument();

  ptr<ast::Conditional> parse_conditional(bool is_expression = false);
  ptr<ast::Branch> parse_branch();
  ptr<ast::Repeat> parse_repeat();
  ptr<ast::Break> parse_break();
  ptr<ast::Continue> parse_continue();

  ptr<ast::Statement> parse_preprocessor();
  ptr<ast::CInclude> parse_cinclude();

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
