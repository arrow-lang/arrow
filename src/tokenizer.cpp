// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <string>

#include "arrow/tokenizer.hpp"

using arrow::Tokenizer;

Tokenizer::Tokenizer(
  std::shared_ptr<std::istream> is, const std::string& filename) :
    _queue(), _scanners(), _file(is), _filename(filename) {
  // Initialize scanners
  // _scanners.push_back(std::bind(&Tokenizer::_scan_numeric, this));
}

auto Tokenizer::pop() -> std::shared_ptr<Token> {
  if (!_read(1)) return nullptr;

  // Get (and consume) the next byte.
  auto tok = _queue.front(); _queue.pop_front();
  return tok;
}

auto Tokenizer::peek(unsigned offset) -> std::shared_ptr<Token> {
  if (!_read(offset + 1)) return nullptr;

  // Peek (and perserve) the `offset` token.
  return _queue.at(offset);
}
