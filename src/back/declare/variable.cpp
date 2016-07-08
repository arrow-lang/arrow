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
  auto type_handle = Type(_ctx).run(item->type);
  auto handle = LLVMAddGlobal(_ctx.mod, type_handle, item->name.c_str());
  _ctx.set_handle(item, handle);

  // Initialize to nil (for globals)
  LLVMSetInitializer(handle, LLVMConstNull(type_handle));

  // Set linkage to private
  LLVMSetLinkage(handle, LLVMLinkerPrivateLinkage);
}
