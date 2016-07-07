// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "mach7.hpp"
#include "arrow/middle/define.hpp"
#include "arrow/log.hpp"

using arrow::middle::Define;

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    return handle_##name(std::dynamic_pointer_cast<type>(item))

void Define::run(ptr<ir::Item> item) {
  Match(*item) {
    ACCEPT(ir::Module, module);
    ACCEPT(ir::Variable, variable);

    Otherwise() {
      Log::get().error("not implemented for {}", typeid(*item).name());
    }
  } EndMatch;
}
