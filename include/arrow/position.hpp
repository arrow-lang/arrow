// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_POSITION_H
#define ARROW_POSITION_H

namespace arrow {

struct Position {
  Position operator +(unsigned offset) const {
    return Position{row, column + offset};
  }

  Position operator -(unsigned offset) const {
    return Position{row, column - offset};
  }

  unsigned row;
  unsigned column;
};

}  // namespace arrow

#endif  // ARROW_POSITION_H
