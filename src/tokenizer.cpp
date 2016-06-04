// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include <utf8.h>

#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "arrow/tokenizer.hpp"
#include "arrow/log.hpp"

using std::vector;
using arrow::Tokenizer;

// Keywords
static std::unordered_map<std::string, arrow::token::Type> keywords = {
  {"and",       arrow::token::Type::And         },
  {"or",        arrow::token::Type::Or          },
  {"not",       arrow::token::Type::Not         },
  {"let",       arrow::token::Type::Let         },
  {"mutable",   arrow::token::Type::Mutable     },
  {"def",       arrow::token::Type::Def         },
  {"extern",    arrow::token::Type::Extern      },
  {"export",    arrow::token::Type::Export      },
  {"import",    arrow::token::Type::Import      },
  {"from",      arrow::token::Type::From        },
  {"true",      arrow::token::Type::True        },
  {"false",     arrow::token::Type::False       },
  {"if",        arrow::token::Type::If          },
  {"unless",    arrow::token::Type::Unless      },
  {"else",      arrow::token::Type::Else        },
  {"loop",      arrow::token::Type::Loop        },
  {"while",     arrow::token::Type::While       },
  {"until",     arrow::token::Type::Until       },
  {"break",     arrow::token::Type::Break       },
  {"continue",  arrow::token::Type::Continue    },
  {"return",    arrow::token::Type::Return      },
  {"global",    arrow::token::Type::Global      },
  {"as",        arrow::token::Type::As          },
  {"struct",    arrow::token::Type::Struct      },
  {"_",         arrow::token::Type::Underscore  },
};

// Symbols
static std::map<vector<char32_t>, arrow::token::Type> symbols = {
  // 1-character
  {{'+'}, arrow::token::Type::Plus             },
  {{'-'}, arrow::token::Type::Minus            },
  {{'/'}, arrow::token::Type::Slash            },
  {{'*'}, arrow::token::Type::Asterisk         },
  {{'%'}, arrow::token::Type::Percent          },
  {{'&'}, arrow::token::Type::Ampersand        },
  {{'|'}, arrow::token::Type::Pipe             },
  {{'^'}, arrow::token::Type::Caret            },
  {{'!'}, arrow::token::Type::ExclamationMark  },
  {{'='}, arrow::token::Type::Equals           },
  {{'<'}, arrow::token::Type::LessThan         },
  {{'>'}, arrow::token::Type::GreaterThan      },
  {{'.'}, arrow::token::Type::Period           },
  {{':'}, arrow::token::Type::Colon            },
  {{';'}, arrow::token::Type::Semicolon        },
  {{'{'}, arrow::token::Type::LeftBrace        },
  {{'}'}, arrow::token::Type::RightBrace       },
  {{'('}, arrow::token::Type::LeftParenthesis  },
  {{')'}, arrow::token::Type::RightParenthesis },
  {{'['}, arrow::token::Type::LeftBracket      },
  {{']'}, arrow::token::Type::RightBracket     },
  {{','}, arrow::token::Type::Comma            },

  // 2-character
  {{'+', '='}, arrow::token::Type::Plus_Equals             },
  {{'-', '='}, arrow::token::Type::Minus_Equals            },
  {{'*', '='}, arrow::token::Type::Asterisk_Equals         },
  {{'/', '='}, arrow::token::Type::Slash_Equals            },
  {{'%', '='}, arrow::token::Type::Percent_Equals          },
  {{'&', '='}, arrow::token::Type::Ampersand_Equals        },
  {{'|', '='}, arrow::token::Type::Pipe_Equals             },
  {{'^', '='}, arrow::token::Type::Caret_Equals            },
  {{'=', '='}, arrow::token::Type::Equals_Equals           },
  {{'!', '='}, arrow::token::Type::ExclamationMark_Equals  },
  {{'>', '='}, arrow::token::Type::GreaterThan_Equals      },
  {{'<', '='}, arrow::token::Type::LessThan_Equals         },
  {{'-', '>'}, arrow::token::Type::Arrow                   },

  // 3-character
  {{'.', '.', '.'}, arrow::token::Type::Ellipsis           },
};

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
  _scanners.push_back(std::bind(&Tokenizer::_scan_string, this));
  _scanners.push_back(std::bind(&Tokenizer::_scan_symbol, this));
  _scanners.push_back(std::bind(&Tokenizer::_scan_identifier, this));
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

auto Tokenizer::_scan_symbol() -> std::shared_ptr<Token> {
  // Fill a vector with 3 characters
  vector<char32_t> test;
  for (unsigned index = 0; index < 3; ++index) {
    test.push_back(_file.peek(index));
  }

  // Iterate backwards and test in order of largest first
  std::shared_ptr<Token> result = nullptr;
  unsigned index;
  for (index = 3; index > 0; --index) {
    auto rec = symbols.find(test);
    if (rec != symbols.end()) {
      result = std::make_shared<token::Symbol>(
        rec->second, Span(_filename, _file.position(), index));

      break;
    }

    test.pop_back();
  }

  // If we matched a token; bump the matched characters
  for ( ; result && index > 0; --index) _file.pop();

  return result;
}

auto Tokenizer::_scan_identifier() -> std::shared_ptr<Token> {
  // REF: http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1518.htm

  // An identifier can contain ..
  static vector<vector<uint32_t>> can_contain = {
    {0x30, 0x39},
    {0x41, 0x5A},
    {0x5F, 0x5F},
    {0x61, 0x7A},

    {0x00A8, 0x00A8},
    {0x00AA, 0x00AA},
    {0x00AD, 0x00AD},
    {0x00AF, 0x00AF},
    {0x00B2, 0x00B5},
    {0x00B7, 0x00BA},
    {0x00BC, 0x00BE},
    {0x00C0, 0x00D6},
    {0x00D8, 0x00F6},
    {0x00F8, 0x00FF},

    {0x0100, 0x167F},
    {0x1681, 0x180D},
    {0x180F, 0x1FFF},
    {0x200B, 0x200D},
    {0x202A, 0x202E},
    {0x203F, 0x2040},
    {0x2054, 0x2054},
    {0x2060, 0x206F},

    {0x2070, 0x218F},
    {0x2460, 0x24FF},
    {0x2776, 0x2793},
    {0x2C00, 0x2DFF},
    {0x2E80, 0x2FFF},

    {0x3004, 0x3007},
    {0x3021, 0x302F},
    {0x3031, 0x303F},

    {0x3040, 0xD7FF},

    {0xF900, 0xFD3D},
    {0xFD40, 0xFDCF},
    {0xFDF0, 0xFE44},
    {0xFE47, 0xFFFD},

    {0x10000, 0x1FFFD},
    {0x20000, 0x2FFFD},
    {0x30000, 0x3FFFD},
    {0x40000, 0x4FFFD},
    {0x50000, 0x5FFFD},
    {0x60000, 0x6FFFD},
    {0x70000, 0x7FFFD},
    {0x80000, 0x8FFFD},
    {0x90000, 0x9FFFD},
    {0xA0000, 0xAFFFD},
    {0xB0000, 0xBFFFD},
    {0xC0000, 0xCFFFD},
    {0xD0000, 0xDFFFD},
    {0xE0000, 0xEFFFD},
  };

  // An identifier must not start with (of those sets) ..
  static vector<vector<uint32_t>> not_start_with = {
    {0x30, 0x39},
    {0x0300, 0x036F},
    {0x1DC0, 0x1DFF},
    {0x20D0, 0x20FF},
    {0xFE20, 0xFE2F},
  };

  // Mark our current position
  auto begin = _file.position();

  // Build our UTF8 identifier
  vector<std::uint8_t> bytes;
  unsigned count = 0;

  for (;;) {
    // Peek the next UTF-32 character
    auto ch = _file.peek(count);
    if (ch == 0) { break; }

    // Is this one of our "can-contain" characters
    if (!in_ranges(ch, can_contain)) {
      // No.. tough luck
      break;
    }

    // Are we at the beginning and is this one of our "must-not-start-with"
    // characters
    if (count == 0 && in_ranges(ch, not_start_with)) {
      // Yep.. tough luck
      break;
    }

    // Increment total counter and append our character
    count += 1;
    utf8::append(ch, std::back_inserter(bytes));
  }

  if (count == 0) {
    // Got nothing
    return nullptr;
  }

  // We found something.. pop the consumed bytes
  for (unsigned i = 0; i < count; ++i) _file.pop();

  // Make a string out of it
  auto text = std::string(reinterpret_cast<char*>(bytes.data()), bytes.size());
  auto span = Span(_filename, begin, _file.position());

  // Check for a match against a keyword
  auto kw = keywords.find(text);
  if (kw != keywords.end()) {
    // Found a keyword; create keyword token
    return std::make_shared<token::Keyword>(kw->second, span);
  }

  // Couldn't match a keyword; return as identifier
  return std::make_shared<token::Identifier>(span, text);
}

auto Tokenizer::_scan_string() -> std::shared_ptr<Token> {
  auto begin = _file.position();

  // Peek and see if we are a double-quoted string
  auto p0 = _file.peek(0);
  if (p0 != '\"') {
    // Not a string
    return nullptr;
  }

  // Drop the quote character(s)
  _file.pop();

  // Declare a buffer for bytes
  std::vector<char> bytes;

  // Iterate through the string token
  auto in_escape = false;
  auto in_byte_escape = false;

  // TODO(mehcode): auto in_unicode_escape = false;
  for (;;) {
    if (in_escape) {
      // Check if we have an extension control character.
      auto byte = _file.pop();
      switch (byte) {
        case 0x58:  // `X`
        case 0x78:  // `x`
          in_byte_escape = true;
          break;

        case 0x5c:  // `\`
        case 0x27:  // `'`
        case 0x22:  // `"`
          bytes.push_back(byte);
          break;

        case 0x61:  // `a`
          bytes.push_back('\a');
          break;

        case 0x62:  // `b`
          bytes.push_back('\b');
          break;

        case 0x66:  // `f`
          bytes.push_back('\f');
          break;

        case 0x6e:  // `n`
          bytes.push_back('\n');
          break;

        case 0x72:  // `r`
          bytes.push_back('\r');
          break;

        case 0x74:  // `t`
          bytes.push_back('\t');
          break;

        case 0x76:  // `v`
          bytes.push_back('\v');
          break;

        default:
          Log::get().error(
            Span(_filename, _file.position() - 2, _file.position()),
            "unknown character escape: {}", byte);

          break;
      }

      // No longer in an escape sequence.
      in_escape = false;
    } else if (in_byte_escape) {
      std::stringstream sstream;
      sstream << static_cast<char>(_file.pop());
      sstream << static_cast<char>(_file.pop());

      unsigned value;
      sstream >> std::hex >> value;

      bytes.push_back(value);

      // No longer in an byte escape sequence.
      in_byte_escape = false;
    } else {
      auto byte = _file.pop();

      if (byte == 0x5c) {
        in_escape = true;
      } else if (byte == 0x22) {
        // Found the matching double-quote; we're done with the string
        break;
      } else {
        utf8::append(byte, std::back_inserter(bytes));
      }
    }
  }

  auto span = Span(_filename, begin, _file.position());
  return std::make_shared<token::String>(
    span, std::string(bytes.data(), bytes.size()));
}
