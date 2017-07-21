//===------ DumpScopPass.cpp ------------------------------------*- C++ -*-===//
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

#include "polly/Support/DumpScopPass.h"

#include "polly/ScopInfo.h"

#define DEBUG_TYPE "polly-dump-scop"

using namespace llvm;
using namespace polly;

namespace {

class DumpScop : public RegionPass {
private:
  DumpScop(const DumpScop &) = delete;
  const DumpScop &operator=(const DumpScop &) = delete;

  ScopInfoRegionPass *ScopInfoPass = nullptr;

public:
  static char ID;

  explicit DumpScop() : RegionPass(ID) {}

  /// @name RegionPass interface
  //@{
  virtual void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.addUsedIfAvailable<ScopInfoRegionPass>();
    AU.setPreservesAll();
  }

  virtual bool runOnRegion(Region *R, RGPassManager &RGM) override {
    ScopInfoPass = getAnalysisIfAvailable<ScopInfoRegionPass>();
    return false;
  }

  virtual void print(raw_ostream &OS, const Module *M) const override {
    if (!ScopInfoPass) {
      OS << "ScopInfo analysis not available\n";
      return;
    }

    Scop *S = ScopInfoPass->getScop();
    if (!S) {
      OS << "Not a SCoP\n";
      return;
    }

    S->print(OS, true);
  }
  //@}
};

char DumpScop::ID;
} // namespace

RegionPass *polly::createDumpScopPass() { return new DumpScop(); }

INITIALIZE_PASS_BEGIN(DumpScop, "polly-dump-scop", "Polly - Dump SCoP", false,
                      false)
INITIALIZE_PASS_DEPENDENCY(ScopInfoRegionPass)
INITIALIZE_PASS_END(DumpScop, "polly-dump-scop", "Polly - Dump SCoP", false,
                    false)
