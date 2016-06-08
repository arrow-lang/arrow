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

namespace arrow {

class Compiler {
 public:
  Compiler();

  ~Compiler() noexcept;

  Compiler(const Compiler&) = delete;
  Compiler(Compiler&&) = delete;

  Compiler& operator=(const Compiler&) = delete;
  Compiler& operator=(Compiler&&) = delete;

  void compile(ptr<ast::Module> node);

 private:
  ptr<ir::Type> make_type(ptr<ast::Type>);

  // Map of built-in types
  std::unordered_map<std::string, ptr<ir::Type>> _btypes;
};

/// Helper function to construct and use a compiler.
inline void compile(ptr<std::istream> is, const std::string& filename) {
  Compiler().compile(Parser(is, filename).parse());
}

}  // namespace arrow

#endif  // ARROW_COMPILER_H
