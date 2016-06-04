// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <utf8.h>

#include <vector>
#include <string>

#include "arrow/tokenizer.hpp"
#include "arrow/log.hpp"

using std::vector;
using std::string;
using arrow::Tokenizer;

static bool is_whitespace(uint32_t ch) {
  switch (ch) {
    case 0x20:  // Space
    case 0x09:  // Tab
    case 0x0b:  // Vertical Tab
    case 0x0c:  // Form Feed
      // Considered a whitespace character (that is not a new-line)
      return true;

    default:
      // Not a whitespace character
      return false;
  }
}

bool Tokenizer::_read(unsigned count) {
  // If we've recursed enough; return
  // If we've enough tokens in the queue; return
  if (count == 0 || _queue.size() > count) return true;

  // Check for the end-of-stream condition ..
  if (_file.empty()) {
    // Reached end-of-stream, signal and get out
    _queue.push_back(std::make_shared<Token>(
      token::Type::End, Span{_filename, _file.position(), 1}));

    return _read(count - 1);
  }

  // Consume all whitespace characters (excluding new lines).
  while (is_whitespace(_file.peek())) { _file.pop(); }

  // Check if we are at a single-line comment and consume it.
  if (_consume_line_comment()) { return _read(count); }

  // Check for and consume the end-of-line character.
  // TODO(mehcode): Insert a semicolon token into the queue if the
  //                situation demands it
  if (_file.peek() == 0x0a) { _file.pop(); return _read(count); }

  // Iterate through our scanning algorithms and
  // continue until someone finds something
  for (auto& scan : _scanners) {
    auto tok = scan();
    if (tok) {
      // Found something; push it back
      _queue.push_back(tok);

      return _read(count - 1);
    }
  }

  // Reached the end; report an error for finding an
  // unknown token.
  auto sp = Span(_filename, _file.position(), 1);
  auto ch = _file.pop();
  vector<char> bytes;
  utf8::append(ch, std::back_inserter(bytes));
  std::string text(bytes.data(), bytes.size());

  Log::get().error(sp, "unexpected token: `{}`", text);

  // Keep going .. (until we get EOF)
  return _read(count);
}
