// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_branch(ptr<Branch> n) {
  handle("Branch", n, [&, this] {
    _w.Key("condition");
    print(n->condition);

    _w.Key("block");
    print(n->block);
  });
}

void Print::print_conditional(ptr<Conditional> n) {
  handle("Conditional", n, [&, this] {
    _w.Key("branches");
    _w.StartArray();

    for (auto& br : n->branches) {
      print(br);
    }

    _w.EndArray();

    _w.Key("otherwise");
    print(n->otherwise);
  });
}
