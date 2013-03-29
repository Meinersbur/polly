#ifndef POLLY_SCOPMEMORY_H
#define POLLY_SCOPMEMORY_H

#include <llvm/Pass.h>
#include <vector>

namespace llvm {
    class BasicBlock;
  class Instruction;
} // namespace llvm

namespace polly {
  class Scop;
} // namespace polly


namespace polly {
  /// ModulePass to store previously determined SCoPs and ensures that code is generated before releasing them if modified. 
  /// Molly has a ModulePass which looks into all SCoPs to see how it accesses a field. TempScopInfo and ScopInfo are RegionPasses so ModulePasses cannot directly query them in the same way ModulePass can access FunctionPasses using getAnalysis<FunctionPass>(F). Additionally, it would be a waste to through these analyses away even though they are not invalidated.
  ///
  /// But the more severe reason is that the Molly code generator will inject code into the SCoPs that cannot easily be back-transformed into SCoPs again. Applying Polly's scheduling algorithms would become impossible.
  class ScopMemory : public llvm::ModulePass {
    private:
      typedef std::vector<Scop*> ScopList;
      ScopList scops;

  public:
    static char ID;
    ScopMemory() : ModulePass(ID) {}

    virtual void getAnalysisUsage(llvm::AnalysisUsage &AU) const override {
      AU.setPreservesAll();
    }

    virtual bool runOnModule(llvm::Module &M) override {
      // Nothing to do; ScopInfo will put its detected Scops in this object
      return false;
    }

    void addScop(polly::Scop *);


    Scop *getScop(llvm::Instruction *);
    Scop *getScop(llvm::BasicBlock *);

  }; // class ScopMemory
} // namespace polly
#endif /* POLLY_SCOPMEMORY_H */
