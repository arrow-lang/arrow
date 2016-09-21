// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_type_pointer(ptr<TypePointer> n) {
  handle("TypePointer", n, [&, this] {
    _w.Key("element");
    print(n->element);
  });
}
