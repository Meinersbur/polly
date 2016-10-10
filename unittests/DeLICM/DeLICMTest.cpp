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

#define indef                                                                  \
  (-1) /* For test cases where the true/false value should have no effect on   \
          the outcome. */

#define BOOL_FOR(VAR)                                                          \
  for (int VAR##_iter = (VAR == indef) ? 0 : VAR;                              \
       VAR##_iter <= ((VAR == indef) ? 1 : VAR); VAR##_iter += 1)              \
    for (bool VAR = VAR##_iter, VAR##_repeat = true; VAR##_repeat;             \
         VAR##_repeat = false)

namespace {

void computeReachingDefinitionZone_check(const char *ScheduleStr,
                                         const char *DefsStr, int IncludeDef,
                                         int IncludeRedef,
                                         const char *ExpectedStr) {
  BOOL_FOR(IncludeDef)
  BOOL_FOR(IncludeRedef) {
    auto *Ctx = isl_ctx_alloc();

    {
      auto Schedule = give(isl_union_map_read_from_str(Ctx, ScheduleStr));
      auto Defs = give(isl_union_map_read_from_str(Ctx, DefsStr));
      auto Expected = give(isl_union_map_read_from_str(Ctx, ExpectedStr));

      auto Result =
          computeReachingDefinition(Schedule, Defs, IncludeDef, IncludeRedef);

      auto Success = isl_union_map_is_equal(Result.keep(), Expected.keep());
      assert(isl_bool_true == Success);
      EXPECT_EQ(isl_bool_true, Success);
    }

    isl_ctx_free(Ctx);
  }
}

TEST(DeLICM, ReachingDefinitionZone) {
  EXPECT_FALSE(computeReachingDefinition(nullptr, nullptr, false, false));

  computeReachingDefinitionZone_check("{ Dom[] -> [0] }", "{ Dom[] -> Elt[] }",
                                      true, indef,
                                      "{ [Elt[] -> [i]] -> Dom[] : 0 <= i }");
  computeReachingDefinitionZone_check("{ Dom[] -> [0] }", "{ Dom[] -> Elt[] }",
                                      false, indef,
                                      "{ [Elt[] -> [i]] -> Dom[] : 0 < i }");

  computeReachingDefinitionZone_check(
      "{ Dom1[] -> [0]; Dom2[] -> [10] }",
      "{ Dom1[] -> Elt[]; Dom2[] -> Elt[] }", true, false,
      "{ [Elt[] -> [i]] -> Dom1[] : 0 <= i < 10; [Elt[] -> [i]] -> Dom2[] : 10 "
      "<= i }");
  computeReachingDefinitionZone_check(
      "{ Dom1[] -> [0]; Dom2[] -> [10] }",
      "{ Dom1[] -> Elt[]; Dom2[] -> Elt[] }", false, false,
      "{ [Elt[] -> [i]] -> Dom1[] : 0 < i < 10; [Elt[] -> [i]] -> Dom2[] : 10 "
      "< i }");
  computeReachingDefinitionZone_check("{ Dom1[] -> [0]; Dom2[] -> [10] }",
                                      "{ Dom1[] -> Elt[]; Dom2[] -> Elt[] }",
                                      false, true, "{ [Elt[] -> [i]] -> Dom1[] "
                                                   ": 0 < i <= 10; [Elt[] -> "
                                                   "[i]] -> Dom2[] : 10 < i }");
  computeReachingDefinitionZone_check("{ Dom1[] -> [0]; Dom2[] -> [10] }",
                                      "{ Dom1[] -> Elt[]; Dom2[] -> Elt[] }",
                                      true, true, "{ [Elt[] -> [i]] -> Dom1[] "
                                                  ": 0 <= i <= 10; [Elt[] -> "
                                                  "[i]] -> Dom2[] : 10 <= i }");

  computeReachingDefinitionZone_check("{ Dom1[] -> [0]; Dom2[] -> [10] }",
                                      "{ Dom1[] -> Elt1[]; Dom2[] -> Elt2[] }",
                                      true, indef,
                                      "{ [Elt1[] -> [i]] -> Dom1[] : 0 <= i; "
                                      "[Elt2[] -> [i]] -> Dom2[] : 10 <= i }");

  computeReachingDefinitionZone_check(
      "{ Dom[i] -> [i] }", "{ Dom[i] -> Elt[]; Dom2[] -> Elt[] }", true, false,
      "{ [Elt[] -> [i]] -> Dom[i] }");

  computeReachingDefinitionZone_check("{ Dom[1] -> [0]; Dom[2] -> [10] }",
                                      "{ Dom[1] -> Elt[]; Dom[2] -> Elt[] }",
                                      false, true, "{ [Elt[] -> [i]] -> Dom[1] "
                                                   ": 0 < i <= 10; [Elt[] -> "
                                                   "[i]] -> Dom[2] : 10 < i }");

  computeReachingDefinitionZone_check(
      "{ Stmt_reduction_for[i] -> [3i] : 0 <= i <= 4 }",
      "{ Stmt_reduction_for[i] -> Elt[] : 0 <= i <= 4 }", false, true,
      "{ [Elt[] -> [i]] -> Stmt_reduction_for[0] : 0 < i <= 3; [Elt[] -> [i]] "
      "-> Stmt_reduction_for[1] : 3 < i <= 6; [Elt[] -> [i]] -> "
      "Stmt_reduction_for[2] : 6 < i <= 9; [Elt[] -> [i]] -> "
      "Stmt_reduction_for[3] : 9 < i <= 12; [Elt[] -> [i]] -> "
      "Stmt_reduction_for[4] : 12 < i }");
}

void checkComputeArrayLifetime(const char *ScheduleStr ,
                                  const char *WritesStr, const char *ReadsStr,
                                  int ReadEltInSameInst, int InclWrite,
                                  int InclLastRead, int ExitReads, const char *ExpectedStr) {
	  BOOL_FOR(ReadEltInSameInst) BOOL_FOR(InclWrite) BOOL_FOR(InclLastRead) BOOL_FOR(ExitReads) {
    isl_ctx *Ctx = isl_ctx_alloc();

    {
      auto Schedule = give(isl_union_map_read_from_str(Ctx, ScheduleStr));
      auto Writes = give(isl_union_map_read_from_str(Ctx, WritesStr));
      auto Reads = give(isl_union_map_read_from_str(Ctx, ReadsStr));
      auto Expected = give(isl_union_map_read_from_str(Ctx, ExpectedStr));

      auto Result = computeArrayLifetime(Schedule, Writes, Reads, ReadEltInSameInst,InclWrite, InclLastRead, ExitReads);
      auto Success = isl_union_map_is_equal(Result.keep(), Expected.keep());

      EXPECT_EQ(isl_bool_true, Success);
    }

    isl_ctx_free(Ctx);
  }
}

TEST(DeLICM, ArrayPerWriteLifetimeZone) {
	checkComputeArrayLifetime("{ }","{ }", "{ }", indef, indef, indef, indef, "{ }");
	checkComputeArrayLifetime("{ Read[] -> [10] }","{ Read[] -> A[] }", "{ }", indef, indef, indef, false, "{ }");

	checkComputeArrayLifetime("{ Def[] -> [10] }","{ Def[] -> A[] }", "{ }", indef, indef, indef, false, "{ }");
	checkComputeArrayLifetime("{ Def[] -> [10] }","{ Def[] -> A[] }", "{ }", indef, false, indef, true, "{ [A[] -> Def[]] -> [i] : 10 < i }");
	checkComputeArrayLifetime("{ Def[] -> [10] }","{ Def[] -> A[] }", "{ }", indef, true, indef, true, "{ [A[] -> Def[]] -> [i] : 10 <= i }");

	checkComputeArrayLifetime("{ Def[] -> [10]; Read[] -> [20] }","{ Def[] -> A[] }", "{ Read[] -> A[] }",indef, false, false,  false, "{ [A[] -> Def[]] -> [i] : 10 < i < 20 }");
	checkComputeArrayLifetime("{ Def[] -> [10]; Read[] -> [20] }","{ Def[] -> A[] }", "{ Read[] -> A[] }", indef,true, false,  false, "{ [A[] -> Def[]] -> [i] : 10 <= i < 20 }");
	checkComputeArrayLifetime("{ Def[] -> [10]; Read[] -> [20] }","{ Def[] -> A[] }", "{ Read[] -> A[] }",indef, false, true,  false, "{ [A[] -> Def[]] -> [i] : 10 < i <= 20 }");
	checkComputeArrayLifetime("{ Def[] -> [10]; Read[] -> [20] }","{ Def[] -> A[] }", "{ Read[] -> A[] }",indef, true, true,  false, "{ [A[] -> Def[]] -> [i] : 10 <= i <= 20 }");
	checkComputeArrayLifetime("{ Def[] -> [10]; Read[] -> [20] }","{ Def[] -> A[] }", "{ Read[] -> A[] }", indef, false, indef, true, "{ [A[] -> Def[]] -> [i] : 10 < i }");
	checkComputeArrayLifetime("{ Def[] -> [10]; Read[] -> [20] }","{ Def[] -> A[] }", "{ Read[] -> A[] }", indef, true, indef, true, "{ [A[] -> Def[]] -> [i] : 10 <= i }");

	checkComputeArrayLifetime("{ Def[] -> [10]; Read1[] -> [20]; Read2[] -> [30] }","{ Def[] -> A[] }", "{ Read1[] -> A[]; Read2[] -> A[] }",indef, true, indef,  true, "{ [A[] -> Def[]] -> [i] : 10 <= i }");
	checkComputeArrayLifetime("{ Def[] -> [10]; Read1[] -> [20]; Read2[] -> [30] }","{ Def[] -> A[] }", "{ Read1[] -> A[]; Read2[] -> A[] }", indef, true, true, false, "{ [A[] -> Def[]] -> [i] : 10 <= i <= 30 }");

	checkComputeArrayLifetime("{ Def1[] -> [0]; Read[] -> [10]; Def2[] -> [20] }","{ Def1[] -> A[]; Def2[] -> A[] }", "{ Read[] -> A[] }", indef,  true, true,  false,  "{ [A[] -> Def1[]] -> [i] : 0 <= i <= 10 }");
	checkComputeArrayLifetime("{ Def1[] -> [0]; Read[] -> [10]; Def2[] -> [20] }","{ Def1[] -> A[]; Def2[] -> A[] }", "{ Read[] -> A[] }", indef,  true, true,  true,  "{ [A[] -> Def1[]] -> [i] : 0 <= i <= 10; [A[] -> Def2[]] -> [i] : 20 <= i }");

	checkComputeArrayLifetime("{ Def1[] -> [0]; Def2[] -> [10]; Read[] -> [10] }","{ Def1[] -> A[]; Def2[] -> A[] }", "{ Read[] -> A[] }", false,  true, true,  true,  "{ [A[] -> Def1[]] -> [i] : 0 <= i <= 10; [A[] -> Def2[]] -> [i] : 10 <= i }");
	checkComputeArrayLifetime("{ Def1[] -> [0]; Def2[] -> [10]; Read[] -> [10] }","{ Def1[] -> A[]; Def2[] -> A[] }", "{ Read[] -> A[] }", true,   true, true,  true, "{ [A[] -> Def2[]] -> [i] : 10 <= i }");
}

void computeReachingOverwriteZone_check(const char *ScheduleStr,
                                        const char *DefsStr,
                                        int IncludePrevWrite,
                                        int IncludeOverwrite,
                                        const char *ExpectedStr) {
  BOOL_FOR(IncludePrevWrite)
  BOOL_FOR(IncludeOverwrite) {
    isl_ctx *Ctx = isl_ctx_alloc();
    {
      auto Schedule = give(isl_union_map_read_from_str(Ctx, ScheduleStr));
      auto Defs = give(isl_union_map_read_from_str(Ctx, DefsStr));
      auto Expected = give(isl_union_map_read_from_str(Ctx, ExpectedStr));

      auto Result = computeReachingOverwrite(Schedule, Defs, IncludePrevWrite,
                                             IncludeOverwrite);
      auto Success = isl_union_map_is_equal(Result.keep(), Expected.keep());

      EXPECT_EQ(isl_bool_true, Success);
    }

    isl_ctx_free(Ctx);
  }
}

TEST(DeLICM, ReachingOverwriteZone) {
  computeReachingOverwriteZone_check("{ Write[] -> [0] }",
                                     "{ Write[] -> Elt[] }", indef, false,
                                     "{ [Elt[] -> [i]] -> Write[] :  i < 0 }");
  computeReachingOverwriteZone_check("{ Write[] -> [0] }",
                                     "{ Write[] -> Elt[] }", indef, true,
                                     "{ [Elt[] -> [i]] -> Write[] : i <= 0 }");

  computeReachingOverwriteZone_check(
      "{ Write[0] -> [0]; Write[1] -> [10] }", "{ Write[i] -> Elt[]; }", false,
      false, "{ [Elt[] -> [i]] -> Write[0] : i < 0 ; [Elt[] -> [i]] -> "
             "Write[1] : 0 < i < 10 }");
  computeReachingOverwriteZone_check(
      "{ Write[0] -> [0]; Write[1] -> [10] }", "{ Write[i] -> Elt[]; }", false,
      true, "{ [Elt[] -> [i]] -> Write[0] : i <= 0 ; [Elt[] -> [i]] -> "
            "Write[1] : 0 < i <= 10 }");
  computeReachingOverwriteZone_check(
      "{ Write[0] -> [0]; Write[1] -> [10] }", "{ Write[i] -> Elt[]; }", true,
      false, "{ [Elt[] -> [i]] -> Write[0] : i < 0 ; [Elt[] -> [i]] -> "
             "Write[1] : 0 <= i < 10 }");
  computeReachingOverwriteZone_check(
      "{ Write[0] -> [0]; Write[1] -> [10] }", "{ Write[i] -> Elt[]; }", true,
      true, "{ [Elt[] -> [i]] -> Write[0] : i <= 0 ; [Elt[] -> [i]] -> "
            "Write[1] : 0 <= i <= 10 }");
}

void computeArrayUnusedZone_check(const char *ScheduleStr,
                                  const char *WritesStr, const char *ReadsStr,
                                  int ReadEltInSameInst, int IncludeLastRead,
                                  int IncludeWrite, const char *ExpectedStr) {
  BOOL_FOR(ReadEltInSameInst) BOOL_FOR(IncludeLastRead) BOOL_FOR(IncludeWrite) {
    isl_ctx *Ctx = isl_ctx_alloc();

    {
      auto Schedule = give(isl_union_map_read_from_str(Ctx, ScheduleStr));
      auto Writes = give(isl_union_map_read_from_str(Ctx, WritesStr));
      auto Reads = give(isl_union_map_read_from_str(Ctx, ReadsStr));
      auto Expected = give(isl_union_map_read_from_str(Ctx, ExpectedStr));

      auto Result =
          computeArrayUnused(Schedule, Writes, Reads, ReadEltInSameInst,
                             IncludeLastRead, IncludeWrite);
      auto Success = isl_union_map_is_equal(Result.keep(), Expected.keep());

      EXPECT_EQ(isl_bool_true, Success);
    }

    isl_ctx_free(Ctx);
  }
}

TEST(DeLICM, ArrayUnused) {
  computeArrayUnusedZone_check("{ Read[] -> [0]; Write[] -> [10] }",
                               "{ Write[] -> Elt[] }", "{ Read[] -> Elt[] }",
                               indef, false, false,
                               "{ Elt[] -> [i] : 0 < i < 10 }");
  computeArrayUnusedZone_check("{ Read[] -> [0]; Write[] -> [10] }",
                               "{ Write[] -> Elt[] }", "{ Read[] -> Elt[] }",
                               indef, false, true,
                               "{ Elt[] -> [i] : 0 < i <= 10 }");
  computeArrayUnusedZone_check("{ Read[] -> [0]; Write[] -> [10] }",
                               "{ Write[] -> Elt[] }", "{ Read[] -> Elt[] }",
                               indef, true, false,
                               "{ Elt[] -> [i] : 0 <= i < 10 }");
  computeArrayUnusedZone_check("{ Read[] -> [0]; Write[] -> [10] }",
                               "{ Write[] -> Elt[] }", "{ Read[] -> Elt[] }",
                               indef, true, true,
                               "{ Elt[] -> [i] : 0 <= i <= 10 }");

  computeArrayUnusedZone_check(
      "{ Read[0] -> [-10]; Read[1] -> [0]; Write[] -> [10] }",
      "{ Write[] -> Elt[] }", "{ Read[i] -> Elt[] }", indef, false, true,
      "{ Elt[] -> [i] : 0 < i <= 10 }");
  computeArrayUnusedZone_check("{ Read[] -> [0];  }", "{ }",
                               "{ Read[] -> Elt[] }", indef, indef, indef,
                               "{ }");
  computeArrayUnusedZone_check("{ Write[] -> [0];  }", "{ Write[] -> Elt[] }",
                               "{ }", indef, indef, true,
                               "{ Elt[] -> [i] : i <= 0  }");

  computeArrayUnusedZone_check("{ RW[] -> [0] }", "{ RW[] -> Elt[] }",
                               "{ RW[] -> Elt[] }", true, indef, false,
                               "{ Elt[] -> [i] : i < 0 }");
  computeArrayUnusedZone_check("{ RW[] -> [0] }", "{ RW[] -> Elt[] }",
                               "{ RW[] -> Elt[] }", true, indef, true,
                               "{ Elt[] -> [i] : i <= 0 }");
  computeArrayUnusedZone_check("{ RW[] -> [0] }", "{ RW[] -> Elt[] }",
                               "{ RW[] -> Elt[] }", false, true, true,
                               "{ Elt[] -> [0] }");
}

IslPtr<isl_union_map> emptyUMap(isl_ctx *Ctx) {
  return give(isl_union_map_empty(isl_space_params_alloc(Ctx, 0)));
}
IslPtr<isl_union_set> emptyUSet(isl_ctx *Ctx) {
  return give(isl_union_set_empty(isl_space_params_alloc(Ctx, 0)));
}

void isConflicting_check(const char *ThisKnownStr, const char *ThisUndefStr,
                         const char *ThisWrittenStr, const char *ThatKnownStr,
                         const char *ThatUnknownStr, const char *ThatWrittenStr,
                         bool Expected) {
  isl_ctx *Ctx = isl_ctx_alloc();
  LLVMContext C;

  {
    auto ThisKnown = ThisKnownStr
                         ? give(isl_union_map_read_from_str(Ctx, ThisKnownStr))
                         : emptyUMap(Ctx);
    auto ThisUndef = ThisUndefStr
                         ? give(isl_union_set_read_from_str(Ctx, ThisUndefStr))
                         : emptyUSet(Ctx);
    auto ThisWritten =
        ThisWrittenStr ? give(isl_union_map_read_from_str(Ctx, ThisWrittenStr))
                       : emptyUMap(Ctx);

    auto ThatKnown = ThatKnownStr
                         ? give(isl_union_map_read_from_str(Ctx, ThatKnownStr))
                         : emptyUMap(Ctx);
    auto ThatUnknown =
        ThatUnknownStr ? give(isl_union_set_read_from_str(Ctx, ThatUnknownStr))
                       : emptyUSet(Ctx);
    auto ThatWritten =
        ThatWrittenStr ? give(isl_union_map_read_from_str(Ctx, ThatWrittenStr))
                       : emptyUMap(Ctx);

    auto UndefVal = UndefValue::get(IntegerType::get(C, 8));
    auto UndefId = give(isl_id_alloc(Ctx, "Undef", UndefVal));
    auto UndefSpace = give(isl_space_set_alloc(Ctx, 0, 0));
    UndefSpace = give(
        isl_space_set_tuple_id(UndefSpace.take(), isl_dim_set, UndefId.take()));
    auto UndefSet = give(isl_set_universe(UndefSpace.take()));
    auto UndefUSet = give(isl_union_set_from_set(UndefSet.take()));

    auto UnknownSpace = give(isl_space_set_alloc(Ctx, 0, 0));
    auto UnknownSet = give(isl_set_universe(UnknownSpace.take()));
    auto UnknownUSet = give(isl_union_set_from_set(UnknownSet.take()));

    auto ThisLifetime = give(isl_union_map_union(
        ThisKnown.take(), isl_union_map_from_domain_and_range(
                              ThisUndef.take(), UndefUSet.take())));
    auto ThatLifetime = give(isl_union_map_union(
        ThatKnown.take(), isl_union_map_from_domain_and_range(
                              ThatUnknown.take(), UnknownUSet.take())));

    auto Result = polly::isConflicting(ThisLifetime, true, ThisWritten,
                                       ThatLifetime, false, ThatWritten);

    EXPECT_EQ(Expected, Result);
  }

  isl_ctx_free(Ctx);
}

void isConflicting_checksymmetric(const char *ThisKnownStr,
                                  const char *ThisWrittenStr,
                                  const char *ThatKnownStr,
                                  const char *ThatWrittenStr, bool Expected) {
  isConflicting_check(ThisKnownStr, nullptr, ThisWrittenStr, ThatKnownStr,
                      nullptr, ThatWrittenStr, Expected);
  isConflicting_check(ThatKnownStr, nullptr, ThatWrittenStr, ThisKnownStr,
                      nullptr, ThisWrittenStr, Expected);
}

TEST(DeLICM, IsConflicting) {
  isConflicting_check(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                      false);
  isConflicting_check(nullptr, nullptr, "{ Dom[0] -> Val[] }", nullptr, nullptr,
                      nullptr, false);
  isConflicting_check(nullptr, nullptr, "{ Dom[0] -> [] }", nullptr, nullptr,
                      nullptr, false);
  isConflicting_checksymmetric("{ Dom[0] -> Val[] }", nullptr,
                               "{ Dom[0] -> Val[] }", nullptr, false);
  // computeArrayUnusedZone_checksymmetric("{ Dom[i] -> Val[] : 0 < i < 10 }",
  // nullptr, nullptr,  "{ Dom[0] -> [] }", false );
  isConflicting_check("{ Dom[i] -> Val[] : 0 < i  }", "{ Dom[i] : i <= 0 }",
                      nullptr, nullptr, nullptr, "{ Dom[-1] -> [] }", false);
  isConflicting_check("{ Dom[i] -> Val[] : i <= 10 }", "{ Dom[i] :  10  < i }",
                      nullptr, nullptr, nullptr, "{ Dom[10] -> [] }", false);
  isConflicting_check(nullptr, "{ Dom[0] }", nullptr, "{ Dom[0] -> Val[] }",
                      nullptr, nullptr, false);
  isConflicting_check(nullptr, "{ Dom[i] }", nullptr, nullptr, nullptr,
                      "{ Dom[0] -> Val[] }", false);
  isConflicting_check(nullptr, "{ Dom[i] }", "{ Dom[0] -> [] }", nullptr,
                      nullptr, "{ Dom[0] -> Val[] }", false);
  isConflicting_check(nullptr, "{ Dom[i] }", "{ Dom[0] -> Val[] }", nullptr,
                      nullptr, "{ Dom[0] -> Val[] }", false);
  isConflicting_check(nullptr, "{ Dom[i] }", "{ Dom[0] -> Val[] }",
                      "{ Dom[i] -> Val[] }", nullptr, nullptr, false);

  isConflicting_checksymmetric("{ Dom[0] -> ValA[] }", nullptr,
                               "{ Dom[0] -> ValB[] }", nullptr, true);
  isConflicting_check("{ Dom[0] -> Val[] }", nullptr, nullptr, nullptr,
                      "{ Dom[0] }", nullptr, true);
  isConflicting_check(nullptr, nullptr, nullptr, "{ Dom[] -> Val[] }", nullptr,
                      nullptr, true);

  // computeArrayUnusedZone_checksymmetric("{ Dom[i] -> Val[] : 0 < i < 10 }",
  // nullptr, nullptr,  "{ Dom[0] -> [] }", true );
  isConflicting_check("{ Dom[i] -> Val[] : 0 < i <= 10 }", nullptr, nullptr,
                      nullptr, nullptr, "{ Dom[1] -> [] }", true);
  isConflicting_check("{ Dom[i] -> Val[] : 0 < i <= 10 }", nullptr, nullptr,
                      nullptr, nullptr, "{ Dom[9] -> [] }", true);

  isConflicting_checksymmetric("{ Dom[i] -> ValA[] }", nullptr,
                               "{ Dom[i] -> ValA[] }", "{ Dom[0] -> ValB[] }",
                               true);
  isConflicting_checksymmetric("{ Dom[i] -> Val[] }", nullptr,
                               "{ Dom[i] -> Val[] }", "{ Dom[0] -> [] }", true);
  isConflicting_check("{ Dom[i] -> [] }", nullptr, nullptr, nullptr, nullptr,
                      "{ Dom[0] -> [] }", true);
  isConflicting_check(nullptr, "{ Dom[i] }", "{ Dom[0] -> [] }",
                      "{ Dom[i] -> [] }", nullptr, nullptr, true);

  isConflicting_check(nullptr, nullptr, nullptr, nullptr, nullptr,
                      "{ Dom[0] -> Val[] }", true);
  isConflicting_check(nullptr, nullptr, nullptr, nullptr, nullptr,
                      "{ Dom[0] -> [] }", true);

  isConflicting_check(nullptr, nullptr, "{ Dom[0] -> Val[] }", nullptr,
                      "{ Dom[i] }", nullptr, true);
  isConflicting_check(nullptr, nullptr, "{ Dom[0] -> [] }", nullptr,
                      "{ Dom[i] }", nullptr, true);

  isConflicting_check(nullptr, nullptr, "{ Dom[0] -> Val[] }",
                      "{ Dom[i] -> [] }", nullptr, nullptr, true);
  isConflicting_check(nullptr, nullptr, "{ Dom[0] -> [] }",
                      "{ Dom[i] -> Val[] }", nullptr, nullptr, true);
  isConflicting_check(nullptr, nullptr, "{ Dom[0] -> [] }", "{ Dom[i] -> [] }",
                      nullptr, nullptr, true);
}

} // anonymous namespace
