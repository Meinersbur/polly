//===------ Simplify.cpp ----------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Simplify a SCoP by removing unnecessary statements and accesses.
//
//===----------------------------------------------------------------------===//

#include "polly/Simplify.h"
#include "polly/ScopInfo.h"
#include "polly/ScopPass.h"
#include "polly/Support/GICHelper.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/Debug.h"
#define DEBUG_TYPE "polly-simplify"

using namespace llvm;
using namespace polly;

namespace {

STATISTIC(ScopsProcessed, "Number of SCoPs processed");
STATISTIC(ScopsModified, "Number of SCoPs simplified");

STATISTIC(PairUnequalAccRels, "Number of Load-Store pairs NOT removed because "
                              "of different access relations");
STATISTIC(InBetweenStore, "Number of Load-Store pairs NOT removed because "
                          "there is another store between them");
STATISTIC(TotalIdenticalWritesRemoved,
          "Number of double writes removed in any SCoP");
STATISTIC(TotalOverwritesRemoved, "Number of overwrites removed in any SCoP");
STATISTIC(TotalRedundantWritesRemoved,
          "Number of writes of same value removed in any SCoP");
STATISTIC(TotalStmtsRemoved, "Number of statements removed in any SCoP");

/// Find the llvm::Value that is written by a MemoryAccess. Return nullptr if
/// there is no such unique value.
static Value *getWrittenScalar(MemoryAccess *WA) {
  assert(WA->isWrite());

  if (WA->isOriginalAnyPHIKind()) {
    Value *Result = nullptr;
    for (auto Incoming : WA->getIncoming()) {
      assert(Incoming.second);

      if (!Result) {
        Result = Incoming.second;
        continue;
      }

      if (Result == Incoming.second)
        continue;

      return nullptr;
    }
    return Result;
  }

  return WA->getAccessInstruction();
}

static void
visitInOrder(ScopStmt *Stmt, bool VisitImplicitReads, bool VisitExplicit,
             bool VisitImplicitWrites,
             const std::function<void(MemoryAccess *, bool)> &Func) {
  if (VisitImplicitReads) {
    for (auto *MA : *Stmt)
      if (MA->isRead() && MA->isOriginalScalarKind())
        Func(MA, true);
  }

  if (VisitExplicit) {
    for (auto *MA : *Stmt)
      if (MA->isOriginalArrayKind())
        Func(MA, false);
  }

  if (VisitImplicitWrites) {
    for (auto *MA : *Stmt)
      if (MA->isWrite() && MA->isOriginalScalarKind())
        Func(MA, true);
  }
}

static void sortByExecutionOrder(ScopStmt *Stmt,
                                 SmallVectorImpl<MemoryAccess *> &Accesses) {
  Accesses.clear();

  for (auto *MA : *Stmt)
    if (MA->isRead() && MA->isOriginalScalarKind())
      Accesses.push_back(MA);

  for (auto *MA : *Stmt)
    if (MA->isOriginalArrayKind())
      Accesses.push_back(MA);

  for (auto *MA : *Stmt)
    if (MA->isWrite() && MA->isOriginalScalarKind())
      Accesses.push_back(MA);
}

static bool isImplicitRead(MemoryAccess *MA) {
  return MA->isRead() && MA->isOriginalScalarKind();
}
static bool isExplicitAccess(MemoryAccess *MA) {
  return MA->isOriginalArrayKind();
}
static bool isImplicitWrite(MemoryAccess *MA) {
  return MA->isWrite() && MA->isOriginalScalarKind();
}

static auto accessesInOrder(ScopStmt *Stmt) -> decltype(concat<MemoryAccess *>(
    make_filter_range(make_range(Stmt->begin(), Stmt->end()), isImplicitRead),
    make_filter_range(make_range(Stmt->begin(), Stmt->end()), isExplicitAccess),
    make_filter_range(make_range(Stmt->begin(), Stmt->end()),
                      isImplicitWrite))) {
  auto AllRange = make_range(Stmt->begin(), Stmt->end());
  return concat<MemoryAccess *>(make_filter_range(AllRange, isImplicitRead),
                                make_filter_range(AllRange, isExplicitAccess),
                                make_filter_range(AllRange, isImplicitWrite));
}

static void getAccessesBetween(ScopStmt *Stmt, MemoryAccess *MA1,
                               MemoryAccess *MA2,
                               const std::function<bool(MemoryAccess *)> &Pred,
                               SmallVectorImpl<MemoryAccess *> &Accesses) {
  assert(MA1 && MA2);
  Accesses.clear();

  auto IsImplictRead1 = isImplicitRead(MA1);
  auto IsImplictRead2 = isImplicitRead(MA2);
  auto IsImplictWrite1 = isImplicitWrite(MA1);
  auto IsImplictWrite2 = isImplicitWrite(MA2);

  if (MA1 == MA2)
    return;
  if (IsImplictRead1 && IsImplictRead2)
    return;
  if (IsImplictWrite1 && IsImplictWrite2)
    return;

  bool OpenStart = IsImplictRead1 || IsImplictRead2;
  auto OpenEnd = IsImplictWrite1 || IsImplictWrite2;

  auto AllRange = make_range(Stmt->begin(), Stmt->end());
  auto ExplicitRange = make_filter_range(AllRange, isExplicitAccess);

  if (Stmt->isRegionStmt() || (OpenStart && OpenEnd)) {
    auto PredRange = make_filter_range(AllRange, Pred);
    Accesses.append(PredRange.begin(), PredRange.end());
    return;
  }

  assert(Stmt->isBlockStmt());

  bool Started = OpenStart;
  for (auto *MA : ExplicitRange) {
    if (!Started) {
      if (MA1 == MA || MA2 == MA)
        Started = true;
      continue;
    }

    if (MA1 == MA || MA2 == MA) {
      assert(!OpenEnd);
      return;
    }

    if (Pred(MA))
      Accesses.push_back(MA);
  }

  assert(OpenEnd && "End not encountered");
}

static void getAccessesBetween(ScopStmt *Stmt, MemoryAccess *MA1,
                               MemoryAccess *MA2, bool Reads, bool MustWrites,
                               bool MayWrites, isl::union_map Targets,
                               SmallVectorImpl<MemoryAccess *> &Accesses) {
  getAccessesBetween(
      Stmt, MA1, MA2,
      [=](MemoryAccess *MA) {
        if (MA->isRead() && !Reads)
          return false;
        if (MA->isMustWrite() && !MustWrites)
          return false;
        if (MA->isMayWrite() && !MayWrites)
          return false;

        auto AccRel = give(MA->getAccessRelation());
        AccRel = give(isl_map_intersect_domain(
            AccRel.take(), MA->getStatement()->getDomain()));
        AccRel = give(isl_map_intersect_params(
            AccRel.take(), MA->getStatement()->getParent()->getContext()));

        return isl_union_map_is_disjoint(isl::union_map(AccRel).keep(),
                                         Targets.keep()) != isl_bool_true;
      },
      Accesses);
}

static MemoryAccess *hasReadBetween(ScopStmt *Stmt, MemoryAccess *MA1,
                                    MemoryAccess *MA2, isl::union_map Targets) {
  SmallVector<MemoryAccess *, 4> Accesses;
  getAccessesBetween(Stmt, MA1, MA2, true, false, false, Targets, Accesses);
  if (Accesses.empty())
    return nullptr;
  return Accesses.front();
}

/// Return a write access that occurs between @p From and @p To.
///
/// In region statements the order is ignored because we cannot predict it.
///
/// @param Stmt    Statement of both writes.
/// @param From    Start looking after this access.
/// @param To      Stop looking at this access, with the access itself.
/// @param Targets Look for an access that may wrote to one of these elements.
///
/// @return A write access between @p From and @p To that writes to at least
///         one element in @p Targets.
static MemoryAccess *hasWriteBetween(ScopStmt *Stmt, MemoryAccess *MA1,
                                     MemoryAccess *MA2,
                                     isl::union_map Targets) {
  SmallVector<MemoryAccess *, 4> Accesses;
  getAccessesBetween(Stmt, MA1, MA2, false, true, true, Targets, Accesses);
  if (Accesses.empty())
    return nullptr;
  return Accesses.front();
}

class Simplify : public ScopPass {
private:
  /// The last/current SCoP that is/has been processed.
  Scop *S;

  /// Number of double writes removed from this SCoP.
  int IdenticalWritesRemoved = 0;

  int OverwritesRemoved = 0;

  /// Number of redundant writes removed from this SCoP.
  int RedundantWritesRemoved = 0;

  /// Number of unnecessary statements removed from the SCoP.
  int StmtsRemoved = 0;

  /// Return whether at least one simplification has been applied.
  bool isModified() const {
    return IdenticalWritesRemoved > 0 || OverwritesRemoved > 0 ||
           RedundantWritesRemoved > 0 || StmtsRemoved > 0;
  }

  MemoryAccess *getReadAccessForValue(ScopStmt *Stmt, llvm::Value *Val) {
    if (!isa<Instruction>(Val))
      return nullptr;

    for (auto *MA : *Stmt) {
      if (!MA->isRead())
        continue;
      if (MA->getAccessValue() != Val)
        continue;

      return MA;
    }

    return nullptr;
  }

  /// If there are two writes in the same statement that write the same value to
  /// the same location, remove one of them.
  ///
  /// This currently handles only implicit writes (writes which logically occur
  /// at the end of a statement when all StoreInst and LoadInst have been
  /// executed), to avoid interference with other memory accesses.
  ///
  /// Two implicit writes have no defined order. It can be produced by DeLICM
  /// when it determined that both write the same value.
  void removeIdenticalWrites() {
    for (auto &Stmt : *S) {
      // Delay actual removal to not invalidate iterators.
      SmallPtrSet<MemoryAccess *, 4> StoresToRemove;

      auto Domain = give(Stmt.getDomain());
      auto AccRange = accessesInOrder(&Stmt);

      // TODO: This has quadratic runtime. Accesses could be grouped by
      // getAccessValue() to avoid.
      for (auto It1 = AccRange.begin(); It1 != AccRange.end(); ++It1) {
        MemoryAccess *WA1 = *It1;

        if (!WA1->isMustWrite())
          continue;
        if (!WA1->isOriginalScalarKind())
          continue;
        if (StoresToRemove.count(WA1))
          continue;

        auto *WrittenScalar1 = getWrittenScalar(WA1);
        if (!WrittenScalar1)
          continue;

        auto Next = It1;
        ++Next;
        for (auto It2 = Next; It2 != AccRange.end(); ++It2) {
          MemoryAccess *WA2 = *It2;

          if (!WA2->isMustWrite())
            continue;
          if (!WA2->isOriginalScalarKind())
            continue;
          if (StoresToRemove.count(WA2))
            continue;

          auto *WrittenScalar2 = getWrittenScalar(WA2);
          if (WrittenScalar1 != WrittenScalar2)
            continue;

          auto AccRel1 = give(isl_map_intersect_domain(WA1->getAccessRelation(),
                                                       Domain.copy()));
          AccRel1 =
              give(isl_map_intersect_params(AccRel1.take(), S->getContext()));
          auto AccRel2 = give(isl_map_intersect_domain(WA2->getAccessRelation(),
                                                       Domain.copy()));
          AccRel2 =
              give(isl_map_intersect_params(AccRel2.take(), S->getContext()));
          if (isl_map_is_equal(AccRel1.keep(), AccRel2.keep()) != isl_bool_true)
            continue;

          if (auto *Conflicting = hasReadBetween(&Stmt, WA1, WA2, AccRel1)) {
            DEBUG(
                dbgs() << "Not removing identical writes " << WA2 << " and "
                       << WA2
                       << " because there is another load to the same element "
                          "between\n");
            DEBUG(Conflicting->print(dbgs()));
            continue;
          }

          DEBUG(dbgs() << "Remove identical writes:\n");
          DEBUG(dbgs() << "  First write  (kept)   : " << WA1 << '\n');
          DEBUG(dbgs() << "  Second write (removed): " << WA2 << '\n');
          StoresToRemove.insert(WA2);
        }
      }

      for (auto *WA : StoresToRemove) {
        auto *Stmt = WA->getStatement();

        Stmt->removeSingleMemoryAccess(WA);

        IdenticalWritesRemoved++;
        TotalIdenticalWritesRemoved++;
      }
    }
  }

  void removeOverwrites() {
    for (auto &Stmt : *S) {
      //  if (!Stmt.isBlockStmt())
      //	   continue;
      auto Domain = give(Stmt.getDomain());

      auto AccRange = accessesInOrder(&Stmt);
      SmallVector<MemoryAccess *, 32> Accesses{AccRange.begin(),
                                               AccRange.end()};

      isl::union_map WillBeOverwritten =
          isl::union_map::empty(give(S->getParamSpace()));
      // isl::union_map WillBeOverwrittenBy = isl::union_map::empty(  give(
      // S->getParamSpace() ));

      for (auto *MA : reverse(Accesses)) {
        auto AccRel = give(MA->getAccessRelation());
        AccRel = AccRel.intersect_domain(Domain);
        AccRel = AccRel.intersect_params(give(S->getContext()));

        // auto Wrapped =  give( isl_map_wrap( AccRel.copy()) );

        if (MA->isRead()) {
          WillBeOverwritten = WillBeOverwritten.subtract(AccRel);
          // WillBeOverwrittenBy = WillBeOverwrittenBy.subtract_domain(
          // Wrapped);
          continue;
        }

        // auto AccId = give( MA->getId());
        // auto AccSpace = isl::space::space()
        // auto WrittenBy = give(isl_map_from_domain_and_range(Wrapped.copy(),
        // ));

        isl::union_map AccRelUnion = AccRel;
        if (isl_union_map_is_subset(AccRelUnion.keep(),
                                    WillBeOverwritten.keep()) ==
            isl_bool_true) {
          DEBUG(dbgs() << "Removing " << MA
                       << " which will be overwritten anyway\n");

          Stmt.removeSingleMemoryAccess(MA);
          OverwritesRemoved++;
          TotalOverwritesRemoved++;
        }

        if (MA->isMustWrite())
          WillBeOverwritten = WillBeOverwritten.add_map(AccRel);
      }
    }
  }

  /// Remove writes that just write the same value already stored in the
  /// element.
  void removeRedundantWrites() {
    // Delay actual removal to not invalidate iterators.
    SmallVector<MemoryAccess *, 8> StoresToRemove;

    for (auto &Stmt : *S) {
      for (auto *WA : Stmt) {
        if (!WA->isMustWrite())
          continue;
        if (!WA->isLatestArrayKind())
          continue;
        if (!isa<StoreInst>(WA->getAccessInstruction()))
          continue;

        auto ReadingValue = WA->getAccessValue();
        if (!ReadingValue)
          continue;

        auto RA = getReadAccessForValue(&Stmt, ReadingValue);
        if (!RA)
          continue;
        if (!RA->isLatestArrayKind())
          continue;

        auto WARel = give(WA->getLatestAccessRelation());
        WARel = give(isl_map_intersect_domain(WARel.take(),
                                              WA->getStatement()->getDomain()));
        WARel = give(isl_map_intersect_params(WARel.take(), S->getContext()));
        auto RARel = give(RA->getLatestAccessRelation());
        RARel = give(isl_map_intersect_domain(RARel.take(),
                                              RA->getStatement()->getDomain()));
        RARel = give(isl_map_intersect_params(RARel.take(), S->getContext()));

        if (isl_map_is_equal(RARel.keep(), WARel.keep()) != isl_bool_true) {
          PairUnequalAccRels++;
          DEBUG(dbgs() << "Not cleaning up " << WA
                       << " because of unequal access relations:\n");
          DEBUG(dbgs() << "      RA: " << RARel << "\n");
          DEBUG(dbgs() << "      WA: " << WARel << "\n");
          continue;
        }

        if (auto *Conflicting = hasWriteBetween(&Stmt, RA, WA, WARel)) {
          (void)Conflicting;
          InBetweenStore++;
          DEBUG(dbgs() << "Not cleaning up " << WA
                       << " because there is another store to the same element "
                          "between\n");
          DEBUG(Conflicting->print(dbgs()));
          continue;
        }

        StoresToRemove.push_back(WA);
      }
    }

    for (auto *WA : StoresToRemove) {
      auto Stmt = WA->getStatement();
      auto AccRel = give(WA->getAccessRelation());
      auto AccVal = WA->getAccessValue();

      DEBUG(dbgs() << "Cleanup of " << WA << ":\n");
      DEBUG(dbgs() << "      Scalar: " << *AccVal << "\n");
      DEBUG(dbgs() << "      AccRel: " << AccRel << "\n");
      (void)AccVal;
      (void)AccRel;

      Stmt->removeSingleMemoryAccess(WA);

      RedundantWritesRemoved++;
      TotalRedundantWritesRemoved++;
    }
  }

  /// Remove statements without side effects.
  void removeUnnecessayStmts() {
    auto NumStmtsBefore = S->getSize();
    S->simplifySCoP(true);
    assert(NumStmtsBefore >= S->getSize());
    StmtsRemoved = NumStmtsBefore - S->getSize();
    DEBUG(dbgs() << "Removed " << StmtsRemoved << " (of " << NumStmtsBefore
                 << ") statements\n");
    TotalStmtsRemoved += StmtsRemoved;
  }

  /// Print simplification statistics to @p OS.
  void printStatistics(llvm::raw_ostream &OS, int Indent = 0) const {
    OS.indent(Indent) << "Statistics {\n";
    OS.indent(Indent + 4) << "Identical writes removed: "
                          << IdenticalWritesRemoved << '\n';
    OS.indent(Indent + 4) << "Overwrites removed: " << OverwritesRemoved
                          << '\n';
    OS.indent(Indent + 4) << "Redundant writes removed: "
                          << RedundantWritesRemoved << "\n";
    OS.indent(Indent + 4) << "Stmts removed: " << StmtsRemoved << "\n";
    OS.indent(Indent) << "}\n";
  }

  /// Print the current state of all MemoryAccesses to @p OS.
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
  static char ID;
  explicit Simplify() : ScopPass(ID) {}

  virtual void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.addRequiredTransitive<ScopInfoRegionPass>();
    AU.setPreservesAll();
  }

  virtual bool runOnScop(Scop &S) override {
    // Reset statistics of last processed SCoP.
    releaseMemory();

    // Prepare processing of this SCoP.
    this->S = &S;
    ScopsProcessed++;

    DEBUG(dbgs() << "Removing identical writes...\n");
    removeIdenticalWrites();

    DEBUG(dbgs() << "Removing overwrites...\n");
    removeOverwrites();

    DEBUG(dbgs() << "Removing redundant writes...\n");
    removeRedundantWrites();

    DEBUG(dbgs() << "Removing statements without side effects...\n");
    removeUnnecessayStmts();

    if (isModified())
      ScopsModified++;
    DEBUG(dbgs() << "\nFinal Scop:\n");
    DEBUG(S.print(dbgs()));

    return false;
  }

  virtual void printScop(raw_ostream &OS, Scop &S) const override {
    assert(&S == this->S &&
           "Can only print analysis for the last processed SCoP");
    printStatistics(OS);

    if (!isModified()) {
      OS << "SCoP could not be simplified\n";
      return;
    }
    printAccesses(OS);
  }

  virtual void releaseMemory() override {
    S = nullptr;

    IdenticalWritesRemoved = 0;
    OverwritesRemoved = 0;
    RedundantWritesRemoved = 0;
    StmtsRemoved = 0;
  }
};

char Simplify::ID;
} // anonymous namespace

Pass *polly::createSimplifyPass() { return new Simplify(); }

INITIALIZE_PASS_BEGIN(Simplify, "polly-simplify", "Polly - Simplify", false,
                      false)
INITIALIZE_PASS_END(Simplify, "polly-simplify", "Polly - Simplify", false,
                    false)
