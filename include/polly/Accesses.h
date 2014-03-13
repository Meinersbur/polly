#ifndef MOLLY_ACCESSES_H
#define MOLLY_ACCESSES_H

#include <llvm/IR/IntrinsicInst.h>
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

  public:
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

  }; // class Access


  /// To enumerate all the accesses by an instruction
  class Accesses {
  private:
  protected:
    Accesses() {}
  public:
    static Accesses fromMemoryAccess(polly::MemoryAccess *memacc);
    static Accesses fromInstruction(llvm::Instruction *instr);
  }; // class Accesses

} // namespace polly

#endif /* MOLLY_ACCESSES_H */
