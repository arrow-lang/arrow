// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_H
#define ARROW_IR_H

#include "llvm.hpp"
#include "mach7.hpp"

#include "arrow/log.hpp"

#include "arrow/ir/item.hpp"
#include "arrow/ir/module.hpp"
#include "arrow/ir/variable.hpp"
#include "arrow/ir/function.hpp"
#include "arrow/ir/import.hpp"

#include "arrow/ir/type.hpp"
#include "arrow/ir/type_integer.hpp"
#include "arrow/ir/type_boolean.hpp"
#include "arrow/ir/type_function.hpp"
#include "arrow/ir/type_real.hpp"
#include "arrow/ir/type_literal_integer.hpp"
#include "arrow/ir/type_literal_real.hpp"
#include "arrow/ir/type_string.hpp"
#include "arrow/ir/type_pointer.hpp"
#include "arrow/ir/type_alias.hpp"
#include "arrow/ir/type_unit.hpp"

#include "arrow/ir/value.hpp"
#include "arrow/ir/unit.hpp"
#include "arrow/ir/transmute.hpp"
#include "arrow/ir/integer.hpp"
#include "arrow/ir/real.hpp"
#include "arrow/ir/boolean.hpp"
#include "arrow/ir/binary.hpp"
#include "arrow/ir/string.hpp"
#include "arrow/ir/unary.hpp"
#include "arrow/ir/pointer.hpp"
#include "arrow/ir/call.hpp"
#include "arrow/ir/return.hpp"

#include "arrow/ir/scope.hpp"

#include "arrow/ir/conditional.hpp"
#include "arrow/ir/repeat.hpp"

namespace arrow {
namespace ir {

// Reduce 2 types following simple rules
extern ptr<Type> type_reduce(ptr<Type> a, ptr<Type> b);

// Check if type RHS is assignable to type LHS
extern bool type_is_assignable(ptr<Type> lhs, ptr<Type> rhs);

// Get the canonical type
extern ptr<Type> type_canonical(ptr<Type> type);

// Transmute shorthand
extern ptr<Value> transmute(ptr<Value> operand, ptr<Type> type);

// Parse CC from String
extern int parse_call_conv(Span span, std::string ccs);

// Type of
inline ptr<Type> type_of(ptr<ir::Node> item) {
  // Check if we have a type directly
  auto type_item = cast<ir::Type>(item);
  if (type_item) {
    return type_item;
  }

  // Pull a type out from something
  Match(*item) {
    Case(mch::C<ir::Variable>()) {
      return cast<ir::Variable>(item)->type;
    }

    Case(mch::C<ir::Parameter>()) {
      return cast<ir::Parameter>(item)->type;
    }

    Case(mch::C<ir::TypeAlias>()) {
      return cast<ir::TypeAlias>(item);
    }

    Case(mch::C<ir::Function>()) {
      return cast<ir::Function>(item)->type;
    }

    Case(mch::C<ir::ExternFunction>()) {
      return cast<ir::ExternFunction>(item)->type;
    }

    Case(mch::C<ir::Value>()) {
      return cast<ir::Value>(item)->type;
    }
  } EndMatch

  return nullptr;
}

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_H
