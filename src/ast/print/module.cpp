// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_module(ptr<Module> n) {
  handle("Module", n, [&, this] {
    _w.Key("statements");
    _w.StartArray();

    for (auto& statement : n->block->statements) {
      print(statement);
    }

    _w.EndArray();
  });
}
