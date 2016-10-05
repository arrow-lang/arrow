// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::TypeFunction;
using arrow::ir::TypeExternFunction;

LLVMTypeRef TypeFunction::handle(GContext& ctx) noexcept {
  // Nil result type => void
  LLVMTypeRef result_type_handle = LLVMVoidType();
  if (result) result_type_handle = result->handle(ctx);

  std::vector<LLVMTypeRef> param_type_handles;
  for (auto& param : parameters) {
    // Parameters can have unit type but do not materialize
    // if (param && param->is_unit()) continue;
    if (!param->is_unit()) {
      param_type_handles.push_back(param->handle(ctx));
    }
  }

  return LLVMFunctionType(
    result_type_handle,
    param_type_handles.data(),
    param_type_handles.size(),
    false);
}

LLVMTypeRef TypeExternFunction::handle(GContext& ctx) noexcept {
  // Nil result type => void
  LLVMTypeRef result_type_handle = LLVMVoidType();
  if (result) result_type_handle = result->handle(ctx);

  std::vector<LLVMTypeRef> param_type_handles;
  param_type_handles.reserve(parameters.size());
  for (auto& param : parameters) {
    param_type_handles.push_back(param->handle(ctx));
  }

  return LLVMFunctionType(
    result_type_handle,
    param_type_handles.data(),
    param_type_handles.size(),
    is_varidac);
}
