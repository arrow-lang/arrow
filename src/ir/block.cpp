// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Block;

LLVMValueRef Block::handle(GContext& ctx) noexcept {
  if (!_handle) {
    for (auto& stmt : statements) {
      _handle = stmt->handle(ctx);
    }
  }

  return _handle;
}
