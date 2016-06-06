// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_FILE_H
#define ARROW_FILE_H

#include <string>
#include <fstream>
#include <deque>
#include <memory>

#include "arrow/position.hpp"
#include "arrow/token.hpp"

namespace arrow {

/// File is in charge of reading UTF-32 characters from a UTF-8 stream of data.
/// Maintains a N-lookahead buffer.
/// Operates as a queue.
class File {
 public:
  explicit File(std::shared_ptr<std::istream> is);

  /// Test for the end of the stream (EOF).
  bool empty() {
    return peek() == 0;
  }

  /// Peek (preserve) the <offset> character from the current position.
  char32_t peek(unsigned offset = 0);

  /// Pop (dispose) of the next characters up to <offset>.
  char32_t pop(unsigned offset = 0);

  /// Get the current position (that the reader is in the file)
  Position position() const noexcept {
    return Position{_row, _column};
  }

 private:
  /// Read more characters from the bound input stream
  /// until we can fulfill the request.
  bool _read(unsigned count);

  // Input stream
  std::shared_ptr<std::istream> _stream;

  // Character queue.
  std::deque<char32_t> _queue;

  // Current row, column in the file
  unsigned _row, _column;
};

}  // namespace arrow

#endif  // ARROW_FILE_H
