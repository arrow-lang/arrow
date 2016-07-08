// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir/scope.hpp"

using arrow::ir::Scope;

Scope::Scope() : _items() {
}

Scope::~Scope() noexcept {
}

bool Scope::contains(std::string name) const {
  return _items.find(name) != _items.end();
}

void Scope::emplace(std::string name, ptr<Item> item) {
  _items.emplace(name, item);
}

auto Scope::get(std::string name) const -> ptr<Item> {
  return _items.find(name)->second;
}
