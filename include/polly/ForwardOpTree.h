//===------ ForwardOpTree.h -------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Move instructions between statements.
//
//===----------------------------------------------------------------------===//

#ifndef POLLY_FORWARDOPTREE_H
#define POLLY_FORWARDOPTREE_H

#include "isl-noexceptions.h"
#include <memory>

namespace llvm {
class Value;
class Loop;
class LoopInfo;
} // namespace llvm

namespace polly {
class Scop;
class ScopPass;
class ScopStmt;

/// The state of whether an operand tree was/can be forwarded.
///
/// The items apply to an instructions and its operand tree with the instruction
/// as the root element. If the value in question is not an instruction in the
/// SCoP, it can be a leaf of an instruction's operand tree.
enum ForwardingDecision {
  /// The root instruction or value cannot be forwarded at all.
  FD_CannotForward,

  /// The root instruction or value can be forwarded as a leaf of a larger
  /// operand tree.
  /// It does not make sense to move the value itself, it would just replace it
  /// by a use of itself. For instance, a constant "5" used in a statement can
  /// be forwarded, but it would just replace it by the same constant "5".
  /// However, it makes sense to move as an operand of
  ///
  ///   %add = add 5, 5
  ///
  /// where "5" is moved as part of a larger operand tree. "5" would be placed
  /// (disregarding for a moment that literal constants don't have a location
  /// and can be used anywhere) into the same statement as %add would.
  FD_CanForwardLeaf,

  /// The root instruction can be forwarded in a non-trivial way. This requires
  /// the operand tree root to be an instruction in some statement.
  FD_CanForwardTree,

  FD_CanForwardPartially,

  /// Used to indicate that a forwarding has be carried out successfully.
  FD_DidForward,

  FD_DidForwardPartially,

  FD_NotApplicable
};

class TryForward {
public:
  virtual ~TryForward(){};

  virtual  isl::map getScalarReachingDefinition(ScopStmt *Stmt) =0;

  virtual ForwardingDecision forwardTree(ScopStmt *TargetStmt, isl::map TargetSchedule,
										 llvm::Value *UseVal,
                                         ScopStmt *UseStmt, llvm::Loop *UseLoop, isl::map UseSchedule, isl::map UseToTargetMapping,
								         ScopStmt *DefStmt, llvm::Loop *DefLoop, isl::map DefSchedule, isl::map DefToTargetMapping,
                                         int Depth, bool DoIt) = 0;

  virtual ForwardingDecision canForward(ScopStmt *TargetStmt,
	  llvm::Value *UseVal, ScopStmt *UseStmt,
	  llvm::Loop *UseLoop) {
	  return FD_NotApplicable;
  };

  virtual void doForward(ScopStmt *TargetStmt, llvm::Value *UseVal,
	  ScopStmt *UseStmt, llvm::Loop *UseLoop) {
  };
};

// Defined in DeLICM.cpp.
std::unique_ptr<TryForward> createTryForwardKnown(Scop *S, llvm::LoopInfo *LI, TryForward *TryForwardSubtree );

ScopPass *createForwardOpTreePass();
} // namespace polly

namespace llvm {
class PassRegistry;
void initializeForwardOpTreePass(llvm::PassRegistry &);
} // namespace llvm

#endif /* POLLY_FORWARDOPTREE_H */
