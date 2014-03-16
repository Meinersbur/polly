#ifndef MOLLY_ACCESSES_H
#define MOLLY_ACCESSES_H

#include <llvm/IR/IntrinsicInst.h>
#include <llvm/ADT/SmallVector.h>
#include <assert.h>

namespace llvm {
  class Instruction;
} // namespace llvm

namespace polly {
  class MemoryAccess;
  class IRAccess;
} // namespace polly 


namespace polly {

  class MollyPtrInst : public llvm::IntrinsicInst {
  public:

    // Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const IntrinsicInst *I) {
      return I->getIntrinsicID() == llvm::Intrinsic::molly_ptr;
    }
    static inline bool classof(const Value *V) {
      return llvm::isa<llvm::IntrinsicInst>(V) && classof(llvm::cast<llvm::IntrinsicInst>(V));
    }

    llvm::Value *getFieldVar() const {
      return getArgOperand(0);
    }

    unsigned getNumDimensions() const {
      assert(getNumOperands() >= 2);
      return getNumOperands() - 1; // First operand is the field variable
    }

    llvm::Value *getCoordOperand(unsigned d) const {
      return getArgOperand(d + 1);
    }

  }; // class MollyPtrInst


  /// Analyzes accesses to memory
  /// It is meant to generalize and finally replace polly::FieldAccess
  class Access {
  private:
    bool flagRead;
    bool flagWrite;
    bool flagStack;
    bool flagField;

    llvm::Instruction *instr;
    int ptrOperator;

  protected:
    Access() {}
    Access(bool flagRead, bool flagWrite, llvm::Instruction *accessInstr, int ptrOperandIdx, llvm::Value *ptrOperand) 
    : flagRead(flagRead), flagWrite(flagWrite), instr(accessInstr), ptrOperator(ptrOperandIdx) {
      assert(accessInstr);
      assert(0 <= ptrOperandIdx && ptrOperandIdx < accessInstr->getNumOperands());
      analyzePtr(ptrOperand);
    }

    void analyzePtr(llvm::Value *ptr);

  public:
    static Access fromLoadInst(llvm::LoadInst *ld);
    static Access fromStoreInst(llvm::StoreInst *st);
    static Access fromMemcpy(llvm::MemTransferInst *intr, int operand);
    static Access fromMemcpy(llvm::MemTransferInst *intr, bool reading, bool writing);
    static Access fromCall(llvm::CallInst *call, int operand, bool reading, bool writing);
    static Access fromInstruction(llvm::Instruction *instr, int operand, bool reading, bool writing);

    
    static Access fromIRAccess(polly::IRAccess *iracc);
    static Access fromMemoryAccess(polly::MemoryAccess *memacc);
  
    bool isValid() const {return flagRead || flagWrite;}
    bool isRead() const { assert(flagRead != flagWrite); return flagRead; }
    bool isWrite() const{ assert(flagRead != flagWrite);  return flagWrite; }
    bool isStackAccess() const{ assert(flagStack != flagField); return flagStack; }
    bool isFieldAccess()const{ assert(flagStack != flagField); return flagField; }
    bool isRegisterAccess() const { return false; } // Not yet implemented
    bool isGlobalAccess() const { return false; }


    /// The instruction doing the access
    /// Can be: LoadInst, StoreInst, llvm.memcpy, llvm.memmove, CallInst, InvokeInst
    llvm::Instruction * getInstruction() {return instr;}


    /// Returns the pointer value read or written to
    /// This is typically:
    /// - a bitcast
    /// - a llvm.molly.ptr
    /// - GEPInst
    /// - AllocaInst
    llvm::Value *getPtr() const { 
      return instr->getOperand(ptrOperator);
    }


    /// as getPtr(), but removes bitcasts
    /// most useful for scalar stack accesses
    llvm::Value *getTypedPtr() const {
      return getPtr()->stripPointerCasts();
    }


    /// Only valid if isFieldAccess()
    /// Returns the pointer to the field object, usually a GlobalVariable
    llvm::Value *getFieldPtr() const {
      assert(isFieldAccess());

      auto mollyptr = llvm::cast<MollyPtrInst>(getTypedPtr());
      return mollyptr->getFieldVar();
    }


    llvm::Value *getCoordinate(unsigned d) const {
      auto ptr = getTypedPtr();
      if (auto mollyptr = llvm::dyn_cast<MollyPtrInst>(ptr)) {
        return mollyptr->getCoordOperand(d);
      }
      llvm_unreachable("Other cases not yet implemented; Other access can have coordinates too, like C-array subscripts");
    }


    //llvm::Value *getWrittenValue() const;

#pragma region For read accesses
    /// Returns the value that contains the read result
    /// Or null if the result is written to a pointer
    llvm::Value *getReadResultRegister() const {
      assert(isRead());
      return llvm::dyn_cast<llvm::LoadInst>(instr);
    }


    llvm::Value *getReadResultPtr() const {
      assert(isRead());
      if (auto memcpyCall = llvm::dyn_cast<llvm::MemTransferInst>(instr)) {
        return memcpyCall->getDest();
      }
      return nullptr;
    }


    /// Return the memory access that the read result is written to
    /// Only exists if value is not a register; use getRegisterReadResult for this case
    Access getReadResultAccess() const {
      assert(isRead());
      return fromInstruction(instr, ptrOperator, false, true);
    }
#pragma endregion


#pragma region For write accesses
    /// Returns the register that is written to memory
    /// or NULL if the value is taken from a pointer
    llvm::Value *getWrittenValueRegister() const {
      assert(isWrite());
      if (auto st = llvm::dyn_cast<llvm::StoreInst>(instr)) {
        return st->getValueOperand();
      }
      return nullptr;
    }


    llvm::Value *getWrittenValuePtr() const {
      assert(isWrite());
      if (auto memcpyCall = llvm::dyn_cast<llvm::MemTransferInst>(instr)) {
        return memcpyCall->getSource();
      }
      // CallInst doesn't have an explicit value that is written
      return nullptr;
    }


    Access getAccessValueAccess() {
      assert(isWrite());
      return fromInstruction(instr, ptrOperator, true, false);
    }
#pragma endregion
  }; // class Access


  /// To enumerate all the accesses by an instruction
  class Accesses {
  private:
    llvm::SmallVector<Access, 2> accs;

  protected:
    Accesses() {}
  public:
    static Accesses fromMemoryAccess(polly::MemoryAccess *memacc);
    static Accesses fromInstruction(llvm::Instruction *instr);
  }; // class Accesses

} // namespace polly

#endif /* MOLLY_ACCESSES_H */
