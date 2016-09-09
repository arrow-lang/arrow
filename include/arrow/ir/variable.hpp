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
  Variable(ptr<ast::Variable> source, std::string name, bool is_global)
    : Item(source, name), Value(nullptr), _is_global(is_global) {
  }

  virtual ~Variable() noexcept;

  virtual bool is_addressable() const {
    return true;
  }

  virtual LLVMValueRef handle(GContext&) noexcept;

  virtual void generate(GContext&);

   // Initializer
   ptr<ir::Value> initializer = nullptr;

 private:
  // Slot
  LLVMValueRef _handle = nullptr;

  // If this is a global vairable or not
  bool _is_global;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_VARIABLE_H
