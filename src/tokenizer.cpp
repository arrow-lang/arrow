// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <utf8.h>

#include <string>
#include <sstream>
#include <vector>

#include "arrow/tokenizer.hpp"
#include "arrow/log.hpp"

using std::vector;
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

/// Test and check if it is within the expected range
static bool in_range(uint32_t ch, uint32_t begin, uint32_t end) {
  return (ch >= begin) && (ch <= end);
}

static bool in_ranges(uint32_t value, const vector<vector<uint32_t>>& ranges) {
  for (auto& range : ranges) {
    auto min = range[0];
    auto max = range[1];

    if ((value >= min) && (value <= max)) {
      return true;
    }
  }

  return false;
}

Tokenizer::Tokenizer(
  std::shared_ptr<std::istream> is, const std::string& filename) :
    _queue(), _scanners(), _file(is), _filename(filename) {
  // Initialize scanners
  _scanners.push_back(std::bind(&Tokenizer::_scan_numeric, this));
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

void Tokenizer::_consume_number(std::stringstream& ss, unsigned base) {
  for (unsigned idx = 0; ; ++idx) {
    // Peek at the next digit
    auto ch = _file.peek();

    // Check if this is a valid digit (for our base)
    if (idx != 0 && ch == '_') {
      _file.pop();
      continue;
    } else if (base == 16) {
      if (!(in_range(ch, '0', '9') ||
            in_range(ch, 'a', 'f') ||
            in_range(ch, 'A', 'F'))) {
        break;
      }
    } else if (!in_range(ch, '0', '0' + (base - 1))) {
      break;
    }

    // Push it into the buffer
    ss << static_cast<char>(ch);

    // Advance the input buffer
    _file.pop();
  }
}

auto Tokenizer::_scan_numeric() -> std::shared_ptr<Token> {
  // Peek ahead and see if we /are/ a digit (and stop now if we aren't)
  if (!in_range(_file.peek(), '0', '9')) return nullptr;

  // Initialize the text buffer.
  std::stringstream text;

  // Store the initial position.
  auto begin = _file.position();

  // Declare a var to store the inferred type and base.
  auto type = token::Type::Integer;
  auto base = 10;

  // Determine the base of the number
  if (_file.peek(0) == '0') {
    auto ch = _file.peek(1);
    auto prefix = true;
    if (ch == 'x' || ch == 'X') {
      // Hexadecimal
      base = 16;
    } else if (ch == 'b' || ch == 'B') {
      // Binary
      base = 2;
    } else if (ch == 'o' || ch == 'O') {
      // Octal
      base = 8;
    } else {
      // decimal
      prefix = false;
    }

    // Consume the base prefix (if present)
    if (prefix) {
      _file.pop();
      _file.pop();
    }
  }

  // Consume the (first part of the) number
  _consume_number(text, base);

  // We are no longer a number (within our range)
  if (base == 10) {
    if (_file.peek() == '.' && in_range(_file.peek(1), '0', '9')) {
      // We have at least '.#' to go; we can be a float
      type = token::Type::Float;

      // Push the `.` into the buffer
      text << static_cast<char>(_file.pop());

      // Consume the fractional part of the number
      _consume_number(text, base);
    }

    // We could continue into a scientific notation
    // with `[eE][+-]?[0-9]`
    auto p0 = _file.peek(0);
    auto p1 = _file.peek(1);
    auto p2 = _file.peek(2);
    if ((p0 == 0x45 || p0 == 0x65)
          && (in_range(p1, '0', '9')
            || ((p1 == 0x2b || p1 == 0x2d) && in_range(p2, '0', '9')))) {
      // We have at least [eE][+-]#
      type = token::Type::Float;

      // Push the first two characters.
      text << static_cast<char>(_file.pop());
      text << static_cast<char>(_file.pop());

      // Consume the expected number (again).
      _consume_number(text, base);
    }
  }

  auto span = Span(_filename, begin, _file.position());
  if (type == token::Type::Integer) {
    return std::make_shared<token::Integer>(span, text.str(), base);
  } else {
    long double value = std::stold(text.str());
    return std::make_shared<token::Float>(span, value);
  }
}
