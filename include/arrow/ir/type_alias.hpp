// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_ALIAS_H
#define ARROW_IR_TYPE_ALIAS_H

#include <memory>
#include <string>
#include <sstream>

#include "arrow/ir/type.hpp"

namespace arrow {
namespace ir {

struct TypeAlias : Type {
  explicit TypeAlias(ptr<ast::Node> source, std::string name, ptr<Type> target)
    : Node(source), Type(name), target(target) {
  }

  virtual ~TypeAlias() noexcept;

  virtual unsigned tag() const noexcept {
    return ARROW_TTAG_ALIAS;
  }

  virtual unsigned size() const noexcept {
    return target->size();
  }

  virtual bool is_integer() const noexcept {
    return target->is_integer();
  }

  virtual bool is_real() const noexcept {
    return target->is_real();
  }

  virtual LLVMTypeRef handle(GContext& ctx) noexcept {
    return target->handle(ctx);
  }

  ptr<Type> target;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_ALIAS_H
