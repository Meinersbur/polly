//===------ DeLICM.h --------------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Undo the effect of Loop Invariant Code Motion (LICM) and
// GVN Partial Redundancy Elimination (PRE) on SCoP-level.
//
// Namely, remove register/scalar dependencies by mapping them back to array
// elements.
//
//===----------------------------------------------------------------------===//

#ifndef POLLY_SIMPLIFY_H
#define POLLY_SIMPLIFY_H
namespace llvm {
class PassRegistry;
class Pass;
} // anonymous namespace
namespace polly {
llvm::Pass *createSimplifyPass();
} // namespace polly
namespace llvm {
void initializeSimplifyPass(llvm::PassRegistry &);
} // namespace llvm
#endif /* POLLY_SIMPLIFY_H */
