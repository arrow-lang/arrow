// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/pass/build.hpp"

using arrow::pass::Build;

auto Build::handle_type_record(ptr<ast::TypeRecord> x) -> ptr<ir::Value> {
  // Do nothing (all done in declare/type_resolve)
  return nullptr;
}
