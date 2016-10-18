#include "polly/Simplify.h"
#include "polly/ScopInfo.h"
#include "polly/ScopPass.h"
#include "polly/Support/GICHelper.h"
#include "llvm/IR/Value.h"
#include "llvm/PassSupport.h"
#include "llvm/Support/Debug.h"
#define DEBUG_TYPE "polly-simplify"

using namespace llvm;
using namespace polly;

namespace {

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

  void print(llvm::raw_ostream &OS, int indent = 0) const {
    OS.indent(indent) << "Cleanup:\n";
    OS.indent(indent + 4) << "Stmt: " << StmtBaseName << "\n";
    OS.indent(indent + 4) << "Scalar: " << *Scalar << "\n";
    OS.indent(indent + 4) << "AccRel: " << AccRel << "\n";
  }
};

class Simplify : public ScopPass {
private:
  Scop *S = nullptr;
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
  void cleanup() {
    assert(S);

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
        auto RARel = give(RA->getLatestAccessRelation());

        auto IsEqualAccRel = isl_map_is_equal(RARel.keep(), WARel.keep());

        if (!IsEqualAccRel) {
          DEBUG(dbgs() << "    Not cleaning up " << WA
                       << " because of unequal access relations:\n");
          DEBUG(dbgs() << "      RA: " << RARel << "\n");
          DEBUG(dbgs() << "      WA: " << WARel << "\n");
        }

        if (IsEqualAccRel)
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
    }
  }

public:
  static char ID;
  explicit Simplify() : ScopPass(ID) {}
  virtual void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.addRequiredTransitive<ScopInfoRegionPass>();
    AU.setPreservesAll();
  }
  virtual bool runOnScop(Scop &S) override {
    // Free resources for previous scop's computation, if not yet done.
    releaseMemory();
    this->S = &S;

    cleanup();
    S.simplifySCoP(true);

    return false;
  }

  virtual void printScop(raw_ostream &OS, Scop &S) const override {
    printCleanups(OS);
  }

  virtual void releaseMemory() override { S = nullptr; }

}; // class Simplify

char Simplify::ID;
} // anonymous namespace

Pass *polly::createSimplifyPass() { return new Simplify(); }

INITIALIZE_PASS_BEGIN(Simplify, "polly-simplify", "Polly - Simplify", false,
                      false)
INITIALIZE_PASS_END(Simplify, "polly-simplify", "Polly - Simplify", false,
                    false)
