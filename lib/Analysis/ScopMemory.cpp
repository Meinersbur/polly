#include "polly/ScopMemory.h"

#include <llvm/IR/Instruction.h>

using namespace polly;
using namespace llvm;

void ScopMemory::addScop(polly::Scop *) {
}


Scop *ScopMemory::getScop(llvm::Instruction *instr) {
  return getScop(instr->getParent());
}
Scop *ScopMemory::getScop(llvm::BasicBlock *) {
  return NULL;
}

char ScopMemory::ID;
static RegisterPass<ScopMemory> ScopMemoryRegistration("molly-scopmemory", "molly - SCoP memory", false, true);
