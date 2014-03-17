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


void Access::analyzePtr(llvm::Value *ptr) {
  assert(ptr);
  auto typedPtr = ptr->stripPointerCasts();

  this->flagField = false;
  this->flagStack = false;
  if (auto mollyPtr = dyn_cast<MollyPtrInst>(typedPtr)) {
    this->flagField = true;
  } else if (auto alloca = dyn_cast<AllocaInst>(typedPtr)) {
    this->flagStack = true;
  }
}


Access Access::fromLoadInst(llvm::LoadInst *ld) {
  assert(ld);
  return Access(true, false, ld, ld->getPointerOperandIndex(), ld->getPointerOperand());
}


Access Access::fromStoreInst(llvm::StoreInst *st) {
  assert(st);
  return Access(false, true, st, st->getPointerOperandIndex(), st->getPointerOperand());
}


Access Access::fromMemcpy(llvm::MemTransferInst *intr, int operand) {
  switch (operand) {
  case 0:
    return fromMemcpy(intr, false, true);
  case 1:
    return fromMemcpy(intr, true, false);
  default:
    llvm_unreachable("Non-valid operand for memcpy");
  }
}


Access Access::fromMemcpy(llvm::MemTransferInst *intr, bool reading, bool writing) {
  if (writing && !reading)
    return Access(reading, writing, intr, 0, intr->getRawDest());
  else if (reading && !writing)
    return Access(reading, writing, intr, 1, intr->getRawSource());
  llvm_unreachable("An access is either reading or writing, but currently not both (use two Access for byref args)");
}


Access Access::fromCall(llvm::CallInst *call, int operand, bool reading, bool writing) {
  assert(reading != writing);

  if (auto memcpyCall = dyn_cast<MemTransferInst>(call)) {
    if ((operand == 0 && writing) || (operand == 1 && reading))
      return fromMemcpy(memcpyCall, operand);
    return Access();
  }

#ifndef NDEBUG
  if (call->getAttributes().hasAttribute(operand + 1, Attribute::StructRet)) {
    assert(reading);
  }

  if (call->getAttributes().hasAttribute(operand + 1, Attribute::ByVal)) {
    assert(writing);
  }
#endif

  return Access(reading, writing, call, operand, call->getArgOperand(operand));
}


Access Access::fromInstruction(llvm::Instruction *instr, int operand, bool reading, bool writing) {
  assert(reading != writing);

  switch (instr->getOpcode()) {
  case Instruction::Load:
    if (writing)
      return Access();
    if (operand != LoadInst::getPointerOperandIndex())
      return Access();
    return fromLoadInst(cast<LoadInst>(instr));
  case Instruction::Store:
    if (reading)
      return Access();
    if (operand != StoreInst::getPointerOperandIndex());
    return Access();
    return fromStoreInst(cast<StoreInst>(instr));
  case Instruction::Call:
    return fromCall(cast<CallInst>(instr), operand, reading, writing);
  default:
    return Access();
  }
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
        assert(ptrOperator == -1 && "Multiple matching accesses found");
        ptrOperator = it->getOperandNo();
      }
    }
    assert(ptrOperator >= 0 && "Access not found");

    assert(isWriting || !call->getAttributes().hasAttribute(ptrOperator + 1, Attribute::StructRet));
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

#if 0
llvm::Value * polly::Access::getWrittenValue() const {
  assert(isWrite());
  if (auto st = llvm::dyn_cast<StoreInst>(instr)) {
    return st->getValueOperand();
  }
  if (auto mcpy = llvm::dyn_cast<MemTransferInst>(instr)) {
    // In contrast to StoreInst, there is only a pointer to the source data
    // Is this really what the caller expects?
    return mcpy->getArgOperand(0);
  }
  llvm_unreachable("Not supported yet");
}
#endif

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
