// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "cppformat/format.h"

#include "arrow/ast/print.hpp"
#include "arrow/log.hpp"

using arrow::ast::Print;

Print::Print() : _s(), _w(_s) {
  _w.SetIndent(' ', 2);
}

Print::~Print() noexcept {
}

void Print::run(std::shared_ptr<Node> node) {
  print(node);

  if (arrow::Log::get().count(arrow::LOG_ERROR) == 0) {
    // Print out the generated JSON AST
    fmt::print("{}\n", _s.GetString());
  }
}

void Print::handle(
  const char* name, std::shared_ptr<Node> n, std::function<void()> handle
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

void Print::print(std::shared_ptr<Node> node) {
  Match(*node) {
    ACCEPT(Module, module);
    ACCEPT(Variable, variable);

    Otherwise() {
      Log::get().error("print not implemented for node: {}",
        typeid(*node).name());
    }
  } EndMatch
}
