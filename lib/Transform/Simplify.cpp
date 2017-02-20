#include "polly/Simplify.h"
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
STATISTIC(PairsCleaned, "Number of Load-Store pairs cleaned");
STATISTIC(PairUnequalAccRels, "Number of Load-Store pairs NOT cleaned because "
                              "of different access relations");
STATISTIC(UnusedAccs, "Number of unused accesses");
STATISTIC(StmtsRemoved, "Number of statements removed");
STATISTIC(ScopsModified, "Number of SCoPs modified");

struct CleanupReport {
  std::string StmtBaseName;
  Value *Scalar;
  IslPtr<isl_map> AccRel;

  CleanupReport(std::string Stmt, Value *Scalar, IslPtr<isl_map> AccRel)
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
  Scop *S = nullptr;
  // ScalarDefUseChains DefUse;

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

  /// Remove load-store pairs that access the same element in the block.
  bool cleanup() {
    assert(S);
    bool Modified = false;

    SmallVector<MemoryAccess *, 8> StoresToRemove;
    for (auto &Stmt : *S) {
      for (auto *WA : Stmt) {
        if (!WA->isMustWrite())
          continue;
        if (!WA->getLatestScopArrayInfo()->isArrayKind())
          continue;

        auto ReadingValue = getUsedValue(WA);
        if (!ReadingValue)
          continue;

        auto RA = getReadAccessForValue(&Stmt, ReadingValue);
        if (!RA)
          continue;
        if (!RA->getLatestScopArrayInfo()->isArrayKind())
          continue;

        auto WARel = give(WA->getLatestAccessRelation());
        WARel = give(isl_map_intersect_domain(WARel.take(),
                                              WA->getStatement()->getDomain()));
        WARel = give(isl_map_intersect_params(WARel.take(), S->getContext()));
        auto RARel = give(RA->getLatestAccessRelation());
        RARel = give(isl_map_intersect_domain(RARel.take(),
                                              RA->getStatement()->getDomain()));
        RARel = give(isl_map_intersect_params(RARel.take(), S->getContext()));

        auto IsEqualAccRel = isl_map_is_equal(RARel.keep(), WARel.keep());
        if (!IsEqualAccRel) {
          PairUnequalAccRels++;
          DEBUG(dbgs() << "    Not cleaning up " << WA
                       << " because of unequal access relations:\n");
          DEBUG(dbgs() << "      RA: " << RARel << "\n");
          DEBUG(dbgs() << "      WA: " << WARel << "\n");
          continue;
        }

        StoresToRemove.push_back(WA);
      }
    }

    for (auto *WA : StoresToRemove) {
      auto Stmt = WA->getStatement();
      auto AccRel = give(WA->getAccessRelation());
      auto AccVal = WA->getAccessValue();

      DEBUG(dbgs() << "    Cleanup of\n");
      DEBUG(dbgs() << "        " << WA << "\n");
      DEBUG(dbgs() << "      Scalar: " << *AccVal << "\n");
      DEBUG(dbgs() << "      AccRel: " << AccRel << "\n");

      CleanupReports.emplace_back(Stmt->getBaseName(), AccVal, AccRel);

      Stmt->removeSingleMemoryAccess(WA);
      // TODO: Also remove read accesses when not used anymore
      PairsCleaned++;
      Modified = true;
    }
    return Modified;
  }

  bool removeEmptyPartialAccesses() {
    bool Modified = false;
    for (auto &Stmt : *S) {
      SmallVector<MemoryAccess *, 8> Accs{Stmt.begin(), Stmt.end()};
      for (auto *MA : Accs) {
        auto AccRel = give(MA->getAccessRelation());
        if (isl_map_is_empty(AccRel.keep()) == isl_bool_true) { DEBUG(dbgs() << "Removing "<< MA << " because it's a partial access that never occurs\n");
          Stmt.removeSingleMemoryAccess(MA);
          Modified = true;
        }
      }
    }
    return Modified;
  }

  bool markAndSweep(LoopInfo *LI) {
    //  DenseSet<VirtualInstruction > Used;
    DenseSet<MemoryAccess *> UsedMA;
    std::vector<VirtualInstruction> InstList;

#if 1
    markReachableGlobal(S, InstList, UsedMA, LI);
#else
    SmallVector<MemoryAccess *, 32> AllMAs;
    SmallVector<VirtualInstruction, 32> Worklist;

    // Add roots (things that are used after the scop; aka escaping values) to
    // worklist
    for (auto &Stmt : *S) {
      for (auto *MA : Stmt) {
        AllMAs.push_back(MA);
        if (!MA->isWrite())
          continue;

        // Writes to arrays are always used
        if (MA->isLatestArrayKind()) {
          auto Inst = MA->getAccessInstruction();
          Worklist.emplace_back(&Stmt, Inst);
          UsedMA.insert(MA);
        }

        // Values are roots if they are escaping
        if (MA->isLatestValueKind()) {
          auto ComputingInst = cast<Instruction>(MA->getAccessValue());
          bool IsEscaping = false;
          for (auto &Use : ComputingInst->uses()) {
            auto User = cast<Instruction>(Use.getUser());
            if (!S->contains(User)) {
              IsEscaping = true;
              break;
            }
          }

          if (IsEscaping) {
            Worklist.emplace_back(&Stmt, ComputingInst);
            UsedMA.insert(MA);
          }
        }

        // Exit phis are, by definition, escaping
        if (MA->isLatestExitPHIKind()) {
          auto ComputingInst = dyn_cast<Instruction>(MA->getAccessValue());
          if (ComputingInst)
            Worklist.emplace_back(&Stmt, ComputingInst);
          UsedMA.insert(MA);
        }
      }
    }

    while (!Worklist.empty()) {
      auto VInst = Worklist.pop_back_val();

      auto InsertResult = Used.insert(VInst);
      if (!InsertResult.second)
        continue;

      if (auto MA =
              VInst.getStmt()->getArrayAccessOrNULLFor(VInst.getInstruction()))
        UsedMA.insert(MA);

      for (auto &Use : VInst.operands()) {
        if (!VInst.isVirtualOperand(Use))
          continue;

        auto InputMA = VInst.findInputAccess(Use.get(), true);
        if (!InputMA) {
          Worklist.push_back(VInst.getIntraOperand(Use));
          continue;
        }

        auto SAI = InputMA->getScopArrayInfo();
        assert(InputMA->isRead());
        UsedMA.insert(InputMA);

        if (InputMA->isLatestPHIKind()) {
          for (auto *IncomingMA : DefUse.getPHIIncomings(SAI)) {
            Worklist.emplace_back(IncomingMA->getStatement(),
                                  cast<Instruction>(Use.get()));
            UsedMA.insert(IncomingMA);
          }
        }

        if (InputMA->isLatestValueKind()) {
          // search for the definition
          auto DefMA = DefUse.getValueDef(SAI);
          Worklist.emplace_back(DefMA->getStatement(),
                                cast<Instruction>(Use.get()));
          UsedMA.insert(DefMA);
        }

        if (InputMA->isLatestArrayKind()) {
          auto LI = cast<LoadInst>(Use.get());

          // If the access is explicit, it is just like the intra-operand case
          // If the access is implicit, there is no getAccessInstruction(). The
          // pointer operand should be synthesizable such that there is no
          // effect of this.
          Worklist.emplace_back(InputMA->getStatement(), LI);
        }
      }
    }
#endif

    SmallVector<MemoryAccess *, 64> AllMAs;
    for (auto &Stmt : *S)
      AllMAs.append(Stmt.begin(), Stmt.end());

    bool Modified = false;
    for (auto *MA : AllMAs) {
      if (UsedMA.count(MA))
        continue;
	  DEBUG(dbgs() << "Removing " << MA << " because it's value is not used\n");
      auto Stmt = MA->getStatement();
      Stmt->removeSingleMemoryAccess(MA);
      Modified = true;
      UnusedAccs++;
    }

    return Modified;
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
  static char ID;
  explicit Simplify() : ScopPass(ID) {}

  virtual void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.addRequiredTransitive<ScopInfoRegionPass>();
    AU.addRequired<LoopInfoWrapperPass>();
    AU.setPreservesAll();
  }

  virtual bool runOnScop(Scop &S) override {
    // Free resources for previous scop's computation, if not yet done.
    releaseMemory();
    this->S = &S;
    IslCtx = S.getSharedIslCtx();
    ScopsProcessed++;
    bool Modified = false;

    DEBUG(dbgs() << "Cleaning up no-op load-store combinations...\n");
    if (cleanup())
      Modified = true;

    DEBUG(dbgs() << "Removing partial writes that never happen...\n");
    if (removeEmptyPartialAccesses())
      Modified = true;

    DEBUG(dbgs() << "Cleanup unused accesses...\n");
    if (markAndSweep(&getAnalysis<LoopInfoWrapperPass>().getLoopInfo()))
      Modified = true;

    DEBUG(dbgs() << "Removing statements...\n");
    auto NumStmtsBefore = S.getSize();
    S.simplifySCoP(true);
    assert(NumStmtsBefore >= S.getSize());
    auto NumRemoved = NumStmtsBefore - S.getSize();
    StmtsRemoved += NumRemoved;
    if (NumRemoved)
      Modified = true;
    if (Modified)
      ScopsModified++;

    DEBUG(dbgs() << "\nFinal Scop:\n");
    DEBUG(S.print(dbgs()));

    return false;
  }

  virtual void printScop(raw_ostream &OS, Scop &S) const override {
    printCleanups(OS);
    printAccesses(OS);
  }

  virtual void releaseMemory() override {
    S = nullptr;
    // DefUse.reset();
    CleanupReports.clear();
    IslCtx.reset();
  }
}; // class Simplify

char Simplify::ID;
} // anonymous namespace

Pass *polly::createSimplifyPass() { return new Simplify(); }

INITIALIZE_PASS_BEGIN(Simplify, "polly-simplify", "Polly - Simplify", false,
                      false)
INITIALIZE_PASS_END(Simplify, "polly-simplify", "Polly - Simplify", false,
                    false)
