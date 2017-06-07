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
#include "polly/Support/ISLOStream.h"
#include "polly/Support/VirtualInstruction.h"
#include "llvm/ADT/STLExtras.h"
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
STATISTIC(TotalOverwritesRemoved, "Number of removed overwritten writes");
STATISTIC(TotalRedundantWritesRemoved,
          "Number of writes of same value removed in any SCoP");

STATISTIC(TotalWritesCoalesced, "Number of writes coalesced with another");

STATISTIC(TotalDeadAccessesRemoved, "Number of partial accesses removed");
STATISTIC(TotalDeadComputedPHIs, "Number of dead computed PHIs removed");
STATISTIC(TotalStmtsRemoved, "Number of statements removed in any SCoP");
STATISTIC(UnusedAccs, "Number of unused accesses");

static bool isImplicitRead(MemoryAccess *MA) {
  return MA->isRead() && MA->isOriginalScalarKind();
}

static bool isExplicitAccess(MemoryAccess *MA) {
  return MA->isOriginalArrayKind();
}

static bool isImplicitWrite(MemoryAccess *MA) {
  return MA->isWrite() && MA->isOriginalScalarKind();
}

/// Return a vector that contains MemoryAccesses in the order in
/// which they are executed.
///
/// The order is:
/// - Implicit reads (BlockGenerator::generateScalarLoads)
/// - Explicit reads and writes (BlockGenerator::generateArrayLoad,
///   BlockGenerator::generateArrayStore)
///   - In block statements, the accesses are in order in which their
///     instructions are executed.
///   - In region statements, that order of execution is not predictable at
///     compile-time.
/// - Implicit writes (BlockGenerator::generateScalarStores)
///   The order in which implicit writes are executed relative to each other is
///   undefined.
static SmallVector<MemoryAccess *, 32> getAccessesInOrder(ScopStmt &Stmt) {

  SmallVector<MemoryAccess *, 32> Accesses;

  for (MemoryAccess *MemAcc : Stmt)
    if (isImplicitRead(MemAcc))
      Accesses.push_back(MemAcc);

  for (MemoryAccess *MemAcc : Stmt)
    if (isExplicitAccess(MemAcc))
      Accesses.push_back(MemAcc);

  for (MemoryAccess *MemAcc : Stmt)
    if (isImplicitWrite(MemAcc))
      Accesses.push_back(MemAcc);

  return Accesses;
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

class Simplify : public ScopPass {
private:
  /// The last/current SCoP that is/has been processed.
  Scop *S;

  /// Number of writes that are overwritten anyway.
  int OverwritesRemoved = 0;

  /// Number of redundant writes removed from this SCoP.
  int RedundantWritesRemoved = 0;

  int WritesCoalesced = 0;

  int EmptyPartialAccessesRemoved = 0;

  int DeadAccessesRemoved = 0;

  int DeadComputedPHIs = 0;

  /// Number of unnecessary statements removed from the SCoP.
  int StmtsRemoved = 0;

  /// Return whether at least one simplification has been applied.
  bool isModified() const {
    return OverwritesRemoved > 0 || RedundantWritesRemoved > 0 ||
           WritesCoalesced > 0 || StmtsRemoved > 0 ||
           EmptyPartialAccessesRemoved > 0 || DeadComputedPHIs > 0 ||
           DeadAccessesRemoved > 0;
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
    auto TargetsSpace = Targets.get_space();

    bool Started = Stmt->isRegionStmt();
    auto Accesses = getAccessesInOrder(*Stmt);
    for (auto *Acc : Accesses) {
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
      auto AccRelSpace = AccRel.get_space();

      // Spaces being different means that they access different arrays.
      if (!TargetsSpace.has_equal_tuples(AccRelSpace))
        continue;

      AccRel = AccRel.intersect_domain(give(Acc->getStatement()->getDomain()));
      AccRel = AccRel.intersect_params(give(S->getContext()));
      auto CommonElt = Targets.intersect(AccRel);
      if (!CommonElt.is_empty())
        return Acc;
    }
    assert(Stmt->isRegionStmt() &&
           "To must be encountered in block statements");
    return nullptr;
  }

  /// Remove writes that are overwritten unconditionally later in the same
  /// statement.
  ///
  /// There must be no read of the same value between the write (that is to be
  /// removed) and the overwrite.
  void removeOverwrites() {
    for (auto &Stmt : *S) {
      auto Domain = give(Stmt.getDomain());
      isl::union_map WillBeOverwritten =
          isl::union_map::empty(give(S->getParamSpace()));

      SmallVector<MemoryAccess *, 32> Accesses(getAccessesInOrder(Stmt));

      // Iterate in reverse order, so the overwrite comes before the write that
      // is to be removed.
      for (auto *MA : reverse(Accesses)) {

        // In region statements, the explicit accesses can be in blocks that are
        // can be executed in any order. We therefore process only the implicit
        // writes and stop after that.
        if (Stmt.isRegionStmt() && isExplicitAccess(MA))
          break;

        auto AccRel = give(MA->getAccessRelation());
        AccRel = AccRel.intersect_domain(Domain);
        AccRel = AccRel.intersect_params(give(S->getContext()));

        // If a value is read in-between, do not consider it as overwritten.
        if (MA->isRead()) {
          WillBeOverwritten = WillBeOverwritten.subtract(AccRel);
          continue;
        }

        // If all of a write's elements are overwritten, remove it.
        isl::union_map AccRelUnion = AccRel;
        if (AccRelUnion.is_subset(WillBeOverwritten)) {
          DEBUG(dbgs() << "Removing " << MA
                       << " which will be overwritten anyway\n");

          Stmt.removeSingleMemoryAccess(MA);
          OverwritesRemoved++;
          TotalOverwritesRemoved++;
        }

        // Unconditional writes overwrite other values.
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
        WARel = WARel.intersect_domain(give(WA->getStatement()->getDomain()));
        WARel = WARel.intersect_params(give(S->getContext()));
        auto RARel = give(RA->getLatestAccessRelation());
        RARel = RARel.intersect_domain(give(RA->getStatement()->getDomain()));
        RARel = RARel.intersect_params(give(S->getContext()));

        if (!RARel.is_equal(WARel)) {
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

      for (size_t i = 0; i < Count; i += 1) {
        if (!MAList[i])
          continue;

        for (size_t j = i; j < Count; j += 1) {
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
    OS.indent(Indent + 4) << "Overwrites removed: " << OverwritesRemoved
                          << '\n';
    OS.indent(Indent + 4) << "Redundant writes removed: "
                          << RedundantWritesRemoved << "\n";
    OS.indent(Indent + 4) << "Empty partial access removed: "
                          << EmptyPartialAccessesRemoved << "\n";
    OS.indent(Indent + 4) << "Partial writes coalesced: " << WritesCoalesced
                          << "\n";
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
    ScopsProcessed++;

    DEBUG(dbgs() << "Removing overwrites...\n");
    removeOverwrites();

    DEBUG(dbgs() << "Removing redundant writes...\n");
    removeRedundantWrites();

    DEBUG(dbgs() << "Removing partial writes that never happen...\n");
    removeEmptyPartialAccesses();

    DEBUG(dbgs() << "Coalesce partial writes...\n");
    coalescePartialWrites();

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
    printAccesses(OS);
  }

  virtual void releaseMemory() override {
    S = nullptr;

    OverwritesRemoved = 0;
    RedundantWritesRemoved = 0;
    WritesCoalesced = 0;
    EmptyPartialAccessesRemoved = 0;
    DeadAccessesRemoved = 0;
    DeadComputedPHIs = 0;
    StmtsRemoved = 0;
    assert(!isModified());
  }
};

char Simplify::ID;
} // anonymous namespace

Pass *polly::createSimplifyPass() { return new Simplify(); }

INITIALIZE_PASS_BEGIN(Simplify, "polly-simplify", "Polly - Simplify", false,
                      false)
INITIALIZE_PASS_END(Simplify, "polly-simplify", "Polly - Simplify", false,
                    false)
