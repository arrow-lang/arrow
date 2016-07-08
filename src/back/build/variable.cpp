// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/log.hpp"
#include "arrow/back/build.hpp"
#include "arrow/back/type.hpp"

using arrow::back::Build;

LLVMValueRef Build::handle_variable(ptr<ir::Variable> item) {
  auto handle = _ctx.get_handle(item);

  if (LLVMIsConstant(handle)) {
    handle = LLVMGetInitializer(handle);
  } else {
    Log::get().error("[back::Build::handle_variable] non-constant initializers not implemented");
    handle = nullptr;
  }

  return handle;
}
