// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/back/define.hpp"
#include "arrow/back/build.hpp"
#include "arrow/back/type.hpp"

using arrow::back::Define;
using arrow::back::Type;

void Define::handle_variable(ptr<ir::Variable> item) {
  auto handle = _ctx.get_handle(item);
  if (!handle) return;

  // Build the initializer if present; else, leave it at null
  if (item->initializer) {
    auto val = Build(_ctx).run(item->initializer);
    if (!val) return;

    // TODO: Handle non-constants for global variables
    LLVMSetInitializer(handle, val);
  }
}
