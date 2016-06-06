// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_integer(std::shared_ptr<Integer> n) {
  handle("Integer", n, [&, this] {
    _w.Key("value");
    _w.String(n->value.get_str(10).c_str());
  });
}
