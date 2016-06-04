// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#pragma once

namespace arrow {

struct Position {
  Position operator +(unsigned offset) const {
    return Position{row, column + offset};
  }

  unsigned row;
  unsigned column;
};

}  // namespace arrow
