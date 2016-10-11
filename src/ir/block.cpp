// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/log.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Block;

LLVMValueRef Block::handle(GContext& ctx) noexcept {
  if (!_handle) {
    auto unreachable = false;
    Span unreachable_sp("");
    for (std::size_t i = 0; i < statements.size(); ++i) {
      auto stmt = statements[i];

      // If we have been terminated ..
      if (LLVMGetBasicBlockTerminator(LLVMGetInsertBlock(ctx.irb))) {
        // Do NOT attempt to build ..
        if (stmt->source) {
          if (unreachable) {
            unreachable_sp = unreachable_sp.extend(stmt->source->span);
          }
          else {
            unreachable = true;
            unreachable_sp = stmt->source->span;
          }
        }

        continue;
      }

      if (!is_expression || i < (statements.size() - 1)) {
        // Not last one
        stmt->handle(ctx);
      } else {
        // Last one and an expression
        _handle = stmt->value_of(ctx);
      }
    }

    if (unreachable) {
      Log::get().warn(unreachable_sp, "unreachable code");
    }
  }

  return _handle;
}
