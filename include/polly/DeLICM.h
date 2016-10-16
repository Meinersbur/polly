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
} // anonymous namespace

namespace polly {
class Scop;

/// Create a new DeLICM pass instance.
llvm::Pass *createDeLICMPass();

/// Compute the reaching definition statement for each definition of an array
/// element.
///
/// The reaching definition of an array element at a specific timepoint is the
/// statement instance that had written the current element's content. This
/// function computes all reaching definitions for all array elements and
/// timepoints. For example:
///
/// Schedule := { Write[] -> [0]; Overwrite[] -> [10] }
/// Defs := { Write[] -> A[5]; Overwrite[] -> A[5] }
///
/// That is, index 5 of array A will be written to at timepoint 0 and 10. The
/// result will be:
///
/// { [A[5] -> [i]] -> Write[] : 0 < i < 10;
///   [A[5] -> [i]] -> Overwrite[] : 10 < i }
///
/// That is, between timepoint 0 (Write[]) and timepoint 10 (Overwrite[]), the
/// content of A[5] was written by statement instance Write[] and after
/// timepoint 10 by Overwrite[]. Values not defined in the map have no known
/// definition. This includes the statements instance timepoints themselves,
/// because reads in those timepoints could either read the old or the new
/// value, defined only by the statement itself. But this can be changed by @p
/// InclDef and @p InclRedef. InclDef=false and InclRedef=true will return a
/// zone. Unless @p InclDef and @p InclRedef are both true, there is only one
/// unique definition per element and timepoint.
///
/// @param Schedule  { DomainWrite[] -> Scatter[] }
///                  Schedule of (at least) all array writes. Instances not in
///                  @p Writes will be ignored.
/// @param Writes    { DomainWrite[] -> Element[] }
///                  Elements written to by the statement instances.
/// @param InclDef   Whether to include the definition's timepoint as where the
///                  element is well-defined (any load at that timepoint would
///                  happen the writes). In the example, enabling adds
///                  { [A[5] -> [0]] -> Write[]; [A[5] -> [10]] -> Overwrite[] }
///                  to the result.
/// @param InclRedef Whether to assume that at the timepoint where an element
///                  is overwritten, it still contains the old value (any load
///                  at that timepoint would happen before the overwrite). In
///                  this example, enabling this adds
///                  { [A[] -> [10]] -> Write[] } to the result.
///
/// @return { [Element[] -> Scatter[]] -> DomainWrite[] }
///         The reaching definitions as described above, or nullptr if either @p
///         Schedule or @p Writes is nullptr, or the ISL max operations count
///         has exceeded.
IslPtr<isl_union_map> computeReachingDefinition(IslPtr<isl_union_map> Schedule,
                                                IslPtr<isl_union_map> Writes,
                                                bool InclDef, bool InclRedef);

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
/// before the first read cannot expressed by this function.
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
IslPtr<isl_union_map> computeArrayLifetime(IslPtr<isl_union_map> Schedule,
                                           IslPtr<isl_union_map> Writes,
                                           IslPtr<isl_union_map> Reads,
                                           bool ReadEltInSameInst,
                                           bool InclWrite, bool InclLastRead,
                                           bool ExitReads);

/// Compute the next overwrite for each array element.
///
/// This is computeReachingDefinition() "in reverse"; Instead of looking to the
/// most recent write to an element, look for the next (over)write. For example:
///
/// Schedule := { Write[] -> [0]; Overwrite[] -> [10] }
/// Writes := { Write[] -> A[5]; Overwrite[] -> A[5] }
///
/// will result in:
///
/// { [A[5] -> [i]] -> Write[] : i < 0;
///   [A[5] -> [i]] -> Overwrite[] : 0 < i < 10 }
///
/// That is, A[5] will be overwritten next by Write[] when before timepoint 0,
/// or by Overwrite[] when between timepoints 0 and 10. Use InclPrevWrite=false
/// and InclOverwrite=true to interpret the result as a Zone.
///
/// @param Schedule      { DomainWrite[] -> Scatter[] }
///                      Schedule of (at least) all array writes. Instances not
///                      in @p Writes will be ignored.
/// @param Writes        { DomainWrite[] -> Element[] }
///                      Elements written to by the statement instances.
/// @param InclPrevWrite Whether to extend an overwrite timepoints to include
///                      the timepoint where the previous write happens (the
///                      previous write would happen at the beginning of its
///                      timepoint). In this example, this adds
///                      { [A[5] -> [0]] -> Overwrite[] } to the result.
/// @param InclOverwrite Whether the reaching overwrite includes the timepoint
///                      of the overwrite itself (so the overwrite would happen
///                      at then end of its timepoint). In the example, this
///                      adds
///                      { [A[5] -> [0]] -> Write[];
///                        [A[5] -> [10]] -> Overwrite[] }
///                      to the result.
///
/// @return { [Element[] -> Scatter[]] -> DomainWrite[] }
///         The reaching overwrite as defined above, or nullptr if either @p
///         Schedule or @p Writes is nullptr, or the ISL max operations count
///         has exceeded.
IslPtr<isl_union_map> computeReachingOverwrite(IslPtr<isl_union_map> Schedule,
                                               IslPtr<isl_union_map> Writes,
                                               bool InclPrevWrite,
                                               bool InclOverwrite);

/// Compute the timepoints where the contents of an array element are not used.
///
/// An element is unused at an timepoint when the element will be overwritten in
/// the future, but it is no read in between. Another way to express this: the
/// time from when the element is written, to the most recent read before it, or
/// infinitely into the past if there no read before. Such unused elements can
/// be overwritten by any value without changing the Scop's semantics. An
/// example:
///
/// Schedule := { Read[] -> [0]; Write[] -> [10]; Def[] -> [20] }
/// Writes := { Write[] -> A[5]; Def[] -> A[6] }
/// Reads := { Read[] -> A[5] }
///
/// The result will be:
///
/// { A[5] -> [i] : 0 < i < 10;
///   A[6] -> [i] : i < 20 }
///
/// That is, A[5] is unused between timepoint 0 (the read) and timepoint 10 (the
/// write). A[6] is unused before timepoint 20, but might be used after the
/// scop's execution (A[5] and any other A[i] as well). Use InclLastRead=false
/// and InclWrite=true to interpret the result as zone.
///
/// @param Schedule          { Domain[] -> Scatter[] }
///                          The schedule of (at least) all statement instances
///                          occurring in @p Writes or @p Reads. All other
///                          instances will be ignored.
/// @param Writes            { DomainWrite[] -> Element[] }
///                          Elements written to by the statement instances.
/// @param Reads             { DomainRead[] -> Element[] }
///                          Elements read from by the statement instances.
/// @param ReadEltInSameInst Whether a load will read the value from a write
///                          that is scheduled at the same timepoint (Writes
///                          happen before reads). Otherwise, loads will use the
///                          value of an element it had before the timepoint
///                          (Reads before writes). For example:
///                          { Read[] -> [0]; Write[] -> [0] }
///                          With ReadEltInSameInst=false it is assumed that the
///                          read happens before the write, such that the
///                          element is never unused, or just at timepoint 0,
///                          depending on InclLastRead/InclWrite.
///                          With ReadEltInSameInst=false it assumes that the
///                          value just written will be used. Anything before
///                          timepoint 0 will be considered unused.
/// @param InclLastRead      Whether the timepoint where an element is last read
///                          counts as unused (the read happens at the beginning
///                          of its timepoint, and nothing (else) can use it
///                          during the timepoint). In the example, this option
///                          adds { A[5] -> [0] } to the result.
/// @param InclWrite         Whether the timepoint where an element is written
///                          itself counts as unused (the write happens at the
///                          end of its timepoint; no (other) operations uses
///                          the element during the timepoint). In this example,
///                          this adds
///                          { A[5] -> [10]; A[6] -> [20] } to the result.
///
/// @return { Element[] -> Scatter[] }
///         The unused timepoints as defined above, or nullptr if either @p
///         Schedule, @p Writes are @p Reads is nullptr, or the ISL max
///         operations count is exceeded.
IslPtr<isl_union_map> computeArrayUnused(IslPtr<isl_union_map> Schedule,
                                         IslPtr<isl_union_map> Writes,
                                         IslPtr<isl_union_map> Reads,
                                         bool ReadEltInSameInst,
                                         bool InclLastRead, bool InclWrite);

/// Determine whether two lifetimes are conflicting.
///
/// Used by unittesting.
///
/// @param ExistingLifetime { [Element[] -> Zone[]] -> ValInst[] }
/// @param ExistingImplicitLifetimeIsUnknown
/// @param ExistingWritten  { [Element[] -> Scatter[]] -> ValInst[] }
/// @param ProposedLifetime { [Element[] -> Zone[]] -> ValInst[] }
/// @param ProposedImplicitLifetimeIsUnknown
/// @param ProposedWritten  { [Element[] -> Scatter[]] -> ValInst[] }
///
/// @param False, iff the lifetimes and writes can me merged.
///
/// @see polly::Knowledge
bool isConflicting(IslPtr<isl_union_map> ExistingLifetime,
                   bool ExistingmplicitLifetimeIsUnknown,
                   IslPtr<isl_union_map> ExistingWrites,
                   IslPtr<isl_union_map> ProposedLifetime,
                   bool ProposedImplicitLifetimeIsUnknown,
                   IslPtr<isl_union_map> ProposedWrites);
} // namespace polly

namespace llvm {
void initializeDeLICMPass(llvm::PassRegistry &);
} // namespace llvm

#endif /* POLLY_DELICM_H */
