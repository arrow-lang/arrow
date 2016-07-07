// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_MODULE_H
#define ARROW_IR_MODULE_H

#include <unordered_map>
#include <string>
#include <vector>

#include "arrow/ir/item.hpp"

namespace arrow {
namespace ir {

struct Module : Item {
  Module(ptr<ast::Module> source, std::string name)
    : Item(source, name), items() {
  }

  virtual ~Module() noexcept;

  // Items (found in the module)
  std::vector<ptr<Item>> items;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_MODULE_H
