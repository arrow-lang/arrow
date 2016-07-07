// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/back/build.hpp"
#include "arrow/back/type.hpp"

using arrow::back::Build;

LLVMValueRef Build::handle_int(ptr<ir::Integer> item) {
  // TODO: Integer literals are untyped at the moment; they need
  //       concrete types
  auto type = LLVMIntType(64);

  return LLVMConstInt(type, item->value.get_ui(), false);
}
