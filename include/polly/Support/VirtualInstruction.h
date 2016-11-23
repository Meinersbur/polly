#ifndef POLLY_VIRTUALINSTRUCTION_H
#define POLLY_VIRTUALINSTRUCTION_H

#include "polly/ScopInfo.h"

namespace polly {



	class ScalarDefUseChains {
	private:
		int ScalarValueDeps=0;
		int ScalarValueLoopDeps=0;
		int ScalarPHIDeps=0;
		int ScalarPHILoopDeps=0;

    /// The definitions/write MemoryAccess of an MK_Value scalar.
  ///
  /// Note that read-only values have no value-defining write access.
  DenseMap<const ScopArrayInfo *, MemoryAccess *> ValueDefAccs;

  /// List of all uses/read MemoryAccesses for an MK_Value scalar.
  DenseMap<const ScopArrayInfo *, SmallVector<MemoryAccess *, 4>> ValueUseAccs;

  /// The PHI/read MemoryAccess of an MK_PHI scalar.
  DenseMap<const ScopArrayInfo *, MemoryAccess *> PHIReadAccs;

  /// List of all incoming values/writes of an MK_PHI scalar.
  DenseMap<const ScopArrayInfo *, SmallVector<MemoryAccess *, 4>> PHIIncomingAccs;


	public:
			/// Find the MemoryAccesses that access the ScopArrayInfo-represented memory.
		void compute(Scop *S);

		void reset();

		MemoryAccess *getValueDef(const ScopArrayInfo *SAI)  { return ValueDefAccs.lookup(SAI); }
		auto & getValueUses(const ScopArrayInfo *SAI)  {			return ValueUseAccs[SAI];		}


				MemoryAccess *getPHIRead(const ScopArrayInfo *SAI)  { return PHIReadAccs.lookup(SAI); }
	auto & getPHIIncomings(const ScopArrayInfo *SAI)  {			return PHIIncomingAccs[SAI];		}
	};

	/// If InputVal is not defined in the stmt itself, return the MemoryAccess that
/// reads the scalar. Return nullptr otherwise (if the value is defined in the
/// scop, or is synthesizable)
	MemoryAccess *getInputAccessOf(Value *InputVal, ScopStmt *Stmt, bool AllowArrayLoads);

	MemoryAccess *getOutputAccessFor(Value *OutputVal, ScopStmt *Stmt);

class VirtualInstruction {
private:
	ScopStmt *Stmt=nullptr;
	Instruction *Inst=nullptr;

public:
	MemoryAccess *findInputAccess(Value *Val , bool AllowLoad)const {
		return getInputAccessOf(Val, Stmt, AllowLoad);
	}

private:
	MemoryAccess *findOutputAccess(Value *Val )const {
		return getOutputAccessFor(Val, Stmt);
	}

public:
	VirtualInstruction() {}
	VirtualInstruction(ScopStmt *Stmt, Instruction *Inst) : Stmt(Stmt), Inst(Inst){};

	Scop *getScop() const {return Stmt->getParent(); }
	ScopStmt *getStmt() const {return Stmt;}
	Instruction*getInstruction() const {return Inst;}

	int getNumOperands() const { return Inst->getNumOperands(); }
	Value *getOperand(unsigned i) const { return Inst->getOperand(i);}

	auto operands() const {return  Inst->operands();   }

	bool isVirtualOperand(const Use &U) const {
		assert(U.getUser() == Inst);
		auto Op = U.get();

		if (isa<Constant>(Op))
			return false;

			auto S = getScop();
			return ! canSynthesize(Op,  *S, S->getSE() , Stmt->getSurroundingLoop() );
	}

	bool isInterScopOperand(const Use &U) const{
		assert(U.getUser() == Inst);
		auto Op = U.get();
		if (isa<Constant>(Op))
			return false;
		return findInputAccess(Op, false);
	}

	bool isIntraOperand(const Use &U) const {
		return isVirtualOperand(U) && !isInterScopOperand(U);
	}

	VirtualInstruction getIntraOperand(const Use &U ) const {
		assert(isIntraOperand(U));
		return {Stmt, cast<Instruction >(U.get()) };
	}

	VirtualInstruction getInterOperand(const Use &U ) const {
		assert(isInterScopOperand(U));
		auto OpInst= cast<Instruction>(U.get());
		auto S = Stmt->getParent()->getStmtFor(OpInst);
		assert(S);
		return { S, OpInst };
	}

	VirtualInstruction getVirtualOperand(const Use &U) const{
	if (isInterScopOperand(U))
		return getInterOperand(U);
	return getIntraOperand(U);
	}

	MemoryAccess *getInterOperandInput(const Use &U ) const {
		auto MA = findInputAccess(U.get(), false);
		assert(MA && "Must be an inter-Stmt use");
		return MA;
	}

		MemoryAccess *getInterOperandOutput() const {
			return findOutputAccess(Inst);
	}
};


void computeStmtInstructions(ScopStmt *Stmt, SmallVectorImpl<Instruction*> &InstList) ;


} // namespace polly

namespace llvm {
	template<>
	class DenseMapInfo<polly::VirtualInstruction> {
	public:
		static bool isEqual (  polly::VirtualInstruction LHS,  polly::VirtualInstruction RHS ) {
			return  DenseMapInfo<polly::ScopStmt*>::isEqual( LHS.getStmt(),RHS.getStmt()) && DenseMapInfo<Instruction*>::isEqual( LHS.getInstruction(),RHS.getInstruction()) ;
		}

		static polly::VirtualInstruction getTombstoneKey() {
		return polly::VirtualInstruction( DenseMapInfo<polly::ScopStmt*>::getTombstoneKey(), DenseMapInfo<Instruction*>::getTombstoneKey() );
		}

			static polly:: VirtualInstruction getEmptyKey() {
		return polly::VirtualInstruction( DenseMapInfo<polly::ScopStmt*>::getEmptyKey(), DenseMapInfo<Instruction*>::getEmptyKey() );
		}

		static unsigned getHashValue(polly::VirtualInstruction Val) {
			return DenseMapInfo<std::pair< polly::ScopStmt*,Instruction* >>::getHashValue( std::make_pair( Val.getStmt( ), Val.getInstruction()));
		}
	};
}

#endif /* POLLY_VIRTUALINSTRUCTION_H */
