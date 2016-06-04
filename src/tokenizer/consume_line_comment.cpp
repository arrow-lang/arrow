// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/tokenizer.hpp"

using arrow::Tokenizer;

bool Tokenizer::_consume_line_comment() {
  // Check if we are at a single-line comment indicator and
  // consume the comment.
  auto in_comment = false;
  bool is_begin = _file.position().row == 0;

  // If we are on the first line, and equals "#!" (shebang)
  if (is_begin && (_file.peek(0) == 0x23 && _file.peek(1) == 0x21)) {
    in_comment = true;
    _file.pop();
    _file.pop();
  }

  if (_file.peek(0) == 0x2f && _file.peek(1) == 0x2f) {  // '//'
    in_comment = true;
    _file.pop();
    _file.pop();
  }

  if (in_comment) {
    // Consume until we reach the end-of-line
    while (_file.peek() != 0x0a) _file.pop();
  }

  return in_comment;
}
