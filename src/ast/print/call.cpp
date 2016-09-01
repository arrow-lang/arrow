// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_call(ptr<Call> n) {
  handle("Call", n, [&, this] {
    _w.Key("operand");
    print(n->operand);

    _w.Key("arguments");
    _w.StartArray();

    for (auto& arg : n->arguments) {
      print(arg);
    }

    _w.EndArray();
  });
}

void Print::print_argument(ptr<Argument> n) {
  handle("Argument", n, [&, this] {
    _w.Key("value");
    print(n->value);
  });
}
