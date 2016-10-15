//===- DeLICMTest.cpp ----------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "polly/DeLICM.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/LLVMContext.h"
#include "gtest/gtest.h"
#include <isl/map.h>
#include <isl/set.h>
#include <isl/stream.h>
#include <isl/union_map.h>
#include <isl/union_set.h>
#include <memory>

using namespace llvm;
using namespace polly;

/// Loop-like control structure to run body for true and false if passed indef.
///
/// Takes an int variable that can be either 0 (false), 1 (true), or -1 (indef).
/// It then shadows that variable with a new variable of type bool.
///
///  - If the int variable has the value of 0, the body is executed with the
///  bool variable set to false.
/// - If the int variable has the value of 1, the body is executed with the bool
/// variable set to true.
/// - If the int variable has the value of -1, the body is executed twice: once
/// with the bool variable set to false and a second time with true.
///
/// For use in tests where the value of a boolean variable should not change the
/// result, such that both settings are tested at once.
#define BOOL_FOR(VAR)                                                          \
  for (int VAR##_iter = (VAR == indef) ? 0 : VAR;                              \
       VAR##_iter <= ((VAR == indef) ? 1 : VAR); VAR##_iter += 1)              \
    for (bool VAR = VAR##_iter, VAR##_repeat = true; VAR##_repeat;             \
         VAR##_repeat = false)

#define indef (-1)

namespace {
bool checkComputeReachingDefinition(const char *ScheduleStr,
                                    const char *DefsStr, int IncludeDef,
                                    int IncludeRedef, const char *ExpectedStr) {
  BOOL_FOR(IncludeDef) BOOL_FOR(IncludeRedef) {
    std::unique_ptr<isl_ctx, decltype(&isl_ctx_free)> Ctx(isl_ctx_alloc(),
                                                          &isl_ctx_free);

    auto Schedule = give(isl_union_map_read_from_str(Ctx.get(), ScheduleStr));
    auto Defs = give(isl_union_map_read_from_str(Ctx.get(), DefsStr));
    auto Expected = give(isl_union_map_read_from_str(Ctx.get(), ExpectedStr));

    auto Result =
        computeReachingDefinition(Schedule, Defs, IncludeDef, IncludeRedef);

    auto Success = isl_union_map_is_equal(Result.keep(), Expected.keep());
    if (Success != isl_bool_true)
      return false;
  }

  return true;
}

TEST(DeLICM, ReachingDefinitionZone) {
  EXPECT_FALSE(computeReachingDefinition(nullptr, nullptr, false, false));

  EXPECT_TRUE(checkComputeReachingDefinition(
      "{ Dom[] -> [0] }", "{ Dom[] -> Elt[] }", true, indef,
      "{ [Elt[] -> [i]] -> Dom[] : 0 <= i }"));
  EXPECT_TRUE(checkComputeReachingDefinition(
      "{ Dom[] -> [0] }", "{ Dom[] -> Elt[] }", false, indef,
      "{ [Elt[] -> [i]] -> Dom[] : 0 < i }"));

  EXPECT_TRUE(checkComputeReachingDefinition(
      "{ Dom1[] -> [0]; Dom2[] -> [10] }",
      "{ Dom1[] -> Elt[]; Dom2[] -> Elt[] }", true, false,
      "{ [Elt[] -> [i]] -> Dom1[] : 0 <= i < 10; [Elt[] -> [i]] -> Dom2[] : 10 "
      "<= i }"));
  EXPECT_TRUE(checkComputeReachingDefinition(
      "{ Dom1[] -> [0]; Dom2[] -> [10] }",
      "{ Dom1[] -> Elt[]; Dom2[] -> Elt[] }", false, false,
      "{ [Elt[] -> [i]] -> Dom1[] : 0 < i < 10; [Elt[] -> [i]] -> Dom2[] : 10 "
      "< i }"));
  EXPECT_TRUE(
      checkComputeReachingDefinition("{ Dom1[] -> [0]; Dom2[] -> [10] }",
                                     "{ Dom1[] -> Elt[]; Dom2[] -> Elt[] }",
                                     false, true, "{ [Elt[] -> [i]] -> Dom1[] "
                                                  ": 0 < i <= 10; [Elt[] -> "
                                                  "[i]] -> Dom2[] : 10 < i }"));
  EXPECT_TRUE(
      checkComputeReachingDefinition("{ Dom1[] -> [0]; Dom2[] -> [10] }",
                                     "{ Dom1[] -> Elt[]; Dom2[] -> Elt[] }",
                                     true, true, "{ [Elt[] -> [i]] -> Dom1[] "
                                                 ": 0 <= i <= 10; [Elt[] -> "
                                                 "[i]] -> Dom2[] : 10 <= i }"));

  EXPECT_TRUE(checkComputeReachingDefinition(
      "{ Dom1[] -> [0]; Dom2[] -> [10] }",
      "{ Dom1[] -> Elt1[]; Dom2[] -> Elt2[] }", true, indef,
      "{ [Elt1[] -> [i]] -> Dom1[] : 0 <= i; "
      "[Elt2[] -> [i]] -> Dom2[] : 10 <= i }"));

  EXPECT_TRUE(checkComputeReachingDefinition(
      "{ Dom[i] -> [i] }", "{ Dom[i] -> Elt[]; Dom2[] -> Elt[] }", true, false,
      "{ [Elt[] -> [i]] -> Dom[i] }"));

  EXPECT_TRUE(
      checkComputeReachingDefinition("{ Dom[1] -> [0]; Dom[2] -> [10] }",
                                     "{ Dom[1] -> Elt[]; Dom[2] -> Elt[] }",
                                     false, true, "{ [Elt[] -> [i]] -> Dom[1] "
                                                  ": 0 < i <= 10; [Elt[] -> "
                                                  "[i]] -> Dom[2] : 10 < i }"));

  EXPECT_TRUE(checkComputeReachingDefinition(
      "{ Stmt_reduction_for[i] -> [3i] : 0 <= i <= 4 }",
      "{ Stmt_reduction_for[i] -> Elt[] : 0 <= i <= 4 }", false, true,
      "{ [Elt[] -> [i]] -> Stmt_reduction_for[0] : 0 < i <= 3; [Elt[] -> [i]] "
      "-> Stmt_reduction_for[1] : 3 < i <= 6; [Elt[] -> [i]] -> "
      "Stmt_reduction_for[2] : 6 < i <= 9; [Elt[] -> [i]] -> "
      "Stmt_reduction_for[3] : 9 < i <= 12; [Elt[] -> [i]] -> "
      "Stmt_reduction_for[4] : 12 < i }"));
}

bool checkComputeArrayLifetime(const char *ScheduleStr, const char *WritesStr,
                               const char *ReadsStr, int ReadEltInSameInst,
                               int InclWrite, int InclLastRead, int ExitReads,
                               const char *ExpectedStr) {
  BOOL_FOR(ReadEltInSameInst)
  BOOL_FOR(InclWrite) BOOL_FOR(InclLastRead) BOOL_FOR(ExitReads) {
    std::unique_ptr<isl_ctx, decltype(&isl_ctx_free)> Ctx(isl_ctx_alloc(),
                                                          &isl_ctx_free);

    auto Schedule = give(isl_union_map_read_from_str(Ctx.get(), ScheduleStr));
    auto Writes = give(isl_union_map_read_from_str(Ctx.get(), WritesStr));
    auto Reads = give(isl_union_map_read_from_str(Ctx.get(), ReadsStr));
    auto Expected = give(isl_union_map_read_from_str(Ctx.get(), ExpectedStr));

    auto Result =
        computeArrayLifetime(Schedule, Writes, Reads, ReadEltInSameInst,
                             InclWrite, InclLastRead, ExitReads);
    auto Success = isl_union_map_is_equal(Result.keep(), Expected.keep());
    if (Success != isl_bool_true)
      return false;
  }

  return true;
}

TEST(DeLICM, ArrayPerWriteLifetimeZone) {
  EXPECT_TRUE(checkComputeArrayLifetime("{ }", "{ }", "{ }", indef, indef,
                                        indef, indef, "{ }"));
  EXPECT_TRUE(checkComputeArrayLifetime("{ Read[] -> [10] }",
                                        "{ Read[] -> A[] }", "{ }", indef,
                                        indef, indef, false, "{ }"));

  EXPECT_TRUE(checkComputeArrayLifetime("{ Def[] -> [10] }", "{ Def[] -> A[] }",
                                        "{ }", indef, indef, indef, false,
                                        "{ }"));
  EXPECT_TRUE(checkComputeArrayLifetime("{ Def[] -> [10] }", "{ Def[] -> A[] }",
                                        "{ }", indef, false, indef, true,
                                        "{ [A[] -> Def[]] -> [i] : 10 < i }"));
  EXPECT_TRUE(checkComputeArrayLifetime("{ Def[] -> [10] }", "{ Def[] -> A[] }",
                                        "{ }", indef, true, indef, true,
                                        "{ [A[] -> Def[]] -> [i] : 10 <= i }"));

  EXPECT_TRUE(checkComputeArrayLifetime(
      "{ Def[] -> [10]; Read[] -> [20] }", "{ Def[] -> A[] }",
      "{ Read[] -> A[] }", indef, false, false, false,
      "{ [A[] -> Def[]] -> [i] : 10 < i < 20 }"));
  EXPECT_TRUE(checkComputeArrayLifetime(
      "{ Def[] -> [10]; Read[] -> [20] }", "{ Def[] -> A[] }",
      "{ Read[] -> A[] }", indef, true, false, false,
      "{ [A[] -> Def[]] -> [i] : 10 <= i < 20 }"));
  EXPECT_TRUE(checkComputeArrayLifetime(
      "{ Def[] -> [10]; Read[] -> [20] }", "{ Def[] -> A[] }",
      "{ Read[] -> A[] }", indef, false, true, false,
      "{ [A[] -> Def[]] -> [i] : 10 < i <= 20 }"));
  EXPECT_TRUE(checkComputeArrayLifetime(
      "{ Def[] -> [10]; Read[] -> [20] }", "{ Def[] -> A[] }",
      "{ Read[] -> A[] }", indef, true, true, false,
      "{ [A[] -> Def[]] -> [i] : 10 <= i <= 20 }"));
  EXPECT_TRUE(checkComputeArrayLifetime("{ Def[] -> [10]; Read[] -> [20] }",
                                        "{ Def[] -> A[] }", "{ Read[] -> A[] }",
                                        indef, false, indef, true,
                                        "{ [A[] -> Def[]] -> [i] : 10 < i }"));
  EXPECT_TRUE(checkComputeArrayLifetime("{ Def[] -> [10]; Read[] -> [20] }",
                                        "{ Def[] -> A[] }", "{ Read[] -> A[] }",
                                        indef, true, indef, true,
                                        "{ [A[] -> Def[]] -> [i] : 10 <= i }"));

  EXPECT_TRUE(checkComputeArrayLifetime(
      "{ Def[] -> [10]; Read1[] -> [20]; Read2[] -> [30] }", "{ Def[] -> A[] }",
      "{ Read1[] -> A[]; Read2[] -> A[] }", indef, true, indef, true,
      "{ [A[] -> Def[]] -> [i] : 10 <= i }"));
  EXPECT_TRUE(checkComputeArrayLifetime(
      "{ Def[] -> [10]; Read1[] -> [20]; Read2[] -> [30] }", "{ Def[] -> A[] }",
      "{ Read1[] -> A[]; Read2[] -> A[] }", indef, true, true, false,
      "{ [A[] -> Def[]] -> [i] : 10 <= i <= 30 }"));

  EXPECT_TRUE(checkComputeArrayLifetime(
      "{ Def1[] -> [0]; Read[] -> [10]; Def2[] -> [20] }",
      "{ Def1[] -> A[]; Def2[] -> A[] }", "{ Read[] -> A[] }", indef, true,
      true, false, "{ [A[] -> Def1[]] -> [i] : 0 <= i <= 10 }"));
  EXPECT_TRUE(checkComputeArrayLifetime(
      "{ Def1[] -> [0]; Read[] -> [10]; Def2[] -> [20] }",
      "{ Def1[] -> A[]; Def2[] -> A[] }", "{ Read[] -> A[] }", indef, true,
      true, true, "{ [A[] -> Def1[]] -> [i] : 0 <= i <= 10; [A[] -> "
                  "Def2[]] -> [i] : 20 <= i }"));

  EXPECT_TRUE(checkComputeArrayLifetime(
      "{ Def1[] -> [0]; Def2[] -> [10]; Read[] -> [10] }",
      "{ Def1[] -> A[]; Def2[] -> A[] }", "{ Read[] -> A[] }", false, true,
      true, true, "{ [A[] -> Def1[]] -> [i] : 0 <= i <= 10; [A[] -> "
                  "Def2[]] -> [i] : 10 <= i }"));
  EXPECT_TRUE(checkComputeArrayLifetime(
      "{ Def1[] -> [0]; Def2[] -> [10]; Read[] -> [10] }",
      "{ Def1[] -> A[]; Def2[] -> A[] }", "{ Read[] -> A[] }", true, true, true,
      true, "{ [A[] -> Def2[]] -> [i] : 10 <= i }"));
}

bool checkComputeReachingOverwrite(const char *ScheduleStr, const char *DefsStr,
                                   int IncludePrevWrite, int IncludeOverwrite,
                                   const char *ExpectedStr) {
  BOOL_FOR(IncludePrevWrite) BOOL_FOR(IncludeOverwrite) {
    std::unique_ptr<isl_ctx, decltype(&isl_ctx_free)> Ctx(isl_ctx_alloc(),
                                                          &isl_ctx_free);

    auto Schedule = give(isl_union_map_read_from_str(Ctx.get(), ScheduleStr));
    auto Defs = give(isl_union_map_read_from_str(Ctx.get(), DefsStr));
    auto Expected = give(isl_union_map_read_from_str(Ctx.get(), ExpectedStr));

    auto Result = computeReachingOverwrite(Schedule, Defs, IncludePrevWrite,
                                           IncludeOverwrite);
    auto Success = isl_union_map_is_equal(Result.keep(), Expected.keep());
    if (Success != isl_bool_true)
      return false;
  }

  return true;
}

TEST(DeLICM, ReachingOverwrite) {
  EXPECT_TRUE(checkComputeReachingOverwrite(
      "{ Write[] -> [0] }", "{ Write[] -> Elt[] }", indef, false,
      "{ [Elt[] -> [i]] -> Write[] :  i < 0 }"));
  EXPECT_TRUE(checkComputeReachingOverwrite(
      "{ Write[] -> [0] }", "{ Write[] -> Elt[] }", indef, true,
      "{ [Elt[] -> [i]] -> Write[] : i <= 0 }"));

  EXPECT_TRUE(checkComputeReachingOverwrite(
      "{ Write[0] -> [0]; Write[1] -> [10] }", "{ Write[i] -> Elt[]; }", false,
      false, "{ [Elt[] -> [i]] -> Write[0] : i < 0 ; [Elt[] -> [i]] -> "
             "Write[1] : 0 < i < 10 }"));
  EXPECT_TRUE(checkComputeReachingOverwrite(
      "{ Write[0] -> [0]; Write[1] -> [10] }", "{ Write[i] -> Elt[]; }", false,
      true, "{ [Elt[] -> [i]] -> Write[0] : i <= 0 ; [Elt[] -> [i]] -> "
            "Write[1] : 0 < i <= 10 }"));
  EXPECT_TRUE(checkComputeReachingOverwrite(
      "{ Write[0] -> [0]; Write[1] -> [10] }", "{ Write[i] -> Elt[]; }", true,
      false, "{ [Elt[] -> [i]] -> Write[0] : i < 0 ; [Elt[] -> [i]] -> "
             "Write[1] : 0 <= i < 10 }"));
  EXPECT_TRUE(checkComputeReachingOverwrite(
      "{ Write[0] -> [0]; Write[1] -> [10] }", "{ Write[i] -> Elt[]; }", true,
      true, "{ [Elt[] -> [i]] -> Write[0] : i <= 0 ; [Elt[] -> [i]] -> "
            "Write[1] : 0 <= i <= 10 }"));
}

bool checkComputeArrayUnused(const char *ScheduleStr, const char *WritesStr,
                             const char *ReadsStr, int ReadEltInSameInst,
                             int IncludeLastRead, int IncludeWrite,
                             const char *ExpectedStr) {
  BOOL_FOR(ReadEltInSameInst) BOOL_FOR(IncludeLastRead) BOOL_FOR(IncludeWrite) {
    std::unique_ptr<isl_ctx, decltype(&isl_ctx_free)> Ctx(isl_ctx_alloc(),
                                                          &isl_ctx_free);

    auto Schedule = give(isl_union_map_read_from_str(Ctx.get(), ScheduleStr));
    auto Writes = give(isl_union_map_read_from_str(Ctx.get(), WritesStr));
    auto Reads = give(isl_union_map_read_from_str(Ctx.get(), ReadsStr));
    auto Expected = give(isl_union_map_read_from_str(Ctx.get(), ExpectedStr));

    auto Result = computeArrayUnused(Schedule, Writes, Reads, ReadEltInSameInst,
                                     IncludeLastRead, IncludeWrite);
    auto Success = isl_union_map_is_equal(Result.keep(), Expected.keep());
    if (Success != isl_bool_true)
      return false;
  }

  return isl_bool_true;
}

TEST(DeLICM, ArrayUnused) {
  EXPECT_TRUE(checkComputeArrayUnused("{ Read[] -> [0]; Write[] -> [10] }",
                                      "{ Write[] -> Elt[] }",
                                      "{ Read[] -> Elt[] }", indef, false,
                                      false, "{ Elt[] -> [i] : 0 < i < 10 }"));
  EXPECT_TRUE(checkComputeArrayUnused("{ Read[] -> [0]; Write[] -> [10] }",
                                      "{ Write[] -> Elt[] }",
                                      "{ Read[] -> Elt[] }", indef, false, true,
                                      "{ Elt[] -> [i] : 0 < i <= 10 }"));
  EXPECT_TRUE(checkComputeArrayUnused("{ Read[] -> [0]; Write[] -> [10] }",
                                      "{ Write[] -> Elt[] }",
                                      "{ Read[] -> Elt[] }", indef, true, false,
                                      "{ Elt[] -> [i] : 0 <= i < 10 }"));
  EXPECT_TRUE(checkComputeArrayUnused("{ Read[] -> [0]; Write[] -> [10] }",
                                      "{ Write[] -> Elt[] }",
                                      "{ Read[] -> Elt[] }", indef, true, true,
                                      "{ Elt[] -> [i] : 0 <= i <= 10 }"));

  EXPECT_TRUE(checkComputeArrayUnused(
      "{ Read[0] -> [-10]; Read[1] -> [0]; Write[] -> [10] }",
      "{ Write[] -> Elt[] }", "{ Read[i] -> Elt[] }", indef, false, true,
      "{ Elt[] -> [i] : 0 < i <= 10 }"));
  EXPECT_TRUE(checkComputeArrayUnused("{ Read[] -> [0];  }", "{ }",
                                      "{ Read[] -> Elt[] }", indef, indef,
                                      indef, "{ }"));
  EXPECT_TRUE(checkComputeArrayUnused(
      "{ Write[] -> [0];  }", "{ Write[] -> Elt[] }", "{ }", indef, indef, true,
      "{ Elt[] -> [i] : i <= 0  }"));

  EXPECT_TRUE(checkComputeArrayUnused("{ RW[] -> [0] }", "{ RW[] -> Elt[] }",
                                      "{ RW[] -> Elt[] }", true, indef, false,
                                      "{ Elt[] -> [i] : i < 0 }"));
  EXPECT_TRUE(checkComputeArrayUnused("{ RW[] -> [0] }", "{ RW[] -> Elt[] }",
                                      "{ RW[] -> Elt[] }", true, indef, true,
                                      "{ Elt[] -> [i] : i <= 0 }"));
  EXPECT_TRUE(checkComputeArrayUnused("{ RW[] -> [0] }", "{ RW[] -> Elt[] }",
                                      "{ RW[] -> Elt[] }", false, true, true,
                                      "{ Elt[] -> [0] }"));
}

/// Get the universes of all spaces in @p USet.
IslPtr<isl_union_set> unionSpace(NonowningIslPtr<isl_union_set> USet) {
  auto Result = give(isl_union_set_empty(isl_union_set_get_space(USet.keep())));
  foreachElt(USet, [=, &Result](IslPtr<isl_set> Set) {
    auto Space = give(isl_set_get_space(Set.keep()));
    auto Universe = give(isl_set_universe(Space.take()));
    Result = give(isl_union_set_add_set(Result.take(), Universe.take()));
  });
  return Result;
}

bool checkIsConflictingNonsymmetric(
    const char *ExistingKnownStr, const char *ExistingUnknownStr,
    const char *ExistingUndefStr, const char *ExistingWrittenStr,
    const char *ProposedKnownStr, const char *ProposedUnknownStr,
    const char *ProposedUndefStr, const char *ProposedWrittenStr) {
  std::unique_ptr<isl_ctx, decltype(&isl_ctx_free)> Ctx(isl_ctx_alloc(),
                                                        &isl_ctx_free);
  LLVMContext C;

  auto ExistingKnown =
      give(isl_union_map_read_from_str(Ctx.get(), ExistingKnownStr));
  auto ExistingUnknown =
      ExistingUnknownStr
          ? give(isl_union_set_read_from_str(Ctx.get(), ExistingUnknownStr))
          : nullptr;
  auto ExistingUndef =
      ExistingUndefStr
          ? give(isl_union_set_read_from_str(Ctx.get(), ExistingUndefStr))
          : nullptr;
  auto ExistingWritten =
      give(isl_union_map_read_from_str(Ctx.get(), ExistingWrittenStr));

  auto ProposedKnown =
      give(isl_union_map_read_from_str(Ctx.get(), ProposedKnownStr));
  auto ProposedUnknown =
      ProposedUnknownStr
          ? give(isl_union_set_read_from_str(Ctx.get(), ProposedUnknownStr))
          : nullptr;
  auto ProposedUndef =
      ProposedUndefStr
          ? give(isl_union_set_read_from_str(Ctx.get(), ProposedUndefStr))
          : nullptr;
  auto ProposedWritten =
      give(isl_union_map_read_from_str(Ctx.get(), ProposedWrittenStr));

  auto UndefVal = UndefValue::get(IntegerType::get(C, 8));
  auto UndefId = give(isl_id_alloc(Ctx.get(), "Undef", UndefVal));
  auto UndefSpace = give(isl_space_set_tuple_id(
      isl_space_set_alloc(Ctx.get(), 0, 0), isl_dim_set, UndefId.take()));
  auto UndefSet = give(isl_set_universe(UndefSpace.take()));
  auto UndefUSet = give(isl_union_set_from_set(UndefSet.take()));

  auto ExistingDefined = give(isl_union_map_domain(ExistingKnown.copy()));
  auto ExistingLifetime = ExistingKnown;
  if (ExistingUnknown) {
    ExistingDefined = give(
        isl_union_set_union(ExistingDefined.take(), ExistingUnknown.copy()));
    ExistingLifetime = give(
        isl_union_map_union(ExistingLifetime.take(),
                            isl_union_map_from_domain(ExistingUnknown.copy())));
  }
  if (ExistingUndef) {
    ExistingDefined =
        give(isl_union_set_union(ExistingDefined.take(), ExistingUndef.copy()));
    ExistingLifetime = give(isl_union_map_union(
        ExistingLifetime.take(), isl_union_map_from_domain_and_range(
                                     ExistingUndef.copy(), UndefUSet.copy())));
  }

  auto ProposedDefined = give(isl_union_map_domain(ProposedKnown.copy()));
  auto ProposedLifetime = ProposedKnown;
  if (ProposedUnknown) {
    ProposedDefined = give(
        isl_union_set_union(ProposedDefined.take(), ProposedUnknown.copy()));
    ProposedLifetime = give(
        isl_union_map_union(ProposedLifetime.take(),
                            isl_union_map_from_domain(ProposedUnknown.copy())));
  }
  if (ProposedUndef) {
    ProposedDefined =
        give(isl_union_set_union(ProposedDefined.take(), ProposedUndef.copy()));
    ProposedLifetime = give(isl_union_map_union(
        ProposedLifetime.take(), isl_union_map_from_domain_and_range(
                                     ProposedUndef.copy(), UndefUSet.copy())));
  }

  auto ExistingUniverse = unionSpace(ExistingDefined);
  ExistingUniverse = give(isl_union_set_union(
      ExistingUniverse.take(),
      unionSpace(give(isl_union_map_domain(ExistingWritten.copy()))).take()));

  auto ProposedUniverse = unionSpace(ProposedDefined);
  ProposedUniverse = give(isl_union_set_union(
      ProposedUniverse.take(),
      unionSpace(give(isl_union_map_domain(ProposedWritten.copy()))).take()));

  // The 'universe' contains all statement instances; because there is no
  // isl_union_set_universe, we derive it from all statement domains passes ti
  // this function.
  auto Universe = give(
      isl_union_set_union(ExistingUniverse.take(), ProposedUniverse.take()));

  // If the user did not specify the Existing Undef zone, assume it to be the
  // complement of all specified zones.
  // The Existing's Unknown zone is already assumed to be implicit by
  // isConflicting().
  if (!ExistingUndefStr)
    ExistingLifetime = give(isl_union_map_union(
        ExistingLifetime.take(),
        isl_union_map_from_domain_and_range(
            isl_union_set_subtract(Universe.copy(), ExistingDefined.copy()),
            UndefUSet.copy())));

  // If the user did not specify the Proposed Unknown zone, assume it to be the
  // complement of all specified zones.
  // The Proposed's Unknown zone is already assumed to be implicit by
  // isConflicting().
  if (!ProposedUnknownStr)
    ProposedLifetime = give(
        isl_union_map_union(ProposedLifetime.take(),
                            isl_union_map_from_domain(isl_union_set_subtract(
                                Universe.copy(), ProposedDefined.copy()))));

  return isConflicting(ExistingLifetime, true, ExistingWritten,
                       ProposedLifetime, false, ProposedWritten);
}

bool checkIsConflicting(const char *ThisKnownStr, const char *ThisUnknownStr,
                        const char *ThisUndefStr, const char *ThisWrittenStr,
                        const char *ThatKnownStr, const char *ThatUnknownStr,
                        const char *ThatUndefStr, const char *ThatWrittenStr) {
  auto ThisExisting = checkIsConflictingNonsymmetric(
      ThisKnownStr, ThisUnknownStr, ThisUndefStr, ThisWrittenStr, ThatKnownStr,
      ThatUnknownStr, ThatUndefStr, ThatWrittenStr);
  auto ThatExisting = checkIsConflictingNonsymmetric(
      ThatKnownStr, ThatUnknownStr, ThatUndefStr, ThatWrittenStr, ThisKnownStr,
      ThisUnknownStr, ThisUndefStr, ThisWrittenStr);

  // isConflicting should be symmetric.
  EXPECT_EQ(ThisExisting, ThatExisting);

  return ThisExisting || ThatExisting;
}

TEST(DeLICM, IsConflicting) {
  EXPECT_FALSE(
      checkIsConflicting("{}", "{}", nullptr, "{}", "{}", "{}", nullptr, "{}"));
  EXPECT_FALSE(
      checkIsConflicting("{}", nullptr, "{}", "{}", "{}", "{}", nullptr, "{}"));

  EXPECT_FALSE(checkIsConflicting("{}", nullptr, "{}", "{ Dom[0] -> Val[] }",
                                  "{}", "{}", nullptr, "{}"));

  EXPECT_FALSE(checkIsConflicting("{}", nullptr, "{}", "{ Dom[0] -> [] }", "{}",
                                  "{}", nullptr, "{}"));

  EXPECT_FALSE(checkIsConflicting("{ Dom[0] -> Val[] }", nullptr, "{}", "{}",
                                  "{ Dom[0] -> Val[] }", "{}", nullptr, "{}"));

  EXPECT_FALSE(checkIsConflicting("{ Dom[i] -> Val[] : 0 < i  }", nullptr,
                                  "{ Dom[i] : i <= 0 }", "{}", "{}", "{}",
                                  nullptr, "{ Dom[-1] -> [] }"));

  EXPECT_FALSE(checkIsConflicting("{ Dom[i] -> Val[] : i <= 10 }", nullptr,
                                  "{ Dom[i] :  10  < i }", "{}", "{}", "{}",
                                  nullptr, "{ Dom[10] -> [] }"));

  EXPECT_FALSE(checkIsConflicting("{}", nullptr, "{ Dom[0] }", "{}",
                                  "{ Dom[0] -> Val[] }", "{}", nullptr, "{}"));

  EXPECT_FALSE(checkIsConflicting("{}", nullptr, "{ Dom[i] }", "{}", "{}", "{}",
                                  nullptr, "{ Dom[0] -> Val[] }"));

  EXPECT_TRUE(checkIsConflicting("{}", "{ Dom[i] }", nullptr, "{ }", "{}",
                                 nullptr, "{}", "{ Dom[0] -> Val[] }"));

  EXPECT_FALSE(checkIsConflicting("{}", nullptr, "{ Dom[i] }",
                                  "{ Dom[0] -> Val[] }", "{ Dom[i] -> Val[] }",
                                  "{}", nullptr, "{}"));

  EXPECT_TRUE(checkIsConflicting("{ Dom[0] -> ValA[] }", nullptr, "{}", "{}",
                                 "{ Dom[0] -> ValB[] }", "{}", nullptr, "{}"));

  EXPECT_TRUE(checkIsConflicting("{ Dom[0] -> Val[] }", nullptr, "{}", "{}",
                                 "{}", "{ Dom[0] }", nullptr, "{}"));

  EXPECT_TRUE(checkIsConflicting("{}", nullptr, "{}", "{}",
                                 "{ Dom[] -> Val[] }", "{}", nullptr, "{}"));

  EXPECT_TRUE(checkIsConflicting("{ Dom[i] -> Val[] : 0 < i <= 10 }", nullptr,
                                 "{}", "{}", "{}", "{}", nullptr,
                                 "{ Dom[1] -> [] }"));

  EXPECT_TRUE(checkIsConflicting("{ Dom[i] -> Val[] : 0 < i <= 10 }", nullptr,
                                 "{}", "{}", "{}", "{}", nullptr,
                                 "{ Dom[9] -> [] }"));

  EXPECT_TRUE(checkIsConflicting("{ Dom[i] -> ValA[] }", nullptr, "{}", "{}",
                                 "{ Dom[i] -> ValA[] }", "{}", nullptr,
                                 "{ Dom[0] -> ValB[] }"));

  EXPECT_TRUE(checkIsConflicting("{ Dom[i] -> Val[] }", nullptr, "{}", "{}",
                                 "{ Dom[i] -> Val[] }", "{}", nullptr,
                                 "{ Dom[0] -> [] }"));

  EXPECT_TRUE(checkIsConflicting("{ Dom[i] -> [] }", nullptr, "{}", "{}", "{}",
                                 "{}", nullptr, "{ Dom[0] -> [] }"));

  EXPECT_TRUE(checkIsConflicting("{}", nullptr, "{ Dom[i] }",
                                 "{ Dom[0] -> [] }", "{ Dom[i] -> [] }", "{}",
                                 nullptr, "{}"));

  EXPECT_TRUE(checkIsConflicting("{}", nullptr, "{}", "{}", "{}", "{}", nullptr,
                                 "{ Dom[0] -> Val[] }"));

  EXPECT_TRUE(checkIsConflicting("{}", nullptr, "{}", "{}", "{}", "{}", nullptr,
                                 "{ Dom[0] -> [] }"));

  EXPECT_TRUE(checkIsConflicting("{}", nullptr, "{}", "{ Dom[0] -> Val[] }",
                                 "{}", "{ Dom[i] }", nullptr, "{}"));

  EXPECT_TRUE(checkIsConflicting("{}", nullptr, "{}", "{ Dom[0] -> [] }", "{}",
                                 "{ Dom[i] }", nullptr, "{}"));

  EXPECT_TRUE(checkIsConflicting("{}", nullptr, "{}", "{ Dom[0] -> Val[] }",
                                 "{ Dom[i] -> [] }", "{}", nullptr, "{}"));

  EXPECT_TRUE(checkIsConflicting("{}", nullptr, "{}", "{ Dom[0] -> [] }",
                                 "{ Dom[i] -> Val[] }", "{}", nullptr, "{}"));

  EXPECT_TRUE(checkIsConflicting("{}", nullptr, "{}", "{ Dom[0] -> [] }",
                                 "{ Dom[i] -> [] }", "{}", nullptr, "{}"));

  EXPECT_TRUE(checkIsConflicting("{}", "{}", nullptr, "{ Dom[0] -> ValA[] }",
                                 "{}", "{}", nullptr, "{ Dom[0] -> ValB[] }"));
  EXPECT_TRUE(checkIsConflicting("{}", "{}", nullptr, "{ Dom[0] -> [] }", "{}",
                                 "{}", nullptr, "{ Dom[0] -> Val[] }"));
  EXPECT_TRUE(checkIsConflicting("{}", "{}", nullptr, "{ Dom[0] -> Val[] }",
                                 "{}", "{}", nullptr, "{ Dom[0] -> [] }"));

  EXPECT_TRUE(checkIsConflicting("{}", "{}", nullptr, "{ Dom[0] -> [] }", "{}",
                                 "{}", nullptr, "{ Dom[0] -> [] }"));

  EXPECT_FALSE(checkIsConflicting("{}", "{}", nullptr,
                                  "{ Dom[0] -> ValA[]; Dom[0] -> ValB[] }",
                                  "{}", "{}", nullptr, "{  }"));
}

TEST(X, X) {
	auto Ctx = isl_ctx_alloc();
	auto Test = give(isl_union_map_read_from_str( Ctx  ,
	"[p_0, p_1, b8] -> { [MemRef_img[i0] -> [i1, i2, i3]] -> Val_[] : "
#if 1
		"(exists (e0 = floor((b8)/2): 2e0 = b8 and b8 <= -2 and i0 >= 164 + 64b8 and i0 <= 171 + 64b8 and i1 >= 6)) or "
		"(exists (e0 = floor((b8)/2): 2e0 <= b8 and b8 >= 0 and 112e0 <= -164 - 8b8 + i0 and i1 >= 6 and 2e0 >= -1 + b8 and 112e0 >= -171 - 8b8 + i0)) or "
		"(exists (e0 = floor((-1 + b8)/2): 2e0 = -1 + b8 and b8 < 0 and i0 >= 220 + 64b8 and i0 <= 227 + 64b8 and i1 >= 6)) or "
#endif
"(exists (e0 = floor((-1 + b8)/2), e1 = floor((-51 + 104b8 + i0 + 96i2 + 111i3)/112): i1 = 5 and 2e0 = -1 + b8 and b8 < 0 and i2 >= 0 and i2 <= 7 and 16i2 >= -115 - 64b8 + i0 and 16i2 <= -108 - 64b8 + i0 and i3 >= -107 - 64b8 + i0 - 16i2 and 112e1 >= -162 + 104b8 + i0 + 96i2 + 111i3 and 112e1 >= 60 + 104b8 + i0 + 96i2 and 112e1 <= -51 + 104b8 + i0 + 96i2 + 111i3)) or "

#if 1
		"(exists (e0 = floor((b8)/2), e1 = floor((-44 + i0)/16): 2e0 = b8 and b8 <= -2 and i0 >= 44 + 64b8 and i0 <= 163 + 64b8 and i1 >= 6 and 16e1 >= -59 + i0 and 16e1 <= -52 + i0)) or "
		"(exists (e0 = floor((b8)/2), e1 = floor((-44 + i0)/16): 2e0 = b8 and b8 >= 0 and i0 >= 116 + 64b8 and i0 <= 163 + 64b8 and i1 >= 6 and 16e1 >= -59 + i0 and 16e1 <= -52 + i0)) or "
#endif
"(exists (e0 = floor((b8)/2), e1 = floor((-44 + i0)/16): 2e0 = b8 and b8 >= 0 and i0 >= 44 + 64b8 and i0 <= 107 + 64b8 and i1 >= 6 and 16e1 >= -59 + i0 and 16e1 <= -52 + i0)) or "
"(exists (e0 = floor((-1 + b8)/2), e1 = floor((-100 + i0)/16): 2e0 = -1 + b8 and b8 < 0 and i0 >= 172 + 64b8 and i0 <= 219 + 64b8 and i1 >= 6 and 16e1 >= -115 + i0 and 16e1 <= -108 + i0)) or "
"(exists (e0 = floor((-1 + b8)/2), e1 = floor((-100 + i0)/16): 2e0 = -1 + b8 and b8 < 0 and i0 >= 100 + 64b8 and i0 <= 163 + 64b8 and i1 >= 6 and 16e1 >= -115 + i0 and 16e1 <= -108 + i0)) or "
"(exists (e0 = floor((-1 + b8)/2), e1 = floor((-100 + i0)/16): 2e0 = -1 + b8 and b8 > 0 and i0 >= -12 + 64b8 and i0 <= 107 + 64b8 and i1 >= 6 and 16e1 >= -115 + i0 and 16e1 <= -108 + i0)) or "
"(exists (e0 = floor((b8)/2): i1 = 5 and 2e0 = b8 and b8 <= -2 and i0 >= 165 + 64b8 and i0 <= 171 + 64b8 and i2 >= 8)) or "
"(exists (e0 = floor((b8)/2): i1 = 5 and 2e0 = b8 and b8 >= 0 and i0 >= 164 + 64b8 and i0 <= 171 + 64b8 and i2 >= 8)) or "
"(exists (e0 = floor((-1 + b8)/2): i1 = 5 and 2e0 = -1 + b8 and b8 < 0 and i0 >= 220 + 64b8 and i0 <= 227 + 64b8 and i2 >= 8)) or "
"(exists (e0 = floor((-1 + b8)/2): i1 = 5 and 2e0 = -1 + b8 and b8 > 0 and i0 >= 109 + 64b8 and i0 <= 115 + 64b8 and i2 >= 8)) or "
"(exists (e0 = floor((b8)/2): i1 = 5 and 2e0 = b8 and b8 <= -2 and i2 > 0 and i2 <= 7 and 16i2 >= -43 - 64b8 + i0 and 16i2 <= -37 - 64b8 + i0)) or "

		"(exists (e0 = floor((b8)/2): i1 = 5 and 2e0 = b8 and b8 >= 0 and i2 > 0 and i2 <= 7 and 16i2 >= -43 - 64b8 + i0 and 16i2 <= -36 - 64b8 + i0)) or "
"(exists (e0 = floor((-1 + b8)/2): i1 = 5 and 2e0 = -1 + b8 and b8 < 0 and i2 > 0 and i2 <= 7 and 16i2 >= -99 - 64b8 + i0 and 16i2 <= -92 - 64b8 + i0)) or "
		"(exists (e0 = floor((-1 + b8)/2): i1 = 5 and 2e0 = -1 + b8 and b8 > 0 and i2 > 0 and i2 <= 7 and 16i2 >= 13 - 64b8 + i0 and 16i2 <= 19 - 64b8 + i0)) or "
"(exists (e0 = floor((b8)/2): i1 = 5 and 2e0 = b8 and b8 <= -2 and i2 >= 0 and i2 <= 7 and 16i2 >= -59 - 64b8 + i0 and 16i2 <= -52 - 64b8 + i0 and i3 >= -51 - 64b8 + i0 - 16i2)) or "
		"(exists (e0 = floor((-1 + b8)/2): i1 = 5 and 2e0 = -1 + b8 and b8 > 0 and i2 >= 0 and i2 <= 7 and 16i2 >= -3 - 64b8 + i0 and 16i2 <= 4 - 64b8 + i0 and i3 >= 5 - 64b8 + i0 - 16i2)) or "
		"(exists (e0 = floor((b8)/2), e1 = floor((-44 + i0)/16): i1 = 5 and 2e0 = b8 and b8 <= -2 and i0 >= 44 + 64b8 and i0 <= 164 + 64b8 and 16i2 >= -36 - 64b8 + i0 and 16e1 >= -59 + i0 and 16e1 <= -52 + i0)) or "
		"(exists (e0 = floor((b8)/2), e1 = floor((-44 + i0)/16): i1 = 5 and 2e0 = b8 and b8 >= 0 and i0 >= 116 + 64b8 and i0 <= 163 + 64b8 and i2 >= 8 and 16e1 >= -59 + i0 and 16e1 <= -52 + i0)) or "
		
		"(exists (e0 = floor((b8)/2), e1 = floor((-44 + i0)/16): i1 = 5 and 2e0 = b8 and b8 >= 0 and i0 >= 44 + 64b8 and i0 <= 108 + 64b8 and 16i2 >= 20 - 64b8 + i0 and 16e1 >= -59 + i0 and 16e1 <= -52 + i0)) or "
		"(exists (e0 = floor((-1 + b8)/2), e1 = floor((-100 + i0)/16): i1 = 5 and 2e0 = -1 + b8 and b8 < 0 and i0 >= 172 + 64b8 and i0 <= 219 + 64b8 and i2 >= 8 and 16e1 >= -115 + i0 and 16e1 <= -108 + i0)) or "
		"(exists (e0 = floor((-1 + b8)/2), e1 = floor((-100 + i0)/16): i1 = 5 and 2e0 = -1 + b8 and b8 < 0 and i0 >= 100 + 64b8 and i0 <= 164 + 64b8 and 16i2 >= -36 - 64b8 + i0 and 16e1 >= -115 + i0 and 16e1 <= -108 + i0)) or "
		"(exists (e0 = floor((-1 + b8)/2), e1 = floor((-100 + i0)/16): i1 = 5 and 2e0 = -1 + b8 and b8 > 0 and i0 >= -12 + 64b8 and i0 <= 108 + 64b8 and 16i2 >= 20 - 64b8 + i0 and 16e1 >= -115 + i0 and 16e1 <= -108 + i0)) or "
		"(exists (e0 = floor((b8)/2), e1 = floor((-44 + i0)/16): i1 = 5 and 2e0 = b8 and b8 >= 0 and i0 >= 44 + 64b8 and i2 <= 7 and 16i2 >= -35 - 64b8 + i0 and 16i2 <= 12 - 64b8 + i0 and 16e1 >= -59 + i0 and 16e1 <= -52 + i0)) or "
		"(exists (e0 = floor((-1 + b8)/2), e1 = floor((-100 + i0)/16): i1 = 5 and 2e0 = -1 + b8 and b8 < 0 and i0 >= 100 + 64b8 and i2 <= 7 and 16i2 >= -91 - 64b8 + i0 and 16i2 <= -44 - 64b8 + i0 and 16e1 >= -115 + i0 and 16e1 <= -108 + i0)) or "

		"(exists (e0 = floor((b8)/2), e1 = floor((-51 + 104b8 + i0 + 96i2 + 111i3)/112): i1 = 5 and 2e0 = b8 and b8 >= 0 and i2 >= 0 and i2 <= 7 and 16i2 >= -59 - 64b8 + i0 and 16i2 <= -52 - 64b8 + i0 and i3 >= -51 - 64b8 + i0 - 16i2 and 112e1 >= -162 + 104b8 + i0 + 96i2 + 111i3 and 112e1 >= 60 + 104b8 + i0 + 96i2 and 112e1 <= -51 + 104b8 + i0 + 96i2 + 111i3)); "
#if 1
		"[MemRef_img[i0] -> [i1, i2, i3]] -> Undef[] : (exists (e0 = floor((-1 + b8)/2), e1 = floor((-44 - 8b8 + i0)/16): b8 < 0 and i1 <= 4 and 16e1 >= -59 - 8b8 + i0 and 16e1 <= -52 - 8b8 + i0 and 2e0 >= -2 + b8 and 2e0 < b8 and 112e0 >= -283 - 8b8 + i0 and 112e0 <= -156 - 8b8 + i0)) or (exists (e0 = floor((b8)/2), e1 = floor((-44 - 8b8 + i0)/16): p_1 < 0 and b8 >= 0 and i1 <= 4 and 16e1 >= -59 - 8b8 + i0 and 16e1 <= -52 - 8b8 + i0 and 2e0 >= -1 + b8 and 2e0 <= b8 and 112e0 >= -171 - 8b8 + i0 and 112e0 <= -44 - 8b8 + i0)) or "
		"(exists (e0 = floor((b8)/2), e1 = floor((-44 - 8b8 + i0)/16): p_1 > 0 and b8 >= 0 and i1 <= 4 and 16e1 >= -59 - 8b8 + i0 and 16e1 <= -52 - 8b8 + i0 and 2e0 >= -1 + b8 and 2e0 <= b8 and 112e0 >= -171 - 8b8 + i0 and 112e0 <= -44 - 8b8 + i0)) or (exists (e0 = floor((1 + b8)/2): p_1 = 0 and 2e0 = 1 + b8 and p_0 < 0 and b8 > 0 and i0 >= -4 + 64b8 and i0 <= 3 + 64b8 and i1 <= 4)) or "
		"(exists (e0 = floor((1 + b8)/2): p_1 = 0 and 2e0 = 1 + b8 and p_0 > 0 and b8 > 0 and i0 >= -4 + 64b8 and i0 <= 3 + 64b8 and i1 <= 4)) or "
		"(exists (e0 = floor((1 + b8)/2): i1 = 5 and b8 < 0 and i2 >= 0 and i2 <= 7 and 2e0 >= b8 and 2e0 <= 1 + b8 and 112e0 >= -59 - 8b8 + i0 - 16i2 and 112e0 <= -52 - 8b8 + i0 - 16i2 - i3 and 112e0 <= -52 - 8b8 + i0 - 16i2)) or "
		"(exists (e0 = floor((-1 + b8)/2), e1 = floor((-44 - 8b8 + i0)/16): i1 = 5 and b8 < 0 and 16e1 >= -59 - 8b8 + i0 and 16e1 <= -52 - 8b8 + i0 and 2e0 >= -2 + b8 and 2e0 < b8 and 112e0 >= -283 - 8b8 + i0 and 112e0 <= -172 - 8b8 + i0 - 16i2 and 112e0 <= -156 - 8b8 + i0)) or "
		"(exists (e0 = floor((b8)/2): i1 = 5 and p_1 < 0 and b8 >= 0 and i2 >= 0 and i2 <= 7 and 2e0 >= -1 + b8 and 2e0 <= b8 and 112e0 >= -59 - 8b8 + i0 - 16i2 and 112e0 <= -52 - 8b8 + i0 - 16i2 - i3 and 112e0 <= -52 - 8b8 + i0 - 16i2)) or "
		"(exists (e0 = floor((b8)/2): i1 = 5 and p_1 > 0 and b8 >= 0 and i2 >= 0 and i2 <= 7 and 2e0 >= -1 + b8 and 2e0 <= b8 and 112e0 >= -59 - 8b8 + i0 - 16i2 and 112e0 <= -52 - 8b8 + i0 - 16i2 - i3 and 112e0 <= -52 - 8b8 + i0 - 16i2)) or "
		"(exists (e0 = floor((b8)/2), e1 = floor((-44 - 8b8 + i0)/16): i1 = 5 and p_1 < 0 and b8 >= 0 and 16e1 >= -59 - 8b8 + i0 and 16e1 <= -52 - 8b8 + i0 and 2e0 >= -1 + b8 and 2e0 <= b8 and 112e0 >= -171 - 8b8 + i0 and 112e0 <= -60 - 8b8 + i0 - 16i2 and 112e0 <= -44 - 8b8 + i0)) or "
		"(exists (e0 = floor((b8)/2), e1 = floor((-44 - 8b8 + i0)/16): i1 = 5 and p_1 > 0 and b8 >= 0 and 16e1 >= -59 - 8b8 + i0 and 16e1 <= -52 - 8b8 + i0 and 2e0 >= -1 + b8 and 2e0 <= b8 and 112e0 >= -171 - 8b8 + i0 and 112e0 <= -60 - 8b8 + i0 - 16i2 and 112e0 <= -44 - 8b8 + i0)) or "
		"(exists (e0 = floor((b8)/2): p_1 = 0 and 2e0 = b8 and p_0 < 0 and b8 >= 0 and i0 >= 52 + 64b8 and i0 <= 59 + 64b8 and i1 <= 4)) or "
		"(exists (e0 = floor((b8)/2): p_1 = 0 and 2e0 = b8 and p_0 > 0 and b8 >= 0 and i0 >= 52 + 64b8 and i0 <= 59 + 64b8 and i1 <= 4)) or "
		"(exists (e0 = floor((b8)/2): p_0 = 0 and p_1 = 0 and 2e0 >= -1 + b8 and i0 >= 2948 and 112e0 <= -52 - 8b8 + i0 and i1 <= 4 and 2e0 <= b8 and 112e0 >= -59 - 8b8 + i0)) or (exists (e0 = floor((b8)/2): p_1 = 0 and i1 = 5 and 2e0 >= -1 + b8 and p_0 < 0 and b8 >= 0 and 112e0 >= -59 - 8b8 + i0 and i2 <= -2 and 2e0 <= b8 and 112e0 <= -52 - 8b8 + i0)) or "
		"(exists (e0 = floor((b8)/2): p_1 = 0 and i1 = 5 and 2e0 >= -1 + b8 and p_0 > 0 and b8 >= 0 and 112e0 >= -59 - 8b8 + i0 and i2 <= -2 and 2e0 <= b8 and 112e0 <= -52 - 8b8 + i0)) or "
		"(exists (e0 = floor((b8)/2): p_0 = 0 and p_1 = 0 and 2e0 >= -1 + b8 and b8 >= 0 and i0 <= 2945 and 112e0 >= -59 - 8b8 + i0 and i1 <= 4 and 2e0 <= b8 and 112e0 <= -52 - 8b8 + i0)) or (exists (e0 = floor((11 + 15i0)/16), e1 = floor((12 + 8b8 + i0)/16): p_1 = 0 and 2e1 = 1 + b8 + 2i0 - 2e0 and p_0 < 0 and b8 > 0 and i0 >= 60 + 64b8 and i1 <= 4 and i0 <= 123 + 64b8 and 16e0 >= -4 + 15i0 and 16e0 <= 3 + 15i0)) or "
		"(exists (e0 = floor((11 + 15i0)/16), e1 = floor((12 + 8b8 + i0)/16): p_1 = 0 and 2e1 = 1 + b8 + 2i0 - 2e0 and p_0 > 0 and b8 > 0 and i0 >= 60 + 64b8 and i1 <= 4 and i0 <= 123 + 64b8 and 16e0 >= -4 + 15i0 and 16e0 <= 3 + 15i0)) or "
		"(exists (e0 = floor((b8)/2), e1 = floor((11 + 15i0)/16): p_1 = 0 and 2e0 = b8 and p_0 < 0 and b8 >= 0 and i0 >= 60 + 64b8 and i0 <= 171 + 64b8 and i1 <= 4 and 16e1 >= 4 + 15i0 and 16e1 <= 11 + 15i0)) or "
		"(exists (e0 = floor((b8)/2), e1 = floor((11 + 15i0)/16): p_1 = 0 and 2e0 = b8 and p_0 > 0 and b8 >= 0 and i0 >= 60 + 64b8 and i0 <= 171 + 64b8 and i1 <= 4 and 16e1 >= 4 + 15i0 and 16e1 <= 11 + 15i0)) or (exists (e0 = floor((-1 + b8)/2), e1 = floor((11 + 8b8 + 15i0)/16): p_1 = 0 and 2e0 = -1 + b8 and p_0 < 0 and b8 > 0 and i0 >= 4 + 64b8 and i0 <= 51 + 64b8 and i1 <= 4 and 16e1 >= 4 + 8b8 + 15i0 and 16e1 <= 11 + 8b8 + 15i0)) or "
		"(exists (e0 = floor((-1 + b8)/2), e1 = floor((11 + 8b8 + 15i0)/16): p_1 = 0 and 2e0 = -1 + b8 and p_0 > 0 and b8 > 0 and i0 >= 4 + 64b8 and i0 <= 51 + 64b8 and i1 <= 4 and 16e1 >= 4 + 8b8 + 15i0 and 16e1 <= 11 + 8b8 + 15i0)) or "
		"(exists (e0 = floor((b8)/2): p_1 = 0 and i1 = 5 and 2e0 >= -1 + b8 and p_0 < 0 and b8 >= 0 and i2 >= -1 and i2 <= 6 and 112e0 >= -75 - 8b8 + i0 - 16i2 and 2e0 <= b8 and 112e0 <= -68 - 8b8 + i0 - 16i2)) or "
		"(exists (e0 = floor((b8)/2): p_1 = 0 and i1 = 5 and 2e0 >= -1 + b8 and p_0 > 0 and b8 >= 0 and i2 >= -1 and i2 <= 6 and 112e0 >= -75 - 8b8 + i0 - 16i2 and 2e0 <= b8 and 112e0 <= -68 - 8b8 + i0 - 16i2)) or (exists (e0 = floor((51 - 104b8 - i0 - 96i2)/112): p_1 = 0 and i1 = 5 and p_0 < 0 and b8 >= 0 and i2 >= 0 and i2 <= 7 and 2e0 >= -2 - 3b8 - 2i2 and 2e0 < -3b8 - 2i2 and 112e0 >= -60 - 104b8 - i0 - 96i2 + i3 and 112e0 >= -60 - 104b8 - i0 - 96i2 and 112e0 <= -53 - 104b8 - i0 - 96i2)) or "
		"(exists (e0 = floor((51 - 104b8 - i0 - 96i2)/112): p_1 = 0 and i1 = 5 and p_0 > 0 and b8 >= 0 and i2 >= 0 and i2 <= 7 and 2e0 >= -2 - 3b8 - 2i2 and 2e0 < -3b8 - 2i2 and 112e0 >= -60 - 104b8 - i0 - 96i2 + i3 and 112e0 >= -60 - 104b8 - i0 - 96i2 and 112e0 <= -53 - 104b8 - i0 - 96i2)) or "
		"(p_0 = 0 and p_1 = 0 and b8 = 45 and i1 = 2 and i0 >= 2946 and i0 <= 2947 and i2 > 0) or "
		"(exists (e0 = floor((b8)/2), e1 = floor((11 + 15i0)/16): p_0 = 0 and p_1 = 0 and i1 = 5 and 2e0 = b8 and b8 >= 0 and i0 >= 60 + 64b8 and i0 <= 2945 and i0 <= 171 + 64b8 and 16e1 >= 4 + 15i0 and 16e1 <= 11 + 15i0 and 16i2 <= -76 - 64b8 + i0)) or (p_0 = 0 and p_1 = 0 and b8 = 45 and i1 = 2 and i2 = 0 and i0 >= 2946 and i0 <= 2947 and i3 > 0) or "
		"(exists (e0 = floor((-1 + b8)/2), e1 = floor((11 + 8b8 + 15i0)/16): p_0 = 0 and p_1 = 0 and i1 = 5 and 2e0 = -1 + b8 and i0 >= 2948 and i0 <= 115 + 64b8 and i2 >= -1 and 16i2 >= -67 - 64b8 + i0 and 16i2 <= -20 - 64b8 + i0 and 16e1 >= 4 + 8b8 + 15i0 and 16e1 <= 11 + 8b8 + 15i0)) or (p_0 = 0 and p_1 = 0 and b8 = 45 and i0 >= 2946 and i0 <= 2947 and i1 >= 3 and i1 <= 4) or "
		"(exists (e0 = floor((b8)/2): p_0 = 0 and p_1 = 0 and i1 = 5 and 2e0 >= -1 + b8 and i0 >= 2948 and 112e0 <= -52 - 8b8 + i0 and i2 <= -2 and 2e0 <= b8 and 112e0 >= -59 - 8b8 + i0)) or (exists (e0 = floor((-1 + b8)/2), e1 = floor((11 + 8b8 + 15i0)/16): p_0 = 0 and p_1 = 0 and i1 = 5 and 2e0 = -1 + b8 and i0 >= 4 + 64b8 and i0 >= 2948 and i0 <= 51 + 64b8 and i2 <= -2 and 16e1 >= 4 + 8b8 + 15i0 and 16e1 <= 11 + 8b8 + 15i0)) or "
		"(exists (e0 = floor((11 + 15i0)/16), e1 = floor((12 + 8b8 + i0)/16): p_0 = 0 and p_1 = 0 and i1 = 5 and 2e1 = 1 + b8 + 2i0 - 2e0 and i0 >= 2948 and 16i2 <= -76 - 64b8 + i0 and i0 <= 123 + 64b8 and 16e0 >= -4 + 15i0 and 16e0 <= 3 + 15i0 and i0 >= 60 + 64b8)) or "
		"(exists (e0 = floor((11 + 15i0)/16), e1 = floor((12 + 8b8 + i0)/16): p_0 = 0 and p_1 = 0 and 2e1 = 1 + b8 + 2i0 - 2e0 and i0 >= 60 + 64b8 and i0 >= 2948 and i1 <= 4 and i0 <= 123 + 64b8 and 16e0 >= -4 + 15i0 and 16e0 <= 3 + 15i0)) or (exists (e0 = floor((b8)/2), e1 = floor((11 + 15i0)/16): p_0 = 0 and p_1 = 0 and 2e0 = b8 and i0 >= 60 + 64b8 and i0 >= 2948 and i0 <= 171 + 64b8 and i1 <= 4 and 16e1 >= 4 + 15i0 and 16e1 <= 11 + 15i0)) or "
		"(exists (e0 = floor((-1 + b8)/2), e1 = floor((11 + 8b8 + 15i0)/16): p_0 = 0 and p_1 = 0 and 2e0 = -1 + b8 and i0 >= 4 + 64b8 and i0 >= 2948 and i0 <= 51 + 64b8 and i1 <= 4 and 16e1 >= 4 + 8b8 + 15i0 and 16e1 <= 11 + 8b8 + 15i0)) or (exists (e0 = floor((b8)/2): p_0 = 0 and p_1 = 0 and i1 = 5 and 2e0 >= -1 + b8 and i0 >= 2948 and i2 >= -1 and i2 <= 6 and 112e0 >= -75 - 8b8 + i0 - 16i2 and 2e0 <= b8 and 112e0 <= -68 - 8b8 + i0 - 16i2)) or "
		"(exists (e0 = floor((b8)/2): p_0 = 0 and p_1 = 0 and i1 = 5 and 2e0 >= -1 + b8 and b8 >= 0 and i0 <= 2945 and 112e0 >= -59 - 8b8 + i0 and i2 <= -2 and 2e0 <= b8 and 112e0 <= -52 - 8b8 + i0)) or "
		"(exists (e0 = floor((-1 + b8)/2), e1 = floor((11 + 8b8 + 15i0)/16): p_0 = 0 and p_1 = 0 and 2e0 = -1 + b8 and b8 > 0 and i0 >= 4 + 64b8 and i0 <= 2945 and i0 <= 51 + 64b8 and i1 <= 4 and 16e1 >= 4 + 8b8 + 15i0 and 16e1 <= 11 + 8b8 + 15i0)) or "
		"(exists (e0 = floor((11 + 15i0)/16), e1 = floor((12 + 8b8 + i0)/16): p_1 = 0 and i1 = 5 and 2e1 = 1 + b8 + 2i0 - 2e0 and p_0 < 0 and b8 > 0 and i0 >= 60 + 64b8 and i0 <= 123 + 64b8 and 16e0 >= -4 + 15i0 and 16e0 <= 3 + 15i0 and 16i2 <= -76 - 64b8 + i0)) or "
		"(exists (e0 = floor((-1 + b8)/2), e1 = floor((11 + 8b8 + 15i0)/16): p_0 = 0 and p_1 = 0 and i1 = 5 and 2e0 = -1 + b8 and b8 > 0 and i0 >= 4 + 64b8 and i0 <= 2945 and i0 <= 51 + 64b8 and i2 <= -2 and 16e1 >= 4 + 8b8 + 15i0 and 16e1 <= 11 + 8b8 + 15i0)) or (exists (e0 = floor((11 + 15i0)/16), e1 = floor((12 + 8b8 + i0)/16): p_1 = 0 and i1 = 5 and 2e1 = 1 + b8 + 2i0 - 2e0 and p_0 > 0 and b8 > 0 and i0 >= 60 + 64b8 and i0 <= 123 + 64b8 and 16e0 >= -4 + 15i0 and 16e0 <= 3 + 15i0 and 16i2 <= -76 - 64b8 + i0)) or "
		"(exists (e0 = floor((b8)/2), e1 = floor((11 + 15i0)/16): p_0 = 0 and p_1 = 0 and i1 = 5 and 2e0 = b8 and i0 >= 2948 and i0 <= 171 + 64b8 and 16i2 <= -76 - 64b8 + i0 and 16e1 >= 4 + 15i0 and 16e1 <= 11 + 15i0 and i0 >= 60 + 64b8)) or "
		"(exists (e0 = floor((11 + 15i0)/16), e1 = floor((12 + 8b8 + i0)/16): p_0 = 0 and p_1 = 0 and 2e1 = 1 + b8 + 2i0 - 2e0 and b8 > 0 and i0 >= 60 + 64b8 and i0 <= 2945 and i1 <= 4 and i0 <= 123 + 64b8 and 16e0 >= -4 + 15i0 and 16e0 <= 3 + 15i0)) or "
		"(exists (e0 = floor((b8)/2), e1 = floor((11 + 15i0)/16): p_1 = 0 and i1 = 5 and 2e0 = b8 and p_0 < 0 and b8 >= 0 and i0 >= 60 + 64b8 and 16i2 <= -76 - 64b8 + i0 and 16e1 >= 4 + 15i0 and 16e1 <= 11 + 15i0 and i0 <= 171 + 64b8)) or (exists (e0 = floor((-1 + b8)/2), e1 = floor((11 + 8b8 + 15i0)/16): p_0 = 0 and p_1 = 0 and i1 = 5 and 2e0 = -1 + b8 and b8 > 0 and i0 <= 2945 and i0 <= 115 + 64b8 and i2 >= -1 and 16i2 >= -67 - 64b8 + i0 and 16i2 <= -20 - 64b8 + i0 and 16e1 >= 4 + 8b8 + 15i0 and 16e1 <= 11 + 8b8 + 15i0)) or "
		"(exists (e0 = floor((b8)/2), e1 = floor((11 + 15i0)/16): p_1 = 0 and i1 = 5 and 2e0 = b8 and p_0 > 0 and b8 >= 0 and i0 >= 60 + 64b8 and 16i2 <= -76 - 64b8 + i0 and 16e1 >= 4 + 15i0 and 16e1 <= 11 + 15i0 and i0 <= 171 + 64b8)) or (exists (e0 = floor((11 + 15i0)/16), e1 = floor((12 + 8b8 + i0)/16): p_0 = 0 and p_1 = 0 and i1 = 5 and 2e1 = 1 + b8 + 2i0 - 2e0 and b8 > 0 and i0 >= 60 + 64b8 and i0 <= 2945 and i0 <= 123 + 64b8 and 16e0 >= -4 + 15i0 and 16e0 <= 3 + 15i0 and 16i2 <= -76 - 64b8 + i0)) or "
		"(exists (e0 = floor((b8)/2), e1 = floor((11 + 15i0)/16): p_0 = 0 and p_1 = 0 and 2e0 = b8 and b8 >= 0 and i0 >= 60 + 64b8 and i0 <= 2945 and i0 <= 171 + 64b8 and i1 <= 4 and 16e1 >= 4 + 15i0 and 16e1 <= 11 + 15i0)) or "
		"(exists (e0 = floor((-1 + b8)/2), e1 = floor((11 + 8b8 + 15i0)/16): p_1 = 0 and i1 = 5 and 2e0 = -1 + b8 and p_0 < 0 and b8 > 0 and i0 >= 4 + 64b8 and i0 <= 51 + 64b8 and i2 <= -2 and 16e1 >= 4 + 8b8 + 15i0 and 16e1 <= 11 + 8b8 + 15i0)) or (exists (e0 = floor((-1 + b8)/2), e1 = floor((11 + 8b8 + 15i0)/16): p_1 = 0 and i1 = 5 and 2e0 = -1 + b8 and p_0 > 0 and b8 > 0 and i0 >= 4 + 64b8 and i0 <= 51 + 64b8 and i2 <= -2 and 16e1 >= 4 + 8b8 + 15i0 and 16e1 <= 11 + 8b8 + 15i0)) or "
		"(exists (e0 = floor((51 - 104b8 - i0 - 96i2)/112): p_0 = 0 and p_1 = 0 and i1 = 5 and i0 >= 2948 and i2 >= 0 and i2 <= 7 and 2e0 >= -2 - 3b8 - 2i2 and 2e0 < -3b8 - 2i2 and 112e0 >= -60 - 104b8 - i0 - 96i2 + i3 and 112e0 >= -60 - 104b8 - i0 - 96i2 and 112e0 <= -53 - 104b8 - i0 - 96i2)) or "
		"(exists (e0 = floor((b8)/2): p_0 = 0 and p_1 = 0 and i1 = 5 and 2e0 >= -1 + b8 and b8 >= 0 and i0 <= 2945 and i2 >= -1 and i2 <= 6 and 112e0 >= -75 - 8b8 + i0 - 16i2 and 2e0 <= b8 and 112e0 <= -68 - 8b8 + i0 - 16i2)) or (exists (e0 = floor((-1 + b8)/2), e1 = floor((11 + 8b8 + 15i0)/16): p_1 = 0 and i1 = 5 and 2e0 = -1 + b8 and p_0 < 0 and b8 > 0 and i0 <= 115 + 64b8 and i2 >= -1 and 16i2 >= -67 - 64b8 + i0 and 16i2 <= -20 - 64b8 + i0 and 16e1 >= 4 + 8b8 + 15i0 and 16e1 <= 11 + 8b8 + 15i0)) or (exists (e0 = floor((-1 + b8)/2), e1 = floor((11 + 8b8 + 15i0)/16): p_1 = 0 and i1 = 5 and 2e0 = -1 + b8 and p_0 > 0 and b8 > 0 and i0 <= 115 + 64b8 and i2 >= -1 and 16i2 >= -67 - 64b8 + i0 and 16i2 <= -20 - 64b8 + i0 and 16e1 >= 4 + 8b8 + 15i0 and 16e1 <= 11 + 8b8 + 15i0)) or "
		"(exists (e0 = floor((51 - 104b8 - i0 - 96i2)/112): p_0 = 0 and p_1 = 0 and i1 = 5 and b8 >= 0 and i0 <= 2945 and i2 >= 0 and i2 <= 7 and 2e0 >= -2 - 3b8 - 2i2 and 2e0 < -3b8 - 2i2 and 112e0 >= -60 - 104b8 - i0 - 96i2 + i3 and 112e0 >= -60 - 104b8 - i0 - 96i2 and 112e0 <= -53 - 104b8 - i0 - 96i2)) or (p_0 = 0 and p_1 = 0 and b8 = 45 and i1 = 5 and i2 = 4 and i0 >= 2946 and i0 <= 2947 and i3 <= -2940 + i0) or (p_0 = 0 and p_1 = 0 and b8 = 45 and i1 = 5 and i0 >= 2946 and i0 <= 2947 and i2 <= 3) "
#endif
		"}"
	));
	Test.dump();
	auto R = isl_union_map_is_single_valued(Test.keep()) ;
	Test.dump();
	EXPECT_NE(R, isl_bool_error);

}

} // anonymous namespace
