// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_PASS_H
#define ARROW_PASS_H

#include <memory>
#include <string>

#include "arrow/generator.hpp"

namespace arrow {

class Pass {
 public:
  explicit Pass(GContext& ctx) : _ctx(ctx) { }

  Pass(const Pass& other) = delete;
  Pass(Pass&& other) = delete;

  Pass& operator=(const Pass& other) = delete;
  Pass& operator=(Pass&& other) = delete;

 protected:
  GContext& _ctx;
};

}  // namespace arrow

#endif  // ARROW_PASS_H
