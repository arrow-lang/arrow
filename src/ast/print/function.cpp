// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_function(ptr<Function> n) {
  handle("Function", n, [&, this] {
    _w.Key("name");
    _w.String(n->name.c_str());

    _w.Key("result_type");
    print(n->result_type);

    _w.Key("parameters");
    _w.StartArray();

    for (auto& param : n->parameters) {
      print(param);
    }

    _w.EndArray();

    _w.Key("block");
    print(n->block);
  });
}

void Print::print_extern_function(ptr<ExternFunction> n) {
  handle("ExternFunction", n, [&, this] {
    _w.Key("name");
    _w.String(n->name.c_str());

    _w.Key("result_type");
    print(n->result_type);

    _w.Key("parameters");
    _w.StartArray();

    for (auto& param : n->parameters) {
      print(param);
    }

    _w.EndArray();
  });
}

void Print::print_parameter(ptr<Parameter> n) {
  handle("Parameter", n, [&, this] {
    _w.Key("name");
    _w.String(n->name.c_str());

    _w.Key("type");
    print(n->type);
  });
}
