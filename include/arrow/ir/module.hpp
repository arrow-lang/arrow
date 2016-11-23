// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_MODULE_H
#define ARROW_IR_MODULE_H

#include <unordered_map>
#include <string>
#include <vector>

#include "arrow/ir/item.hpp"
#include "arrow/ir/value.hpp"
#include "arrow/ir/block.hpp"

namespace arrow {
namespace ir {

struct Module : Item {
  Module(ptr<ast::Module> source, std::string name, std::string filename)
    : Node(source), Item(name), block(nullptr), initializer(nullptr), filename(filename), _initialized(false) {
  }

  virtual ~Module() noexcept;

  virtual LLVMValueRef handle(GContext&);

  // Block (statements in module)
  ptr<Block> block;

  // Reference to LLVM Initializer
  LLVMValueRef initializer;

  // Filename
  std::string filename;

 private:
  bool _initialized;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_MODULE_H
