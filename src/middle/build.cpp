// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/middle/build.hpp"
#include "arrow/log.hpp"

using arrow::middle::Build;

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    return handle_##name(std::dynamic_pointer_cast<type>(node))

auto Build::run(ptr<ast::Node> node) -> ptr<ir::Value> {
  Match(*node) {
    ACCEPT(ast::Integer, int);
    ACCEPT(ast::Boolean, bool);
    // ACCEPT(ast::Float, float);
    // ACCEPT(ast::String, str);

    Otherwise() {
      Log::get().error("not implemented for {}", typeid(*node).name());
    }
  } EndMatch;

  return nullptr;
}
