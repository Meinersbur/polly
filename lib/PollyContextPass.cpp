#if 0
#define DEBUG_TYPE "polly"
#include "polly/PollyContextPass.h"

#include <llvm/Support/Debug.h>
#include <llvm/Support/raw_ostream.h>
#include <isl/ctx.h>
#include <isl/options.h>
#include <llvm/Pass.h>

using namespace llvm;
using namespace polly;


PollyContextPass::PollyContextPass() : llvm::ModulePass(ID), islctx(nullptr), explicitRelease(false) {
}


PollyContextPass::PollyContextPass(bool explicitRelease) : llvm::ModulePass(ID), islctx(nullptr), explicitRelease(explicitRelease) {
}


PollyContextPass::~PollyContextPass() {
  assert((!explicitRelease || !islctx) && "Premature freeing of PollyContextPass");
  readyToRelease();
}


void PollyContextPass::releaseMemory() {
  assert((!explicitRelease || !islctx) && "Premature release of PollyContextPass");
  readyToRelease();
}


bool PollyContextPass::runOnModule(llvm::Module &M)  {
  DEBUG(llvm::dbgs() << ">>> Creating a isl_ctx\n");
  islctx = isl_ctx_alloc();
   isl_options_set_on_error(islctx, ISL_ON_ERROR_ABORT);
  return false;
}


void PollyContextPass::readyToRelease() {
  if (!islctx)
    return;

  DEBUG(if (islctx) llvm::dbgs() << "<<< Releasing a isl_ctx\n");
  isl_ctx_free(islctx);
  islctx = nullptr;

  for (auto it = attachments.begin(),end=attachments.end();it!=end; ++it) {
    auto attachement = it->second;
    delete attachement;
  }
  attachments.clear();
}


char polly::PollyContextPass::ID = 0;
char &polly::PollyContextPassID = PollyContextPass::ID;
static RegisterPass<PollyContextPass> PollyContextPassRegistration("polly-context", "Molly - Polly context");
llvm::ModulePass *polly::createPollyContextPass(bool explicitRelease) {
  return new PollyContextPass(explicitRelease);
}


char polly::PollyContextRelease::ID = 0;
char &polly::PollyContextReleaseID = PollyContextRelease::ID;
llvm::ModulePass *polly::createPollyContextRelease() {
  return new PollyContextRelease();
}
#endif
