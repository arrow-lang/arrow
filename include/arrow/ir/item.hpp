// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_ITEM_H
#define ARROW_IR_ITEM_H

#include <string>

#include "arrow/ptr.hpp"
#include "arrow/ast.hpp"

namespace arrow {
namespace ir {

struct Type;

/// An item is a named, possibly exported, construct.
///  - Variable
///  - Function
///  - Module
///  - Type
struct Item {
  Item(ptr<ast::Node> source, std::string name)
    : source(source), name(name) {
  }

  virtual ~Item() noexcept;

  /// Source (in file) of the item
  ptr<ast::Node> source;

  /// Referencable name of the item
  std::string name;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_ITEM_H
