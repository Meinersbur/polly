#ifndef POLLY_CODEGENCLEANUP_H
#define POLLY_CODEGENCLEANUP_H

namespace llvm {
class FunctionPass;
class PassRegistry;
namespace legacy {
class PassManagerBase;
}
} // namespace llvm

namespace polly {
llvm::FunctionPass *createCodegenCleanupPass();

void addCleanupPasses(llvm::legacy::PassManagerBase &PM);
} // namespace polly

namespace llvm {
void initializeCodegenCleanupPass(llvm::PassRegistry &);
} // namespace llvm

#endif
