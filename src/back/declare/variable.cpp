// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/back/declare.hpp"
#include "arrow/back/type.hpp"

using arrow::back::Declare;
using arrow::back::Type;

void Declare::handle_variable(ptr<ir::Variable> item) {
  // TODO(mehcode): Local variables?
  // Add global variable to module
  LLVMAddGlobal(_ctx.mod, Type(_ctx).run(item->type), item->name.c_str());
}
