// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_type_name(std::shared_ptr<TypeName> n) {
  handle("TypeName", n, [&, this] {
    _w.Key("name");
    _w.String(n->name.c_str());
  });
}
