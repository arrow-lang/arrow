// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_import(ptr<ast::Import> x) -> ptr<ir::Value> {
  Log::get().error(x->span, "not implemented");

  return nullptr;
}
