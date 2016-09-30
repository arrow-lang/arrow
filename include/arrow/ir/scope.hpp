// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_SCOPE_H
#define ARROW_IR_SCOPE_H

#include <string>
#include <unordered_map>

#include "arrow/ptr.hpp"

namespace arrow {
namespace ir {

class Scope;

class ScopeBlock {
 public:
  ScopeBlock(ptr<Scope> previous, GContext& ctx)
  : _previous(previous), _ctx(ctx) {
  }

  void exit();

 private:
  ptr<Scope> _previous;
  GContext& _ctx;
};

class Scope {
 public:
  static ScopeBlock enter(ptr<Scope> scope, GContext&);

  explicit Scope(ptr<Scope> parent)
  : _parent(parent), _items(), _names() {
  }

  ~Scope() noexcept;

  void put(std::string name, ptr<ir::Node> item);
  void put(ptr<ast::Node> node, ptr<ir::Node> item, std::string name);

  bool contains(std::string name) const;
  bool contains(ptr<ast::Node> node) const;

  ptr<ir::Node> get(std::string name) const;
  ptr<ir::Node> get(ptr<ast::Node> node) const;

  template <typename T>
  ptr<T> get(std::string name) const {
    return cast<T>(get(name));
  }

  template <typename T>
  ptr<T> get(ptr<ast::Node> node) const {
    return cast<T>(get(node));
  }

  ScopeBlock enter(GContext&);

 private:
  ptr<Scope> _parent;
  std::unordered_map<void*, ptr<ir::Node>> _items;
  std::unordered_map<std::string, void*> _names;

};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_SCOPE_H
