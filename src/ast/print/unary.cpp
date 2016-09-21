// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::handle_unary(const char* name, ptr<Unary> n) {
  handle(name, n, [&, this] {
    _w.Key("operand");
    print(n->operand);
  });
}

void Print::print_identity(ptr<Identity> n) {
  handle_unary("Identity", n);
}

void Print::print_negate(ptr<Negate> n) {
  handle_unary("Negate", n);
}

void Print::print_bit_not(ptr<BitNot> n) {
  handle_unary("BitNot", n);
}

void Print::print_not(ptr<Not> n) {
  handle_unary("Not", n);
}

void Print::print_indirect(ptr<Indirect> n) {
  handle_unary("Indirect", n);
}

void Print::print_address_of(ptr<AddressOf> n) {
  handle_unary("AddressOf", n);
}
