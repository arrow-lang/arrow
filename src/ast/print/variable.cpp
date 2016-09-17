// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_variable(ptr<Variable> n) {
  handle("Variable", n, [&, this] {
    _w.Key("name");
    _w.String(n->name.c_str());

    _w.Key("mutable");
    _w.Bool(n->is_mutable);

    _w.Key("type");
    print(n->type);

    _w.Key("initializer");
    print(n->initializer);
  });
}
