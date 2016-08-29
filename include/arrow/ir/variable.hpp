// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_VARIABLE_H
#define ARROW_IR_VARIABLE_H

#include <string>

#include "llvm.hpp"
#include "arrow/ir/item.hpp"
#include "arrow/ir/value.hpp"

namespace arrow {
namespace ir {

struct Variable : Item, Value {
  Variable(ptr<ast::Variable> source, std::string name)
    : Item(source, name), Value(nullptr) {
  }

  virtual ~Variable() noexcept;

  virtual bool is_addressable() const {
    return true;
  }

  virtual LLVMValueRef handle(GContext&) noexcept;

  // Initializer
  ptr<ir::Value> initializer = nullptr;

  // Slot
  LLVMValueRef _handle = nullptr;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_VARIABLE_H
