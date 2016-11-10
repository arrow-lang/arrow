// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/type_build.hpp"
#include "arrow/log.hpp"

using arrow::pass::TypeBuild;

auto TypeBuild::handle_type_path(ptr<ast::TypePath> x) -> ptr<ir::Type> {
  return handle_path(x->path);
}
