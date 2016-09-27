// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Scope;
using arrow::ir::ScopeBlock;

Scope::~Scope() noexcept {
}

void Scope::put(ptr<ast::Node> node, ptr<ir::Node> item, std::string name) {
  _items[node.get()] = item;
  _names[name] = node.get();
}

void Scope::put(std::string name, ptr<ir::Node> item) {
  _items[item.get()] = item;
  _names[name] = item.get();
}

bool Scope::contains(std::string name) const {
  return get(name) != nullptr;
}

bool Scope::contains(ptr<ast::Node> node) const {
  return get(node) != nullptr;
}

auto Scope::get(std::string name) const -> ptr<ir::Node> {
  auto target = this;
  while (target != nullptr) {
    auto ref = target->_names.find(name);
    if (ref != target->_names.end()) {
      return target->_items.at(ref->second);
    }

    target = target->_parent ? target->_parent.get() : nullptr;
  }

  return nullptr;
}

auto Scope::get(ptr<ast::Node> node) const -> ptr<ir::Node> {
  if (!node) return nullptr;

  auto target = this;
  while (target != nullptr) {
    auto ref = target->_items.find(node.get());
    if (ref != target->_items.end()) {
      return ref->second;
    }

    target = target->_parent ? target->_parent.get() : nullptr;
  }

  return nullptr;
}

auto Scope::enter(ptr<Scope> scope, GContext& ctx) -> ir::ScopeBlock {
  auto previous = ctx.scope;
  ctx.scope = scope;

  return ScopeBlock(previous, ctx);
}

void ScopeBlock::exit() {
  _ctx.scope = _previous;
}
