#ifndef POLLY_DUMPMODULEPASS_H
#define POLLY_DUMPMODULEPASS_H

#include "llvm/ADT/StringRef.h"

namespace llvm {
class ModulePass;
}

namespace polly {
llvm::ModulePass *createDumpModulePass(llvm::StringRef Appendix);
}

namespace llvm {
class PassRegistry;
void initializeDumpModulePass(llvm::PassRegistry &);
} // namespace llvm

#endif /* POLLY_DUMPMODULEPASS_H */
