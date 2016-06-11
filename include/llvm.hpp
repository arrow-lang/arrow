// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_LLVM_H
#define ARROW_LLVM_H

// HACK: llvm.hpp must be included BEFORE mach7.hpp because of madness
#ifdef ARROW_MACH7_H
#error "llvm.hpp must be included BEFORE mach7.hpp (because madness)"
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

#include "llvm-c/Core.h"
#include "llvm-c/Target.h"
#include "llvm-c/ExecutionEngine.h"
#include "llvm-c/TargetMachine.h"
#include "llvm-c/Analysis.h"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/Interpreter.h"

#pragma GCC diagnostic pop

#endif  // ARROW_LLVM_H
