// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_PASS_GENERATE_H
#define ARROW_PASS_GENERATE_H

#include "arrow/ptr.hpp"
#include "arrow/ir.hpp"
#include "llvm.hpp"

namespace arrow {

// Takes IR as input and will "generate" LLVM IR
class Generator {
 public:
  Generator();

  Generator(const Generator&) = delete;
  Generator(Generator&&) = delete;

  Generator& operator=(const Generator&) = delete;
  Generator& operator=(Generator&&) = delete;

  virtual ~Generator() noexcept;

  Generator& run(ptr<ir::Module> module);
  Generator& print();

 private:
  void initialize();

  // Declare
  void declare(ptr<ir::Item>);
  void declare_variable(ptr<ir::Variable>);

  // Type
  LLVMTypeRef type(ptr<ir::Type>);
  LLVMTypeRef type_int(ptr<ir::TypeInteger>);
  LLVMTypeRef type_bool(ptr<ir::TypeBoolean>);

  // LLVM module context
  LLVMModuleRef _mod;

  // LLVM instruction builder
  // Simplifies IR generation with LLVM
  LLVMBuilderRef _irb;

  // LLVM target machine
  // Describes the target architecture
  LLVMTargetMachineRef _target;
};

}  // namespace arrow

#endif  // ARROW_PASS_GENERATE_H
