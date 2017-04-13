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
// schedule returned by Scop::getSchedule(). We call an element in that space a
// "timepoint". Timepoints are lexicographically ordered such that we can
// defined ranges in the scatter space. We use two flavors of such ranges:
// Timepoint sets and zones. A timepoint set is simply a subset of the scatter
// space and is directly stored as isl_set.
//
// Zones are used to describe the space between timepoints as open sets, i.e.
// they do not contain the extrema. Using isl rational sets to express these
// would be overkill. We also cannot store them as the integer timepoints they
// contain; the (nonempty) zone between 1 and 2 would be empty and
// indistinguishable from e.g. the zone between 3 and 4. Also, we cannot store
// the integer set including the extrema; the set ]1,2[ + ]3,4[ could be
// coalesced to ]1,3[, although we defined the range [2,3] to be not in the set.
// Instead, we store the "half-open" integer extrema, including the lower bound,
// but excluding the upper bound. Examples:
//
// * The set { [i] : 1 <= i <= 3 } represents the zone ]0,3[ (which contains the
//   integer points 1 and 2, but not 0 or 3)
//
// * { [1] } represents the zone ]0,1[
//
// * { [i] : i = 1 or i = 3 } represents the zone ]0,1[ + ]2,3[
//
// Therefore, an integer i in the set represents the zone ]i-1,i[, i.e. strictly
// speaking the integer points never belong to the zone. However, depending an
// the interpretation, one might want to include them. Part of the
// interpretation may not be known when the zone is constructed.
//
// Reads are assumed to always take place before writes, hence we can think of
// reads taking place at the beginning of a timepoint and writes at the end.
//
// Let's assume that the zone represents the lifetime of a variable. That is,
// the zone begins with a write that defines the value during its lifetime and
// ends with the last read of that value. In the following we consider whether a
// read/write at the beginning/ending of the lifetime zone should be within the
// zone or outside of it.
//
// * A read at the timepoint that starts the live-range loads the previous
//   value. Hence, exclude the timepoint starting the zone.
//
// * A write at the timepoint that starts the live-range is not defined whether
//   it occurs before or after the write that starts the lifetime. We do not
//   allow this situation to occur. Hence, we include the timepoint starting the
//   zone to determine whether they are conflicting.
//
// * A read at the timepoint that ends the live-range reads the same variable.
//   We include the timepoint at the end of the zone to include that read into
//   the live-range. Doing otherwise would mean that the two reads access
//   different values, which would mean that the value they read are both alive
//   at the same time but occupy the same variable.
//
// * A write at the timepoint that ends the live-range starts a new live-range.
//   It must not be included in the live-range of the previous definition.
//
// All combinations of reads and writes at the endpoints are possible, but most
// of the time only the write->read (for instance, a live-range from definition
// to last use) and read->write (for instance, an unused range from last use to
// overwrite) and combinations are interesting (half-open ranges). write->write
// zones might be useful as well in some context to represent
// output-dependencies.
//
// @see convertZoneToTimepoints
//
//
// The code makes use of maps and sets in many different spaces. To not loose
// track in which space a set or map is expected to be in, variables holding an
// isl reference are usually annotated in the comments. They roughly follow isl
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
// statement instance to a timepoint, aka a schedule. There is only one scatter
// space, but most of the time multiple statements are processed in one set.
// This is why most of the time isl_union_map has to be used.
//
// The basic algorithm works as follows:
// At first we verify that the SCoP is compatible with this technique. For
// instance, two writes cannot write to the same location at the same statement
// instance because we cannot determine within the polyhedral model which one
// comes first. Once this was verified, we compute zones at which an array
// element is unused. This computation can fail if it takes too long. Then the
// main algorithm is executed. Because every store potentially trails an unused
// zone, we start at stores. We search for a scalar (MemoryKind::Value or
// MemoryKind::PHI) that we can map to the array element overwritten by the
// store, preferably one that is used by the store or at least the ScopStmt.
// When it does not conflict with the lifetime of the values in the array
// element, the map is applied and the unused zone updated as it is now used. We
// continue to try to map scalars to the array element until there are no more
// candidates to map. The algorithm is greedy in the sense that the first scalar
// not conflicting will be mapped. Other scalars processed later that could have
// fit the same unused zone will be rejected. As such the result depends on the
// processing order.
//
//===----------------------------------------------------------------------===//

#include "polly/DeLICM.h"
#include "polly/CodeGen/BlockGenerators.h"
#include "polly/Options.h"
#include "polly/ScopBuilder.h"
#include "polly/ScopInfo.h"
#include "polly/ScopPass.h"
#include "polly/Support/ISLTools.h"
#include "polly/Support/VirtualInstruction.h"
#include "llvm/ADT/Statistic.h"
#define DEBUG_TYPE "polly-delicm"

using namespace polly;
using namespace llvm;

void foreachPoint(const isl::union_set &USet,
                  const std::function<void(isl::point P)> &F) {
  isl_union_set_foreach_point(
      USet.keep(),
      [](__isl_take isl_point *p, void *User) -> isl_stat {
        auto &F = *static_cast<const std::function<void(isl::point)> *>(User);
        F(give(p));
        return isl_stat_ok;
      },
      const_cast<void *>(static_cast<const void *>(&F)));
}

void foreachPoint(const isl::set &Set,
                  const std::function<void(isl::point P)> &F) {
  isl_set_foreach_point(
      Set.keep(),
      [](__isl_take isl_point *p, void *User) -> isl_stat {
        auto &F = *static_cast<const std::function<void(isl::point)> *>(User);
        F(give(p));
        return isl_stat_ok;
      },
      const_cast<void *>(static_cast<const void *>(&F)));
}

void foreachPoint(isl::basic_set BSet,
                  const std::function<void(isl::point P)> &F) {
  foreachPoint(give(isl_set_from_basic_set(BSet.take())), F);
}

isl::union_set expand(const isl::union_set &Arg) {
  auto USet = Arg;
  simplify(USet);
  isl::union_set Expanded =
      give(isl_union_set_empty(isl_union_set_get_space(USet.keep())));
  foreachElt(USet, [&](isl::set Set) {
    foreachElt(Set, [&](isl::basic_set BSet) {
      bool IsBounded = isl_basic_set_is_bounded(BSet.keep());
      if (IsBounded) {
        foreachPoint(Set, [&](isl::point P) {
          Expanded = give(isl_union_set_add_set(Expanded.take(),
                                                isl_set_from_point(P.copy())));
        });
      } else {
        Expanded = give(isl_union_set_add_set(
            Expanded.take(), isl_set_from_basic_set(BSet.copy())));
      }
    });
  });
  return Expanded;
  // foreachPoint(USet, [] (isl::point P) { llvm::errs().indent(2)  << P
  // << '\n'; });
}

void expandDump(const isl::union_set &Arg) { expand(Arg).dump(); }

isl::union_map expand(const isl::union_map &Map) {
  auto USet = expand(give(isl_union_map_wrap(Map.copy())));
  return give(isl_union_set_unwrap(USet.copy()));
}

void expandDump(const isl::union_map &Arg) { expand(Arg).dump(); }

namespace {

cl::opt<int>
    DelicmMaxOps("polly-delicm-max-ops",
                 cl::desc("Maximum number of isl operations to invest for "
                          "lifetime analysis; 0=no limit"),
                 cl::init(1000000), cl::cat(PollyCategory));

cl::opt<unsigned long>
    KnownMaxOps("polly-known-max-ops",
                cl::desc("Maximum number of ISL operations to invest for known "
                         "analysis; 0=no limit"),
                cl::init(1000000), cl::cat(PollyCategory));

cl::opt<bool> DelicmOverapproximateWrites(
    "polly-delicm-overapproximate-writes",
    cl::desc(
        "Do more PHI writes than necessary in order to avoid partial accesses"),
    cl::init(false), cl::Hidden, cl::cat(PollyCategory));

cl::opt<bool> DelicmPartialWrites("polly-delicm-partial-writes",
                                  cl::desc("Allow partial writes for PHIs"),
                                  cl::init(false), cl::Hidden,
                                  cl::cat(PollyCategory));

cl::opt<bool> DelicmMapPHI("polly-delicm-map-phi",
                           cl::desc("Map PHI to array elements"),
                           cl::init(true), cl::Hidden, cl::cat(PollyCategory));

cl::opt<bool> DelicmComputePHI("polly-delicm-compute-phi",
                               cl::desc("Compute PHI value"), cl::init(false),
                               cl::Hidden, cl::cat(PollyCategory));

STATISTIC(DeLICMAnalyzed, "Number of successfully analyzed SCoPs");
STATISTIC(DeLICMOutOfQuota,
          "Analyses aborted because max_operations was reached");
STATISTIC(DeLICMIncompatible, "Number of SCoPs incompatible for analysis");
STATISTIC(MappedValueScalars, "Number of mapped Value scalars");
STATISTIC(MappedPHIScalars, "Number of mapped PHI scalars");
STATISTIC(ComputedPHIScalars, "Number of computed PHI scalars");
STATISTIC(TargetsMapped, "Number of stores used for at least one mapping");
STATISTIC(DeLICMScopsModified, "Number of SCoPs optimized");
STATISTIC(MapRequiredUndefined,
          "Number of value maps that read an arbitrary element");
STATISTIC(MapUndefinedReject,
          "Number of value maps that would require a partial access");

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

/// Class for keeping track of scalar def-use chains in the polyhedral
/// representation.
///
/// MemoryKind::Value:
/// There is one definition per llvm::Value or zero (read-only values defined
/// before the SCoP) and an arbitrary number of reads.
///
/// MemoryKind::PHI, MemoryKind::ExitPHI:
/// There is at least one write (the incoming blocks/stmts) and one
/// (MemoryKind::PHI) or zero (MemoryKind::ExitPHI) reads per llvm::PHINode.
class ScalarDefUseChains {
public:
  /// The definitions (i.e. write MemoryAccess) of a MemoryKind::Value scalar.
  DenseMap<const ScopArrayInfo *, MemoryAccess *> ValueDefAccs;

  /// List of all uses (i.e. read MemoryAccesses) for a MemoryKind::Value
  /// scalar.
  DenseMap<const ScopArrayInfo *, SmallVector<MemoryAccess *, 4>> ValueUseAccs;

  /// The receiving part (i.e. read MemoryAccess) of a MemoryKind::PHI scalar.
  DenseMap<const ScopArrayInfo *, MemoryAccess *> PHIReadAccs;

  /// List of all incoming values (write MemoryAccess) of a MemoryKind::PHI or
  /// MemoryKind::ExitPHI scalar.
  DenseMap<const ScopArrayInfo *, SmallVector<MemoryAccess *, 4>>
      PHIIncomingAccs;

public:
  /// Find the MemoryAccesses that access the ScopArrayInfo-represented memory.
  ///
  /// @param S The SCoP to analyze.
  void compute(Scop *S) {
    // Purge any previous result.
    reset();

    for (auto &Stmt : *S) {
      for (auto *MA : Stmt) {
        if (MA->isOriginalValueKind() && MA->isWrite()) {
          auto *SAI = MA->getScopArrayInfo();
          assert(!ValueDefAccs.count(SAI) &&
                 "There can be at most one "
                 "definition per MemoryKind::Value scalar");
          ValueDefAccs[SAI] = MA;
        }

        if (MA->isOriginalValueKind() && MA->isRead())
          ValueUseAccs[MA->getScopArrayInfo()].push_back(MA);

        if (MA->isOriginalAnyPHIKind() && MA->isRead()) {
          auto *SAI = MA->getScopArrayInfo();
          assert(!PHIReadAccs.count(SAI) &&
                 "There must be exactly one read "
                 "per PHI (that's where the PHINode is)");
          PHIReadAccs[SAI] = MA;
        }

        if (MA->isOriginalAnyPHIKind() && MA->isWrite())
          PHIIncomingAccs[MA->getScopArrayInfo()].push_back(MA);
      }
    }
  }

  /// Free all memory used by the analysis.
  void reset() {
    ValueDefAccs.clear();
    ValueUseAccs.clear();
    PHIReadAccs.clear();
    PHIIncomingAccs.clear();
  }

  MemoryAccess *getValueDef(const ScopArrayInfo *SAI) const {
    return ValueDefAccs.lookup(SAI);
  }

  ArrayRef<MemoryAccess *> getValueUses(const ScopArrayInfo *SAI) const {
    auto It = ValueUseAccs.find(SAI);
    if (It == ValueUseAccs.end())
      return {};
    return It->second;
  }

  MemoryAccess *getPHIRead(const ScopArrayInfo *SAI) const {
    return PHIReadAccs.lookup(SAI);
  }

  ArrayRef<MemoryAccess *> getPHIIncomings(const ScopArrayInfo *SAI) const {
    auto It = PHIIncomingAccs.find(SAI);
    if (It == PHIIncomingAccs.end())
      return {};
    return It->second;
  }
};

isl::union_map computeReachingDefinition(isl::union_map Schedule,
                                         isl::union_map Writes, bool InclDef,
                                         bool InclRedef) {
  return computeReachingWrite(Schedule, Writes, false, InclDef, InclRedef);
}

isl::union_map computeReachingOverwrite(isl::union_map Schedule,
                                        isl::union_map Writes,
                                        bool InclPrevWrite,
                                        bool InclOverwrite) {
  return computeReachingWrite(Schedule, Writes, true, InclPrevWrite,
                              InclOverwrite);
}

bool isRecursiveValInstMap(const isl::union_map &UMap) {
  SmallPtrSet<Value *, 8> LHSVals;
  SmallPtrSet<Value *, 8> RHSVals;
  foreachElt(UMap, [&](isl::map Map) {
    auto Space = give(isl_map_get_space(Map.keep()));
    auto DomainSpace = give(isl_space_domain(Space.copy()));
    auto DomainMapSpace = give(isl_space_unwrap(DomainSpace.copy()));
    auto LHId =
        give(isl_space_get_tuple_id(DomainMapSpace.keep(), isl_dim_out));
    auto *LVal = static_cast<Value *>(isl_id_get_user(LHId.keep()));
    LHSVals.insert(LVal);

    auto RangeSpace = give(isl_space_range(Space.copy()));
    if (isl_space_is_wrapping(RangeSpace.keep()) == isl_bool_true) {
      auto RangeMapSpace = give(isl_space_unwrap(RangeSpace.copy()));
      auto RHId =
          give(isl_space_get_tuple_id(RangeMapSpace.keep(), isl_dim_out));
      auto *RVal = static_cast<Value *>(isl_id_get_user(RHId.keep()));
      RHSVals.insert(RVal);
    }
  });
  for (auto *LHVal : LHSVals) {
    if (RHSVals.count(LHVal))
      return true;
  }
  return false;
}

/// Compute the next overwrite for a scalar.
///
/// @param Schedule      { DomainWrite[] -> Scatter[] }
///                      Schedule of (at least) all writes. Instances not in @p
///                      Writes are ignored.
/// @param Writes        { DomainWrite[] }
///                      The element instances that write to the scalar.
/// @param InclPrevWrite Whether to extend the timepoints to include
///                      the timepoint where the previous write happens.
/// @param InclOverwrite Whether the reaching overwrite includes the timepoint
///                      of the overwrite itself.
///
/// @return { Scatter[] -> DomainDef[] }
isl::union_map computeScalarReachingOverwrite(isl::union_map Schedule,
                                              isl::union_set Writes,
                                              bool InclPrevWrite,
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
isl::map computeScalarReachingOverwrite(isl::union_map Schedule,
                                        isl::set Writes, bool InclPrevWrite,
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

/// Compute the reaching definition of a scalar.
///
/// Compared to computeReachingDefinition, there is just one element which is
/// accessed and therefore only a set if instances that accesses that element is
/// required.
///
/// @param Schedule  { DomainWrite[] -> Scatter[] }
/// @param Writes    { DomainWrite[] }
/// @param InclDef   Include the timepoint of the definition to the result.
/// @param InclRedef Include the timepoint of the overwrite into the result.
///
/// @return { Scatter[] -> DomainWrite[] }
isl::union_map computeScalarReachingDefinition(isl::union_map Schedule,
                                               isl::union_set Writes,
                                               bool InclDef, bool InclRedef) {

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
isl::map computeScalarReachingDefinition( // { Domain[] -> Zone[] }
    isl::union_map Schedule, isl::set Writes, bool InclDef, bool InclRedef) {
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
isl::multi_aff makeShiftDimAff(isl::space Space, int Pos, int Amount) {
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
isl::map shiftDim(isl::map Map, isl_dim_type Type, int Pos, int Amount) {
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
isl::union_map shiftDim(isl::union_map UMap, isl_dim_type Type, int Pos,
                        int Amount) {
  auto Result = give(isl_union_map_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](isl::map Map) {
    auto Shifted = shiftDim(Map, Type, Pos, Amount);
    Result = give(isl_union_map_add_map(Result.take(), Shifted.take()));
  });
  return Result;
}

/// Input: { Domain[] -> [Range1[] -> Range2[]] }
/// Output: { [Domain[] -> Range1[]] -> [Domain[] -> Range2[]] }
isl::map isl_map_distribute_domain(isl::map Map) {
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

isl::union_map isl_union_map_distribute_domain(isl::union_map UMap) {
  auto Result = give(isl_union_map_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](isl::map Map) {
    auto Distributed = isl_map_distribute_domain(Map);
    Result = give(isl_union_map_add_map(Result.take(), Distributed.copy()));
  });
  return Result;
}

/// Return whether @p Map maps to llvm::Undef.
///
/// @param Map { [] -> ValInst[] }
bool isMapToUndef(const isl::map &Map) {
  if (!isl_map_has_tuple_id(Map.keep(), isl_dim_out))
    return false;

  auto Id = give(isl_map_get_tuple_id(Map.keep(), isl_dim_out));
  auto Val = static_cast<Value *>(isl_id_get_user(Id.keep()));
  return Val && isa<UndefValue>(Val);
}

/// Return whether @p Map maps to an unknown value.
///
/// @param { [] -> ValInst[] }
bool isMapToUnknown(const isl::map &Map) {
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
isl::union_map removeUnknownValInst(const isl::union_map &UMap) {
  auto Result = give(isl_union_map_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](isl::map Map) {
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
isl::union_set getUnknownValInstDomain(const isl::union_map &UMap) {
  auto Result = give(isl_union_set_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](isl::map Map) {
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
isl::union_set getUndefValInstDomain(const isl::union_map &UMap) {
  auto Result = give(isl_union_set_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](isl::map Map) {
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
isl::union_map removeUndefValInst(const isl::union_map &UMap) {
  auto Result = give(isl_union_map_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](isl::map Map) {
    if (!isMapToUndef(Map))
      Result = give(isl_union_map_add_map(Result.take(), Map.take()));
  });
  return Result;
}

isl::union_map applyRangeIfDefined(isl::union_map UMap,
                                   isl::union_map PartialFn) {
  auto Mapped = give(isl_union_map_apply_range(UMap.copy(), PartialFn.copy()));

  auto Defined = give(isl_union_map_domain(PartialFn.take()));
  auto NotMapped =
      give(isl_union_map_subtract_range(UMap.take(), Defined.take()));

  return give(isl_union_map_union(Mapped.take(), NotMapped.take()));
}

/// Return only the mappings that map to known values.
///
/// @param UMap { [] -> ValInst[] }
///
/// @return { [] -> ValInst[] }
isl::union_map filterKnownValInst(const isl::union_map &UMap) {
  auto Result = give(isl_union_map_empty(isl_union_map_get_space(UMap.keep())));
  foreachElt(UMap, [=, &Result](isl::map Map) {
    if (!isMapToUnknown(Map) && !isMapToUndef(Map))
      Result = give(isl_union_map_add_map(Result.take(), Map.take()));
  });
  return Result;
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
isl::union_map expandMapping(isl::union_map Relevant, isl::union_set Universe) {
  Relevant = give(isl_union_map_coalesce(Relevant.take()));
  auto RelevantDomain = give(isl_union_map_domain(Relevant.copy()));
  auto Simplified =
      give(isl_union_map_gist_domain(Relevant.take(), RelevantDomain.take()));
  Simplified = give(isl_union_map_coalesce(Simplified.take()));
  return give(
      isl_union_map_intersect_domain(Simplified.take(), Universe.take()));
}

/// Represent the knowledge of the contents of any array elements in any zone or
/// the knowledge we would add when mapping a scalar to an array element.
///
/// Every array element at every zone unit has one of two states:
///
/// - Unused: Not occupied by any value so a transformation can change it to
///   other values.
///
/// - Occupied: The element contains a value that is still needed.
///
/// The union of Unused and Unknown zones forms the universe, the set of all
/// elements at every timepoint. The universe can easily be derived from the
/// array elements that are accessed someway. Arrays that are never accessed
/// also never play a role in any computation and can hence be ignored. With a
/// given universe, only one of the sets needs to stored implicitly. Computing
/// the complement is also an expensive operation, hence this class has been
/// designed that only one of sets is needed while the other is assumed to be
/// implicit. It can still be given, but is mostly ignored.
///
/// There are two use cases for the Knowledge class:
///
/// 1) To represent the knowledge of the current state of ScopInfo. The unused
///    state means that an element is currently unused: there is no read of it
///    before the next overwrite. Also called 'Existing'.
///
/// 2) To represent the requirements for mapping a scalar to array elements. The
///    unused state means that there is no change/requirement. Also called
///    'Proposed'.
///
/// In addition to these states at unit zones, Knowledge needs to know when
/// values are written. This is because written values may have no lifetime (one
/// reason is that the value is never read). Such writes would therefore never
/// conflict, but overwrite values that might still be required. Another source
/// of problems are multiple writes to the same element at the same timepoint,
/// because their order is undefined.
class Knowledge {
private:
  /// { [Element[] -> Zone[]] -> ValInst[] }
  /// The state of every array element at every unit zone.
  isl::union_map Lifetime;

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
  isl::union_map Written;

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
  Knowledge(isl::union_map Lifetime, bool ImplicitLifetimeIsUnknown,
            isl::union_map Written)
      : Lifetime(std::move(Lifetime)),
        ImplicitLifetimeIsUnknown(ImplicitLifetimeIsUnknown),
        Written(std::move(Written)) {
    canonicalize();
    checkConsistency();
  }

  isl::union_map getWritten() const { return Written; }

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

  void applyIfDefined_inplace(isl::union_map Translator) {
    Lifetime = applyRangeIfDefined(Lifetime, Translator);
    Written = applyRangeIfDefined(Written, Translator);
  }

  /// Combine two knowledges, this and @p That.
  ///
  /// The two knowledges must not conflict each other. Only combining 'implicit
  /// unknown' (use case 1) with 'implicit undef' (use case 2) knowledges is
  /// implemented.
  void learnFrom(Knowledge That) {
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

  /// Determine whether two Knowledges conflict with each other.
  ///
  /// In theory @p Existing and @p Proposed are symmetric, but the
  /// implementation is constrained by the implicit interpretation. That is, @p
  /// Existing must have #Unused defined (use case 1) and @p Proposed must have
  /// #Occupied defined (use case 1).
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
      if (OS) {
        auto Conflicting = give(isl_union_set_subtract(
            ProposedWrittenZone.copy(), ExistingKnownOrUndefDomain.copy()));
        dbgs().indent(Indent)
            << "Conflict of proposed write to current unknown\n";
        dbgs().indent(Indent)
            << "Proposed written: " << Proposed.Written << "\n";
        dbgs().indent(Indent)
            << "Existing known/undef: " << ExistingKnownOrUndefDomain << "\n";
        dbgs().indent(Indent) << "Conflicting: " << Conflicting << "\n";
      }
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

std::string printIntruction(Instruction *Instr, bool IsForDebug = false) {
  std::string Result;
  raw_string_ostream OS(Result);
  Instr->print(OS, IsForDebug);
  OS.flush();
  size_t i = 0;
  while (i < Result.size() && Result[i] == ' ')
    i += 1;
  return Result.substr(i);
}

/// Base class for algorithms based on zones, like DeLICM.
class ZoneAlgorithm {
protected:
  /// Hold a reference to the isl_ctx to avoid it being freed before we released
  /// all of the isl objects.
  ///
  /// This must be declared before any other member that holds an isl object.
  /// This guarantees that the shared_ptr and its isl_ctx is destructed last,
  /// after all other members free'd the isl objects they were holding.
  std::shared_ptr<isl_ctx> IslCtx;

  /// Cached reaching definitions for each ScopStmt.
  ///
  /// Use getScalarReachingDefinition() to get its contents.
  DenseMap<ScopStmt *, isl::map> ScalarReachDefZone;

  /// The analyzed Scop.
  Scop *S;

  LoopInfo *LI;

  /// Parameter space that does not need realignment.
  isl::space ParamSpace;

  /// Space the schedule maps to.
  isl::space ScatterSpace;

  /// Cached version of the schedule and domains.
  isl::union_map Schedule;

  /// Set of all referenced elements.
  /// { Element[] -> Element[] }
  isl::union_set AllElements;

  /// Combined access relations of all MemoryKind::Array READ accesses.
  /// { DomainRead[] -> Element[] }
  isl::union_map AllReads;

  /// Combined access relations of all MemoryKind::Array, MAY_WRITE accesses.
  /// { DomainMayWrite[] -> Element[] }
  isl::union_map AllMayWrites;

  /// Combined access relations of all MemoryKind::Array, MUST_WRITE accesses.
  /// { DomainMustWrite[] -> Element[] }
  isl::union_map AllMustWrites;

  ///  Combined access relations of all MK_Array write accesses (union of
  ///  AllMayWrites and AllMustWrites).
  /// { DomainWrite[] -> Element[] }
  isl::union_map AllWrites;

  /// The value instances written to array elements of all write accesses.
  /// { [Element[] -> DomainWrite[]] -> ValInst[] }
  isl::union_map AllWriteValInst;

  // { [Element[] -> DomainRead[]] -> ValInst[] }
  isl::union_map AllReadValInst;

  /// All reaching definitions for MK_Array writes.
  /// { [Element[] -> Zone[]] -> DomainWrite[] }
  isl::union_map WriteReachDefZone;

  /// Prepare the object before computing the zones of @p S.
  ZoneAlgorithm(Scop *S, LoopInfo *LI)
      : IslCtx(S->getSharedIslCtx()), S(S), LI(LI),
        Schedule(give(S->getSchedule())) {

    auto Domains = give(S->getDomains());

    Schedule =
        give(isl_union_map_intersect_domain(Schedule.take(), Domains.take()));
    ParamSpace = give(isl_union_map_get_space(Schedule.keep()));
    ScatterSpace = getScatterSpace(Schedule);
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
  bool isXtraStmtUse(Value *Val, ScopStmt *UserStmt)
      const { // TODO: Use getInputAccessOf or VirtualUse
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
  /// Scalar reads implicitly always occur before other accesses therefore never
  /// violate the first condition. There is also at most one write to a scalar,
  /// satisfying the second condition.
  bool isCompatibleStmt(ScopStmt *Stmt) {
    auto Stores = makeEmptyUnionMap();
    auto Loads = makeEmptyUnionMap();

    // This assumes that the MemoryKind::Array MemoryAccesses are iterated in
    // order.
    for (auto *MA : *Stmt) {
      if (!MA->isLatestArrayKind())
        continue;

      auto AccRel =
          give(isl_union_map_from_map(getAccessRelationFor(MA).take()));

      if (MA->isRead()) {
        // Reject load after store to same location.
        if (!isl_union_map_is_disjoint(Stores.keep(), AccRel.keep())) {
          OptimizationRemarkMissed R(DEBUG_TYPE, "LoadAfterStore",
                                     MA->getAccessInstruction());
          R << "load after store of same element in same statement";
          R << " (previous stores: " << Stores;
          R << ", loading: " << AccRel << ")";
          S->getFunction().getContext().diagnose(R);
          return false;
        }

        Loads = give(isl_union_map_union(Loads.take(), AccRel.take()));

        continue;
      }

      if (!isa<StoreInst>(MA->getAccessInstruction())) {
        DEBUG(dbgs() << "WRITE that is not a StoreInst not supported\n");
        OptimizationRemarkMissed R(DEBUG_TYPE, "UnusualStore",
                                   MA->getAccessInstruction());
        R << "encountered write that is not a StoreInst: "
          << printIntruction(MA->getAccessInstruction());
        S->getFunction().getContext().diagnose(R);
        return false;
      }

      // In region statements the order is less clear, eg. the load and store
      // might be in a boxed loop.
      if (Stmt->isRegionStmt() &&
          !isl_union_map_is_disjoint(Loads.keep(), AccRel.keep())) {
        OptimizationRemarkMissed R(DEBUG_TYPE, "StoreInSubregion",
                                   MA->getAccessInstruction());
        R << "store is in a non-affine subregion";
        S->getFunction().getContext().diagnose(R);
        return false;
      }

      // Do not allow more than one store to the same location.
      if (!isl_union_map_is_disjoint(Stores.keep(), AccRel.keep())) {
        OptimizationRemarkMissed R(DEBUG_TYPE, "StoreAfterStore",
                                   MA->getAccessInstruction());
        R << "store after store of same element in same statement";
        R << " (previous stores: " << Stores;
        R << ", storing: " << AccRel << ")";
        S->getFunction().getContext().diagnose(R);
        return false;
      }

      Stores = give(isl_union_map_union(Stores.take(), AccRel.take()));
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

    auto *LI = dyn_cast_or_null<LoadInst>(MA->getAccessInstruction());
    if (LI) {
      // { DomainRead[] -> ValInst[] }
      auto LoadValInst =
          makeValInst(LI, Stmt, false, this->LI->getLoopFor(LI->getParent()),
                      Stmt->isBlockStmt());

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

    if (MA->isMustWrite())
      AllMustWrites =
          give(isl_union_map_add_map(AllMustWrites.take(), AccRel.copy()));

    if (MA->isMayWrite())
      AllMayWrites =
          give(isl_union_map_add_map(AllMayWrites.take(), AccRel.copy()));

    // { Domain[] -> ValInst[] }
    auto WriteValInstance =
        makeValInst(MA->getAccessValue(), Stmt, false,
                    LI->getLoopFor(MA->getAccessInstruction()->getParent()),
                    MA->isMustWrite());

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
  isl::union_set makeEmptyUnionSet() const {
    return give(isl_union_set_empty(ParamSpace.copy()));
  }

  isl::union_map makeEmptyUnionMap() const {
    return give(isl_union_map_empty(ParamSpace.copy()));
  }

  /// Check whether @p S can be accurately analyzed by zones.
  bool isCompatibleScop() {
    for (auto &Stmt : *S) {
      if (!isCompatibleStmt(&Stmt))
        return false;
    }
    return true;
  }

  /// Get the schedule for @p Stmt.
  ///
  /// The domain of the result is as narrow as possible.
  isl::map getScatterFor(ScopStmt *Stmt) const {
    auto ResultSpace = give(isl_space_map_from_domain_and_range(
        Stmt->getDomainSpace(), ScatterSpace.copy()));
    return give(isl_union_map_extract_map(Schedule.keep(), ResultSpace.take()));
  }

  /// Get the schedule of @p MA's parent statement.
  isl::map getScatterFor(MemoryAccess *MA) const {
    return getScatterFor(MA->getStatement());
  }

  /// Get the schedule for the statement instances of @p Domain.
  isl::union_map getScatterFor(isl::union_set Domain) const {
    return give(isl_union_map_intersect_domain(Schedule.copy(), Domain.take()));
  }

  /// Get the schedule for the statement instances of @p Domain.
  isl::map getScatterFor(isl::set Domain) const {
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
  isl::set getDomainFor(ScopStmt *Stmt) const {
    return give(Stmt->getDomain());
  }

  /// Get the domain @p MA's parent statement.
  isl::set getDomainFor(MemoryAccess *MA) const {
    return getDomainFor(MA->getStatement());
  }

  /// Get the access relation of @p MA.
  ///
  /// The domain of the result is as narrow as possible.
  isl::map getAccessRelationFor(MemoryAccess *MA) const {
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
  isl::map getScalarReachingDefinition(ScopStmt *Stmt) {
    auto &Result = ScalarReachDefZone[Stmt];
    if (Result)
      return Result;

    auto Domain = getDomainFor(Stmt);
    Result = computeScalarReachingDefinition(Schedule, Domain, false, true);
    simplify(Result);

    return Result;
  }

  /// Get the reaching definition of a scalar defined in @p DefDomain.
  ///
  /// @param DomainDef { DomainDef[] }
  ///              The write statements to get the reaching definition for.
  ///
  /// @return { Scatter[] -> DomainDef[] }
  isl::map getScalarReachingDefinition(isl::set DomainDef) {
    auto DomId = give(isl_set_get_tuple_id(DomainDef.keep()));
    auto *Stmt = static_cast<ScopStmt *>(isl_id_get_user(DomId.keep()));

    auto StmtResult = getScalarReachingDefinition(Stmt);

    return give(isl_map_intersect_range(StmtResult.take(), DomainDef.take()));
  }

  /// Create an isl_id that means 'don't know the value'.
  isl::id makeUnknownId() const { return nullptr; }

  /// Create an isl_space for unknown values.
  isl::space makeUnknownSpace() const {
    return give(isl_space_set_from_params(ParamSpace.copy()));
  }

  /// Create a set with an unknown value in it.
  isl::set makeUnknownSet() const {
    auto Space = makeUnknownSpace();
    return give(isl_set_universe(Space.take()));
  }

  /// Create a union set with an unknown value in it.
  isl::union_set makeUnknownUSet() const {
    return give(isl_union_set_from_set(makeUnknownSet().take()));
  }

  /// Create a domain-to-unknown value mapping.
  ///
  /// @param Domain { Domain[] }
  ///
  /// @return { Domain[] -> ValInst[] }
  isl::map makeUnknownForDomain(isl::set Domain) const {
    return give(isl_map_from_domain(Domain.take()));
  }

  /// Create a statement-to-unknown value mapping.
  ///
  /// @param Stmt The statement whose instances are mapped to unknown.
  ///
  /// @return { Domain[] -> ValInst[] }
  isl::map makeUnknownForDomain(ScopStmt *Stmt) const {
    return give(isl_map_from_domain(getDomainFor(Stmt).take()));
  }

  /// Create a domain-to-unknown value mapping.
  ///
  /// @param Domain { Domain[] }
  ///
  /// @return { Domain[] -> ValInst[] }
  isl::union_map makeUnknownForDomain(isl::union_set Domain) const {
    return give(isl_union_map_from_domain(Domain.take()));
  }

  /// Create an isl_id that represents 'unused storage'.
  isl::id makeUndefId() const {
    auto &LLVMContext = S->getFunction().getContext();
    auto Ty = IntegerType::get(LLVMContext, 1);
    auto Val = UndefValue::get(Ty);
    return give(isl_id_alloc(IslCtx.get(), "Undef", Val));
  }

  /// Create an isl_space for an undefined value.
  isl::space makeUndefSpace() const {
    auto Result = give(isl_space_set_from_params(ParamSpace.copy()));
    return give(isl_space_set_tuple_id(Result.take(), isl_dim_set,
                                       makeUndefId().take()));
  }

  /// Create a set with an undefined value in it.
  isl::set makeUndefSet() const {
    auto Space = makeUndefSpace();
    return give(isl_set_universe(Space.take()));
  }

  /// Create a union set with an undefined value in it.
  isl::union_set makeUndefUSet() const {
    return give(isl_union_set_from_set(makeUndefSet().take()));
  }

  /// Create an isl_id that represents @p V.
  isl::id makeValueId(Value *V) const {
    if (!V)
      return makeUnknownId();
    if (isa<UndefValue>(V))
      return makeUndefId();

    auto Name = getIslCompatibleName("Val_", V, std::string());
    return give(isl_id_alloc(IslCtx.get(), Name.c_str(), V));
  }

  /// Create the space for an llvm::Value that is available everywhere.
  isl::space makeValueSpace(Value *V) const {
    auto Result = give(isl_space_set_from_params(ParamSpace.copy()));
    return give(isl_space_set_tuple_id(Result.take(), isl_dim_set,
                                       makeValueId(V).take()));
  }

  /// Create a set with the llvm::Value @p V which is available everywhere.
  isl::set makeValueSet(Value *V) const {
    auto Space = makeValueSpace(V);
    return give(isl_set_universe(Space.take()));
  }

  // { UserDomain[] -> ValInst[] }
  isl::map makeValInst(Value *Val, ScopStmt *UserStmt, bool IsEntryPHIUser,
                       Loop *Scope, bool IsCertain = true) {
    return makeValInst(Val, nullptr, UserStmt, getDomainFor(UserStmt),
                       IsEntryPHIUser, Scope, IsCertain);
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
  isl::map makeValInst(Value *V, isl::set DomainDef, ScopStmt *UseStmt,
                       isl::set DomainUse, bool IsEntryPHIUser, Loop *Scope,
                       bool IsCertain = true) {
    assert(DomainUse && "Must pass a user domain");

    // If the definition/write is conditional, the previous write may "shine
    // through" on conditions we cannot determine. Again, return the unknown
    // value.
    if (!IsCertain)
      return makeUnknownForDomain(DomainUse);

    auto *OrigV = V;
    // FIXME: It doesn't really work well if the LCSSA %phi is intra-stmt, but
    // the incoming value is extra-phi.
    // V = deLCSSA(V);

    auto VUse = VirtualUse::create(UseStmt, IsEntryPHIUser, Scope, V);
    switch (VUse.getType()) {
    case VirtualUse::Constant:
    case VirtualUse::ReadOnly:
    case VirtualUse::Synthesizable: {
      auto ValSet = makeValueSet(V);
      return give(
          isl_map_from_domain_and_range(DomainUse.take(), ValSet.take()));
    }

    case VirtualUse::IntraValue: { // TODO: This might also just mean that the
                                   // value has been rematerialized in UseStmt.
                                   // In this case we don't get a canonical
                                   // ValInst. This might be OK or just wrong,
                                   // depending on how the result is used.
                                   // Should probably provide an option to
                                   // choose whether this is OK.
      // { llvm::Value }
      auto ValSet = makeValueSet(V);

      // {  UserDomain[] -> llvm::Value }
      auto ValInstSet =
          give(isl_map_from_domain_and_range(DomainUse.take(), ValSet.take()));

      // { UserDomain[] -> [UserDomain[] - >llvm::Value] }
      auto Result =
          give(isl_map_reverse(isl_map_domain_map(ValInstSet.take())));
      simplify(Result);
      return Result;
    }

    case VirtualUse::InterValue:
      break;
    }

#if 0
    if (V && !isa<Instruction>(V)) {
      // Non-instructions are available anywhere.
      auto ValSet = makeValueSet(V);
      return give(isl_map_from_domain_and_range(DomainUse.take(), ValSet.take()));
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
#endif

    // Try to derive DomainDef if not explicitly specified.
    if (!DomainDef) {
      auto *Inst = cast<Instruction>(V);
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
      auto ValSet = makeValueSet(V);

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
  void computeCommon() {
    AllReads = makeEmptyUnionMap();
    AllMayWrites = makeEmptyUnionMap();
    AllMustWrites = makeEmptyUnionMap();
    AllWriteValInst = makeEmptyUnionMap();
    AllReadValInst = makeEmptyUnionMap();
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
    AllElements = makeEmptyUnionSet();
    foreachElt(AllWrites, [this](isl::map Write) {
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
  isl::map Target;

  /// Lifetime expressed from the MK_Value write or MK_PHI read.
  /// { Domain[] -> Zone[] }
  isl::map Lifetime;

  /// The constants that were checked before the transformation/applied to the
  /// common knowledge after the transformation.
  Knowledge Proposed;

public:
  MapReport(const ScopArrayInfo *SAI, MemoryAccess *PrimaryAcc,
            ArrayRef<MemoryAccess *> SecondaryAccs, isl::map Target,
            isl::map Lifetime, Knowledge Zone)
      : SAI(SAI), PrimaryAcc(PrimaryAcc),
        SecondaryAccs(SecondaryAccs.begin(), SecondaryAccs.end()),
        Target(std::move(Target)), Lifetime(std::move(Lifetime)),
        Proposed(std::move(Zone)) {
    assert(SAI);
    DEBUG(print(llvm::dbgs(), 0));
  }

  /// Print this transformation report to @p OS.
  void print(llvm::raw_ostream &OS, int Indent = 0) const {
    OS.indent(Indent) << "Mapping of " << SAI->getName() << " {\n";
    if (PrimaryAcc) {
      OS.indent(Indent + 4) << "Primary:\n";
      PrimaryAcc->print(OS);
    }
    for (auto *MA : SecondaryAccs) {
      OS.indent(Indent + 4) << "Secondary:\n";
      MA->print(OS);
    }
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

  /// Number of StoreInsts something can be mapped to.
  int NumberOfCompatibleTargets = 0;

  /// The number of StoreInsts to which at least one value or PHI has been
  /// mapped to.
  int NumberOfTargetsMapped = 0;

  /// The number of llvm::Value mapped to some array element.
  int NumberOfMappedValueScalars = 0;

  /// The number of PHIs mapped to some array element.
  int NumberOfMappedPHIScalars = 0;

  /// Determine whether two knowledges are conflicting with each other.
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
      // does not have the information to where it is mapped to. Only the
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

  /// Compute the uses of a MemoryKind::Value and its lifetime (from its
  /// definition to the last use).
  ///
  /// @param SAI The ScopArrayInfo representing the value's storage.
  ///
  /// @return { DomainDef[] -> DomainUse[] }, { DomainDef[] -> Zone[] }
  ///         First element is the set of uses for each definition.
  ///         The second is the lifetime of each definition.
  std::tuple<isl::union_map, isl::map>
  computeValueUses(const ScopArrayInfo *SAI) {
    assert(SAI->isValueKind());

    // { DomainRead[] }
    auto Reads = makeEmptyUnionSet();

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
  isl::union_map computePerPHI(const ScopArrayInfo *SAI) {
    assert(SAI->isPHIKind());

    // { DomainPHIWrite[] -> Scatter[] }
    auto PHIWriteScatter = makeEmptyUnionMap();

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

  /// Try to map a MemoryKind::Value to a given array element.
  ///
  /// @param SAI       Representation of the scalar's memory to map.
  /// @param TargetElt { Scatter[] -> Element[] }
  ///                  Suggestion where to map a scalar to when at a timepoint.
  ///
  /// @return true if the scalar was successfully mapped.
  bool tryMapValue(const ScopArrayInfo *SAI, isl::map TargetElt) {
    assert(SAI->isValueKind());

    auto *DefMA = DefUse.getValueDef(SAI);
    assert(DefMA->isValueKind());
    assert(DefMA->isMustWrite());
    auto *V = DefMA->getAccessValue();
    auto *DefInst = DefMA->getAccessInstruction();

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
    isl::map Lifetime;

    // { DomainDef[] -> DomainUse[] }
    isl::union_map DefUses;

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
    auto ValInst = translateComputedPHI(
        makeValInst(V, DefMA->getStatement(), false,
                    LI->getLoopFor(DefInst->getParent()), true));

    // { [Element[] -> Zone[]] -> ValInst[] }
    auto EltLifetime = give(isl_union_map_apply_domain(
        ValInst.copy(), isl_union_map_from_map(EltLifetimeTranslator.take())));

    // { [Element[] -> Scatter[]] -> ValInst[] }
    auto EltWriteAction = give(isl_union_map_apply_domain(
        ValInst.copy(), isl_union_map_from_map(WrittenTranslator.take())));

    Knowledge Proposed(std::move(EltLifetime), false,
                       std::move(EltWriteAction));
    if (isConflicting(Proposed))
      return false;

    // { DomainUse[] -> Element[] }
    auto UseTarget = give(
        isl_union_map_apply_range(isl_union_map_reverse(DefUses.take()),
                                  isl_union_map_from_map(DefTarget.copy())));

    bool isValid =
        mapValue(SAI, DefTarget, UseTarget, Lifetime, Proposed, false);
    if (!isValid) {
      MapUndefinedReject++;
      return false;
    }

    isValid = mapValue(SAI, std::move(DefTarget), std::move(UseTarget),
                       std::move(Lifetime), std::move(Proposed), true);
    assert(isValid);

    return true;
  }

  /// After a scalar has been mapped, update the global knowledge.
  void applyLifetime(Knowledge Proposed) {
    Zone.learnFrom(std::move(Proposed));
  }

  /// Map a MemoryKind::Value scalar to an array element.
  ///
  /// Callers must have ensured that the mapping is valid and not conflicting.
  ///
  /// @param SAI       The ScopArrayInfo representing the scalar's memory to
  ///                  map.
  /// @param DefTarget { DomainDef[] -> Element[] }
  ///                  The array element to map the scalar to.
  /// @param UseTarget { DomainUse[] -> Element[] }
  ///                  The array elements the uses are mapped to.
  /// @param Lifetime  { DomainDef[] -> Zone[] }
  ///                  The lifetime of each llvm::Value definition for
  ///                  reporting.
  /// @param Proposed  Mapping constraints for reporting.
  /// @param DoIt      True if action should be executed; false to only check
  /// whether it can be done.
  ///
  /// @return          True if the transformation is valid.
  bool mapValue(const ScopArrayInfo *SAI, isl::map DefTarget,
                isl::union_map UseTarget, isl::map Lifetime, Knowledge Proposed,
                bool DoIt) {

    // { Element[] }
    auto EltSpace = give(isl_space_range(isl_map_get_space(DefTarget.keep())));

    bool RequiresUndefined = false;

    // Redirect the use accesses.
    SmallVector<MemoryAccess *, 4> SecondaryAccs;
    for (auto *MA : DefUse.getValueUses(SAI)) {
      // { DomainUse[] }
      auto Domain = getDomainFor(MA);
      auto DomainSpace = give(isl_set_get_space(Domain.keep()));
      auto NewAccRelSpace = give(isl_space_map_from_domain_and_range(
          DomainSpace.copy(), EltSpace.copy()));

      // { DomainUse[] -> Element[] }
      auto NewAccRel = give(isl_union_map_intersect_domain(
          UseTarget.copy(), isl_union_set_from_set(Domain.copy())));
      auto NewAccRelMap = singleton(NewAccRel, NewAccRelSpace);

      simplify(NewAccRelMap);

      auto DefinedDomain = give(isl_map_domain(NewAccRelMap.copy()));
      if (isl_set_is_subset(Domain.keep(), DefinedDomain.keep()) !=
          isl_bool_true)
        return false;

      if (!DoIt)
        continue;

      MA->setNewAccessRelation(NewAccRelMap.copy());
      SecondaryAccs.push_back(MA);
    }

    if (!DoIt)
      return true;

    if (RequiresUndefined)
      MapRequiredUndefined++;

    auto *WA = DefUse.getValueDef(SAI);
    WA->setNewAccessRelation(DefTarget.copy());
    applyLifetime(Proposed);

    MappedValueScalars++;
    NumberOfMappedValueScalars += 1;
    MapReports.emplace_back(SAI, WA, SecondaryAccs, DefTarget, Lifetime,
                            std::move(Proposed));
    return true;
  }

  /// Express the incoming values of a PHI for each incoming statement in an
  /// isl_union_map.
  ///
  /// @param SAI The PHI scalar represented by a ScopArrayInfo.
  ///
  /// @return { PHIWriteDomain[] -> ValInst[] }
  isl::union_map determinePHIWrittenValues(const ScopArrayInfo *SAI) {
    auto Result = makeEmptyUnionMap();

    // Collect the incoming values.
    for (auto *MA : DefUse.getPHIIncomings(SAI)) {
      // { DomainWrite[] -> ValInst[] }
      isl::union_map ValInst;
      auto *WriteStmt = MA->getStatement();

      auto Incoming = MA->getIncoming();
      assert(!Incoming.empty());
      if (Incoming.size() == 1) {
        ValInst = translateComputedPHI(
            makeValInst(Incoming[0].second, WriteStmt, false,
                        LI->getLoopFor(Incoming[0].first), true));
      } else {
        // If the PHI is in a subregion's exit node it can have multiple
        // incoming values (+ maybe another incoming edge from an unrelated
        // block). Since we cannot directly represent it as a single
        // llvm::Value from multiple exiting block, it is represented using
        // the PHI itself.
        // We currently model it as unknown value, but modeling as the PHIInst
        // itself could be OK, too.
        ValInst = give(
            isl_union_map_from_map(makeUnknownForDomain(WriteStmt).take()));
      }

      Result = give(isl_union_map_union(Result.take(), ValInst.take()));
    }

    assert(isl_union_map_is_single_valued(Result.keep()) == isl_bool_true &&
           "Cannot have multiple incoming values for same incoming statement");
    return Result;
  }

  /// Try to map a MemoryKind::PHI scalar to a given array element.
  ///
  /// @param SAI       Representation of the scalar's memory to map.
  /// @param TargetElt { Scatter[] -> Element[] }
  ///                  Suggestion where to map the scalar to when at a
  ///                  timepoint.
  ///
  /// @return true if the PHI scalar has been mapped.
  bool tryMapPHI(const ScopArrayInfo *SAI, isl::map TargetElt) {
    if (!DelicmMapPHI)
      return false;

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
    auto WritesTarget = give(isl_union_map_reverse(isl_union_map_apply_domain(
        PerPHIWrites.copy(), isl_union_map_from_map(PHITarget.copy()))));
    simplify(WritesTarget);

    // { DomainWrite[] }
    auto UniverseWritesDom = give(isl_union_set_empty(ParamSpace.copy()));

    for (auto *MA : DefUse.getPHIIncomings(SAI))
      UniverseWritesDom = give(isl_union_set_add_set(UniverseWritesDom.take(),
                                                     getDomainFor(MA).take()));

    auto RelevantWritesTarget = WritesTarget;
    if (DelicmOverapproximateWrites)
      WritesTarget = expandMapping(WritesTarget, UniverseWritesDom);

    auto ExpandedWritesDom = give(isl_union_map_domain(WritesTarget.copy()));
    if (!DelicmPartialWrites &&
        !isl_union_set_is_subset(UniverseWritesDom.keep(),
                                 ExpandedWritesDom.keep())) {
      DEBUG(dbgs() << "    Reject because did not find PHI write mapping for "
                      "all instances\n");
      if (DelicmOverapproximateWrites)
        DEBUG(dbgs() << "      Relevant Mapping:    " << RelevantWritesTarget
                     << '\n');
      DEBUG(dbgs() << "      Deduced Mapping:     " << WritesTarget << '\n');
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
    auto WrittenTranslator =
        give(isl_union_map_range_product(WritesTarget.copy(), Schedule.copy()));

    // { DomainWrite[] -> [Element[], Zone[]] }
    auto LifetimeTranslator = give(
        isl_union_map_range_product(WritesTarget.copy(), WriteLifetime.take()));

    // { [Element[] -> Zone[]] -> ValInst[] }
    auto EltLifetimeInst = give(isl_union_map_apply_domain(
        WrittenValue.copy(), LifetimeTranslator.take()));

    // { [Element[] -> Scatter[]] -> ValInst[] }
    auto EltWritten = give(isl_union_map_apply_domain(
        WrittenValue.copy(), WrittenTranslator.take()));

    Knowledge Proposed(EltLifetimeInst, false, EltWritten);
    if (isConflicting(Proposed))
      return false;

    mapPHI(SAI, std::move(PHITarget), std::move(WritesTarget),
           std::move(Lifetime), std::move(Proposed), std::move(WrittenValue));
    return true;
  }

  bool tryComputePHI(const ScopArrayInfo *SAI) {
    if (!DelicmComputePHI)
      return false;

    auto *PHIRead = DefUse.getPHIRead(SAI);
    assert(PHIRead->isPHIKind());
    assert(PHIRead->isRead());
    auto *PHI = cast<PHINode>(PHIRead->getAccessInstruction());
    auto *ReadStmt = PHIRead->getStatement();
    // Do no support non-affine subregion's exit phis
    for (auto PHIWrite : DefUse.getPHIIncomings(SAI)) {
      if (PHIWrite->getIncoming().size() != 1)
        return false;
    }

    // { DomainPHIRead[] -> DomainPHIWrite[] }
    auto IncomingWrites = computePerPHI(SAI);

    // { PHIValInst[] -> ValInst[] }
    auto ComputedPHITranslator = makeEmptyUnionMap();

    // { DomainPHIRead[] -> Value[] }
    auto IncomingValues = makeEmptyUnionMap();
    foreachElt(IncomingWrites, [&, this](isl::map Map) {
      auto Space = give(isl_map_get_space(Map.keep()));
      auto RangeSpace = give(isl_space_range(Space.copy()));
      auto RangeId = give(isl_space_get_tuple_id(Space.keep(), isl_dim_out));
      auto *IncomingStmt =
          static_cast<ScopStmt *>(isl_id_get_user(RangeId.keep()));
      auto *IncomingVal =
          PHI->getIncomingValueForBlock(IncomingStmt->getBasicBlock());
      assert(IncomingVal &&
             "TODO: exit block if predecessor is non-affine subregion");

      // { DomainPHIRead[] }
      auto PHIDomain = give(isl_map_domain(Map.copy()));

      // { PHIValue[] }
      auto PHISet = makeValueSet(PHI);

      // { DomainPHIRead[] -> PHIValue[] } == { PHIValueInst[] }
      auto PHIMap =
          give(isl_map_from_domain_and_range(PHIDomain.copy(), PHISet.copy()));

      // { DomainPHIRead[] -> PHIValueInst[] }
      auto ReadToPHIInst =
          give(isl_map_reverse(isl_map_domain_map(PHIMap.copy())));

      // { DomainPHIWrite[] }
      auto IncomingDomain = give(isl_map_range(Map.copy()));

      // { IncomingValue[] }
      auto ValSet = makeValueSet(IncomingVal);

      // { DomainPHIRead[] -> IncomingValue[] }
      auto SelectVal =
          give(isl_map_from_domain_and_range(PHIDomain.copy(), ValSet.copy()));
      IncomingValues =
          give(isl_union_map_add_map(IncomingValues.take(), SelectVal.copy()));

      // { PHIWriteDomain[] -> IncomingValInst[] }
      auto IncomingValInst = makeValInst(IncomingVal, IncomingStmt, false,
                                         IncomingStmt->getSurroundingLoop());

      // { PHIWriteRead[] -> IncomingValInst[] }
      auto PHIWriteInst =
          give(isl_map_apply_range(Map.copy(), IncomingValInst.copy()));

      // { PHIValueInst[] -> IncomingValueInst[] }
      auto Translator =
          give(isl_map_apply_domain(PHIWriteInst.copy(), ReadToPHIInst.copy()));
      ComputedPHITranslator = give(isl_union_map_add_map(
          ComputedPHITranslator.take(), Translator.copy()));

      // { IncomingValInst[] }
      auto ValInstSpace =
          give(isl_space_range(isl_map_get_space(IncomingValInst.keep())));

      ScopStmt *DefStmt = nullptr;
      if (isl_space_is_wrapping(ValInstSpace.keep())) {
        auto Unwrapped = give(isl_space_unwrap(ValInstSpace.copy()));
        // ValSpace = give(isl_space_range(Unwrapped.copy()));
        // auto DefStmtSpace = give(isl_space_domain(Unwrapped.copy()));
        auto DefStmtId =
            give(isl_space_get_tuple_id(Unwrapped.keep(), isl_dim_in));
        DefStmt = static_cast<ScopStmt *>(isl_id_get_user(DefStmtId.keep()));
        assert(DefStmt);

        auto ValId =
            give(isl_space_get_tuple_id(Unwrapped.keep(), isl_dim_out));
        assert(IncomingVal ==
               static_cast<Value *>(isl_id_get_user(ValId.keep())));
      }

      // IncomingVal might be available in multiple Stmts: The Stmt it is
      // originally defined in and those it is has been rematerialized (e.g. by
      // polly-known pass). makeValInst will prefer the rematerialized one so
      // inter-stmt dependencies are avoided. Indeed, the original defining
      // might not even exist anymore and been removed (by polly-simplify pass).
      // If that happens we have no other choice than to use the scop where it
      // has been rematerialized. There might be multiple such stmts and we risk
      // that the rematerialization is only done after use in this statement
      // (FIXME: Have to think about whether this is even possible)
      ScopStmt *DefStmt2 = S->getStmtFor(IncomingVal);
      if (DefStmt2) {
        assert(DefStmt && "Contradicting information on whether the value is "
                          "defined within the SCoP");
        DefStmt = DefStmt2;
      }

      // TODO: Refactor with ScopBuilder
      bool NeedAccess;
      if (canSynthesize(IncomingVal, *S, S->getSE(),
                        ReadStmt->getSurroundingLoop()))
        NeedAccess = false;
      else if (DefStmt) {
        NeedAccess = true;
      } else {
        NeedAccess = !isa<Constant>(IncomingVal) && ModelReadOnlyScalars;
      }

      // Ensure read of value in the BB we add a use to.
      if (NeedAccess && !ReadStmt->lookupValueReadOf(IncomingVal)) {
        auto *ValSAI = S->getOrCreateScopArrayInfo(
            IncomingVal, IncomingVal->getType(), {}, MemoryKind::Value);

        // ScopStmt *DefStmt2 =  S->getStmtFor( IncomingVal );
        // assert(DefStmt == S->getStmtFor(IncomingVal));
        // if (!DefStmt)
        // DefStmt = IncomingStmt;

        // Ensure write of value if it does not exist yet.
        if (!DefUse.getValueDef(ValSAI) && DefStmt) {
          auto *WA = new MemoryAccess(
              IncomingStmt, cast<Instruction>(IncomingVal),
              MemoryAccess::MUST_WRITE, IncomingVal, IncomingVal->getType(),
              true, {}, {}, IncomingVal, MemoryKind::Value,
              getIslCompatibleName("MemRef_", IncomingVal, ""));
          WA->buildAccessRelation(ValSAI);
          IncomingStmt->addAccess(WA);
          S->addAccessFunction(WA);
          assert(DefUse.ValueDefAccs.find(SAI) == DefUse.ValueDefAccs.end());
          DefUse.ValueDefAccs[ValSAI] = WA;
          assert(DefUse.getValueDef(ValSAI)->getStatement() == DefStmt);
        }

        auto *RA =
            new MemoryAccess(ReadStmt, PHI, MemoryAccess::READ, IncomingVal,
                             IncomingVal->getType(), true, {}, {}, IncomingVal,
                             MemoryKind::Value,
                             getIslCompatibleName("MemRef_", IncomingVal, ""));
        RA->buildAccessRelation(ValSAI);
        ReadStmt->addAccess(RA);
        S->addAccessFunction(RA);
        DefUse.ValueUseAccs[ValSAI].push_back(RA);
      }

    });

#if 0
    // Remove accesses entirely so codegen will generate on demand.
    for (auto PHIWrite : DefUse.getPHIIncomings(SAI)) {
      auto *WriteStmt = PHIWrite->getStatement();
      auto *Val = PHIWrite->getIncoming().front().second;

      auto *Inst = dyn_cast<Instruction>(Val);
      if (Inst) {
        auto InstStmt = S->getStmtFor(Inst);
        if (!InstStmt)
          InstStmt = WriteStmt;

		 auto *ValSAI = S->getOrCreateScopArrayInfo(Val, Val->getType(), {},MemoryKind::Value);
		auto *WA = DefUse.getValueDef(ValSAI);
		      if (WA)
          InstStmt = WA->getStatement();

			  auto InScop = S->contains(Inst);
        if (InScop && !InstStmt->lookupValueWriteOf(Inst)) {
          WA = new MemoryAccess(InstStmt, Inst, MemoryAccess::MUST_WRITE, Val,
                                Val->getType(), true, {}, {}, Val,
                                MemoryKind::Value,
                                getIslCompatibleName("MemRef_", Val, ""));
          WA->buildAccessRelation(ValSAI);
          InstStmt->addAccess(WA);
          S->addAccessFunction(WA);
          assert(DefUse.ValueDefAccs.find(SAI) == DefUse.ValueDefAccs.end());
          DefUse.ValueDefAccs[ValSAI] = WA;
        }

        if (!ReadStmt->lookupValueReadOf(Val)) {
          auto *RA = new MemoryAccess(ReadStmt, PHI, MemoryAccess::READ, Val,
                                      Val->getType(), true, {}, {}, Val,
                                      MemoryKind::Value,
                                      getIslCompatibleName("MemRef_", Val, ""));
          RA->buildAccessRelation(ValSAI);
          ReadStmt->addAccess(RA);
          S->addAccessFunction(RA);
          DefUse.ValueUseAccs[ValSAI].push_back(RA);
        }
      }

    }
#endif
    // Remove ExitPHI accesses
    for (auto PHIWrite : DefUse.getPHIIncomings(SAI)) {
      auto *WriteStmt = PHIWrite->getStatement();
      WriteStmt->removeSingleMemoryAccess(PHIWrite);
    }

    ReadStmt->removeSingleMemoryAccess(PHIRead);
    ReadStmt->ComputedPHIs[PHI] = IncomingValues;
    ComputedPHIScalars++;
    applyComputedPHI(ComputedPHITranslator);
    return true;
  }

  isl::union_map ComputedPHIs = makeEmptyUnionMap();
  isl::union_map translateComputedPHI(isl::union_map UMap) {
    // auto Untranslatable = give(isl_union_map_subtract_range(
    //   UMap.copy(), isl_union_map_domain(ComputedPHIs.copy())));

    // auto Translated =
    //    give(isl_union_map_apply_range(UMap.copy(), ComputedPHIs.copy()));

    auto Result = applyRangeIfDefined(UMap, ComputedPHIs);
    //    give(isl_union_map_union(Translated.copy(), Untranslatable.copy()));
    simplify(Result);
    return Result;
  }
  isl::union_map translateComputedPHI(isl::map Map) {
    return translateComputedPHI(give(isl_union_map_from_map(Map.take())));
  }

  bool applyComputedPHI(isl::union_map ValInstTranslator) {
    auto Fn = applyRangeIfDefined(ValInstTranslator, ComputedPHIs);
    auto NewComputedPHIs = give(isl_union_map_union(
        Fn.copy(), applyRangeIfDefined(ComputedPHIs, Fn).take()));
    if (isRecursiveValInstMap(NewComputedPHIs))
      return false;

    Zone.applyIfDefined_inplace(Fn);
    ComputedPHIs = std::move(NewComputedPHIs);
    return true;
  }

  // { [Element[] -> Scatter[]] -> ValInst[] }
  bool isWriteNecessary(isl::union_map ValInst) {
    return ValInst.is_subset(Zone.getWritten()).is_false_or_error();
  }

  MemoryAccess *findExistingWrite(ScopStmt *Stmt) {}

  /// Map a MemoryKind::PHI scalar to an array element.
  ///
  /// Callers must have ensured that the mapping is valid and not conflicting
  /// with the common knowledge.
  ///
  /// @param SAI         The ScopArrayInfo representing the scalar's memory to
  ///                    map.
  /// @param ReadTarget  { DomainRead[] -> Element[] }
  ///                    The array element to map the scalar to.
  /// @param WriteTarget { DomainWrite[] -> Element[] }
  ///                    New access target for each PHI incoming write.
  /// @param Lifetime    { DomainRead[] -> Zone[] }
  ///                    The lifetime of each PHI for reporting.
  /// @param Proposed    Mapping constraints for reporting.
  /// @param WrittenValue { DomainWrite[] -> ValInst[] }
  void mapPHI(const ScopArrayInfo *SAI, isl::map ReadTarget,
              isl::union_map WriteTarget, isl::map Lifetime, Knowledge Proposed,
              isl::union_map WrittenValue) {

    auto ElementSpace =
        give(isl_space_range(isl_map_get_space(ReadTarget.keep())));

    // Redirect the PHI incoming writes.
    SmallVector<MemoryAccess *, 4> SecondaryAccs;
    for (auto *MA : DefUse.getPHIIncomings(SAI)) {
      // { DomainWrite[] }
      auto Domain = getDomainFor(MA);
      auto DomainSpace = give(isl_set_get_space(Domain.keep()));

      // { DomainWrite[] -> Scatter[] }
      auto Schedule = getScatterFor(Domain);

#if 0
	  // { DomainWrite[] -> Element[] }
	  auto MAWriteTarget =   WriteTarget.intersect_domain(Domain);
	  
	  // { DomainWrite[] -> [Element[] -> Scatter[]] }
	  auto DomToEltScatter = isl::manage( isl_union_map_range_product( MAWriteTarget.copy(), isl::union_map(  Schedule).take() ));

	  // { DomainWrite[] -> ValInst[] }
	  auto MAWrittenValue =   WrittenValue.intersect_domain(Domain);
	  
	  // { [Element[] -> Scatter[]] -> ValInst[] } 
	  auto MAWritten = MAWrittenValue.apply_domain(DomToEltScatter);


	  if (!isWriteNecessary( MAWritten )) {
		  MA->getStatement()->removeSingleMemoryAccess(MA);
		  continue;
	  }
#endif

      // { DomainWrite[] -> Element[] }
      auto NewAccRel = give(isl_union_map_intersect_domain(
          WriteTarget.copy(), isl_union_set_from_set(Domain.take())));
      simplify(NewAccRel);

      // assert(isl_union_map_n_map(NewAccRel.keep()) == 1);
      auto ExpectedSpace = give(isl_space_map_from_domain_and_range(
          DomainSpace.copy(), ElementSpace.copy()));

      MA->setNewAccessRelation(singleton(NewAccRel, ExpectedSpace).take());
      SecondaryAccs.push_back(MA);
    }

    // Redirect the PHI read.
    auto *PHIRead = DefUse.getPHIRead(SAI);
    PHIRead->setNewAccessRelation(ReadTarget.copy());
    applyLifetime(Proposed);

    MappedPHIScalars++;
    NumberOfMappedPHIScalars++;
    MapReports.emplace_back(SAI, PHIRead, SecondaryAccs, std::move(ReadTarget),
                            std::move(Lifetime), std::move(Proposed));
  }

  /// Search and map scalars to memory overwritten by @p TargetStoreMA.
  ///
  /// Start trying to map scalars that are used in the same statement as the
  /// store. For every successful mapping, try to also map scalars of the
  /// statements where those are written. Repeat, until no more mapping
  /// opportunity is found.
  ///
  /// There is currently no preference in which order scalars are tried.
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

    // Stack of elements not yet processed.
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

    ProcessAllIncoming(TargetStmt);

    auto AnyMapped = false;
    auto &DL = S->getRegion().getEntry()->getModule()->getDataLayout();
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

      // Try to map MemoryKind::Value scalars.
      if (SAI->isValueKind()) {
        if (!tryMapValue(SAI, EltTarget))
          continue;

        auto *DefAcc = DefUse.getValueDef(SAI);
        ProcessAllIncoming(DefAcc->getStatement());

        AnyMapped = true;
        continue;
      }

      // Try to map MemoryKind::PHI scalars.
      if (SAI->isPHIKind()) {
        if (tryMapPHI(SAI, EltTarget)) {
          // Add inputs of all incoming statements to the worklist.
          for (auto *PHIWrite : DefUse.getPHIIncomings(SAI))
            ProcessAllIncoming(PHIWrite->getStatement());

          AnyMapped = true;
        } else if (tryComputePHI(SAI)) {
          auto *PHIAcc = DefUse.getPHIRead(SAI);
          ProcessAllIncoming(PHIAcc->getStatement());
        }
      }
    }

    if (AnyMapped) {
      TargetsMapped++;
      NumberOfTargetsMapped++;
    }
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
  isl::union_map computeLifetime() const {
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
  isl::union_map computeWritten() const {
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

  /// Determine whether an access touches at most one element.
  ///
  /// The accessed element could be a scalar or accessing an array with constant
  /// subscript, such that all instances access only that element.
  ///
  /// @param MA The access to test.
  ///
  /// @return True, if zero or one elements are accessed; False if at least two
  ///         different elements are accessed.
  bool isScalarAccess(MemoryAccess *MA) {
    auto Map = getAccessRelationFor(MA);
    auto Set = give(isl_map_range(Map.take()));
    return isl_set_is_singleton(Set.keep()) == isl_bool_true;
  }

  /// Print mapping statistics to @p OS.
  void printStatistics(llvm::raw_ostream &OS, int Indent = 0) const {
    OS.indent(Indent) << "Statistics {\n";
    OS.indent(Indent + 4) << "Compatible overwrites: "
                          << NumberOfCompatibleTargets << "\n";
    OS.indent(Indent + 4) << "Overwrites mapped to:  " << NumberOfTargetsMapped
                          << '\n';
    OS.indent(Indent + 4) << "Value scalars mapped:  "
                          << NumberOfMappedValueScalars << '\n';
    OS.indent(Indent + 4) << "PHI scalars mapped:    "
                          << NumberOfMappedPHIScalars << '\n';
    OS.indent(Indent) << "}\n";
  }

  /// Return whether at least one transformation been applied.
  bool isModified() const { return NumberOfTargetsMapped > 0; }

public:
  DeLICMImpl(Scop *S, LoopInfo *LI) : ZoneAlgorithm(S, LI) {}

  /// Calculate the lifetime (definition to last use) of every array element.
  ///
  /// @return True if the computed lifetimes (#Zone) is usable.
  bool computeZone() {
    // Check that nothing strange occurs.
    if (!isCompatibleScop()) {
      DeLICMIncompatible++;
      return false;
    }

    DefUse.compute(S);
    isl::union_map EltLifetime, EltWritten;

    {
      IslMaxOperationsGuard MaxOpGuard(IslCtx.get(), DelicmMaxOps);

      computeCommon();

      EltLifetime = computeLifetime();
      EltWritten = computeWritten();
    }
    DeLICMAnalyzed++;

    if (!EltLifetime || !EltWritten) {
      assert(isl_ctx_last_error(IslCtx.get()) == isl_error_quota &&
             "The only reason that these things have not been computed should "
             "be if the max-operations limit hit");
      DeLICMOutOfQuota++;
      DEBUG(dbgs() << "DeLICM analysis exceeded max_operations\n");
      DebugLoc Begin, End;
      getDebugLocations(getBBPairForRegion(&S->getRegion()), Begin, End);
      OptimizationRemarkAnalysis R(DEBUG_TYPE, "OutOfQuota", Begin,
                                   S->getEntry());
      R << "maximal number of operations exceeded during zone analysis";
      S->getFunction().getContext().diagnose(R);
      return false;
    }

    Zone = OriginalZone =
        Knowledge(std::move(EltLifetime), true, std::move(EltWritten));
    DEBUG(dbgs() << "Computed Zone:\n"; OriginalZone.print(dbgs(), 4));

    assert(Zone.isUsable() && OriginalZone.isUsable());
    return true;
  }

  /// Try to map as many scalars to unused array elements as possible.
  ///
  /// Multiple scalars might be mappable to intersecting unused array element
  /// zones, but we can only chose one. This is a greedy algorithm, therefore
  /// the first processed element claims it.
  void greedyCollapse() {
    bool Modified = false;

    for (auto &Stmt : *S) {
      // collapseScalarsToStore() can add more MemoryAccesses (tryComputedPHI),
      // which can cause the vector that stores the accesses to grow,
      // invalidating the iterators.
      SmallVector<MemoryAccess *, 16> Accs(Stmt.begin(), Stmt.end());

      for (auto *MA : Accs) {
        if (!MA->isLatestArrayKind())
          continue;
        if (!MA->isWrite())
          continue;

        if (MA->isMayWrite()) {
          DEBUG(dbgs() << "Access " << MA
                       << " pruned because it is a MAY_WRITE\n");
          OptimizationRemarkMissed R(DEBUG_TYPE, "TargetMayWrite",
                                     MA->getAccessInstruction());
          R << "Skipped possible mapping target because it is not an "
               "unconditional overwrite";
          S->getFunction().getContext().diagnose(R);
          continue;
        }

        if (Stmt.getNumIterators() == 0) {
          DEBUG(dbgs() << "Access " << MA
                       << " pruned because it is not in a loop\n");
          OptimizationRemarkMissed R(DEBUG_TYPE, "WriteNotInLoop",
                                     MA->getAccessInstruction());
          R << "skipped possible mapping target because it is not in a loop";
          S->getFunction().getContext().diagnose(R);
          continue;
        }

        if (isScalarAccess(MA)) {
          DEBUG(dbgs() << "Access " << MA
                       << " pruned because it writes only a single element\n");
          OptimizationRemarkMissed R(DEBUG_TYPE, "ScalarWrite",
                                     MA->getAccessInstruction());
          R << "skipped possible mapping target because the memory location "
               "written to does not depend on its outer loop";
          S->getFunction().getContext().diagnose(R);
          continue;
        }

        NumberOfCompatibleTargets++;
        DEBUG(dbgs() << "Analyzing target access " << MA << "\n");
        if (collapseScalarsToStore(MA))
          Modified = true;
      }
    }

    if (Modified)
      DeLICMScopsModified++;
  }

  /// Dump the internal information about a performed DeLICM to @p OS.
  void print(llvm::raw_ostream &OS, int Indent = 0) {
    if (!Zone.isUsable()) {
      OS.indent(Indent) << "Zone not computed\n";
      return;
    }

    printStatistics(OS, Indent);
    if (!isModified()) {
      OS.indent(Indent) << "No modification has been made\n";
      return;
    }
    printBefore(OS, Indent);
    printMappedScalars(OS, Indent);
    printAfter(OS, Indent);
    printAccesses(OS, Indent);
  }
};

class DeLICM : public ScopPass {
private:
  DeLICM(const DeLICM &) = delete;
  const DeLICM &operator=(const DeLICM &) = delete;

  /// The pass implementation, also holding per-scop data.
  std::unique_ptr<DeLICMImpl> Impl;

  void collapseToUnused(Scop &S) {
    Impl = make_unique<DeLICMImpl>(
        &S, &getAnalysis<LoopInfoWrapperPass>().getLoopInfo());

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
    AU.addRequired<LoopInfoWrapperPass>();
    AU.setPreservesAll();
  }

  virtual bool runOnScop(Scop &S) override {
    // Free resources for previous scop's computation, if not yet done.
    releaseMemory();

    if (UnprofitableScalarAccs && !PollyProcessUnprofitable)
      DEBUG(dbgs() << "WARNING: -polly-unprofitable-scalar-accs=true active; "
                      "optimizable SCoPs might have been pruned prematurely\n");

    collapseToUnused(S);

    return false;
  }

  virtual void printScop(raw_ostream &OS, Scop &S) const override {
    if (!Impl)
      return;
    assert(Impl->getScop() == &S);

    OS << "DeLICM result:\n";
    assert(Impl->getScop() == &S);
    Impl->print(OS);
  }

  virtual void releaseMemory() override { Impl.reset(); }
};

char DeLICM::ID;
} // anonymous namespace

Pass *polly::createDeLICMPass() { return new DeLICM(); }

INITIALIZE_PASS_BEGIN(DeLICM, "polly-delicm", "Polly - DeLICM/DePRE", false,
                      false)
INITIALIZE_PASS_DEPENDENCY(ScopInfoWrapperPass)
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
  isl::union_map Candidates;

  /// The chosen array elements, one for each element execution.
  // { Domain[] -> Element[] }
  isl::map Target;

  /// Value each MemoryAccess instance expects to read, either from
  // { Domain[] -> Value[] }
  isl::map RequiredValue;

  KnownReport(MemoryAccess *ReadMA, isl::union_map Candidates, isl::map Target,
              isl::map RequiredValue)
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
  isl::union_map Known;

  /// List of redirect-scalar-access-to-known-array-element actions done.
  /// @see collapseKnownLoad()
  SmallVector<KnownReport, 8> KnownReports;

  // LoopInfo *LI;
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
  void collapseKnownLoad(MemoryAccess *RA, isl::map Target,
                         isl::union_map Candidates, isl::map RequiredValue) {
    assert(RA->isRead());
    assert(RA->isLatestScalarKind());
    assert(isl_map_is_single_valued(Target.keep()));

    RA->setNewAccessRelation(Target.copy());

    MappedKnown++;
    KnownReports.emplace_back(RA, std::move(Candidates), std::move(Target),
                              std::move(RequiredValue));
  }

  static ScopStmt *getStmtOfMap(isl::map Map, isl_dim_type DimType) {
    auto Id = give(isl_map_get_tuple_id(Map.keep(), DimType));
    auto *Result = reinterpret_cast<ScopStmt *>(isl_id_get_user(Id.keep()));
    return Result;
  }

  bool canForwardTree(llvm::Value *UseVal, ScopStmt *UseStmt, Loop *UseLoop,
                      // { DomainUse[] -> Scatter[] }
                      isl::map UseScatter, ScopStmt *TargetStmt,
                      // { DomainUse[] -> DomainTarget[] }
                      isl::map UseToTargetMapping, int Depth, bool DoIt,
                      MemoryAccess *&ReuseMe) {
    assert(getStmtOfMap(UseToTargetMapping, isl_dim_in) == UseStmt);
    assert(getStmtOfMap(UseToTargetMapping, isl_dim_out) == TargetStmt);

    // Don't handle PHIs (yet)
    if (isa<PHINode>(UseVal))
      return false;

    auto VUse = VirtualUse::create(UseStmt, false, UseLoop, UseVal);

    switch (VUse.getType()) {
    case VirtualUse::Constant:
    case VirtualUse::Synthesizable:
      return true;

    case VirtualUse::ReadOnly:
      if (DoIt && ModelReadOnlyScalars &&
          !getInputAccessOf(UseVal, TargetStmt, false)) {
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
    // auto DefLoop = LI->getLoopFor(Inst->getParent());

    // { DomainDef[] -> Scatter[] }
    isl::map DefScatter;

    // { DomainDef[] -> DomainTarget[] }
    isl::map DefToTargetMapping;

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
      DefToTargetMapping = give(isl_map_apply_range(
          isl_map_reverse(DefToUseMapping.copy()), UseToTargetMapping.copy()));

      assert(getStmtOfMap(DefToTargetMapping, isl_dim_in) == DefStmt);
      assert(getStmtOfMap(DefToTargetMapping, isl_dim_out) == TargetStmt);
    }

    if (auto LI = dyn_cast<LoadInst>(Inst)) {
      if (!canForwardTree(LI->getPointerOperand(), DefStmt, UseLoop, DefScatter,
                          TargetStmt, DefToTargetMapping, Depth + 1, DoIt,
                          ReuseMe))
        return false;

      auto *RA = &DefStmt->getArrayAccessFor(LI);

      // { DomainDef[] -> ValInst[] }
      auto ExpectedVal = makeValInst(UseVal, DefStmt, false, UseLoop);

      // { DomainTarget[] -> ValInst[] }
      auto ToExpectedVal = give(
          isl_map_apply_domain(ExpectedVal.copy(), DefToTargetMapping.copy()));

      isl::union_map Candidates;
      // { DomainTo[] -> Element[] }
      auto SameVal = containsSameValue(ToExpectedVal, getScatterFor(TargetStmt),
                                       Candidates);
      if (!SameVal)
        return false;
      if (DoIt) {
        MemoryAccess *Access = TargetStmt->getArrayAccessOrNULLFor(LI);
        if (!Access) {
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
        }

        MappedKnown++;
        KnownReports.emplace_back(RA, std::move(Candidates), std::move(SameVal),
                                  std::move(ToExpectedVal));
      }
      return true;
    }

    if (Inst->mayHaveSideEffects())
      return false;

    for (auto OpVal : Inst->operand_values()) {
      if (!canForwardTree(OpVal, DefStmt, UseLoop, DefScatter, TargetStmt,
                          DefToTargetMapping, Depth + 1, DoIt, ReuseMe))
        return false;
    }

    return true;
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
  isl::map containsSameValue(
      // { Domain[] -> ValInst[] }
      isl::map ValInst,
      // { Domain[] -> Scatter[] }
      isl::map Sched, isl::union_map &MustKnownMap) {

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

    isl::map Result;

    // MemoryAccesses can read only elements from a single array (not: { Dom[0]
    // -> A[0]; Dom[1] -> B[1] }). Look through all arrays until we find one
    // that contains exactly the wanted values.
    foreachEltWithBreak(MustKnownMap, [&, this](isl::map Map) -> isl_stat {
      // Get the array this is accessing.
      auto ArrayId = give(isl_map_get_tuple_id(Map.keep(), isl_dim_out));
      auto SAI = static_cast<ScopArrayInfo *>(isl_id_get_user(ArrayId.keep()));

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
    auto ValInst = makeValInst(RA->getAccessValue(), RA->getStatement(),
                               RA->isRead() && RA->isImplicit(),
                               RA->getStatement()->getSurroundingLoop());

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
    foreachEltWithBreak(MustKnownMap, [&, this](isl::map Map) -> isl_stat {
      // Get the array this is accessing.
      auto ArrayId = give(isl_map_get_tuple_id(Map.keep(), isl_dim_out));
      auto SAI = static_cast<ScopArrayInfo *>(isl_id_get_user(ArrayId.keep()));

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
  KnownImpl(Scop *S, LoopInfo *LI) : ZoneAlgorithm(S, LI) {}

  /// A reaching definition zone is known to have the definition's written value
  /// if the definition is a MUST_WRITE.
  ///
  /// @return { [Element[] -> Zone[]] -> ValInst[] }
  isl::union_map computeKnownFromMustWrites() const {
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
  isl::union_map computeKnownFromLoad() const {

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
  isl::union_map computeKnownFromInit() const {
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
    isl::union_map MustKnown, KnownFromLoad, KnownFromInit;

    // Check that nothing strange occurs.
    if (!isCompatibleScop()) {
      DeLICMIncompatible++;
      return false;
    }

    {
      IslMaxOperationsGuard MaxOpGuard(IslCtx.get(), KnownMaxOps);

      computeCommon();

      // { [Element[] -> Zone[]] -> ValInst[] }
      MustKnown = computeKnownFromMustWrites();

      // { [Element[] -> Zone[]] -> ValInst[] }
      KnownFromLoad = computeKnownFromLoad();

      // { [Element[] -> Zone[]] -> ValInst[] }
      Known = give(isl_union_map_union(KnownFromLoad.copy(), MustKnown.copy()));
      simplify(Known);
    }

    if (isl_ctx_last_error(IslCtx.get()) == isl_error_quota) {
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
    if (!UseVirtualStmts) {
      DEBUG(dbgs() << "-polly-known requires virtual statements "
                      "(-polly-codegen-virtual-statements)\n");
      return;
    }

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

    if (UnprofitableScalarAccs)
      DEBUG(dbgs() << "WARNING: -polly-unprofitable-scalar-accs=true active; "
                      "optimizable SCoPs might have been pruned prematurely\n");

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

isl::union_map
polly::computeArrayLifetime(isl::union_map Schedule, isl::union_map Writes,
                            isl::union_map Reads, bool ReadEltInSameInst,
                            bool InclWrite, bool InclLastRead, bool ExitReads) {
  isl::union_map ExitRays;
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

bool polly::isConflicting(isl::union_map ExistingLifetime,
                          bool ExistingImplicitLifetimeIsUnknown,
                          isl::union_map ExistingWritten,
                          isl::union_map ProposedLifetime,
                          bool ProposedImplicitLifetimeIsUnknown,
                          isl::union_map ProposedWritten) {
  Knowledge Existing(std::move(ExistingLifetime),
                     ExistingImplicitLifetimeIsUnknown,
                     std::move(ExistingWritten));
  Knowledge Proposed(std::move(ProposedLifetime),
                     ProposedImplicitLifetimeIsUnknown,
                     std::move(ProposedWritten));

  return Knowledge::isConflicting(Existing, Proposed);
}
