// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_SPAN_H
#define ARROW_SPAN_H

#include <string>
#include <iostream>
#include <sstream>

#include "arrow/position.hpp"

namespace arrow {

struct Span {
  explicit Span(std::string filename) :
    filename(filename), begin(), end() {
  }

  Span(std::string filename, Position begin, unsigned offset) :
    filename(filename), begin(begin), end(begin + offset) {
  }

  Span(std::string filename, Position begin, Position end) :
    filename(filename), begin(begin), end(end) {
  }

  friend std::ostream &operator<<(std::ostream &os, const Span &sp) {
    os << sp.filename << ":";

    if (sp.begin.row == sp.end.row) {
      os << sp.begin.row + 1 << ":" << sp.begin.column + 1;

      if (sp.end.column != sp.begin.column) {
        os << "-" << sp.end.column + 1;
      }
    } else {
      // TODO: Perhaps a better way to show this?
      os << sp.begin.row + 1 << "-" << sp.end.row + 1;
    }

    return os;
  }

  std::string to_string() const {
    std::stringstream stream;
    stream << *this;

    return stream.str();
  }

  /// Creates a new span that takes the begin position of `this` and the
  /// end position of `other`.
  inline Span extend(const Span& other) {
    return Span(filename, begin, other.end);
  }

  // Source filename where the span is located
  std::string filename;

  // [begin, end) inclusive, exclusive range that is selected
  Position begin;
  Position end;
};

}  // namespace arrow

#endif  // ARROW_SPAN_H
