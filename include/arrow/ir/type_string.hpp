// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_STRING_H
#define ARROW_IR_TYPE_STRING_H

#include <memory>
#include <string>

#include "arrow/ir/type.hpp"
#include "arrow/ir/type_pointer.hpp"

namespace arrow {
namespace ir {

struct TypeString : TypePointer {
  TypeString() : Node(nullptr), TypePointer(nullptr, make<ir::TypeInteger>(true, 8)) {
  }

  virtual ~TypeString() noexcept;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_STRING_H
