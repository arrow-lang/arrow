// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_type_path(ptr<TypePath> n) {
  handle("TypePath", n, [&, this] {
    _w.Key("segments");
    _w.StartArray();

    for (auto& s : n->segments) {
      print(s);
    }

    _w.EndArray();
  });

}
