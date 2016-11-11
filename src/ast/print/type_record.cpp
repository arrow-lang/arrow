// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::print_type_record(ptr<TypeRecord> n) {
  handle("TypeRecord", n, [&, this] {
    _w.Key("name");
    _w.String(n->name.c_str());

    _w.Key("members");
    _w.StartArray();

    for (auto& param : n->members) {
      print(param);
    }

    _w.EndArray();
  });
}

void Print::print_type_record_member(ptr<TypeRecordMember> n) {
  handle("TypeRecordMember", n, [&, this] {
    _w.Key("name");
    _w.String(n->name.c_str());

    _w.Key("type");
    print(n->type);
  });
}
