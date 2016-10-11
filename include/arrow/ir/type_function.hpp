// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_FUNCTION_H
#define ARROW_IR_TYPE_FUNCTION_H

#include <memory>
#include <string>
#include <vector>

#include "arrow/ir/type.hpp"

namespace arrow {
namespace ir {

struct TypeFunction : Type {
  // TODO(mehcode): Name of function type
  explicit TypeFunction(ptr<ast::Function> source)
    : Node(source), Type("<?>") {
  }

  virtual ~TypeFunction() noexcept;

  virtual unsigned tag() const noexcept {
    return ARROW_TTAG_FUNCTION;
  }

  virtual LLVMTypeRef handle(GContext&) noexcept;

  virtual bool is_equal(ptr<Type>) const {
    // Functions cannot be typed yet
    return false;
  }

  virtual bool is_function() const {
    return true;
  }

  // Result type
  ptr<Type> result;

  // Sequence of parameter types
  std::vector<ptr<Type>> parameters;
};

struct TypeExternFunction : Type {
  // TODO(mehcode): Name of function type
  explicit TypeExternFunction(ptr<ast::ExternFunction> source, bool is_varidac)
    : Node(source), Type("extern <?>"), is_varidac(is_varidac) {
  }

  virtual ~TypeExternFunction() noexcept;

  virtual unsigned tag() const noexcept {
    return ARROW_TTAG_EXTERN_FUNCTION;
  }

  virtual LLVMTypeRef handle(GContext&) noexcept;

  virtual bool is_equal(ptr<Type>) const {
    // Functions cannot be typed yet
    return false;
  }

  virtual bool is_function() const {
    return true;
  }

  // Result type
  ptr<Type> result;

  // Sequence of parameter types
  std::vector<ptr<Type>> parameters;

  // Varidac
  bool is_varidac;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_FUNCTION_H
