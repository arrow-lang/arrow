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

struct Module;

struct Function : Item, Value {
  Function(ptr<ast::Function> source, ptr<Module> module, std::string name, ptr<TypeFunction> type)
    : Node(source), Item(name), Value(type), statements(), _module(module) {
  }

  virtual ~Function() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  virtual void generate(GContext&);

  // Get mangled name (for linking and loading)
  std::string name_mangle() const;

  // Statements in the function
  std::vector<ptr<Value>> statements;

 private:
  // Module (container)
  ptr<Module> _module;

  // Slot
  LLVMValueRef _handle = nullptr;
};

struct ExternFunction : Item, Value {
  ExternFunction(ptr<ast::ExternFunction> source, ptr<Module> module, std::string name, ptr<TypeExternFunction> type)
    : Node(source), Item(name), Value(type), _module(module) {
  }

  virtual ~ExternFunction() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  virtual void generate(GContext&);

 private:
  // Module (container)
  ptr<Module> _module;

  // Slot
  LLVMValueRef _handle = nullptr;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_FUNCTION_H
