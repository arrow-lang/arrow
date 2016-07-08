// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_COMPILER_H
#define ARROW_COMPILER_H

#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "arrow/ast.hpp"
#include "arrow/token.hpp"
#include "arrow/tokenizer.hpp"
#include "arrow/parser.hpp"
#include "arrow/ir.hpp"
#include "arrow/ptr.hpp"
#include "arrow/log.hpp"

namespace arrow {

class Compiler {
 public:
  struct Context {
    ir::Scope scope;
  };

  Compiler();

  ~Compiler() noexcept;

  Compiler(const Compiler&) = delete;
  Compiler(Compiler&&) = delete;

  Compiler& operator=(const Compiler&) = delete;
  Compiler& operator=(Compiler&&) = delete;

  void compile(ptr<ast::Module> node);

 private:
  Context _ctx;
};

/// Helper function to construct and use a compiler.
inline void compile(ptr<std::istream> is, const std::string& filename) {
  auto node = Parser(is, filename).parse();
  if (Log::get().count(arrow::LOG_ERROR) > 0) return;

  Compiler().compile(node);
}

}  // namespace arrow

#endif  // ARROW_COMPILER_H
