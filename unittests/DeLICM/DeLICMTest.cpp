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
      true, true,
      "{ [A[] -> Def1[]] -> [i] : 0 <= i <= 10; [A[] -> "
      "Def2[]] -> [i] : 20 <= i }"));

  EXPECT_TRUE(checkComputeArrayLifetime(
      "{ Def1[] -> [0]; Def2[] -> [10]; Read[] -> [10] }",
      "{ Def1[] -> A[]; Def2[] -> A[] }", "{ Read[] -> A[] }", false, true,
      true, true,
      "{ [A[] -> Def1[]] -> [i] : 0 <= i <= 10; [A[] -> "
      "Def2[]] -> [i] : 10 <= i }"));
  EXPECT_TRUE(checkComputeArrayLifetime(
      "{ Def1[] -> [0]; Def2[] -> [10]; Read[] -> [10] }",
      "{ Def1[] -> A[]; Def2[] -> A[] }", "{ Read[] -> A[] }", true, true, true,
      true, "{ [A[] -> Def2[]] -> [i] : 10 <= i }"));
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
} // anonymous namespace
