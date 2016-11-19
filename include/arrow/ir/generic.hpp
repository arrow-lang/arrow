// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_GENERIC_H
#define ARROW_IR_GENERIC_H

#include <string>

#include "arrow/ir/item.hpp"

namespace arrow {
namespace ir {

// NOTE: Type parameters are distinct for later extension

struct GenericTypeParameter : Item {
  GenericTypeParameter(ptr<ast::Node> node, std::string name)
    : Node(node), Item(name) {
  }

  virtual ~GenericTypeParameter() noexcept;
};

struct Generic : virtual Node {
  Generic(std::vector<ptr<GenericTypeParameter>> parameters)
    : Node(nullptr), type_parameters(parameters), _cache() {
  }

  virtual ~Generic() noexcept;

  /// Instantiate a concrete item (with cache)
  ptr<ir::Node> instantiate(GContext& ctx, std::vector<ptr<ast::Type>>& type_arguments, Span span);

  /// Type Parameters
  std::vector<ptr<GenericTypeParameter>> type_parameters;

 private:
  /// Instantiate a concrete item
  virtual ptr<ir::Node> do_instantiate(GContext& ctx, std::vector<ptr<ir::Type>>& type_arguments) = 0;

  /// Name
  virtual std::string get_base_name() = 0;

  std::unordered_map<std::string, ptr<ir::Node>> _cache;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_GENERIC_H
