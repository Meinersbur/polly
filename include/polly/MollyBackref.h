//===----------------------------------------------------------------------===//
//
// Contains linker references to Molly, if it is linked into
// Polly passes need to know this so its passes can preserve MollyPasses
// Alternatively, one needs to modify the PassManager, which is ugly to do and will be rewritten in the near future anyway
//
//===----------------------------------------------------------------------===//

#ifndef POLLY_MOLLYBACKREF_H
#define POLLY_MOLLYBACKREF_H

#ifdef MOLLY
#include <llvm/Support/Compiler.h>

namespace molly {
  extern const char &MollyContextPassID LLVM_ATTRIBUTE_WEAK;
  extern const char &FieldDetectionAnalysisPassID LLVM_ATTRIBUTE_WEAK;
} // namespace molly
#endif
#endif /* POLLY_MOLLYBACKREF_H */
