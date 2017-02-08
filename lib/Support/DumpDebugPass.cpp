#include "polly/DumpDebugPass.h"

#include "llvm/IR/LegacyPassManagers.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/circular_raw_ostream.h"
#include <string.h>

using namespace llvm;
using namespace polly;

namespace {

class DumpDebug : public ModulePass {
private:
  DumpDebug(const DumpDebug &) = delete;
  const DumpDebug &operator=(const DumpDebug &) = delete;

  std::string Appendix;

public:
  static char ID;
  explicit DumpDebug() : ModulePass(ID), Appendix() {}

  /// @name ModulePass interface
  //@{
  virtual void getAnalysisUsage(llvm::AnalysisUsage &AU) const override {
    AU.setPreservesAll();
  }

  virtual bool runOnModule(llvm::Module &M) override {
    auto Name = M.getName();
    auto stem = sys::path::stem(Name);
    std::string DbgFilename = (Twine(stem) + ".log").str();
    errs() << "Dumping DEBUG to " << DbgFilename << "\n";

    std::error_code EC;
    auto &Dbgout = static_cast<circular_raw_ostream &>(dbgs());
    Dbgout.setStream(*(new raw_fd_ostream(DbgFilename, EC, sys::fs::F_None)),
                     true);
    if (EC) {
      errs() << EC.message() << '\n';
      llvm_unreachable("Unexpected errorcode");
    }

    return false;
  }
  //@}
};

char DumpDebug::ID;
}

ModulePass *polly::createDumpDebugPass() { return new DumpDebug(); }

INITIALIZE_PASS_BEGIN(DumpDebug, "polly-dump-debug", "Polly - Dump Debug",
                      false, false)
INITIALIZE_PASS_END(DumpDebug, "polly-dump-debug", "Polly - Dump Debug", false,
                    false)
