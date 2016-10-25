// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ast/print.hpp"

using arrow::ast::Print;

void Print::handle_binary(const char* name, ptr<Binary> n) {
  handle(name, n, [&, this] {
    _w.Key("lhs");
    print(n->lhs);

    _w.Key("rhs");
    print(n->rhs);
  });
}

void Print::print_mul(ptr<Mul> n) {
  handle_binary("Mul", n);
}

void Print::print_div(ptr<Div> n) {
  handle_binary("Div", n);
}

void Print::print_mod(ptr<Mod> n) {
  handle_binary("Mod", n);
}

void Print::print_add(ptr<Add> n) {
  handle_binary("Add", n);
}

void Print::print_sub(ptr<Sub> n) {
  handle_binary("Sub", n);
}

void Print::print_bit_and(ptr<BitAnd> n) {
  handle_binary("BitAnd", n);
}

void Print::print_bit_xor(ptr<BitXor> n) {
  handle_binary("BitXor", n);
}

void Print::print_bit_or(ptr<BitOr> n) {
  handle_binary("BitOr", n);
}

void Print::print_gte(ptr<GreaterThanOrEqualTo> n) {
  handle_binary("GreaterThanOrEqualTo", n);
}

void Print::print_gt(ptr<GreaterThan> n) {
  handle_binary("GreaterThan", n);
}

void Print::print_lt(ptr<LessThan> n) {
  handle_binary("LessThan", n);
}

void Print::print_lte(ptr<LessThanOrEqualTo> n) {
  handle_binary("LessThanOrEqualTo", n);
}

void Print::print_eq(ptr<EqualTo> n) {
  handle_binary("EqualTo", n);
}

void Print::print_ne(ptr<NotEqualTo> n) {
  handle_binary("NotEqualTo", n);
}

void Print::print_and(ptr<And> n) {
  handle_binary("And", n);
}

void Print::print_or(ptr<Or> n) {
  handle_binary("Or", n);
}

void Print::print_assign(ptr<Assign> n) {
  handle_binary("Assign", n);
}

void Print::print_assign_add(ptr<AssignAdd> n) {
  handle_binary("AssignAdd", n);
}

void Print::print_assign_sub(ptr<AssignSub> n) {
  handle_binary("AssignSub", n);
}

void Print::print_assign_mul(ptr<AssignMul> n) {
  handle_binary("AssignMul", n);
}

void Print::print_assign_div(ptr<AssignDiv> n) {
  handle_binary("AssignDiv", n);
}

void Print::print_assign_mod(ptr<AssignMod> n) {
  handle_binary("AssignMod", n);
}

void Print::print_assign_bit_or(ptr<AssignBitOr> n) {
  handle_binary("AssignBitOr", n);
}

void Print::print_assign_bit_and(ptr<AssignBitAnd> n) {
  handle_binary("AssignBitAnd", n);
}

void Print::print_assign_bit_xor(ptr<AssignBitXor> n) {
  handle_binary("AssignBitXor", n);
}
