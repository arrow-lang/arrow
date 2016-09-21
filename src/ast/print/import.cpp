// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_import(ptr<Import> n) {
  handle("Import", n, [&, this] {
    _w.Key("source");
    _w.String(n->source.c_str());

    _w.Key("alias");
    _w.String(n->alias.c_str());
  });
}
