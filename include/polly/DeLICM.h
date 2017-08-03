//===------ DeLICM.h --------------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Undo the effect of Loop Invariant Code Motion (LICM) and
// GVN Partial Redundancy Elimination (PRE) on SCoP-level.
//
// Namely, remove register/scalar dependencies by mapping them back to array
// elements.
//
//===----------------------------------------------------------------------===//

#ifndef POLLY_DELICM_H
#define POLLY_DELICM_H

#include "polly/Support/GICHelper.h"

namespace llvm {
class PassRegistry;
class Pass;
} // namespace llvm

namespace polly {
class Scop;

/// Create a new DeLICM pass instance.
llvm::Pass *createDeLICMPass();

/// Compute the timepoints from a write to its (last) use.
///
/// Example:
/// Schedule := { Def[] -> [0]; Read[] -> [10]; }
/// Writes := { Def[] -> A[5] }
/// Reads := { Read[] -> A[5] }
///
/// Result:
/// { [A[5] -> Write[]] -> [i] : 0 < i < 10 }
///
/// Note: Lifetimes are expressed in terms of the preceding write. Hence, reads
/// before the first read cannot be expressed by this function.
///
/// @param Schedule          { Domain[] -> Scatter[] }
///                          The schedule of (at least) all statement instances
///                          occurring in @p Writes or @p Reads. All other
///                          instances will be ignored.
/// @param Writes            { DomainDef[] -> Element[] }
///                          Elements written to by the statement instances.
/// @param Reads             { DomainRead[] -> Element[] }
///                          Elements read from by the statement instances.
/// @param ReadEltInSameInst Whether a load will read the value from a write
///                          that is scheduled at the same timepoint (Writes
///                          happen before reads).
/// @param InclWrite         Whether to also include the timepoint where a value
///                          is written to the lifetime. If enabled for the
///                          example, it changes to
///                          { [A[5] -> Def[]] -> [i] : 0 <= i < 10 }.
/// @param InclLastRead      Whether to also include the timepoint where with
///                          the last use to the lifetime. If enabled for the
///                          example, it changes to
///                          { [A[5] -> Def[]] -> [i] : 0 < i <= 10 }.
/// @param ExitReads         Whether to extend the lifetimes that are not
///                          overwritten into infinity. This corresponds to the
///                          assumption that the values must be available after
///                          the scop. If enabled, the example changes to
///                          { [A[5] -> Def[]] -> [i] : 0 < i }
///
/// @return { [Element[] -> DomainWrite[]] -> Zone[] }
isl::union_map computeArrayLifetime(isl::union_map Schedule,
                                    isl::union_map Writes, isl::union_map Reads,
                                    bool ReadEltInSameInst, bool InclWrite,
                                    bool InclLastRead, bool ExitReads);

/// Determine whether two lifetimes are conflicting.
///
/// Used by unittesting.
bool isConflicting(isl::union_set ExistingOccupied,
                   isl::union_set ExistingUnused, isl::union_map ExistingKnown,
                   isl::union_map ExistingWrites,
                   isl::union_set ProposedOccupied,
                   isl::union_set ProposedUnused, isl::union_map ProposedKnown,
                   isl::union_map ProposedWrites,
                   llvm::raw_ostream *OS = nullptr, unsigned Indent = 0);

} // namespace polly

namespace llvm {
void initializeDeLICMPass(llvm::PassRegistry &);
void initializeForwardOpTreePass(llvm::PassRegistry &);
} // namespace llvm

#endif /* POLLY_DELICM_H */
