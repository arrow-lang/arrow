// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/compiler.hpp"
#include "arrow/log.hpp"
#include "arrow/ast.hpp"
#include "arrow/generator.hpp"

using arrow::Compiler;

Compiler::Compiler() {
}

Compiler::~Compiler() noexcept {
}

void Compiler::compile(ptr<ast::Module> node) {
  // Generator: Convert IR into CODE (LLVM IR)
  Generator g;
  g.run(node);
  if (Log::get().count(arrow::LOG_ERROR) > 0) return;

  g.print();
}
