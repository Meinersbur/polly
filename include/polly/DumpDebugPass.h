#ifndef POLLY_DUMPDEBUGPASS_H
#define POLLY_DUMPDEBUGPASS_H

namespace llvm {
class ModulePass;
}

namespace polly {
llvm::ModulePass *createDumpDebugPass();
}

namespace llvm {
class PassRegistry;
void initializeDumpDebugPass(llvm::PassRegistry &);
} // namespace llvm

#endif /* POLLY_DUMPDEBUGPASS_H */
