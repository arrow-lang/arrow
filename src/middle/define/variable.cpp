// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/middle/define.hpp"
#include "arrow/middle/build.hpp"

using arrow::middle::Define;

void Define::handle_variable(ptr<ir::Variable> item) {
  // Define the initializer expression (if present)
  auto source = cast<ast::Variable>(item->source);
  if (source && source->initializer) {
    item->initializer = Build().run(source->initializer);
  }
}
