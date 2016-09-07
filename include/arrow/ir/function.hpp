// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_FUNCTION_H
#define ARROW_IR_FUNCTION_H

#include "arrow/ir/item.hpp"
#include "arrow/ir/value.hpp"
#include "arrow/ir/type_function.hpp"

namespace arrow {
namespace ir {

struct Function : Item, Value {
  Function(ptr<ast::Function> source, std::string name, ptr<TypeFunction> type)
    : Item(source, name), Value(type) {
  }

  virtual ~Function() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

 private:
  // Slot
  LLVMValueRef _handle = nullptr;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_FUNCTION_H
