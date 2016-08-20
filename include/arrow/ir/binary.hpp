// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_BINARY_H
#define ARROW_IR_BINARY_H

#include "arrow/ir/value.hpp"

namespace arrow {
namespace ir {

struct Binary : Value {
  Binary(ptr<Type> type, ptr<Value> lhs, ptr<Value> rhs)
    : Value(type), lhs(lhs), rhs(rhs) {
  }

  virtual ~Binary() noexcept;

  ptr<Value> lhs;
  ptr<Value> rhs;
};

#define DEF_BINARY(Name) \
  struct Name : Binary { \
    using Binary::Binary; \
    virtual ~Name() noexcept; \
  }

DEF_BINARY(Add);

#undef DEF_BINARY

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_BINARY_H
