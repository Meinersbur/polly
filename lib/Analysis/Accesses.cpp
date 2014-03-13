#include "polly/Accesses.h"

#include "polly/ScopInfo.h"
#include "polly/TempScopInfo.h"

#include <llvm/IR/IntrinsicInst.h>

using namespace llvm;
using namespace polly;

 Access Access::fromIRAccess(polly::IRAccess *iracc) {
   auto base = iracc->getBase();
   llvm_unreachable("Not yet implemented");
}



Access Access::fromMemoryAccess(polly::MemoryAccess *memacc) {
  assert(memacc->isRead() != memacc->isWrite()); // Only readin or writing
  auto rel = memacc->getAccessRelation();
  auto base = memacc->getBaseAddr();
  auto name = memacc->getBaseName();
  auto instr = const_cast<llvm::Instruction*>(memacc->getAccessInstruction()); // Why is it const?
  bool isReading = memacc->isRead();
  bool isWriting = memacc->isWrite();
  auto isStack = false;
  auto isField = false;

  int ptrOperator;
  if (auto ld = dyn_cast<LoadInst>(instr)) {
    assert(memacc->isRead());
    assert(!memacc->isWrite());
    ptrOperator = ld->getPointerOperandIndex();
    assert(ld->getPointerOperand() == base); // TODO: There might be pointer-arithmetic instructions before
    assert(isReading && !isWriting);
  } else if (auto st = dyn_cast<StoreInst>(instr)) {
    assert(memacc->isWrite()); // No distinction between MAY_READ and MUST_READ yet
    assert(!memacc->isRead());
    ptrOperator = st->getPointerOperandIndex();
    assert(st->getPointerOperand() == base);
    assert(isWriting && !isReading);
  } else if (auto cpy = dyn_cast<MemTransferInst>(instr)) {

    if (memacc->isRead()) {
      ptrOperator = 1;
    }

    if (memacc->isWrite()) {
      ptrOperator = 0;
    }

  } else if (auto call = dyn_cast<CallInst>(instr)) { // TODO: InvokeInst
    // Have to search for which operator is actually meant
    ptrOperator = -1;
    for (auto it = call->op_begin(), end = call->op_end(); it != end; ++it) {
      auto op = it->get();
      if (base == op) {
        assert(ptrOperator==-1 && "Multiple matching accesses found");
        ptrOperator = it->getOperandNo();
      }
    }
    assert(ptrOperator >= 0 && "Access not found");

   assert(isWriting || !call->getAttributes().hasAttribute(ptrOperator+1, Attribute::StructRet));
   assert(isReading || !call->getAttributes().hasAttribute(ptrOperator + 1, Attribute::ByVal));
  }

  // Get the origin of the pointer
  auto ptr = instr->getOperand(ptrOperator)->stripPointerCasts();
  if (auto mollyptr = dyn_cast<MollyPtrInst>(ptr)) {
    isField = true;
  }

  if (auto alloca = dyn_cast<AllocaInst>(ptr)) {
    isStack = true;
  }

  //assert(isField != isStack);

  Access result;
  result.flagRead = isReading;
  result.flagWrite = isWriting;
  result.flagStack = isStack;
  result.flagField = isField;
  result.instr = instr;
  result.ptrOperator = ptrOperator;
  return result; // NRVO
}


Accesses Accesses::fromMemoryAccess(polly::MemoryAccess *memacc) {
  llvm_unreachable("Not yet implemented");
  Accesses result;
  return result; // NRVO
}


Accesses Accesses::fromInstruction(llvm::Instruction *instr) {
  llvm_unreachable("Not yet implemented");
  Accesses result;
  return result; // NRVO
}
