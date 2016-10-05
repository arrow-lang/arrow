// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_IR_BLOCK_H
#define ARROW_IR_BLOCK_H

#include <unordered_map>
#include <string>
#include <vector>

#include "arrow/ir/item.hpp"
#include "arrow/ir/value.hpp"
#include "arrow/ir/scope.hpp"

namespace arrow {
namespace ir {

struct Block : Value {
  explicit Block(ptr<ast::Block> source, ptr<Scope> parent_scope)
    : Node(source), Value(nullptr), statements(),
      scope(make<ir::Scope>(parent_scope)),
      is_expression(false), _handle(nullptr) {
  }

  virtual ~Block() noexcept;

  virtual LLVMValueRef handle(GContext&) noexcept;

  // Statements in the module (initializer)
  std::vector<ptr<Value>> statements;

  // Scope
  ptr<Scope> scope;

  // Statement OR Expression 
  bool is_expression;

 private:
  LLVMValueRef _handle;
};

}  // namespace ir
}  // namespace arrow

#endif  // ARROW_IR_BLOCK_H
