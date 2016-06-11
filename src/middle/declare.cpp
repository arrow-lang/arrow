// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/middle/declare.hpp"
#include "arrow/log.hpp"

using arrow::middle::Declare;

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    return handle_##name(std::dynamic_pointer_cast<type>(node))

auto Declare::run(ptr<ast::Node> node) -> ptr<ir::Item> {
  Match(*node) {
    ACCEPT(ast::Module, module);
    ACCEPT(ast::Variable, variable);

    Otherwise() {
      Log::get().error("not implemented for {}", typeid(*node).name());
    }
  } EndMatch;

  return nullptr;
}
