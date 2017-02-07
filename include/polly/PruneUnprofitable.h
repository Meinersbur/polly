//===- PruneUnprofitable.cpp ------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Mark a SCoP as unfeasible if not deemed profitable to optimize.
//
//===----------------------------------------------------------------------===//

#ifndef POLLY_PRUNEUNPROFITABLE_H
#define POLLY_PRUNEUNPROFITABLE_H

namespace llvm {
class PassRegistry;
class Pass;
} // anonymous namespace

namespace polly {
llvm::Pass *createPruneUnprofitablePass();
} // namespace polly

namespace llvm {
void initializePruneUnprofitablePass(llvm::PassRegistry &);
} // namespace llvm

#endif /* POLLY_PRUNEUNPROFITABLE_H */
