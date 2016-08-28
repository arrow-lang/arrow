// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"

using arrow::pass::Build;

auto Build::handle_module(ptr<ast::Module> x) -> ptr<ir::Value> {
  // Declare module initializer
  auto init = LLVMAddFunction(_ctx.mod, "#init", LLVMFunctionType(
    LLVMVoidType(),
    nullptr,
    0,
    false
  ));

  LLVMPositionBuilderAtEnd(_ctx.irb,
    LLVMAppendBasicBlock(init, ""));

  // Iterate through each statement ..
  for (auto& statement : x->statements) {
    run(statement);
  }

  // Terminate module initializer
  LLVMBuildRetVoid(_ctx.irb);

  // Has no value
  return nullptr;
}
