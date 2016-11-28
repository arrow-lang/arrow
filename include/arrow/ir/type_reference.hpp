// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_REFERENCE_H
#define ARROW_IR_TYPE_REFERENCE_H

#include <memory>
#include <string>
#include <sstream>

#include "arrow/ir/type.hpp"

namespace arrow {
namespace ir {

struct TypeReference : Type {
  explicit TypeReference(ptr<ast::Node> source, ptr<Type> element)
    : Node(source), Type(element->name), element(element) {
  }

  virtual ~TypeReference() noexcept;

  virtual unsigned tag() const noexcept {
    return ARROW_TTAG_REFERENCE;
  }

  virtual LLVMTypeRef handle(GContext& ctx) noexcept {
    return LLVMPointerType(element->handle(ctx), 0);
  }

  virtual bool is_reference() const noexcept {
    return true;
  }

  virtual ptr<Type> get_element() const {
    return element;
  }

  virtual bool is_equal(ptr<ir::Type> other) const {
    if (isa<TypeReference>(other)) {
      return other->get_element()->is_equal(element);
    }

    return element->is_equal(other);
  }

  virtual bool is_integer() const noexcept {
    return element->is_integer();
  }

  virtual bool is_real() const noexcept {
    return element->is_real();
  }

  ptr<Type> element;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_REFERENCE_H
