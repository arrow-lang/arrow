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

Compiler::Compiler() {
}

Compiler::~Compiler() noexcept {
}

void Compiler::compile(ptr<ast::Module> node) {
  // Declare
  auto module = cast<ir::Module>(middle::Declare().run(node));

  // Define
  middle::Define().run(module);

  // Generator: Convert IR into CODE (LLVM IR)
  Generator{}.run(module).print();
}
