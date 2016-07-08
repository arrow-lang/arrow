// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/back/declare.hpp"
#include "arrow/log.hpp"
#include "mach7.hpp"

using arrow::back::Declare;

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    return handle_##name(std::dynamic_pointer_cast<type>(item))

void Declare::run(ptr<ir::Item> item) {
  Match(*item) {
    ACCEPT(ir::Variable, variable);

    Otherwise() {
      Log::get().error("back::Declare not implemented for {}", typeid(*item).name());
    }
  } EndMatch;
}
