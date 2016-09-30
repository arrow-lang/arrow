// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/parser.hpp"
#include "arrow/log.hpp"

using arrow::Parser;

auto Parser::parse_conditional() -> ptr<ast::Conditional> {
  std::vector<ptr<ast::Branch>> branches;
  ptr<ast::Block> otherwise = nullptr;
  unsigned index = 0;

  for (;;) {
    index++;
    if (index == 1 && _t.peek()->type == token::Type::If) {
      // Leading branch
      _t.pop();

      auto br = parse_branch();
      if (!br) return nullptr;

      branches.push_back(br);
      continue;
    } else if (_t.peek()->type == token::Type::Else) {
      if (_t.peek(1)->type == token::Type::If) {
        // Subsequent branch
        _t.pop();
        _t.pop();

        auto br = parse_branch();
        if (!br) return nullptr;

        branches.push_back(br);
        continue;
      } else {
        // Trailing branch (otherwise)
        _t.pop();
        otherwise = parse_block(false);
        if (!otherwise) return nullptr;
      }
    }

    // Require `if`
    if (branches.size() == 0) return expect(token::Type::If), nullptr;

    // Parsed at least one branch; get out
    break;
  }

  // Make
  auto sp = branches[0]->span;
  if (otherwise) sp = sp.extend(otherwise->span);

  return make<ast::Conditional>(sp, branches, otherwise);
}

auto Parser::parse_branch() -> ptr<ast::Branch> {
  // Parse: expression (condition)
  auto cond = parse_expression();
  if (!cond) return nullptr;

  // Parse: block
  auto block = parse_block(false);
  if (!block) return nullptr;

  return std::make_shared<ast::Branch>(
    cond->span.extend(block->span), cond, block);
}
