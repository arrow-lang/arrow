// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/file.hpp"

#include <utf8.h>

using arrow::File;

File::File(ptr<std::istream> is) :
  _stream(is), _queue(), _row(0), _column(0) {
}


char32_t File::peek(unsigned offset) {
  if (!_read(offset + 1)) return 0;

  return _queue.at(offset);
}

char32_t File::pop(unsigned offset) {
  if (!_read(offset + 1)) return 0;

  char32_t ch;
  offset += 1;
  while (offset-- > 0) {
    // Get (and consume) the next byte.
    ch = _queue.front(); _queue.pop_front();

    // Advance the column position
    _column += 1;

    // If at a newline; reset the column position and advance the row position
    if (ch == 0x0a) {
      _column = 0;
      _row += 1;
    }
  }

  return ch;
}

bool File::_read(unsigned count) {
  // If we have enough characters in the queue; just return
  if (_queue.size() >= count) return true;

  std::istreambuf_iterator<char> end;
  unsigned needed = count - _queue.size();
  for (; needed > 0; --needed) {
    std::istreambuf_iterator<char> beg(*_stream);
    if (beg == end) {
      // Hit the end-of-file
      return false;
    }

    // Normalize line ending; only return 'Line Feed' to signal EOL
    auto ch = utf8::next(beg, end);
    if (ch == 0x0d) {  // Carriage Return
      ch = 0x0a;  // Interpret us as a Line Feed
      // Check if the next char is 'Carriage Return' and if so, drop it
      if (beg != end) {
        auto ch2 = utf8::next(beg, end);
        if (ch2 != 0x0a) {  // CR + LF or just CR
          _stream->seekg(-1, std::ios::cur);
        }
      }
    }

    _queue.push_back(ch);
  }

  return true;
}
