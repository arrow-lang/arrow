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

template <typename T>
class Scope {
 public:
  Scope() : _items() {
  }

  ~Scope() noexcept {
  }

  void emplace(std::string name, ptr<T> item) {
    _items[name] = item;
  }

  bool contains(std::string name) const {
    return _items.find(name) != _items.end();
  }

  ptr<T> get(std::string name) const {
    return _items.find(name)->second;
  }

 private:
  std::unordered_map<std::string, ptr<T>> _items;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_SCOPE_H
