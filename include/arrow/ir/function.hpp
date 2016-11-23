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

struct IFunction {
  virtual ~IFunction() noexcept;
  virtual LLVMValueRef invoke(GContext& ctx, std::vector<ptr<Value>>& arguments) = 0;
};

struct Function : Item, Value, IFunction {
  Function(ptr<ast::Function> source, ptr<Module> module, std::string name, ptr<TypeFunction> type, std::string namespace_)
    : Node(source), Item(name), Value(type), block(nullptr), parameters(), _module(module), _namespace(namespace_) {
  }

  virtual ~Function() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  bool has_self() const {
    if (parameters.size() < 1) return false;

    return parameters[0]->name == "self";
  }

  // Get mangled name (for linking and loading)
  std::string name_mangle() const;

  // Function block – body
  ptr<Block> block;

  // Function parameters
  std::vector<ptr<Parameter>> parameters;

  virtual LLVMValueRef invoke(GContext& ctx, std::vector<ptr<Value>>& arguments);

 protected:
  // Module (container)
  ptr<Module> _module;

  // Namespace
  std::string _namespace;

  // Slot
  LLVMValueRef _handle = nullptr;
};

struct Method : Value, IFunction {
  Method(ptr<Function> function, ptr<Value> self)
    : Node(function->source), Value(function->type), _function(function), _self(self) {
  }

  virtual ~Method() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept {
    Log::get().error("not implemented: method closure");

    return nullptr;
  }

  virtual LLVMValueRef invoke(GContext& ctx, std::vector<ptr<Value>>& arguments);

 private:
  ptr<Function> _function;
  ptr<Value> _self;
};

struct GenericFunction : Item, Generic {
  GenericFunction(ptr<ast::Function> source, ptr<Module> module, std::string name, std::vector<ptr<GenericTypeParameter>> type_parameters, std::string namespace_)
    : Node(source), Item(name), Generic(type_parameters), _module(module), _namespace(namespace_) {
  }

  virtual ~GenericFunction() noexcept;

 protected:
  // Module (container)
  ptr<Module> _module;

  // Namespace
  std::string _namespace;

 private:
  virtual ptr<ir::Node> do_instantiate(GContext&, std::vector<ptr<ir::Type>>&);

  virtual std::string get_base_name() {
    return name;
  }
};

struct ExternFunction : Item, Value, IFunction {
  ExternFunction(ptr<ast::ExternFunction> source, ptr<Module> module, std::string name, ptr<TypeExternFunction> type)
    : Node(source), Item(name), Value(type), _module(module) {
  }

  virtual ~ExternFunction() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  virtual LLVMValueRef invoke(GContext& ctx, std::vector<ptr<Value>>& arguments);

  // Function parameters
  std::vector<ptr<Parameter>> parameters;

 protected:
  // Module (container)
  ptr<Module> _module;

  // Slot
  LLVMValueRef _handle = nullptr;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_FUNCTION_H
