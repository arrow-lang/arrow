// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_FUNCTION_H
#define ARROW_IR_FUNCTION_H

#include <vector>

#include "arrow/ir/item.hpp"
#include "arrow/ir/value.hpp"
#include "arrow/ir/type_function.hpp"
#include "arrow/ir/block.hpp"
#include "arrow/ir/generic.hpp"

namespace arrow {
namespace ir {

struct Module;
struct Function;

struct Parameter : Item, Value {
  Parameter(ptr<ast::Parameter> source, std::string name)
    : Node(source), Item(name), Value(nullptr) {
  }

  virtual ~Parameter() noexcept;

  virtual bool is_addressable() const {
    return true;
  }

  virtual LLVMValueRef handle(GContext&) noexcept {
    return _handle;
  }

 private:
  friend struct Function;

  // Slot
  LLVMValueRef _handle = nullptr;
};

struct Function : Item, Value {
  Function(ptr<ast::Function> source, ptr<Module> module, std::string name, ptr<TypeFunction> type)
    : Node(source), Item(name), Value(type), block(nullptr), parameters(), _module(module) {
  }

  virtual ~Function() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  // Get mangled name (for linking and loading)
  std::string name_mangle() const;

  // Function block – body
  ptr<Block> block;

  // Function parameters
  std::vector<ptr<Parameter>> parameters;

 protected:
  // Module (container)
  ptr<Module> _module;

  // Slot
  LLVMValueRef _handle = nullptr;
};

struct GenericFunction : Item, Generic {
  GenericFunction(ptr<ast::Function> source, ptr<Module> module, std::string name, std::vector<ptr<GenericTypeParameter>> type_parameters)
    : Node(source), Item(name), Generic(type_parameters), _module(module) {
  }

  virtual ~GenericFunction() noexcept;

 protected:
  // Module (container)
  ptr<Module> _module;

 private:
  virtual ptr<ir::Node> do_instantiate(GContext&, std::vector<ptr<ir::Type>>&);
};

struct ExternFunction : Function {
  ExternFunction(ptr<ast::ExternFunction> source, ptr<Module> module, std::string name, ptr<TypeExternFunction> type)
    : Node(source), Function(source, module, name, type) {
  }

  virtual ~ExternFunction() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_FUNCTION_H
