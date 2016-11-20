// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_interface(ptr<Interface> n) {
  handle("Interface", n, [&, this] {
    _w.Key("type_parameters");
    _w.StartArray();

    for (auto& param : n->type_parameters) {
      print(param);
    }

    _w.EndArray();

    _w.Key("name");
    _w.String(n->name.c_str());

    _w.Key("functions");
    _w.StartArray();

    for (auto& fn : n->functions) {
      print(fn);
    }

    _w.EndArray();
  });
}
