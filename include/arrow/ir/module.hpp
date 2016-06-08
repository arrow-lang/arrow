// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_MODULE_H
#define ARROW_IR_MODULE_H

#include <unordered_map>
#include <string>
#include <memory>

namespace arrow {
namespace ir {

struct Item;

struct Module {
  explicit Module(std::string name) : name(name), items() {
  }

  virtual ~Module() noexcept;

  // Name of the module
  std::string name;

  // Declared module items
  std::unordered_map<std::string, std::shared_ptr<Item>> items;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_MODULE_H
