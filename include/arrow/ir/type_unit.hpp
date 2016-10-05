// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_TYPE_UNIT_H
#define ARROW_IR_TYPE_UNIT_H

#include <memory>
#include <string>

#include "arrow/ir/type.hpp"

namespace arrow {
namespace ir {

struct TypeUnit : Type {
  TypeUnit(bool divergent) 
  : Node(nullptr), Type("()"), _divergent(divergent) {
  }

  virtual ~TypeUnit() noexcept;

  virtual LLVMTypeRef handle(GContext&) noexcept {
    return LLVMVoidType();
  }

  virtual bool is_unit() const {
  	return true;
  }

  virtual bool is_divergent() const {
    return _divergent;
  }

 private:
  bool _divergent;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_TYPE_UNIT_H
