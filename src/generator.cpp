// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#include "cppformat/format.h"
#include "mach7.hpp"

#include "arrow/generator.hpp"
#include "llvm.hpp"

using arrow::Generator;

Generator::Generator()
  : _mod(nullptr),
    _irb(nullptr),
    _target(nullptr) {
  initialize();
}

Generator::~Generator() noexcept {
  // Dispose of the LLVM module
  if (_mod) LLVMDisposeModule(_mod);

  // Dispose of the instruction builder
  if (_irb) LLVMDisposeBuilder(_irb);

  // Dispose of the target machine
  if (_target) LLVMDisposeTargetMachine(_target);
}

void Generator::initialize() {
  // LLVM: Initialize target and printer
  LLVMInitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();

  // LLVM: Construct instruction builder
  _irb = LLVMCreateBuilder();

  // Discern the triple for our target machine.
  // TODO(mehcode): Allow client to specify architecture here
  auto triple = LLVMGetDefaultTargetTriple();
  LLVMTargetRef target = nullptr;
  char* error = nullptr;
  if (LLVMGetTargetFromTriple(triple, &target, &error) != 0) {
    // Failed to get a valid target; shouldn't be able to happen
    // TODO(mehcode): error message of some kind
    return;
  }

  // Construct the target machine
  _target = LLVMCreateTargetMachine(
    target, triple, "", "",
    LLVMCodeGenLevelDefault,
    LLVMRelocDefault,
    LLVMCodeModelDefault);

  LLVMDisposeMessage(triple);
}

// TODO(mehcode): How do imports work with regards to ir::Module and LLVMModule
Generator& Generator::run(ptr<ir::Module> module) {
  // LLVM: Construct module context
  _mod = LLVMModuleCreateWithName(module->name.c_str());

  // Set the target on the module
  auto triple = LLVMGetTargetMachineTriple(_target);
  LLVMSetTarget(_mod, triple);
  LLVMDisposeMessage(triple);

  // Set the data layout on the module
  auto data = LLVMCopyStringRepOfTargetData(LLVMGetTargetMachineData(_target));
  LLVMSetDataLayout(_mod, data);
  LLVMDisposeMessage(data);

  // 1 - Iterate over each item in the IR module.
  //   * Declare the global variable/function/type/etc.
  for (auto& item : module->items) declare(item.second);

  return *this;
}

Generator& Generator::print() {
  auto bytes = LLVMPrintModuleToString(_mod);
  fmt::print("{}\n", bytes);
  LLVMDisposeMessage(bytes);

  return *this;
}

// Declare
// TODO(mehcode): This should probably be moved out when it gets bigger
// ----------------------------------------------------------------------------|

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    return declare_##name(std::dynamic_pointer_cast<type>(item))

void Generator::declare(ptr<ir::Item> item) {
  Match(*item) {
    ACCEPT(ir::Variable, variable);
  } EndMatch;
}

#undef ACCEPT

void Generator::declare_variable(ptr<ir::Variable> item) {
  LLVMAddGlobal(_mod, type(item->type), item->name.c_str());
}

// Type
// TODO(mehcode): This should probably be moved out when it gets bigger
// ----------------------------------------------------------------------------|

#define ACCEPT(type, name) \
  Case(mch::C<type>()) \
    return type_##name(std::dynamic_pointer_cast<type>(type_))

LLVMTypeRef Generator::type(ptr<ir::Type> type_) {
  Match(*type_) {
    ACCEPT(ir::TypeInteger, int);
    ACCEPT(ir::TypeBoolean, bool);
  } EndMatch;

  return nullptr;
}

#undef ACCEPT

LLVMTypeRef Generator::type_int(ptr<ir::TypeInteger> type) {
  return LLVMIntType(type->bits);
}

LLVMTypeRef Generator::type_bool(ptr<ir::TypeBoolean>) {
  return LLVMInt1Type();
}
