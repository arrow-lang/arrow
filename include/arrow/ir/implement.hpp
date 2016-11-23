// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_IMPL_H
#define ARROW_IR_IMPL_H

#include <unordered_map>
#include <string>
#include <vector>

#include "arrow/ir/item.hpp"
#include "arrow/ir/node.hpp"
#include "arrow/ir/generic.hpp"
#include "arrow/ir/scope.hpp"

namespace arrow {
namespace ir {

struct Implement : Node {
  Implement(ptr<ast::Implement> source, ptr<Scope> parent_scope)
    : Node(source),
      scope(make<ir::Scope>(parent_scope)) {
  }

  virtual ~Implement() noexcept;

  // Scope
  ptr<Scope> scope;
};

struct GenericImplement : Generic {
  GenericImplement(ptr<ast::Implement> source, std::vector<ptr<GenericTypeParameter>> type_parameters, ptr<Scope> parent_scope)
    : Node(source),
      Generic(type_parameters),
      parent_scope(parent_scope) {
  }

  virtual ~GenericImplement() noexcept;

  // Parent Scope
  ptr<Scope> parent_scope;

 private:
  virtual ptr<ir::Node> do_instantiate(GContext&, std::vector<ptr<ir::Type>>&);

  virtual std::string get_base_name() {
    // Unused
    return "";
  }
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_IMPL_H
