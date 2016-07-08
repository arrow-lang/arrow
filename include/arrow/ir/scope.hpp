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

struct Item;

class Scope {
 public:
  Scope();

  virtual ~Scope() noexcept;

  void emplace(std::string name, ptr<Item> item);

  bool contains(std::string name) const;

  ptr<Item> get(std::string name) const;

 private:
  std::unordered_map<std::string, ptr<Item>> _items;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_SCOPE_H
