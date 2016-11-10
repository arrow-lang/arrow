// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_IMPORT_H
#define ARROW_IR_IMPORT_H

#include "arrow/ptr.hpp"
#include "arrow/ir/module.hpp"
#include "arrow/ir/item.hpp"

namespace arrow {
namespace ir {

struct Import : Item {
  explicit Import(ptr<ast::Import> source, ptr<Module> module_)
    : Node(source), Item(module_->name), module(module_) {
  }

  virtual ~Import() noexcept;

  ptr<Module> module;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_IMPORT_H
