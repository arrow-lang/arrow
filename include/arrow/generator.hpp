// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_PASS_GENERATE_H
#define ARROW_PASS_GENERATE_H

#include <stack>

#include "arrow/ptr.hpp"
#include "arrow/ir.hpp"
#include "llvm.hpp"
#include "fmt.hpp"

namespace arrow {

// Generation context.
struct GContext {
  // LLVM module context
  LLVMModuleRef mod;

  // LLVM instruction builder
  // Simplifies IR generation with LLVM
  LLVMBuilderRef irb;

  // LLVM target machine
  // Describes the target architecture
  LLVMTargetMachineRef target;
  LLVMTargetDataRef target_data;

  // Platform/Machine Integer Size (bits)
  unsigned target_int_size;

  // Scope
  ptr<ir::Scope> scope;

  // Function stack – which function are we currently processing
  std::stack<ir::Function*> function_s;

  // Module stack – which module are we currently processing
  std::stack<ptr<ir::Module>> module_s;

  // Module Pathname Cache
  std::unordered_map<std::string, ptr<ir::Module>> modules_by_pathname;

  // Modules
  std::vector<ptr<ir::Module>> modules;

  // Loop Frame Stack (<condition>, <merge>)
  std::stack<std::pair<LLVMBasicBlockRef, LLVMBasicBlockRef>> loop_s;

  // Implementation Registry
  std::unordered_map<ir::Type*, std::vector<ptr<ir::Implement>>> impl;

  // Generic Implementation Registry
  std::vector<ptr<ir::GenericImplement>> impl_g;

  // Namespace
  std::deque<std::string> ns;
};

// Takes IR as input and will "generate" LLVM IR
class Generator {
 public:
  Generator();

  Generator(const Generator&) = delete;
  Generator(Generator&&) = delete;

  Generator& operator=(const Generator&) = delete;
  Generator& operator=(Generator&&) = delete;

  virtual ~Generator() noexcept;

  Generator& run(ptr<ast::Module> module);
  Generator& print();

 private:
  GContext _ctx;

  void initialize();
};

}  // namespace arrow

#endif  // ARROW_PASS_GENERATE_H
