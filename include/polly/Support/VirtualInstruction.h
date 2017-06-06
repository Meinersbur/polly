//===------ VirtualInstruction.cpp ------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Tools for determining which instructions are within a statement and the
// nature of their operands.
//
//===----------------------------------------------------------------------===//

#ifndef POLLY_SUPPORT_VIRTUALINSTRUCTION_H
#define POLLY_SUPPORT_VIRTUALINSTRUCTION_H

#include "polly/ScopInfo.h"

namespace polly {

class ScalarDefUseChains {
public:
  int ScalarValueDeps = 0;
  int ScalarValueLoopDeps = 0;
  int ScalarPHIDeps = 0;
  int ScalarPHILoopDeps = 0;

  /// The definitions/write MemoryAccess of an MK_Value scalar.
  ///
  /// Note that read-only values have no value-defining write access.
  DenseMap<const ScopArrayInfo *, MemoryAccess *> ValueDefAccs;

  /// List of all uses/read MemoryAccesses for an MK_Value scalar.
  DenseMap<const ScopArrayInfo *, SmallVector<MemoryAccess *, 4>> ValueUseAccs;

  /// The PHI/read MemoryAccess of an MK_PHI scalar.
  DenseMap<const ScopArrayInfo *, MemoryAccess *> PHIReadAccs;

  /// List of all incoming values/writes of an MK_PHI scalar.
  DenseMap<const ScopArrayInfo *, SmallVector<MemoryAccess *, 4>>
      PHIIncomingAccs;

public:
  /// Find the MemoryAccesses that access the ScopArrayInfo-represented memory.
  void compute(Scop *S);

  void reset();

  MemoryAccess *getValueDef(const ScopArrayInfo *SAI) {
    return ValueDefAccs.lookup(SAI);
  }
  auto getValueUses(const ScopArrayInfo *SAI) -> decltype(ValueUseAccs[SAI]) {
    return ValueUseAccs[SAI];
  }

  MemoryAccess *getPHIRead(const ScopArrayInfo *SAI) {
    return PHIReadAccs.lookup(SAI);
  }
  auto getPHIIncomings(const ScopArrayInfo *SAI)
      -> decltype(PHIIncomingAccs[SAI]) {
    return PHIIncomingAccs[SAI];
  }
};

/// Determine the nature of a value's use within a statement.
///
/// These are not always representable by llvm::Use. For instance, scalar write
/// MemoryAccesses do use a value, but are not associated with an instruction's
/// argument.
///
/// Despite its name it is not tied to virtual instructions (although it works
/// fine with them), but to promote consistent handling of values used in
/// statements.
class VirtualUse {
	friend class VirtualInstruction;
public:
  /// The different types of uses. Handling usually differentiates a lot between
  /// these; one can use a switch to handle each case (and get warned by the
  /// compiler if one is not handled).
  enum UseKind {
    // An llvm::Constant.
    Constant,

    // An llvm::BasicBlock.
    Block,

    // A value that can be generated using ScopExpander.
    Synthesizable,

    // A load that always reads the same value throughout the SCoP (address and
    // the value located there a SCoP-invariant) and has been hoisted in front
    // of the SCoP.
    Hoisted,

    // Definition before the SCoP and not synthesizable. Can be an instruction
    // outside the SCoP, a function argument or a global value. Whether there is
    // a scalar MemoryAccess in this statement for reading it depends on the
    // -polly-analyze-read-only-scalars switch.
    ReadOnly,

    // A definition within the same statement. No MemoryAccess between
    // definition and use are necessary.
    Intra,

    // Definition in another statement. There is a scalar MemoryAccess that
    // makes it available in this statement.
    Inter
  };

private:
  /// The statement where a value is used.
  ScopStmt *User;

  /// The value that is used.
  Value *Val;

  /// The type of value use.
  UseKind Kind;

  /// The value represented as llvm::SCEV expression.
  const SCEV *ScevExpr;

  /// If this is an inter-statement (or read-only) use, contains the
  /// MemoryAccess that makes the value available in this statement. In case of
  /// intra-statement uses, can contain a MemoryKind::Array access. In all other
  /// cases, it is a nullptr.
  MemoryAccess *InputMA;

  VirtualUse(ScopStmt *User, Value *Val, UseKind Kind, const SCEV *ScevExpr,
             MemoryAccess *InputMA)
      : User(User), Val(Val), Kind(Kind), ScevExpr(ScevExpr), InputMA(InputMA) {
  }

public:
  /// Get a VirtualUse for an llvm::Use.
  ///
  /// @param S       The Scop object.
  /// @param U       The llvm::Use the get information for.
  /// @param LI      The LoopInfo analysis. Needed to determine whether the
  ///                value is synthesizable.
  /// @param Virtual Whether to ignore existing MemoryAcccess.
  ///
  /// @return The VirtualUse representing the same use as @p U.
  static VirtualUse create(Scop *S, const Use &U, LoopInfo *LI, bool Virtual);

  /// Get a VirtualUse for any kind of use of a value within a statement.
  ///
  /// @param S         The Scop object.
  /// @param UserStmt  The statement in which @p Val is used. Can be nullptr, in
  ///                  which case it assumed that the statement has been
  ///                  removed, which is only possible if no instruction in it
  ///                  had side-effects or computes a value used by another
  ///                  statement.
  /// @param UserScope Loop scope in which the value is used. Needed to
  ///                  determine whether the value is synthesizable.
  /// @param Val       The value being used.
  /// @param Virtual   Whether to use (and prioritize over instruction location)
  ///                  information about MemoryAccesses.
  ///
  /// @return A VirtualUse object that gives information about @p Val's use in
  ///         @p UserStmt.
  static VirtualUse create(Scop *S, ScopStmt *UserStmt, Loop *UserScope,
                           Value *Val, bool Virtual = true);

  static VirtualUse create(ScopStmt *UserStmt, Loop *UserScope, Value *Val,
                           bool Virtual = true) {
    return create(UserStmt->getParent(), UserStmt, UserScope, Val,
                  Virtual = true);
  }

  bool isConstant() const { return Kind == Constant; }
  bool isBlock() const { return Kind == Block; }
  bool isSynthesizable() const { return Kind == Synthesizable; }
  bool isHoisted() const { return Kind == Hoisted; }
  bool isReadOnly() const { return Kind == ReadOnly; }
  bool isIntra() const { return Kind == Intra; }
  bool isInter() const { return Kind == Inter; }

  /// Return user statement.
  ScopStmt *getUser() const { return User; }

  /// Return the used value.
  llvm::Value *getValue() const { return Val; }

  /// Return the type of use.
  UseKind getKind() const { return Kind; }

  /// Return the ScalarEvolution representation of @p Val.
  const SCEV *getScevExpr() const { return ScevExpr; }

  /// Return the MemoryAccess that makes the value available in this statement,
  /// if any.
  MemoryAccess *getMemoryAccess() const { return InputMA; }

  /// Print a description of this object.
  ///
  /// @param OS           Stream to print to.
  /// @param Reproducible If true, ensures that the output is stable between
  /// runs and is suitable to check in regression tests. This excludes printing
  /// e.g. pointer values.
  ///                     If false, the output should not be used for regression
  ///                     tests, but may contain more information useful in
  ///                     debugger sessions.
  void print(raw_ostream &OS, bool Reproducible = true) const;

#if !defined(NDEBUG) || defined(LLVM_ENABLE_DUMP)
  void dump() const;
#endif
};

MemoryAccess *getOutputAccessFor(Value *OutputVal, ScopStmt *Stmt);

class VirtualInstruction {
private:
  ScopStmt *Stmt = nullptr;
  Instruction *Inst = nullptr;

private:
  MemoryAccess *findOutputAccess(Value *Val) const {
    return getOutputAccessFor(Val, Stmt);
  }

public:
  VirtualInstruction() {}
  VirtualInstruction(ScopStmt *Stmt, Instruction *Inst)
      : Stmt(Stmt), Inst(Inst){};

  Scop *getScop() const { return Stmt->getParent(); }
  ScopStmt *getStmt() const { return Stmt; }
  Instruction *getInstruction() const { return Inst; }

  int getNumOperands() const { return Inst->getNumOperands(); }
  Value *getOperand(unsigned i) const { return Inst->getOperand(i); }

  auto operands() const -> decltype(Inst->operands()) {
    return Inst->operands();
  }

  VirtualUse getVirtualUse(const Use &U, LoopInfo *LI,
                           bool Virtual = true) const {
    assert(U.getUser() == Inst); // TODO: Not true for virtual operand trees
    return VirtualUse::create(Stmt->getParent(), U, LI, Virtual);
    //  return VirtualUse::create(Stmt, U.get(),
    //  LI->getLoopFor(Inst->getParent()), Stmt->getParent()->getSE());
  }

  VirtualUse getIntraVirtualUse(Instruction *Val) const {
	  return VirtualUse::create(Stmt->getParent(), Stmt,Stmt->getSurroundingLoop(),  Val, true);
	 // return VirtualUse(Stmt, Val, VirtualUse::Intra, nullptr, nullptr);
  }

  VirtualUse getVirtualUse(int i, LoopInfo *LI) const {
    return getVirtualUse(Inst->getOperandUse(i), LI);
  }

  void dump() const;
};

static inline bool operator==(VirtualInstruction LHS, VirtualInstruction RHS) {
  return LHS.getStmt() == RHS.getStmt() &&
         LHS.getInstruction() == RHS.getInstruction();
}

void markReachableGlobal(Scop *S, std::vector<VirtualInstruction> &InstList,
                         DenseSet<MemoryAccess *> &UsedMA, LoopInfo *LI);
void markReachableLocal(ScopStmt *Stmt,
                        std::vector<VirtualInstruction> &InstList,
                        LoopInfo *LI);

// void computeStmtInstructions(ScopStmt *Stmt, SmallVectorImpl<Instruction*>
// &InstList) ;

} // namespace polly

namespace llvm {
template <> class DenseMapInfo<polly::VirtualInstruction> {
public:
  static bool isEqual(polly::VirtualInstruction LHS,
                      polly::VirtualInstruction RHS) {
    return DenseMapInfo<polly::ScopStmt *>::isEqual(LHS.getStmt(),
                                                    RHS.getStmt()) &&
           DenseMapInfo<Instruction *>::isEqual(LHS.getInstruction(),
                                                RHS.getInstruction());
  }

  static polly::VirtualInstruction getTombstoneKey() {
    return polly::VirtualInstruction(
        DenseMapInfo<polly::ScopStmt *>::getTombstoneKey(),
        DenseMapInfo<Instruction *>::getTombstoneKey());
  }

  static polly::VirtualInstruction getEmptyKey() {
    return polly::VirtualInstruction(
        DenseMapInfo<polly::ScopStmt *>::getEmptyKey(),
        DenseMapInfo<Instruction *>::getEmptyKey());
  }

  static unsigned getHashValue(polly::VirtualInstruction Val) {
    return DenseMapInfo<std::pair<polly::ScopStmt *, Instruction *>>::
        getHashValue(std::make_pair(Val.getStmt(), Val.getInstruction()));
  }
};
} // namespace llvm

#endif /* POLLY_SUPPORT_VIRTUALINSTRUCTION_H */
