// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/back/type.hpp"
#include "arrow/log.hpp"
#include "mach7.hpp"

using arrow::back::Type;

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    return handle_##name(std::dynamic_pointer_cast<type>(item))

LLVMTypeRef Type::run(ptr<ir::Type> item) {
  Match(*item) {
    ACCEPT(ir::TypeInteger, int);
    ACCEPT(ir::TypeBoolean, bool);

    Otherwise() {
      Log::get().error("not implemented for {}", typeid(*item).name());
    }
  } EndMatch;

  return nullptr;
}
