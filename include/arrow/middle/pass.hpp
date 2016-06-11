// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_MIDDLE_PASS_H
#define ARROW_MIDDLE_PASS_H

#include <memory>
#include <string>

#include "arrow/compiler.hpp"

namespace arrow {
namespace middle {

class Pass {
 public:
  Pass() { }

  Pass(const Pass& other) = delete;
  Pass(Pass&& other) = delete;

  Pass& operator=(const Pass& other) = delete;
  Pass& operator=(Pass&& other) = delete;
};

}  // namespace middle
}  // namespace arrow

#endif  // ARROW_MIDDLE_PASS_H
