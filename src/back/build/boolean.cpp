// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/back/build.hpp"
#include "arrow/back/type.hpp"

using arrow::back::Build;

LLVMValueRef Build::handle_bool(ptr<ir::Boolean> item) {
  auto type = Type(_ctx).run(item->type);
  return LLVMConstInt(type, item->value ? 1 : 0, false);
}
