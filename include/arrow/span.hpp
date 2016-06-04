// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#pragma once

#include <string>
#include <iostream>

#include "arrow/position.hpp"

namespace arrow {

struct Span {
  Span(std::string filename, Position begin, unsigned offset) :
    filename(filename), begin(begin), end(begin + offset) {
  }

  friend std::ostream &operator<<(std::ostream &os, const Span &sp) {
    os << sp.filename << ":";

    if (sp.begin.row == sp.end.row) {
      os << sp.begin.row + 1 << ":" << sp.begin.column + 1;

      if (sp.end.column - 1 != sp.begin.column) {
        os << "-" << sp.end.column + 1;
      }
    } else {
      throw new std::runtime_error(
        "not implemented: multi-line span indication");
    }

    return os;
  }

  // Source filename where the span is located
  std::string filename;

  // [begin, end) inclusive, exclusive range that is selected
  Position begin;
  Position end;
};

}  // namespace arrow
