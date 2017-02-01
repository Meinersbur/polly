//===------ DeLICM.cpp -----------------------------------------*- C++ -*-===//
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
// The algorithms here work on the scatter space - the image space of the
// schedule returned by Scop::getSchedule(). We call an element in that space an
// "timepoint". Timepoints are lexicographically ordered such that we can
// defined ranges in the scatter space. We use two flavors of such ranges:
// Timepoint sets and zones. A timepoint set is simply a subset of the scatter
// space and is directly stored as isl_set.
//
// Zones are used to describe the space between timepoints as open sets, ie.
// they
// do not contain the extrema. Using ISL rational sets to express these would be
// overkill. We also cannot store them as the integer timepoints they contain;
// the (nonempty) zone between 1 and 2 would be empty and not differentiable
// from eg. the zone between 3 and 4. Also, we cannot store the integer set
// including the extrema; the set ]1,2[ + ]3,4[ could be coalesced to ]1,3[,
// although we defined the range [2,3] to be not in the set. Instead, we store
// the "half-open" integer extrema, including the lower bound, but excluding the
// upper bound. Examples:
//
// * The set { [i] : 1 <= i <= 3 } represents the zone ]0,3[ (which contains the
//   integer points 1 and 2, but not 0 or 3)
//
// * { [1] } represents the zone ]0,1[
//
// * { [i] : i = 1 or i = 3 } represents the zone ]0,1[ + ]2,3[
//
// Therefore, an integer i in the set represents the zone ]i-1,i[, ie. strictly
// speaking the integer points never belong to the zone. However, depending an
// the interpretation, one might want to include them:
//
// * The timepoints adjacent to two unit zones: zoneToInsideInstances()
//
// * The timepoints before a unit zone begins:
//   shiftDim(<Zone>, isl_dim_in, -1, 1)
//
// * The timepoints that directly follow a unit zone: Reinterpret the zone as
//   a set of timepoints.
//
// It sometimes helps think about a value of i stored in an isl_set to represent
// the timepoint i-0.5 between two integer-valued timepoints.
// @see zoneToInsideInstances()
//
//
// The code makes use of maps and sets in many different spaces. To not loose
// track in which space a set or map is expected to be in, variables holding an
// ISL reference are usually annotated in the comments. They roughly follow ISL
// syntax for spaces, but only the tuples, not the dimensions. The tuples have a
// meaning as follows:
//
// * Space[] - An unspecified tuple. Used for function parameters such that the
//             function caller can use it for anything they like.
//
// * Domain[] - A statement instance as returned by ScopStmt::getDomain()
//     isl_id_get_name: Stmt_<NameOfBasicBlock>
//     isl_id_get_user: Pointer to ScopStmt
//
// * Element[] - An array element as in the range part of
//               MemoryAccess::getAccessRelation()
//     isl_id_get_name: MemRef_<NameOfArrayVariable>
//     isl_id_get_user: Pointer to ScopArrayInfo
//
// * Scatter[] - Scatter space or space of timepoints
//     Has no tuple id
//
// * Zone[] - Range between timepoints as described above
//     Has no tuple id
//
// * ValInst[] - An llvm::Value as defined at a specific timepoint.
//     A ValInst[] itself can be structured as one of:
//     * [] - An unknown value
//         Always zero dimensions
//         Has no tuple id
//     * Undef[] - Value is not used
//         Always zero dimensions
//         isl_id_get_name: Undef
//         isl_id_get_user: A pointer to an llvm::UndefValue
//     * Value[] - An llvm::Value that is read-only in the Scop, ie. its
//                 runtime content does not depend on the timepoint.
//         Always zero dimensions
//         isl_id_get_name: Val_<NameOfValue>
//         isl_id_get_user: A pointer to an llvm::Value
//     * [Domain[] -> Value[]] - An llvm::Value that may change during the
//                               Scop's execution
//         The tuple itself has no id, but it wraps a map space holding a
//         statement instance which defines the llvm::Value as the map's domain
//         and llvm::Value itself as range.
// @see makeValInst()
//
// An annotation "{ Domain[] -> Scatter[] }" therefore means: A map from a
// statement instance to a timepoint, aka. a schedule. There is only one scatter
// space, but most of the time multiple statements are processed in one set.
// This is why most of the time isl_union_map has to be used.
//
//===----------------------------------------------------------------------===//

#include "polly/DeLICM.h"
#include "polly/Options.h"
#include "polly/ScopBuilder.h"
#include "polly/ScopInfo.h"
#include "polly/ScopPass.h"
#include "polly/Support/VirtualInstruction.h"
#include "llvm/ADT/Statistic.h"
#define DEBUG_TYPE "polly-delicm"

using namespace polly;
using namespace llvm;

namespace {

cl::opt<unsigned long>
    DelicmMaxOps("polly-delicm-max-ops",
                 cl::desc("Maximum number of ISL operations to invest for "
                          "lifetime analysis; 0=no limit"),
                 cl::init(1000000), cl::cat(PollyCategory));

cl::opt<unsigned long>
    KnownMaxOps("polly-known-max-ops",
                cl::desc("Maximum number of ISL operations to invest for known "
                         "analysis; 0=no limit"),
                cl::init(1000000), cl::cat(PollyCategory));

STATISTIC(DeLICMAnalyzed, "Number of successfully analyzed SCoPs");
STATISTIC(DeLICMOutOfQuota,
          "Analyses aborted because max_operations was reached");
STATISTIC(DeLICMIncompatible, "Number of SCoPs incompatible for analysis");
STATISTIC(MappedValueScalars, "Number of mapped Value scalars");
STATISTIC(MappedPHIScalars, "Number of mapped PHI scalars");
STATISTIC(TargetsMapped, "Number of stores used for at least one mapping");
STATISTIC(DeLICMScopsModified, "Number of SCoPs optimized");

#undef DEBUG_TYPE
#define DEBUG_TYPE "polly-scalardeps"

STATISTIC(ScalarValueDeps, "Number of scalar value dependencies");
STATISTIC(ScalarValueLoopDeps, "Number of scalar value dependencies in loops");
STATISTIC(ScalarPHIDeps, "Number of scalar PHI dependencies");
STATISTIC(ScalarPHILoopDeps, "Number of scalar PHI dependencies in loops");

#undef DEBUG_TYPE
#define DEBUG_TYPE "polly-known"

STATISTIC(KnownAnalyzed, "Number of successfully analyzed SCoPs");
STATISTIC(KnownOutOfQuota,
          "Analyses aborted because max_operations was reached");
STATISTIC(KnownIncompatible, "Number of SCoPs incompatible for analysis");
STATISTIC(MappedKnown, "Number of deviated scalar loads to known content");
STATISTIC(MappedReadOnly, "Number of rematerialized read-only vars");
STATISTIC(KnownScopsModified, "Number of SCoPs optimized");

#undef DEBUG_TYPE
#define DEBUG_TYPE "polly-delicm"

/// Return the range elements that are lexicographically smaller.
///
/// @param Map    { Space[] -> Scatter[] }
/// @param Strict True for strictly lexicographically smaller elements. (exclude
///               same timepoints from the result)
///
/// @return { Space[] -> Scatter[] }
///         A map to all timepoints that happen before the timepoints the input
///         mapped to.
IslPtr<isl_map> beforeScatter(IslPtr<isl_map> Map, bool Strict) {
  auto RangeSpace = give(isl_space_range(isl_map_get_space(Map.keep())));
  auto ScatterRel = give(Strict ? isl_map_lex_gt(RangeSpace.take())
                                : isl_map_lex_ge(RangeSpace.take()));
  return give(isl_map_apply_range(Map.take(), ScatterRel.take()));
}

/// Piecewise beforeScatter(IslPtr<isl_map>,bool).
IslPtr<isl_union_map> beforeScatter(IslPtr<isl_union_map> UMap, bool Strict) {
  auto Result = give(isl_union_map_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](IslPtr<isl_map> Map) {
    auto After = beforeScatter(Map, Strict);
    Result = give(isl_union_map_add_map(Result.take(), After.take()));
  });
  return Result;
}

/// Return the range elements that are lexicographically larger.
///
/// @param Map    { Space[] -> Scatter[] }
/// @param Strict True for strictly lexicographically larger elements. (exclude
///               same timepoints from the result)
///
/// @return { Space[] -> Scatter[] }
///         A map to all timepoints that happen after the timepoints the input
///         map originally mapped to.
IslPtr<isl_map> afterScatter(IslPtr<isl_map> Map, bool Strict) {
  auto RangeSpace = give(isl_space_range(isl_map_get_space(Map.keep())));
  auto ScatterRel = give(Strict ? isl_map_lex_lt(RangeSpace.take())
                                : isl_map_lex_le(RangeSpace.take()));
  return give(isl_map_apply_range(Map.take(), ScatterRel.take()));
}

/// Piecewise afterScatter(IslPtr<isl_map>,bool).
IslPtr<isl_union_map> afterScatter(NonowningIslPtr<isl_union_map> UMap,
                                   bool Strict) {
  auto Result = give(isl_union_map_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](IslPtr<isl_map> Map) {
    auto After = afterScatter(Map, Strict);
    Result = give(isl_union_map_add_map(Result.take(), After.take()));
  });
  return Result;
}

/// Construct a range of timepoints between two timepoints.
///
/// Example:
/// From := { A[] -> [0]; B[] -> [0] }
/// To   := {             B[] -> [10]; C[] -> [20] }
///
/// Result:
/// { B[] -> [i] : 0 < i < 10 }
///
/// Note that A[] and C[] are not in the result because they do not have a start
/// or end timepoint. If a start (or end) timepoint is not unique, the first
/// (respectively last) is chosen.
///
/// @param From     { Space[] -> Scatter[] }
///                 Map to start timepoints.
/// @param To       { Space[] -> Scatter[] }
///                 Map to end timepoints.
/// @param InclFrom Whether to include the start timepoints to the result. In
///                 the example, this would add { B[] -> [0] }
/// @param InclTo   Whether to include the end timepoints to the result. In this
///                 example, this would add { B[] -> [10] }
///
/// @return { Space[] -> Scatter[] }
///         A map for each domain element of timepoints between two extreme
///         points, or nullptr if @p From or @p To is nullptr, or the ISL max
///         operations is exceeded.
IslPtr<isl_map> betweenScatter(IslPtr<isl_map> From, IslPtr<isl_map> To,
                               bool InclFrom, bool InclTo) {
  auto AfterFrom = afterScatter(From, !InclFrom);
  auto BeforeTo = beforeScatter(To, !InclTo);

  return give(isl_map_intersect(AfterFrom.take(), BeforeTo.take()));
}

/// Piecewise betweenScatter(IslPtr<isl_map>,IslPtr<isl_map>,bool,bool).
IslPtr<isl_union_map> betweenScatter(IslPtr<isl_union_map> From,
                                     IslPtr<isl_union_map> To, bool IncludeFrom,
                                     bool IncludeTo) {
  auto AfterFrom = afterScatter(From, !IncludeFrom);
  auto BeforeTo = beforeScatter(To, !IncludeTo);

  return give(isl_union_map_intersect(AfterFrom.take(), BeforeTo.take()));
}

/// If by construction a union map is known to contain only a single map, return
/// it.
///
/// This function combines isl_map_from_union_map() and
/// isl_union_map_extract_map(). isl_map_from_union_map() fails if the map is
/// empty because it doesn't not know which space it would be in.
/// isl_union_map_extract_map() on the other hand does not check whether there
/// is (at most) one isl_map in the union, ie. how it has been constructed is
/// probably wrong.
IslPtr<isl_map> singleton(IslPtr<isl_union_map> UMap,
                          IslPtr<isl_space> ExpectedSpace) {
  if (!UMap)
    return nullptr;

  if (isl_union_map_n_map(UMap.keep()) == 0)
    return give(isl_map_empty(ExpectedSpace.take()));

  auto Result = give(isl_map_from_union_map(UMap.take()));
  assert(!Result || isl_space_has_equal_tuples(
                        give(isl_map_get_space(Result.keep())).keep(),
                        ExpectedSpace.keep()) == isl_bool_true);
  return Result;
}

/// If by construction an isl_union_set is known to contain only a single
/// isl_set, return it.
///
/// This function combines isl_set_from_union_set() and
/// isl_union_set_extract_set(). isl_map_from_union_set() fails if the set is
/// empty because it doesn't not know which space it would be in.
/// isl_union_set_extract_set() on the other hand does not check whether there
/// is (at most) one isl_set in the union, ie. how it has been constructed is
/// probably wrong.
IslPtr<isl_set> singleton(IslPtr<isl_union_set> USet,
                          IslPtr<isl_space> ExpectedSpace) {
  if (!USet)
    return nullptr;

  if (isl_union_set_n_set(USet.keep()) == 0)
    return give(isl_set_empty(ExpectedSpace.copy()));

  auto Result = give(isl_set_from_union_set(USet.take()));
  assert(!Result || isl_space_has_equal_tuples(
                        give(isl_set_get_space(Result.keep())).keep(),
                        ExpectedSpace.keep()) == isl_bool_true);
  return Result;
}
#if 0
/// Returns whether @p Map has a mapping for at least all elements of @p Domain.
isl_bool isMapDomainSubsetOf(IslPtr<isl_map> Map,
                             NonowningIslPtr<isl_set> Domain) {
  auto Subset = give(isl_map_domain(Map.take()));
  return isl_set_is_subset(Subset.keep(), Domain.keep());
}
#endif
/// Determine how many dimensions the scatter space of @p Schedule has.
///
/// The schedule must not be empty and have equal number of dimensions of any
/// subspace it contains.
///
/// The implementation currently returns the maximum number of dimensions it
/// encounters, if different, and 0 if none is encountered. However, most other
/// code will most likely fail if one of these happen.
unsigned getNumScatterDims(NonowningIslPtr<isl_union_map> Schedule) {
  unsigned Dims = 0;
  foreachElt(Schedule, [=, &Dims](IslPtr<isl_map> Map) {
    Dims = std::max(Dims, isl_map_dim(Map.keep(), isl_dim_out));
  });
  return Dims;
}

/// Return the scatter space of a @p Schedule.
///
/// This is basically the range space of the schedule map, but harder to
/// determine because it is an isl_union_map.
IslPtr<isl_space> getScatterSpace(NonowningIslPtr<isl_union_map> Schedule) {
  if (!Schedule)
    return nullptr;
  auto Dims = getNumScatterDims(Schedule);
  auto ScatterSpace =
      give(isl_space_set_from_params(isl_union_map_get_space(Schedule.keep())));
  return give(isl_space_add_dims(ScatterSpace.take(), isl_dim_set, Dims));
}

/// Construct an identity map for the given domain values.
///
/// There is no type resembling isl_union_space, hence we have to pass an
/// isl_union_set as the map's domain and range space.
///
/// @param USet           { Space[] }
///                       The returned map's domain and range.
/// @param RestrictDomain If true, the returned map only maps elements contained
///                       in @p USet and no other. If false, it returns an
///                       overapproximation with the identity maps of any space
///                       in @p USet, not just the elements in it.
///
/// @return { Space[] -> Space[] }
///         A map that maps each value of @p USet to itself.
IslPtr<isl_union_map> makeIdentityMap(NonowningIslPtr<isl_union_set> USet,
                                      bool RestrictDomain) {
  auto Result = give(isl_union_map_empty(isl_union_set_get_space(USet.keep())));
  foreachElt(USet, [=, &Result](IslPtr<isl_set> Set) {
    auto IdentityMap = give(isl_map_identity(
        isl_space_map_from_set(isl_set_get_space(Set.keep()))));
    if (RestrictDomain)
      IdentityMap =
          give(isl_map_intersect_domain(IdentityMap.take(), Set.take()));
    Result = give(isl_union_map_add_map(Result.take(), IdentityMap.take()));
  });
  return Result;
}

/// Constructs a map that swaps two nested tuples.
///
/// @param FromSpace1 { Space1[] }
/// @param FromSpace2 { Space2[] }
///
/// @result { [Space1[] -> Space2[]] -> [Space2[] -> Space1[]] }
IslPtr<isl_basic_map> makeTupleSwapBasicMap(IslPtr<isl_space> FromSpace1,
                                            IslPtr<isl_space> FromSpace2) {
  assert(isl_space_is_set(FromSpace1.keep()) != isl_bool_false);
  assert(isl_space_is_set(FromSpace2.keep()) != isl_bool_false);

  auto Dims1 = isl_space_dim(FromSpace1.keep(), isl_dim_set);
  auto Dims2 = isl_space_dim(FromSpace2.keep(), isl_dim_set);
  auto FromSpace = give(isl_space_wrap(isl_space_map_from_domain_and_range(
      FromSpace1.copy(), FromSpace2.copy())));
  auto ToSpace = give(isl_space_wrap(isl_space_map_from_domain_and_range(
      FromSpace2.take(), FromSpace1.take())));
  auto MapSpace = give(
      isl_space_map_from_domain_and_range(FromSpace.take(), ToSpace.take()));

  auto Result = give(isl_basic_map_universe(MapSpace.take()));
  for (auto i = Dims1 - Dims1; i < Dims1; i += 1) {
    Result = give(isl_basic_map_equate(Result.take(), isl_dim_in, i,
                                       isl_dim_out, Dims2 + i));
  }
  for (auto i = Dims2 - Dims2; i < Dims2; i += 1) {
    Result = give(isl_basic_map_equate(Result.take(), isl_dim_in, Dims1 + i,
                                       isl_dim_out, i));
  }

  return Result;
}

/// Like makeTupleSwapBasicMap(IslPtr<isl_space>,IslPtr<isl_space>), but returns
/// an isl_map.
IslPtr<isl_map> makeTupleSwapMap(IslPtr<isl_space> FromSpace1,
                                 IslPtr<isl_space> FromSpace2) {
  auto BMapResult =
      makeTupleSwapBasicMap(std::move(FromSpace1), std::move(FromSpace2));
  return give(isl_map_from_basic_map(BMapResult.take()));
}

/// Reverse the nested map tuple in @p Map's domain.
///
/// @param Map { [Space1[] -> Space2[]] -> Space3[] }
///
/// @return { [Space2[] -> Space1[]] -> Space3[] }
IslPtr<isl_map> reverseDomain(IslPtr<isl_map> Map) {
  auto DomSpace =
      give(isl_space_unwrap(isl_space_domain(isl_map_get_space(Map.keep()))));
  auto Space1 = give(isl_space_domain(DomSpace.copy()));
  auto Space2 = give(isl_space_range(DomSpace.take()));
  auto Swap = makeTupleSwapMap(std::move(Space1), std::move(Space2));
  return give(isl_map_apply_domain(Map.take(), Swap.take()));
}

/// Piecewise reverseDomain(IslPtr<isl_map>).
IslPtr<isl_union_map> reverseDomain(NonowningIslPtr<isl_union_map> UMap) {
  auto Result = give(isl_union_map_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](IslPtr<isl_map> Map) {
    auto Reversed = reverseDomain(std::move(Map));
    Result = give(isl_union_map_add_map(Result.take(), Reversed.take()));
  });
  return Result;
}

/// Compute the next overwrite for a scalar.
///
/// @param Schedule      { DomainWrite[] -> Scatter[] }
///                      Schedule of (at least) all writes. Instances not in @p
///                      Writes will be ignored.
/// @param Writes        { DomainWrite[] }
///                      The element instances that write to the scalar.
/// @param InclPrevWrite Whether to extend an overwrite timepoints to include
/// the timepoint where the previous write happens.
/// @param InclOverwrite Whether the reaching overwrite includes the timepoint
/// of the overwrite itself.
///
/// @return { Scatter[] -> DomainDef[] }
IslPtr<isl_union_map>
computeScalarReachingOverwrite(IslPtr<isl_union_map> Schedule,
                               IslPtr<isl_union_set> Writes, bool InclPrevWrite,
                               bool InclOverwrite) {

  // { DomainWrite[] }
  auto WritesMap = give(isl_union_map_from_domain(Writes.take()));

  // { [Element[] -> Scatter[]] -> DomainWrite[] }
  auto Result = computeReachingOverwrite(
      std::move(Schedule), std::move(WritesMap), InclPrevWrite, InclOverwrite);

  return give(isl_union_map_domain_factor_range(Result.take()));
}

/// Overload of computeScalarReachingOverwrite, with only one writing statement.
/// Consequently, the result consists of only one map space.
///
/// @param Schedule      { DomainWrite[] -> Scatter[] }
/// @param Writes        { DomainWrite[] }
/// @param InclPrevWrite Include the previous write to result.
/// @param InclOverwrite Include the overwrite to the result.
///
/// @return { Scatter[] -> DomainWrite[] }
IslPtr<isl_map> computeScalarReachingOverwrite(IslPtr<isl_union_map> Schedule,
                                               IslPtr<isl_set> Writes,
                                               bool InclPrevWrite,
                                               bool InclOverwrite) {
  auto ScatterSpace = getScatterSpace(Schedule);
  auto DomSpace = give(isl_set_get_space(Writes.keep()));

  auto ReachOverwrite = computeScalarReachingOverwrite(
      Schedule, give(isl_union_set_from_set(Writes.take())), InclPrevWrite,
      InclOverwrite);

  auto ResultSpace = give(isl_space_map_from_domain_and_range(
      ScatterSpace.take(), DomSpace.take()));
  return singleton(std::move(ReachOverwrite), ResultSpace);
}

// Just a wrapper around computeScalarReachingDefinition if there is just
// one element.
// { Scatter[] -> Domain[] }

/// Compute the reaching definition of a scalar.
///
/// Compared to computeReachingDefinition, there is just one element which is
/// accessed an therefore doesn't need to be specified.
///
/// @param Schedule  { DomainWrite[] -> Scatter[] }
/// @param Writes    { DomainWrite[] }
/// @param InclDef   Include the timepoint of the definition to the result.
/// @param InclRedef Include the timepoint of the overwrite into the result.
///
/// @return { Scatter[] -> DomainWrite[] }
IslPtr<isl_union_map>
computeScalarReachingDefinition(IslPtr<isl_union_map> Schedule,
                                IslPtr<isl_union_set> Writes, bool InclDef,
                                bool InclRedef) {

  // { DomainWrite[] -> Element[] }
  auto Defs = give(isl_union_map_from_domain(Writes.take()));

  // { [Element[] -> Scatter[]] -> DomainWrite[] }
  auto ReachDefs =
      computeReachingDefinition(Schedule, Defs, InclDef, InclRedef);

  // { Scatter[] -> DomainWrite[] }
  return give(isl_union_set_unwrap(
      isl_union_map_range(isl_union_map_curry(ReachDefs.take()))));
}

/// Compute the reaching definition of a scalar.
///
/// This overload accepts only a single writing statement as an isl_map,
/// consequently the result also is only a single isl_map.
///
/// @param Schedule  { DomainWrite[] -> Scatter[] }
/// @param Writes    { DomainWrite[] }
/// @param InclDef   Include the timepoint of the definition to the result.
/// @param InclRedef Include the timepoint of the overwrite into the result.
///
/// @return { Scatter[] -> DomainWrite[] }
IslPtr<isl_map> computeScalarReachingDefinition( // { Domain[] -> Zone[] }
    IslPtr<isl_union_map> Schedule, IslPtr<isl_set> Writes, bool InclDef,
    bool InclRedef) {
  auto DomainSpace = give(isl_set_get_space(Writes.keep()));
  auto ScatterSpace = getScatterSpace(Schedule);

  //  { Scatter[] -> DomainWrite[] }
  auto UMap = computeScalarReachingDefinition(
      Schedule, give(isl_union_set_from_set(Writes.take())), InclDef,
      InclRedef);

  auto ResultSpace = give(isl_space_map_from_domain_and_range(
      ScatterSpace.take(), DomainSpace.take()));
  return singleton(UMap, ResultSpace);
}

/// Create a map that shifts one dimension by an offset.
///
/// Example:
/// makeShiftDimAff({ [i0, i1] -> [o0, o1] }, 1, -2)
///   = { [i0, i1] -> [i0, i1 - 1] }
///
/// @param Space  The map space of the result. Must have equal number of in- and
/// out-dimensions.
/// @param Pos    Position to shift.
/// @param Amount Value added to the shifted dimension.
///
/// @return An isl_multi_aff for the map with this shifted dimension.
IslPtr<isl_multi_aff> makeShiftDimAff(IslPtr<isl_space> Space, int Pos,
                                      int Amount) {
  auto Identity = give(isl_multi_aff_identity(Space.take()));
  if (Amount == 0)
    return Identity;
  auto ShiftAff = give(isl_multi_aff_get_aff(Identity.keep(), Pos));
  ShiftAff = give(isl_aff_set_constant_si(ShiftAff.take(), Amount));
  return give(isl_multi_aff_set_aff(Identity.take(), Pos, ShiftAff.take()));
}

/// Add a constant to one dimension of a map.
///
/// @param Map    The map to shift a dimension in.
/// @param Type   A tuple of @p Map which contains the dimension to shift.
/// @param Pos    The dimension to shift. If negative, the dimensions are
/// counted from the end instead from the beginning. Eg. -1 is the last
/// dimension in the tuple.
/// @param Amount The offset to add to the specified dimension.
///
/// @return The modified map.
IslPtr<isl_map> shiftDim(IslPtr<isl_map> Map, isl_dim_type Type, int Pos,
                         int Amount) {
  assert((Type == isl_dim_in || Type == isl_dim_out) &&
         "Cannot shift parameter dims");
  int NumDims = isl_map_dim(Map.keep(), Type);
  if (Pos < 0)
    Pos = NumDims + Pos;
  assert(Pos < NumDims && "Dimension index must be in range");
  auto Space = give(isl_map_get_space(Map.keep()));
  Space = give((Type == isl_dim_in) ? isl_space_domain(Space.take())
                                    : isl_space_range(Space.take()));
  Space = give(isl_space_map_from_domain_and_range(Space.copy(), Space.copy()));
  auto Translator = makeShiftDimAff(std::move(Space), Pos, Amount);
  auto TranslatorMap = give(isl_map_from_multi_aff(Translator.take()));
  return give((Type == isl_dim_in)
                  ? isl_map_apply_domain(Map.take(), TranslatorMap.take())
                  : isl_map_apply_range(Map.take(), TranslatorMap.take()));
}

/// Add a constant to one dimension of a each map in a union map.
///
/// @param UMap   The maps to shift a dimension in.
/// @param Type   The tuple which contains the dimension to shift.
/// @param Pos    The dimension to shift. If negative, the dimensions are
/// counted from the ends of each map of union instead from their beginning. Eg.
/// -1 is the last dimension of any map.
/// @param Amount The offset to add to the specified dimension.
///
/// @return The union of all modified maps.
IslPtr<isl_union_map> shiftDim(IslPtr<isl_union_map> UMap, isl_dim_type Type,
                               int Pos, int Amount) {
  auto Result = give(isl_union_map_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](IslPtr<isl_map> Map) {
    auto Shifted = shiftDim(Map, Type, Pos, Amount);
    Result = give(isl_union_map_add_map(Result.take(), Shifted.take()));
  });
  return Result;
}

/// Simplify a map inplace.
void simplify(IslPtr<isl_map> &Map) {
  Map = give(isl_map_compute_divs(Map.take()));
  Map = give(isl_map_detect_equalities(Map.take()));
  Map = give(isl_map_coalesce(Map.take()));
}

/// Simplify a union map inplace.
void simplify(IslPtr<isl_union_map> &Map) {
  Map = give(isl_union_map_compute_divs(Map.take()));
  Map = give(isl_union_map_detect_equalities(Map.take()));
  Map = give(isl_union_map_coalesce(Map.take()));
}

/// Try to find a 'natural' extension of a mapped to elements outside its
/// domain.
///
/// @param Relevant The map with mapping that may not be modified.
/// @param Universe The domain to which @p Relevant needs to be extended.
///
/// @return A map with that associates the domain elements of @p Relevant to the
///         same elements and in addition the elements of @p Universe to some
///         undefined elements. The function prefers to return simple maps.
IslPtr<isl_union_map> expandMapping(IslPtr<isl_union_map> Relevant,
                                    IslPtr<isl_union_set> Universe) {
  Relevant = give(isl_union_map_coalesce(Relevant.take()));
  auto RelevantDomain = give(isl_union_map_domain(Relevant.copy()));
  auto Simplified =
      give(isl_union_map_gist_domain(Relevant.take(), RelevantDomain.take()));
  Simplified = give(isl_union_map_coalesce(Simplified.take()));
  return give(
      isl_union_map_intersect_domain(Simplified.take(), Universe.take()));
}

/// Input: { Domain[] -> [Range1[] -> Range2[]] }
/// Output: { [Domain[] -> Range1[]] -> [Domain[] -> Range2[]] }
IslPtr<isl_map> isl_map_distribute_domain(IslPtr<isl_map> Map) {
  auto Space = give(isl_map_get_space(Map.keep()));
  auto DomainSpace = give(isl_space_domain(Space.copy()));
  assert(DomainSpace);
  auto DomainDims = isl_space_dim(DomainSpace.keep(), isl_dim_set);
  auto RangeSpace = give(isl_space_unwrap(isl_space_range(Space.copy())));
  auto Range1Space = give(isl_space_domain(RangeSpace.copy()));
  assert(Range1Space);
  auto Range1Dims = isl_space_dim(Range1Space.keep(), isl_dim_set);
  auto Range2Space = give(isl_space_range(RangeSpace.copy()));
  assert(Range2Space);
  auto Range2Dims = isl_space_dim(Range2Space.keep(), isl_dim_set);

  auto OutputSpace = give(isl_space_map_from_domain_and_range(
      isl_space_wrap(isl_space_map_from_domain_and_range(DomainSpace.copy(),
                                                         Range1Space.copy())),
      isl_space_wrap(isl_space_map_from_domain_and_range(DomainSpace.copy(),
                                                         Range2Space.copy()))));

  auto Translator =
      give(isl_basic_map_universe(isl_space_map_from_domain_and_range(
          isl_space_wrap(Space.copy()), isl_space_wrap(OutputSpace.copy()))));

  for (unsigned i = 0; i < DomainDims; i += 1) {
    Translator = give(
        isl_basic_map_equate(Translator.take(), isl_dim_in, i, isl_dim_out, i));
    Translator =
        give(isl_basic_map_equate(Translator.take(), isl_dim_in, i, isl_dim_out,
                                  DomainDims + Range1Dims + i));
  }
  for (unsigned i = 0; i < Range1Dims; i += 1) {
    Translator =
        give(isl_basic_map_equate(Translator.take(), isl_dim_in, DomainDims + i,
                                  isl_dim_out, DomainDims + i));
  }
  for (unsigned i = 0; i < Range2Dims; i += 1) {
    Translator = give(isl_basic_map_equate(
        Translator.take(), isl_dim_in, DomainDims + Range1Dims + i, isl_dim_out,
        DomainDims + Range1Dims + DomainDims + i));
  }

  return give(isl_set_unwrap(isl_set_apply(
      isl_map_wrap(Map.copy()), isl_map_from_basic_map(Translator.copy()))));
}

IslPtr<isl_union_map>
isl_union_map_distribute_domain(IslPtr<isl_union_map> UMap) {
  auto Result = give(isl_union_map_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](IslPtr<isl_map> Map) {
    auto Distributed = isl_map_distribute_domain(Map);
    Result = give(isl_union_map_add_map(Result.take(), Distributed.copy()));
  });
  return Result;
}

/// Determine whether an access touches at most one element.
///
/// The accessed element could be a scalar or accessing an array with constant
/// subscript, st. all instances access only that element.
///
/// @param Map { Domain[] -> Element[] }
///            The access's access relation.
///
/// @return True, if zero or one elements are accessed; False if at least two
///         different elements are accessed.
bool isScalarAccess(IslPtr<isl_map> Map) {
  auto Set = give(isl_map_range(Map.take()));
  return isl_set_is_singleton(Set.keep());
}

/// Return whether @p Map maps to llvm::Undef.
///
/// @param Map { [] -> ValInst[] }
bool isMapToUndef(NonowningIslPtr<isl_map> Map) {
  if (!isl_map_has_tuple_id(Map.keep(), isl_dim_out))
    return false;

  auto Id = give(isl_map_get_tuple_id(Map.keep(), isl_dim_out));
  auto Val = static_cast<Value *>(isl_id_get_user(Id.keep()));
  return Val && isa<UndefValue>(Val);
}

/// Return whether @p Map maps to an unknown value.
///
/// @param { [] -> ValInst[] }
bool isMapToUnknown(NonowningIslPtr<isl_map> Map) {
  auto Space = give(isl_space_range(isl_map_get_space(Map.keep())));
  return !isl_map_has_tuple_id(Map.keep(), isl_dim_set) &&
         !isl_space_is_wrapping(Space.keep());
}

/// Remove unknown values from the mapping, leaving only mappings to
/// llvm::Value's and llvm::Undef.
///
/// @param UMap { [] -> ValInst[] }
///
/// @return { [] -> ValInst[] }
IslPtr<isl_union_map>
removeUnknownValInst(NonowningIslPtr<isl_union_map> UMap) {
  auto Result = give(isl_union_map_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](IslPtr<isl_map> Map) {
    if (!isMapToUnknown(Map))
      Result = give(isl_union_map_add_map(Result.take(), Map.take()));
  });
  return Result;
}

/// Return the domain of everything that maps to an unknown value.
///
/// @param UMap { Domain[] -> ValInst[] }
///
/// @return { Domain[] }
IslPtr<isl_union_set>
getUnknownValInstDomain(NonowningIslPtr<isl_union_map> UMap) {
  auto Result = give(isl_union_set_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](IslPtr<isl_map> Map) {
    if (isMapToUnknown(Map))
      Result = give(
          isl_union_set_add_set(Result.take(), isl_map_domain(Map.take())));
  });
  return Result;
}

/// Return the domain of everything that maps to Undef.
///
/// @param UMap { Domain[] -> ValInst[] }
///
/// @return { Domain[] }
IslPtr<isl_union_set>
getUndefValInstDomain(NonowningIslPtr<isl_union_map> UMap) {
  auto Result = give(isl_union_set_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](IslPtr<isl_map> Map) {
    if (isMapToUndef(Map))
      Result = give(
          isl_union_set_add_set(Result.take(), isl_map_domain(Map.take())));
  });
  return Result;
}

/// Remove everything that maps to llvm::Undef.
///
/// @param UMap { [] -> ValInst[] }
///
/// @return { [] -> ValInst[] }
IslPtr<isl_union_map> removeUndefValInst(NonowningIslPtr<isl_union_map> UMap) {
  auto Result = give(isl_union_map_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](IslPtr<isl_map> Map) {
    if (!isMapToUndef(Map))
      Result = give(isl_union_map_add_map(Result.take(), Map.take()));
  });
  return Result;
}

/// Return only the mappings that map to known values.
///
/// @param UMap { [] -> ValInst[] }
///
/// @return { [] -> ValInst[] }
IslPtr<isl_union_map> filterKnownValInst(NonowningIslPtr<isl_union_map> UMap) {
  auto Result = give(isl_union_map_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](IslPtr<isl_map> Map) {
    if (!isMapToUnknown(Map) && !isMapToUndef(Map))
      Result = give(isl_union_map_add_map(Result.take(), Map.take()));
  });
  return Result;
}

/// Represent the knowledge of the contents any array elements in any zone or
/// the knowledge we would add when mapping a scalar to an array element.
///
/// Every array element at every zone unit has one three states:
/// - Undef: Not occupied by any value so transformation can change it to other
/// values.
/// - Known: Contains an llvm::Value instance, the instance is stored as the
/// domain of the statement instance defining it.
/// - Unknown: The element contains a value, but it is not a determinable
/// llvm::Value instance.
///
/// There are two uses for the Knowledge class:
/// 1) To represent the knowledge of the current state of ScopInfo. The Undef
///    state means that an element is currently unused: there is no read of it
///    before the next overwrite. Also called 'existing'.
/// 2) To represent the requirements for mapping a scalar to array elements. The
///    undef state means that there is no change/requirement. Also called
///    'proposed'.
///
/// In addition to the these states at unit zones, Knowledge need to know when
/// values are written. This is because written values may have no lifetime (one
/// reason is that the value is never read). Such writes would therefore never
/// conflict, but overwrite values that might still be required. Another source
/// of problems problem are multiple writes to the same element at the same
/// timepoint, because their order is undefined. Writes can either write know or
/// unknown states. An 'undef' write would a non-existing write.
class Knowledge {
private:
  /// { [Element[] -> Zone[]] -> ValInst[] }
  /// The state of every array element at every unit zone.
  IslPtr<isl_union_map> Lifetime;

  /// An array element at any time has one of the three states. For efficiency,
  /// one of them can be represented implicitly by assuming that state when it
  /// maps to nothing. Which one is more efficient depends on the use case.
  ///
  /// If ImplicitLifetimeIsUnknown == false, unmapped zones are assumed to be
  /// Unknown. This is more efficient for use case 1) because anything that
  /// cannot be determined to be Known or Undef is Unknown.
  ///
  /// If ImplicitLifetimeIsUnknown == true, unmapped zones are assumed to be
  /// Undef. This is more efficient for use case 2) because scalar mapping only
  /// constraints zones that are in scalar's lifetime.
  bool ImplicitLifetimeIsUnknown = false;

  /// { [Element[] -> Scatter[]] -> ValInst[] }
  /// The write actions currently in the scop or that would be added when
  /// mapping a scalar.
  IslPtr<isl_union_map> Written;

  /// Check whether this Knowledge object is well-formed.
  void checkConsistency() const {
    assert(!Lifetime == !Written);

    // Default-initialized object
    if (!Lifetime && !Written)
      return;

    assert(Lifetime);
    assert(Written);
    assert(isl_union_map_is_single_valued(Lifetime.keep()) != isl_bool_false);
  }

  /// Ensure an unique representation depending on ImplicitLifetimeIsUnknown.
  void canonicalize() {
    // If at least one is nullptr, the max_operations quota for computing one
    // might have exceeded. In this case, this Knowledge object is not usable.
    if (!Lifetime || !Written) {
      Lifetime = nullptr;
      Written = nullptr;
      return;
    }

    if (isImplicitLifetimeUndef())
      Lifetime = removeUndefValInst(this->Lifetime);
    if (isImplicitLifetimeUnknown())
      Lifetime = removeUnknownValInst(this->Lifetime);
  }

  /// Accessor for ImplicitLifetimeIsUnknown.
  bool isImplicitLifetimeUnknown() const { return ImplicitLifetimeIsUnknown; }

  /// Accessor for ImplicitLifetimeIsUnknown.
  bool isImplicitLifetimeUndef() const { return !ImplicitLifetimeIsUnknown; }

public:
  /// Initialize an nullptr-Knowledge. This is only provided for convenience; do
  /// not use such an object.
  Knowledge() {}

  /// Create a new object with the given members.
  Knowledge(IslPtr<isl_union_map> Lifetime, bool ImplicitLifetimeIsUnknown,
            IslPtr<isl_union_map> Written)
      : Lifetime(std::move(Lifetime)),
        ImplicitLifetimeIsUnknown(ImplicitLifetimeIsUnknown),
        Written(std::move(Written)) {
    canonicalize();
    checkConsistency();
  }

  /// Alternative constructor taking isl_maps instead isl_union_map.
  Knowledge(IslPtr<isl_map> Lifetime, bool ImplicitLifetimeIsUnknown,
            IslPtr<isl_map> Written)
      : Knowledge(give(isl_union_map_from_map(Lifetime.take())),
                  ImplicitLifetimeIsUnknown,
                  give(isl_union_map_from_map(Written.take()))) {}

  /// Return whether this object was default-constructed.
  bool isUsable() const { return Lifetime && Written; }

  /// Print the content of this object to @p OS.
  void print(llvm::raw_ostream &OS, unsigned Indent = 0) const {
    if (isUsable()) {
      if (isImplicitLifetimeUnknown())
        OS.indent(Indent) << "Lifetime: " << Lifetime << " + Unknown\n";
      else
        OS.indent(Indent) << "Lifetime: " << Lifetime << " + Undef\n";
      OS.indent(Indent) << "Written : " << Written << '\n';
    } else {
      OS.indent(Indent) << "Invalid knowledge\n";
    }
  }

  /// Dump the object content stderr. Meant to be called in a debugger.
  void dump() const;

  /// Combine two knowledges, this and @p That.
  ///
  /// The two knowledges must not conflict each other. Only combining 'implicit
  /// unknown' (use case 1) with 'implicit undef' (use case 2) knowledges is
  /// implemented.
  void merge_inplace(Knowledge That) {
    assert(!isConflicting(*this, That));
    assert(this->isImplicitLifetimeUnknown());
    assert(That.isImplicitLifetimeUndef());

    auto ThatKnownDomain = filterKnownValInst(That.Lifetime);
    auto ThatDomain = give(isl_union_map_domain(That.Lifetime.take()));

    Lifetime =
        give(isl_union_map_subtract_domain(Lifetime.take(), ThatDomain.take()));
    Lifetime =
        give(isl_union_map_union(Lifetime.take(), ThatKnownDomain.take()));

    Written = give(isl_union_map_union(Written.take(), That.Written.take()));

    checkConsistency();
  }

  /// Determine whether two Knowledges conflict each other.
  ///
  /// In theory @p This and @p That are symmetric, but the implementation is
  /// constrained by the implicit interpretation.
  ///
  /// A conflict is defined as non-preserved semantics when they are merged. For
  /// instance, when for the same array and zone they assume different
  /// llvm::Values.
  ///
  /// @param Existing One of the knowledges; current implementation requires it
  ///                 to be 'implicit unknown' (use case 1).
  /// @param Proposed One of the knowledges; current implementation requires it
  ///                 to be 'implicit undef' (use case 2).
  /// @param OS       Dump the conflict reason to this output stream; use
  /// nullptr to
  ///                 not output anything.
  /// @param Indent   Indention for the conflict reason.
  ///
  /// @return True, iff the two knowledges are conflicting.
  static bool isConflicting(const Knowledge &Existing,
                            const Knowledge &Proposed,
                            llvm::raw_ostream *OS = nullptr,
                            unsigned Indent = 0) {
    assert(Existing.isImplicitLifetimeUnknown());
    assert(Proposed.isImplicitLifetimeUndef());

    // The following domain intersections conflict:
    // 1) Unknown vs Unknown
    // 2a) Known vs Unknown, 2b) Unknown vs Known
    // 3) Known vs Known that do not map to the same llvm::Value instance
    // 4a) Written vs Unknown, 4b) Unknown vs Written
    // 5a) Written Unknown vs Known, 5b) Known vs Written Unknown
    // 6a) Written Known vs Known, 6b) Known vs Written Known that do not write
    //     the same llvm::Value instance
    // 7) Written Known/Unknown vs Written Known/Unknown, where the first writes
    //    different values to the same location and at the same timepoint as the
    //    latter.

    // Check 1) and 2a)
    auto ExistingUndef = getUndefValInstDomain(Existing.Lifetime);
    auto ProposedUnknownDomain = getUnknownValInstDomain(Proposed.Lifetime);
    if (!isl_union_set_is_subset(ProposedUnknownDomain.keep(),
                                 ExistingUndef.keep())) {
      if (OS)
        OS->indent(Indent) << "Conflict with proposed unknown\n";
      return true;
    }

    // Check 2b)
    auto ProposedKnown = filterKnownValInst(Proposed.Lifetime);
    auto ProposedKnownDomain = give(isl_union_map_domain(ProposedKnown.copy()));
    auto ExistingKnownOrUndefDomain =
        give(isl_union_map_domain(Existing.Lifetime.copy()));
    if (!isl_union_set_is_subset(ProposedKnownDomain.keep(),
                                 ExistingKnownOrUndefDomain.keep())) {
      if (OS)
        OS->indent(Indent) << "Conflict of existing unknown\n";
      return true;
    }

    // Check 3)
    auto ExistingKnown = filterKnownValInst(Existing.Lifetime);
    auto ExistingKnownDomain = give(isl_union_map_domain(ExistingKnown.copy()));
    auto CommonOverlapKnown = give(isl_union_set_intersect(
        ExistingKnownDomain.copy(), ProposedKnownDomain.copy()));
    auto ExistingOverlapKnown = give(isl_union_map_intersect_domain(
        ExistingKnown.copy(), CommonOverlapKnown.copy()));
    auto ProposedOverlapKnown = give(isl_union_map_intersect_domain(
        ProposedKnown.copy(), CommonOverlapKnown.copy()));
    if (!isl_union_map_is_equal(ExistingOverlapKnown.keep(),
                                ProposedOverlapKnown.keep())) {
      if (OS) {
        OS->indent(Indent)
            << "Conflict of lifetime-to-map known with existing known\n";
        auto ExistingConflict = give(isl_union_map_subtract(
            ExistingOverlapKnown.copy(), ProposedOverlapKnown.copy()));
        auto ProposedConflict = give(isl_union_map_subtract(
            ProposedOverlapKnown.copy(), ExistingOverlapKnown.copy()));
        OS->indent(Indent + 2)
            << "Existing wants: " << ExistingConflict << '\n';
        OS->indent(Indent + 2)
            << "Proposed wants: " << ProposedConflict << '\n';
      }
      return true;
    }

    // Check 4a)
    auto ExistingWritten = shiftDim(Existing.Written, isl_dim_in, -1, 1);
    auto ExistingWrittenZone =
        give(isl_union_map_domain(ExistingWritten.copy()));
    if (!isl_union_set_is_disjoint(ExistingWrittenZone.keep(),
                                   ProposedUnknownDomain.keep())) {
      if (OS)
        OS->indent(Indent) << "Conflict of current write to proposed unknown\n";
      return true;
    }

    // Check 4b)
    auto ProposedWritten = shiftDim(Proposed.Written, isl_dim_in, -1, 1);
    auto ProposedWrittenZone =
        give(isl_union_map_domain(ProposedWritten.copy()));
    if (!isl_union_set_is_subset(ProposedWrittenZone.keep(),
                                 ExistingKnownOrUndefDomain.keep())) {
      if (OS)
        dbgs().indent(Indent)
            << "Conflict of proposed write to current unknown\n";
      return true;
    }

    // Check 5a)
    auto ExistingWrittenUnknownZone = getUnknownValInstDomain(ExistingWritten);
    if (!isl_union_set_is_disjoint(ExistingWrittenUnknownZone.keep(),
                                   ProposedKnownDomain.keep())) {
      if (OS)
        dbgs().indent(Indent)
            << "Conflict of current unknown write to proposed\n";
      return true;
    }

    // Check 5b)
    auto ProposedWrittenUnknownZone = getUnknownValInstDomain(ProposedWritten);
    if (!isl_union_set_is_disjoint(ProposedWrittenUnknownZone.keep(),
                                   ExistingKnownDomain.keep())) {
      if (OS)
        OS->indent(Indent) << "Conflict of proposed unknown write to current\n";
      return true;
    }

    // Check 6a)
    auto ExistingWrittenOverlap = give(isl_union_map_intersect_domain(
        ExistingWritten.copy(), ProposedKnownDomain.copy()));
    if (!isl_union_map_is_subset(ExistingWrittenOverlap.keep(),
                                 ProposedKnown.keep())) {
      if (OS)
        OS->indent(Indent) << "Conflict of current write to proposed known\n";
      return true;
    }

    // Check 6b)
    auto ProposedWrittenOverlap = give(isl_union_map_intersect_domain(
        ProposedWritten.copy(), ExistingKnownDomain.copy()));
    if (!isl_union_map_is_subset(ProposedWrittenOverlap.keep(),
                                 ExistingKnown.keep())) {
      if (OS)
        OS->indent(Indent) << "Conflict of proposed write to current known\n";
      return true;
    }

    // Check 7)
    auto ExistingWrittenDomain =
        give(isl_union_map_domain(Existing.Written.copy()));
    auto ProposedWrittenDomain =
        give(isl_union_map_domain(Proposed.Written.copy()));
    auto WriteOverlap = give(isl_union_set_intersect(
        ExistingWrittenDomain.copy(), ProposedWrittenDomain.copy()));
    auto ExistingOverlapOverwrite = give(isl_union_map_intersect_domain(
        Existing.Written.copy(), WriteOverlap.copy()));
    auto ProposedOverlapOverwrite = give(isl_union_map_intersect_domain(
        Proposed.Written.copy(), WriteOverlap.copy()));

    if (!isl_union_map_is_equal(ExistingOverlapOverwrite.keep(),
                                ProposedOverlapOverwrite.keep())) {
      if (OS) {
        OS->indent(Indent)
            << "Conflict because of existing/proposed undefined write order\n";
        // Note that if eg. Existing writes two values, one of which is also
        // written by Proposed, that value is removed from
        // ExistingConflictingOverwrite, st. it seems the value in Proposed does
        // not conflict with anything. The isl_union_map_is_equal above still
        // fails (and has to!)
        auto ExistingConflictingOverwrite = isl_union_map_subtract(
            ExistingOverlapOverwrite.copy(), ProposedOverlapOverwrite.copy());
        auto ProposedConflictingOverwrite = isl_union_map_subtract(
            ProposedOverlapOverwrite.copy(), ExistingOverlapOverwrite.copy());
        OS->indent(Indent + 2)
            << "Existing wants to write: " << ExistingConflictingOverwrite
            << '\n';
        OS->indent(Indent + 2)
            << "Proposed wants to write: " << ProposedConflictingOverwrite
            << '\n';
      }
      return true;
    }

    auto ExistingWrittenUnknown = getUnknownValInstDomain(Existing.Written);
    if (!isl_union_set_is_disjoint(ExistingWrittenUnknown.keep(),
                                   ProposedWrittenDomain.keep())) {
      if (OS)
        OS->indent(Indent) << "Existing writes unknown with undefined order to "
                              "proposed write\n";
      return true;
    }

    auto ProposedWrittenUnknown = getUnknownValInstDomain(Proposed.Written);
    if (!isl_union_set_is_disjoint(ProposedWrittenUnknown.keep(),
                                   ExistingWrittenDomain.keep())) {
      if (OS)
        OS->indent(Indent) << "Existing writes with undefined order to "
                              "proposed write unknown\n";
      return true;
    }

    return false;
  }
};

void Knowledge::dump() const { print(llvm::errs()); }

/// Base class for algorithms based on zones, like DeLICM.
class ZoneAlgorithm {
protected:
private:
  /// Cached reaching definitions for each ScopStmt.
  ///
  /// Use getScalarReachingDefinition() to get its contents.
  DenseMap<ScopStmt *, IslPtr<isl_map>> ScalarReachDefZone;

protected:
  /// The isl_ctx used for all computations.
  isl_ctx *IslCtx;

  /// The analyzed Scop.
  Scop *S;

  /// Parameter space that does not need realignment.
  IslPtr<isl_space> ParamSpace;

  /// Space the schedule maps to.
  IslPtr<isl_space> ScatterSpace;

  /// Cached version of the schedule and domains.
  IslPtr<isl_union_map> Schedule;

  /// As many isl_union_maps are initialized empty, this can be used to increase
  /// only a reference a counter, instead of creating an entirely new
  /// isl_union_map.
  IslPtr<isl_union_map> EmptyUnionMap;

  /// As many isl_union_sets are initialized empty, this can be used to increase
  /// only a reference a counter, instead of creating an entirely new
  /// isl_union_set.
  IslPtr<isl_union_set> EmptyUnionSet;

  /// Set of all referenced elements.
  /// { Element[] -> Element[] }
  IslPtr<isl_union_set> AllElements;

  /// Combined access relations of all MK_Array READ accesses.
  /// { DomainRead[] -> Element[] }
  IslPtr<isl_union_map> AllReads;

  /// Combined access relations of all MK_Array, MAY_WRITE accesses.
  /// { DomainMayWrite[] -> Element[] }
  IslPtr<isl_union_map> AllMayWrites;

  /// Combined access relations of all MK_Array, MUST_WRITE accesses.
  /// { DomainMustWrite[] -> Element[] }
  IslPtr<isl_union_map> AllMustWrites;

  ///  Combined access relations of all MK_Array write accesses (union of
  ///  AllMayWrites and AllMustWrites).
  /// { DomainWrite[] -> Element[] }
  IslPtr<isl_union_map> AllWrites;

  /// The value instances written to array elements of all write accesses.
  /// { [Element[] -> DomainWrite[]] -> ValInst[] }
  IslPtr<isl_union_map> AllWriteValInst;

  // { [Element[] -> DomainRead[]] -> ValInst[] }
  IslPtr<isl_union_map> AllReadValInst;

  /// All reaching definitions for MK_Array writes.
  /// { [Element[] -> Zone[]] -> DomainWrite[] }
  IslPtr<isl_union_map> WriteReachDefZone;

  /// Prepare the object before computing the zones of @p S.
  ZoneAlgorithm(Scop *S)
      : IslCtx(S->getIslCtx()), S(S), Schedule(give(S->getSchedule())) {

    auto Domains = give(S->getDomains());

    Schedule =
        give(isl_union_map_intersect_domain(Schedule.take(), Domains.take()));
    ParamSpace = give(isl_union_map_get_space(Schedule.keep()));
    ScatterSpace = getScatterSpace(Schedule);

    EmptyUnionMap = give(isl_union_map_empty(ParamSpace.copy()));
    EmptyUnionSet = give(isl_union_set_empty(ParamSpace.copy()));
  }

private:
  /// Of all the llvm::Values that represent the same content, try to find an
  /// unique one.
  ///
  /// PHI nodes with just one incoming block are introduced by LCSSA. All other
  /// exact copy instructions (eg. bitwise 'or' with zero) should be removed by
  /// InstCombine.
  ///
  /// Without this normalization, the two values would be considered different,
  /// leading to less optimization opportunities.
  Value *deLCSSA(Value *Val) {
    if (!Val)
      return Val;

    if (auto *PHI = dyn_cast<PHINode>(Val)) {
      Value *NormVal = nullptr;
      for (auto &Use : PHI->incoming_values()) {
        auto InVal = Use.get();
        assert(InVal);

        if (isa<UndefValue>(InVal))
          continue;

        if (NormVal && NormVal != InVal)
          return Val;

        NormVal = Val;
      }
      if (NormVal)
        return NormVal;
    }

    return Val;
  }

  /// Determine whether an instruction is defined in a different statement
  /// instance as in which it is used.
  ///
  /// We here assume that a BB/region cannot use a definition in the same
  /// BB/region, which would be theoretically possible in loops within region
  /// statements and with disconnected loops:
  /// BB:
  ///   ... = add i32 %def, 5
  ///   %def = ...
  ///   br label %BB
  ///
  /// @param Val      The instruction defining a value.
  /// @param UserStmt The statement using @p Val. The use must not be a PHI,
  ///                 they must handled separately.
  ///
  /// @return True iff a use of @p Val in @p UserStmt introduces a
  ///         flow-dependency.
  bool isXtraStmtUse(Value *Val, ScopStmt *UserStmt) const {
    assert(UserStmt);
    auto *Inst = dyn_cast<Instruction>(Val);

    // Non-instruction like literals do not add inter-stmt dependencies.
    if (!Inst)
      return false;

    auto *DefStmt = S->getStmtFor(Inst);

    // Read-only uses do not add inter-stmt dependencies.
    if (!DefStmt)
      return false;

    // This assumes that there must be a PHI in the same statement if we are
    // going to use a value from a previous execution of the same statement.
    return DefStmt != UserStmt;
  }

  /// Check whether @p Stmt can be accurately analyzed by zones.
  ///
  /// What violates our assumptions:
  /// - A load after a write of the same location; we assume that all reads
  ///   occur before the writes.
  /// - Two writes to the same location; we cannot model the order in which
  ///   these occur.
  ///
  /// Scalar reads implicitly always occur before other access therefore never
  /// violate the first condition. There is also at most one write to a scalar,
  /// satisfying the second condition.
  bool isCompatibleStmt(ScopStmt *Stmt) {
    auto Stores = EmptyUnionMap;
    auto Loads = EmptyUnionMap;

    // This assumes that the MK_Array MemoryAccesses are iterated in order.
    for (auto *MA : *Stmt) {
      if (!MA->isLatestArrayKind())
        continue;

      auto AccRel =
          give(isl_union_map_from_map(getAccessRelationFor(MA).take()));

      if (MA->isRead()) {
        // Reject store after load to same location.
        if (!isl_union_map_is_disjoint(Stores.keep(), AccRel.keep()))
          return false;

        Loads = give(isl_union_map_union(Loads.take(), AccRel.take()));
      }

      if (MA->isWrite()) {
        if (!isa<StoreInst>(MA->getAccessInstruction())) {
          DEBUG(dbgs() << "WRITE that is not a StoreInst not supported\n");
          return false;
        }

        // In region statements the order is less clear, eg. the load and store
        // might be in a boxed loop.
        if (Stmt->isRegionStmt() &&
            !isl_union_map_is_disjoint(Loads.keep(), AccRel.keep()))
          return false;

        // Do not allow more than one store to the same location.
        if (!isl_union_map_is_disjoint(Stores.keep(), AccRel.keep()))
          return false;

        Stores = give(isl_union_map_union(Stores.take(), AccRel.take()));
      }
    }

    return true;
  }

  void addArrayReadAccess(MemoryAccess *MA) {
    assert(MA->isLatestArrayKind());
    assert(MA->isRead());
    auto *Stmt = MA->getStatement();

    // { DomainRead[] -> Element[] }
    auto AccRel = getAccessRelationFor(MA);
    AllReads = give(isl_union_map_add_map(AllReads.take(), AccRel.copy()));

    auto LI = dyn_cast_or_null<LoadInst>(MA->getAccessInstruction());
    if (LI) {
      // { DomainRead[] -> ValInst[] }
      auto LoadValInst = makeValInst(LI, Stmt, Stmt->isBlockStmt());

      // { DomainRead[] -> [Element[] -> DomainRead[]] }
      auto IncludeElement =
          give(isl_map_curry(isl_map_domain_map(AccRel.take())));

      // { [Element[] -> DomainRead[]] -> ValInst[] }
      auto EltLoadValInst =
          give(isl_map_apply_domain(LoadValInst.take(), IncludeElement.take()));

      AllReadValInst = give(
          isl_union_map_add_map(AllReadValInst.take(), EltLoadValInst.take()));
    }
  }

  void addArrayWriteAccess(MemoryAccess *MA) {
    assert(MA->isLatestArrayKind());
    assert(MA->isWrite());
    auto *Stmt = MA->getStatement();

    // { Domain[] -> Element[] }
    auto AccRel = getAccessRelationFor(MA);

    if (MA->isMustWrite()) {
      AllMustWrites =
          give(isl_union_map_add_map(AllMustWrites.take(), AccRel.copy()));
    }
    if (MA->isMayWrite()) {
      AllMayWrites =
          give(isl_union_map_add_map(AllMayWrites.take(), AccRel.copy()));
    }

    // { Domain[] -> ValInst[] }
    auto WriteValInstance =
        makeValInst(MA->getAccessValue(), Stmt, MA->isMustWrite());

    // { Domain[] -> [Element[] -> Domain[]] }
    auto IncludeElement =
        give(isl_map_curry(isl_map_domain_map(AccRel.copy())));

    // { [Element[] -> DomainWrite[]] -> ValInst[] }
    auto EltWriteValInst = give(
        isl_map_apply_domain(WriteValInstance.take(), IncludeElement.take()));

    AllWriteValInst = give(
        isl_union_map_add_map(AllWriteValInst.take(), EltWriteValInst.take()));
  }

protected:
  /// Get the schedule for @p Stmt.
  ///
  /// The domain of the result will as narrow as possible.
  IslPtr<isl_map> getScatterFor(ScopStmt *Stmt) const {
    auto ResultSpace = give(isl_space_map_from_domain_and_range(
        Stmt->getDomainSpace(), ScatterSpace.copy()));
    return give(isl_union_map_extract_map(Schedule.keep(), ResultSpace.take()));
  }

  /// Get the schedule of @p MA's parent statement.
  IslPtr<isl_map> getScatterFor(MemoryAccess *MA) const {
    return getScatterFor(MA->getStatement());
  }

  /// Get the schedule for the statement instances of @p Domain.
  IslPtr<isl_union_map> getScatterFor(IslPtr<isl_union_set> Domain) const {
    return give(isl_union_map_intersect_domain(Schedule.copy(), Domain.take()));
  }

  /// Get the schedule for the statement instances of @p Domain.
  IslPtr<isl_map> getScatterFor(IslPtr<isl_set> Domain) const {
    auto ResultSpace = give(isl_space_map_from_domain_and_range(
        isl_set_get_space(Domain.keep()), ScatterSpace.copy()));
    auto UDomain = give(isl_union_set_from_set(Domain.copy()));
    auto UResult = getScatterFor(std::move(UDomain));
    auto Result = singleton(std::move(UResult), std::move(ResultSpace));
    assert(isl_set_is_equal(give(isl_map_domain(Result.copy())).keep(),
                            Domain.keep()) == isl_bool_true);
    return Result;
  }

  /// Get the domain of @p Stmt.
  IslPtr<isl_set> getDomainFor(ScopStmt *Stmt) const {
    return give(Stmt->getDomain());
  }

  /// Get the domain @p MA's parent statement.
  IslPtr<isl_set> getDomainFor(MemoryAccess *MA) const {
    return getDomainFor(MA->getStatement());
  }

  /// get the access relation of @p MA.
  ///
  /// The domain of the result will as narrow as possible.
  IslPtr<isl_map> getAccessRelationFor(MemoryAccess *MA) const {
    auto Domain = getDomainFor(MA);
    auto AccRel = give(MA->getLatestAccessRelation());
    return give(isl_map_intersect_domain(AccRel.take(), Domain.take()));
  }

  /// Get the reaching definition of a scalar defined in @p Stmt.
  ///
  /// Note that this does not depend on the llvm::Instruction, only on the
  /// statement it is defined in. Therefore the same computation can be reused.
  ///
  /// @param Stmt The statement in which a scalar is defined.
  ///
  /// @return { Scatter[] -> DomainDef[] }
  IslPtr<isl_map> getScalarReachingDefinition(ScopStmt *Stmt) {
    auto &Result = ScalarReachDefZone[Stmt];
    if (Result)
      return Result;

    auto Domain = getDomainFor(Stmt);
    Result = computeScalarReachingDefinition(Schedule, Domain, false, true);
    simplify(Result);

    assert(Result);
    return Result;
  }

  /// Get the reaching definition of a scalar defined in @p DefDomain.
  ///
  /// @param DomainDef { DomainDef[] }
  ///              The write statements to get the reaching definition for.
  ///
  /// @return { Scatter[] -> DomainDef[] }
  IslPtr<isl_map> getScalarReachingDefinition(IslPtr<isl_set> DomainDef) {
    auto DomId = give(isl_set_get_tuple_id(DomainDef.keep()));
    auto *Stmt = static_cast<ScopStmt *>(isl_id_get_user(DomId.keep()));

    auto StmtResult = getScalarReachingDefinition(Stmt);

    return give(isl_map_intersect_range(StmtResult.take(), DomainDef.take()));
  }

  /// Create an isl_id that means 'don't know the value'.
  IslPtr<isl_id> makeUnknownId() const { return nullptr; }

  /// Create an isl_space for unknown values.
  IslPtr<isl_space> makeUnknownSpace() const {
    return give(isl_space_set_from_params(ParamSpace.copy()));
  }

  /// Create a set with an unknown value in it.
  IslPtr<isl_set> makeUnknownSet() const {
    auto Space = makeUnknownSpace();
    return give(isl_set_universe(Space.take()));
  }

  /// Create a union set with an unknown value in it.
  IslPtr<isl_union_set> makeUnknownUSet() const {
    return give(isl_union_set_from_set(makeUnknownSet().take()));
  }

  /// Create a domain-to-unknown value mapping.
  ///
  /// @param Domain { Domain[] }
  ///
  /// @return { Domain[] -> ValInst[] }
  IslPtr<isl_map> makeUnknownForDomain(IslPtr<isl_set> Domain) const {
    return give(isl_map_from_domain(Domain.take()));
  }

  /// Create a statement-to-unknown value mapping.
  ///
  /// @param Stmt The statement whose instances are mapped to unknown.
  ///
  /// @return { Domain[] -> ValInst[] }
  IslPtr<isl_map> makeUnknownForDomain(ScopStmt *Stmt) const {
    return give(isl_map_from_domain(getDomainFor(Stmt).take()));
  }

  /// Create a domain-to-unknown value mapping.
  ///
  /// @param Domain { Domain[] }
  ///
  /// @return { Domain[] -> ValInst[] }
  IslPtr<isl_union_map>
  makeUnknownForDomain(IslPtr<isl_union_set> Domain) const {
    return give(isl_union_map_from_domain(Domain.take()));
  }

  /// Create an isl_id that represents 'unused storage'.
  IslPtr<isl_id> makeUndefId() const {
    auto &LLVMContext = S->getFunction().getContext();
    auto Ty = IntegerType::get(LLVMContext, 1);
    auto Val = UndefValue::get(Ty);
    return give(isl_id_alloc(IslCtx, "Undef", Val));
  }

  /// Create an isl_space for an undefined value.
  IslPtr<isl_space> makeUndefSpace() const {
    auto Result = give(isl_space_set_from_params(ParamSpace.copy()));
    return give(isl_space_set_tuple_id(Result.take(), isl_dim_set,
                                       makeUndefId().take()));
  }

  /// Create a set with an undefined value in it.
  IslPtr<isl_set> makeUndefSet() const {
    auto Space = makeUndefSpace();
    return give(isl_set_universe(Space.take()));
  }

  /// Create a union set with an undefined value in it.
  IslPtr<isl_union_set> makeUndefUSet() const {
    return give(isl_union_set_from_set(makeUndefSet().take()));
  }

  /// Create an isl_id that represents @p V.
  IslPtr<isl_id> makeValueId(Value *V) const {
    if (!V)
      return makeUnknownId();
    if (isa<UndefValue>(V))
      return makeUndefId();

    auto Name = getIslCompatibleName("Val_", V, std::string());
    return give(isl_id_alloc(IslCtx, Name.c_str(), V));
  }

  /// Create the space for an llvm::Value that is available everywhere.
  IslPtr<isl_space> makeValueSpace(Value *V) const {
    auto Result = give(isl_space_set_from_params(ParamSpace.copy()));
    return give(isl_space_set_tuple_id(Result.take(), isl_dim_set,
                                       makeValueId(V).take()));
  }

  /// Create a set with the llvm::Value @p V which is available everywhere.
  IslPtr<isl_set> makeValueSet(Value *V) const {
    auto Space = makeValueSpace(V);
    return give(isl_set_universe(Space.take()));
  }

  // { UserDomain[] -> ValInst[] }
  IslPtr<isl_map> makeValInst(Value *Val, ScopStmt *UserStmt,
                              bool IsCertain = true) {
    return makeValInst(Val, nullptr, UserStmt, getDomainFor(UserStmt),
                       IsCertain);
  }

  /// Create a mapping from a statement instance to the instance of an
  /// llvm::Value that can be used in there.
  ///
  /// Although LLVM IR used single static assignment, llvm::Values can have
  /// different contents in loops, when they get redefined in the last
  /// iteration. This function tries to get the statement instance of the
  /// previous definition, relative to a user.
  ///
  /// Example:
  /// for (int i = 0; i < N; i += 1) {
  /// DEF:
  ///    int v = A[i];
  /// USE:
  ///    use(v);
  ///  }
  ///
  /// The value instance used by statement instance USE[i] is DEF[i]. Hence,
  /// makeValInst would return
  /// { USE[i] -> DEF[i] : 0 <= i < N }
  ///
  ///
  /// @param V           The value to look get the instance of.
  /// @param DomainDef  { DomainDef[] }
  ///                   The domain of the statement that defines @p V. If
  ///                   nullptr, will be derived automatically. If defined, the
  ///                   domain gets precedence over trying to use the
  ///                   llvm::Value instance from the same statement.
  /// @param UseStmt    The statement that uses @p V. Can be nullptr.
  /// @param DomainUse  { DomainUse[] }
  ///                   The domain of @p UseStmt.
  /// @param IsCertain  Pass true if the definition of @p V is a MUST_WRITE or
  /// false if the write is conditional.
  ///
  /// @return { DomainUse[] -> ValInst[] }
  IslPtr<isl_map> makeValInst(Value *V, IslPtr<isl_set> DomainDef,
                              ScopStmt *UseStmt, IslPtr<isl_set> DomainUse,
                              bool IsCertain = true) {
    assert(DomainUse && "Must pass a user domain");

    // If the definition/write is conditional, the previous write may "shine
    // through" on conditions we cannot determine. Again, return the unknown
    // value.
    if (!IsCertain)
      return give(isl_map_from_domain(DomainUse.take()));

    if (V && !isa<Instruction>(V)) {
      // Non-instructions are available anywhere.
      auto ValSet = makeValueSet(V);
      return give(
          isl_map_from_domain_and_range(DomainUse.take(), ValSet.take()));
    }

    // Normalize
    // FIXME: It doesn't really work well if the LCSSA %phi is intra-stmt, but
    // the incoming value is extra-phi.
    // TODO: In a SCoP, we should be able to determine the predecessor for
    // _every_ PHI.
    auto *NormV = deLCSSA(V);

    // If the definition is in the using Stmt itself, use DomainUse[] for the
    // Value's instance.
    // Note that the non-isIntraStmtUse assumes extra-Stmt use, ie. a use would
    // use the definition from a previous instance.
    if (!DomainDef && UseStmt && V && !isXtraStmtUse(V, UseStmt)) {
      // Even if V is within UseStmt, NormV might be somewhere else; return
      // unknown to avoid problems.
      if (V != NormV)
        return makeUnknownForDomain(DomainUse);

      // { llvm::Value }
      auto ValSet = makeValueSet(NormV);

      // {  UserDomain[] -> llvm::Value }
      auto ValInstSet =
          give(isl_map_from_domain_and_range(DomainUse.take(), ValSet.take()));

      // { UserDomain[] -> [UserDomain[] - >llvm::Value] }
      auto Result =
          give(isl_map_reverse(isl_map_domain_map(ValInstSet.take())));
      simplify(Result);
      return Result;
    }

    // Try to derive DomainDef if not explicitly specified.
    if (!DomainDef) {
      auto *Inst = cast<Instruction>(NormV);
      auto *ValStmt = S->getStmtFor(Inst);

      // It is possible that the llvm::Value is in a removed Stmt, in which case
      // we cannot derive its domain.
      if (ValStmt)
        DomainDef = getDomainFor(ValStmt);
    }

    if (DomainDef) {
      // { Scatter[] -> DefDomain[] }
      auto ReachDef = getScalarReachingDefinition(DomainDef);

      // { DomainUse[] -> Scatter[] }
      auto UserSched = getScatterFor(DomainUse);

      // { DomainUse[] -> DomainDef[] }
      auto UsedInstance =
          give(isl_map_apply_range(UserSched.take(), ReachDef.take()));

      // { llvm::Value }
      auto ValSet = makeValueSet(NormV);

      // { DomainUse[] -> llvm::Value }
      auto ValInstSet =
          give(isl_map_from_domain_and_range(DomainUse.take(), ValSet.take()));

      // { DomainUse[] -> [DomainDef[] -> llvm::Value]  }
      auto Result =
          give(isl_map_range_product(UsedInstance.take(), ValInstSet.take()));
      simplify(Result);
      return Result;
    }

    // If neither the value not the user if given, we cannot determine the
    // reaching definition; return value is unknown.
    return makeUnknownForDomain(DomainUse);
  }

  /// Compute the different zones.
  ///
  /// @return true iff the computed zones accurately describe the SCoP.
  /// Otherwise, do not try to use them.
  bool computeCommon() {
    // Check that nothing strange occurs.
    for (auto &Stmt : *S) {
      if (!isCompatibleStmt(&Stmt))
        return false;
    }

    AllReads = EmptyUnionMap;
    AllMayWrites = EmptyUnionMap;
    AllMustWrites = EmptyUnionMap;
    AllWriteValInst = EmptyUnionMap;
    AllReadValInst = EmptyUnionMap;
    for (auto &Stmt : *S) {
      for (auto *MA : Stmt) {
        if (!MA->isLatestArrayKind())
          continue;

        if (MA->isRead())
          addArrayReadAccess(MA);

        if (MA->isWrite())
          addArrayWriteAccess(MA);
      }
    }

    // { DomainWrite[] -> Element[] }
    AllWrites =
        give(isl_union_map_union(AllMustWrites.copy(), AllMayWrites.copy()));

    // { Element[] }
    AllElements = EmptyUnionSet;
    foreachElt(AllWrites, [this](IslPtr<isl_map> Write) {
      auto Space = give(isl_map_get_space(Write.keep()));
      auto EltSpace = give(isl_space_range(Space.take()));
      auto EltUniv = give(isl_set_universe(EltSpace.take()));
      AllElements =
          give(isl_union_set_add_set(AllElements.take(), EltUniv.take()));
    });

    // { Element[] -> Element[] }
    auto AllElementsId = makeIdentityMap(AllElements, false);

    // { Element[] -> Zone[] }
    auto UniverseZone = give(isl_union_map_from_domain_and_range(
        AllElements.copy(),
        isl_union_set_from_set(isl_set_universe(ScatterSpace.copy()))));

    // { [Element[] -> Zone[]] -> DomainWrite[] }
    WriteReachDefZone =
        computeReachingDefinition(Schedule, AllWrites, false, true);
    simplify(WriteReachDefZone);

    return true;
  }

  /// Print the current state of all MemoryAccesses to @p.
  void printAccesses(llvm::raw_ostream &OS, int Indent = 0) const {
    OS.indent(Indent) << "After accesses {\n";
    for (auto &Stmt : *S) {
      OS.indent(Indent + 4) << Stmt.getBaseName() << "\n";
      for (auto *MA : Stmt)
        MA->print(OS);
    }
    OS.indent(Indent) << "}\n";
  }

public:
  /// Return the SCoP this object is analyzing.
  Scop *getScop() const { return S; }
};

/// Class to remember a scalar-to-array element transformation for printing by
/// opt -analyze.
class MapReport {
private:
  /// The scalar that was mapped.
  const ScopArrayInfo *SAI;

  /// The definition of an MK_Value or read of an MK_PHI having been mapped.
  MemoryAccess *PrimaryAcc;

  /// The uses of an MK_Value or incoming writes of an MK_Value having been
  /// mapped.
  SmallVector<MemoryAccess *, 4> SecondaryAccs;

  /// Target mapping for the MK_Value write or MK_PHI read.
  /// { Domain[] -> Element[] }
  IslPtr<isl_map> Target;

  /// Lifetime expressed from the MK_Value write or MK_PHI read.
  /// { Domain[] -> Zone[] }
  IslPtr<isl_map> Lifetime;

  /// The constants that were checked before the transformation/applied to the
  /// common knowledge after the transformation.
  Knowledge Proposed;

public:
  MapReport(const ScopArrayInfo *SAI, MemoryAccess *PrimaryAcc,
            ArrayRef<MemoryAccess *> SecondaryAccs, IslPtr<isl_map> Target,
            IslPtr<isl_map> Lifetime, Knowledge Zone)
      : SAI(SAI), PrimaryAcc(PrimaryAcc),
        SecondaryAccs(SecondaryAccs.begin(), SecondaryAccs.end()),
        Target(std::move(Target)), Lifetime(std::move(Lifetime)),
        Proposed(std::move(Zone)) {
    assert(SAI);
    DEBUG(print(llvm::dbgs(), 0));
  }

  /// Print this transformation report to @p OS.
  void print(llvm::raw_ostream &OS, int Indent = 0) const {
    OS.indent(Indent) << "Mapping of " << SAI << " {\n";
    if (PrimaryAcc)
      OS.indent(Indent + 4) << "Primary:   " << PrimaryAcc << "\n";
    for (auto *MA : SecondaryAccs)
      OS.indent(Indent + 4) << "Secondary: " << MA << "\n";
    OS.indent(Indent + 4) << "Target:    " << Target << "\n";
    OS.indent(Indent + 4) << "Lifetime:  " << Lifetime << "\n";
    OS.indent(Indent + 4) << "Zone:\n";
    Proposed.print(OS, Indent + 8);
    OS.indent(Indent) << "}\n";
  }
};

/// Implementation of the DeLICM/DePRE transformation.
class DeLICMImpl : public ZoneAlgorithm {
private:
  /// Knowledge before any transformation took place.
  Knowledge OriginalZone;

  /// Current knowledge of the SCoP including all already applied
  /// transformations.
  Knowledge Zone;

  /// Log of every applied mapping transformations.
  SmallVector<MapReport, 8> MapReports;

  ScalarDefUseChains DefUse;

  /// Determine whether to knowledges are conflicting each other.
  ///
  /// @see Knowledge::isConflicting
  bool isConflicting(const Knowledge &Proposed) {
    raw_ostream *OS = nullptr;
    DEBUG(OS = &llvm::dbgs());
    return Knowledge::isConflicting(Zone, Proposed, OS, 4);
  }

  /// Determine whether @p SAI is a scalar that can be mapped to an array
  /// element.
  bool isMappable(const ScopArrayInfo *SAI) {
    assert(SAI);

    if (SAI->isValueKind()) {
      auto *MA = DefUse.getValueDef(SAI);
      if (!MA) {
        DEBUG(dbgs()
              << "    Reject because value is read-only within the scop\n");
        return false;
      }

      // Mapping if value is used after scop is not supported. The code
      // generator would need to reload the scalar after the scop, but it
      // doesn't have the information to where it is mapped to. Only the
      // MemoryAccesses have that information, not the ScopArrayInfo.
      auto Inst = MA->getAccessInstruction();
      for (auto User : Inst->users()) {
        if (!isa<Instruction>(User))
          return false;
        auto UserInst = cast<Instruction>(User);

        if (!S->contains(UserInst)) {
          DEBUG(dbgs() << "    Reject because value is escaping\n");
          return false;
        }
      }

      return true;
    }

    if (SAI->isPHIKind()) {
      auto *MA = DefUse.getPHIRead(SAI);
      assert(MA);

      // Mapping of an incoming block from before the SCoP is not supported by
      // the code generator.
      auto PHI = cast<PHINode>(MA->getAccessInstruction());
      for (auto Incoming : PHI->blocks()) {
        if (!S->contains(Incoming)) {
          DEBUG(dbgs() << "    Reject because at least one incoming block is "
                          "not in the scop region\n");
          return false;
        }
      }

      return true;
    }

    DEBUG(dbgs() << "    Reject ExitPHI or other non-value\n");
    return false;
  }

  /// Compute the uses of an MK_Value and its lifetime (from its definition to
  /// the last use).
  ///
  /// @param SAI The ScopArrayInfo representing the value's storage.
  ///
  /// @return { DomainDef[] -> DomainUse[] }, { DomainDef[] -> Zone[] }
  ///         First element is the this of uses for each definition.
  ///         The second is the lifetime of each definition.
  std::tuple<IslPtr<isl_union_map>, IslPtr<isl_map>>
  computeValueUses(const ScopArrayInfo *SAI) {
    assert(SAI->isValueKind());

    // { DomainRead[] }
    auto Reads = EmptyUnionSet;

    // Find all uses.
    for (auto *MA : DefUse.getValueUses(SAI))
      Reads =
          give(isl_union_set_add_set(Reads.take(), getDomainFor(MA).take()));

    // { DomainRead[] -> Scatter[] }
    auto ReadSchedule = getScatterFor(Reads);

    auto *DefMA = DefUse.getValueDef(SAI);
    assert(DefMA);

    // { DomainDef[] }
    auto Writes = getDomainFor(DefMA);

    // { DomainDef[] -> Scatter[] }
    auto WriteScatter = getScatterFor(Writes);

    // { Scatter[] -> DomainDef[] }
    auto ReachDef = getScalarReachingDefinition(DefMA->getStatement());

    // { [DomainDef[] -> Scatter[]] -> DomainUse[] }
    auto Uses = give(
        isl_union_map_apply_range(isl_union_map_from_map(isl_map_range_map(
                                      isl_map_reverse(ReachDef.take()))),
                                  isl_union_map_reverse(ReadSchedule.take())));

    // { DomainDef[] -> Scatter[] }
    auto UseScatter =
        singleton(give(isl_union_set_unwrap(isl_union_map_domain(Uses.copy()))),
                  give(isl_space_map_from_domain_and_range(
                      isl_set_get_space(Writes.keep()), ScatterSpace.copy())));

    // { DomainDef[] -> Zone[] }
    auto Lifetime = betweenScatter(WriteScatter, UseScatter, false, true);

    // { DomainDef[] -> DomainRead[] }
    auto DefUses = give(isl_union_map_domain_factor_domain(Uses.take()));

    return std::make_pair(DefUses, Lifetime);
  }

  /// For each 'execution' of a PHINode, get the incoming block that was
  /// executed before.
  ///
  /// For each PHI instance we can directly determine which was the incoming
  /// block, and hence derive which value the PHI will have.
  ///
  /// @param SAI The ScopArrayInfo representing the PHI's storage.
  ///
  /// @return { DomainPHIRead[] -> DomainPHIWrite[] }
  IslPtr<isl_union_map> computePerPHI(const ScopArrayInfo *SAI) {
    assert(SAI->isPHIKind());

    // { DomainPHIWrite[] -> Scatter[] }
    auto PHIWriteScatter = EmptyUnionMap;

    // Collect all incoming block timepoint.
    for (auto *MA : DefUse.getPHIIncomings(SAI)) {
      auto Scatter = getScatterFor(MA);
      PHIWriteScatter =
          give(isl_union_map_add_map(PHIWriteScatter.take(), Scatter.take()));
    }

    // { DomainPHIRead[] -> Scatter[] }
    auto PHIReadScatter = getScatterFor(DefUse.getPHIRead(SAI));

    // { DomainPHIRead[] -> Scatter[] }
    auto BeforeRead = beforeScatter(PHIReadScatter, true);

    // { Scatter[] }
    auto WriteTimes = singleton(
        give(isl_union_map_range(PHIWriteScatter.copy())), ScatterSpace);

    // { DomainPHIRead[] -> Scatter[] }
    auto PHIWriteTimes =
        give(isl_map_intersect_range(BeforeRead.take(), WriteTimes.take()));
    simplify(PHIWriteTimes);
    auto LastPerPHIWrites = give(isl_map_lexmax(PHIWriteTimes.take()));

    // { DomainPHIRead[] -> DomainPHIWrite[] }
    auto Result = give(isl_union_map_apply_range(
        isl_union_map_from_map(LastPerPHIWrites.take()),
        isl_union_map_reverse(PHIWriteScatter.take())));
    assert(isl_union_map_is_single_valued(Result.keep()) == isl_bool_true);
    assert(isl_union_map_is_injective(Result.keep()) == isl_bool_true);
    return Result;
  }

  /// Try to map a MK_Value to a given array element.
  ///
  /// @param SAI       Representation of the scalar's memory to map.
  /// @param TargetElt { Scatter[] -> Element[] }
  ///                  Suggestion where to map a scalar to when at a timepoint.
  ///
  /// @return true if the scalar was successfully mapped.
  bool tryMapValue(const ScopArrayInfo *SAI, IslPtr<isl_map> TargetElt) {
    assert(SAI->isValueKind());

    auto *DefMA = DefUse.getValueDef(SAI);
    assert(DefMA->isValueKind());
    assert(DefMA->isMustWrite());
    auto *V = DefMA->getAccessValue();

    // Stop if the scalar has already been mapped.
    if (!DefMA->getLatestScopArrayInfo()->isValueKind())
      return false;

    // { DomainDef[] -> Scatter[] }
    auto DefSched = getScatterFor(DefMA);

    // Where each write is mapped to, according to the suggestion.
    // { DomainDef[] -> Element[] }
    auto DefTarget = give(isl_map_apply_domain(
        TargetElt.copy(), isl_map_reverse(DefSched.copy())));
    simplify(DefTarget);
    DEBUG(dbgs() << "    Def Mapping: " << DefTarget << '\n');

    auto OrigDomain = getDomainFor(DefMA);
    auto MappedDomain = give(isl_map_domain(DefTarget.copy()));
    if (!isl_set_is_subset(OrigDomain.keep(), MappedDomain.keep())) {
      DEBUG(dbgs()
            << "    Reject because mapping does not encompass all instances\n");
      return false;
    }

    // { DomainDef[] -> Zone[] }
    IslPtr<isl_map> Lifetime;

    // { DomainDef[] -> DomainUse[] }
    IslPtr<isl_union_map> DefUses;

    std::tie(DefUses, Lifetime) = computeValueUses(SAI);
    simplify(Lifetime);
    DEBUG(dbgs() << "    Lifetime: " << Lifetime << '\n');

    // { DomainDef[] -> [Element[] -> Zone[]] }
    auto EltLifetimeTranslator =
        give(isl_map_range_product(DefTarget.copy(), Lifetime.copy()));

    // { DomainDef[] -> [Element[] -> Scatter[]] }
    auto WrittenTranslator =
        give(isl_map_range_product(DefTarget.copy(), DefSched.take()));

    // { DomainDef[] -> ValInst[] }
    auto ValInst = makeValInst(V, DefMA->getStatement(), true);

    // { [Element[] -> Zone[]] -> ValInst[] }
    auto EltLifetime = give(
        isl_map_apply_domain(ValInst.copy(), EltLifetimeTranslator.take()));

    // { [Element[] -> Scatter[]] -> ValInst[] }
    auto EltWriteAction =
        give(isl_map_apply_domain(ValInst.copy(), WrittenTranslator.take()));

    Knowledge Proposed(std::move(EltLifetime), false,
                       std::move(EltWriteAction));
    if (isConflicting(Proposed))
      return false;

    // { DomainUse[] -> Element[] }
    auto UseTarget = give(
        isl_union_map_apply_range(isl_union_map_reverse(DefUses.take()),
                                  isl_union_map_from_map(DefTarget.copy())));

    mapValue(SAI, std::move(DefTarget), std::move(UseTarget),
             std::move(Lifetime), std::move(Proposed));
    return true;
  }

  /// After a scalar has been mapped, update the global knowledge.
  void applyLifetime(Knowledge Proposed) {
    Zone.merge_inplace(std::move(Proposed));
  }

  /// Map a MK_Value scalar to an array element.
  ///
  /// Callers must have ensured that the mapping is valid and not conflicting.
  ///
  /// @param SAI       The ScopArrayInfo representing the scalar's memory to
  /// map.
  /// @param DefTarget { DomainDef[] -> Element[] }
  ///                  The array element to map the scalar to.
  /// @param UseTarget { DomainUse[] -> Element[] }
  ///                  The array elements the uses are mapped to.
  /// @param Lifetime  { DomainDef[] -> Zone[] }
  ///                  The lifetime of each llvm::Value definition for
  ///                  reporting.
  /// @param Proposed  Mapping constraints for reporting.
  void mapValue(const ScopArrayInfo *SAI, IslPtr<isl_map> DefTarget,
                IslPtr<isl_union_map> UseTarget, IslPtr<isl_map> Lifetime,
                Knowledge Proposed) {
    // Redirect the use accesses.
    SmallVector<MemoryAccess *, 4> SecondaryAccs;
    for (auto *MA : DefUse.getValueUses(SAI)) {
      // { DomainUse[] }
      auto Domain = getDomainFor(MA);

      // { DomainUse[] -> Element[] }
      auto NewAccRel = give(isl_union_map_intersect_domain(
          UseTarget.copy(), isl_union_set_from_set(Domain.take())));
      simplify(NewAccRel);

      assert(isl_union_map_n_map(NewAccRel.keep()) == 1);
      MA->setNewAccessRelation(isl_map_from_union_map(NewAccRel.take()));
      SecondaryAccs.push_back(MA);
    }

    auto *WA = DefUse.getValueDef(SAI);
    WA->setNewAccessRelation(DefTarget.copy());
    applyLifetime(Proposed);

    MappedValueScalars++;
    MapReports.emplace_back(SAI, WA, SecondaryAccs, DefTarget, Lifetime,
                            std::move(Proposed));
  }

  /// Get the all the statement instances of any statement for which there is at
  /// least one instance in @p RelevantDomain.
  IslPtr<isl_union_set>
  wholeStmtDomain(NonowningIslPtr<isl_union_set> RelevantDomain) {
    auto Universe = EmptyUnionSet;
    foreachElt(RelevantDomain, [&Universe](IslPtr<isl_set> Dom) {
      auto Space = give(isl_set_get_space(Dom.keep()));
      auto DomUniv = give(isl_set_universe(Space.take()));
      Universe = give(isl_union_set_add_set(Universe.take(), DomUniv.take()));
    });
    return give(isl_union_set_intersect(Universe.take(),
                                        isl_union_map_domain(Schedule.copy())));
  }

  /// Try to find a 'natural' extension of a mapped to elements outside its
  /// domain.
  ///
  /// @see ::expandMapping
  IslPtr<isl_union_map> expandMapping(IslPtr<isl_union_map> Relevant) {
    auto RelevantDomain = give(isl_union_map_domain(Relevant.copy()));
    auto Universe = wholeStmtDomain(RelevantDomain);
    return ::expandMapping(Relevant, Universe);
  }

  /// Express the incoming values of a PHI for each incoming statement in an
  /// isl_union_map.
  ///
  /// @param SAI The PHI scalar represented by a ScopArrayInfo.
  ///
  /// @return { PHIWriteDomain[] -> ValInst[] }
  IslPtr<isl_union_map> determinePHIWrittenValues(const ScopArrayInfo *SAI) {
    auto Result = EmptyUnionMap;

    // Collect the incoming values.
    for (auto *MA : DefUse.getPHIIncomings(SAI)) {
      // { DomainWrite[] -> ValInst[] }
      IslPtr<isl_map> ValInst;
      auto *WriteStmt = MA->getStatement();

      auto Incoming = MA->getIncoming();
      assert(!Incoming.empty());
      if (Incoming.size() == 1) {
        ValInst = makeValInst(Incoming[0].second, WriteStmt, true);
      } else {
        // If the PHI is in a subregion's exit node it can have multiple
        // incoming values (+ maybe another incoming edge from an unrelated
        // block. Since we cannot directly represent it as a single
        // llvm::Value from multiple exiting block, it is represented using
        // the PHI itself.
        // We currently model it as unknown value, but modeling as the PHIInst
        // itself could be OK, too.
        ValInst = makeUnknownForDomain(WriteStmt);
      }

      Result = give(isl_union_map_add_map(Result.take(), ValInst.take()));
    }

    assert(isl_union_map_is_single_valued(Result.keep()) == isl_bool_true &&
           "Cannot have multiple incoming values for same incoming statement");
    return Result;
  }

  /// Try to map a MK_PHI scalar to a given array element.
  ///
  /// @param SAI       Representation of the scalar's memory to map.
  /// @param TargetElt { Scatter[] -> Element[] }
  ///                  Suggestion where to map the scalar to when at a
  ///                  timepoint.
  ///
  /// @return true if the PHI scalar has been mapped.
  bool tryMapPHI(const ScopArrayInfo *SAI, IslPtr<isl_map> TargetElt) {
    auto *PHIRead = DefUse.getPHIRead(SAI);
    assert(PHIRead->isPHIKind());
    assert(PHIRead->isRead());

    // Skip if already been mapped.
    if (!PHIRead->getLatestScopArrayInfo()->isPHIKind())
      return false;

    // { DomainRead[] -> Scatter[] }
    auto PHISched = getScatterFor(PHIRead);

    // { DomainRead[] -> Element[] }
    auto PHITarget =
        give(isl_map_apply_range(PHISched.copy(), TargetElt.copy()));
    simplify(PHITarget);
    DEBUG(dbgs() << "    Mapping: " << PHITarget << '\n');

    auto OrigDomain = getDomainFor(PHIRead);
    auto MappedDomain = give(isl_map_domain(PHITarget.copy()));
    if (!isl_set_is_subset(OrigDomain.keep(), MappedDomain.keep())) {
      DEBUG(dbgs()
            << "    Reject because mapping does not encompass all instances\n");
      return false;
    }

    // { DomainRead[] -> DomainWrite[] }
    auto PerPHIWrites = computePerPHI(SAI);

    // { DomainWrite[] -> Element[] }
    auto RelevantWritesTarget =
        give(isl_union_map_reverse(isl_union_map_apply_domain(
            PerPHIWrites.copy(), isl_union_map_from_map(PHITarget.copy()))));

    simplify(RelevantWritesTarget);
    auto ExpandedTargetWrites = expandMapping(RelevantWritesTarget);

    // { DomainWrite[] }
    auto ExpandedWritesDom =
        give(isl_union_map_domain(ExpandedTargetWrites.copy()));
    auto UniverseWritesDom = give(isl_union_set_empty(ParamSpace.copy()));

    for (auto *MA : DefUse.getPHIIncomings(SAI))
      UniverseWritesDom = give(isl_union_set_add_set(UniverseWritesDom.take(),
                                                     getDomainFor(MA).take()));

    if (!isl_union_set_is_subset(UniverseWritesDom.keep(),
                                 ExpandedWritesDom.keep())) {
      DEBUG(dbgs() << "    Reject because did not find PHI write mapping for "
                      "all instances\n");
      DEBUG(dbgs() << "      Relevant mapping:     " << RelevantWritesTarget
                   << '\n');
      DEBUG(dbgs() << "      Extrapolated mapping: " << ExpandedTargetWrites
                   << '\n');
      DEBUG(dbgs() << "      Missing instances:    "
                   << give(isl_union_set_subtract(UniverseWritesDom.copy(),
                                                  ExpandedWritesDom.copy()))
                   << '\n');
      return false;
    }

    //  { DomainRead[] -> Scatter[] }
    auto PerPHIWriteScatter = give(isl_map_from_union_map(
        isl_union_map_apply_range(PerPHIWrites.copy(), Schedule.copy())));

    // { DomainRead[] -> Zone[] }
    auto Lifetime = betweenScatter(PerPHIWriteScatter, PHISched, false, true);
    simplify(Lifetime);
    DEBUG(dbgs() << "    Lifetime: " << Lifetime << "\n");

    // { DomainWrite[] -> Zone[] }
    auto WriteLifetime = give(isl_union_map_apply_domain(
        isl_union_map_from_map(Lifetime.copy()), PerPHIWrites.copy()));

    // { DomainWrite[] -> ValInst[] }
    auto WrittenValue = determinePHIWrittenValues(SAI);

    // { DomainWrite[] -> [Element[] -> Scatter[]] }
    auto WrittenTranslator = give(isl_union_map_range_product(
        ExpandedTargetWrites.copy(), Schedule.copy()));

    // { DomainWrite[] -> [Element[], Zone[]] }
    auto LifetimeTranslator = give(isl_union_map_range_product(
        ExpandedTargetWrites.copy(), WriteLifetime.take()));

    // { [Element[] -> Zone[]] -> ValInst[] }
    auto EltLifetimeInst = give(isl_union_map_apply_domain(
        WrittenValue.copy(), LifetimeTranslator.take()));

    // { [Element[] -> Scatter[]] -> ValInst[] }
    auto EltWritten = give(isl_union_map_apply_domain(
        WrittenValue.copy(), WrittenTranslator.take()));

    Knowledge Proposed(EltLifetimeInst, false, EltWritten);
    if (isConflicting(Proposed))
      return false;

    mapPHI(SAI, std::move(PHITarget), std::move(ExpandedTargetWrites),
           std::move(Lifetime), std::move(Proposed));
    return true;
  }

  /// Map an MK_PHI scalar to an array element.
  ///
  /// Callers must have ensured that the mapping is valid and not conflicting
  /// with the common knowledge.
  ///
  /// @param SAI         The ScopArrayInfo representing the scalar's memory to
  /// map.
  /// @param ReadTarget  { DomainRead[] -> Element[] }
  ///                    The array element to map the scalar to.
  /// @param WriteTarget { DomainWrite[] -> Element[] }
  ///                    New access target for each PHI incoming write.
  /// @param Lifetime    { DomainRead[] -> Zone[] }
  ///                    The lifetime of each PHI for reporting.
  /// @param Proposed    Mapping constraints for reporting.
  void mapPHI(const ScopArrayInfo *SAI, IslPtr<isl_map> ReadTarget,
              IslPtr<isl_union_map> WriteTarget, IslPtr<isl_map> Lifetime,
              Knowledge Proposed) {
    // Redirect the PHI incoming writes.
    SmallVector<MemoryAccess *, 4> SecondaryAccs;
    for (auto *MA : DefUse.getPHIIncomings(SAI)) {
      // { DomainWrite[] }
      auto Domain = getDomainFor(MA);

      // { DomainWrite[] -> Element[] }
      auto NewAccRel = give(isl_union_map_intersect_domain(
          WriteTarget.copy(), isl_union_set_from_set(Domain.take())));
      simplify(NewAccRel);

      assert(isl_union_map_n_map(NewAccRel.keep()) == 1);
      MA->setNewAccessRelation(isl_map_from_union_map(NewAccRel.take()));
      SecondaryAccs.push_back(MA);
    }

    // Redirect the PHI read.
    auto *PHIRead = DefUse.getPHIRead(SAI);
    PHIRead->setNewAccessRelation(ReadTarget.copy());
    applyLifetime(Proposed);

    MappedPHIScalars++;
    MapReports.emplace_back(SAI, PHIRead, SecondaryAccs, std::move(ReadTarget),
                            std::move(Lifetime), std::move(Proposed));
  }

  /// Search and map scalars to memory overwritten by @p TargetStoreMA.
  ///
  /// Start trying mapping of scalars that are used in the same statement as the
  /// store. For every successful mapping, try to also map scalars of the
  /// statements where those are written. Repeat, until no more mapping
  /// opportunity is found.
  ///
  /// There is currently no preference in which order scalars are being tried.
  /// Ideally, we would direct it towards a load instruction of the same array
  /// element.
  bool collapseScalarsToStore(MemoryAccess *TargetStoreMA) {
    assert(TargetStoreMA->isLatestArrayKind());
    assert(TargetStoreMA->isMustWrite());

    auto TargetStmt = TargetStoreMA->getStatement();

    // { DomTarget[] }
    auto TargetDom = getDomainFor(TargetStmt);

    // { DomTarget[] -> Element[] }
    auto TargetAccRel = getAccessRelationFor(TargetStoreMA);

    // { Zone[] -> DomTarget[] }
    // For each point in time, find the next target store instance.
    auto Target =
        computeScalarReachingOverwrite(Schedule, TargetDom, false, true);

    // { Zone[] -> Element[] }
    // Use the target store's write location as a suggestion to map scalars to.
    auto EltTarget =
        give(isl_map_apply_range(Target.take(), TargetAccRel.take()));
    simplify(EltTarget);
    DEBUG(dbgs() << "    Target mapping is " << EltTarget << '\n');

    // Stack of elements no yet processed.
    SmallVector<MemoryAccess *, 16> Worklist;

    // Set of scalars already tested.
    SmallPtrSet<const ScopArrayInfo *, 16> Closed;

    // Lambda to add all scalar reads to the work list.
    auto ProcessAllIncoming = [&](ScopStmt *Stmt) {
      for (auto *MA : *Stmt) {
        if (!MA->isLatestScalarKind())
          continue;
        if (!MA->isRead())
          continue;

        Worklist.push_back(MA);
      }
    };

    // Add initial scalar. Either the value written by the store, or all inputs
    // of its statement.
    auto WrittenVal = TargetStoreMA->getAccessValue();
    if (auto InputAcc = getInputAccessOf(WrittenVal, TargetStmt, false))
      Worklist.push_back(InputAcc);
    else
      ProcessAllIncoming(TargetStmt);

    auto AnyMapped = false;
    auto &DL =
        S->getRegion().getEntry()->getParent()->getParent()->getDataLayout();
    auto StoreSize =
        DL.getTypeAllocSize(TargetStoreMA->getAccessValue()->getType());

    while (!Worklist.empty()) {
      auto *MA = Worklist.pop_back_val();

      auto *SAI = MA->getScopArrayInfo();
      if (Closed.count(SAI))
        continue;
      Closed.insert(SAI);
      DEBUG(dbgs() << "\n    Trying to map " << MA << " (SAI: " << SAI
                   << ")\n");

      // Skip non-mappable scalars.
      if (!isMappable(SAI))
        continue;

      auto MASize = DL.getTypeAllocSize(MA->getAccessValue()->getType());
      if (MASize > StoreSize) {
        DEBUG(dbgs() << "    Reject because storage size is insufficient\n");
        continue;
      }

      // Try to map MK_Value scalars.
      if (SAI->isValueKind() && tryMapValue(SAI, EltTarget)) {
        auto *DefAcc = DefUse.getValueDef(SAI);
        ProcessAllIncoming(DefAcc->getStatement());

        AnyMapped = true;
        continue;
      }

      // Try to map MK_PHI scalars.
      if (SAI->isPHIKind() && tryMapPHI(SAI, EltTarget)) {
        // Add inputs of all incoming statements to the worklist.
        for (auto *PHIWrite : DefUse.getPHIIncomings(SAI))
          ProcessAllIncoming(PHIWrite->getStatement());

        AnyMapped = true;
        continue;
      }
    }

    if (AnyMapped)
      TargetsMapped++;
    return AnyMapped;
  }

  /// Print the knowledge before any transformation has been applied to @p OS.
  void printBefore(llvm::raw_ostream &OS, int Indent = 0) {
    OS.indent(Indent) << "Original knowledge {\n";
    OriginalZone.print(OS, Indent + 4);
    OS.indent(Indent) << "}\n";
  }

  /// Print the report about all executions transformations to @p OS.
  void printMappedScalars(llvm::raw_ostream &OS, int Indent = 0) {
    OS.indent(Indent) << "Mapped scalars {\n";
    for (auto &Report : MapReports)
      Report.print(OS, Indent + 4);
    OS.indent(Indent) << "}\n";
  }

  /// Print the knowledge from after transformations have been applied to @p OS.
  void printAfter(llvm::raw_ostream &OS, int Indent = 0) {
    OS.indent(Indent) << "After knowledge {\n";
    Zone.print(OS, Indent + 4);
    OS.indent(Indent) << "}\n";
  }

  /// Compute when an array element is alive (Its value will be read in the
  /// future) and its value at that time.
  ///
  /// @return { [Element[] -> Zone[]] -> ValInst[] }
  IslPtr<isl_union_map> computeLifetime() const {
    // { [Element[] -> Zone[]] }
    auto ArrayUnused = computeArrayUnused(Schedule, AllMustWrites, AllReads,
                                          false, false, true);

    // { [Element[] -> Zone[]] }
    auto UnusedZone = give(isl_union_map_wrap(ArrayUnused.take()));

    // { [Element[] -> Zone[]] -> ValInst[] }
    auto UnusedUndef = give(isl_union_map_from_domain_and_range(
        UnusedZone.copy(), makeUndefUSet().take()));

    // { Element[] -> Zone[] }
    auto UniverseZone = give(isl_union_map_from_domain_and_range(
        AllElements.copy(),
        isl_union_set_from_set(isl_set_universe(ScatterSpace.copy()))));

    // { [Element[] -> Zone[]] -> [Element[] -> DomainWrite[]] }
    auto EltReachdDef = give(isl_union_map_range_product(
        isl_union_map_domain_map(UniverseZone.take()),
        WriteReachDefZone.copy()));

    // { [Element[] -> Zone[]] -> ValInst[] }
    auto EltLifetime = give(isl_union_map_apply_domain(
        AllWriteValInst.copy(), isl_union_map_reverse(EltReachdDef.take())));

    // Remove the zones that are guaranteed to be overwritten - they do not
    // belong to a lifetime.
    EltLifetime = give(
        isl_union_map_subtract_domain(EltLifetime.take(), UnusedZone.take()));
    EltLifetime =
        give(isl_union_map_union(EltLifetime.take(), UnusedUndef.take()));
    EltLifetime = removeUnknownValInst(EltLifetime);

    // TODO: If EltLifetime at a point maps to two (non-undef) values, replace
    // by unknown.
    simplify(EltLifetime);
    return EltLifetime;
  }

  /// Determine when an array element is written to, and which value instance is
  /// written.
  ///
  /// @return { [Element[] -> Scatter[]] -> ValInst[] }
  IslPtr<isl_union_map> computeWritten() const {
    // { Element[] -> Element[] }
    auto AllElementsId = makeIdentityMap(AllElements, false);

    // { [Element[] -> DomainWrite[]] -> [Element[] -> Scatter[]] }
    auto EltWriteTranslator =
        give(isl_union_map_product(AllElementsId.take(), Schedule.copy()));

    // { [Element[] -> Scatter[]] -> ValInst[] }
    auto EltWritten = give(isl_union_map_apply_domain(
        AllWriteValInst.copy(), EltWriteTranslator.take()));

    simplify(EltWritten);
    return EltWritten;
  }

public:
  DeLICMImpl(Scop *S) : ZoneAlgorithm(S) { DefUse.compute(S); }

  /// Calculate the lifetime (definition to last use) of every array element.
  ///
  /// @return True if the computed lifetimes (#Zone) is usable.
  bool computeZone() {
    IslPtr<isl_union_map> EltLifetime, EltWritten;

    {
      IslMaxOperationsGuard MaxOpGuard(IslCtx, DelicmMaxOps);

      if (!computeCommon()) {
        DeLICMIncompatible++;
        return false;
      }

      EltLifetime = computeLifetime();
      EltWritten = computeWritten();
    }

    if (isl_ctx_last_error(IslCtx) == isl_error_quota) {
      DeLICMOutOfQuota++;
      DEBUG(dbgs() << "DeLICM analysis exceeded max_operations\n");
    }

    DeLICMAnalyzed++;
    OriginalZone =
        Knowledge(std::move(EltLifetime), true, std::move(EltWritten));
    DEBUG(dbgs() << "Computed Zone:\n"; OriginalZone.print(dbgs(), 4));

    Zone = OriginalZone;

    return DelicmMaxOps == 0 || Zone.isUsable();
  }

  /// Try to map as many scalars to unused array elements as possible.
  ///
  /// Multiple scalars might be mappable to intersecting unused array element
  /// zones, but we can only chose one. This is a greedy algorithm, therefore
  /// the first processed will claim it.
  void greedyCollapse() {
    bool Modified = false;

    for (auto &Stmt : *S) {
      for (auto *MA : Stmt) {
        if (!MA->isLatestArrayKind())
          continue;
        if (!MA->isWrite())
          continue;

        if (MA->isMayWrite()) {
          DEBUG(dbgs() << "Access " << MA
                       << " pruned because it is a MAY_WRITE\n");
          continue;
        }

        if (Stmt.getNumIterators() == 0) {
          DEBUG(dbgs() << "Access " << MA
                       << " pruned because it is not in a loop\n");
          continue;
        }

        if (isScalarAccess(getAccessRelationFor(MA))) {
          DEBUG(dbgs() << "Access " << MA
                       << " pruned because it writes only a single element\n");
          continue;
        }

        DEBUG(dbgs() << "Analyzing target access " << MA << "\n");
        if (collapseScalarsToStore(MA))
          Modified = true;
      }
    }

    if (Modified)
      DeLICMScopsModified++;
  }

  /// Dump the internal information about a performed DeLICM to @p OS.
  void print(llvm::raw_ostream &OS, int indent = 0) {
    printBefore(OS, indent);
    printMappedScalars(OS, indent);
    printAfter(OS, indent);
    printAccesses(OS, indent);
  }
};

class DeLICM : public ScopPass {
private:
  DeLICM(const DeLICM &) = delete;
  const DeLICM &operator=(const DeLICM &) = delete;

  /// Hold a reference to the isl_ctx to avoid it being freed before we released
  /// all of the ISL objects.
  std::shared_ptr<isl_ctx> IslCtx;

  /// The pass implementation, also holding per-scop data.
  std::unique_ptr<DeLICMImpl> Impl;

  void collapseToUnused(Scop &S) {
    Impl = make_unique<DeLICMImpl>(&S);

    if (!Impl->computeZone()) {
      DEBUG(dbgs() << "Abort because cannot reliably compute lifetimes\n");
      return;
    }

    DEBUG(dbgs() << "Collapsing scalars to unused array elements...\n");
    Impl->greedyCollapse();

    DEBUG(dbgs() << "\nFinal Scop:\n");
    DEBUG(S.print(dbgs()));
  }

public:
  static char ID;
  explicit DeLICM() : ScopPass(ID) {}

  virtual void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.addRequiredTransitive<ScopInfoRegionPass>();
    AU.setPreservesAll();
  }

  virtual bool runOnScop(Scop &S) override {
    // Free resources for previous scop's computation, if not yet done.
    releaseMemory();

    IslCtx = S.getSharedIslCtx();
    collapseToUnused(S);

    return false;
  }

  virtual void printScop(raw_ostream &OS, Scop &S) const override {
    if (!Impl)
      return;

    OS << "DeLICM result:\n";
    assert(Impl->getScop() == &S);
    Impl->print(OS);
  }

  virtual void releaseMemory() override {
    Impl.reset();

    // It is important to release the isl_ctx last, to ensure it is not free'd
    // before any other ISL object held.
    // Other passes may still own references to this isl_ctx, so it is not
    // free'd immediately.
    IslCtx.reset();
  }
};

char DeLICM::ID;
} // anonymous namespace

Pass *polly::createDeLICMPass() { return new DeLICM(); }

INITIALIZE_PASS_BEGIN(DeLICM, "polly-delicm", "Polly - DeLICM/DePRE", false,
                      false)
INITIALIZE_PASS_END(DeLICM, "polly-delicm", "Polly - DeLICM/DePRE", false,
                    false)

namespace {
/// Hold the information about a change to report with -analyze.
struct KnownReport {
  /// The scalar READ MemoryAccess that have been changed to an MK_Array access.
  MemoryAccess *ReadMA;

  /// Array elements that store the same value when the MemoryAcceess is
  /// executed.
  // { Domain[] -> Element[] }
  IslPtr<isl_union_map> Candidates;

  /// The chosen array elements, one for each element execution.
  // { Domain[] -> Element[] }
  IslPtr<isl_map> Target;

  /// Value each MemoryAccess instance expects to read, either from
  // { Domain[] -> Value[] }
  IslPtr<isl_map> RequiredValue;

  KnownReport(MemoryAccess *ReadMA, IslPtr<isl_union_map> Candidates,
              IslPtr<isl_map> Target, IslPtr<isl_map> RequiredValue)
      : ReadMA(ReadMA), Candidates(std::move(Candidates)),
        Target(std::move(Target)), RequiredValue(std::move(RequiredValue)) {
    DEBUG(print(dbgs(), 0));
  }

  void print(raw_ostream &OS, int Indent = 0) const {
    OS.indent(Indent) << "Redirect " << ReadMA << " {\n";
    OS.indent(Indent + 4) << "Expects   : " << RequiredValue << '\n';
    OS.indent(Indent + 4) << "Candidates: " << Candidates << '\n';
    OS.indent(Indent + 4) << "Chosen    : " << Target << '\n';
    OS.indent(Indent) << "}\n";
  }
};

/// Implements the KnownPass for a specific Scop.
///
/// This class is responsible for
/// - Computing the zones of all array elements where it is known to contain a
///   specific value.
/// - Find MemoryAccesses that could read from an array element instead from a
///   scalar.
/// - Change the MemoryAccess to read from the found element instead.
class KnownImpl : public ZoneAlgorithm {
private:
  /// Contains the zones where array elements are known to contain a specific
  /// value.
  /// { [Element[] -> Zone[]] -> ValInst[] }
  /// @see computeKnown()
  IslPtr<isl_union_map> Known;

  /// List of redirect-scalar-access-to-known-array-element actions done.
  /// @see collapseKnownLoad()
  SmallVector<KnownReport, 8> KnownReports;

  LoopInfo *LI;
  // ScalarEvolution *SE;

  /// Redirect a read MemoryAccess to an array element that we have proven to
  /// contain the same value.
  ///
  /// Callers are responsible to determine that this does not change the scop's
  /// semantics.
  ///
  /// @param RA            The MemoryAccess to redirect.
  /// @param Target        { Domain[] -> Element[] }
  ///                      The array element replacement to read from. Must be
  ///                      single-valued.
  /// @param Candidates    { Domain[] -> Element[] }
  ///                      Complete list of array elements that contain the same
  ///                      value (but @p Target has been chosen). For report
  ///                      purposes only.
  /// @param RequiredValue { Domain[] -> ValInst[] }
  ///                      The value @p RA is expected to load. For report
  ///                      purposes only.
  void collapseKnownLoad(MemoryAccess *RA, IslPtr<isl_map> Target,
                         IslPtr<isl_union_map> Candidates,
                         IslPtr<isl_map> RequiredValue) {
    assert(RA->isRead());
    assert(RA->isLatestScalarKind());
    assert(isl_map_is_single_valued(Target.keep()));

    RA->setNewAccessRelation(Target.copy());

    MappedKnown++;
    KnownReports.emplace_back(RA, std::move(Candidates), std::move(Target),
                              std::move(RequiredValue));
  }

  struct SCEVGetUnknowns {
    std::vector<llvm::Value *> Unknowns;

    void visit(const SCEV *S) {
      if (isa<SCEVUnknown>(S))
        Unknowns.push_back(cast<SCEVUnknown>(S)->getValue());
    }

    bool isDone() { return false; }
    bool follow(const SCEV *S) { return true; }
  };

  std::vector<llvm::Value *> getUnknowns(const SCEV *Root) {
    SCEVGetUnknowns Visitor;
    visitAll(Root, Visitor);
    return std::move(Visitor.Unknowns);
  }

  bool canForwardTree(llvm::Value *UseVal, ScopStmt *UseStmt, Loop *UseLoop,
                      // { DomainUse[] -> Scatter[] }
                      IslPtr<isl_map> UseScatter, ScopStmt *TargetStmt,
                      // { DomainUse[] -> DomainTarget[] }
                      IslPtr<isl_map> UseToTargetMapping, int Depth, bool DoIt,
                      MemoryAccess *&ReuseMe) {
    // Don't handle PHIs (yet)
    if (isa<PHINode>(UseVal))
      return false;

    auto VUse = VirtualUse::create(UseStmt, UseVal, UseLoop, S->getSE());

    switch (VUse.getType()) {
    case VirtualUse::Constant:
    case VirtualUse::Synthesizable:
      return true;

    case VirtualUse::ReadOnly:
      if (DoIt && ModelReadOnlyScalars &&
          !getInputAccessOf(UseVal, TargetStmt)) {
        auto *SAI = S->getOrCreateScopArrayInfo(UseVal, UseVal->getType(), {},
                                                MemoryKind::Value);
        auto *Access = new MemoryAccess(
            TargetStmt, nullptr, MemoryAccess::READ, UseVal, UseVal->getType(),
            true, {}, {}, UseVal, MemoryKind::Value, UseVal->getName());
        Access->buildAccessRelation(SAI);
        S->addAccessFunction(Access);
        TargetStmt->addAccess(Access);
        MappedReadOnly++;
      }
      return true;

    case VirtualUse::IntraValue:
    case VirtualUse::InterValue:
      break;
    }

    auto Inst = cast<Instruction>(UseVal);
    if (Inst->mayHaveSideEffects() &&
        !isa<LoadInst>(Inst)) // isSafeToSpeculativelyExecute()???
      return false;

    auto DefStmt = S->getStmtFor(Inst);
    assert(DefStmt);
    auto DefLoop = LI->getLoopFor(Inst->getParent());

    // { DomainDef[] -> Scatter[] }
    IslPtr<isl_map> DefScatter;

    // { DomainDef[] -> DomainTarget[] }
    IslPtr<isl_map> DefToTargetMapping;

    if (UseStmt == DefStmt) {
      DefScatter = UseScatter;
      DefToTargetMapping = UseToTargetMapping;
    } else {

      // { DomainDef[] -> Scatter[] }
      DefScatter = getScatterFor(DefStmt);

      // { Scatter[] -> DomainDef[] }
      auto ReachDef = getScalarReachingDefinition(DefStmt);

      // { DomainUse[] -> DomainDef[] }
      auto DefToUseMapping =
          give(isl_map_apply_range(UseScatter.copy(), ReachDef.copy()));

      // { DomainDef[] -> DomainTarget[] }
      DefToTargetMapping = give(isl_map_apply_domain(
          isl_map_reverse(UseToTargetMapping.copy()), DefToUseMapping.copy()));
    }

    if (auto LI = dyn_cast<LoadInst>(Inst)) {
      if (!canForwardTree(LI->getPointerOperand(), DefStmt, DefLoop, DefScatter,
                          TargetStmt, UseToTargetMapping, Depth + 1, DoIt,
                          ReuseMe))
        return false;

      auto *RA = &DefStmt->getArrayAccessFor(LI);

      // { DomainDef[] -> ValInst[] }
      auto ExpectedVal = makeValInst(UseVal, DefStmt);

      // { DomainTarget[] -> ValInst[] }
      auto ToExpectedVal = give(
          isl_map_apply_domain(ExpectedVal.copy(), DefToTargetMapping.copy()));

      IslPtr<isl_union_map> Candidates;
      // { DomainTo[] -> Element[] }
      auto SameVal = containsSameValue(ToExpectedVal, getScatterFor(TargetStmt),
                                       Candidates);
      if (!SameVal)
        return false;
      if (DoIt) {
        MemoryAccess *Access;
        if (Depth == 0 && ReuseMe) {
          Access = ReuseMe;
          ReuseMe = nullptr;
        } else {
          auto ArrayId =
              give(isl_map_get_tuple_id(SameVal.keep(), isl_dim_out));
          auto SAI = reinterpret_cast<ScopArrayInfo *>(
              isl_id_get_user(ArrayId.keep()));
          SmallVector<const SCEV *, 4> Sizes;
          Sizes.reserve(SAI->getNumberOfDimensions());
          SmallVector<const SCEV *, 4> Subscripts;
          Subscripts.reserve(SAI->getNumberOfDimensions());
          for (unsigned i = 0; i < SAI->getNumberOfDimensions(); i += 1) {
            auto DimSize = SAI->getDimensionSize(i);
            Sizes.push_back(DimSize);

            // Dummy access, to be replaced anyway.
            Subscripts.push_back(nullptr);
          }
          Access = new MemoryAccess(TargetStmt, LI, MemoryAccess::READ,
                                    SAI->getBasePtr(), Inst->getType(), true,
                                    {}, Sizes, Inst, MemoryKind::Array,
                                    RA->getBaseName());
          S->addAccessFunction(Access);
          TargetStmt->addAccess(Access);
        }
        Access->setNewAccessRelation(SameVal.copy());

        MappedKnown++;
        KnownReports.emplace_back(RA, std::move(Candidates), std::move(SameVal),
                                  std::move(ToExpectedVal));
      }
      return true;
    }

    if (Inst->mayHaveSideEffects())
      return false;

    for (auto OpVal : Inst->operand_values()) {
      if (!canForwardTree(OpVal, DefStmt, DefLoop, DefScatter, TargetStmt,
                          DefToTargetMapping, Depth + 1, DoIt, ReuseMe))
        return false;
    }

    return true;
  }

  Loop *getOutermostLoopFor(ScopStmt *Stmt) {
    return LI->getLoopFor(Stmt->getEntryBlock());
  }

  bool tryForwardTree(MemoryAccess *RA) {
    assert(RA->isLatestScalarKind());

    auto Stmt = RA->getStatement();
    auto InLoop = Stmt->getSurroundingLoop();
    auto DomSpace = give(Stmt->getDomainSpace());
    auto Identity = give(isl_map_identity(
        isl_space_map_from_domain_and_range(DomSpace.copy(), DomSpace.copy())));
    auto Scatter = getScatterFor(Stmt);

    if (!canForwardTree(RA->getAccessValue(), Stmt, InLoop, Scatter, Stmt,
                        Identity, 0, false, RA))
      return false;

    bool Success = canForwardTree(RA->getAccessValue(), Stmt, InLoop, Scatter,
                                  Stmt, Identity, 0, true, RA);
    assert(Success && "If it says it can do it, it must be able to do it");

    // Remove if not been reused.
    if (RA)
      Stmt->removeSingleMemoryAccess(RA);

    return true;
  }

  // { Domain[] -> Element[] }
  IslPtr<isl_map> containsSameValue(
      // { Domain[] -> ValInst[] }
      IslPtr<isl_map> ValInst,
      // { Domain[] -> Scatter[] }
      IslPtr<isl_map> Sched, IslPtr<isl_union_map> &MustKnownMap) {

    // { Domain[] }
    auto Domain = give(isl_map_domain(ValInst.copy()));

    // { Element[] -> [Zone[] -> ValInst[]] }
    auto MustKnownCurried = give(isl_union_map_curry(Known.copy()));

    // { [DomainUser[] -> ValInst[]] -> DomainUser[] }
    auto DomValDom = give(isl_map_domain_map(ValInst.copy()));

    // { [DomainUser[] -> ValInst[]] -> ValInst[] }
    auto DomValVal = give(isl_map_range_map(ValInst.copy()));

    // { [DomainUser[] -> ValInst[]] -> Scatter[] }
    auto DomValSched =
        give(isl_map_apply_range(DomValDom.take(), Sched.take()));

    // { [Scatter[] -> ValInst[]] -> [DomainUser[] -> ValInst[]] }
    auto SchedValDomVal = give(isl_union_map_from_map(isl_map_reverse(
        isl_map_range_product(DomValSched.take(), DomValVal.take()))));

    // { Element[] -> [DomainUser[] -> ValInst[]] }
    // Zone[] of MustKnownCurried is reinterpreted as Scatter[]: Those instants
    // that immediately follow an unit-zone. Scalar reads take place at the
    // beginning of a statement's execution, meaning they read directly the
    // value that is known in the unit-zone.
    auto MustKnownInst = give(isl_union_map_apply_range(MustKnownCurried.take(),
                                                        SchedValDomVal.take()));

    // { DomainUser[] -> Element[] }
    // List of array elements that do contain the same ValInst[] at when the
    // read access takes place.
    MustKnownMap = give(isl_union_map_reverse(isl_union_set_unwrap(
        isl_union_map_domain(isl_union_map_uncurry(MustKnownInst.take())))));
    simplify(MustKnownMap);

    IslPtr<isl_map> Result;

    // MemoryAccesses can read only elements from a single array (not: { Dom[0]
    // -> A[0]; Dom[1] -> B[1] }). Look through all arrays until we find one
    // that contains exactly the wanted values.
    foreachEltWithBreak(
        MustKnownMap, [&, this](IslPtr<isl_map> Map) -> isl_stat {
          // Get the array this is accessing.
          auto ArrayId = give(isl_map_get_tuple_id(Map.keep(), isl_dim_out));
          auto SAI =
              static_cast<ScopArrayInfo *>(isl_id_get_user(ArrayId.keep()));

          // No support for generation of indirect array accesses.
          if (SAI->getBasePtrOriginSAI())
            return isl_stat_ok; // continue

          // Determine whether this map contains all wanted values.
          auto MapDom = give(isl_map_domain(Map.copy()));
          if (!isl_set_is_subset(Domain.keep(), MapDom.keep()))
            return isl_stat_ok; // continue

          // TODO: Check requirement that it maps not only to the same location,
          // otherwise we don't gain anything; DeLICM already does this.

          // There might be multiple array elements the contain the same value,
          // but
          // choose only one of them. lexmin is used because it returns a
          // one-value
          // mapping, we currently do not care about which one.
          // TODO: Get the simplest access function.
          Result = give(isl_map_lexmin(Map.take()));
          return isl_stat_error; // break
        });

    return Result;
  }

  /// Find array elements that contain the same value as @p RA reads and try to
  /// redirect the scalar load to read from that array element instead.
  bool tryCollapseKnownLoad(MemoryAccess *RA) {
    assert(RA->isLatestScalarKind());

    // { DomainUser[] -> ValInst[] }
    auto ValInst = makeValInst(RA->getAccessValue(), RA->getStatement());

    // { DomainUser[] -> Scatter[] }
    auto Sched = getScatterFor(RA);

    // { Element[] -> [Zone[] -> ValInst[]] }
    auto MustKnownCurried = give(isl_union_map_curry(Known.copy()));

    // { [DomainUser[] -> ValInst[]] -> DomainUser[] }
    auto DomValDom = give(isl_map_domain_map(ValInst.copy()));

    // { [DomainUser[] -> ValInst[]] -> ValInst[] }
    auto DomValVal = give(isl_map_range_map(ValInst.copy()));

    // { [DomainUser[] -> ValInst[]] -> Scatter[] }
    auto DomValSched =
        give(isl_map_apply_range(DomValDom.take(), Sched.take()));

    // { [Scatter[] -> ValInst[]] -> [DomainUser[] -> ValInst[]] }
    auto SchedValDomVal = give(isl_union_map_from_map(isl_map_reverse(
        isl_map_range_product(DomValSched.take(), DomValVal.take()))));

    // { Element[] -> [DomainUser[] -> ValInst[]] }
    // Zone[] of MustKnownCurried is reinterpreted as Scatter[]: Those instants
    // that immediately follow an unit-zone. Scalar reads take place at the
    // beginning of a statement's execution, meaning they read directly the
    // value that is known in the unit-zone.
    auto MustKnownInst = give(isl_union_map_apply_range(MustKnownCurried.take(),
                                                        SchedValDomVal.take()));

    // { DomainUser[] -> Element[] }
    // List of array elements that do contain the same ValInst[] at when the
    // read access takes place.
    auto MustKnownMap = give(isl_union_map_reverse(isl_union_set_unwrap(
        isl_union_map_domain(isl_union_map_uncurry(MustKnownInst.take())))));
    simplify(MustKnownMap);

    bool Modified = false;

    // MemoryAccesses can read only elements from a single array (not: { Dom[0]
    // -> A[0]; Dom[1] -> B[1] }). Look through all arrays until we find one
    // that contains exactly the wanted values.
    foreachEltWithBreak(
        MustKnownMap, [&, this](IslPtr<isl_map> Map) -> isl_stat {
          // Get the array this is accessing.
          auto ArrayId = give(isl_map_get_tuple_id(Map.keep(), isl_dim_out));
          auto SAI =
              static_cast<ScopArrayInfo *>(isl_id_get_user(ArrayId.keep()));

          // No support for generation of indirect array accesses.
          if (SAI->getBasePtrOriginSAI())
            return isl_stat_ok; // continue

          // Determine whether this map contains all wanted values.
          auto Dom = getDomainFor(RA);
          auto MapDom = give(isl_map_domain(Map.copy()));
          if (!isl_set_is_subset(Dom.keep(), MapDom.keep()))
            return isl_stat_ok; // continue

          // TODO: Check requirement that it maps not only to the same location,
          // otherwise we don't gain anything; DeLICM already does this.

          // There might be multiple array elements the contain the same value,
          // but
          // choose only one of them. lexmin is used because it returns a
          // one-value
          // mapping, we currently do not care about which one.
          // TODO: Get the simplest access function.
          auto Target = give(isl_map_lexmin(Map.take()));

          // Do the transformation which we determined is valid.
          collapseKnownLoad(RA, std::move(Target), MustKnownMap, ValInst);

          // We were successful and do not need to look for more candidates.
          Modified = true;
          return isl_stat_error; // break
        });

    return Modified;
  }

public:
  KnownImpl(Scop *S, LoopInfo *LI) : ZoneAlgorithm(S), LI(LI) {}

  /// A reaching definition zone is known to have the definition's written value
  /// if the definition is a MUST_WRITE.
  ///
  /// @return { [Element[] -> Zone[]] -> ValInst[] }
  IslPtr<isl_union_map> computeKnownFromMustWrites() const {
    // { [Element[] -> Zone[]] -> DomainWrite[] }
    auto MustWriteReachDefZone = give(isl_union_map_intersect_range(
        WriteReachDefZone.copy(), isl_union_map_domain(AllMustWrites.copy())));

    // { Element[] -> Zone[] }
    auto UniverseZone = give(isl_union_map_from_domain_and_range(
        AllElements.copy(),
        isl_union_set_from_set(isl_set_universe(ScatterSpace.copy()))));

    // { [Element[] -> Zone[]] -> [Element[] -> DomainWrite[]] }
    auto MustWriteReachDefEltZone = give(isl_union_map_range_product(
        isl_union_map_domain_map(UniverseZone.take()),
        MustWriteReachDefZone.take()));

    // { [Element[] -> Zone[]] -> ValInst[] }
    auto MustKnown = give(isl_union_map_apply_range(
        MustWriteReachDefEltZone.take(), AllWriteValInst.copy()));

    return filterKnownValInst(std::move(MustKnown));
  }

  /// A reaching definition zone is known to be the same value as any load that
  /// reads from that array element in that period.
  ///
  /// @return { [Element[] -> Zone[]] -> ValInst[] }
  IslPtr<isl_union_map> computeKnownFromLoad() const {

    // { Scatter[] }
    auto ScatterUniverse =
        give(isl_union_set_from_set(isl_set_universe(ScatterSpace.copy())));

    // { Element[] }
    auto AllAccessedElts =
        give(isl_union_set_union(isl_union_map_range(AllReads.copy()),
                                 isl_union_map_range(AllWrites.copy())));

    // { Element[] -> Scatter[] }
    auto EltZoneUniverse = give(isl_union_map_from_domain_and_range(
        AllAccessedElts.copy(), ScatterUniverse.copy()));

    // This assumes there are no "holes" in
    // isl_union_map_domain(WriteReachDefZone); alternatively, compute the zone
    // before the first write or that are not written at all.
    // { Element[] -> Scatter[] }
    auto NonReachDef = give(
        isl_union_set_subtract(isl_union_map_wrap(EltZoneUniverse.copy()),
                               isl_union_map_domain(WriteReachDefZone.copy())));

    // { [Element[] -> Zone[]] -> ReachDefId[] }
    auto DefZone = give(
        isl_union_map_union(WriteReachDefZone.copy(),
                            isl_union_map_from_domain(NonReachDef.copy())));

    // { [Element[] -> Scatter[]] -> Element[] }
    auto EltZoneElt = give(isl_union_map_domain_map(EltZoneUniverse.copy()));

    // { [Element[] -> Zone[]] -> [Element[] -> ReachDefId[]] }
    auto DefZoneEltDefId =
        give(isl_union_map_range_product(EltZoneElt.copy(), DefZone.copy()));

    // { [Element[] -> Zone[]] -> [ReachDefId[] -> Element[]] }
    auto DefZoneDefidElt =
        give(isl_union_map_range_product(DefZone.copy(), EltZoneElt.copy()));

    // { Element[] -> [Zone[] -> ReachDefId[]] }
    auto EltDefZone = give(isl_union_map_curry(DefZone.copy()));

    // { [Element[] -> Zone[] -> [Element[] -> ReachDefId[]] }
    auto EltZoneEltDefid = isl_union_map_distribute_domain(EltDefZone);

    // { [Element[] -> Scatter[]] -> DomainRead[] }
    auto Reads = give(isl_union_map_reverse(
        isl_union_map_range_product(AllReads.copy(), Schedule.copy())));

    // { [Element[] -> Scatter[]] -> [Element[] -> DomainRead[]] }
    auto ReadsElt =
        give(isl_union_map_range_product(EltZoneElt.copy(), Reads.copy()));

    // { [Element[] -> Scatter[]] -> ValInst[] }
    auto ScatterKnown =
        give(isl_union_map_apply_range(ReadsElt.copy(), AllReadValInst.copy()));

    // { [Element[] -> ReachDefId[]] -> ValInst[] }
    auto DefidKnown = give(isl_union_map_reverse(isl_union_map_apply_domain(
        DefZoneEltDefId.copy(), ScatterKnown.copy())));

    // { [Element[] -> Zone[]] -> ValInst[] }
    auto DefZoneKnown = give(
        isl_union_map_apply_range(DefZoneEltDefId.copy(), DefidKnown.copy()));
    return DefZoneKnown;
  }

  /// If there are loads of an array element before the first write, use these
  /// loaded value as known.
  ///
  /// @return { [Element[] -> Zone[]] -> ValInst[] }
  IslPtr<isl_union_map> computeKnownFromInit() const {
    // { Element[] }
    auto NotWrittenElts =
        give(isl_union_set_subtract(isl_union_map_range(AllReads.copy()),
                                    isl_union_map_range(AllWrites.copy())));

    // { Element[] -> Zone[] }
    auto NeverWritten = give(isl_union_map_from_domain_and_range(
        NotWrittenElts.take(),
        isl_union_set_from_set(isl_set_universe(ScatterSpace.copy()))));

    // { Element[] -> Scatter[] }
    auto WriteSched = give(isl_union_map_apply_range(
        isl_union_map_reverse(AllWrites.copy()), Schedule.copy()));
    auto FirstWrites = give(isl_union_map_lexmin(WriteSched.take()));

    // { Element[] -> Zone[] }
    // Reinterpretation of Scatter[] as Zone[]: The unit-zone before the write
    // timepoint is before the write.
    auto BeforeFirstWrite = beforeScatter(FirstWrites, false);

    // { Element[] -> Zone[] }
    auto BeforeAnyWrite =
        give(isl_union_map_union(BeforeFirstWrite.take(), NeverWritten.take()));

    // { [Element[] -> Zone[]] -> Zone[] }
    auto BeforeFirstWriteZone =
        give(isl_union_map_range_map(BeforeAnyWrite.copy()));
    // give(isl_union_map_uncurry(isl_union_map_range_product(
    // BeforeAnyWrite.copy(), BeforeAnyWrite.copy())));

    // { [Element[] -> Zone[]] -> Domain[] }
    // Reinterpretation of Zone[] as Scatter[]: get the writes at the end of
    // before-write zones.
    // TODO: Might avoid the double reconversion by keeping the DomainWrite[] in
    // FirstWrites.
    auto BeforeFirstWriteDom = give(isl_union_map_apply_range(
        BeforeFirstWriteZone.copy(), isl_union_map_reverse(Schedule.copy())));

    // { [Element[] -> Zone[]] -> [Element[] -> Domain[]] }
    auto BeforeFirstWriteEltDom = give(isl_union_map_range_product(
        isl_union_map_domain_map(BeforeAnyWrite.take()),
        BeforeFirstWriteDom.take()));

    // { [Element[] -> Zone[]] -> ValInst[] }
    return give(isl_union_map_apply_range(BeforeFirstWriteEltDom.take(),
                                          AllReadValInst.copy()));
  }

  /// Compute the zones of known array element contents.
  ///
  /// @return True if the computed #Known is usable.
  bool computeKnown() {
    IslPtr<isl_union_map> MustKnown, KnownFromLoad, KnownFromInit;

    {
      IslMaxOperationsGuard MaxOpGuard(IslCtx, KnownMaxOps);

      if (!computeCommon()) {
        KnownIncompatible++;
        return false;
      }

      // { [Element[] -> Zone[]] -> ValInst[] }
      MustKnown = computeKnownFromMustWrites();

      // { [Element[] -> Zone[]] -> ValInst[] }
      KnownFromLoad = computeKnownFromLoad();

      // { [Element[] -> Zone[]] -> ValInst[] }
      Known = give(isl_union_map_union(KnownFromLoad.copy(), MustKnown.copy()));
      simplify(Known);
    }

    if (isl_ctx_last_error(IslCtx) == isl_error_quota) {
      KnownOutOfQuota++;
      DEBUG(dbgs() << "DeLICM analysis exceeded max_operations\n");
      return false;
    }

    KnownAnalyzed++;
    DEBUG(dbgs() << "Known from must writes: " << MustKnown << "\n");
    DEBUG(dbgs() << "Known from load: " << KnownFromLoad << "\n");
    // DEBUG(dbgs() << "Known from init: " << KnownFromInit << "\n");
    DEBUG(dbgs() << "All known: " << Known << "\n");

    // If maxops is enabled and Known is nullptr, we exceeded the operations
    // limit somewhere during the computation.
    return KnownMaxOps == 0 || !!Known;
  }

  /// Try to redirect all scalar reads in the scop that to array elements that
  /// contain the same value.
  void collapseKnown() {
    assert(Known);
    bool Modified = false;

    SmallVector<MemoryAccess *, 16> Accs;

    for (auto &Stmt : *S) {
      for (auto *RA : Stmt) {
        if (!RA->isLatestScalarKind())
          continue;
        if (!RA->isRead())
          continue;

        Accs.push_back(RA);
      }
    }

    for (auto *RA : Accs)
      if (tryForwardTree(RA))
        Modified = true;

#if 0
    for (auto &Stmt : *S) {
      for (auto *MA : Stmt) {
        if (!MA->isLatestScalarKind())
          continue;

        if (!MA->isRead())
          continue;

        DEBUG(dbgs() << "Trying to collapse " << MA << "\n");
        if (tryCollapseKnownLoad(MA))
          Modified = true;
      }
    }
#endif

    if (Modified)
      KnownScopsModified++;
  }

  void collectInsts(ScopStmt *Stmt, SmallVectorImpl<Instruction *> &List) {
    if (!Stmt->isRegionStmt()) {
      for (auto &Inst : *Stmt->getBasicBlock())
        List.push_back(&Inst);
      return;
    }

    for (auto *BB : Stmt->getRegion()->blocks())
      for (auto &Inst : *BB)
        List.push_back(&Inst);
  }

  /// Print the analysis result, performed transformations and the scop after
  /// the transformation.
  void print(llvm::raw_ostream &OS, int Indent = 0) {
    OS.indent(Indent) << "Known zone: " << Known << "\n";
    OS.indent(Indent) << "Redirected knowns {\n";
    for (auto &Report : KnownReports)
      Report.print(OS, Indent + 4);
    OS.indent(Indent) << "}\n";
    printAccesses(OS, Indent);
  }
};

/// Pass that redirects scalar reads to array elements that are known to contain
/// the same value.
///
/// This reduces the number of scalar accesses and therefore potentially
/// increased the freedom of the scheduler. In the ideal case, all reads of a
/// scalar definition are redirected (We currently do not care about removing
/// the write in this case).  This is also useful for the main DeLICM pass as
/// there are less scalars to be mapped.
class Known : public ScopPass {
private:
  Known(const Known &) = delete;
  const Known &operator=(const Known &) = delete;

  /// Hold a reference to the isl_ctx to avoid it being freed before we released
  /// all of the ISL objects.
  std::shared_ptr<isl_ctx> IslCtx;

  /// The pass implementation, also holding per-scop data.
  std::unique_ptr<KnownImpl> Impl;

  void collapseToKnown(Scop &S) {
    Impl = make_unique<KnownImpl>(
        &S, &getAnalysis<LoopInfoWrapperPass>().getLoopInfo());

    if (!Impl->computeKnown())
      return;

    DEBUG(dbgs() << "Collapsing scalars to known array elements...\n");
    Impl->collapseKnown();

    DEBUG(dbgs() << "\nFinal Scop:\n");
    DEBUG(S.print(dbgs()));
  }

public:
  static char ID;
  explicit Known() : ScopPass(ID) {}
  virtual void getAnalysisUsage(AnalysisUsage &AU) const override {
    // TODO: preserve only ScopInfo and dependencies
    AU.addRequiredTransitive<ScopInfoRegionPass>();
    AU.addRequired<LoopInfoWrapperPass>();
    AU.setPreservesAll();
  }

  virtual bool runOnScop(Scop &S) override {
    // Free resources for previous scop's computation, if not yet done.
    releaseMemory();

    IslCtx = S.getSharedIslCtx();
    collapseToKnown(S);

    return false;
  }

  virtual void printScop(raw_ostream &OS, Scop &S) const override {
    if (!Impl)
      return;

    assert(Impl->getScop() == &S);
    Impl->print(OS);
  }

  virtual void releaseMemory() override {
    Impl.reset();

    // It is important to release the isl_ctx last, to ensure it is not free'd
    // before any other ISL object held.
    IslCtx.reset();
  }

}; // class Known

char Known::ID;
} // anonymous namespace

Pass *polly::createKnownPass() { return new Known(); }

// TODO: use llvm::RegisterPass
INITIALIZE_PASS_BEGIN(Known, "polly-known",
                      "Polly - Scalar accesses to explicit", false, false)
INITIALIZE_PASS_END(Known, "polly-known", "Polly - Scalar accesses to explicit",
                    false, false)

IslPtr<isl_union_map>
polly::computeReachingDefinition(IslPtr<isl_union_map> Schedule,
                                 IslPtr<isl_union_map> Writes, bool InclDef,
                                 bool InclRedef) {
  // { Scatter[] }
  auto ScatterSpace = getScatterSpace(Schedule);

  // { Element[] -> ScatterWrite[] }
  auto DefSched =
      give(isl_union_map_apply_domain(Schedule.copy(), Writes.take()));

  // { ScatterRead[] -> ScatterWrite[] }
  auto Before = give(InclRedef ? isl_map_lex_gt(ScatterSpace.take())
                               : isl_map_lex_ge(ScatterSpace.take()));

  // { ScatterWrite[] -> [ScatterRead[] -> ScatterWrite[]] }
  auto BeforeMap = give(isl_map_reverse(isl_map_range_map(Before.take())));

  // { Element[] -> [ScatterUse[] -> ScatterWrite[]] }
  auto DefSchedBefore =
      give(isl_union_map_apply_domain(isl_union_map_from_map(BeforeMap.take()),
                                      isl_union_map_reverse(DefSched.copy())));

  // For each element, at every point in time, map to the times of previous
  // definitions.
  // { [Element[] -> ScatterRead[]] -> ScatterWrite[] }
  auto ReachableDefs = give(isl_union_map_uncurry(DefSchedBefore.take()));
  auto LastReachableDef = give(isl_union_map_lexmax(ReachableDefs.copy()));

  // { [Element[] -> ScatterWrite[]] -> ScatterWrite[] }
  auto SelfUse = give(isl_union_map_range_map(DefSched.take()));

  if (InclDef && InclRedef) {
    // Add the Def itself to the solution.
    LastReachableDef =
        give(isl_union_map_union(LastReachableDef.take(), SelfUse.take()));
    LastReachableDef = give(isl_union_map_coalesce(LastReachableDef.take()));
  } else if (!InclDef && !InclRedef) {
    // Remove Def itself from the solution.
    LastReachableDef =
        give(isl_union_map_subtract(LastReachableDef.take(), SelfUse.take()));
  }

  // { [Element[] -> ScatterRead[]] -> Domain[] }
  return give(isl_union_map_apply_range(
      LastReachableDef.take(), isl_union_map_reverse(Schedule.take())));
}

IslPtr<isl_union_map>
polly::computeArrayLifetime(IslPtr<isl_union_map> Schedule,
                            IslPtr<isl_union_map> Writes,
                            IslPtr<isl_union_map> Reads, bool ReadEltInSameInst,
                            bool InclWrite, bool InclLastRead, bool ExitReads) {
  IslPtr<isl_union_map> ExitRays;
  if (ExitReads) {
    // Add all writes that are never overwritten as rays.

    // { Element[] }
    auto WriteElements = give(isl_union_map_range(Writes.copy()));

    // { DomainWrite[] -> Scatter[] }
    auto WriteSched = give(isl_union_map_intersect_domain(
        Schedule.copy(), isl_union_map_domain(Writes.copy())));

    // { Element[] -> Scatter[] }
    auto WriteActions = give(isl_union_map_apply_range(
        isl_union_map_reverse(Writes.copy()), Schedule.copy()));
    auto LastWrites = give(isl_union_map_lexmax(WriteActions.take()));

    // { [Element[] -> Scatter[]] -> Zone[] }
    auto AfterLastWrite = afterScatter(
        give(isl_union_map_range_map(LastWrites.take())), !InclWrite);

    // { [Element[] -> DomainWrite[]] -> Zone[] }
    ExitRays = give(isl_union_map_apply_domain(
        AfterLastWrite.take(),
        isl_union_map_product(makeIdentityMap(WriteElements, false).take(),
                              isl_union_map_reverse(WriteSched.take()))));
  }

  // { [Element[] -> DomainWrite[] -> Scatter[] }
  auto Defs = give(isl_union_map_apply_range(
      isl_union_map_range_map(isl_union_map_reverse(Writes.copy())),
      Schedule.copy()));

  // { [Element[] -> Zone[]] -> DomainWrite[] }
  auto ReachDef = computeReachingDefinition(Schedule, Writes, ReadEltInSameInst,
                                            !ReadEltInSameInst);

  // { Element[] -> Scatter[] }
  auto ReadActions =
      give(isl_union_map_apply_domain(Schedule.take(), Reads.take()));

  // { [Element[] -> Scatter[]] -> DomainWrite[] }
  auto WhatIsItReading = give(isl_union_map_intersect_domain(
      ReachDef.take(), isl_union_map_wrap(ReadActions.take())));

  // { [Element[] -> DomainWrite[]] -> Scatter[] }
  auto Uses = give(isl_union_map_reverse(
      isl_union_map_curry(reverseDomain(WhatIsItReading).take())));

  // { [Element[] -> DomainWrite[]] ->  Scatter[] }
  auto Result = betweenScatter(Defs, Uses, InclWrite, InclLastRead);

  if (ExitRays)
    Result = give(isl_union_map_union(Result.take(), ExitRays.take()));

  return Result;
}

IslPtr<isl_union_map>
polly::computeReachingOverwrite(IslPtr<isl_union_map> Schedule,
                                IslPtr<isl_union_map> Writes,
                                bool InclPrevWrite, bool IncludeOverwrite) {
  assert(isl_union_map_is_bijective(Schedule.keep()) != isl_bool_false);

  // { Scatter[] }
  auto ScatterSpace = getScatterSpace(Schedule);

  // { Element[] -> ScatterWrite[] }
  auto WriteAction =
      give(isl_union_map_apply_domain(Schedule.copy(), Writes.take()));

  // { ScatterWrite[] -> Element[] }
  auto WriteActionRev = give(isl_union_map_reverse(WriteAction.copy()));

  // { ScatterRead[] -> ScatterWrite[] }
  auto After = give(InclPrevWrite ? isl_map_lex_lt(ScatterSpace.take())
                                  : isl_map_lex_le(ScatterSpace.take()));

  // { ScatterWrite[] -> [ScatterRead[] -> ScatterWrite[]] }
  auto BeforeMap = give(isl_map_reverse(isl_map_range_map(After.take())));

  // { Element[] -> [ScatterRead[] -> ScatterWrite[]] }
  auto DefSchedBefore = give(isl_union_map_apply_domain(
      isl_union_map_from_map(BeforeMap.take()), WriteActionRev.take()));

  // For each element, at every point in time, map to the times of previous
  // definitions.
  // { [Element[] -> ScatterRead[]] -> ScatterWrite[] }
  auto ReachableDefs = give(isl_union_map_uncurry(DefSchedBefore.take()));
  auto LastReachableDef = give(isl_union_map_lexmin(ReachableDefs.take()));

  if (InclPrevWrite && IncludeOverwrite) {
    // Add the def itself to the solution

    // { [Element[] -> ScatterWrite[]] -> ScatterWrite[] }
    auto SelfUse = give(isl_union_map_range_map(WriteAction.take()));
    LastReachableDef =
        give(isl_union_map_union(LastReachableDef.take(), SelfUse.take()));
    LastReachableDef = give(isl_union_map_coalesce(LastReachableDef.take()));
  } else if (!InclPrevWrite && !IncludeOverwrite) {
    // Remove def itself from the solution

    // { [Element[] -> ScatterWrite[]] -> ScatterWrite[] }
    auto SelfUse = give(isl_union_map_range_map(WriteAction.take()));
    LastReachableDef =
        give(isl_union_map_subtract(LastReachableDef.take(), SelfUse.take()));
  }

  // { [Element[] -> ScatterRead[]] -> Domain[] }
  auto LastReachableDefDomain = give(isl_union_map_apply_range(
      LastReachableDef.take(), isl_union_map_reverse(Schedule.take())));

  return LastReachableDefDomain;
}

IslPtr<isl_union_map> polly::computeArrayUnused(IslPtr<isl_union_map> Schedule,
                                                IslPtr<isl_union_map> Writes,
                                                IslPtr<isl_union_map> Reads,
                                                bool ReadEltInSameInst,
                                                bool IncludeLastRead,
                                                bool IncludeWrite) {
  // { Element[] -> Scatter[] }
  auto ReadActions =
      give(isl_union_map_apply_domain(Schedule.copy(), Reads.take()));
  auto WriteActions =
      give(isl_union_map_apply_domain(Schedule.copy(), Writes.copy()));

  // { [Element[] -> Scatter[] }
  auto AfterReads = afterScatter(ReadActions, ReadEltInSameInst);
  auto WritesBeforeAnyReads =
      give(isl_union_map_subtract(WriteActions.take(), AfterReads.take()));
  auto BeforeWritesBeforeAnyReads =
      beforeScatter(WritesBeforeAnyReads, !IncludeWrite);

  // { [Element[] -> DomainWrite[]] -> Scatter[] }
  auto EltDomWrites = give(isl_union_map_apply_range(
      isl_union_map_range_map(isl_union_map_reverse(Writes.copy())),
      Schedule.copy()));

  // { [Element[] -> Scatter[]] -> DomainWrite[] }
  auto ReachingOverwrite = computeReachingOverwrite(
      Schedule, Writes, ReadEltInSameInst, !ReadEltInSameInst);

  // { [Element[] -> Scatter[]] -> DomainWrite[] }
  auto ReadsOverwritten = give(isl_union_map_intersect_domain(
      ReachingOverwrite.take(), isl_union_map_wrap(ReadActions.take())));

  // { [Element[] -> DomainWrite[]] -> Scatter[] }
  auto ReadsOverwrittenRotated = give(isl_union_map_reverse(
      isl_union_map_curry(reverseDomain(ReadsOverwritten).take())));
  auto LastOverwrittenRead =
      give(isl_union_map_lexmax(ReadsOverwrittenRotated.take()));

  // { [Element[] -> DomainWrite[]] -> Scatter[] }
  auto BetweenLastReadOverwrite = betweenScatter(
      LastOverwrittenRead, EltDomWrites, IncludeLastRead, IncludeWrite);

  return give(isl_union_map_union(
      BeforeWritesBeforeAnyReads.take(),
      isl_union_map_domain_factor_domain(BetweenLastReadOverwrite.take())));
}

bool polly::isConflicting(IslPtr<isl_union_map> ExistingLifetime,
                          bool ExistingImplicitLifetimeIsUnknown,
                          IslPtr<isl_union_map> ExistingWritten,
                          IslPtr<isl_union_map> ProposedLifetime,
                          bool ProposedImplicitLifetimeIsUnknown,
                          IslPtr<isl_union_map> ProposedWritten) {
  Knowledge Existing(std::move(ExistingLifetime),
                     ExistingImplicitLifetimeIsUnknown,
                     std::move(ExistingWritten));
  Knowledge Proposed(std::move(ProposedLifetime),
                     ProposedImplicitLifetimeIsUnknown,
                     std::move(ProposedWritten));

  return Knowledge::isConflicting(Existing, Proposed);
}
