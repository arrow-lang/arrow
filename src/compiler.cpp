// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/compiler.hpp"
#include "arrow/log.hpp"
#include "arrow/ast.hpp"
#include "arrow/generator.hpp"
#include "arrow/middle/declare.hpp"
#include "arrow/middle/define.hpp"

using arrow::Compiler;

Compiler::Compiler() : _ctx() {
}

Compiler::~Compiler() noexcept {
}

void Compiler::compile(ptr<ast::Module> node) {
  // Declare
  auto module = cast<ir::Module>(middle::Declare(_ctx).run(node));
  if (Log::get().count(LOG_ERROR) > 0) return;

  // Define
  middle::Define(_ctx).run(module);
  if (Log::get().count(LOG_ERROR) > 0) return;

  // Generator: Convert IR into CODE (LLVM IR)
  Generator g;
  g.run(module);
  if (Log::get().count(arrow::LOG_ERROR) > 0) return;

  g.print();
}
