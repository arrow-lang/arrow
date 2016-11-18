// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "llvm.hpp"
#include "mach7.hpp"

#include "arrow/pass/build.hpp"
#include "arrow/log.hpp"

using arrow::pass::Build;

auto Build::handle_name(ptr<ast::Name> x) -> ptr<ir::Value> {
  // TODO: Error when not a value-able expression (eg. module)
  return cast<ir::Value>(ir::resolve_name(_ctx, x, false));
}

auto Build::handle_path(ptr<ast::Path> x) -> ptr<ir::Value> {
  // TODO: Error when not a value-able expression (eg. module)
  auto r = cast<ir::Value>(ir::resolve_path(_ctx, x, false, true));
  return r;
}
