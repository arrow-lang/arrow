// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/back/build.hpp"
#include "arrow/log.hpp"
#include "mach7.hpp"

using arrow::back::Build;

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    return handle_##name(std::dynamic_pointer_cast<type>(item))

LLVMValueRef Build::run(ptr<ir::Value> item) {
  Match(*item) {
    ACCEPT(ir::Integer, int);
    ACCEPT(ir::Boolean, bool);
    ACCEPT(ir::Variable, variable);

    ACCEPT(ir::Add, add);

    Otherwise() {
      Log::get().error("back::Build not implemented for {}", typeid(*item).name());
    }
  } EndMatch;

  return nullptr;
}
