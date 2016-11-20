// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "fmt.hpp"

#include "arrow/ast/print.hpp"
#include "arrow/log.hpp"

using arrow::ast::Print;

Print::Print() : _s(), _w(_s) {
  _w.SetIndent(' ', 2);
}

Print::~Print() noexcept {
}

void Print::run(ptr<Node> node) {
  print(node);

  if (arrow::Log::get().count(arrow::LOG_ERROR) == 0) {
    // Print out the generated JSON AST
    fmt::print("{}\n", _s.GetString());
  }
}

void Print::handle(
  const char* name, ptr<Node> n, std::function<void()> handle
) {
  _w.StartObject();

  _w.Key("tag");
  _w.String(name);

  _w.Key("span");
  _w.String(n->span.to_string().c_str());

  handle();

  _w.EndObject();
}

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    return print_##name(std::dynamic_pointer_cast<type>(node))

void Print::print(ptr<Node> node) {
  if (!node) {
    // Null
    _w.Null();
    return;
  }

  Match(*node) {
    ACCEPT(Add, add);
    ACCEPT(AddressOf, address_of);
    ACCEPT(And, and);
    ACCEPT(Argument, argument);
    ACCEPT(Assign, assign);
    ACCEPT(AssignAdd, assign_add);
    ACCEPT(AssignBitAnd, assign_bit_and);
    ACCEPT(AssignBitOr, assign_bit_or);
    ACCEPT(AssignBitXor, assign_bit_xor);
    ACCEPT(AssignDiv, assign_div);
    ACCEPT(AssignMod, assign_mod);
    ACCEPT(AssignMul, assign_mul);
    ACCEPT(AssignSub, assign_sub);
    ACCEPT(BitAnd, bit_and);
    ACCEPT(BitNot, bit_not);
    ACCEPT(BitOr, bit_or);
    ACCEPT(BitXor, bit_xor);
    ACCEPT(Block, block);
    ACCEPT(Boolean, bool);
    ACCEPT(Branch, branch);
    ACCEPT(Break, break);
    ACCEPT(Call, call);
    ACCEPT(CInclude, cinclude);
    ACCEPT(Conditional, conditional);
    ACCEPT(Continue, continue);
    ACCEPT(Div, div);
    ACCEPT(EqualTo, eq);
    ACCEPT(ExpressionStatement, expression_statement);
    ACCEPT(ExternFunction, extern_function);
    ACCEPT(Function, function);
    ACCEPT(GreaterThan, gt);
    ACCEPT(GreaterThanOrEqualTo, gte);
    ACCEPT(Identifier, id);
    ACCEPT(Identity, identity);
    ACCEPT(Implement, implement);
    ACCEPT(Import, import);
    ACCEPT(Indirect, indirect);
    ACCEPT(Integer, integer);
    ACCEPT(Interface, interface);
    ACCEPT(LessThan, lt);
    ACCEPT(LessThanOrEqualTo, lte);
    ACCEPT(Mod, mod);
    ACCEPT(Module, module);
    ACCEPT(Mul, mul);
    ACCEPT(Name, name);
    ACCEPT(Negate, negate);
    ACCEPT(Not, not);
    ACCEPT(NotEqualTo, ne);
    ACCEPT(Or, or);
    ACCEPT(Parameter, parameter);
    ACCEPT(Path, path);
    ACCEPT(Real, real);
    ACCEPT(Repeat, repeat);
    ACCEPT(Return, return);
    ACCEPT(String, str);
    ACCEPT(Sub, sub);
    ACCEPT(Transmute, transmute);
    ACCEPT(Tuple, tuple);
    ACCEPT(TypeAlias, type_alias);
    ACCEPT(TypeFunction, type_function);
    ACCEPT(TypeName, type_name);
    ACCEPT(TypeParameter, type_parameter);
    ACCEPT(TypePath, type_path);
    ACCEPT(TypePointer, type_pointer);
    ACCEPT(TypeRecord, type_record);
    ACCEPT(TypeRecordMember, type_record_member);
    ACCEPT(TypeTuple, type_tuple);
    ACCEPT(TypeUnit, type_unit);
    ACCEPT(Unit, unit);
    ACCEPT(Variable, variable);

    Otherwise() {
      Log::get().error("print not implemented for node: {}",
        typeid(*node).name());
    }
  } EndMatch
}
