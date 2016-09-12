// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_FUNCTION_H
#define ARROW_IR_TYPE_FUNCTION_H

#include <memory>
#include <string>

#include "arrow/ir/type.hpp"

namespace arrow {
namespace ir {

struct TypeFunction : Type {
  // TODO(mehcode): Name of function type
  TypeFunction(ptr<ast::Function> source)
    : Type(source, "<?>") {
  }

  virtual ~TypeFunction() noexcept;

  virtual LLVMTypeRef handle(GContext&) noexcept;

  virtual bool is_equal(ptr<Type>) const {
    // Functions cannot be typed yet
    return false;
  }

  // Result type
  ptr<Type> result;

  // Sequence of parameter types
  std::vector<ptr<Type>> parameters;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_FUNCTION_H
