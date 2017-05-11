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
#include "polly/CodeGen/BlockGenerators.h"
#include "polly/ScopInfo.h"
#include "polly/ScopPass.h"
#include "polly/Support/GICHelper.h"
#include "polly/Support/VirtualInstruction.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Value.h"
#include "llvm/PassSupport.h"
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
STATISTIC(TotalRedundantWritesRemoved,
          "Number of writes of same value removed in any SCoP");
STATISTIC(TotalDoubleWritesRemoved, "Number of writes removed that are "
                                    "overwritten without being read first in "
                                    "any SCoP");
STATISTIC(TotalWritesCoalesced, "Number of writes coalesced with another");

STATISTIC(TotalDeadAccessesRemoved, "Number of partial accesses removed");
STATISTIC(TotalDeadComputedPHIs, "Number of dead computed PHIs removed");
STATISTIC(TotalStmtsRemoved, "Number of statements removed in any SCoP");

STATISTIC(PairsCleaned, "Number of Load-Store pairs cleaned");
STATISTIC(UnusedAccs, "Number of unused accesses");

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

struct CleanupReport {
  std::string StmtBaseName;
  Value *Scalar;
  isl::map AccRel;

  CleanupReport(std::string Stmt, Value *Scalar, isl::map AccRel)
      : StmtBaseName(Stmt), Scalar(Scalar), AccRel(std::move(AccRel)) {
    DEBUG(print(llvm::dbgs(), 0));
  }

  CleanupReport(const CleanupReport &That) = delete;
  CleanupReport(CleanupReport &&That)
      : StmtBaseName(std::move(That.StmtBaseName)), Scalar(That.Scalar),
        AccRel(That.AccRel) {
    That.AccRel = nullptr;
  }

  void print(llvm::raw_ostream &OS, int Indent = 0) const {
    OS.indent(Indent) << "Cleanup {\n";
    OS.indent(Indent + 4) << "Stmt: " << StmtBaseName << "\n";
    if (Scalar)
      OS.indent(Indent + 4) << "Scalar: " << *Scalar << "\n";
    OS.indent(Indent + 4) << "AccRel: " << AccRel << "\n";
    OS.indent(Indent) << "}\n";
  }
};

class Simplify : public ScopPass {
private:
  /// The last/current SCoP that is/has been processed.
  Scop *S;

  /// Number of double writes removed from this SCoP.
  int IdenticalWritesRemoved = 0;

  /// Number of redundant writes removed from this SCoP.
  int RedundantWritesRemoved = 0;

  int DoubleWritesRemoved = 0;

  int WritesCoalesced = 0;

  int EmptyPartialAccessesRemoved = 0;

  int DeadAccessesRemoved = 0;

  int DeadComputedPHIs = 0;

  /// Number of unnecessary statements removed from the SCoP.
  int StmtsRemoved = 0;

  /// Return whether at least one simplification has been applied.
  bool isModified() const {
    return IdenticalWritesRemoved > 0 || RedundantWritesRemoved > 0 ||
           DoubleWritesRemoved > 0 || WritesCoalesced > 0 || StmtsRemoved > 0 ||
           EmptyPartialAccessesRemoved > 0 || DeadComputedPHIs > 0 ||
           DeadAccessesRemoved > 0;
  }

  /// Hold a reference to the isl_ctx to avoid it being freed before we released
  /// all of the ISL objects.
  std::shared_ptr<isl_ctx> IslCtx;

  SmallVector<CleanupReport, 8> CleanupReports;

  void printCleanups(llvm::raw_ostream &OS, int Indent = 0) const {
    OS.indent(Indent) << "Cleanups {\n";
    for (auto &Report : CleanupReports)
      Report.print(OS, Indent + 4);
    OS.indent(Indent) << "}\n";
  }
  Value *getUniqueIncoming(MemoryAccess *MA) {
    assert(MA->isAnyPHIKind());
    assert(MA->isWrite());

    Value *IncomingValue = nullptr;
    for (auto Incoming : MA->getIncoming()) {
      auto Val = Incoming.second;
      assert(Val);

      // Handle undef values as if they don't exist.
      if (isa<UndefValue>(Val))
        continue;

      if (IncomingValue && Val != IncomingValue)
        return nullptr;

      IncomingValue = Val;
    }
    return IncomingValue;
  }
  Value *getUsedValue(MemoryAccess *MA) {
    if (MA->isWrite() && (MA->isValueKind() || MA->isArrayKind()))
      return MA->getAccessValue();

    if (MA->isWrite() && MA->isAnyPHIKind())
      return getUniqueIncoming(MA);

    return nullptr;
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
  MemoryAccess *hasWriteBetween(ScopStmt *Stmt, MemoryAccess *From,
                                MemoryAccess *To, isl::map Targets) {
    auto TargetsSpace = give(isl_map_get_space(Targets.keep()));

    bool Started = Stmt->isRegionStmt();
    for (auto *Acc : *Stmt) {
      if (Acc->isLatestScalarKind())
        continue;

      if (Stmt->isBlockStmt() && From == Acc) {
        assert(!Started);
        Started = true;
        continue;
      }
      if (Stmt->isBlockStmt() && To == Acc) {
        assert(Started);
        return nullptr;
      }
      if (!Started)
        continue;

      if (!Acc->isWrite())
        continue;

      auto AccRel = give(Acc->getAccessRelation());
      auto AccRelSpace = give(isl_map_get_space(AccRel.keep()));

      // Spaces being different means that they access different arrays.
      if (isl_space_has_equal_tuples(TargetsSpace.keep(), AccRelSpace.keep()) ==
          isl_bool_false)
        continue;

      AccRel = give(isl_map_intersect_domain(AccRel.take(),
                                             Acc->getStatement()->getDomain()));
      AccRel = give(isl_map_intersect_params(AccRel.take(), S->getContext()));
      auto CommonElt = give(isl_map_intersect(Targets.copy(), AccRel.copy()));
      if (isl_map_is_empty(CommonElt.keep()) != isl_bool_true)
        return Acc;
    }
    assert(Stmt->isRegionStmt() &&
           "To must be encountered in block statements");
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

      // TODO: This has quadratic runtime. Accesses could be grouped by
      // getAccessValue() to avoid.
      for (auto *WA1 : Stmt) {
        if (!WA1->isMustWrite())
          continue;
        if (!WA1->isOriginalScalarKind())
          continue;
        if (StoresToRemove.count(WA1))
          continue;

        auto *WrittenScalar1 = getWrittenScalar(WA1);
        if (!WrittenScalar1)
          continue;

        for (auto *WA2 : Stmt) {
          if (WA1 == WA2)
            continue;
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
          auto AccRel2 = give(isl_map_intersect_domain(WA2->getAccessRelation(),
                                                       Domain.copy()));
          if (isl_map_is_equal(AccRel1.keep(), AccRel2.keep()) != isl_bool_true)
            continue;

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

  /// Remove writes that just write the same value already stored in the
  /// element.
  void removeRedundantWrites() {
    assert(S);
    bool Modified = false;

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

      CleanupReports.emplace_back(Stmt->getBaseName(), AccVal, AccRel);

      Stmt->removeSingleMemoryAccess(WA);
      // TODO: Also remove read accesses when not used anymore
      PairsCleaned++;
      Modified = true;

      RedundantWritesRemoved++;
      TotalRedundantWritesRemoved++;
    }
  }

  void removeDoubleWrites(ScopStmt *Stmt) {
    auto Domain = isl::manage(Stmt->getDomain());
    auto ParamSpace =
        isl::manage(isl_space_params(isl_set_get_space(Domain.keep())));
    isl::union_map Overwritten = isl::union_map::empty(ParamSpace);

    SmallVector<MemoryAccess *, 8> StoresToRemove;

    for (auto *MA : reverse(*Stmt)) {
      if (!MA->isExplicit())
        continue;

      auto AccRel = isl ::manage(MA->getAccessRelation());
      AccRel =
          AccRel.intersect_domain(isl::manage(MA->getStatement()->getDomain()));

      if (MA->isRead()) {
        Overwritten = Overwritten.subtract(AccRel);
        continue;
      }

      if (isl::union_map(AccRel).is_subset(Overwritten)) {
        StoresToRemove.push_back(MA);
        continue;
      }

      if (!MA->isMustWrite())
        continue;

      Overwritten = Overwritten.add_map(AccRel);
    }

    for (auto *WA : StoresToRemove) {
      Stmt->removeSingleMemoryAccess(WA);

      DoubleWritesRemoved++;
      TotalDoubleWritesRemoved++;
    }
  }

  void removeDoubleWrites() {
    for (auto &Stmt : *S)
      removeDoubleWrites(&Stmt);
  }

  // TODO: Merge with removeDoubleWrites()
  void coalescePartialWrites(ScopStmt *Stmt) {
    auto Domain = isl::manage(Stmt->getDomain());
    SmallVector<MemoryAccess *, 8> StoresToRemove;
    DenseMap<llvm::Value *, SmallVector<MemoryAccess *, 2>> WrittenBy;
    // DenseMap<llvm::Value*, isl::union_map > WrittenTo;

    for (auto *MA : *Stmt) {
      // We currently only handle implicit writes so we don't have to look reads
      // between them. All implicit writes take place at the end of a statement.
      if (!(MA->isImplicit() && MA->isMustWrite()))
        continue;

      // TODO: The same value can have multiple names if used in a PHINode. Try
      // to find all alternative names.
      WrittenBy[MA->getAccessValue()].push_back(MA);
    }

    for (auto &Pair : WrittenBy) {
      auto &MAList = Pair.second;
      auto Count = MAList.size();

      // Nothing to coalesce if there is just a single access.
      if (Count <= 1)
        continue;

      for (int i = 0; i < Count; i += 1) {
        if (!MAList[i])
          continue;

        for (int j = i; j < Count; j += 1) {
          if (!MAList[j])
            continue;

          // Cannot coalesce if they access two different arrays.
          if (MAList[i]->getLatestScopArrayInfo() !=
              MAList[j]->getLatestScopArrayInfo())
            continue;

          auto IAccRel = isl::manage(MAList[i]->getAccessRelation());
          auto JAccRel = isl::manage(MAList[j]->getAccessRelation());
          auto CommonDomain = isl::manage(isl_set_intersect(
              isl_set_intersect(isl_map_domain(IAccRel.copy()),
                                isl_map_domain(JAccRel.copy())),
              Domain.copy()));

          // Cannot coalesce if the common parts access different elements.
          if (!IAccRel.intersect_domain(CommonDomain)
                   .is_equal(JAccRel.intersect_domain(CommonDomain))
                   .is_true())
            continue;

          // Coalesce: Combine both accesses into a single.
          auto NewAccRel = IAccRel.unite(JAccRel);
          MAList[i]->setNewAccessRelation(NewAccRel.take());

          Stmt->removeSingleMemoryAccess(MAList[j]);
          MAList[j] = nullptr;

          WritesCoalesced++;
          TotalWritesCoalesced++;
        }
      }
    }
  }

  void coalescePartialWrites() {
    for (auto &Stmt : *S)
      coalescePartialWrites(&Stmt);
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

  void removeEmptyPartialAccesses() {
    for (auto &Stmt : *S) {
      SmallVector<MemoryAccess *, 8> Accs{Stmt.begin(), Stmt.end()};
      for (auto *MA : Accs) {
        auto AccRel = give(MA->getAccessRelation());
        if (isl_map_is_empty(AccRel.keep()) == isl_bool_true) {
          DEBUG(dbgs() << "Removing " << MA
                       << " because it's a partial access that never occurs\n");
          Stmt.removeSingleMemoryAccess(MA);
          DeadAccessesRemoved++;
          TotalDeadAccessesRemoved++;
        }
      }
    }
  }

  void markAndSweep(LoopInfo *LI) {
    if (!UseVirtualStmts) {
      DEBUG(dbgs()
            << "Mark-and-sweep simplifier needs -polly-codegen-virtual-stmts");
      return;
    }

    //  DenseSet<VirtualInstruction > Used;
    DenseSet<MemoryAccess *> UsedMA;
    std::vector<VirtualInstruction> InstList;

    markReachableGlobal(S, InstList, UsedMA, LI);

    SmallVector<MemoryAccess *, 64> AllMAs;
    for (auto &Stmt : *S)
      AllMAs.append(Stmt.begin(), Stmt.end());

    for (auto *MA : AllMAs) {
      if (UsedMA.count(MA))
        continue;
      DEBUG(dbgs() << "Removing " << MA << " because it's value is not used\n");
      auto Stmt = MA->getStatement();
      Stmt->removeSingleMemoryAccess(MA);

      UnusedAccs++;
      DeadAccessesRemoved++;
    }

    for (auto &Stmt : *S) {
      decltype(Stmt.ComputedPHIs) UsedComputedPHIs;

      for (auto &VInst : InstList) {
        if (&Stmt != VInst.getStmt())
          continue;

        auto *Inst = VInst.getInstruction();
        auto *PHI = dyn_cast<PHINode>(Inst);
        if (!PHI)
          continue;

        auto CompPHI = Stmt.ComputedPHIs.lookup(PHI);
        if (!CompPHI)
          continue;
        UsedComputedPHIs[PHI] = CompPHI;
      }
      if (Stmt.ComputedPHIs.size() != UsedComputedPHIs.size()) {
        DEBUG(dbgs() << "Removed "
                     << (Stmt.ComputedPHIs.size() - UsedComputedPHIs.size())
                     << " ComputedPHI(s) which are not used\n");
        DeadComputedPHIs += Stmt.ComputedPHIs.size() - UsedComputedPHIs.size();
        TotalDeadComputedPHIs +=
            Stmt.ComputedPHIs.size() - UsedComputedPHIs.size();
      }
      Stmt.ComputedPHIs = std::move(UsedComputedPHIs);
    }
  }

  /// Print simplification statistics to @p OS.
  void printStatistics(llvm::raw_ostream &OS, int Indent = 0) const {
    OS.indent(Indent) << "Statistics {\n";
    OS.indent(Indent + 4) << "Identical writes removed: "
                          << IdenticalWritesRemoved << '\n';
    OS.indent(Indent + 4) << "Double writes removed: " << DoubleWritesRemoved
                          << "\n";
    OS.indent(Indent + 4) << "Partial writes coalesced: " << WritesCoalesced
                          << "\n";
    OS.indent(Indent + 4) << "Empty partial access removed: "
                          << EmptyPartialAccessesRemoved << "\n";
    OS.indent(Indent + 4) << "Dead accesses removed: " << DeadAccessesRemoved
                          << "\n";
    OS.indent(Indent + 4) << "Dead computed PHIs removed: " << DeadComputedPHIs
                          << "\n";
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
    AU.addRequired<LoopInfoWrapperPass>();
    AU.setPreservesAll();
  }

  virtual bool runOnScop(Scop &S) override {
    // Reset statistics of last processed SCoP.
    releaseMemory();

    // Prepare processing of this SCoP.
    this->S = &S;
    IslCtx = S.getSharedIslCtx();
    ScopsProcessed++;

	DEBUG(dbgs() << "Removing identical writes...\n");
	removeIdenticalWrites();

    DEBUG(dbgs() << "Removing identical writes...\n");
    removeIdenticalWrites();

    DEBUG(dbgs() << "Removing redundant writes...\n");
    removeRedundantWrites();

    DEBUG(dbgs() << "Removing double writes...\n");
    removeDoubleWrites();

    DEBUG(dbgs() << "Coalesce partial writes...\n");
    coalescePartialWrites();

    DEBUG(dbgs() << "Removing partial writes that never happen...\n");
    removeEmptyPartialAccesses();

    DEBUG(dbgs() << "Cleanup unused accesses...\n");
    markAndSweep(&getAnalysis<LoopInfoWrapperPass>().getLoopInfo());

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

    printCleanups(OS);
    printAccesses(OS);
  }

  virtual void releaseMemory() override {
    S = nullptr;
    IdenticalWritesRemoved = 0;
    RedundantWritesRemoved = 0;
    DoubleWritesRemoved = 0;
    WritesCoalesced = 0;
    EmptyPartialAccessesRemoved = 0;
    DeadAccessesRemoved = 0;
    DeadComputedPHIs = 0;
    StmtsRemoved = 0;
    assert(!isModified());

    // DefUse.reset();
    CleanupReports.clear();
    IslCtx.reset();
  }
};

char Simplify::ID;
} // anonymous namespace

Pass *polly::createSimplifyPass() { return new Simplify(); }

INITIALIZE_PASS_BEGIN(Simplify, "polly-simplify", "Polly - Simplify", false,
                      false)
INITIALIZE_PASS_END(Simplify, "polly-simplify", "Polly - Simplify", false,
                    false)
