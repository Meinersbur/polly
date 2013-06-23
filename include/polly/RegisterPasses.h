//===------ polly/RegisterPasses.h - Register the Polly passes *- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Functions to register the Polly passes in a LLVM pass manager.
//
//===----------------------------------------------------------------------===//

#ifndef POLLY_REGISTER_PASSES_H
#define POLLY_REGISTER_PASSES_H

#include <llvm/Support/CommandLine.h>

namespace llvm { 
  class PassManagerBase; 
}

enum OptimizerChoice {
  OPTIMIZER_NONE,
#ifdef PLUTO_FOUND
  OPTIMIZER_PLUTO,
#endif
#ifdef SCOPLIB_FOUND
  OPTIMIZER_POCC,
#endif
  OPTIMIZER_ISL
};

enum CodeGenChoice {
#ifdef CLOOG_FOUND
  CODEGEN_CLOOG,
#endif
  CODEGEN_ISL,
  CODEGEN_NONE
};

extern llvm::cl::opt<OptimizerChoice> Optimizer;
extern llvm::cl::opt<CodeGenChoice> CodeGenerator;

#endif
