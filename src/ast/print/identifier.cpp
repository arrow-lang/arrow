// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_id(ptr<Identifier> n) {
  handle("Identifier", n, [&, this] {
    _w.Key("text");
    _w.String(n->text.c_str());
  });
}
