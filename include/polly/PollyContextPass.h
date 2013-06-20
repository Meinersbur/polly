#ifndef POLLY_POLLYCONTEXTPASS_H
#define POLLY_POLLYCONTEXTPASS_H

#include <llvm/Pass.h> // baseclass llvm::ModulePass
#include <llvm/ADT/DenseMap.h> // member llvm::DenseMap
#include <utility>
#include <functional>

struct isl_ctx;


namespace polly {

  class Destructible {
  public:
    virtual ~Destructible() {}
  }; // class Destructible


  /// Pass that remembers stuff between passes
  class PollyContextPass final : public llvm::ModulePass {
  private:
    bool explicitRelease;
    isl_ctx *islctx;

    llvm::DenseMap<const char * /*key*/, Destructible*> attachments;

  public:
    static char ID;
    PollyContextPass();
    PollyContextPass(bool explicitRelease);
    virtual ~PollyContextPass();

    void getAnalysisUsage(llvm::AnalysisUsage &AU) const LLVM_OVERRIDE {
      AU.setPreservesAll();
    }

    void releaseMemory() LLVM_OVERRIDE;
    bool runOnModule(llvm::Module &M) LLVM_OVERRIDE;
    const char *getPassName() const LLVM_OVERRIDE { return "PollyContextPass"; }

    void readyToRelease();
    isl_ctx *getIslCtx() { 
      assert(islctx && "isl_ctx already released???");
      return islctx;
    }

    void addAttachment(const char &key, Destructible *data) {
     assert( attachments.find(&key) == attachments.end());
     attachments[&key] = data;
    }

    Destructible *getAttachment(const char &key) {
      auto it = attachments.find(&key);
      if (it==attachments.end()) {
        return NULL;
      }
      return it->second;
    }
  }; // class PollyContextPass

  extern char &PollyContextPassID;
  llvm::ModulePass *createPollyContextPass(bool explicitRelease = false);


  /// This class is intended to define the point where the isl_ctx is not needed anymore and can be freed
  /// If it is freed before, it means one pass did not AU.addPreserved<PollyContextPass>()
  class PollyContextRelease : public llvm::ModulePass {
  public:
    static char ID;
    PollyContextRelease() : llvm::ModulePass(ID) {}

    const char *getPassName() const LLVM_OVERRIDE { return "PollyContextRelease"; }
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const LLVM_OVERRIDE {
      AU.addRequired<PollyContextPass>(); // Lengthen lifetime of PollyContextPass until this pass
      AU.setPreservesAll();
    }

    bool runOnModule(llvm::Module &M) LLVM_OVERRIDE {
      auto pollyCtx = &getAnalysis<PollyContextPass>();
      pollyCtx -> readyToRelease();
      return false;
    }
  }; // class PollyContextRelease

  extern char &PollyContextReleaseID;
  llvm::ModulePass *createPollyContextRelease();

} // namespace polly
#endif /* POLLY_POLLYCONTEXTPASS_H */
