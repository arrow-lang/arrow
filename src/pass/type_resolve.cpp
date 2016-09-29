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

// Type reduction over a vector is done 2 at a time and falls back to
// the LHS if an inner reduction fails. This method cannot fail.
static auto type_set_reduce(std::vector<ptr<ir::Type>>& type_set) -> ptr<ir::Type> {
  ptr<ir::Type> result = type_set[0];
  for (std::size_t i = 1; i < type_set.size(); ++i) {
    auto tmp = ir::type_reduce(result, type_set[i]);
    if (!tmp) break;

    result = tmp;
  }

  return result;
}

void TypeResolve::run(ptr<ast::Node> x) {
  do {
    // Reset incomplete flag
    _incomplete = false;

    // Accept (visit each child expression)
    accept(x);

    // Enumerate through each discovered declaration
    // Ensure all variables are either annotated or there is enough information
    // to infer the type
    for (auto& item : _declare) {
      bool invalid = false;
      auto& assign_set = _assigns[item.get()];
      auto& use_set = _uses[item.get()];

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
        _incomplete = true;
        continue;
      }

      // Reduce types
      auto type = type_set_reduce(type_set);

      // Attempt to further speciaize the type using its uses
      type_set.clear();
      for (auto& use : use_set) {
        if (!use.type) {
          // An invalid type was resolved
          invalid = true;
          break;
        }

        type_set.push_back(use.type);
      }

      if (invalid) {
        _incomplete = true;
        continue;
      }

      // Treat the use types as "weak" (assign types win)
      auto temp = type_set_reduce(type_set);
      if (temp) {
        temp = ir::type_reduce(type, temp);
        if (temp) {
          type = temp;
        }
      }

      // Mark the type of the item
      item->type = type_literal_promote(type);
    }
  } while (_incomplete && (Log::get().count(arrow::LOG_ERROR) == 0));
}
