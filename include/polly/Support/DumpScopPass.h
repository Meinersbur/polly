//===------ DumpScopPass.h --------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Print a SCoP description at -analyze.
//
//===----------------------------------------------------------------------===//

#ifndef POLLY_SUPPORT_DUMPSCOPPASS_H
#define POLLY_SUPPORT_DUMPSCOPPASS_H

namespace llvm {
class RegionPass;
}

namespace polly {
llvm::RegionPass *createDumpScopPass();
} // namespace polly

namespace llvm {
class PassRegistry;
void initializeDumpScopPass(llvm::PassRegistry &);
} // namespace llvm

#endif /* POLLY_SUPPORT_DUMPSCOPPASS_H */
