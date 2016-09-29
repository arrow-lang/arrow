// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"
#include "arrow/log.hpp"

using arrow::pass::TypeResolve;
using arrow::ptr;
namespace ir = arrow::ir;

// Literal types are not allowed as an lvalue
static auto type_literal_promote(ptr<ir::Type> type) -> ptr<ir::Type> {
  if (type->size() == 0) {
    if (type->is_integer()) {
      // Return int64
      return arrow::make<ir::TypeInteger>(true, 64);
    }

    if (type->is_real()) {
      // Return float64
      return arrow::make<ir::TypeReal>(64);
    }
  }

  return type;
}

void TypeResolve::run(ptr<ast::Node> x) {
  bool incomplete;
  do {
    incomplete = false;

    // Accept (visit each child expression)
    accept(x);

    // Enumerate through each discovered declaration
    // Ensure all variables are either annotated or there is enough information
    // to infer the type
    for (auto& item : _declare) {
      if (item->type) continue;

      bool invalid = false;
      auto& assign_set = _assigns[item.get()];
      std::vector<ptr<ir::Type>> type_set;

      for (auto& assign : assign_set) {
        if (!assign.type) {
          // An invalid type was resolved
          invalid = true;
          break;
        }

        type_set.push_back(assign.type);
      }

      if (invalid) {
        incomplete = true;
        continue;
      }

      // TODO: Reduce types

      // Mark the type of the item
      item->type = type_literal_promote(type_set[0]);
    }

  } while (incomplete && (Log::get().count(arrow::LOG_ERROR) == 0));
}
