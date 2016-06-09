// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/back/type.hpp"

using arrow::back::Type;

LLVMTypeRef Type::handle_bool(ptr<ir::TypeBoolean>) {
  return LLVMInt1Type();
}
