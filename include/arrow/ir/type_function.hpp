// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_FUNCTION_H
#define ARROW_IR_TYPE_FUNCTION_H

#include <memory>
#include <string>
#include <sstream>
#include <vector>

#include "arrow/ir/type.hpp"
#include "arrow/ir/generic.hpp"

namespace arrow {
namespace ir {

struct TypeFunction : Type {
  explicit TypeFunction(ptr<ast::Node> source, std::vector<ptr<Type>> parameters, ptr<Type> result)
    : Node(source), Type(TypeFunction::_name(parameters, result)), parameters(parameters), result(result) {
  }

  virtual ~TypeFunction() noexcept;

  virtual unsigned tag() const noexcept {
    return ARROW_TTAG_FUNCTION;
  }

  virtual LLVMTypeRef handle(GContext&) noexcept;

  virtual bool is_equal(ptr<Type> other) const {
    auto other_fn = cast<TypeFunction>(other);
    if (!other_fn) return false;

    if (!result->is_equal(other_fn->result)) return false;

    if (parameters.size() != other_fn->parameters.size()) return false;
    for (unsigned i = 0; i < parameters.size(); ++i) {
      if (!parameters[i]->is_equal(other_fn->parameters[i])) return false;
    }

    return true;
  }

  virtual bool is_function() const {
    return true;
  }

  // Sequence of parameter types
  std::vector<ptr<Type>> parameters;

  // Result type
  ptr<Type> result;

 private:
  static std::string _name(
    std::vector<ptr<Type>>& parameters,
    arrow::ptr<Type>& result
  ) {
    std::stringstream stream;
    stream << "(";

    for (unsigned i = 0; i < parameters.size(); ++i) {
      if (i > 0) stream << ",";
      stream << parameters[i]->name;
    }

    stream << ") -> ";
    stream << result->name;

    return stream.str();
  }
};

struct TypeExternFunction : TypeFunction {
  explicit TypeExternFunction(ptr<ast::Node> source, bool is_varidac, std::string abi, std::vector<ptr<Type>> parameters, ptr<Type> result)
    : Node(source), TypeFunction(source, parameters, result), is_varidac(is_varidac), abi(abi) {
    // Prepend `extern ` to the typename
    this->name = "extern \"" + abi + "\" " + this->name;
  }

  virtual ~TypeExternFunction() noexcept;

  virtual unsigned tag() const noexcept {
    return ARROW_TTAG_EXTERN_FUNCTION;
  }

  virtual LLVMTypeRef handle(GContext&) noexcept;

  virtual bool is_equal(ptr<Type> other) const {
    if (!TypeFunction::is_equal(other)) return false;

    auto other_fn = cast<TypeExternFunction>(other);
    if (!other_fn) return false;
    if (is_varidac != other_fn->is_varidac) return false;
    if (abi != other_fn->abi) return false;

    return true;
  }

  // Varidac
  bool is_varidac;

  // ABI
  std::string abi;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_FUNCTION_H
