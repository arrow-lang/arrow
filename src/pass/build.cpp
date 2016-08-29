// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"
#include "mach7.hpp"

using arrow::pass::Build;

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    return handle_##name(std::dynamic_pointer_cast<type>(x))

auto Build::run(ptr<ast::Node> x) -> ptr<ir::Value> {
  Match(*x) {
    ACCEPT(ast::Module, module);
    ACCEPT(ast::Variable, variable);
    ACCEPT(ast::Identifier, id);
    ACCEPT(ast::Boolean, bool);
    ACCEPT(ast::Integer, int);
    ACCEPT(ast::ExpressionStatement, expression_statement);

    ACCEPT(ast::Add, add);
    ACCEPT(ast::Sub, sub);
    ACCEPT(ast::Mul, mul);
    ACCEPT(ast::Div, div);
    ACCEPT(ast::Mod, mod);
    ACCEPT(ast::Assign, assign);

    Otherwise() {
      Log::get().error("Build not implemented for {}", typeid(*x).name());
    }
  } EndMatch;

  return nullptr;
}
