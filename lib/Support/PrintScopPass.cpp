//===------ DumpScopPass.cpp ------------------------------------*- C++ -*-===//
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

#include "polly/Support/PrintScopPass.h"

#include "polly/ScopInfo.h"

#define DEBUG_TYPE "polly-print-scop"

using namespace llvm;
using namespace polly;

namespace {

class PrintScop : public RegionPass {
private:
  PrintScop(const PrintScop &) = delete;
  const PrintScop &operator=(const PrintScop &) = delete;

  raw_ostream &OS;

public:
  static char ID;

  explicit PrintScop() : RegionPass(ID), OS(dbgs()) {}
  explicit PrintScop(raw_ostream &OS) : RegionPass(ID), OS(OS) {}

  /// @name RegionPass interface
  //@{
  virtual void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.addUsedIfAvailable<ScopInfoRegionPass>();
    AU.setPreservesAll();
  }

  virtual bool runOnRegion(Region *R, RGPassManager &RGM) override {
    ScopInfoRegionPass *SIP = getAnalysisIfAvailable<ScopInfoRegionPass>();
    if (!SIP) {
      OS << "No SCoP analysis for '" << R->getNameStr() << "' in function '"
         << R->getEntry()->getParent()->getName() << "'\n";
      return false;
    }

    Scop *S = SIP->getScop();
    if (!S)
      return false;

    S->print(OS, true);
    OS << '\n';

    return false;
  }

  virtual void print(raw_ostream &OS, const Module *M) const override {}

  StringRef getPassName() const override { return "Print SCoP"; }
  //@}
};

char PrintScop::ID;

class AnalyzeScop : public RegionPass {
private:
  AnalyzeScop(const AnalyzeScop &) = delete;
  const AnalyzeScop &operator=(const AnalyzeScop &) = delete;

  ScopInfoRegionPass *SIP = nullptr;

public:
  static char ID;

  explicit AnalyzeScop() : RegionPass(ID) {}

  /// @name RegionPass interface
  //@{
  virtual void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.addUsedIfAvailable<ScopInfoRegionPass>();
    AU.setPreservesAll();
  }

  virtual bool runOnRegion(Region *R, RGPassManager &RGM) override {
    SIP = getAnalysisIfAvailable<ScopInfoRegionPass>();
    return false;
  }

  virtual void print(raw_ostream &OS, const Module *M) const override {
    if (!SIP) {
      OS << "No SCoP analysis available\n";
      return;
    }

    Scop *S = SIP->getScop();
    if (!S) {
      OS << "Not a SCoP\n";
      return;
    }

    S->print(OS, true);
  }

  StringRef getPassName() const override { return "Analyze SCoP"; }
  //@}
};

char AnalyzeScop::ID;

} // namespace

RegionPass *polly::createPrintScopPass(raw_ostream &OS) {
  return new PrintScop(OS);
}

RegionPass *polly::createAnalyzeScopPass() { return new AnalyzeScop(); }

INITIALIZE_PASS_BEGIN(PrintScop, "polly-print-scop", "Polly - Print SCoP",
                      false, false)
INITIALIZE_PASS_DEPENDENCY(ScopInfoRegionPass)
INITIALIZE_PASS_END(PrintScop, "polly-print-scop", "Polly - Print SCoP", false,
                    false)

INITIALIZE_PASS_BEGIN(AnalyzeScop, "polly-analyze-scop", "Polly - Analyze SCoP",
                      false, false)
INITIALIZE_PASS_DEPENDENCY(ScopInfoRegionPass)
INITIALIZE_PASS_END(AnalyzeScop, "polly-analyze-scop", "Polly - Analyze SCoP",
                    false, false)
