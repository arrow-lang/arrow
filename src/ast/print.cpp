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
    ACCEPT(Module, module);
    ACCEPT(Variable, variable);
    ACCEPT(ExpressionStatement, expression_statement);
    ACCEPT(Return, return);

    ACCEPT(Integer, integer);
    ACCEPT(Boolean, bool);
    ACCEPT(String, str);
    ACCEPT(Real, real);
    ACCEPT(Identifier, id);

    ACCEPT(Identity, identity);
    ACCEPT(Negate, negate);
    ACCEPT(BitNot, bit_not);
    ACCEPT(Not, not);

    ACCEPT(Mul, mul);
    ACCEPT(Div, div);
    ACCEPT(Mod, mod);
    ACCEPT(Add, add);
    ACCEPT(Sub, sub);
    ACCEPT(BitAnd, bit_and);
    ACCEPT(BitXor, bit_xor);
    ACCEPT(BitOr, bit_or);
    ACCEPT(GreaterThanOrEqualTo, gte);
    ACCEPT(GreaterThan, gt);
    ACCEPT(LessThan, lt);
    ACCEPT(LessThanOrEqualTo, lte);
    ACCEPT(EqualTo, eq);
    ACCEPT(NotEqualTo, ne);
    ACCEPT(And, and);
    ACCEPT(Or, or);
    ACCEPT(Assign, assign);

    ACCEPT(TypeName, type_name);
    ACCEPT(TypePointer, type_pointer);
    ACCEPT(TypeAlias, type_alias);

    ACCEPT(Function, function);
    ACCEPT(ExternFunction, extern_function);
    ACCEPT(Parameter, parameter);
    ACCEPT(Call, call);
    ACCEPT(Argument, argument);

    ACCEPT(Import, import);

    ACCEPT(CInclude, cinclude);

    Otherwise() {
      Log::get().error("print not implemented for node: {}",
        typeid(*node).name());
    }
  } EndMatch
}
