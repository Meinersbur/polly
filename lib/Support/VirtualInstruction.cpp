#include "polly/Support/VirtualInstruction.h"

using namespace polly;
using namespace llvm;

namespace {
bool isInLoop(MemoryAccess *MA) {
  auto Stmt = MA->getStatement();
  return Stmt->getNumIterators() > 0;
}
} // anonymous namespace

void ScalarDefUseChains::reset() {
  ValueDefAccs.clear();
  ValueUseAccs.clear();
  PHIReadAccs.clear();
  PHIIncomingAccs.clear();

  ScalarValueDeps = 0;
  ScalarValueLoopDeps = 0;
  ScalarPHIDeps = 0;
  ScalarPHILoopDeps = 0;
}

void ScalarDefUseChains::compute(Scop *S) {
  reset();

  for (auto &Stmt : *S) {
    for (auto *MA : Stmt) {
      if (MA->isOriginalValueKind() && MA->isWrite()) {
        auto *SAI = MA->getScopArrayInfo();
        assert(!ValueDefAccs.count(SAI) &&
               "There can be at most one definition per MK_Value scalar");
        ValueDefAccs[SAI] = MA;
      }

      if (MA->isOriginalValueKind() && MA->isRead())
        ValueUseAccs[MA->getScopArrayInfo()].push_back(MA);

      if (MA->isOriginalAnyPHIKind() && MA->isRead()) {
        auto *SAI = MA->getScopArrayInfo();
        assert(!PHIReadAccs.count(SAI) && "There must be exactly one read "
                                          "per PHI (that's where the PHINode "
                                          "is)");
        PHIReadAccs[SAI] = MA;
      }

      if (MA->isOriginalAnyPHIKind() && MA->isWrite())
        PHIIncomingAccs[MA->getScopArrayInfo()].push_back(MA);
    }
  }

  for (auto ScalarVals : ValueDefAccs) {
    if (!ValueUseAccs[ScalarVals.first].empty())
      ScalarValueDeps++;

    if (!isInLoop(ScalarVals.second))
      continue;
    for (auto Use : ValueUseAccs[ScalarVals.first])
      if (isInLoop(Use)) {
        ScalarValueLoopDeps++;
        break;
      }
  }

  for (auto ScalarPHIs : PHIReadAccs) {
    if (!PHIIncomingAccs[ScalarPHIs.first].empty())
      ScalarPHIDeps++;

    if (!isInLoop(ScalarPHIs.second))
      continue;
    for (auto Incoming : PHIIncomingAccs[ScalarPHIs.first])
      if (isInLoop(Incoming)) {
        ScalarPHILoopDeps++;
        break;
      }
  }
}

/// If InputVal is not defined in the stmt itself, return the MemoryAccess that
/// reads the scalar. Return nullptr otherwise (if the value is defined in the
/// scop, or is synthesizable)
MemoryAccess *polly::getInputAccessOf(Value *InputVal, ScopStmt *Stmt,
                                      bool AllowArrayLoads) {
  for (auto *MA : *Stmt) {
    if (!MA->isRead())
      continue;
    if (!(MA->isOriginalScalarKind() ||
          (AllowArrayLoads && MA->isOriginalArrayKind())))
      continue;

    if (MA->getAccessValue() == InputVal)
      return MA;
  }
  return nullptr;
}

MemoryAccess *polly::getOutputAccessFor(Value *OutputVal, ScopStmt *Stmt) {
  for (auto *MA : *Stmt) {
    if (!MA->isWrite())
      continue;
    if (!MA->isOriginalValueKind())
      continue;

    assert(MA->getAccessValue() == MA->getBaseAddr());
    if (MA->getAccessValue() == OutputVal)
      return MA;
  }
  return nullptr;
}

static bool isRoot(Instruction *Inst) {
  if (isa<LoadInst>(Inst) || isa<StoreInst>(Inst)) // The store is handled by
                                                   // its MemoryAccess. The load
                                                   // must be reached from the
                                                   // roots in order to be
                                                   // marked as used.
    return false;

  if (isa<TerminatorInst>(Inst))
    return true;

  if (Inst->mayReadOrWriteMemory())
    return true;

  return false;
}

static void addRoots(ScopStmt *Stmt, BasicBlock *BB,
                     SmallVectorImpl<VirtualInstruction> &RootInsts) {
  for (auto &Inst : *BB) {
    if (isRoot(&Inst))
      RootInsts.emplace_back(Stmt, &Inst);
  }
}

static bool isEscaping(Scop *S, Instruction *ComputingInst) {
  for (auto &Use : ComputingInst->uses()) {
    auto User = cast<Instruction>(Use.getUser());
    if (!S->contains(User))
      return true;
  }
  return false;
}

static bool isEscaping(MemoryAccess *MA) {
  assert(MA->isOriginalValueKind());
  return isEscaping(MA->getStatement()->getParent(),
                    cast<Instruction>(MA->getAccessValue()));
}

static void addRoots(ScopStmt *Stmt,
                     SmallVectorImpl<VirtualInstruction> &RootInsts,
                     SmallVectorImpl<MemoryAccess *> &RootAccs, bool Local) {
  if (Stmt->isBlockStmt()) {
    addRoots(Stmt, Stmt->getBasicBlock(), RootInsts);
  } else {
    for (auto *BB : Stmt->getRegion()->blocks())
      addRoots(Stmt, BB, RootInsts);
  }

  for (auto *MA : *Stmt) {
    if (!MA->isWrite())
      continue;

    // Writes to arrays are always used
    if (MA->isLatestArrayKind()) {
      // auto Inst = MA->getAccessInstruction();
      // RootInsts.emplace_back(&Stmt, Inst);
      RootAccs.push_back(MA);
    }

    // Values are roots if they are escaping
    else if (MA->isLatestValueKind()) {
      if (Local || isEscaping(MA))
        RootAccs.push_back(MA);
    }

    // Exit phis are, by definition, escaping
    else if (MA->isLatestExitPHIKind()) {
      // auto ComputingInst=  dyn_cast<Instruction>( MA->getAccessValue());
      // if (ComputingInst)
      // Worklist.emplace_back(&Stmt, ComputingInst);
      RootAccs.push_back(MA);
    }

    else if (MA->isLatestPHIKind() && Local)
      RootAccs.push_back(MA);
  }
}

static void markReachable(Scop *S, ArrayRef<VirtualInstruction> Roots,
                          SmallVectorImpl<MemoryAccess *> &&WorklistMA,
                          std::vector<VirtualInstruction> &InstList,
                          DenseSet<MemoryAccess *> &UsedMA, ScopStmt *OnlyLocal,
                          LoopInfo *LI) {
  ScalarDefUseChains DefUse;
  DefUse.compute(S);
  auto *SE = S->getSE();

  SmallVector<SmallVector<VirtualInstruction, 4>, 16> WorklistTree;
  DenseSet<VirtualInstruction> Used;

  WorklistTree.emplace_back();
  auto &Root = WorklistTree.front();
  Root.emplace_back();
  Root.append(Roots.begin(), Roots.end());

  auto AddToWorklist = [&](VirtualUse VUse) {
    if (VUse.getMemAccess())
      WorklistMA.push_back(VUse.getMemAccess());
    if (VUse.isIntra()) {
      auto &Leaf = WorklistTree.back();
      Leaf.emplace_back(VUse.getUser(), cast<Instruction>(VUse.getValue()));
    }
  };

  while (true) {
    auto &Leaf = WorklistTree.back();

    if (!WorklistMA.empty()) {
      auto MA = WorklistMA.pop_back_val();
      if (!MA)
        continue; // Possible for read-only scalars

      if (OnlyLocal && MA->getStatement() != OnlyLocal)
        continue;

      auto Inserted = UsedMA.insert(MA);
      if (!Inserted.second)
        continue;

      auto Stmt = MA->getStatement();
      auto SAI = MA->getScopArrayInfo();
      auto Scope = Stmt->getSurroundingLoop();

      if (MA->isRead() && MA->isOriginalValueKind())
        WorklistMA.push_back(DefUse.getValueDef(SAI));

      if (MA->isRead() && MA->isOriginalAnyPHIKind()) {
        auto &IncomingMAs = DefUse.getPHIIncomings(SAI);
        WorklistMA.append(IncomingMAs.begin(), IncomingMAs.end());
        // Leaf.emplace_back(Stmt, MA->getAccessInstruction());
      }

      if (MA->isRead() && MA->isOriginalArrayKind()) {
        // assert(MemAccInst::isa(MA->getAccessInstruction()));
        // Worklist.emplace_back(Stmt, MA->getAccessInstruction());
        // Leaf.emplace_back(Stmt, MA->getAccessInstruction());
      }

      if (MA->isWrite() && MA->isOriginalValueKind()) {
        auto Val = MA->getAccessValue();
        // If it was synthesizable it would not have a write access.
        auto VUse = VirtualUse::create(Stmt, Val, Scope, SE);
        AddToWorklist(VUse);
      }

      if (MA->isWrite() && MA->isOriginalAnyPHIKind()) {
        for (auto Incoming : MA->getIncoming()) {
          auto VUse = VirtualUse::create(Stmt, Incoming.second,
                                         LI->getLoopFor(Incoming.first), SE);
          AddToWorklist(VUse);
        }
      }

      if (MA->isWrite() && MA->isOriginalArrayKind()) {
        if (MemAccInst::isa(MA->getAccessInstruction()))
          // Worklist.emplace_back(Stmt, MA->getAccessInstruction());
          Leaf.emplace_back(Stmt, MA->getAccessInstruction());
        else {
          assert(MA->isAffine());
          auto VUse = VirtualUse::create(
              Stmt, MA->getAccessValue(),
              LI->getLoopFor(MA->getAccessInstruction()->getParent()), SE);
          AddToWorklist(VUse);
        }
      }

      continue;
    }
    // TODO: Order roots by original order, after all root instructions are
    // known
    auto VInst = Leaf.pop_back_val();
    if (Leaf.empty()) {
      WorklistTree.pop_back();

      if (WorklistTree.empty())
        break;

      InstList.push_back(VInst);

      continue;
    }

    auto *Stmt = VInst.getStmt();
    auto *Inst = VInst.getInstruction();
    if (OnlyLocal && Stmt != OnlyLocal)
      continue;

    auto InsertResult = Used.insert(VInst);
    if (!InsertResult.second)
      continue;

    // This will also cause VInst to be appended to InstList.
    WorklistTree.emplace_back();
    auto &NewLeaf = WorklistTree.back();
    NewLeaf.push_back(VInst);

    // if (isa<PHINode>(Inst)  && Stmt->getEntryBlock() == Inst->getParent()) {
    //	  auto SAI = S->getScopArrayInfo(Inst, ScopArrayInfo::MK_PHI);
    // assert(SAI);
    //	  auto MA = DefUse.getPHIRead(SAI);
    //	  WorklistMA.push_back(MA);
    // } else {
    bool hasMA = false;
    for (auto *MA : *Stmt) {
      if (MA->isOriginalScalarKind() &&
          !(isa<PHINode>(Inst) && MA->isRead() && MA->isPHIKind()))
        continue;
      if (MA->getAccessInstruction() != Inst)
        continue;
      WorklistMA.push_back(MA);
      hasMA = true;
    }

    if (isa<PHINode>(Inst) && hasMA)
      continue;

    for (auto &Use : VInst.operands()) {
      auto VUse = VInst.getVirtualUse(Use, LI);
      AddToWorklist(VUse);
    }
  }
}

void polly::markReachableGlobal(Scop *S,
                                std::vector<VirtualInstruction> &InstList,
                                DenseSet<MemoryAccess *> &UsedMA,
                                LoopInfo *LI) {
  SmallVector<VirtualInstruction, 32> Worklist;
  SmallVector<MemoryAccess *, 32> WorklistMA;

  for (auto &Stmt : *S)
    addRoots(&Stmt, Worklist, WorklistMA, false);

  markReachable(S, Worklist, std::move(WorklistMA), InstList, UsedMA, nullptr,
                LI);
}

void polly::markReachableLocal(ScopStmt *Stmt,
                               std::vector<VirtualInstruction> &InstList,
                               LoopInfo *LI) {
  SmallVector<VirtualInstruction, 32> Worklist;
  SmallVector<MemoryAccess *, 32> WorklistMA;
  DenseSet<MemoryAccess *> UsedMA;
  auto *S = Stmt->getParent();

  addRoots(Stmt, Worklist, WorklistMA, true);
  markReachable(S, Worklist, std::move(WorklistMA), InstList, UsedMA, Stmt, LI);
}

VirtualUse polly::VirtualUse::create(ScopStmt *User, Value *Val, Loop *Scope,
                                     ScalarEvolution *SE) {
  if (isa<llvm::Constant>(Val) || isa<llvm::BasicBlock>(Val))
    return VirtualUse(User, Val, Constant, nullptr);

  if (canSynthesize(Val, *User->getParent(), SE, Scope))
    return VirtualUse(User, Val, Synthesizable, nullptr);

  auto InputMA = getInputAccessOf(Val, User);

  if (isa<Argument>(Val))
    return VirtualUse(User, Val, ReadOnly, InputMA);

  auto S = User->getParent();
  auto Inst = cast<Instruction>(Val);
  if (!S->contains(Inst))
    return VirtualUse(User, Val, ReadOnly, InputMA);

  if (isa<PHINode>(Inst) && Inst->getParent() == User->getEntryBlock())
    return VirtualUse(User, Val, IntraValue, nullptr);

  if (InputMA)
    return VirtualUse(User, Val, InterValue, InputMA);

  return VirtualUse(User, Val, IntraValue, nullptr);
}
