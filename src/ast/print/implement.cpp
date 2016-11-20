// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_implement(ptr<Implement> n) {
  handle("Implement", n, [&, this] {
    _w.Key("type_parameters");
    _w.StartArray();

    for (auto& param : n->type_parameters) {
      print(param);
    }

    _w.EndArray();

    _w.Key("target");
    print(n->target);

    _w.Key("functions");
    _w.StartArray();

    for (auto& fn : n->functions) {
      print(fn);
    }

    _w.EndArray();
  });
}
