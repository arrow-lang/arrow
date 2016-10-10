// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_DIVERGENT_H
#define ARROW_IR_TYPE_DIVERGENT_H

#include <memory>
#include <string>
#include <sstream>

#include "arrow/ir/type.hpp"

namespace arrow {
namespace ir {

struct TypeDivergent : TypeT<TypeDivergent> {
  explicit TypeDivergent(ptr<Type> element)
    : Node(nullptr), TypeT(element->name), element(element) {
  }

  virtual ~TypeDivergent() noexcept;

  virtual LLVMTypeRef handle(GContext& ctx) noexcept {
    return element->handle(ctx);
  }

  virtual bool is_equal(ptr<Type> other) const {
    return element->is_equal(other);
  }

  virtual bool is_signed() const {
    return element->is_signed();
  }

  virtual bool is_unit() const {
    return element->is_unit();
  }

  virtual bool is_divergent() const {
    return true;
  }

  virtual unsigned size() const {
    return element->size();
  }

  virtual bool is_boolean() const {
    return element->is_boolean();
  }

  virtual bool is_integer() const {
    return element->is_integer();
  }

  virtual bool is_real() const {
    return element->is_real();
  }

  virtual bool is_function() const {
    return element->is_function();
  }

  ptr<Type> element;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_DIVERGENT_H
