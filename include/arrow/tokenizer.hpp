// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#pragma once

#include <string>
#include <memory>
#include <deque>
#include <fstream>
#include <vector>
#include <sstream>
#include <functional>

#include "arrow/token.hpp"
#include "arrow/file.hpp"

namespace arrow {

class Tokenizer {
  using Token = token::Token;

 public:
  Tokenizer(std::shared_ptr<std::istream> is, const std::string& filename);

  /// Peek (perserve) the next token and test if we are at the end
  /// of the input stream.
  bool empty() {
    return peek()->type == token::Type::End;
  }

  /// Peek (perserve) the token `offset` tokens away from the current position
  /// in the input stream.
  std::shared_ptr<Token> peek(unsigned offset = 0);

  /// Get (consume) the next token in the input stream.
  std::shared_ptr<Token> pop();

 private:
  bool _read(unsigned offset);

  bool _consume_line_comment();
  void _consume_number(std::stringstream& ss, unsigned base);

  std::shared_ptr<Token> _scan_numeric();

  std::deque<std::shared_ptr<Token>> _queue;
  std::vector<std::function<std::shared_ptr<Token>()>> _scanners;
  File _file;
  std::string _filename;
};

}  // namespace arrow
