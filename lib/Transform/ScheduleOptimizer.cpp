//===- Schedule.cpp - Calculate an optimized schedule ---------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This pass generates an entirely new schedule tree from the data dependences
// and iteration domains. The new schedule tree is computed in two steps:
//
// 1) The isl scheduling optimizer is run
//
// The isl scheduling optimizer creates a new schedule tree that maximizes
// parallelism and tileability and minimizes data-dependence distances. The
// algorithm used is a modified version of the ``Pluto'' algorithm:
//
//   U. Bondhugula, A. Hartono, J. Ramanujam, and P. Sadayappan.
//   A Practical Automatic Polyhedral Parallelizer and Locality Optimizer.
//   In Proceedings of the 2008 ACM SIGPLAN Conference On Programming Language
//   Design and Implementation, PLDI ’08, pages 101–113. ACM, 2008.
//
// 2) A set of post-scheduling transformations is applied on the schedule tree.
//
// These optimizations include:
//
//  - Tiling of the innermost tilable bands
//  - Prevectorization - The choice of a possible outer loop that is strip-mined
//                       to the innermost level to enable inner-loop
//                       vectorization.
//  - Some optimizations for spatial locality are also planned.
//
// For a detailed description of the schedule tree itself please see section 6
// of:
//
// Polyhedral AST generation is more than scanning polyhedra
// Tobias Grosser, Sven Verdoolaege, Albert Cohen
// ACM Transactions on Programming Languages and Systems (TOPLAS),
// 37(4), July 2015
// http://www.grosser.es/#pub-polyhedral-AST-generation
//
// This publication also contains a detailed discussion of the different options
// for polyhedral loop unrolling, full/partial tile separation and other uses
// of the schedule tree.
//
//===----------------------------------------------------------------------===//

#include "polly/CodeGen/CodeGeneration.h"
#include "polly/DependenceInfo.h"
#include "polly/LinkAllPasses.h"
#include "polly/Options.h"
#include "polly/ScheduleOptimizer.h"
#include "polly/ScopInfo.h"
#include "polly/ScopPass.h"
#include "polly/Simplify.h"
#include "polly/Support/GICHelper.h"
#include "polly/Support/ISLOStream.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/LoopUtils.h"
#include "isl/constraint.h"
#include "isl/ctx.h"
#include "isl/map.h"
#include "isl/options.h"
#include "isl/printer.h"
#include "isl/schedule.h"
#include "isl/schedule_node.h"
#include "isl/space.h"
#include "isl/union_map.h"
#include "isl/union_set.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>
#include <tuple>

using namespace llvm;
using namespace polly;

#define DEBUG_TYPE "polly-opt-isl"

static cl::opt<std::string>
    OptimizeDeps("polly-opt-optimize-only",
                 cl::desc("Only a certain kind of dependences (all/raw)"),
                 cl::Hidden, cl::init("all"), cl::ZeroOrMore,
                 cl::cat(PollyCategory));

static cl::opt<std::string>
    SimplifyDeps("polly-opt-simplify-deps",
                 cl::desc("Dependences should be simplified (yes/no)"),
                 cl::Hidden, cl::init("yes"), cl::ZeroOrMore,
                 cl::cat(PollyCategory));

static cl::opt<int> MaxConstantTerm(
    "polly-opt-max-constant-term",
    cl::desc("The maximal constant term allowed (-1 is unlimited)"), cl::Hidden,
    cl::init(20), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<int> MaxCoefficient(
    "polly-opt-max-coefficient",
    cl::desc("The maximal coefficient allowed (-1 is unlimited)"), cl::Hidden,
    cl::init(20), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<std::string> FusionStrategy(
    "polly-opt-fusion", cl::desc("The fusion strategy to choose (min/max)"),
    cl::Hidden, cl::init("min"), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<std::string>
    MaximizeBandDepth("polly-opt-maximize-bands",
                      cl::desc("Maximize the band depth (yes/no)"), cl::Hidden,
                      cl::init("yes"), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<std::string> OuterCoincidence(
    "polly-opt-outer-coincidence",
    cl::desc("Try to construct schedules where the outer member of each band "
             "satisfies the coincidence constraints (yes/no)"),
    cl::Hidden, cl::init("no"), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<int> PrevectorWidth(
    "polly-prevect-width",
    cl::desc(
        "The number of loop iterations to strip-mine for pre-vectorization"),
    cl::Hidden, cl::init(4), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<bool> FirstLevelTiling("polly-tiling",
                                      cl::desc("Enable loop tiling"),
                                      cl::init(true), cl::ZeroOrMore,
                                      cl::cat(PollyCategory));

static cl::opt<int> LatencyVectorFma(
    "polly-target-latency-vector-fma",
    cl::desc("The minimal number of cycles between issuing two "
             "dependent consecutive vector fused multiply-add "
             "instructions."),
    cl::Hidden, cl::init(8), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<int> ThroughputVectorFma(
    "polly-target-throughput-vector-fma",
    cl::desc("A throughput of the processor floating-point arithmetic units "
             "expressed in the number of vector fused multiply-add "
             "instructions per clock cycle."),
    cl::Hidden, cl::init(1), cl::ZeroOrMore, cl::cat(PollyCategory));

// This option, along with --polly-target-2nd-cache-level-associativity,
// --polly-target-1st-cache-level-size, and --polly-target-2st-cache-level-size
// represent the parameters of the target cache, which do not have typical
// values that can be used by default. However, to apply the pattern matching
// optimizations, we use the values of the parameters of Intel Core i7-3820
// SandyBridge in case the parameters are not specified or not provided by the
// TargetTransformInfo.
static cl::opt<int> FirstCacheLevelAssociativity(
    "polly-target-1st-cache-level-associativity",
    cl::desc("The associativity of the first cache level."), cl::Hidden,
    cl::init(-1), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<int> FirstCacheLevelDefaultAssociativity(
    "polly-target-1st-cache-level-default-associativity",
    cl::desc("The default associativity of the first cache level"
             " (if not enough were provided by the TargetTransformInfo)."),
    cl::Hidden, cl::init(8), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<int> SecondCacheLevelAssociativity(
    "polly-target-2nd-cache-level-associativity",
    cl::desc("The associativity of the second cache level."), cl::Hidden,
    cl::init(-1), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<int> SecondCacheLevelDefaultAssociativity(
    "polly-target-2nd-cache-level-default-associativity",
    cl::desc("The default associativity of the second cache level"
             " (if not enough were provided by the TargetTransformInfo)."),
    cl::Hidden, cl::init(8), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<int> FirstCacheLevelSize(
    "polly-target-1st-cache-level-size",
    cl::desc("The size of the first cache level specified in bytes."),
    cl::Hidden, cl::init(-1), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<int> FirstCacheLevelDefaultSize(
    "polly-target-1st-cache-level-default-size",
    cl::desc("The default size of the first cache level specified in bytes"
             " (if not enough were provided by the TargetTransformInfo)."),
    cl::Hidden, cl::init(32768), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<int> SecondCacheLevelSize(
    "polly-target-2nd-cache-level-size",
    cl::desc("The size of the second level specified in bytes."), cl::Hidden,
    cl::init(-1), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<int> SecondCacheLevelDefaultSize(
    "polly-target-2nd-cache-level-default-size",
    cl::desc("The default size of the second cache level specified in bytes"
             " (if not enough were provided by the TargetTransformInfo)."),
    cl::Hidden, cl::init(262144), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<int> VectorRegisterBitwidth(
    "polly-target-vector-register-bitwidth",
    cl::desc("The size in bits of a vector register (if not set, this "
             "information is taken from LLVM's target information."),
    cl::Hidden, cl::init(-1), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<int> FirstLevelDefaultTileSize(
    "polly-default-tile-size",
    cl::desc("The default tile size (if not enough were provided by"
             " --polly-tile-sizes)"),
    cl::Hidden, cl::init(32), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::list<int>
    FirstLevelTileSizes("polly-tile-sizes",
                        cl::desc("A tile size for each loop dimension, filled "
                                 "with --polly-default-tile-size"),
                        cl::Hidden, cl::ZeroOrMore, cl::CommaSeparated,
                        cl::cat(PollyCategory));

static cl::opt<bool>
    SecondLevelTiling("polly-2nd-level-tiling",
                      cl::desc("Enable a 2nd level loop of loop tiling"),
                      cl::init(false), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<int> SecondLevelDefaultTileSize(
    "polly-2nd-level-default-tile-size",
    cl::desc("The default 2nd-level tile size (if not enough were provided by"
             " --polly-2nd-level-tile-sizes)"),
    cl::Hidden, cl::init(16), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::list<int>
    SecondLevelTileSizes("polly-2nd-level-tile-sizes",
                         cl::desc("A tile size for each loop dimension, filled "
                                  "with --polly-default-tile-size"),
                         cl::Hidden, cl::ZeroOrMore, cl::CommaSeparated,
                         cl::cat(PollyCategory));

static cl::opt<bool> RegisterTiling("polly-register-tiling",
                                    cl::desc("Enable register tiling"),
                                    cl::init(false), cl::ZeroOrMore,
                                    cl::cat(PollyCategory));

static cl::opt<int> RegisterDefaultTileSize(
    "polly-register-tiling-default-tile-size",
    cl::desc("The default register tile size (if not enough were provided by"
             " --polly-register-tile-sizes)"),
    cl::Hidden, cl::init(2), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<int> PollyPatternMatchingNcQuotient(
    "polly-pattern-matching-nc-quotient",
    cl::desc("Quotient that is obtained by dividing Nc, the parameter of the"
             "macro-kernel, by Nr, the parameter of the micro-kernel"),
    cl::Hidden, cl::init(256), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::list<int>
    RegisterTileSizes("polly-register-tile-sizes",
                      cl::desc("A tile size for each loop dimension, filled "
                               "with --polly-register-tile-size"),
                      cl::Hidden, cl::ZeroOrMore, cl::CommaSeparated,
                      cl::cat(PollyCategory));

static cl::opt<bool>
    PMBasedOpts("polly-pattern-matching-based-opts",
                cl::desc("Perform optimizations based on pattern matching"),
                cl::init(true), cl::ZeroOrMore, cl::cat(PollyCategory));

static cl::opt<bool> OptimizedScops(
    "polly-optimized-scops",
    cl::desc("Polly - Dump polyhedral description of Scops optimized with "
             "the isl scheduling optimizer and the set of post-scheduling "
             "transformations is applied on the schedule tree"),
    cl::init(false), cl::ZeroOrMore, cl::cat(PollyCategory));

STATISTIC(ScopsProcessed, "Number of scops processed");
STATISTIC(ScopsRescheduled, "Number of scops rescheduled");
STATISTIC(ScopsOptimized, "Number of scops optimized");

STATISTIC(NumAffineLoopsOptimized, "Number of affine loops optimized");
STATISTIC(NumBoxedLoopsOptimized, "Number of boxed loops optimized");

#define THREE_STATISTICS(VARNAME, DESC)                                        \
  static Statistic VARNAME[3] = {                                              \
      {DEBUG_TYPE, #VARNAME "0", DESC " (original)", {0}, {false}},            \
      {DEBUG_TYPE, #VARNAME "1", DESC " (after scheduler)", {0}, {false}},     \
      {DEBUG_TYPE, #VARNAME "2", DESC " (after optimizer)", {0}, {false}}}

THREE_STATISTICS(NumBands, "Number of bands");
THREE_STATISTICS(NumBandMembers, "Number of band members");
THREE_STATISTICS(NumCoincident, "Number of coincident band members");
THREE_STATISTICS(NumPermutable, "Number of permutable bands");
THREE_STATISTICS(NumFilters, "Number of filter nodes");
THREE_STATISTICS(NumExtension, "Number of extension nodes");

STATISTIC(FirstLevelTileOpts, "Number of first level tiling applied");
STATISTIC(SecondLevelTileOpts, "Number of second level tiling applied");
STATISTIC(RegisterTileOpts, "Number of register tiling applied");
STATISTIC(PrevectOpts, "Number of strip-mining for prevectorization applied");
STATISTIC(MatMulOpts,
          "Number of matrix multiplication patterns detected and optimized");

/// Create an isl::union_set, which describes the isolate option based on
/// IsolateDomain.
///
/// @param IsolateDomain An isl::set whose @p OutDimsNum last dimensions should
///                      belong to the current band node.
/// @param OutDimsNum    A number of dimensions that should belong to
///                      the current band node.
static isl::union_set getIsolateOptions(isl::set IsolateDomain,
                                        unsigned OutDimsNum) {
  unsigned Dims = IsolateDomain.dim(isl::dim::set);
  assert(OutDimsNum <= Dims &&
         "The isl::set IsolateDomain is used to describe the range of schedule "
         "dimensions values, which should be isolated. Consequently, the "
         "number of its dimensions should be greater than or equal to the "
         "number of the schedule dimensions.");
  isl::map IsolateRelation = isl::map::from_domain(IsolateDomain);
  IsolateRelation = IsolateRelation.move_dims(isl::dim::out, 0, isl::dim::in,
                                              Dims - OutDimsNum, OutDimsNum);
  isl::set IsolateOption = IsolateRelation.wrap();
  isl::id Id = isl::id::alloc(IsolateOption.get_ctx(), "isolate", nullptr);
  IsolateOption = IsolateOption.set_tuple_id(Id);
  return isl::union_set(IsolateOption);
}

namespace {
/// Create an isl::union_set, which describes the specified option for the
/// dimension of the current node.
///
/// @param Ctx    An isl::ctx, which is used to create the isl::union_set.
/// @param Option The name of the option.
isl::union_set getDimOptions(isl::ctx Ctx, const char *Option) {
  isl::space Space(Ctx, 0, 1);
  auto DimOption = isl::set::universe(Space);
  auto Id = isl::id::alloc(Ctx, Option, nullptr);
  DimOption = DimOption.set_tuple_id(Id);
  return isl::union_set(DimOption);
}
} // namespace

/// Create an isl::union_set, which describes the option of the form
/// [isolate[] -> unroll[x]].
///
/// @param Ctx An isl::ctx, which is used to create the isl::union_set.
static isl::union_set getUnrollIsolatedSetOptions(isl::ctx Ctx) {
  isl::space Space = isl::space(Ctx, 0, 0, 1);
  isl::map UnrollIsolatedSetOption = isl::map::universe(Space);
  isl::id DimInId = isl::id::alloc(Ctx, "isolate", nullptr);
  isl::id DimOutId = isl::id::alloc(Ctx, "unroll", nullptr);
  UnrollIsolatedSetOption =
      UnrollIsolatedSetOption.set_tuple_id(isl::dim::in, DimInId);
  UnrollIsolatedSetOption =
      UnrollIsolatedSetOption.set_tuple_id(isl::dim::out, DimOutId);
  return UnrollIsolatedSetOption.wrap();
}

/// Make the last dimension of Set to take values from 0 to VectorWidth - 1.
///
/// @param Set         A set, which should be modified.
/// @param VectorWidth A parameter, which determines the constraint.
static isl::set addExtentConstraints(isl::set Set, int VectorWidth) {
  unsigned Dims = Set.dim(isl::dim::set);
  isl::space Space = Set.get_space();
  isl::local_space LocalSpace = isl::local_space(Space);
  isl::constraint ExtConstr = isl::constraint::alloc_inequality(LocalSpace);
  ExtConstr = ExtConstr.set_constant_si(0);
  ExtConstr = ExtConstr.set_coefficient_si(isl::dim::set, Dims - 1, 1);
  Set = Set.add_constraint(ExtConstr);
  ExtConstr = isl::constraint::alloc_inequality(LocalSpace);
  ExtConstr = ExtConstr.set_constant_si(VectorWidth - 1);
  ExtConstr = ExtConstr.set_coefficient_si(isl::dim::set, Dims - 1, -1);
  return Set.add_constraint(ExtConstr);
}

isl::set getPartialTilePrefixes(isl::set ScheduleRange, int VectorWidth) {
  unsigned Dims = ScheduleRange.dim(isl::dim::set);
  isl::set LoopPrefixes =
      ScheduleRange.drop_constraints_involving_dims(isl::dim::set, Dims - 1, 1);
  auto ExtentPrefixes = addExtentConstraints(LoopPrefixes, VectorWidth);
  isl::set BadPrefixes = ExtentPrefixes.subtract(ScheduleRange);
  BadPrefixes = BadPrefixes.project_out(isl::dim::set, Dims - 1, 1);
  LoopPrefixes = LoopPrefixes.project_out(isl::dim::set, Dims - 1, 1);
  return LoopPrefixes.subtract(BadPrefixes);
}

isl::schedule_node
ScheduleTreeOptimizer::isolateFullPartialTiles(isl::schedule_node Node,
                                               int VectorWidth) {
  assert(isl_schedule_node_get_type(Node.get()) == isl_schedule_node_band);
  Node = Node.child(0).child(0);
  isl::union_map SchedRelUMap = Node.get_prefix_schedule_relation();
  isl::map ScheduleRelation = isl::map::from_union_map(SchedRelUMap);
  isl::set ScheduleRange = ScheduleRelation.range();
  isl::set IsolateDomain = getPartialTilePrefixes(ScheduleRange, VectorWidth);
  auto AtomicOption = getDimOptions(IsolateDomain.get_ctx(), "atomic");
  isl::union_set IsolateOption = getIsolateOptions(IsolateDomain, 1);
  Node = Node.parent().parent();
  isl::union_set Options = IsolateOption.unite(AtomicOption);
  Node = Node.band_set_ast_build_options(Options);
  return Node;
}

isl::schedule_node ScheduleTreeOptimizer::prevectSchedBand(
    isl::schedule_node Node, unsigned DimToVectorize, int VectorWidth) {
  assert(isl_schedule_node_get_type(Node.get()) == isl_schedule_node_band);

  auto Space = isl::manage(isl_schedule_node_band_get_space(Node.get()));
  auto ScheduleDimensions = Space.dim(isl::dim::set);
  assert(DimToVectorize < ScheduleDimensions);

  if (DimToVectorize > 0) {
    Node = isl::manage(
        isl_schedule_node_band_split(Node.release(), DimToVectorize));
    Node = Node.child(0);
  }
  if (DimToVectorize < ScheduleDimensions - 1)
    Node = isl::manage(isl_schedule_node_band_split(Node.release(), 1));
  Space = isl::manage(isl_schedule_node_band_get_space(Node.get()));
  auto Sizes = isl::multi_val::zero(Space);
  Sizes = Sizes.set_val(0, isl::val(Node.get_ctx(), VectorWidth));
  Node =
      isl::manage(isl_schedule_node_band_tile(Node.release(), Sizes.release()));
  Node = isolateFullPartialTiles(Node, VectorWidth);
  Node = Node.child(0);
  // Make sure the "trivially vectorizable loop" is not unrolled. Otherwise,
  // we will have troubles to match it in the backend.
  Node = Node.band_set_ast_build_options(
      isl::union_set(Node.get_ctx(), "{ unroll[x]: 1 = 0 }"));
  Node = isl::manage(isl_schedule_node_band_sink(Node.release()));
  Node = Node.child(0);
  if (isl_schedule_node_get_type(Node.get()) == isl_schedule_node_leaf)
    Node = Node.parent();
  auto LoopMarker = isl::id::alloc(Node.get_ctx(), "SIMD", nullptr);
  PrevectOpts++;
  return Node.insert_mark(LoopMarker);
}

isl::schedule_node ScheduleTreeOptimizer::tileNode(isl::schedule_node Node,
                                                   const char *Identifier,
                                                   ArrayRef<int> TileSizes,
                                                   int DefaultTileSize) {
  auto Space = isl::manage(isl_schedule_node_band_get_space(Node.get()));
  auto Dims = Space.dim(isl::dim::set);
  auto Sizes = isl::multi_val::zero(Space);
  std::string IdentifierString(Identifier);
  for (unsigned i = 0; i < Dims; i++) {
    auto tileSize = i < TileSizes.size() ? TileSizes[i] : DefaultTileSize;
    Sizes = Sizes.set_val(i, isl::val(Node.get_ctx(), tileSize));
  }
  auto TileLoopMarkerStr = IdentifierString + " - Tiles";
  auto TileLoopMarker =
      isl::id::alloc(Node.get_ctx(), TileLoopMarkerStr, nullptr);
  Node = Node.insert_mark(TileLoopMarker);
  Node = Node.child(0);
  Node =
      isl::manage(isl_schedule_node_band_tile(Node.release(), Sizes.release()));
  Node = Node.child(0);
  auto PointLoopMarkerStr = IdentifierString + " - Points";
  auto PointLoopMarker =
      isl::id::alloc(Node.get_ctx(), PointLoopMarkerStr, nullptr);
  Node = Node.insert_mark(PointLoopMarker);
  return Node.child(0);
}

isl::schedule_node ScheduleTreeOptimizer::applyRegisterTiling(
    isl::schedule_node Node, ArrayRef<int> TileSizes, int DefaultTileSize) {
  Node = tileNode(Node, "Register tiling", TileSizes, DefaultTileSize);
  auto Ctx = Node.get_ctx();
  return Node.band_set_ast_build_options(isl::union_set(Ctx, "{unroll[x]}"));
}

static bool isSimpleInnermostBand(const isl::schedule_node &Node) {
  assert(isl_schedule_node_get_type(Node.get()) == isl_schedule_node_band);
  assert(isl_schedule_node_n_children(Node.get()) == 1);

  auto ChildType = isl_schedule_node_get_type(Node.child(0).get());

  if (ChildType == isl_schedule_node_leaf)
    return true;

  if (ChildType != isl_schedule_node_sequence)
    return false;

  auto Sequence = Node.child(0);

  for (int c = 0, nc = isl_schedule_node_n_children(Sequence.get()); c < nc;
       ++c) {
    auto Child = Sequence.child(c);
    if (isl_schedule_node_get_type(Child.get()) != isl_schedule_node_filter)
      return false;
    if (isl_schedule_node_get_type(Child.child(0).get()) !=
        isl_schedule_node_leaf)
      return false;
  }
  return true;
}

bool ScheduleTreeOptimizer::isTileableBandNode(isl::schedule_node Node) {
  if (isl_schedule_node_get_type(Node.get()) != isl_schedule_node_band)
    return false;

  if (isl_schedule_node_n_children(Node.get()) != 1)
    return false;

  if (!isl_schedule_node_band_get_permutable(Node.get()))
    return false;

  auto Space = isl::manage(isl_schedule_node_band_get_space(Node.get()));
  auto Dims = Space.dim(isl::dim::set);

  if (Dims <= 1)
    return false;

  return isSimpleInnermostBand(Node);
}

__isl_give isl::schedule_node
ScheduleTreeOptimizer::standardBandOpts(isl::schedule_node Node, void *User) {
  if (FirstLevelTiling) {
    Node = tileNode(Node, "1st level tiling", FirstLevelTileSizes,
                    FirstLevelDefaultTileSize);
    FirstLevelTileOpts++;
  }

  if (SecondLevelTiling) {
    Node = tileNode(Node, "2nd level tiling", SecondLevelTileSizes,
                    SecondLevelDefaultTileSize);
    SecondLevelTileOpts++;
  }

  if (RegisterTiling) {
    Node =
        applyRegisterTiling(Node, RegisterTileSizes, RegisterDefaultTileSize);
    RegisterTileOpts++;
  }

  if (PollyVectorizerChoice == VECTORIZER_NONE)
    return Node;

  auto Space = isl::manage(isl_schedule_node_band_get_space(Node.get()));
  auto Dims = Space.dim(isl::dim::set);

  for (int i = Dims - 1; i >= 0; i--)
    if (Node.band_member_get_coincident(i)) {
      Node = prevectSchedBand(Node, i, PrevectorWidth);
      break;
    }

  return Node;
}

/// Permute the two dimensions of the isl map.
///
/// Permute @p DstPos and @p SrcPos dimensions of the isl map @p Map that
/// have type @p DimType.
///
/// @param Map     The isl map to be modified.
/// @param DimType The type of the dimensions.
/// @param DstPos  The first dimension.
/// @param SrcPos  The second dimension.
/// @return        The modified map.
isl::map permuteDimensions(isl::map Map, isl::dim DimType, unsigned DstPos,
                           unsigned SrcPos) {
  assert(DstPos < Map.dim(DimType) && SrcPos < Map.dim(DimType));
  if (DstPos == SrcPos)
    return Map;
  isl::id DimId;
  if (Map.has_tuple_id(DimType))
    DimId = Map.get_tuple_id(DimType);
  auto FreeDim = DimType == isl::dim::in ? isl::dim::out : isl::dim::in;
  isl::id FreeDimId;
  if (Map.has_tuple_id(FreeDim))
    FreeDimId = Map.get_tuple_id(FreeDim);
  auto MaxDim = std::max(DstPos, SrcPos);
  auto MinDim = std::min(DstPos, SrcPos);
  Map = Map.move_dims(FreeDim, 0, DimType, MaxDim, 1);
  Map = Map.move_dims(FreeDim, 0, DimType, MinDim, 1);
  Map = Map.move_dims(DimType, MinDim, FreeDim, 1, 1);
  Map = Map.move_dims(DimType, MaxDim, FreeDim, 0, 1);
  if (DimId)
    Map = Map.set_tuple_id(DimType, DimId);
  if (FreeDimId)
    Map = Map.set_tuple_id(FreeDim, FreeDimId);
  return Map;
}

/// Check the form of the access relation.
///
/// Check that the access relation @p AccMap has the form M[i][j], where i
/// is a @p FirstPos and j is a @p SecondPos.
///
/// @param AccMap    The access relation to be checked.
/// @param FirstPos  The index of the input dimension that is mapped to
///                  the first output dimension.
/// @param SecondPos The index of the input dimension that is mapped to the
///                  second output dimension.
/// @return          True in case @p AccMap has the expected form and false,
///                  otherwise.
static bool isMatMulOperandAcc(isl::set Domain, isl::map AccMap, int &FirstPos,
                               int &SecondPos) {
  isl::space Space = AccMap.get_space();
  isl::map Universe = isl::map::universe(Space);

  if (Space.dim(isl::dim::out) != 2)
    return false;

  // MatMul has the form:
  // for (i = 0; i < N; i++)
  //   for (j = 0; j < M; j++)
  //     for (k = 0; k < P; k++)
  //       C[i, j] += A[i, k] * B[k, j]
  //
  // Permutation of three outer loops: 3! = 6 possibilities.
  int FirstDims[] = {0, 0, 1, 1, 2, 2};
  int SecondDims[] = {1, 2, 2, 0, 0, 1};
  for (int i = 0; i < 6; i += 1) {
    auto PossibleMatMul =
        Universe.equate(isl::dim::in, FirstDims[i], isl::dim::out, 0)
            .equate(isl::dim::in, SecondDims[i], isl::dim::out, 1);

    AccMap = AccMap.intersect_domain(Domain);
    PossibleMatMul = PossibleMatMul.intersect_domain(Domain);

    // If AccMap spans entire domain (Non-partial write),
    // compute FirstPos and SecondPos.
    // If AccMap != PossibleMatMul here (the two maps have been gisted at
    // this point), it means that the writes are not complete, or in other
    // words, it is a Partial write and Partial writes must be rejected.
    if (AccMap.is_equal(PossibleMatMul)) {
      if (FirstPos != -1 && FirstPos != FirstDims[i])
        continue;
      FirstPos = FirstDims[i];
      if (SecondPos != -1 && SecondPos != SecondDims[i])
        continue;
      SecondPos = SecondDims[i];
      return true;
    }
  }

  return false;
}

/// Does the memory access represent a non-scalar operand of the matrix
/// multiplication.
///
/// Check that the memory access @p MemAccess is the read access to a non-scalar
/// operand of the matrix multiplication or its result.
///
/// @param MemAccess The memory access to be checked.
/// @param MMI       Parameters of the matrix multiplication operands.
/// @return          True in case the memory access represents the read access
///                  to a non-scalar operand of the matrix multiplication and
///                  false, otherwise.
static bool isMatMulNonScalarReadAccess(MemoryAccess *MemAccess,
                                        MatMulInfoTy &MMI) {
  if (!MemAccess->isLatestArrayKind() || !MemAccess->isRead())
    return false;
  auto AccMap = MemAccess->getLatestAccessRelation();
  isl::set StmtDomain = MemAccess->getStatement()->getDomain();
  if (isMatMulOperandAcc(StmtDomain, AccMap, MMI.i, MMI.j) && !MMI.ReadFromC) {
    MMI.ReadFromC = MemAccess;
    return true;
  }
  if (isMatMulOperandAcc(StmtDomain, AccMap, MMI.i, MMI.k) && !MMI.A) {
    MMI.A = MemAccess;
    return true;
  }
  if (isMatMulOperandAcc(StmtDomain, AccMap, MMI.k, MMI.j) && !MMI.B) {
    MMI.B = MemAccess;
    return true;
  }
  return false;
}

/// Check accesses to operands of the matrix multiplication.
///
/// Check that accesses of the SCoP statement, which corresponds to
/// the partial schedule @p PartialSchedule, are scalar in terms of loops
/// containing the matrix multiplication, in case they do not represent
/// accesses to the non-scalar operands of the matrix multiplication or
/// its result.
///
/// @param  PartialSchedule The partial schedule of the SCoP statement.
/// @param  MMI             Parameters of the matrix multiplication operands.
/// @return                 True in case the corresponding SCoP statement
///                         represents matrix multiplication and false,
///                         otherwise.
static bool containsOnlyMatrMultAcc(isl::map PartialSchedule,
                                    MatMulInfoTy &MMI) {
  auto InputDimId = PartialSchedule.get_tuple_id(isl::dim::in);
  auto *Stmt = static_cast<ScopStmt *>(InputDimId.get_user());
  unsigned OutDimNum = PartialSchedule.dim(isl::dim::out);
  assert(OutDimNum > 2 && "In case of the matrix multiplication the loop nest "
                          "and, consequently, the corresponding scheduling "
                          "functions have at least three dimensions.");
  auto MapI =
      permuteDimensions(PartialSchedule, isl::dim::out, MMI.i, OutDimNum - 1);
  auto MapJ =
      permuteDimensions(PartialSchedule, isl::dim::out, MMI.j, OutDimNum - 1);
  auto MapK =
      permuteDimensions(PartialSchedule, isl::dim::out, MMI.k, OutDimNum - 1);

  auto Accesses = getAccessesInOrder(*Stmt);
  for (auto *MemA = Accesses.begin(); MemA != Accesses.end() - 1; MemA++) {
    auto *MemAccessPtr = *MemA;
    if (MemAccessPtr->isLatestArrayKind() && MemAccessPtr != MMI.WriteToC &&
        !isMatMulNonScalarReadAccess(MemAccessPtr, MMI) &&
        !(MemAccessPtr->isStrideZero(MapI)) &&
        MemAccessPtr->isStrideZero(MapJ) && MemAccessPtr->isStrideZero(MapK))
      return false;
  }
  return true;
}

/// Check for dependencies corresponding to the matrix multiplication.
///
/// Check that there is only true dependence of the form
/// S(..., k, ...) -> S(..., k + 1, …), where S is the SCoP statement
/// represented by @p Schedule and k is @p Pos. Such a dependence corresponds
/// to the dependency produced by the matrix multiplication.
///
/// @param  Schedule The schedule of the SCoP statement.
/// @param  D The SCoP dependencies.
/// @param  Pos The parameter to describe an acceptable true dependence.
///             In case it has a negative value, try to determine its
///             acceptable value.
/// @return True in case dependencies correspond to the matrix multiplication
///         and false, otherwise.
static bool containsOnlyMatMulDep(isl::map Schedule, const Dependences *D,
                                  int &Pos) {
  auto Dep = isl::manage(D->getDependences(Dependences::TYPE_RAW));
  auto Red = isl::manage(D->getDependences(Dependences::TYPE_RED));
  if (Red)
    Dep = Dep.unite(Red);
  auto DomainSpace = Schedule.get_space().domain();
  auto Space = DomainSpace.map_from_domain_and_range(DomainSpace);
  auto Deltas = Dep.extract_map(Space).deltas();
  int DeltasDimNum = Deltas.dim(isl::dim::set);
  for (int i = 0; i < DeltasDimNum; i++) {
    auto Val = Deltas.plain_get_val_if_fixed(isl::dim::set, i);
    Pos = Pos < 0 && Val.is_one() ? i : Pos;
    if (Val.is_nan() || !(Val.is_zero() || (i == Pos && Val.is_one())))
      return false;
  }
  if (DeltasDimNum == 0 || Pos < 0)
    return false;
  return true;
}

/// Check if the SCoP statement could probably be optimized with analytical
/// modeling.
///
/// containsMatrMult tries to determine whether the following conditions
/// are true:
/// 1. The last memory access modeling an array, MA1, represents writing to
///    memory and has the form S(..., i1, ..., i2, ...) -> M(i1, i2) or
///    S(..., i2, ..., i1, ...) -> M(i1, i2), where S is the SCoP statement
///    under consideration.
/// 2. There is only one loop-carried true dependency, and it has the
///    form S(..., i3, ...) -> S(..., i3 + 1, ...), and there are no
///    loop-carried or anti dependencies.
/// 3. SCoP contains three access relations, MA2, MA3, and MA4 that represent
///    reading from memory and have the form S(..., i3, ...) -> M(i1, i3),
///    S(..., i3, ...) -> M(i3, i2), S(...) -> M(i1, i2), respectively,
///    and all memory accesses of the SCoP that are different from MA1, MA2,
///    MA3, and MA4 have stride 0, if the innermost loop is exchanged with any
///    of loops i1, i2 and i3.
///
/// @param PartialSchedule The PartialSchedule that contains a SCoP statement
///        to check.
/// @D     The SCoP dependencies.
/// @MMI   Parameters of the matrix multiplication operands.
static bool containsMatrMult(isl::map PartialSchedule, const Dependences *D,
                             MatMulInfoTy &MMI) {
  auto InputDimsId = PartialSchedule.get_tuple_id(isl::dim::in);
  auto *Stmt = static_cast<ScopStmt *>(InputDimsId.get_user());
  if (Stmt->size() <= 1)
    return false;

  auto Accesses = getAccessesInOrder(*Stmt);
  for (auto *MemA = Accesses.end() - 1; MemA != Accesses.begin(); MemA--) {
    auto *MemAccessPtr = *MemA;
    if (!MemAccessPtr->isLatestArrayKind())
      continue;
    if (!MemAccessPtr->isWrite())
      return false;
    auto AccMap = MemAccessPtr->getLatestAccessRelation();
    if (!isMatMulOperandAcc(Stmt->getDomain(), AccMap, MMI.i, MMI.j))
      return false;
    MMI.WriteToC = MemAccessPtr;
    break;
  }

  if (!containsOnlyMatMulDep(PartialSchedule, D, MMI.k))
    return false;

  if (!MMI.WriteToC || !containsOnlyMatrMultAcc(PartialSchedule, MMI))
    return false;

  if (!MMI.A || !MMI.B || !MMI.ReadFromC)
    return false;
  return true;
}

/// Permute two dimensions of the band node.
///
/// Permute FirstDim and SecondDim dimensions of the Node.
///
/// @param Node The band node to be modified.
/// @param FirstDim The first dimension to be permuted.
/// @param SecondDim The second dimension to be permuted.
static isl::schedule_node permuteBandNodeDimensions(isl::schedule_node Node,
                                                    unsigned FirstDim,
                                                    unsigned SecondDim) {
  assert(isl_schedule_node_get_type(Node.get()) == isl_schedule_node_band &&
         isl_schedule_node_band_n_member(Node.get()) >
             std::max(FirstDim, SecondDim));
  auto PartialSchedule =
      isl::manage(isl_schedule_node_band_get_partial_schedule(Node.get()));
  auto PartialScheduleFirstDim = PartialSchedule.get_union_pw_aff(FirstDim);
  auto PartialScheduleSecondDim = PartialSchedule.get_union_pw_aff(SecondDim);
  PartialSchedule =
      PartialSchedule.set_union_pw_aff(SecondDim, PartialScheduleFirstDim);
  PartialSchedule =
      PartialSchedule.set_union_pw_aff(FirstDim, PartialScheduleSecondDim);
  Node = isl::manage(isl_schedule_node_delete(Node.release()));
  return Node.insert_partial_schedule(PartialSchedule);
}

isl::schedule_node ScheduleTreeOptimizer::createMicroKernel(
    isl::schedule_node Node, MicroKernelParamsTy MicroKernelParams) {
  Node = applyRegisterTiling(Node, {MicroKernelParams.Mr, MicroKernelParams.Nr},
                             1);
  Node = Node.parent().parent();
  return permuteBandNodeDimensions(Node, 0, 1).child(0).child(0);
}

isl::schedule_node ScheduleTreeOptimizer::createMacroKernel(
    isl::schedule_node Node, MacroKernelParamsTy MacroKernelParams) {
  assert(isl_schedule_node_get_type(Node.get()) == isl_schedule_node_band);
  if (MacroKernelParams.Mc == 1 && MacroKernelParams.Nc == 1 &&
      MacroKernelParams.Kc == 1)
    return Node;
  int DimOutNum = isl_schedule_node_band_n_member(Node.get());
  std::vector<int> TileSizes(DimOutNum, 1);
  TileSizes[DimOutNum - 3] = MacroKernelParams.Mc;
  TileSizes[DimOutNum - 2] = MacroKernelParams.Nc;
  TileSizes[DimOutNum - 1] = MacroKernelParams.Kc;
  Node = tileNode(Node, "1st level tiling", TileSizes, 1);
  Node = Node.parent().parent();
  Node = permuteBandNodeDimensions(Node, DimOutNum - 2, DimOutNum - 1);
  Node = permuteBandNodeDimensions(Node, DimOutNum - 3, DimOutNum - 1);
  return Node.child(0).child(0);
}

/// Get the size of the widest type of the matrix multiplication operands
/// in bytes, including alignment padding.
///
/// @param MMI Parameters of the matrix multiplication operands.
/// @return The size of the widest type of the matrix multiplication operands
///         in bytes, including alignment padding.
static uint64_t getMatMulAlignTypeSize(MatMulInfoTy MMI) {
  auto *S = MMI.A->getStatement()->getParent();
  auto &DL = S->getFunction().getParent()->getDataLayout();
  auto ElementSizeA = DL.getTypeAllocSize(MMI.A->getElementType());
  auto ElementSizeB = DL.getTypeAllocSize(MMI.B->getElementType());
  auto ElementSizeC = DL.getTypeAllocSize(MMI.WriteToC->getElementType());
  return std::max({ElementSizeA, ElementSizeB, ElementSizeC});
}

/// Get the size of the widest type of the matrix multiplication operands
/// in bits.
///
/// @param MMI Parameters of the matrix multiplication operands.
/// @return The size of the widest type of the matrix multiplication operands
///         in bits.
static uint64_t getMatMulTypeSize(MatMulInfoTy MMI) {
  auto *S = MMI.A->getStatement()->getParent();
  auto &DL = S->getFunction().getParent()->getDataLayout();
  auto ElementSizeA = DL.getTypeSizeInBits(MMI.A->getElementType());
  auto ElementSizeB = DL.getTypeSizeInBits(MMI.B->getElementType());
  auto ElementSizeC = DL.getTypeSizeInBits(MMI.WriteToC->getElementType());
  return std::max({ElementSizeA, ElementSizeB, ElementSizeC});
}

/// Get parameters of the BLIS micro kernel.
///
/// We choose the Mr and Nr parameters of the micro kernel to be large enough
/// such that no stalls caused by the combination of latencies and dependencies
/// are introduced during the updates of the resulting matrix of the matrix
/// multiplication. However, they should also be as small as possible to
/// release more registers for entries of multiplied matrices.
///
/// @param TTI Target Transform Info.
/// @param MMI Parameters of the matrix multiplication operands.
/// @return The structure of type MicroKernelParamsTy.
/// @see MicroKernelParamsTy
static struct MicroKernelParamsTy
getMicroKernelParams(const TargetTransformInfo *TTI, MatMulInfoTy MMI) {
  assert(TTI && "The target transform info should be provided.");

  // Nvec - Number of double-precision floating-point numbers that can be hold
  // by a vector register. Use 2 by default.
  long RegisterBitwidth = VectorRegisterBitwidth;

  if (RegisterBitwidth == -1)
    RegisterBitwidth = TTI->getRegisterBitWidth(true);
  auto ElementSize = getMatMulTypeSize(MMI);
  assert(ElementSize > 0 && "The element size of the matrix multiplication "
                            "operands should be greater than zero.");
  auto Nvec = RegisterBitwidth / ElementSize;
  if (Nvec == 0)
    Nvec = 2;
  int Nr =
      ceil(sqrt(Nvec * LatencyVectorFma * ThroughputVectorFma) / Nvec) * Nvec;
  int Mr = ceil(Nvec * LatencyVectorFma * ThroughputVectorFma / Nr);
  return {Mr, Nr};
}

namespace {
/// Determine parameters of the target cache.
///
/// @param TTI Target Transform Info.
void getTargetCacheParameters(const llvm::TargetTransformInfo *TTI) {
  auto L1DCache = llvm::TargetTransformInfo::CacheLevel::L1D;
  auto L2DCache = llvm::TargetTransformInfo::CacheLevel::L2D;
  if (FirstCacheLevelSize == -1) {
    if (TTI->getCacheSize(L1DCache).hasValue())
      FirstCacheLevelSize = TTI->getCacheSize(L1DCache).getValue();
    else
      FirstCacheLevelSize = static_cast<int>(FirstCacheLevelDefaultSize);
  }
  if (SecondCacheLevelSize == -1) {
    if (TTI->getCacheSize(L2DCache).hasValue())
      SecondCacheLevelSize = TTI->getCacheSize(L2DCache).getValue();
    else
      SecondCacheLevelSize = static_cast<int>(SecondCacheLevelDefaultSize);
  }
  if (FirstCacheLevelAssociativity == -1) {
    if (TTI->getCacheAssociativity(L1DCache).hasValue())
      FirstCacheLevelAssociativity =
          TTI->getCacheAssociativity(L1DCache).getValue();
    else
      FirstCacheLevelAssociativity =
          static_cast<int>(FirstCacheLevelDefaultAssociativity);
  }
  if (SecondCacheLevelAssociativity == -1) {
    if (TTI->getCacheAssociativity(L2DCache).hasValue())
      SecondCacheLevelAssociativity =
          TTI->getCacheAssociativity(L2DCache).getValue();
    else
      SecondCacheLevelAssociativity =
          static_cast<int>(SecondCacheLevelDefaultAssociativity);
  }
}
} // namespace

/// Get parameters of the BLIS macro kernel.
///
/// During the computation of matrix multiplication, blocks of partitioned
/// matrices are mapped to different layers of the memory hierarchy.
/// To optimize data reuse, blocks should be ideally kept in cache between
/// iterations. Since parameters of the macro kernel determine sizes of these
/// blocks, there are upper and lower bounds on these parameters.
///
/// @param TTI Target Transform Info.
/// @param MicroKernelParams Parameters of the micro-kernel
///                          to be taken into account.
/// @param MMI Parameters of the matrix multiplication operands.
/// @return The structure of type MacroKernelParamsTy.
/// @see MacroKernelParamsTy
/// @see MicroKernelParamsTy
static struct MacroKernelParamsTy
getMacroKernelParams(const llvm::TargetTransformInfo *TTI,
                     const MicroKernelParamsTy &MicroKernelParams,
                     MatMulInfoTy MMI) {
  getTargetCacheParameters(TTI);
  // According to www.cs.utexas.edu/users/flame/pubs/TOMS-BLIS-Analytical.pdf,
  // it requires information about the first two levels of a cache to determine
  // all the parameters of a macro-kernel. It also checks that an associativity
  // degree of a cache level is greater than two. Otherwise, another algorithm
  // for determination of the parameters should be used.
  if (!(MicroKernelParams.Mr > 0 && MicroKernelParams.Nr > 0 &&
        FirstCacheLevelSize > 0 && SecondCacheLevelSize > 0 &&
        FirstCacheLevelAssociativity > 2 && SecondCacheLevelAssociativity > 2))
    return {1, 1, 1};
  // The quotient should be greater than zero.
  if (PollyPatternMatchingNcQuotient <= 0)
    return {1, 1, 1};
  int Car = floor(
      (FirstCacheLevelAssociativity - 1) /
      (1 + static_cast<double>(MicroKernelParams.Nr) / MicroKernelParams.Mr));

  // Car can be computed to be zero since it is floor to int.
  // On Mac OS, division by 0 does not raise a signal. This causes negative
  // tile sizes to be computed. Prevent division by Cac==0 by early returning
  // if this happens.
  if (Car == 0)
    return {1, 1, 1};

  auto ElementSize = getMatMulAlignTypeSize(MMI);
  assert(ElementSize > 0 && "The element size of the matrix multiplication "
                            "operands should be greater than zero.");
  int Kc = (Car * FirstCacheLevelSize) /
           (MicroKernelParams.Mr * FirstCacheLevelAssociativity * ElementSize);
  double Cac =
      static_cast<double>(Kc * ElementSize * SecondCacheLevelAssociativity) /
      SecondCacheLevelSize;
  int Mc = floor((SecondCacheLevelAssociativity - 2) / Cac);
  int Nc = PollyPatternMatchingNcQuotient * MicroKernelParams.Nr;

  assert(Mc > 0 && Nc > 0 && Kc > 0 &&
         "Matrix block sizes should be  greater than zero");
  return {Mc, Nc, Kc};
}

/// Create an access relation that is specific to
///        the matrix multiplication pattern.
///
/// Create an access relation of the following form:
/// [O0, O1, O2, O3, O4, O5, O6, O7, O8] -> [OI, O5, OJ]
/// where I is @p FirstDim, J is @p SecondDim.
///
/// It can be used, for example, to create relations that helps to consequently
/// access elements of operands of a matrix multiplication after creation of
/// the BLIS micro and macro kernels.
///
/// @see ScheduleTreeOptimizer::createMicroKernel
/// @see ScheduleTreeOptimizer::createMacroKernel
///
/// Subsequently, the described access relation is applied to the range of
/// @p MapOldIndVar, that is used to map original induction variables to
/// the ones, which are produced by schedule transformations. It helps to
/// define relations using a new space and, at the same time, keep them
/// in the original one.
///
/// @param MapOldIndVar The relation, which maps original induction variables
///                     to the ones, which are produced by schedule
///                     transformations.
/// @param FirstDim, SecondDim The input dimensions that are used to define
///        the specified access relation.
/// @return The specified access relation.
isl::map getMatMulAccRel(isl::map MapOldIndVar, unsigned FirstDim,
                         unsigned SecondDim) {
  auto AccessRelSpace = isl::space(MapOldIndVar.get_ctx(), 0, 9, 3);
  auto AccessRel = isl::map::universe(AccessRelSpace);
  AccessRel = AccessRel.equate(isl::dim::in, FirstDim, isl::dim::out, 0);
  AccessRel = AccessRel.equate(isl::dim::in, 5, isl::dim::out, 1);
  AccessRel = AccessRel.equate(isl::dim::in, SecondDim, isl::dim::out, 2);
  return MapOldIndVar.apply_range(AccessRel);
}

isl::schedule_node createExtensionNode(isl::schedule_node Node,
                                       isl::map ExtensionMap) {
  auto Extension = isl::union_map(ExtensionMap);
  auto NewNode = isl::schedule_node::from_extension(Extension);
  return Node.graft_before(NewNode);
}

/// Apply the packing transformation.
///
/// The packing transformation can be described as a data-layout
/// transformation that requires to introduce a new array, copy data
/// to the array, and change memory access locations to reference the array.
/// It can be used to ensure that elements of the new array are read in-stride
/// access, aligned to cache lines boundaries, and preloaded into certain cache
/// levels.
///
/// As an example let us consider the packing of the array A that would help
/// to read its elements with in-stride access. An access to the array A
/// is represented by an access relation that has the form
/// S[i, j, k] -> A[i, k]. The scheduling function of the SCoP statement S has
/// the form S[i,j, k] -> [floor((j mod Nc) / Nr), floor((i mod Mc) / Mr),
/// k mod Kc, j mod Nr, i mod Mr].
///
/// To ensure that elements of the array A are read in-stride access, we add
/// a new array Packed_A[Mc/Mr][Kc][Mr] to the SCoP, using
/// Scop::createScopArrayInfo, change the access relation
/// S[i, j, k] -> A[i, k] to
/// S[i, j, k] -> Packed_A[floor((i mod Mc) / Mr), k mod Kc, i mod Mr], using
/// MemoryAccess::setNewAccessRelation, and copy the data to the array, using
/// the copy statement created by Scop::addScopStmt.
///
/// @param Node The schedule node to be optimized.
/// @param MapOldIndVar The relation, which maps original induction variables
///                     to the ones, which are produced by schedule
///                     transformations.
/// @param MicroParams, MacroParams Parameters of the BLIS kernel
///                                 to be taken into account.
/// @param MMI Parameters of the matrix multiplication operands.
/// @return The optimized schedule node.
static isl::schedule_node
optimizeDataLayoutMatrMulPattern(isl::schedule_node Node, isl::map MapOldIndVar,
                                 MicroKernelParamsTy MicroParams,
                                 MacroKernelParamsTy MacroParams,
                                 MatMulInfoTy &MMI) {
  auto InputDimsId = MapOldIndVar.get_tuple_id(isl::dim::in);
  auto *Stmt = static_cast<ScopStmt *>(InputDimsId.get_user());

  // Create a copy statement that corresponds to the memory access to the
  // matrix B, the second operand of the matrix multiplication.
  Node = Node.parent().parent().parent().parent().parent().parent();
  Node = isl::manage(isl_schedule_node_band_split(Node.release(), 2)).child(0);
  auto AccRel = getMatMulAccRel(MapOldIndVar, 3, 7);
  unsigned FirstDimSize = MacroParams.Nc / MicroParams.Nr;
  unsigned SecondDimSize = MacroParams.Kc;
  unsigned ThirdDimSize = MicroParams.Nr;
  auto *SAI = Stmt->getParent()->createScopArrayInfo(
      MMI.B->getElementType(), "Packed_B",
      {FirstDimSize, SecondDimSize, ThirdDimSize});
  AccRel = AccRel.set_tuple_id(isl::dim::out, SAI->getBasePtrId());
  auto OldAcc = MMI.B->getLatestAccessRelation();
  MMI.B->setNewAccessRelation(AccRel);
  auto ExtMap = MapOldIndVar.project_out(isl::dim::out, 2,
                                         MapOldIndVar.dim(isl::dim::out) - 2);
  ExtMap = ExtMap.reverse();
  ExtMap = ExtMap.fix_si(isl::dim::out, MMI.i, 0);
  auto Domain = Stmt->getDomain();

  // Restrict the domains of the copy statements to only execute when also its
  // originating statement is executed.
  auto DomainId = Domain.get_tuple_id();
  auto *NewStmt = Stmt->getParent()->addScopStmt(
      OldAcc, MMI.B->getLatestAccessRelation(), Domain);
  ExtMap = ExtMap.set_tuple_id(isl::dim::out, DomainId);
  ExtMap = ExtMap.intersect_range(Domain);
  ExtMap = ExtMap.set_tuple_id(isl::dim::out, NewStmt->getDomainId());
  Node = createExtensionNode(Node, ExtMap);

  // Create a copy statement that corresponds to the memory access
  // to the matrix A, the first operand of the matrix multiplication.
  Node = Node.child(0);
  AccRel = getMatMulAccRel(MapOldIndVar, 4, 6);
  FirstDimSize = MacroParams.Mc / MicroParams.Mr;
  ThirdDimSize = MicroParams.Mr;
  SAI = Stmt->getParent()->createScopArrayInfo(
      MMI.A->getElementType(), "Packed_A",
      {FirstDimSize, SecondDimSize, ThirdDimSize});
  AccRel = AccRel.set_tuple_id(isl::dim::out, SAI->getBasePtrId());
  OldAcc = MMI.A->getLatestAccessRelation();
  MMI.A->setNewAccessRelation(AccRel);
  ExtMap = MapOldIndVar.project_out(isl::dim::out, 3,
                                    MapOldIndVar.dim(isl::dim::out) - 3);
  ExtMap = ExtMap.reverse();
  ExtMap = ExtMap.fix_si(isl::dim::out, MMI.j, 0);
  NewStmt = Stmt->getParent()->addScopStmt(
      OldAcc, MMI.A->getLatestAccessRelation(), Domain);

  // Restrict the domains of the copy statements to only execute when also its
  // originating statement is executed.
  ExtMap = ExtMap.set_tuple_id(isl::dim::out, DomainId);
  ExtMap = ExtMap.intersect_range(Domain);
  ExtMap = ExtMap.set_tuple_id(isl::dim::out, NewStmt->getDomainId());
  Node = createExtensionNode(Node, ExtMap);
  return Node.child(0).child(0).child(0).child(0).child(0);
}

/// Get a relation mapping induction variables produced by schedule
/// transformations to the original ones.
///
/// @param Node The schedule node produced as the result of creation
///        of the BLIS kernels.
/// @param MicroKernelParams, MacroKernelParams Parameters of the BLIS kernel
///                                             to be taken into account.
/// @return  The relation mapping original induction variables to the ones
///          produced by schedule transformation.
/// @see ScheduleTreeOptimizer::createMicroKernel
/// @see ScheduleTreeOptimizer::createMacroKernel
/// @see getMacroKernelParams
isl::map
getInductionVariablesSubstitution(isl::schedule_node Node,
                                  MicroKernelParamsTy MicroKernelParams,
                                  MacroKernelParamsTy MacroKernelParams) {
  auto Child = Node.child(0);
  auto UnMapOldIndVar = Child.get_prefix_schedule_union_map();
  auto MapOldIndVar = isl::map::from_union_map(UnMapOldIndVar);
  if (MapOldIndVar.dim(isl::dim::out) > 9)
    return MapOldIndVar.project_out(isl::dim::out, 0,
                                    MapOldIndVar.dim(isl::dim::out) - 9);
  return MapOldIndVar;
}

/// Isolate a set of partial tile prefixes and unroll the isolated part.
///
/// The set should ensure that it contains only partial tile prefixes that have
/// exactly Mr x Nr iterations of the two innermost loops produced by
/// the optimization of the matrix multiplication. Mr and Nr are parameters of
/// the micro-kernel.
///
/// In case of parametric bounds, this helps to auto-vectorize the unrolled
/// innermost loops, using the SLP vectorizer.
///
/// @param Node              The schedule node to be modified.
/// @param MicroKernelParams Parameters of the micro-kernel
///                          to be taken into account.
/// @return The modified isl_schedule_node.
static isl::schedule_node
isolateAndUnrollMatMulInnerLoops(isl::schedule_node Node,
                                 struct MicroKernelParamsTy MicroKernelParams) {
  isl::schedule_node Child = Node.get_child(0);
  isl::union_map UnMapOldIndVar = Child.get_prefix_schedule_relation();
  isl::set Prefix = isl::map::from_union_map(UnMapOldIndVar).range();
  unsigned Dims = Prefix.dim(isl::dim::set);
  Prefix = Prefix.project_out(isl::dim::set, Dims - 1, 1);
  Prefix = getPartialTilePrefixes(Prefix, MicroKernelParams.Nr);
  Prefix = getPartialTilePrefixes(Prefix, MicroKernelParams.Mr);

  isl::union_set IsolateOption =
      getIsolateOptions(Prefix.add_dims(isl::dim::set, 3), 3);
  isl::ctx Ctx = Node.get_ctx();
  auto Options = IsolateOption.unite(getDimOptions(Ctx, "unroll"));
  Options = Options.unite(getUnrollIsolatedSetOptions(Ctx));
  Node = Node.band_set_ast_build_options(Options);
  Node = Node.parent().parent().parent();
  IsolateOption = getIsolateOptions(Prefix, 3);
  Options = IsolateOption.unite(getDimOptions(Ctx, "separate"));
  Node = Node.band_set_ast_build_options(Options);
  Node = Node.child(0).child(0).child(0);
  return Node;
}

/// Mark @p BasePtr with "Inter iteration alias-free" mark node.
///
/// @param Node The child of the mark node to be inserted.
/// @param BasePtr The pointer to be marked.
/// @return The modified isl_schedule_node.
static isl::schedule_node markInterIterationAliasFree(isl::schedule_node Node,
                                                      Value *BasePtr) {
  if (!BasePtr)
    return Node;

  auto Id =
      isl::id::alloc(Node.get_ctx(), "Inter iteration alias-free", BasePtr);
  return Node.insert_mark(Id).child(0);
}

/// Insert "Loop Vectorizer Disabled" mark node.
///
/// @param Node The child of the mark node to be inserted.
/// @return The modified isl_schedule_node.
static isl::schedule_node markLoopVectorizerDisabled(isl::schedule_node Node) {
  auto Id = isl::id::alloc(Node.get_ctx(), "Loop Vectorizer Disabled", nullptr);
  return Node.insert_mark(Id).child(0);
}

/// Restore the initial ordering of dimensions of the band node
///
/// In case the band node represents all the dimensions of the iteration
/// domain, recreate the band node to restore the initial ordering of the
/// dimensions.
///
/// @param Node The band node to be modified.
/// @return The modified schedule node.
static isl::schedule_node
getBandNodeWithOriginDimOrder(isl::schedule_node Node) {
  assert(isl_schedule_node_get_type(Node.get()) == isl_schedule_node_band);
  if (isl_schedule_node_get_type(Node.child(0).get()) != isl_schedule_node_leaf)
    return Node;
  auto Domain = Node.get_universe_domain();
  assert(isl_union_set_n_set(Domain.get()) == 1);
  if (Node.get_schedule_depth() != 0 ||
      (isl::set(Domain).dim(isl::dim::set) !=
       isl_schedule_node_band_n_member(Node.get())))
    return Node;
  Node = isl::manage(isl_schedule_node_delete(Node.copy()));
  auto PartialSchedulePwAff = Domain.identity_union_pw_multi_aff();
  auto PartialScheduleMultiPwAff =
      isl::multi_union_pw_aff(PartialSchedulePwAff);
  PartialScheduleMultiPwAff =
      PartialScheduleMultiPwAff.reset_tuple_id(isl::dim::set);
  return Node.insert_partial_schedule(PartialScheduleMultiPwAff);
}

isl::schedule_node
ScheduleTreeOptimizer::optimizeMatMulPattern(isl::schedule_node Node,
                                             const TargetTransformInfo *TTI,
                                             MatMulInfoTy &MMI) {
  assert(TTI && "The target transform info should be provided.");
  Node = markInterIterationAliasFree(
      Node, MMI.WriteToC->getLatestScopArrayInfo()->getBasePtr());
  int DimOutNum = isl_schedule_node_band_n_member(Node.get());
  assert(DimOutNum > 2 && "In case of the matrix multiplication the loop nest "
                          "and, consequently, the corresponding scheduling "
                          "functions have at least three dimensions.");
  Node = getBandNodeWithOriginDimOrder(Node);
  Node = permuteBandNodeDimensions(Node, MMI.i, DimOutNum - 3);
  int NewJ = MMI.j == DimOutNum - 3 ? MMI.i : MMI.j;
  int NewK = MMI.k == DimOutNum - 3 ? MMI.i : MMI.k;
  Node = permuteBandNodeDimensions(Node, NewJ, DimOutNum - 2);
  NewK = NewK == DimOutNum - 2 ? NewJ : NewK;
  Node = permuteBandNodeDimensions(Node, NewK, DimOutNum - 1);
  auto MicroKernelParams = getMicroKernelParams(TTI, MMI);
  auto MacroKernelParams = getMacroKernelParams(TTI, MicroKernelParams, MMI);
  Node = createMacroKernel(Node, MacroKernelParams);
  Node = createMicroKernel(Node, MicroKernelParams);
  if (MacroKernelParams.Mc == 1 || MacroKernelParams.Nc == 1 ||
      MacroKernelParams.Kc == 1)
    return Node;
  auto MapOldIndVar = getInductionVariablesSubstitution(Node, MicroKernelParams,
                                                        MacroKernelParams);
  if (!MapOldIndVar)
    return Node;
  Node = markLoopVectorizerDisabled(Node.parent()).child(0);
  Node = isolateAndUnrollMatMulInnerLoops(Node, MicroKernelParams);
  return optimizeDataLayoutMatrMulPattern(Node, MapOldIndVar, MicroKernelParams,
                                          MacroKernelParams, MMI);
}

bool ScheduleTreeOptimizer::isMatrMultPattern(isl::schedule_node Node,
                                              const Dependences *D,
                                              MatMulInfoTy &MMI) {
  auto PartialSchedule = isl::manage(
      isl_schedule_node_band_get_partial_schedule_union_map(Node.get()));
  Node = Node.child(0);
  auto LeafType = isl_schedule_node_get_type(Node.get());
  Node = Node.parent();
  if (LeafType != isl_schedule_node_leaf ||
      isl_schedule_node_band_n_member(Node.get()) < 3 ||
      Node.get_schedule_depth() != 0 ||
      isl_union_map_n_map(PartialSchedule.get()) != 1)
    return false;
  auto NewPartialSchedule = isl::map::from_union_map(PartialSchedule);
  if (containsMatrMult(NewPartialSchedule, D, MMI))
    return true;
  return false;
}

__isl_give isl_schedule_node *
ScheduleTreeOptimizer::optimizeBand(__isl_take isl_schedule_node *Node,
                                    void *User) {
  if (!isTileableBandNode(isl::manage_copy(Node)))
    return Node;

  const OptimizerAdditionalInfoTy *OAI =
      static_cast<const OptimizerAdditionalInfoTy *>(User);

  MatMulInfoTy MMI;
  if (PMBasedOpts && User &&
      isMatrMultPattern(isl::manage_copy(Node), OAI->D, MMI)) {
    LLVM_DEBUG(dbgs() << "The matrix multiplication pattern was detected\n");
    MatMulOpts++;
    return optimizeMatMulPattern(isl::manage(Node), OAI->TTI, MMI).release();
  }

  return standardBandOpts(isl::manage(Node), User).release();
}

isl::schedule
ScheduleTreeOptimizer::optimizeSchedule(isl::schedule Schedule,
                                        const OptimizerAdditionalInfoTy *OAI) {
  auto Root = Schedule.get_root();
  Root = optimizeScheduleNode(Root, OAI);
  return Root.get_schedule();
}

isl::schedule_node ScheduleTreeOptimizer::optimizeScheduleNode(
    isl::schedule_node Node, const OptimizerAdditionalInfoTy *OAI) {
  Node = isl::manage(isl_schedule_node_map_descendant_bottom_up(
      Node.release(), optimizeBand,
      const_cast<void *>(static_cast<const void *>(OAI))));
  return Node;
}

bool ScheduleTreeOptimizer::isProfitableSchedule(Scop &S,
                                                 isl::schedule NewSchedule) {
  // To understand if the schedule has been optimized we check if the schedule
  // has changed at all.
  // TODO: We can improve this by tracking if any necessarily beneficial
  // transformations have been performed. This can e.g. be tiling, loop
  // interchange, or ...) We can track this either at the place where the
  // transformation has been performed or, in case of automatic ILP based
  // optimizations, by comparing (yet to be defined) performance metrics
  // before/after the scheduling optimizer
  // (e.g., #stride-one accesses)
  if (S.containsExtensionNode(NewSchedule))
    return true;
  auto NewScheduleMap = NewSchedule.get_map();
  auto OldSchedule = S.getSchedule();
  assert(OldSchedule && "Only IslScheduleOptimizer can insert extension nodes "
                        "that make Scop::getSchedule() return nullptr.");
  bool changed = !OldSchedule.is_equal(NewScheduleMap);
  return changed;
}

namespace {

class IslScheduleOptimizer : public ScopPass {
public:
  static char ID;

  explicit IslScheduleOptimizer() : ScopPass(ID) {}

  ~IslScheduleOptimizer() override { isl_schedule_free(LastSchedule); }

  /// Optimize the schedule of the SCoP @p S.
  bool runOnScop(Scop &S) override;

  /// Print the new schedule for the SCoP @p S.
  void printScop(raw_ostream &OS, Scop &S) const override;

  /// Register all analyses and transformation required.
  void getAnalysisUsage(AnalysisUsage &AU) const override;

  /// Release the internal memory.
  void releaseMemory() override {
    isl_schedule_free(LastSchedule);
    LastSchedule = nullptr;
  }

private:
  isl_schedule *LastSchedule = nullptr;
};
} // namespace

char IslScheduleOptimizer::ID = 0;

/// Collect statistics for the schedule tree.
///
/// @param Schedule The schedule tree to analyze. If not a schedule tree it is
/// ignored.
/// @param Version  The version of the schedule tree that is analyzed.
///                 0 for the original schedule tree before any transformation.
///                 1 for the schedule tree after isl's rescheduling.
///                 2 for the schedule tree after optimizations are applied
///                 (tiling, pattern matching)
static void walkScheduleTreeForStatistics(isl::schedule Schedule, int Version) {
  auto Root = Schedule.get_root();
  if (!Root)
    return;

  isl_schedule_node_foreach_descendant_top_down(
      Root.get(),
      [](__isl_keep isl_schedule_node *nodeptr, void *user) -> isl_bool {
        isl::schedule_node Node = isl::manage_copy(nodeptr);
        int Version = *static_cast<int *>(user);

        switch (isl_schedule_node_get_type(Node.get())) {
        case isl_schedule_node_band: {
          NumBands[Version]++;
          if (isl_schedule_node_band_get_permutable(Node.get()) ==
              isl_bool_true)
            NumPermutable[Version]++;

          int CountMembers = isl_schedule_node_band_n_member(Node.get());
          NumBandMembers[Version] += CountMembers;
          for (int i = 0; i < CountMembers; i += 1) {
            if (Node.band_member_get_coincident(i))
              NumCoincident[Version]++;
          }
          break;
        }

        case isl_schedule_node_filter:
          NumFilters[Version]++;
          break;

        case isl_schedule_node_extension:
          NumExtension[Version]++;
          break;

        default:
          break;
        }

        return isl_bool_true;
      },
      &Version);
}

template <typename Derived, typename RetVal = void, typename... Args>
struct ScheduleTreeVisitor {
  Derived &getDerived() { return *static_cast<Derived *>(this); }
  const Derived &getDerived() const {
    return *static_cast<const Derived *>(this);
  }

  RetVal visit(const isl::schedule_node &Node, Args... args) {
    switch (isl_schedule_node_get_type(Node.get())) {
    case isl_schedule_node_domain:
      assert(isl_schedule_node_n_children(Node.get()) == 1);
      return getDerived().visitDomain(Node, args...);
    case isl_schedule_node_band:
      assert(isl_schedule_node_n_children(Node.get()) == 1);
      return getDerived().visitBand(Node, args...);
    case isl_schedule_node_sequence:
      assert(isl_schedule_node_n_children(Node.get()) >= 2);
      return getDerived().visitSequence(Node, args...);
    case isl_schedule_node_set:
      return getDerived().visitSet(Node, args...);
      assert(isl_schedule_node_n_children(Node.get()) >= 2);
    case isl_schedule_node_leaf:
      assert(isl_schedule_node_n_children(Node.get()) == 0);
      return getDerived().visitLeaf(Node, args...);
    case isl_schedule_node_mark:
      assert(isl_schedule_node_n_children(Node.get()) == 1);
      return getDerived().visitMark(Node, args...);
    default:
      llvm_unreachable("unimplemented schedule node type");
    }
  }

  RetVal visitDomain(const isl::schedule_node &Domain, Args... args) {
    return getDerived().visitOther(Domain, args...);
  }

  RetVal visitBand(const isl::schedule_node &Band, Args... args) {
    return getDerived().visitOther(Band, args...);
  }

  RetVal visitSequence(const isl::schedule_node &Sequence, Args... args) {
    return getDerived().visitOther(Sequence, args...);
  }

  RetVal visitSet(const isl::schedule_node &Set, Args... args) {
    return getDerived().visitOther(Set, args...);
  }

  RetVal visitLeaf(const isl::schedule_node &Leaf, Args... args) {
    return getDerived().visitOther(Leaf, args...);
  }

  RetVal visitMark(const isl::schedule_node &Mark, Args... args) {
    return getDerived().visitOther(Mark, args...);
  }

  RetVal visitOther(const isl::schedule_node &Other, Args... args) {
    llvm_unreachable("Unimplemented other");
  }
};

// TODO: Instead of always copying, an unmodified isl::schedule_tree could be
// returned. Unfortunately, isl keeps the access to the data structure private
// and forces users to create copies of the complete isl::schedule when
// modifiying it.
template <typename Derived, typename... Args>
struct ScheduleTreeRewriteVisitor
    : public ScheduleTreeVisitor<Derived, isl::schedule, Args...> {
	Derived &getDerived() { return *static_cast<Derived *>(this); }

  isl::schedule visitDomain(const isl::schedule_node &Domain, Args... args) {
    return  getDerived().visit(Domain.child(0), args...);
  }

  isl::schedule visitBand(const isl::schedule_node &Band, Args... args) {
    // TODO: apply band properties (conicident, permutable)
    // TODO: Reuse if not changed
    auto PartialSched =
        isl::manage(isl_schedule_node_band_get_partial_schedule(Band.get()));
    auto NewChild = getDerived().visit(Band.child(0), args...);
    return NewChild.insert_partial_schedule(PartialSched);
  }

  isl::schedule visitSequence(const isl::schedule_node &Sequence,
                              Args... args) {
    auto NumChildren = isl_schedule_node_n_children(Sequence.get());
    assert(NumChildren >= 1);
    auto Result = getDerived().visit(Sequence.child(0), args...);
    for (int i = 1; i < NumChildren; i += 1)
      Result = Result.sequence(getDerived().visit(Sequence.child(i), args...));
    return Result;
  }

  isl::schedule visitSet(const isl::schedule_node &Set, Args... args) {
    auto NumChildren = isl_schedule_node_n_children(Set.get());
    assert(NumChildren >= 1);
    auto Result = getDerived().visit(Set.child(0), args...);
    for (int i = 1; i < NumChildren; i += 1)
      Result = Result.set(getDerived().visit(Set.child(i), args...));
    return Result;
  }

  isl::schedule visitLeaf(const isl::schedule_node &Leaf, Args... args) {
    auto Dom = Leaf.get_domain();
    return isl::schedule::from_domain(Dom);
  }

  isl::schedule visitMark(const isl::schedule_node &Mark, Args... args) {
    auto TheMark = Mark.mark_get_id();
    auto NewChild = getDerived().visit(Mark.child(0), args...);
    return NewChild.get_root().get_child(0).insert_mark(TheMark).get_schedule();
  }
};

class LoopIdentification {
	Loop *ByLoop=nullptr;
	isl::id ByIslId;
	std::string ByName;
	MDNode *ByMetadata=nullptr;

public:
        Loop *getLoop() const {
			if (ByLoop)
				return ByLoop;
			if (ByIslId)
				return static_cast<Loop*> (ByIslId.get_user());
			return nullptr;
		}

		isl::id getIslId() const {
			return ByIslId;
		}

		isl::id getIslId(isl::ctx &Ctx) const {
			auto Result = ByIslId;
			if (!Result) {
				if (auto L = getLoop())
					Result = getIslLoopId(Ctx, L);
			}
			return Result;
		}

		StringRef getName() const {
			if (!ByName.empty())	
				return ByName;
			if (ByIslId)
				return ByIslId.get_name();
			StringRef Result;
			if (auto L = getLoop()) {
				auto IdVal = findStringMetadataForLoop(L, "llvm.loop.id");
				if (IdVal) 
					Result = cast<MDString>(IdVal.getValue()->get())->getString();
			}
			assert(!ByMetadata && "TODO: extract llvm.loop.id directly from Metadata");
			return Result;
		}


		MDNode *getMetadata() const {
			if (ByMetadata)
				return ByMetadata;
			if (auto L = getLoop())
				return L->getLoopID();
			return nullptr;
		}

	static LoopIdentification createFromLoop(Loop *L) {
		assert(L);
		LoopIdentification Result;
		Result.ByLoop = L;
		Result.ByMetadata = L->getLoopID();
#if 0
		if (Result.ByMetadata) {
		 	auto IdVal = findStringMetadataForLoop(L, "llvm.loop.id");
			if (IdVal) 
				Result.ByName = cast<MDString>(IdVal.getValue()->get())->getString();
          }
#endif
		return Result;
	}

	static LoopIdentification createFromIslId(isl::id Id) {
		assert(!Id.is_null());
		LoopIdentification Result;
		Result.ByIslId = Id;
		Result.ByLoop = static_cast<Loop*>( Id.get_user());
		Result.ByName = Id.get_name();
		Result.ByMetadata = Result.ByLoop->getLoopID();
#if 0
		if (Result.ByMetadata) {
		 	auto IdVal = findStringMetadataForLoop(Result.ByLoop, "llvm.loop.id");
			if (IdVal) 
				Result.ByName = cast<MDString>(IdVal.getValue())->getString();
          }
#endif
		return Result;
	}

		static LoopIdentification createFromMetadata(MDNode *Metadata) {
		assert(Metadata);

		LoopIdentification Result;
		Result.ByMetadata = Metadata;
		return Result;
	}

	static LoopIdentification createFromName(StringRef Name) {
		assert(!Name.empty());

		LoopIdentification Result;
		Result.ByName = Name;
		return Result;
	}
};


static bool operator==(const LoopIdentification &LHS, const LoopIdentification &RHS) {
	auto LHSLoop = LHS.getLoop();
	auto RHSLoop = RHS.getLoop();

	if (LHSLoop && RHSLoop)
		return LHSLoop == RHSLoop;

	auto LHSIslId = LHS.getIslId();
	auto RHSIslId =RHS.getIslId();
	isl::ctx Ctx(nullptr);
	if (LHSIslId)
		Ctx = LHSIslId.get_ctx();
	if (RHSIslId)
		Ctx = RHSIslId.get_ctx();
	if (Ctx.get()) {
		LHSIslId = LHS.getIslId(Ctx);
		RHSIslId = RHS.getIslId(Ctx);
		if (LHSIslId && RHSIslId)
			return LHSIslId.get() == RHSIslId.get();
	}

	auto LHSMetadata = LHS.getMetadata();
	auto RHSMetadata = RHS.getMetadata();
	if (LHSMetadata &&RHSMetadata )
		return LHSMetadata == RHSMetadata;

	auto LHSName = LHS.getName();
	auto RHSName = RHS.getName();
	if (!LHSName.empty() && !RHSName.empty())
		return LHSName == RHSName;

	llvm_unreachable("No means to determine whether both define the same loop");
}

class LoopNestTransformation {
public:
  isl::schedule Sched;

  isl::union_map ValidityConstraints;
  isl::union_map TransformativeConstraints;

  StringMap<int> LoopNames;
};

static isl::schedule applyLoopReversal(isl::schedule_node BandToReverse) {
  struct LoopReversalVisitor
      : public ScheduleTreeRewriteVisitor<LoopReversalVisitor> {
    typedef ScheduleTreeRewriteVisitor<LoopReversalVisitor> Super;
    isl::schedule_node ReverseBand;
    bool Applied = false;
    LoopReversalVisitor(isl::schedule_node ReverseBand)
        : ReverseBand(ReverseBand) {}

    isl::schedule visitBand(const isl::schedule_node &OrigBand) {
      if (!OrigBand.is_equal(ReverseBand))
        return Super::visitBand(OrigBand);

      assert(!Applied && "Should apply at most once");
      Applied = true;

      auto PartialSched = isl::manage(
          isl_schedule_node_band_get_partial_schedule(OrigBand.get()));
      assert(PartialSched.dim(isl::dim::out) == 1);
      auto ParentParentBand = OrigBand.parent();

      auto OrigChild = OrigBand.get_child(0);
      assert(OrigChild);

      auto NewChild = visit(OrigChild);
      assert(NewChild);

      auto MPA = PartialSched.get_union_pw_aff(0);
      auto Neg = MPA.neg();

      return NewChild.insert_partial_schedule(Neg);
    }
  } Visitor(BandToReverse);
  auto Result = Visitor.visit(BandToReverse.get_schedule().get_root());
  assert(Visitor.Applied && "Band must be in schedule tree");
  return Result;
}

static LoopNestTransformation
applyLoopReversal(const LoopNestTransformation &Trans,
                  isl::schedule_node BandToReverse, bool CheckValidity,
                  bool ApplyOnSchedule, bool AddTransformativeConstraints,
                  bool RemoveContradictingConstraints) {
  if (CheckValidity) {
  }

  LoopNestTransformation Result = Trans;

  if (ApplyOnSchedule) {
    Result.Sched = applyLoopReversal(BandToReverse);
  }

  if (RemoveContradictingConstraints) {
  }

  if (AddTransformativeConstraints) {
  }

  return Result;
}

static Loop *getBandLoop(isl::schedule_node Band) {
  assert(isl_schedule_node_get_type(Band.get()) == isl_schedule_node_band);
  assert(isl_schedule_node_band_n_member(Band.get()) == 1 &&
         "The schedule tree must not been transformed yet");

  auto UDom = Band.get_universe_domain();

  Loop *Result = nullptr;
  UDom.foreach_set([&Result](isl::set StmtDom) -> isl::stat {
    auto Stmt = static_cast<ScopStmt *>(StmtDom.get_tuple_id().get_user());

    auto Loop = Stmt->getLoopForDimension(0); // ?? Need relative depth?
    assert(Loop);
    assert(!Result || Loop == Result);
    Result = Loop;

    return isl::stat::ok;
  });
  assert(Result);
  return Result;
}

static isl::schedule applyReverseLoopHint(isl::schedule OrigBand, Loop *Loop,
                                          bool &Changed) {
  auto ReverseMD = findStringMetadataForLoop(Loop, "llvm.loop.reverse.enable");
  if (!ReverseMD)
    return OrigBand;

  auto *Op = *ReverseMD;
  assert(Op && mdconst::hasa<ConstantInt>(*Op) && "invalid metadata");
  bool EnableReverse = !mdconst::extract<ConstantInt>(*Op)->isZero();
  if (!EnableReverse)
    return OrigBand;

  LLVM_DEBUG(dbgs() << "Applying manual loop reversal\n");
  Changed = true;
  return applyLoopReversal(OrigBand.get_root());
}

static isl::schedule applyTransformationHints(isl::schedule Band, Loop *Loop,
                                              bool &Changed) {
  return applyReverseLoopHint(Band, Loop, Changed);
}

static isl::schedule
walkScheduleTreeForTransformationHints(isl::schedule_node Parent,
                                       Loop *ParentLoop, bool &Changed) {
  struct HintTransformator
      : public ScheduleTreeRewriteVisitor<HintTransformator> {
    typedef ScheduleTreeRewriteVisitor<HintTransformator> Super;
    Loop *ParentLoop;
    bool &Changed;
    HintTransformator(Loop *ParentLoop, bool &Changed)
        : ParentLoop(ParentLoop), Changed(Changed) {}

    isl::schedule visitBand(const isl::schedule_node &OrigBand) {
      auto L = getBandLoop(OrigBand);
      assert(ParentLoop == L->getParentLoop());

      // I would prefer to pass ParentLoop as a parameter, but the visitor
      // pattern does not allow this.
      std::swap(ParentLoop, L);
      // FIXME: This makes a copy of the subtree that we might not need if no
      // transformation is applied
      auto BandSchedule = Super::visitBand(OrigBand);
      std::swap(ParentLoop, L);

      return applyTransformationHints(BandSchedule, L, Changed);
    }
  } Transformator(ParentLoop, Changed);

  auto Result = Transformator.visit(Parent);
  return Result;
}

static Loop *getSurroundingLoop(Scop &S) {
  auto EntryBB = S.getEntry();
  auto L = S.getLI()->getLoopFor(EntryBB);
  while (L && S.contains(L))
    L = L->getParentLoop();
  return L;
}

static isl::schedule
walkScheduleTreeForNamedLoops(const isl::schedule_node &Node,
                              Loop *ParentLoop) {
  struct NameMarker : public ScheduleTreeRewriteVisitor<NameMarker, Loop *> {
    typedef ScheduleTreeRewriteVisitor<NameMarker, Loop *> Super;

    isl::schedule visitBand(const isl::schedule_node &OrigBand,
                            Loop *ParentLoop) {
      auto L = getBandLoop(OrigBand);
      assert(ParentLoop == L->getParentLoop() &&
             "Loop nest must be the original");

      auto BandSchedule = Super::visitBand(OrigBand, L);

    //  auto LoopId = L->getLoopID();
     // auto LoopName = findStringMetadataForLoop(L, "llvm.loop.id");

      /// FIXME: is this id sufficient?
      isl::id id = getIslLoopId(OrigBand.get_ctx(), L);

      auto Marked = BandSchedule.get_root().get_child(0).insert_mark(id);
		  
		 // isl::manage(isl_schedule_node_insert_mark( BandSchedule.get_root().get_child(0).release(), id.copy()));

      return Marked.get_schedule();
    }
  } Transformator;

  auto Result = Transformator.visit(Node, ParentLoop);
  return Result;
}

static isl::schedule annotateBands(Scop &S, isl::schedule Sched) {
  LLVM_DEBUG(dbgs() << "Mark named loops...\n");

  auto Root = Sched.get_root();
  // Root.insert_mark

  auto OuterL = getLoopSurroundingScop(S, *S.getLI());

  return walkScheduleTreeForNamedLoops(Root, OuterL);
  // return Root.get_schedule();
}

static bool applyTransformationHints(Scop &S, isl::schedule &Sched,
                                     isl::schedule_constraints &SC) {
  bool Changed = false;

  LLVM_DEBUG(dbgs() << "Looking for loop transformation metadata...\n");

  auto OuterL = getSurroundingLoop(S);
  auto Result =
      walkScheduleTreeForTransformationHints(Sched.get_root(), OuterL, Changed);
  if (Changed) {
    LLVM_DEBUG(dbgs() << "At least one manual loop transformation applied\n");
    Sched = Result;
  } else {
    LLVM_DEBUG(dbgs() << "No loop transformation applied\n");
  }

  return Changed;
}

static isl::stat
foreachTopdown(const isl::schedule Sched,
               const std::function<isl::boolean(isl::schedule_node)> &Func) {
  auto Result = isl_schedule_foreach_schedule_node_top_down(
      Sched.get(),
      [](__isl_keep isl_schedule_node *nodeptr, void *user) -> isl_bool {
        isl::schedule_node Node = isl::manage_copy(nodeptr);
        auto &Func = *static_cast<
            const std::function<isl::boolean(isl::schedule_node)> *>(user);
        auto Result = Func(std::move(Node));

        // FIXME: No direct access to isl::boolean's val.
        if (Result.is_true())
          return isl_bool_true;
        if (Result.is_false())
          return isl_bool_false;
        return isl_bool_error;
      },
      (void *)&Func);
  return isl::stat(Result); // FIXME: No isl::manage(isl_stat)
}

static isl::schedule_node findBand(const isl::schedule Sched, StringRef Name) {
  isl::schedule_node Result;
  foreachTopdown(
      Sched, [Name, &Result](isl::schedule_node Node) -> isl::boolean {
        if (isl_schedule_node_get_type(Node.get()) != isl_schedule_node_mark)
          return true;

        auto MarkId = Node.mark_get_id();
        if (MarkId.get_name() == Name) {
          auto NewResult = Node.get_child(0);
          assert(!Result || (Result.get() == NewResult.get()));
          Result = NewResult;
          return isl::boolean(); // abort();
        }

        return true;
      });
  return Result;
}


static bool isSameLoopId(isl::id LHS, isl::id RHS) {
 if (LHS.get() == RHS.get()) return true;
 assert (LHS.get_user() != RHS.get_user());
 return false;
}


static isl::schedule_node findBand(const isl::schedule Sched, isl::id Name) {
  isl::schedule_node Result;
  foreachTopdown(
      Sched, [Name, &Result](isl::schedule_node Node) -> isl::boolean {
        if (isl_schedule_node_get_type(Node.get()) != isl_schedule_node_mark)
          return true;

        auto MarkId = Node.mark_get_id();
        if (isSameLoopId(MarkId, Name)) {
          auto NewResult = Node.get_child(0);
          assert(!Result || (Result.get() == NewResult.get()));
          Result = NewResult;
          return isl::boolean(); // abort();
        }

        return true;
      });
  return Result;
}


static bool isSameLoopId(isl::id LHS, MDNode * RHS) {
	auto L = static_cast<Loop*>(LHS.get_user());
	return L->getLoopID() == RHS;
}

static isl::schedule_node findBand(const isl::schedule Sched, MDNode *LoopId) {
  isl::schedule_node Result;
  foreachTopdown(
      Sched, [LoopId, &Result](isl::schedule_node Node) -> isl::boolean {
        if (isl_schedule_node_get_type(Node.get()) != isl_schedule_node_mark)
          return true;

        auto MarkId = Node.mark_get_id();
        if (isSameLoopId(MarkId, LoopId) ) {
          auto NewResult = Node.get_child(0);
          assert(!Result || (Result.get() == NewResult.get()));
          Result = NewResult;
          return isl::boolean(); // abort();
        }

        return true;
      });
  return Result;
}

static isl::schedule_node findBand(const isl::schedule Sched, LoopIdentification LoopId) {
  isl::schedule_node Result;
  foreachTopdown(
      Sched, [LoopId, &Result](isl::schedule_node Node) -> isl::boolean {
        if (isl_schedule_node_get_type(Node.get()) != isl_schedule_node_mark)
          return true;

        auto MarkId = Node.mark_get_id();
		auto MarkLoopId = LoopIdentification::createFromIslId(MarkId);
        if (MarkLoopId == LoopId) {
          auto NewResult = Node.get_child(0);
          assert(!Result || (Result.get() == NewResult.get()));
          Result = NewResult;
          return isl::boolean(); // abort();
        }

        return true;
      });
  return Result;
}



static void applyLoopReversal(isl::schedule &Sched, StringRef ApplyOn) {
  // TODO: Can do in a single traversal
  // TODO: Remove mark?
  auto Band = findBand(Sched, ApplyOn);
  Sched = applyLoopReversal(Band);
}

static void applyLoopReversal(isl::schedule &Sched, isl::id ApplyOn) {
  // TODO: Can do in a single traversal
  // TODO: Remove mark?
  auto Band = findBand(Sched, ApplyOn);
  Sched = applyLoopReversal(Band);
}


static void applyLoopReversal(isl::schedule &Sched, MDNode *ApplyOn) {
  // TODO: Can do in a single traversal
  // TODO: Remove mark?
  auto Band = findBand(Sched, ApplyOn);
  Sched = applyLoopReversal(Band);
}


static isl::schedule_node ignoreMarkChild(isl::schedule_node Node) {
	assert(Node);
	while (isl_schedule_node_get_type(Node.get()) == isl_schedule_node_mark) {
		assert(Node.n_children() ==1);
		Node = Node.get_child(0);
	}
	return Node;
}

static isl::schedule_node ignoreMarkParent(isl::schedule_node Node) {
	assert(Node);
	while (isl_schedule_node_get_type(Node.get()) == isl_schedule_node_mark) {
		Node = Node.parent();
	}
	return Node;
}

static isl::schedule_node moveToBandMark(isl::schedule_node Band) {
	if (isl_schedule_node_get_type(Band.get()) != isl_schedule_node_band)
		return Band;
	while (true) {
		auto Parent = Band.parent();
		assert(Parent);
		if (isl_schedule_node_get_type(Parent.get()) != isl_schedule_node_mark)
			break;
		Band = Parent;
	}
	return Band;
}

static isl::schedule_node collapseBands(isl::schedule_node FirstBand, int NumBands) {
	assert(NumBands >= 2);
	auto Ctx = FirstBand.get_ctx();
	SmallVector<isl::multi_union_pw_aff,4> PartialMultiSchedules;
	SmallVector<isl::union_pw_aff,4> PartialSchedules;
	isl::multi_union_pw_aff CombinedSchedule;

	FirstBand = moveToBandMark(FirstBand);

	int CollapsedBands = 0;
	int CollapsedLoops = 0;
	// assert(isl_schedule_node_get_type(FirstBand.get()) == isl_schedule_node_band);
	auto Band = FirstBand;

	while (CollapsedBands < NumBands) {
		while (isl_schedule_node_get_type(Band.get()) == isl_schedule_node_mark)
			Band = isl::manage( isl_schedule_node_delete(Band.release()));
		assert(isl_schedule_node_get_type(Band.get()) == isl_schedule_node_band);

		auto X = isl::manage(isl_schedule_node_band_get_partial_schedule(Band.get()));
		PartialMultiSchedules.push_back(X);

		if (CombinedSchedule) {
		CombinedSchedule =	CombinedSchedule.flat_range_product(X);
                } else {
                  CombinedSchedule = X;
                }
            
		auto NumDims = X.dim(isl::dim::out);
		for (unsigned i =0; i < NumDims; i+=1) {
			auto Y = X.get_union_pw_aff(0);
			PartialSchedules.push_back(Y);
			CollapsedLoops += 1;
    }

		CollapsedBands+=1;

		Band = isl::manage( isl_schedule_node_delete(Band.release()));
	}

	//auto DomainSpace = PartialSchedules[0].get_space();
	//auto RangeSpace = isl::space(Ctx, 0, PartialSchedules.size());
	//auto Space = DomainSpace.map_from_domain_and_range(RangeSpace);

	Band = Band.insert_partial_schedule(CombinedSchedule);

	return Band;
}

// TODO: Assign names to separated bands
static isl::schedule_node separateBand(isl::schedule_node Band) {
	auto PartialSched = isl::manage(isl_schedule_node_band_get_partial_schedule(Band.get()));
	auto NumDims = PartialSched.dim(isl::dim::out);

	Band = isl::manage( isl_schedule_node_delete(Band.release()));

	for (unsigned i = 0; i < NumDims;i+=1) {
		auto LoopSched = PartialSched.get_union_pw_aff(i);
		Band = Band.insert_partial_schedule(LoopSched);
	}
	return Band;
}


// TODO: Use ScheduleTreeOptimizer::tileNode
static isl::schedule_node tileBand(isl::schedule_node BandToTile) {
		  auto Ctx = BandToTile.get_ctx();

	 auto Space =isl::manage(isl_schedule_node_band_get_space(BandToTile.get()));
	 auto Dims = Space.dim(isl::dim::set);
	 auto Sizes = isl::multi_val::zero(Space);
  for (unsigned i = 0; i < Dims; i+=1) {
    auto tileSize = 32;
    Sizes = Sizes.set_val(i, isl::val(Ctx, tileSize));
  }

		auto Result =  isl::manage(  isl_schedule_node_band_tile(BandToTile.release(), Sizes.release()));
		return Result;
}



static void applyLoopTiling(isl::schedule &Sched, ArrayRef<LoopIdentification> TheLoops) {
	SmallVector<isl::schedule_node , 4> Bands;
	Bands.reserve(TheLoops.size());
	for (auto TheLoop : TheLoops) {
		auto TheBand = findBand(Sched, TheLoop);
		assert(TheBand);
		Bands.push_back(TheBand);
	}

	auto TheBand = collapseBands(Bands[0], Bands.size());
	TheBand = tileBand(TheBand);

	auto OuterBand = TheBand;
	auto InnerBand = TheBand.get_child(0);

	InnerBand = separateBand(InnerBand);
	OuterBand = InnerBand.parent();
	OuterBand =  separateBand(OuterBand);

	Sched = OuterBand.get_schedule();
}

static isl::schedule applyManualTransformations(Scop &S, isl::schedule Sched, isl::schedule_constraints &SC) {
  auto &F = S.getFunction();
  bool Changed = false;

  auto MD = F.getMetadata("looptransform");
  for (auto &Op : MD->operands()) {
    auto Opdata = Op.get();
    auto OpMD = cast<MDNode>(Opdata);
    auto Which = OpMD->getOperand(0).get();
    auto WhichStr = cast<MDString>(Which)->getString();
    if (WhichStr == "llvm.loop.reverse") {
	  auto ApplyOnArg = OpMD->getOperand(1).get();

	  	  // TODO: Either templated version of applyLoopReversal or generalized method to get the isl::id of either a loop name or MDNode
	  if (auto MDApplyOn = dyn_cast<MDString>(ApplyOnArg)) {
		 applyLoopReversal(Sched, MDApplyOn->getString());
	  } else {
		  auto MDNodeApplyOn = cast<MDNode>(ApplyOnArg) ;
		  applyLoopReversal(Sched, MDNodeApplyOn);
	  }

	  Changed=true;
    continue;
	} 
	
	if (WhichStr == "llvm.loop.tile") {
		SmallVector<LoopIdentification,4> TiledLoops;
		auto ApplyOnArg = cast<MDNode> (OpMD->getOperand(1).get());
		for (auto &X : ApplyOnArg->operands() ) {
			auto TheMetadata = X.get();
				  if (auto MDApplyOn = dyn_cast<MDString>(TheMetadata)) {
		 TiledLoops.push_back( LoopIdentification::createFromName( MDApplyOn->getString()));
	  } else {
		  auto MDNodeApplyOn = cast<MDNode>(TheMetadata) ;
		  TiledLoops.push_back( LoopIdentification::createFromMetadata( MDNodeApplyOn));
	  }
		}


		applyLoopTiling(Sched, TiledLoops);

		Changed = true;
		continue;
	}

	llvm_unreachable("unknown loop transformation");
  }
  return Sched;
}

bool IslScheduleOptimizer::runOnScop(Scop &S) {
  // Skip SCoPs in case they're already optimised by PPCGCodeGeneration
  if (S.isToBeSkipped())
    return false;

  // Skip empty SCoPs but still allow code generation as it will delete the
  // loops present but not needed.
  if (S.getSize() == 0) {
    S.markAsOptimized();
    return false;
  }

  const Dependences &D =
      getAnalysis<DependenceInfo>().getDependences(Dependences::AL_Statement);

  if (D.getSharedIslCtx() != S.getSharedIslCtx()) {
    LLVM_DEBUG(dbgs() << "DependenceInfo for another SCoP/isl_ctx\n");
    return false;
  }

  if (!D.hasValidDependences())
    return false;

  isl_schedule_free(LastSchedule);
  LastSchedule = nullptr;

  // Build input data.
  int ValidityKinds =
      Dependences::TYPE_RAW | Dependences::TYPE_WAR | Dependences::TYPE_WAW;
  int ProximityKinds;

  if (OptimizeDeps == "all")
    ProximityKinds =
        Dependences::TYPE_RAW | Dependences::TYPE_WAR | Dependences::TYPE_WAW;
  else if (OptimizeDeps == "raw")
    ProximityKinds = Dependences::TYPE_RAW;
  else {
    errs() << "Do not know how to optimize for '" << OptimizeDeps << "'"
           << " Falling back to optimizing all dependences.\n";
    ProximityKinds =
        Dependences::TYPE_RAW | Dependences::TYPE_WAR | Dependences::TYPE_WAW;
  }

  isl::union_set Domain = S.getDomains();

  if (!Domain)
    return false;

  ScopsProcessed++;
  walkScheduleTreeForStatistics(S.getScheduleTree(), 0);

  isl::union_map Validity = isl::manage(D.getDependences(ValidityKinds));
  isl::union_map Proximity = isl::manage(D.getDependences(ProximityKinds));

  // Simplify the dependences by removing the constraints introduced by the
  // domains. This can speed up the scheduling time significantly, as large
  // constant coefficients will be removed from the dependences. The
  // introduction of some additional dependences reduces the possible
  // transformations, but in most cases, such transformation do not seem to be
  // interesting anyway. In some cases this option may stop the scheduler to
  // find any schedule.
  if (SimplifyDeps == "yes") {
    Validity = Validity.gist_domain(Domain);
    Validity = Validity.gist_range(Domain);
    Proximity = Proximity.gist_domain(Domain);
    Proximity = Proximity.gist_range(Domain);
  } else if (SimplifyDeps != "no") {
    errs() << "warning: Option -polly-opt-simplify-deps should either be 'yes' "
              "or 'no'. Falling back to default: 'yes'\n";
  }

  LLVM_DEBUG(dbgs() << "\n\nCompute schedule from: ");
  LLVM_DEBUG(dbgs() << "Domain := " << Domain << ";\n");
  LLVM_DEBUG(dbgs() << "Proximity := " << Proximity << ";\n");
  LLVM_DEBUG(dbgs() << "Validity := " << Validity << ";\n");

  unsigned IslSerializeSCCs;

  if (FusionStrategy == "max") {
    IslSerializeSCCs = 0;
  } else if (FusionStrategy == "min") {
    IslSerializeSCCs = 1;
  } else {
    errs() << "warning: Unknown fusion strategy. Falling back to maximal "
              "fusion.\n";
    IslSerializeSCCs = 0;
  }

  int IslMaximizeBands;

  if (MaximizeBandDepth == "yes") {
    IslMaximizeBands = 1;
  } else if (MaximizeBandDepth == "no") {
    IslMaximizeBands = 0;
  } else {
    errs() << "warning: Option -polly-opt-maximize-bands should either be 'yes'"
              " or 'no'. Falling back to default: 'yes'\n";
    IslMaximizeBands = 1;
  }

  int IslOuterCoincidence;

  if (OuterCoincidence == "yes") {
    IslOuterCoincidence = 1;
  } else if (OuterCoincidence == "no") {
    IslOuterCoincidence = 0;
  } else {
    errs() << "warning: Option -polly-opt-outer-coincidence should either be "
              "'yes' or 'no'. Falling back to default: 'no'\n";
    IslOuterCoincidence = 0;
  }

  isl_ctx *Ctx = S.getIslCtx().get();

  isl_options_set_schedule_outer_coincidence(Ctx, IslOuterCoincidence);
  isl_options_set_schedule_serialize_sccs(Ctx, IslSerializeSCCs);
  isl_options_set_schedule_maximize_band_depth(Ctx, IslMaximizeBands);
  isl_options_set_schedule_max_constant_term(Ctx, MaxConstantTerm);
  isl_options_set_schedule_max_coefficient(Ctx, MaxCoefficient);
  isl_options_set_tile_scale_tile_loops(Ctx, 0);

  auto OnErrorStatus = isl_options_get_on_error(Ctx);

  auto SC = isl::schedule_constraints::on_domain(Domain);
  SC = SC.set_proximity(Proximity);
  SC = SC.set_validity(Validity);
  SC = SC.set_coincidence(Validity);

  auto ManualSchedule = S.getScheduleTree();
  auto AnnotatedSchedule = ManualSchedule;// annotateBands(S, ManualSchedule);

  auto ManuallyTransformed = applyManualTransformations(S, AnnotatedSchedule, SC);
  if (AnnotatedSchedule.plain_is_equal(ManuallyTransformed))
	  ManuallyTransformed = nullptr;

  isl::schedule Schedule;
  if (ManuallyTransformed) {
    Schedule = ManuallyTransformed;
  } else {
    isl_options_set_on_error(Ctx, ISL_ON_ERROR_CONTINUE);
    Schedule = SC.compute_schedule();
    isl_options_set_on_error(Ctx, OnErrorStatus);
  }

  // In cases the scheduler is not able to optimize the code, we just do not
  // touch the schedule.
  if (!Schedule)
    return false;

  ScopsRescheduled++;

  LLVM_DEBUG({
    auto *P = isl_printer_to_str(Ctx);
    P = isl_printer_set_yaml_style(P, ISL_YAML_STYLE_BLOCK);
    P = isl_printer_print_schedule(P, Schedule.get());
    auto *str = isl_printer_get_str(P);
    dbgs() << "NewScheduleTree: \n" << str << "\n";
    free(str);
    isl_printer_free(P);
  });

  isl::schedule NewSchedule;

  if (ManuallyTransformed) {
	  NewSchedule = Schedule;
  } else {
    Function &F = S.getFunction();
	 auto *TTI = &getAnalysis<TargetTransformInfoWrapperPass>().getTTI(F);
	  const OptimizerAdditionalInfoTy OAI = {TTI, const_cast<Dependences *>(&D)};
	   NewSchedule = ScheduleTreeOptimizer::optimizeSchedule(Schedule, &OAI);
  }

  walkScheduleTreeForStatistics(NewSchedule, 2);

  if (!ScheduleTreeOptimizer::isProfitableSchedule(S, NewSchedule))
    return false;

  auto ScopStats = S.getStatistics();
  ScopsOptimized++;
  NumAffineLoopsOptimized += ScopStats.NumAffineLoops;
  NumBoxedLoopsOptimized += ScopStats.NumBoxedLoops;

  S.setScheduleTree(NewSchedule);
  S.markAsOptimized();

  if (OptimizedScops)
    errs() << S;

  return false;
}

void IslScheduleOptimizer::printScop(raw_ostream &OS, Scop &) const {
  isl_printer *p;
  char *ScheduleStr;

  OS << "Calculated schedule:\n";

  if (!LastSchedule) {
    OS << "n/a\n";
    return;
  }

  p = isl_printer_to_str(isl_schedule_get_ctx(LastSchedule));
  p = isl_printer_print_schedule(p, LastSchedule);
  ScheduleStr = isl_printer_get_str(p);
  isl_printer_free(p);

  OS << ScheduleStr << "\n";
}

void IslScheduleOptimizer::getAnalysisUsage(AnalysisUsage &AU) const {
  ScopPass::getAnalysisUsage(AU);
  AU.addRequired<DependenceInfo>();
  AU.addRequired<TargetTransformInfoWrapperPass>();

  AU.addPreserved<DependenceInfo>();
}

Pass *polly::createIslScheduleOptimizerPass() {
  return new IslScheduleOptimizer();
}

INITIALIZE_PASS_BEGIN(IslScheduleOptimizer, "polly-opt-isl",
                      "Polly - Optimize schedule of SCoP", false, false);
INITIALIZE_PASS_DEPENDENCY(DependenceInfo);
INITIALIZE_PASS_DEPENDENCY(ScopInfoRegionPass);
INITIALIZE_PASS_DEPENDENCY(TargetTransformInfoWrapperPass);
INITIALIZE_PASS_END(IslScheduleOptimizer, "polly-opt-isl",
                    "Polly - Optimize schedule of SCoP", false, false)
