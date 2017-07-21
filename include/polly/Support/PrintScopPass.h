//===------ PrintScopPass.h --------------------------------------*- C++
//-*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Print a SCoP description.
//
//===----------------------------------------------------------------------===//

#ifndef POLLY_SUPPORT_PRINTSCOPPASS_H
#define POLLY_SUPPORT_PRINTSCOPPASS_H

namespace llvm {
class raw_ostream;
class RegionPass;
} // namespace llvm

namespace polly {
llvm::RegionPass *createPrintScopPass(llvm::raw_ostream &OS);
llvm::RegionPass *createAnalyzeScopPass();
} // namespace polly

namespace llvm {
class PassRegistry;
void initializePrintScopPass(llvm::PassRegistry &);
void initializeAnalyzeScopPass(llvm::PassRegistry &);
} // namespace llvm

#endif /* POLLY_SUPPORT_PRINTSCOPPASS_H */
