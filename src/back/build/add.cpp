// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/back/build.hpp"
#include "arrow/back/type.hpp"

using arrow::back::Build;

LLVMValueRef Build::handle_add(ptr<ir::Add> x) {
  auto lhs = run(x->lhs);
  auto rhs = run(x->rhs);

  // TODO: Add IR casts to normalize the type

  auto result = LLVMBuildAdd(_ctx.irb, lhs, rhs, "");

  // TODO: Add IR cast from w/e result is to x->type

  return result;
}
