// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_path(ptr<Path> n) {
  handle("Path", n, [&, this] {
    _w.Key("operand");
    print(n->operand);

    _w.Key("member");
    print(n->member);
  });
}
