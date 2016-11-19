// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_CONSTANT_H
#define ARROW_IR_CONSTANT_H

#include <string>

#include "llvm.hpp"
#include "arrow/ir/item.hpp"
#include "arrow/ir/value.hpp"

namespace arrow {
namespace ir {

struct Constant : Item, Value {
  Constant(std::string name, ptr<Type> type, ptr<Value> value)
    : Node(nullptr), Item(name), Value(type), value(value) {
  }

  virtual ~Constant() noexcept;

  virtual bool is_addressable() const {
    return false;
  }

  virtual LLVMValueRef handle(GContext& ctx) noexcept;

 private:
  ptr<ir::Value> value;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_CONSTANT_H
