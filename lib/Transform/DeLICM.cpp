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
//   integer points 1 and 2)
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
#include "polly/ScopInfo.h"
#include "polly/ScopPass.h"
#include "polly/Support/GICHelper.h"
#include "llvm/ADT/Statistic.h"
#include "isl/aff.h"
#include "isl/aff_type.h"
#include "isl/map.h"
#include "isl/options.h"
#include "isl/printer.h"
#include "isl/union_map.h"
#include "isl/union_set.h"
#include <algorithm>
#include <tuple>
#define DEBUG_TYPE "polly-delicm"

using namespace polly;
using namespace llvm;

namespace {

cl::opt<unsigned long>
    DelicmMaxOps("polly-delicm-max-ops",
                 cl::desc("Maximum number of ISL operations to invest for "
                          "lifetime analysis; 0=no limit"),
                 cl::init(1000000), cl::cat(PollyCategory));

STATISTIC(MappedValueScalars, "Number of mapped Value scalars");
STATISTIC(MappedPHIScalars, "Number of mapped PHI scalars");
STATISTIC(TargetsMapped, "Number of stores used for at least one mapping");

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
  assert(
      !Result ||
      isl_space_has_equal_tuples(give(isl_map_get_space(Result.keep())).keep(),
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
  assert(
      !Result ||
      isl_space_has_equal_tuples(give(isl_set_get_space(Result.keep())).keep(),
                                 ExpectedSpace.keep()) == isl_bool_true);
  return Result;
}

/// Returns whether @p Map has a mapping for at least all elements of @p Domain.
isl_bool isMapDomainSubsetOf(IslPtr<isl_map> Map,
                             NonowningIslPtr<isl_set> Domain) {
  auto Subset = give(isl_map_domain(Map.take()));
  return isl_set_is_subset(Subset.keep(), Domain.keep());
}

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

/// Compute the lifetime of a scalar.
///
/// In contrast to computeArrayLifetime, only considers just one variable
/// instead of multiple arrays. Hence, the element is not required for input and
/// is not part of the output.
///
/// @param Schedule          { Domain[] -> Scatter[] }
/// @param Writes            { DomainWrite[] }
/// @param Reads             { DomainRead[] }
/// @param ReadEltInSameInst A read at the same timepoint as a write will read
/// that value instead of the previous's.
/// @param InclWrite         Include the write itself to the lifetime.
/// @param InclLastRead      Include the last write to the lifetime.
/// @param ExitReads         Extend the last definition to infinity.
///
/// @return { DomainWrite[] -> Zone[] }
///         The scalar's lifetime.
///
/// @see computeArrayLifetime
IslPtr<isl_union_map> computeScalarLifetime(IslPtr<isl_union_map> Schedule,
                                            IslPtr<isl_union_set> Writes,
                                            IslPtr<isl_union_set> Reads,
                                            bool ReadEltInSameInst,
                                            bool InclWrite, bool InclLastRead,
                                            bool ExitReads) {

  // { DomainWrite[] -> Element[] }
  auto WritesElt = give(isl_union_map_from_domain(Writes.take()));

  // { DomainRead[] -> Element[] }
  auto ReadsElt = give(isl_union_map_from_domain(Reads.take()));

  // { [Element[] -> DomainWrite[]] -> Scatter[] }
  auto Result =
      computeArrayLifetime(Schedule, WritesElt, ReadsElt, ReadEltInSameInst,
                           InclWrite, InclLastRead, ExitReads);

  return give(isl_union_map_domain_factor_range(Result.take()));
}

/// Compute the lifetime of a scalar with a single definition.
///
/// Because there is only one defining statement, takes only an isl_map for
/// writes and only returns an isl_map.
///
/// @param Schedule          { Domain[] -> Scatter[] }
/// @param Writes            { DomainWrite[] }
/// @param Reads             { DomainRead[] }
/// @param ReadEltInSameInst A read at the same timepoint as a write will read
/// that value instead of the previous's.
/// @param InclWrite         Include the write itself to the lifetime.
/// @param InclLastRead      Include the last write to the lifetime.
/// @param ExitReads         Extend the last definition to infinity.
///
/// @return { DomainWrite[] -> Zone[] }
///         The scalar's lifetime.
///
/// @see computeArrayLifetime
IslPtr<isl_map> computeScalarLifetime(IslPtr<isl_union_map> Schedule,
                                      IslPtr<isl_set> Writes,
                                      IslPtr<isl_union_set> Reads,
                                      bool ReadEltInSameInst, bool InclWrite,
                                      bool InclLastRead, bool ExitsReads) {
  return give(isl_map_from_union_map(
      computeScalarLifetime(
          Schedule, give(isl_union_set_from_set(Writes.take())), Reads,
          ReadEltInSameInst, InclWrite, InclLastRead, ExitsReads)
          .take()));
}

/// Simplify the a map inplace.
void simplify(IslPtr<isl_map> &Map) {
  Map = give(isl_map_compute_divs(Map.take()));
  Map = give(isl_map_detect_equalities(Map.take()));
  Map = give(isl_map_coalesce(Map.take()));
}

/// Simplify the a union map inplace.
void simplify(IslPtr<isl_union_map> &Map) {
  Map = give(isl_union_map_compute_divs(Map.take()));
  Map = give(isl_union_map_detect_equalities(Map.take()));
  Map = give(isl_union_map_coalesce(Map.take()));
}

/// If InputVal is not defined in the stmt itself, return the MemoryAccess that
/// reads the scalar. Return nullptr otherwise (if the value is defined in the
/// scop, or is synthesizable)
MemoryAccess *getInputAccessOf(Value *InputVal, ScopStmt *Stmt) {
  for (auto *MA : *Stmt) {
    if (!MA->isRead())
      continue;
    if (!MA->isLatestScalarKind())
      continue;

    assert(MA->getAccessValue() == MA->getBaseAddr());
    if (MA->getAccessValue() == InputVal)
      return MA;
  }
  return nullptr;
}

/// Try to find a 'natural' extension of a mapped to elements outside its
/// domain.
///
/// @param Relevant The map with mapping that may not be modified.
/// @param Universe The domain to which @p Relevant needs to be extended.
///
/// @return A map with that associates the domain elements of @p Relevant to the
/// same elements and in addition the elements of @p Universe to some undefined
/// elements. The function prefers to return simple maps.
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
/// state means that an element is currently unused: there is no read of it
/// before the next overwrite. Also called 'existing'.
/// 2) To represent the requirements for mapping a scalar to array elements. The
/// undef state means that there is no change/requirement. Also called
/// 'proposed'.
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
    // Default-initialized object
    if (!Lifetime && !Written)
      return;

    assert(Lifetime);
    assert(Written);
    assert(isl_union_map_is_single_valued(Lifetime.keep()) == isl_bool_true);
  }

  /// Ensure an unique representation depending on ImplicitLifetimeIsUnknown.
  void canonicalize() {
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

  /// Alternative ctor taking isl_maps instead isl_union_map.
  Knowledge(IslPtr<isl_map> Lifetime, bool ImplicitLifetimeIsUnknown,
            IslPtr<isl_map> Written)
      : Knowledge(give(isl_union_map_from_map(Lifetime.take())),
                  ImplicitLifetimeIsUnknown,
                  give(isl_union_map_from_map(Written.take()))) {}

  /// Return whether this object was default-constructed.
  bool isUsable() const { return Lifetime && Written; }

  /// Print the content of this object to @p OS.
  void print(llvm::raw_ostream &OS, unsigned indent = 0) const {
    if (isImplicitLifetimeUnknown())
      OS.indent(indent) << "Lifetime: " << Lifetime << " + Unknown\n";
    else
      OS.indent(indent) << "Lifetime: " << Lifetime << " + Undef\n";
    OS.indent(indent) << "Written : " << Written << '\n';
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

    auto ThatKnowDomain = filterKnownValInst(That.Lifetime);
    auto ThatDomain = give(isl_union_map_domain(That.Lifetime.take()));

    Lifetime =
        give(isl_union_map_subtract_domain(Lifetime.take(), ThatDomain.take()));
    Lifetime =
        give(isl_union_map_union(Lifetime.take(), ThatKnowDomain.take()));

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
  /// to be 'implicit unknown' (use case 1).
  /// @param Proposed One of the knowledges; current implementation requires it
  /// to be 'implicit undef' (use case 2).
  /// @param OS Dump the conflict reason to this output stream; use nullptr to
  /// not output anything.
  /// @param Indent Indention for the conflict reason.
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
    // the same llvm::Value instance
    // 7) Written Known/Unknown vs Written Known/Unknown, where the first writes
    // to the same location and at the same timepoint as the latter
    // TODO: Exception to 7) if the same value is written

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
        OS->indent(Indent + 2) << "Existing wants: " << ExistingConflict
                               << '\n';
        OS->indent(Indent + 2) << "Proposed wants: " << ProposedConflict
                               << '\n';
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
    if (!isl_union_set_is_disjoint(ExistingWrittenDomain.keep(),
                                   ProposedWrittenDomain.keep())) {
      if (OS) {
        OS->indent(Indent)
            << "Conflict because of existing/proposed undefined write order\n";
        auto Overlap = give(isl_union_set_intersect(
            ExistingWrittenDomain.take(), ProposedWrittenDomain.take()));
        auto ExistingOverwrite = give(isl_union_map_intersect_domain(
            Existing.Written.copy(), Overlap.copy()));
        auto ProposedOverwrite = give(isl_union_map_intersect_domain(
            Proposed.Written.copy(), Overlap.take()));
        OS->indent(Indent + 2)
            << "Existing wants to write: " << ExistingOverwrite << '\n';
        OS->indent(Indent + 2)
            << "Proposed wants to write: " << ProposedOverwrite << '\n';
      }
      return true;
    }

    return false;
  }
};
} // anonymous namespace

void Knowledge::dump() const { print(llvm::errs()); }

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
  assert(isl_union_map_is_bijective(Schedule.keep()));

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

namespace {

/// Base class for algorithms based on zones, like DeLICM.
class ZoneAlgorithm {
protected:
  Scop *S;
  isl_ctx *IslCtx;

  IslPtr<isl_union_map> Schedule;
  IslPtr<isl_space> ParamSpace;
  IslPtr<isl_space> ScatterSpace;

  IslPtr<isl_union_map> EmptyUnionMap;
  IslPtr<isl_union_set> EmptyUnionSet;

  /// Prepare the object before computing the zones of @p S.
  ZoneAlgorithm(Scop *S)
      : S(S), IslCtx(S->getIslCtx()), Schedule(give(S->getSchedule())),
        ParamSpace(give(isl_union_map_get_space(Schedule.keep()))) {

    auto Domains = give(S->getDomains());
    ParamSpace = give(isl_space_align_params(
        ParamSpace.take(), isl_union_set_get_space(Domains.keep())));
    Schedule =
        give(isl_union_map_intersect_domain(Schedule.take(), Domains.take()));
    ScatterSpace = getScatterSpace(Schedule);

    EmptyUnionMap = give(isl_union_map_empty(ParamSpace.copy()));
    EmptyUnionSet = give(isl_union_set_empty(ParamSpace.copy()));
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

  /// Create an isl_id that represent 'unused storage'.
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

  IslPtr<isl_id> makeValueId(Value *V) const {
    if (!V)
      return makeUnknownId();
    if (isa<UndefValue>(V))
      return makeUndefId();
    auto Name = getIslCompatibleName("Val_", V, std::string());
    return give(isl_id_alloc(IslCtx, Name.c_str(), V));
  }
  IslPtr<isl_space> makeValueSpace(Value *V) const {
    auto Result = give(isl_space_set_from_params(ParamSpace.copy()));
    return give(isl_space_set_tuple_id(Result.take(), isl_dim_set,
                                       makeValueId(V).take()));
  }

  IslPtr<isl_set> makeValueSet(Value *V) const {
    auto Space = makeValueSpace(V);
    return give(isl_set_universe(Space.take()));
  }

  // { UserDomain[] -> ValInst[] }
  IslPtr<isl_map> makeValInst(Value *Val, IslPtr<isl_set> DefDomain,
                              ScopStmt *UserStmt, bool IsCertain) {
    return makeValInst(Val, std::move(DefDomain), UserStmt,
                       getDomainFor(UserStmt), IsCertain);
  }

  // { UserDomain[] -> ValInst[] }
  IslPtr<isl_map> makeValInst(Value *Val, ScopStmt *UserStmt,
                              bool IsCertain = true) {
    return makeValInst(Val, nullptr, UserStmt, getDomainFor(UserStmt),
                       IsCertain);
  }

  // { UserDomain[] -> ValInst[] }
  IslPtr<isl_map> makeValInst(Value *V, IslPtr<isl_set> DefDomain,
                              ScopStmt *UserStmt, IslPtr<isl_set> UserDomain,
                              bool IsCertain) {
    assert(UserDomain);

    if (!V && !UserStmt)
      return give(isl_map_from_domain(UserDomain.take()));

    if (!IsCertain)
      return give(isl_map_from_domain(UserDomain.take()));

    if (!isa<Instruction>(V)) {
      // Available anywhere
      auto ValSet = makeValueSet(V);
      return give(
          isl_map_from_domain_and_range(UserDomain.take(), ValSet.take()));
    }

    // FIXME: Should use transitivity in case of LCSSA (ReachingDefinition for
    // each %phi)
    // It doesn't really work well if the LCSSA %phi is intra-stmt, but the
    // incoming value is extra-phi.
    // TODO: Actually, in the SCop, we should be able to determine the
    // predecessor for _every_ PHI.
    auto NormV = deLCSSA(V);

    if (!DefDomain && !isXtraStmtUse(V, UserStmt)) {
      // assert(V==NormV && "Cannot yet handle the case where NormV is
      // extra-stmt");
      // Easy case: the definition is in the using Stmt itself, so use UserDom[]
      // for the Value's instance.
      // Not that the non-isIntraStmtUse assumes extra-Stmt use, ie. a use would
      // use the definition from a previous instance.

      // { llvm::Value }
      auto ValSet = makeValueSet(NormV);

      // {  UserDomain[] -> llvm::Value }
      auto ValInstSet =
          give(isl_map_from_domain_and_range(UserDomain.take(), ValSet.take()));

      // { UserDomain[] -> [UserDomain[] - >llvm::Value] }
      auto Result =
          give(isl_map_reverse(isl_map_domain_map(ValInstSet.take())));
      simplify(Result);
      return Result;
    }

    if (!DefDomain) {
      auto Inst = dyn_cast<Instruction>(NormV);
      auto ValStmt = S->getStmtFor(Inst);

      if (!ValStmt) {
        // Cannot associate with an instance; return as if unknown
        // TODO: Maybe look for successor/predecessor and link to its instance.
        // { Domain[] -> [] }
        return give(isl_map_from_domain(UserDomain.take()));
      }

      // { DefDomain[] -> Scatter[] }
      DefDomain = getDomainFor(ValStmt);
    }

    // { Scatter[] -> DefDomain[] }
    auto ReachDef =
        computeScalarReachingDefinition(Schedule, DefDomain, false, true);

    // { UserDomain[] -> Scatter[] }
    auto UserSched = getScatterFor(UserDomain);

    // { UserDomain[] -> DefDomain[] }
    auto UsedInstance =
        give(isl_map_apply_range(UserSched.take(), ReachDef.take()));

    // { llvm::Value }
    auto ValSet = makeValueSet(NormV);

    // { UserDomain[] -> llvm::Value }
    auto ValInstSet =
        give(isl_map_from_domain_and_range(UserDomain.take(), ValSet.take()));

    // { UserDomain[] -> [DefDomain[] -> llvm::Value]  }
    auto Result =
        give(isl_map_range_product(UsedInstance.take(), ValInstSet.take()));
    simplify(Result);
    return Result;
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

#if 0
  /// Determine whether an instruction is defined in the same statement instance as in which it is used.
  ///
  /// @param Val      The instruction defining a value.
  /// @param UserStmt The statement using @p Val. The use must not be a PHI, they must handled separately.
  ///
  /// @return True iff @p Val is defined in @p UserStmt.
  bool isIntraStmtUse(Value *Val, ScopStmt *UserStmt) const {
    assert(UserStmt);
    auto *Inst = dyn_cast<Instruction>(Val);

	// Non-instructions (eg. literals) are not adding to complexity
    if (!Inst) {
		assert(false);
      return false;
	}

    auto *DefStmt = S->getStmtFor(Inst);

    // This assumes that there must be a PHI in the same statement if we are
    // going to use a value from a previous execution of the same statement.
    return DefStmt == UserStmt;
  }
#endif

  /// Determine whether an instruction is defined in a different statement
  /// instance as in which it is used.
  ///
  /// @param Val      The instruction defining a value.
  /// @param UserStmt The statement using @p Val. The use must not be a PHI,
  /// they must handled separately.
  ///
  /// @return True iff a use of @p Val in @p UserStmt introduces a
  /// flow-dependency.
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
  /// occur before the writes.
  /// - Two writes to the same location; we cannot model the order in which
  /// these occur.
  ///
  /// Scalar reads implicitly always occur before other access therefore never
  /// violate the first condition. There is also at most one write to a scalar,
  /// satisfying the second condition.
  bool isAcceptableStmt(ScopStmt *Stmt) {
    auto Stores = EmptyUnionMap;
    auto Loads = EmptyUnionMap;

    // This assumes that the MK_Array MemoryAccesses are iterated in order.
    for (auto *MA : *Stmt) {
      if (!MA->isLatestArrayKind())
        continue;

      auto AccRel = give(isl_union_map_from_map(MA->getAccessRelation()));

      if (MA->isRead()) {
        // Reject store after load to same location.
        if (!isl_union_map_is_disjoint(Stores.keep(), AccRel.keep()))
          return false;

        Loads = give(isl_union_map_union(Loads.take(), AccRel.take()));
      }

      if (MA->isWrite()) {
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

protected:
  // { [Element[] -> Zone[]] -> DomainWrite[] }
  IslPtr<isl_union_map> WriteReachDefZone;

  // { DomainMayWrite[] -> Element[] }
  IslPtr<isl_union_map> AllMayWrites;

  // { DomainMustWrite[] -> Element[] }
  IslPtr<isl_union_map> AllMustWrites;

  // { Element[] -> Zone[] }
  IslPtr<isl_union_map> UniverseZone;

  // { [Element[] -> DomainWrite[]] -> ValInst[] }
  IslPtr<isl_union_map> AllWriteValInst;

  // { [Element[] -> DomainRead[]] -> ValInst[] }
  IslPtr<isl_union_map> AllReadValInst;

  // { DomainRead[] -> Element[] }
  IslPtr<isl_union_map> AllReads;

  // { DomainWrite[] -> Element[] }
  IslPtr<isl_union_map> AllWrites;

  // { Element[] -> Element[] }
  IslPtr<isl_union_map> AllElementsId;

  bool computeCommon() {
    // Check that nothing strange occurs.
    for (auto &Stmt : *S) {
      if (!isAcceptableStmt(&Stmt))
        return false;
    }

    // { DomainRead[] -> Element[] }
    AllReads = EmptyUnionMap;

    // { DomainMayWrite[] -> Element[] }
    AllMayWrites = EmptyUnionMap;

    // { DomainMustWrite[] -> Element[] }
    AllMustWrites = EmptyUnionMap;

    // { [Element[] -> DomainWrite[]] -> ValInst[] }
    AllWriteValInst = EmptyUnionMap;

    // { [Element[] -> DomainRead[]] -> ValInst[] }
    AllReadValInst = EmptyUnionMap;

    // TODO: Identify and ensure non-usability of possible dependency within the
    // statement.
    for (auto &Stmt : *S) {
      for (auto *MA : Stmt) {
        if (!MA->isLatestArrayKind())
          continue;

        if (MA->isRead()) {
          // { DomainRead[] -> Element[] }
          auto AccRel = getAccessRelationFor(MA);
          AllReads =
              give(isl_union_map_add_map(AllReads.take(), AccRel.copy()));

          auto LI = dyn_cast_or_null<LoadInst>(MA->getAccessInstruction());
          if (LI) { // TODO: Maybe use MA->getAccessValue()
                    // { DomainRead[] -> ValInst[] }
            auto LoadValInst = makeValInst(
                LI, &Stmt,
                Stmt.isBlockStmt() /* In Region Statements could be a 'MayRead' */);

            // { DomainRead[] -> [Element[] -> DomainRead[]] }
            auto IncludeElement =
                give(isl_map_curry(isl_map_domain_map(AccRel.take())));

            // { [Element[] -> DomainRead[]] -> ValInst[] }
            auto EltLoadValInst = give(isl_map_apply_domain(
                LoadValInst.take(), IncludeElement.take()));

            AllReadValInst = give(isl_union_map_add_map(AllReadValInst.take(),
                                                        EltLoadValInst.take()));
          }

          continue;
        }

        auto SI = dyn_cast<StoreInst>(MA->getAccessInstruction());
        if (!SI) {
          DEBUG(dbgs() << "WRITE that is not a StoreInst not supported\n");
          return false;
        }

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
            makeValInst(MA->getAccessValue(), &Stmt, MA->isMustWrite());

        // { Domain[] -> [Element[] -> Domain[]] }
        auto IncludeElement =
            give(isl_map_curry(isl_map_domain_map(AccRel.copy())));

        // { [Element[] -> DomainWrite[]] -> ValInst[] }
        auto EltWriteValInst = give(isl_map_apply_domain(
            WriteValInstance.take(), IncludeElement.take()));

        AllWriteValInst = give(isl_union_map_add_map(AllWriteValInst.take(),
                                                     EltWriteValInst.take()));
      }
    }

    // { DomainRead[] -> ValInst[] }
    AllReadValInst = filterKnownValInst(AllReadValInst);

    // { DomainWrite[] -> Element[] }
    AllWrites =
        give(isl_union_map_union(AllMustWrites.copy(), AllMayWrites.copy()));

    // { Element[] }
    auto AllElements = give(isl_union_set_empty(ParamSpace.copy()));
    foreachElt(AllWrites, [=, &AllElements](IslPtr<isl_map> Write) {
      auto Space = give(isl_map_get_space(Write.keep()));
      auto EltSpace = give(isl_space_range(Space.take()));
      auto EltUniv = give(isl_set_universe(EltSpace.take()));
      AllElements =
          give(isl_union_set_add_set(AllElements.take(), EltUniv.take()));
    });

    // { Element[] -> Element[] }
    AllElementsId = makeIdentityMap(AllElements, false);

    // { Element[] -> Zone[] }
    UniverseZone = give(isl_union_map_from_domain_and_range(
        AllElements.copy(),
        isl_union_set_from_set(isl_set_universe(ScatterSpace.copy()))));

    // { [Element[] -> Zone[]] -> DomainWrite[] }
    WriteReachDefZone =
        computeReachingDefinition(Schedule, AllWrites, false, true);

    simplify(WriteReachDefZone);
    return true;
  }

protected:
  // { [Element[] -> Domain[]] -> Scatter[] }
  IslPtr<isl_map> getEltDomScatter(MemoryAccess *MA) const {
    // { Domain[] -> Element[] }
    auto Acc = getAccessRelationFor(MA);

    // { Domain[] -> Scatter[] }
    auto Scatter = getScatterFor(MA);

    // { [Element[] -> Domain[]] -> Domain[] }
    auto EltDomDom = give(isl_map_range_map(isl_map_reverse(Acc.take())));

    // { [Element[] -> Domain[]] -> Scatter[] }
    return give(isl_map_apply_range(EltDomDom.take(), Scatter.take()));
  }

  IslPtr<isl_map> getScatterFor(ScopStmt *Stmt) const {
    auto Dom = getDomainFor(Stmt);
    auto Space = give(isl_set_get_space(Dom.keep()));
    auto Domain = give(isl_union_set_from_set(Dom.take()));
    // TODO: getSchedule() is already intersected with all domains(?), no need
    // to do again.
    auto Sched =
        give(isl_union_map_intersect_domain(Schedule.copy(), Domain.take()));
    return singleton(Sched, give(isl_space_map_from_domain_and_range(
                                Space.take(), ScatterSpace.copy())));
  }

  IslPtr<isl_map> getScatterFor(ScopStmt &Stmt) const {
    return getScatterFor(&Stmt);
  }

  // TODO: There is currently no notion of where within a statement an access
  // occurs. This leads to problem such as the lifetime of a scalar:
  // Def at [0,0,0]
  // Use at [0,0,1]
  // Because a scalar write occurs after everything in the statement, and a read
  // before, neither [0,0,0] nor [0,0,1] belong to the lifetime. Therefore the
  // lifetime would be empty, equivalent to not requiring storage at all.
  // The current workaround is the write belongs to the lifetime. This will
  // make mapping of the result of LoadInst of the location mapped-to (typical
  // for reductions) impossible since at timestep [0,0,0] the array element it
  // reads from still occupies the memory.
  // Better solutions:
  // Multiply every scatter by two (or more); adds the odd numbers between two
  // scatters
  // - Append another dimensions such that there's something between [0,0,0] and
  // [0,0,1] (namely, eg. [0,0,0,1])
  // - Adding a dimension also allow a notation of "before" the statement
  // [0,0,0,-1] and "after" it [0,0,0,1]
  // - Might give each instruction its own 'order number'
  // - Allow rational solutions.
  // - Treat a zone coordinate [0,0,0] as "right after statement instance
  // [0,0,0]"/"between instance [0,0,0] and [0,0,1]" (staggered grid); will
  // require adding/subtraction 1 to convert between before and after; this
  // works along the line of the current workaround.
  IslPtr<isl_map> getScatterFor(MemoryAccess *MA) const {
    return getScatterFor(MA->getStatement());
  }

  IslPtr<isl_map> getScatterFor(IslPtr<isl_set> Domain) const {
    auto Space = give(isl_space_map_from_domain_and_range(
        isl_set_get_space(Domain.keep()), ScatterSpace.copy()));
    auto Sched = give(isl_union_map_extract_map(Schedule.keep(), Space.take()));
    assert(isMapDomainSubsetOf(Sched, Domain) != isl_bool_false);
    return give(isl_map_intersect_domain(Sched.take(), Domain.take()));
  }

  IslPtr<isl_set> getDomainFor(ScopStmt *Stmt) const {
    return give(Stmt->getDomain());
  }

  IslPtr<isl_set> getDomainFor(MemoryAccess *MA) const {
    return getDomainFor(MA->getStatement());
  }

  IslPtr<isl_map> getAccessRelationFor(MemoryAccess *MA) const {
    auto Domain = give(MA->getStatement()->getDomain());
    auto AccRel = give(MA->getLatestAccessRelation());
    return give(isl_map_intersect_domain(AccRel.take(), Domain.take()));
  }
  IslPtr<isl_union_map> getSchedule() const { return Schedule; }

  // friend class Knowledge;

public:
  /// Return the SCoP this object is analyzing.
  Scop *getScop() const { return S; }
};

struct MapReport {
  MemoryAccess *NormMA;
  int NumAccesses;
  IslPtr<isl_map> Target;
  IslPtr<isl_map> Lifetime;
  Knowledge Zone;

  MapReport(MemoryAccess *NormMA, int NumAccesses, IslPtr<isl_map> Target,
            IslPtr<isl_map> Lifetime, Knowledge Zone)
      : NormMA(NormMA), NumAccesses(NumAccesses), Target(std::move(Target)),
        Lifetime(std::move(Lifetime)), Zone(std::move(Zone)) {
    DEBUG(print(llvm::dbgs(), 0));
  }

  MapReport(const MapReport &That) = delete;
  MapReport(MapReport &&That)
      : NormMA(That.NormMA), NumAccesses(That.NumAccesses), Target(That.Target),
        Lifetime(That.Lifetime), Zone(std::move(That.Zone)) {
    That.Target = nullptr;
    That.Lifetime = nullptr;
  }

  void print(llvm::raw_ostream &OS, int indent = 0) const {
    OS.indent(indent) << "Scalar access " << *NormMA << ":\n";
    OS.indent(indent + 4) << "Accesses:  " << NumAccesses << "\n";
    OS.indent(indent + 4) << "Target:    " << Target << "\n";
    OS.indent(indent + 4) << "Lifetime:  " << Lifetime << "\n";
    OS.indent(indent + 4) << "Zone:\n";
    Zone.print(OS, indent + 8);
  }
};

class DeLICMImpl : public ZoneAlgorithm {
private:
  Knowledge OriginalZone;
  Knowledge Zone;

  SmallVector<MapReport, 8> MapReports;

  bool isConflicting(const Knowledge &Proposed) {
    raw_ostream *OS = nullptr;
    DEBUG(OS = &llvm::dbgs());
    return Knowledge::isConflicting(Zone, Proposed, OS, 4);
  }

  MemoryAccess *getDefAccsFor(const ScopArrayInfo *SAI) {
    assert(SAI);
    auto *MA = ValueDefAccs.lookup(SAI);
    assert(MA);
    assert(MA->isOriginalValueKind());
    assert(MA->isWrite());
    return MA;
  }

  MemoryAccess *getPHIAccsFor(const ScopArrayInfo *SAI) {
    assert(SAI);
    auto *MA = PHIReadAccs.lookup(SAI);
    assert(MA);
    assert(MA->isOriginalAnyPHIKind());
    assert(MA->isRead());
    return MA;
  }

  bool isMappable(const ScopArrayInfo *SAI) {
    assert(SAI);

    if (SAI->isValueKind()) {
      auto *MA = ValueDefAccs.lookup(SAI);
      if (!MA) {
        DEBUG(dbgs()
              << "    Reject because value is read-only within the scop\n");
        return false;
      }

      // Mapping if value is used after scop is not supported.s
      auto Inst = MA->getAccessInstruction();
      for (auto User : Inst->users()) {
        if (!isa<Instruction>(User))
          return false; // Play safe with strange user
        auto UserInst = cast<Instruction>(User);

        if (!S->contains(UserInst)) {
          DEBUG(dbgs() << "    Reject because value is escaping\n");
          return false;
        }
      }
      return true;
    }

    if (SAI->isPHIKind()) {
      auto *MA = getPHIAccsFor(SAI);

      // Mapping if PHI has incoming block from before the block is not
      // supported.
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

    DEBUG(dbgs() << "    Reject ExitPHI or other non-Value\n");
    return false;
  }

  // { DomainValueDef[] -> Zone[] }
  // Get the zone from a scalar's definition to its last use.
  // TODO: Cache results?
  // TODO: Values might be escaping to after the scop; need to exclude such
  // scalars or extend their lifetime as ray
  /// Compute the lifetime of an MK_Value (from the definition to the last use)
  /// Pass the WRITE MemoryAccess that defines the llvm::Value
  /// { DomainDef[] -> Zone[] }
  IslPtr<isl_map> computeValueLifetime(const ScopArrayInfo *WA) {
    assert(WA->isValueKind());

    // { DomainRead[] }
    auto Reads = give(isl_union_set_empty(ParamSpace.copy()));

    // Find all uses
    // TODO: Create a map of defs and uses

    for (auto *MA : ValueUseAccs.lookup(WA))
      Reads =
          give(isl_union_set_add_set(Reads.take(), getDomainFor(MA).take()));

    // { DomainDef[] }
    auto Writes = getDomainFor(ValueDefAccs.lookup(WA));

    // { DomainDef[] -> Zone[] }
    auto Lifetime = computeScalarLifetime(Schedule, Writes, Reads, false, false,
                                          true, false);

    // TODO: This does not consider uses of the scalar after the scop; we
    // currently bail out if there is such a use.
    return Lifetime;
  }

  // { DomainPHIRead[] -> DomainPHIWrite[] }
  IslPtr<isl_union_map> computePerPHI(const ScopArrayInfo *SAI) {
    assert(SAI->isPHIKind());

    // { DomainPHIWrite[] -> Scatter[] }
    auto PHIWriteScatter = give(isl_union_map_empty(ParamSpace.copy()));

    for (auto *MA : PHIIncomingAccs.lookup(SAI)) {
      auto Scatter = getScatterFor(MA);
      PHIWriteScatter =
          give(isl_union_map_add_map(PHIWriteScatter.take(), Scatter.take()));
    }

    // For each PHIRead instance, find the PHI instance which writes it.
    // We assume that there must be exactly one!

    // { DomainPHIRead[] -> Scatter[] }
    auto PHIReadScatter = getScatterFor(PHIReadAccs.lookup(SAI));

    // { DomainPHIRead[] -> Scatter[] }
    auto BeforeRead = beforeScatter(PHIReadScatter, true);

    // { Scatter[] }
    auto WriteTimes = singleton(
        give(isl_union_map_range(PHIWriteScatter.copy())), ScatterSpace);

    // { DomainPHIRead[] -> Scatter[] }
    auto PHIWriteTimes =
        give(isl_map_intersect_range(BeforeRead.take(), WriteTimes.take()));
    auto LastPerPHIWrites = give(isl_map_lexmax(PHIWriteTimes.take()));

    // { DomainPHIRead[] -> DomainPHIWrite[] }
    auto PerPHIWrite = give(isl_union_map_apply_range(
        isl_union_map_from_map(LastPerPHIWrites.take()),
        isl_union_map_reverse(PHIWriteScatter.take())));

    return PerPHIWrite;
  }

  // TODO: No need for RefMA
  /// @param RefMA The MemoryAccess that is sought to be mapped to @p TargetElt
  /// @param DefMA The definition MemoryAccess MUST_WRITE for the same value
  /// (unique).
  bool tryMapValue(const ScopArrayInfo *SAI, MemoryAccess *RefMA,
                   // { Zone[] -> Element[] }
                   IslPtr<isl_map> TargetElt) {
    assert(SAI->isValueKind());
    auto *DefMA = ValueDefAccs.lookup(SAI);
    assert(DefMA->isValueKind());
    assert(DefMA->isMustWrite());
    assert(RefMA->isValueKind());
    //    assert(isLatestAccessingSameScalar(DefMA, RefMA));
    // TODO: Check same(or at least more) byte size
    // Means it already has been mapped
    if (!DefMA->getLatestScopArrayInfo()->isValueKind())
      return false;

    auto V = DefMA->getAccessValue();

    // { DomainDef[] -> Scatter[] }
    auto DefSched = getScatterFor(DefMA);

    // Where each write is mapped to
    // { DomainDef[] -> Element[] }
    auto DomDefTargetElt = give(isl_map_apply_domain(
        TargetElt.copy(), isl_map_reverse(DefSched.copy())));

    simplify(DomDefTargetElt);
    DEBUG(dbgs() << "    Mapping: " << DomDefTargetElt << "\n");

    auto OrigDomain = getDomainFor(DefMA);
    auto MappedDomain = give(isl_map_domain(DomDefTargetElt.copy()));
    if (!isl_set_is_subset(OrigDomain.keep(), MappedDomain.keep())) {
      DEBUG(dbgs().indent(4)
            << "Reject because mapping does not encompass all instances.\n");
      return false;
    }

    // { DomainDef[] -> Zone[] }
    auto Lifetime = computeValueLifetime(SAI);
    if (!Lifetime)
      return false;

    simplify(Lifetime);
    DEBUG(dbgs() << "    Lifetime: " << Lifetime << "\n");

    // { DefDomain[] -> [Element[] -> Zone[]] }
    auto EltLifetimeTranslator =
        give(isl_map_range_product(DomDefTargetElt.copy(), Lifetime.copy()));

    // { DefDomain[] -> [Element[] -> Scatter[]] }
    auto WrittenTranslator =
        give(isl_map_range_product(DomDefTargetElt.copy(), DefSched.take()));

    // { DefDomain[] -> ValInst[] }
    auto ValInst = makeValInst(V, DefMA->getStatement(), true);

    // { [Element[] -> Zone[]] -> ValInst[] }
    auto EltLifetime = give(
        isl_map_apply_domain(ValInst.copy(), EltLifetimeTranslator.take()));

    // { [Element[] -> Scatter[]] -> ValInst[] }
    auto EltWriteAction =
        give(isl_map_apply_domain(ValInst.copy(), WrittenTranslator.take()));

    Knowledge Proposed(EltLifetime, false, EltWriteAction);

    if (isConflicting(Proposed))
      return false;

    // OK to map
    mapValue(SAI, DomDefTargetElt, Lifetime, std::move(Proposed));
    return true;
  }

  void applyLifetime(Knowledge Proposed) {
    Zone.merge_inplace(std::move(Proposed));
  }

  void mapValue(const ScopArrayInfo *SAI,
                // { DomainDef[] -> Element[] }
                IslPtr<isl_map> Mapping,
                // { DomainDef[] -> Zone[] }
                IslPtr<isl_map> Lifetime, Knowledge Proposed) {
    auto *WA = ValueDefAccs.lookup(SAI);
    // TODO: This must already have been computed before: reuse
    // { Scatter[] -> DomainDef[] }
    auto ReachDef = computeScalarReachingDefinition(Schedule, getDomainFor(WA),
                                                    false, true);
    assert(ReachDef && "Operations count exceeded?");

    // { Scatter[] -> Element[] }
    auto TargetZone =
        give(isl_map_apply_range(ReachDef.take(), Mapping.copy()));
    simplify(TargetZone);
    int NumMappedAccessed = 1;

    for (auto *MA : ValueUseAccs.lookup(SAI)) {
      // { Domain[] -> Scatter[] }
      auto Sched = getScatterFor(MA);

      // { Domain[] -> Element[] }
      auto NewAccRel =
          give(isl_map_apply_range(Sched.take(), TargetZone.copy()));

      simplify(NewAccRel);
      MA->setNewAccessRelation(NewAccRel.take());
      NumMappedAccessed += 1;
    }

    WA->setNewAccessRelation(Mapping.copy());

    applyLifetime(Proposed);

    MappedValueScalars++;
    MapReports.emplace_back(WA, NumMappedAccessed, Mapping, Lifetime,
                            std::move(Proposed));
  }

  IslPtr<isl_union_set>
  wholeStmtDomain(NonowningIslPtr<isl_union_set> RelevantDomain) {
    auto Universe = give(isl_union_set_empty(ParamSpace.copy()));
    foreachElt(RelevantDomain, [&Universe](IslPtr<isl_set> Dom) {
      auto Space = give(isl_set_get_space(Dom.keep()));
      auto DomUniv = give(isl_set_universe(Space.take()));
      Universe = give(isl_union_set_add_set(Universe.take(), DomUniv.take()));
    });
    return give(isl_union_set_intersect(Universe.take(),
                                        isl_union_map_domain(Schedule.copy())));
  }

  IslPtr<isl_union_map> expandMapping(IslPtr<isl_union_map> Relevant) {
    auto RelevantDomain = give(isl_union_map_domain(Relevant.copy()));
    auto Universe = wholeStmtDomain(RelevantDomain);
    return ::expandMapping(Relevant, Universe);
  }

  // { PHIWriteDomain[] -> ValInst[] }
  IslPtr<isl_union_map> determinePHIWrittenValues(const ScopArrayInfo *SAI) {
    auto *PHIRead = this->PHIReadAccs.lookup(SAI);
    auto Result = EmptyUnionMap;
    // auto PHIInst = cast<PHINode>( PHIRead->getAccessValue());
    auto *ReadStmt = PHIRead->getStatement();

    for (auto *MA : PHIIncomingAccs.lookup(SAI)) {
      // { PHIWriteDomain[] -> ValInst[] }
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
        ValInst = give(isl_map_from_domain(getDomainFor(WriteStmt).take()));
      }

      Result = give(isl_union_map_add_map(Result.take(), ValInst.take()));
    }

    assert(isl_union_map_is_single_valued(Result.keep()));
    return Result;
  }

  bool tryMapPHI(const ScopArrayInfo *SAI,
                 // { Zone[] -> Element[] }
                 IslPtr<isl_map> Target) {
    auto PHIRead = this->PHIReadAccs.lookup(SAI);
    assert(PHIRead->isPHIKind());
    assert(PHIRead->isRead());
    // TODO: Check same(or at least more) byte size
    // Means it already has been mapped
    if (!PHIRead->getLatestScopArrayInfo()->isPHIKind())
      return false;

    // { DomainPHIRead[] -> Scatter[] }
    auto PHISched = getScatterFor(PHIRead);

    // { DomainPHIRead[] -> Element[] }
    auto PHITarget = give(isl_map_apply_range(PHISched.copy(), Target.copy()));

    simplify(PHITarget);
    DEBUG(dbgs() << "    Mapping: " << PHITarget << "\n");

    auto OrigDomain = getDomainFor(PHIRead);
    auto MappedDomain = give(isl_map_domain(PHITarget.copy()));
    // TODO: use expandMapping() as well? Are there any non-relevant PHIReads?
    // Can we get a lifetime?
    if (!isl_set_is_subset(OrigDomain.keep(), MappedDomain.keep())) {
      DEBUG(dbgs().indent(4)
            << "Reject because mapping does not encompass all instances.\n");
      return false;
    }

    // { DomainPHIRead[] -> DomainPHIWrite[] }
    auto PerPHIWrites = computePerPHI(SAI);
    assert(isl_union_map_is_single_valued(PerPHIWrites.keep()));
    assert(isl_union_map_is_injective(PerPHIWrites.keep()));

    // { DomainPHIWrite[] -> Element[] }
    auto RelevantWritesTarget =
        give(isl_union_map_reverse(isl_union_map_apply_domain(
            PerPHIWrites.copy(), isl_union_map_from_map(PHITarget.copy()))));
    simplify(RelevantWritesTarget);
    auto ExpandedTargetWrites = expandMapping(RelevantWritesTarget);
    simplify(ExpandedTargetWrites);

    // { DomainPHIWrite[] }
    auto ExpandedWritesDom =
        give(isl_union_map_domain(ExpandedTargetWrites.copy()));
    auto UniverseWritesDom = give(isl_union_set_empty(ParamSpace.copy()));
    //        wholeStmtDomain(isl_union_set_copy(ExpandedWritesDom));

    for (auto *MA : PHIIncomingAccs.lookup(SAI)) {
      UniverseWritesDom = give(isl_union_set_add_set(UniverseWritesDom.take(),
                                                     getDomainFor(MA).take()));
    }

    if (!isl_union_set_is_subset(UniverseWritesDom.keep(),
                                 ExpandedWritesDom.keep())) {
      DEBUG(dbgs() << "    Reject because did not find PHI write mapping for "
                      "all instances.\n");
      DEBUG(dbgs() << "      Relevant mapping:     " << RelevantWritesTarget
                   << "\n");
      DEBUG(dbgs() << "      Extrapolated mapping: " << ExpandedTargetWrites
                   << "\n");
      DEBUG(dbgs() << "      Missing instances: "
                   << give(isl_union_set_subtract(UniverseWritesDom.copy(),
                                                  ExpandedWritesDom.copy()))
                   << "\n");
      return false;
    }

    //  { DomainPHIRead[] -> Scatter[] }
    auto PerPHIWriteScatter = give(isl_map_from_union_map(
        isl_union_map_apply_range(PerPHIWrites.copy(), Schedule.copy())));

    // { DomainPHIRead[] -> Zone[] }
    auto Lifetime = betweenScatter(PerPHIWriteScatter, PHISched, false, true);

    // { DomainPHIWrite[] -> Zone[] }
    auto WriteLifetime = give(isl_union_map_apply_domain(
        isl_union_map_from_map(Lifetime.copy()), PerPHIWrites.copy()));

    // { DomainPHIWrite[] -> ValInst[] }
    auto WrittenValue = determinePHIWrittenValues(SAI);

    // { DomainPHIWrite[] -> [Element[] -> Scatter[]] }
    auto WrittenTranslator = give(isl_union_map_range_product(
        ExpandedTargetWrites.copy(), Schedule.copy()));

    simplify(Lifetime);
    DEBUG(dbgs() << "    Lifetime: " << Lifetime << "\n");

    // { Element[] -> Zone[] }
    auto EltLifetime =
        give(isl_map_apply_domain(Lifetime.copy(), PHITarget.copy()));

    simplify(EltLifetime);
    DEBUG(dbgs() << "    Occupancy: " << EltLifetime << "\n");

    // { DomainPHIWrite[] -> [Element[], Zone[]] }
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

  void mapPHI(const ScopArrayInfo *SAI,
              // { DomainPHIRead[] -> Element[] }
              IslPtr<isl_map> ReadMapping,
              // { DomainPHIWrite[] -> Element[] }
              IslPtr<isl_union_map> WriteMapping,
              // { DomainPHIRead[] -> Zone[] }
              IslPtr<isl_map> Lifetime, Knowledge Proposed) {
    auto *PHIRead = this->PHIReadAccs.lookup(SAI);

    // { Element[] }
    auto ElementSpace =
        give(isl_space_range(isl_map_get_space(ReadMapping.keep())));

    int NumMappedAccessed = 1;

    for (auto *MA : PHIIncomingAccs.lookup(SAI)) {
      auto DomSpace = give(MA->getStatement()->getDomainSpace());
      auto WriteTargetSpace = give(isl_space_map_from_domain_and_range(
          DomSpace.take(), ElementSpace.copy()));
      auto NewAccRel = give(isl_union_map_extract_map(WriteMapping.keep(),
                                                      WriteTargetSpace.take()));

      MA->setNewAccessRelation(NewAccRel.take());
      NumMappedAccessed += 1;
    }

    PHIRead->setNewAccessRelation(ReadMapping.copy());

    MappedPHIScalars++;
    MapReports.emplace_back(PHIRead, NumMappedAccessed, std::move(ReadMapping),
                            std::move(Lifetime), std::move(Proposed));
  }

  void collapseScalarsToStore(MemoryAccess *TargetStoreMA) {
    assert(TargetStoreMA->isLatestArrayKind());
    assert(TargetStoreMA->isMustWrite());

    auto TargetStmt = TargetStoreMA->getStatement();

    // { DomTarget[] }
    auto TargetDom = getDomainFor(TargetStmt);

    // { DomTarget[] -> Element[] }
    auto TargetAccRel = getAccessRelationFor(TargetStoreMA);

    // { Zone[] -> DomTarget[] }
    auto Target =
        computeScalarReachingOverwrite(Schedule, TargetDom, false, true);

    // { Zone[] -> Element[] }
    auto EltTarget = give(
        isl_map_apply_range(Target.take(), TargetAccRel.take())); // TODO: gist
    simplify(EltTarget);
    DEBUG(dbgs() << "    Target mapping is " << EltTarget << "\n");

    // TODO: Mark LoadInst of same element and its derivatives as preferable to
    // map.

    SmallVector<MemoryAccess *, 16> Worklist;

    auto ProcessAllIncoming = [&](ScopStmt *Stmt) {
      for (auto *MA : *Stmt) {
        if (!MA->isLatestScalarKind())
          continue;
        if (!MA->isRead())
          continue;

        Worklist.push_back(MA);
      }
    };

    auto WrittenVal = TargetStoreMA->getAccessValue();
    if (auto InputAcc = getInputAccessOf(WrittenVal, TargetStmt))
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

      if (MA->isLatestArrayKind())
        continue;

      auto *SAI = MA->getScopArrayInfo();
      assert(SAI);
      DEBUG(dbgs() << "\n    Trying to map " << MA << " (SAI: " << SAI
                   << ")\n");

      auto MASize = DL.getTypeAllocSize(MA->getAccessValue()->getType());
      if (MASize > StoreSize) {
        DEBUG(dbgs() << "    Reject because storage size is insufficient.\n");
        continue;
      }

      if (!isMappable(SAI))
        continue;

      if (SAI->isValueKind() && tryMapValue(SAI, MA, EltTarget)) {
        ProcessAllIncoming(MA->getStatement());
        AnyMapped = true;
        continue;
      }

      if (SAI->isPHIKind() && tryMapPHI(SAI, EltTarget)) {

        for (auto *PHIWrite : PHIIncomingAccs.lookup(SAI))
          ProcessAllIncoming(PHIWrite->getStatement());

        AnyMapped = true;
        continue;
      }
    }

    if (AnyMapped)
      TargetsMapped++;
  }

  void printBefore(llvm::raw_ostream &OS, int indent = 0) {
    OS.indent(indent) << "Original zone:\n";
    OriginalZone.print(OS, indent + 4);
  }

  void printMappedScalars(llvm::raw_ostream &OS, int indent = 0) {
    OS.indent(indent) << "Mapped scalars {\n";
    for (auto &Report : MapReports) {
      Report.print(OS, indent + 4);
    }
    OS.indent(indent) << "}\n";
  }

  void printAfter(llvm::raw_ostream &OS, int indent = 0) {
    OS.indent(indent) << "After zone:\n";
    Zone.print(OS, indent + 4);
  }

  void printAccesses(llvm::raw_ostream &OS, int indent = 0) {
    OS.indent(indent) << "After Statements {\n";
    for (auto &Stmt : *S) {
      OS.indent(indent + 4) << Stmt.getBaseName() << "\n";
      for (auto *MA : Stmt)
        MA->print(OS); // No indent parameters
    }
    OS.indent(indent) << "}\n";
  }

#if 0
    DenseMap<Value *, MemoryAccess *> ValueDefs;
  DenseMap<Value *, MemoryAccess *> PHIReads;
#endif

  DenseMap<const ScopArrayInfo *, MemoryAccess *> ValueDefAccs;
  DenseMap<const ScopArrayInfo *, SmallVector<MemoryAccess *, 4>> ValueUseAccs;
  DenseMap<const ScopArrayInfo *, MemoryAccess *> PHIReadAccs;
  DenseMap<const ScopArrayInfo *, SmallVector<MemoryAccess *, 4>>
      PHIIncomingAccs;

  // Find the MemoryAccess that defines an MK_Value/reads and MK_PHI.
  // MK_ExitPHIs are never mapped.
  void findScalarAccesses() {
    for (auto &Stmt : *S) {
      for (auto *MA : Stmt) {

        if (MA->isOriginalValueKind() && MA->isWrite()) {
          auto *SAI = MA->getScopArrayInfo();
          assert(!ValueDefAccs.count(SAI) &&
                 "There must be at most one definition per MK_Value scalar");
          ValueDefAccs[SAI] = MA;
        }

        if (MA->isOriginalValueKind() && MA->isRead())
          ValueUseAccs[MA->getScopArrayInfo()].push_back(MA);

        if (MA->isOriginalAnyPHIKind() && MA->isRead()) {
          auto *SAI = MA->getScopArrayInfo();
          assert(!PHIReadAccs.count(SAI) &&
                 "There must be exactly one read by "
                 "PHI (that's where the PHINode is)");
          PHIReadAccs[SAI] = MA;
        }

        if (MA->isOriginalAnyPHIKind() && MA->isWrite())
          PHIIncomingAccs[MA->getScopArrayInfo()].push_back(MA);
      }
    }
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

    // { [Element[] -> Zone[]] -> [Element[] -> DomainWrite[]] }
    auto EltReachdDef = give(isl_union_map_range_product(
        isl_union_map_domain_map(UniverseZone.copy()),
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

  /// Compute when an array element is written to.
  ///
  /// @return { [Element[] -> Scatter[]] -> ValInst[] }
  IslPtr<isl_union_map> computeWritten() const {
    // { [Element[] -> DomainWrite[]] -> [Element[] -> Scatter[]] }
    auto EltWriteTranslator =
        give(isl_union_map_product(AllElementsId.copy(), Schedule.copy()));

    // { [Element[] -> Scatter[]] -> ValInst[] }
    auto EltWritten = give(isl_union_map_apply_domain(
        AllWriteValInst.copy(), EltWriteTranslator.take()));

    simplify(EltWritten);
    return EltWritten;
  }

public:
  DeLICMImpl(Scop *S) : ZoneAlgorithm(S) {}

  /// Calculate the lifetime (definition to last use) of every array element.
  ///
  /// @return True if the computed lifetimes (#Zone) is usable.
  bool computeZone() {
    IslMaxOperationsGuard MaxOpGuard(IslCtx, DelicmMaxOps);

    if (!computeCommon())
      return false;

    findScalarAccesses();

    auto EltLifetime = computeLifetime();
    auto EltWritten = computeWritten();
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
    for (auto &Stmt : *S) {
      for (auto *MA : Stmt) {
        if (!MA->isLatestArrayKind())
          continue;
        if (!MA->isWrite())
          continue;

        if (MA->isMayWrite()) {
          DEBUG(dbgs() << "Access " << *MA
                       << " pruned because it is a MAY_WRITE\n");
          continue;
        }

        if (Stmt.getNumIterators() == 0) {
          DEBUG(dbgs() << "Access " << *MA
                       << " pruned because it is not in a loop\n");
          continue;
        }

        if (isScalarAccess(getAccessRelationFor(MA))) {
          DEBUG(dbgs() << "Access " << *MA
                       << " pruned because it writes only a single element\n");
          continue;
        }

        DEBUG(dbgs() << "Analyzing target access " << MA << "\n");
        collapseScalarsToStore(MA);
      }
    }
  }

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
  std::unique_ptr<DeLICMImpl> ZoneComputer;

  void collapseToUnused(Scop &S) {
    ZoneComputer = make_unique<DeLICMImpl>(&S);

    if (!ZoneComputer->computeZone()) {
      DEBUG(dbgs() << "Abort because cannot reliably compute lifetimes\n");
      return;
    }

    DEBUG(dbgs() << "Collapsing scalars to unused array elements...\n");
    ZoneComputer->greedyCollapse();

    DEBUG(dbgs() << "Simplifying...\n");
    S.simplifySCoP(true);

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
    if (!ZoneComputer)
      return;

    assert(ZoneComputer->getScop() == &S);
    ZoneComputer->print(OS);
  }

  virtual void releaseMemory() override {
    ZoneComputer.reset();

    // It is important to release the isl_ctx last, to ensure it is not free'd
    // before any other ISL object held.
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
