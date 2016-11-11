// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::TypeRecord;

LLVMTypeRef TypeRecord::handle(GContext& ctx) noexcept {
  if (!_handle) {
    // Create initial, opaque definition
    _handle = LLVMStructCreateNamed(LLVMGetGlobalContext(), name.c_str());

    // Enumerate members ..
    std::vector<LLVMTypeRef> member_handles;
    for (auto member : members) {
      member_handles.push_back(member->handle(ctx));
    }

    // Set body of record
    LLVMStructSetBody(_handle,
      member_handles.data(), member_handles.size(), false);
  }

  return _handle;
}
