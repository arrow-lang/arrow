// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_repeat(ptr<Repeat> n) {
  handle("Repeat", n, [&, this] {
    _w.Key("condition");
    print(n->condition);

    _w.Key("statements");
    _w.StartArray();

    for (auto& statement : n->block->statements) {
      print(statement);
    }

    _w.EndArray();
  });
}

void Print::print_continue(ptr<Continue> n) {
  handle("Continue", n, [&, this] {
    // Nothing
  });
}

void Print::print_break(ptr<Break> n) {
  handle("Break", n, [&, this] {
    // Nothing
  });
}
