// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_build.hpp"
#include "arrow/log.hpp"

using arrow::pass::TypeBuild;
namespace ast = arrow::ast;
using arrow::ptr;
using arrow::isa;
using arrow::cast;

auto TypeBuild::handle_name(ptr<ast::Name> x) -> ptr<ir::Type> {
  return ir::type_of(ir::resolve_name(_ctx, x, _silent));
}

auto TypeBuild::handle_type_name(ptr<ast::TypeName> x) -> ptr<ir::Type> {
  return handle_name(x->name);
}

auto TypeBuild::handle_path(ptr<ast::Path> x) -> ptr<ir::Type> {
  return ir::type_of(ir::resolve_path(_ctx, x, _silent));
}

auto TypeBuild::handle_type_path(ptr<ast::TypePath> x) -> ptr<ir::Type> {
  return handle_path(x->path);
}
