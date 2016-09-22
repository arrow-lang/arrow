// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_STRING_H
#define ARROW_IR_STRING_H

#include <string>

#include "arrow/ir/value.hpp"
#include "arrow/ir/type_string.hpp"

namespace arrow {
namespace ir {

struct String : Value {
  explicit String(ptr<ast::Node> source, std::string value) : Node(source), Value(make<TypeString>()), value(value) {
  }

  virtual ~String() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  std::string value;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_STRING_H
