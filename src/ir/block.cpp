// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Block;

LLVMValueRef Block::handle(GContext& ctx) noexcept {
  if (!_handle) {
    for (std::size_t i = 0; i < statements.size(); ++i) {
      auto stmt = statements[i];
      if (i < (statements.size() - 1)) {
        // Not last one
        stmt->handle(ctx);
      } else {
        // Last one
        _handle = stmt->value_of(ctx);
      }
    }
  }

  return _handle;
}
