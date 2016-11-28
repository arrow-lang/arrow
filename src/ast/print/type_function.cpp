// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_type_function(ptr<TypeFunction> n) {
  handle("TypeFunction", n, [&, this] {
    _w.Key("parameters");
    _w.StartArray();

    for (auto& param : n->parameters) {
      print(param);
    }

    _w.EndArray();

    _w.Key("result");
    print(n->result);
  });
}

void Print::print_type_function_parameter(ptr<TypeFunctionParameter> n) {
  handle("TypeFunctionParameter", n, [&, this] {
    _w.Key("type");
    print(n->type);

    _w.Key("is_mutable");
    _w.Bool(n->is_mutable);
  });
}
