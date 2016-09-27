// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_resolve.hpp"
#include "arrow/log.hpp"
#include "mach7.hpp"

using arrow::pass::TypeResolve;

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    handle_##name(std::dynamic_pointer_cast<type>(x)); break

void TypeResolve::run(ptr<ast::Node> x) {
  Match(*x) {
    ACCEPT(ast::Module, module);
    ACCEPT(ast::Variable, variable);
    // ACCEPT(ast::Function, function);
    // ACCEPT(ast::ExternFunction, extern_function);
    ACCEPT(ast::Block, block);

    Otherwise() {
      Log::get().error("TypeResolve not implemented for {}", typeid(*x).name());
    }
  } EndMatch;
}
