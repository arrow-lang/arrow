// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_H
#define ARROW_IR_TYPE_H

#include <memory>
#include <string>

#include "arrow/ir/item.hpp"

namespace arrow {
namespace ir {

struct Type : Item {
  using Item::Item;

  virtual ~Type() noexcept;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_H
