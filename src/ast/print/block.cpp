// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_block(
  ptr<Block> n
) {
  handle("Block", n, [&, this] {
    _w.Key("statements");
    _w.StartArray();

    for (auto& statement : n->statements) {
      print(statement);
    }

    _w.EndArray();
  });
}
