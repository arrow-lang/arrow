// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_build.hpp"
#include "arrow/log.hpp"
#include "mach7.hpp"

using arrow::pass::TypeBuild;

TypeBuild::TypeBuild(GContext& ctx) : Pass(ctx) {
}

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    return handle_##name(std::dynamic_pointer_cast<type>(node))

auto TypeBuild::run(ptr<ast::Node> node) -> ptr<ir::Type> {
  Match(*node) {
    ACCEPT(ast::TypeName, type_name);
    ACCEPT(ast::Identifier, id);
    ACCEPT(ast::TypePointer, type_pointer);
    ACCEPT(ast::TypeUnit, type_unit);
    ACCEPT(ast::TypeFunction, type_function);

    Otherwise() {
      Log::get().error("TypeBuild not implemented for {}", typeid(*node).name());
    }
  } EndMatch;

  return nullptr;
}
