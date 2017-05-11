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
isl::union_set unionSpace(const isl::union_set &USet) {
  auto Result = give(isl_union_set_empty(isl_union_set_get_space(USet.keep())));
  USet.foreach_set([=, &Result](isl::set Set) -> isl::stat {
    auto Space = give(isl_set_get_space(Set.keep()));
    auto Universe = give(isl_set_universe(Space.take()));
    Result = give(isl_union_set_add_set(Result.take(), Universe.take()));
    return isl::stat::ok;
  });
  return Result;
}

void completeLifetime(isl::union_set Universe, isl::union_map OccupiedAndKnown,
                      isl::union_set &Occupied, isl::union_map &Known,
  auto ParamSpace = give(isl_union_set_get_space(Universe.keep()));

  if (Undef && !Occupied) {
  assert(!Occupied);
  Occupied = give(isl_union_set_subtract(Universe.copy(), Undef.copy()));
  }

  if (OccupiedAndKnown) {
  assert(!Known);

  Known = isl::union_map::empty(ParamSpace);

  if (!Occupied)
    Occupied = OccupiedAndKnown.domain();

  OccupiedAndKnown.foreach_map([&Known](isl::map Map) -> isl::stat {
    if (isl_map_has_tuple_name(Map.keep(), isl_dim_out) != isl_bool_true)
      return isl::stat::ok;
    Known = give(isl_union_map_add_map(Known.take(), Map.take()));
    return isl::stat::ok;
  });
  assert(Occupied);
  Undef = give(isl_union_set_subtract(Universe.copy(), Occupied.copy()));

  if (!Known) { // By default, nothing is known.
    Known = isl::union_map::empty(ParamSpace);
  }

  // Conditions that must hold when returning.
  assert(Occupied);
  assert(Undef);
  assert(Known);
} KnowledgeStr;
isl::union_set parseSetOrNull(isl_ctx *Ctx, const char *Str) {
  if (!Str)
    return nullptr;
  return isl::union_set(Ctx, Str);
}

isl::union_map parseMapOrNull(isl_ctx *Ctx, const char *Str) {
  if (!Str)
    return nullptr;
  return isl::union_map(Ctx, Str);
}

  LLVMContext C;
          ? give(isl_union_set_read_from_str(Ctx.get(), ExistingUnknownStr))
          : nullptr;
  auto ExistingUndef =
      ExistingUndefStr
          ? give(isl_union_set_read_from_str(Ctx.get(), ExistingUndefStr))
          : nullptr;
  auto ExistingWritten =
      give(isl_union_map_read_from_str(Ctx.get(), ExistingWrittenStr));
      ProposedUnknownStr
          ? give(isl_union_set_read_from_str(Ctx.get(), ProposedUnknownStr))
          : nullptr;
  auto ProposedUndef =
      ProposedUndefStr
          ? give(isl_union_set_read_from_str(Ctx.get(), ProposedUndefStr))
          : nullptr;
  auto ProposedWritten =
      give(isl_union_map_read_from_str(Ctx.get(), ProposedWrittenStr));

bool checkIsConflictingNonsymmetricCommon(
    isl_ctx *Ctx, isl::union_map ExistingOccupiedAndKnown,
    isl::union_set ExistingUnused, isl::union_map ExistingWritten,
    isl::union_map ProposedOccupiedAndKnown, isl::union_set ProposedUnused,
    isl::union_map ProposedWritten) {
  auto UndefUSet = give(isl_union_set_from_set(UndefSet.take()));
  auto Universe = give(isl_union_set_empty(isl_space_params_alloc(Ctx, 0)));
  if (ExistingOccupiedAndKnown)
    Universe = give(isl_union_set_union(
        Universe.take(), ExistingOccupiedAndKnown.domain().take()));
  Universe = give(
      isl_union_set_union(Universe.take(), ExistingWritten.domain().take()));
  if (ProposedOccupiedAndKnown)
    Universe = give(isl_union_set_union(
        Universe.take(), ProposedOccupiedAndKnown.domain().take()));
  Universe = give(
      isl_union_set_union(Universe.take(), ProposedWritten.domain().take()));

  auto ExistingDefined = give(isl_union_map_domain(ExistingKnown.copy()));
  auto ExistingLifetime = ExistingKnown;
  isl::id NewId = give(isl_id_alloc(Ctx, "Unrelated", &NewId));
  ExistingDefined =
      give(isl_union_set_union(ExistingDefined.take(), ExistingUnknown.copy()));
  auto NewSpace = give(isl_space_set_alloc(Ctx, 0, 1));
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
  isl::union_set ExistingOccupied;
  isl::union_map ExistingKnown;
  completeLifetime(Universe, ExistingOccupiedAndKnown, ExistingOccupied,
                   ExistingKnown, ExistingUnused);
    ProposedLifetime = give(
        isl_union_map_union(ProposedLifetime.take(),
                            isl_union_map_from_domain(ProposedUnknown.copy())));
} // namespace
if (ProposedUndef) {
  ProposedDefined =
      give(isl_union_set_union(ProposedDefined.take(), ProposedUndef.copy()));
  ProposedLifetime = give(isl_union_map_union(
      ProposedLifetime.take(), isl_union_map_from_domain_and_range(
                                   ProposedUndef.copy(), UndefUSet.copy())));
}

isl::union_set ProposedOccupied;
isl::union_map ProposedKnown;
completeLifetime(Universe, ProposedOccupiedAndKnown, ProposedOccupied,
                 ProposedKnown, ProposedUnused);

auto Result = isConflicting(ExistingOccupied, ExistingUnused, ExistingKnown,
                            ExistingWritten, ProposedOccupied, ProposedUnused,
                            ProposedKnown, ProposedWritten);

auto ProposedUniverse = unionSpace(ProposedDefined);
ProposedUniverse = give(isl_union_set_union(
    ProposedUniverse.take(),
    unionSpace(give(isl_union_map_domain(ProposedWritten.copy()))).take()));
            isConflicting(ExistingOccupied, ExistingUnused, ExistingKnown,
                          ExistingWritten, ProposedOccupied, {}, ProposedKnown,
                          ProposedWritten));
            isConflicting({}, ExistingUnused, ExistingKnown, ExistingWritten,
                          ProposedOccupied, ProposedUnused, ProposedKnown,
                          ProposedWritten));
            EXPECT_EQ(Result,
                      isConflicting({}, ExistingUnused, ExistingKnown,
                                    ExistingWritten, ProposedOccupied, {},
                                    ProposedKnown, ProposedWritten));

            // The 'universe' contains all statement instances; because there is
            // no isl_union_set_universe, we derive it from all statement
            // domains passes ti this function.
            auto Universe = give(isl_union_set_union(ExistingUniverse.take(),
                                                     ProposedUniverse.take()));

            // If the user did not specify the Existing Undef zone, assume it to
            // be the complement of all specified zones. The Existing's Unknown
            // zone is already assumed to be implicit by isConflicting().
            if (!ExistingUndefStr)
              ExistingLifetime = give(isl_union_map_union(
                  ExistingLifetime.take(),
                  isl_union_map_from_domain_and_range(
                      isl_union_set_subtract(Universe.copy(),
                                             ExistingDefined.copy()),
                      UndefUSet.copy())));

            // If the user did not specify the Proposed Unknown zone, assume it
            // to be the complement of all specified zones. The Proposed's
            // Unknown zone is already assumed to be implicit by
            // isConflicting().
            if (!ProposedUnknownStr)
              ProposedLifetime = give(isl_union_map_union(
                  ProposedLifetime.take(),
                  isl_union_map_from_domain(isl_union_set_subtract(
                      Universe.copy(), ProposedDefined.copy()))));

            return isConflicting(ExistingLifetime, true, ExistingWritten,
                                 ProposedLifetime, false, ProposedWritten);
            }

            bool checkIsConflictingNonsymmetricKnown(KnowledgeStr Existing,
                                                     KnowledgeStr Proposed) {
              std::unique_ptr<isl_ctx, decltype(&isl_ctx_free)> Ctx(
                  isl_ctx_alloc(), &isl_ctx_free);

              // Parse knowledge.
              auto ExistingOccupiedAndKnown =
                  parseMapOrNull(Ctx.get(), Existing.OccupiedStr);
              auto ExistingUnused =
                  parseSetOrNull(Ctx.get(), Existing.UndefStr);
              auto ExistingWritten =
                  parseMapOrNull(Ctx.get(), Existing.WrittenStr);

              auto ProposedOccupiedAndKnown =
                  parseMapOrNull(Ctx.get(), Proposed.OccupiedStr);
              auto ProposedUnused =
                  parseSetOrNull(Ctx.get(), Proposed.UndefStr);
              auto ProposedWritten =
                  parseMapOrNull(Ctx.get(), Proposed.WrittenStr);

              return checkIsConflictingNonsymmetricCommon(
                  Ctx.get(), ExistingOccupiedAndKnown, ExistingUnused,
                  ExistingWritten, ProposedOccupiedAndKnown, ProposedUnused,
                  ProposedWritten);
            }

            bool checkIsConflictingNonsymmetric(KnowledgeStr Existing,
                                                KnowledgeStr Proposed) {
              std::unique_ptr<isl_ctx, decltype(&isl_ctx_free)> Ctx(
                  isl_ctx_alloc(), &isl_ctx_free);

              // Parse knowledge.
              auto ExistingOccupied =
                  parseSetOrNull(Ctx.get(), Existing.OccupiedStr);
              auto ExistingUnused =
                  parseSetOrNull(Ctx.get(), Existing.UndefStr);
              auto ExistingWritten =
                  parseSetOrNull(Ctx.get(), Existing.WrittenStr);

              auto ProposedOccupied =
                  parseSetOrNull(Ctx.get(), Proposed.OccupiedStr);
              auto ProposedUnused =
                  parseSetOrNull(Ctx.get(), Proposed.UndefStr);
              auto ProposedWritten =
                  parseSetOrNull(Ctx.get(), Proposed.WrittenStr);

              return checkIsConflictingNonsymmetricCommon(
                  Ctx.get(),
                  isl::manage(
                      isl_union_map_from_domain(ExistingOccupied.take())),
                  ExistingUnused,
                  isl::manage(
                      isl_union_map_from_domain(ExistingWritten.take())),
                  isl::manage(
                      isl_union_map_from_domain(ProposedOccupied.take())),
                  ProposedUnused,
                  isl::manage(
                      isl_union_map_from_domain(ProposedWritten.take())));
            }

            bool checkIsConflicting(KnowledgeStr Existing,
                                    KnowledgeStr Proposed) {

              // isConflicting should be symmetric.
              EXPECT_EQ(ThisExisting, ThatExisting);

              return ThisExisting || ThatExisting;
            }

            bool checkIsConflictingKnown(KnowledgeStr Existing,
                                         KnowledgeStr Proposed) {
              auto Forward =
                  checkIsConflictingNonsymmetricKnown(Existing, Proposed);
              auto Backward =
                  checkIsConflictingNonsymmetricKnown(Proposed, Existing);

              // checkIsConflictingKnown should be symmetric.
              EXPECT_EQ(Forward, Backward);

              return Forward || Backward;
            }

            EXPECT_FALSE(checkIsConflicting("{}", nullptr, "{}",
                                            "{ Dom[0] -> Val[] }", "{}", "{}",
                                            nullptr, "{}"));

            // Check occupied vs. occupied with known values.
            EXPECT_FALSE(checkIsConflictingKnown(
                {"{ Dom[i] -> Val[] }", nullptr, "{}"},
                {"{ Dom[i] -> Val[] }", nullptr, "{}"}));
            EXPECT_TRUE(checkIsConflictingKnown(
                {"{ Dom[i] -> ValA[] }", nullptr, "{}"},
                {"{ Dom[i] -> ValB[] }", nullptr, "{}"}));
            EXPECT_TRUE(
                checkIsConflictingKnown({"{ Dom[i] -> Val[] }", nullptr, "{}"},
                                        {"{ Dom[i] -> [] }", nullptr, "{}"}));
            EXPECT_FALSE(
                checkIsConflictingKnown({"{ Dom[0] -> Val[] }", nullptr, "{}"},
                                        {nullptr, "{ Dom[0] }", "{}"}));
            EXPECT_FALSE(checkIsConflictingKnown(
                {"{ Dom[i] -> Val[]; Dom[i] -> Phi[] }", nullptr, "{}"},
                {"{ Dom[i] -> Val[] }", nullptr, "{}"}));

            // An implementation using subtract would have exponential runtime
            // on patterns such as this one.
            EXPECT_TRUE(checkIsConflictingKnown(
                {"{ Dom[i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15]"
                 "-> Val[] }",
                 nullptr, "{}"},
                {"[p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,q0,"
                 "q1,q2,q3,q4,q5,q6,q7,q8,q9,q10,q11,q12,q13,q14,q15] -> {"
                 "Dom[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0] -> Val[];"
                 "Dom[p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15] "
                 "-> Val[];"
                 "Dom[q0,q1,q2,q3,q4,q5,q6,q7,q8,q9,q10,q11,q12,q13,q14,q15] "
                 "-> Val[] }",
                 "{}", "{}"}));

            EXPECT_FALSE(checkIsConflicting("{ Dom[0] -> Val[] }", nullptr,
                                            "{}", "{}", "{ Dom[0] -> Val[] }",
                                            "{}", nullptr, "{}"));

            EXPECT_FALSE(checkIsConflicting("{ Dom[i] -> Val[] : 0 < i  }",
                                            nullptr, "{ Dom[i] : i <= 0 }",
                                            "{}", "{}", "{}", nullptr,
                                            "{ Dom[-1] -> [] }"));

            // Check occupied vs. written with known values.
            EXPECT_FALSE(checkIsConflictingKnown(
                {"{ Dom[i] -> Val[] }", nullptr, "{}"},
                {"{}", nullptr, "{ Dom[0] -> Val[] }"}));
            EXPECT_TRUE(checkIsConflictingKnown(
                {"{ Dom[i] -> ValA[] }", nullptr, "{}"},
                {"{}", nullptr, "{ Dom[0] -> ValB[] }"}));
            EXPECT_TRUE(
                checkIsConflictingKnown({"{ Dom[i] -> Val[] }", nullptr, "{}"},
                                        {"{}", nullptr, "{ Dom[0] -> [] }"}));
            EXPECT_TRUE(checkIsConflictingKnown(
                {"{ Dom[i] -> [] }", nullptr, "{}"},
                {"{}", nullptr, "{ Dom[0] -> Val[] }"}));

            // The same value can be known under multiple names, for instance a
            // PHINode has the same value as one of the incoming values. One
            // matching pair suffices.
            EXPECT_FALSE(checkIsConflictingKnown(
                {"{ Dom[i] -> Val[]; Dom[i] -> Phi[] }", nullptr, "{}"},
                {"{}", nullptr, "{ Dom[0] -> Val[] }"}));
            EXPECT_FALSE(checkIsConflictingKnown(
                {"{ Dom[i] -> Val[] }", nullptr, "{}"},
                {"{}", nullptr, "{ Dom[0] -> Val[]; Dom[0] -> Phi[] }"}));

            EXPECT_TRUE(checkIsConflicting("{ Dom[0] -> Val[] }", nullptr, "{}",
                                           "{}", "{}", "{ Dom[0] }", nullptr,
                                           "{}"));

            EXPECT_TRUE(checkIsConflicting("{}", nullptr, "{}", "{}",
                                           "{ Dom[] -> Val[] }", "{}", nullptr,
                                           "{}"));

  EXPECT_TRUE(checkIsConflicting("{ Dom[i] -> Val[] : 0 < i <= 10 }", nullptr,

  // Check written vs. written with known values.
  EXPECT_FALSE(checkIsConflictingKnown({"{}", nullptr, "{ Dom[0] -> Val[] }"},
                                       {"{}", nullptr, "{ Dom[0] -> Val[] }"}));
  EXPECT_TRUE(checkIsConflictingKnown({"{}", nullptr, "{ Dom[0] -> ValA[] }"},
                                      {"{}", nullptr, "{ Dom[0] -> ValB[] }"}));
  EXPECT_TRUE(checkIsConflictingKnown({"{}", nullptr, "{ Dom[0] -> Val[] }"},
                                      {"{}", nullptr, "{ Dom[0] -> [] }"}));
  EXPECT_FALSE(checkIsConflictingKnown(
      {"{}", nullptr, "{ Dom[0] -> Val[]}"},
      {"{}", nullptr, "{ Dom[0] -> Val[]; Dom[0] -> Phi[] }"}));
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
