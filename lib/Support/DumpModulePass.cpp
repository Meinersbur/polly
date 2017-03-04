#include "polly/DumpModulePass.h"

#include "llvm/IR/LegacyPassManagers.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/ToolOutputFile.h"
#include "polly/Options.h"
#include <string.h>

using namespace llvm;
using namespace polly;

namespace {

cl::opt<std::string  > DumpFile( "polly-dump-file",                       cl::desc("File to dump to"),                        cl::Optional, cl::cat(PollyCategory) );
 
class DumpModule : public ModulePass {
private:
  DumpModule(const DumpModule &) = delete;
  const DumpModule &operator=(const DumpModule &) = delete;

  std::string Appendix;

public:
  static char ID;
  explicit DumpModule() : ModulePass(ID), Appendix() {
    llvm::errs() << "Creating dumper\n";
  }
  explicit DumpModule(llvm::StringRef Appendix)
      : ModulePass(ID), Appendix(Appendix) {
    llvm::errs() << "Creating " << Appendix << " dumper\n";
  }

  /// @name ModulePass interface
  //@{
  virtual void getAnalysisUsage(llvm::AnalysisUsage &AU) const override {
    AU.setPreservesAll();
  }

  virtual bool runOnModule(llvm::Module &M) override {
    auto Name = M.getName();
    auto stem = sys::path::stem(Name);
    std::string OutputFilename =   DumpFile.getValue().empty() ?       (Twine(stem) + Appendix + ".ll").str() : DumpFile;

    std::unique_ptr<tool_output_file> Out;
    std::error_code EC;
    Out.reset(new tool_output_file(OutputFilename, EC, sys::fs::F_None));
    if (EC) {
      errs() << EC.message() << '\n';
      llvm_unreachable("Unexpected out");
    }
    llvm::errs() << "Dumping module to " << OutputFilename << "\n";
    M.print(Out->os(), nullptr);
    Out->keep();
    return false;
  }
  //@}
};

char DumpModule::ID;
}

ModulePass *polly::createDumpModulePass(llvm::StringRef Appendix) {
  return new DumpModule(Appendix);
}

INITIALIZE_PASS_BEGIN(DumpModule, "polly-dump-module", "Polly - Dump Module",
                      false, false)
INITIALIZE_PASS_END(DumpModule, "polly-dump-module", "Polly - Dump Module",
                    false, false)
