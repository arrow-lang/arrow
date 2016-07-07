// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/middle/define.hpp"

using arrow::middle::Define;

void Define::handle_module(ptr<ir::Module> x) {
  // Iterate through each item in the module
  for (auto& item : x->items) run(item);
}
