// Copyright (c) 2014-2015 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "arrow/ir.hpp"
#include "arrow/generator.hpp"

using arrow::ir::Integer;

LLVMValueRef Integer::handle(GContext& ctx) noexcept {
  LLVMTypeRef type_handle;
  bool is_signed;
  if (type) {
    type_handle = type->handle(ctx);
    is_signed = cast<TypeInteger>(type)->is_signed;
  } else {

    // It shouldn't be possible to not know the exact type
    // of an integer literal at code generation time.
    // However, right now, there is no type inference so this is very
    // possible.
    // TODO: Figure out a solution for integer literals

    type_handle = LLVMIntType(64);
    is_signed = true;

    // auto bitsize = mpz_sizeinbase(value.get_mpz_t(), 2);
    // type_handle = LLVMIntType(bitsize);
    // is_signed = false;
  }

  return LLVMConstInt(type_handle, value.get_ui(), is_signed);
}
