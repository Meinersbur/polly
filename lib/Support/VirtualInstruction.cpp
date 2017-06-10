//===------ VirtualInstruction.cpp ------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Tools for determining which instructions are within a statement and the
// nature of their operands.
//
//===----------------------------------------------------------------------===//

#include "polly/Support/VirtualInstruction.h"
#include "polly/Support/SCEVValidator.h"
#include "polly/ScopBuilder.h"

using namespace polly;
using namespace llvm;

static bool isInLoop(MemoryAccess *MA) {
  auto Stmt = MA->getStatement();
  return Stmt->getNumIterators() > 0;
}

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

static bool isDefinedInStmt(Value *Val, ScopStmt *Stmt) {
  auto *Inst = dyn_cast<Instruction>(Val);
  if (!Inst)
    return false;
  return Stmt->contains(Inst);
}
MemoryAccess *polly::getOutputAccessFor(Value *OutputVal, ScopStmt *Stmt) {
  for (auto *MA : *Stmt) {
    if (!MA->isWrite())
      continue;
    if (!MA->isOriginalValueKind())
      continue;

    // assert(MA->getAccessValue() == MA->getBaseAddr());
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

    // Writes to arrays are always used.
    if (MA->isLatestArrayKind()) {
      // auto Inst = MA->getAccessInstruction();
      // RootInsts.emplace_back(&Stmt, Inst);
      RootAccs.push_back(MA);
    }

    // Values are roots if they are escaping.
    else if (MA->isLatestValueKind()) {
      if (Local || isEscaping(MA))
        RootAccs.push_back(MA);
    }

    // Exit phis are, by definition, escaping.
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


static void walkReachable(Scop *S ,LoopInfo *LI,
	ArrayRef<VirtualInstruction> RootInsts, ArrayRef<MemoryAccess*> RootAccs, 
	DenseSet<VirtualInstruction> &UsedInsts, 	DenseSet<MemoryAccess *> &UsedAccs,
	ScopStmt  *OnlyLocal) {

	UsedInsts.clear();
	UsedAccs.clear();

	ScalarDefUseChains DefUse;
	DefUse.compute(S);

	SmallVector<VirtualInstruction, 32> WorklistInsts;
	SmallVector<MemoryAccess*, 32> WorklistAccs;
	
	WorklistInsts.append(RootInsts.begin(), RootInsts.end());
	WorklistAccs.append(RootAccs.begin(), RootAccs.end());

	auto AddToWorklist = [&](VirtualUse VUse) {
		switch (VUse.getKind()) {
		case VirtualUse::Block:
		case VirtualUse::Constant:
		case VirtualUse::Synthesizable:
		case VirtualUse::Hoisted:
			break;
		case VirtualUse::ReadOnly:
			if (!ModelReadOnlyScalars)
				break;
			LLVM_FALLTHROUGH;
		case VirtualUse::Inter:
			WorklistAccs.push_back(VUse.getMemoryAccess());
			break;
		case VirtualUse::Intra:
			WorklistInsts.emplace_back(VUse.getUser(), cast<Instruction>( VUse.getValue()));
			break;
		}
	};

	while (true) {

		while (!WorklistAccs.empty()) {
			auto *Acc = WorklistAccs.pop_back_val();

			auto *Stmt = Acc->getStatement();
			if (OnlyLocal && Stmt != OnlyLocal)
				continue;

			auto Inserted = UsedAccs.insert(Acc);
			if (!Inserted.second)
				continue;

			if (Acc->isRead()) {
				auto *SAI = Acc->getScopArrayInfo();

				if (Acc->isOriginalValueKind())
					WorklistAccs.push_back(DefUse.getValueDef(SAI));

				if (Acc->isOriginalAnyPHIKind()) {
					auto &IncomingMAs = DefUse.getPHIIncomings(SAI);
					WorklistAccs.append(IncomingMAs.begin(), IncomingMAs.end());
				}
			}

			if (Acc->isWrite()) {
				if (Acc->isOriginalValueKind() || Acc->isOriginalArrayKind()) {
					auto *Scope = Stmt->getSurroundingLoop();
					// If it was synthesizable it would not have a write access.
					auto VUse = VirtualUse::create(S, Stmt, Scope, Acc->getAccessValue(), true);
					AddToWorklist(VUse);
				}

				if (Acc->isOriginalAnyPHIKind()) {
					for (auto Incoming : Acc->getIncoming()) {
						auto VUse = VirtualUse::create(S, Stmt, LI->getLoopFor(Incoming.first), Incoming.second, true);
						AddToWorklist(VUse);
					}
				}

				if (Acc->isExplicit()) 
					WorklistInsts.emplace_back(Stmt, Acc->getAccessInstruction());
			}
		}


		
		if (WorklistInsts.empty())
			break; 

		auto VInst = WorklistInsts.pop_back_val();
		auto *Stmt = VInst.getStmt();
		auto *Inst = VInst.getInstruction();

		if (OnlyLocal && Stmt != OnlyLocal)
			continue;

		auto InsertResult = UsedInsts.insert(VInst);
		if (!InsertResult.second)
			continue;



		for (auto VUse : VInst.operands()) {
			//auto VUse = VirtualUse::create(S, Use, LI, true);
			AddToWorklist(VUse);
		}

		auto Accs = Stmt->lookupArrayAccessesFor(Inst);
		if (!Accs)
			continue;

		for (auto Acc : *Accs)
			WorklistAccs.push_back(Acc);
	}
}


static void markReachable2(Scop *S, ArrayRef<VirtualInstruction> Roots,
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

  auto PrintMAStatus = [&](MemoryAccess *MA, int Indent = 2) {
    if (UsedMA.count(MA))
      errs().indent(Indent) << "[*] " << MA << "\n";
    else if (std::find(WorklistMA.begin(), WorklistMA.end(), MA) !=
             WorklistMA.end())
      errs().indent(Indent) << "[?] " << MA << "\n";
    else
      errs().indent(Indent) << "[ ] " << MA << "\n";
  };

  auto PrintVInst = [&](VirtualInstruction VInst) {
    if (!VInst.getInstruction() || !VInst.getStmt()) {
      errs() << "<null>";
      return;
    }
    errs() << "[" << VInst.getStmt()->getBaseName() << "] ";
    VInst.getInstruction()->print(errs(), true);
  };

  auto PrintVIStatus = [&](VirtualInstruction VInst, bool Extra) {
    auto *Inst = VInst.getInstruction();
    auto *Stmt = VInst.getStmt();

    int Level = WorklistTree.size();
    int Op = -1;
    while (true) {
      if (Level < 0)
        break;

      if (Op < 0) {
        Level -= 1;
        Op = (Level >= 0) ? WorklistTree[Level].size() - 1 : -1;
        continue;
      }

      if (WorklistTree[Level][Op] == VInst) {
        // Match
        break;
      }

      Op -= 1;
    }

    if (Level >= 0) {
      if (Op) {
        errs() << "  [" << Level << "." << Op << "] ";
        Inst->print(errs(), true);
        errs() << "\n";
      } else {
        errs() << "  [" << Level << "] ";
        Inst->print(errs(), true);
        errs() << "\n";
      }
    } else if (Used.count(VInst)) {
      errs() << "  [" << (Extra ? '#' : '*') << "] ";
      Inst->print(errs(), true);
      errs() << "\n";
    } else if (canSynthesize(Inst, *S, SE, Stmt->getSurroundingLoop())) {
      errs() << "      ";
      Inst->print(errs(), true);
      errs() << "\n";
    } else {
      errs() << "  [ ] ";
      Inst->print(errs(), true);
      errs() << "\n";
    }
  };

  auto PrintMarked = [&]() {
    for (auto &Stmt : *S) {
      errs() << Stmt.getBaseName() << ":\n";
      for (auto *MA : Stmt) {
        if (!MA->isImplicit())
          continue;
        if (!MA->isRead())
          continue;
        PrintMAStatus(MA);
      }
      for (auto VInst : InstList) {
        if (VInst.getStmt() != &Stmt)
          continue;
        auto Inst = VInst.getInstruction();
        if (Inst->getParent() == Stmt.getEntryBlock())
          continue;
        PrintVIStatus(VInst, true);
        // errs() << "  [#] "; Inst->printAsOperand(errs(), false); errs() <<
        // "\n";
        if (auto MA = Stmt.getArrayAccessOrNULLFor(Inst))
          PrintMAStatus(MA, 4);
      }
      errs() << "  "
                "--------------------------------------------------------------"
                "----------------\n";
      for (auto &Inst : *Stmt.getEntryBlock()) {
        PrintVIStatus({&Stmt, &Inst}, false);
        if (auto MA = Stmt.getArrayAccessOrNULLFor(&Inst))
          PrintMAStatus(MA, 4);
      }
      for (auto *MA : Stmt) {
        if (!MA->isImplicit())
          continue;
        if (!MA->isWrite())
          continue;
        PrintMAStatus(MA);
      }
    }
  };

  auto PrintTree = [&]() {
    int Level = 0;
    for (; Level < (int)WorklistTree.size(); Level += 1) {
      for (int Op = !Level; Op < (int)WorklistTree[Level].size(); Op += 1) {
        if (Op == 0)
          errs().indent(Level * 4 - 4) << "->";
        else
          errs().indent(2 + Level * 4);
        PrintVInst(WorklistTree[Level][Op]);
        errs() << "\n";
      }
    }
    for (auto MA : WorklistMA) {
      errs().indent(Level * 4) << MA << "\n";
    }
  };

  auto AddToWorklist = [&](VirtualUse VUse) {
    if (VUse.getMemoryAccess())
      WorklistMA.push_back(VUse.getMemoryAccess());
    if (VUse.isIntra()) {
      auto &Leaf = WorklistTree.back();
      Leaf.emplace_back(VUse.getUser(), cast<Instruction>(VUse.getValue()));
    }
  };

  while (true) {
#if 0
	  errs()<<"### Mark\n"; PrintMarked();
	  errs()<<"\n### Worklist stack\n";
	  PrintTree();
	  errs()<<"\n\n";
#endif
    auto &Leaf = WorklistTree.back();

    if (!WorklistMA.empty()) {
      auto *MA = WorklistMA.pop_back_val();
      if (!MA)
        continue; // Possible for read-only scalars

      if (OnlyLocal && MA->getStatement() != OnlyLocal)
        continue;

      auto Inserted = UsedMA.insert(MA);
      if (!Inserted.second)
        continue;

      auto *Stmt = MA->getStatement();
      auto *SAI = MA->getScopArrayInfo();
      auto *Scope = Stmt->getSurroundingLoop();

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
        auto VUse =
            VirtualUse::create(Stmt->getParent(), Stmt, Scope, Val, true);
        AddToWorklist(VUse);
      }

      if (MA->isWrite() && MA->isOriginalAnyPHIKind()) {
        // auto *PHI = cast<PHINode>(MA->getAccessInstruction ());
        for (auto Incoming : MA->getIncoming()) {
          // auto &U = PHI->getOperandUse(
          // PHI->getBasicBlockIndex(Incoming.first) );  auto VUse =
          // VirtualUse::create(Stmt,  U, LI);
          auto VUse = VirtualUse::create(Stmt->getParent(), Stmt,
                                         LI->getLoopFor(Incoming.first),
                                         Incoming.second, true);
          // auto VUse = VirtualUse::create(Stmt, Incoming.second,
          // LI->getLoopFor(Incoming.first), SE);
          AddToWorklist(VUse);
        }
      }

      if (MA->isWrite() && MA->isOriginalArrayKind()) {
        if (MemAccInst::isa(MA->getAccessInstruction())) {
          // Worklist.emplace_back(Stmt, MA->getAccessInstruction());
          Leaf.emplace_back(Stmt, MA->getAccessInstruction());
        } else {
          assert(MA->isAffine());
          auto VUse = VirtualUse::create(
              Stmt->getParent(), Stmt,
              LI->getLoopFor(MA->getAccessInstruction()->getParent()),
              MA->getAccessValue(), true);
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

    if (Inst->getName().startswith("mul16.i")) {
      int a = 0;
    }

    if (Inst->getName() == "tmp62") {
      int b = 0;
    }

    // This will also cause VInst to be appended to InstList later.
    WorklistTree.emplace_back();
    auto &NewLeaf = WorklistTree.back();
    NewLeaf.push_back(VInst);

    // TODO: Use VirtualUse

    // if (isa<PHINode>(Inst)  && Stmt->getEntryBlock() == Inst->getParent()) {
    //	  auto SAI = S->getScopArrayInfo(Inst, ScopArrayInfo::MK_PHI);
    // assert(SAI);
    //	  auto MA = DefUse.getPHIRead(SAI);
    //	  WorklistMA.push_back(MA);
    // } else {
    bool hasMA = false;
    MemoryAccess *FoundMA = nullptr;
    for (auto *MA : *Stmt) {
      if (MA->isOriginalScalarKind() &&
          !(isa<PHINode>(Inst) && MA->isRead() && MA->isPHIKind()))
        continue;
      if (MA->getAccessInstruction() != Inst)
        continue;
      WorklistMA.push_back(MA);
      hasMA = true;

      FoundMA = MA;
    }

    if (isa<PHINode>(Inst) && hasMA)
      continue;

    for (auto &Use : Inst->operands()) {
      auto UseInst = dyn_cast<Instruction>(Use.get());
      if (!UseInst)
        continue;

      auto VUse = VInst.getIntraVirtualUse(UseInst);
      AddToWorklist(VUse);
    }
  }
  assert(Used.size() == InstList.size());

  // The worklist tree above exist to ensure postorder traversal order such that
  // instructions appear before their uses. Unfortunately this does not also
  // ensure that explicit Load/Store are in the original order. We'll have to
  // explicitly sort to ensure this, at least the instructions in the ScopStmt's
  // BB/Region. Currently BlockGenerator does this.
  std::vector<VirtualInstruction> ResultList;
  ResultList.reserve(InstList.size());
  for (auto VInst : InstList) {
    if (!isDefinedInStmt(VInst.getInstruction(), VInst.getStmt()))
      ResultList.push_back(VInst);
  }
  for (auto &Stmt : *S) {
    auto AddUsedVInstsFromBlock = [&](BasicBlock *BB) {
      for (auto &Inst : *BB) {
        auto VInst = VirtualInstruction(&Stmt, &Inst);
        if (Used.count(VInst))
          ResultList.push_back(VInst);
      }
    };
    if (Stmt.isCopyStmt()) {
    } else if (Stmt.isBlockStmt()) {
      AddUsedVInstsFromBlock(Stmt.getBasicBlock());
    } else {
      for (auto BB : Stmt.getRegion()->blocks())
        AddUsedVInstsFromBlock(BB);
    }
  }
  assert(InstList.size() == ResultList.size());
  std::swap(InstList, ResultList);
}


void polly::markReachable(Scop *S, LoopInfo *LI,
	DenseSet<VirtualInstruction> &UsedInsts, DenseSet<MemoryAccess *> &UsedAccs,
	ScopStmt  *OnlyLocal) {

	SmallVector<VirtualInstruction, 32> RootInsts;
	SmallVector<MemoryAccess *, 32> RootAccs;

	if (OnlyLocal) {
		addRoots(OnlyLocal, RootInsts, RootAccs, true);
	} 	else {
		for (auto &Stmt : *S)
			addRoots(&Stmt, RootInsts, RootAccs, false);
	}

	walkReachable(S,  LI, RootInsts, RootAccs, UsedInsts, UsedAccs, OnlyLocal);
}


void polly::markReachableGlobal(Scop *S,
                                std::vector<VirtualInstruction> &InstList,
                                DenseSet<MemoryAccess *> &UsedMA,
                                LoopInfo *LI) {
  SmallVector<VirtualInstruction, 32> Worklist;
  SmallVector<MemoryAccess *, 32> WorklistMA;

  for (auto &Stmt : *S)
    addRoots(&Stmt, Worklist, WorklistMA, false);

  markReachable2(S, Worklist, std::move(WorklistMA), InstList, UsedMA, nullptr,
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
  markReachable2(S, Worklist, std::move(WorklistMA), InstList, UsedMA, Stmt, LI);
}

VirtualUse VirtualUse::create(Scop *S, const Use &U, LoopInfo *LI,
                              bool Virtual) {
  auto *UserBB = getUseBlock(U);
  auto *UserStmt = S->getStmtFor(UserBB);
  auto *UserScope = LI->getLoopFor(UserBB);
  return create(S, UserStmt, UserScope, U.get(), Virtual);
}

VirtualUse VirtualUse::create(Scop *S, ScopStmt *UserStmt, Loop *UserScope,
                              Value *Val, bool Virtual) {
  assert(!isa<StoreInst>(Val) && "a StoreInst cannot be used");

  if (isa<BasicBlock>(Val))
    return VirtualUse(UserStmt, Val, Block, nullptr, nullptr);

  if (isa<llvm::Constant>(Val))
    return VirtualUse(UserStmt, Val, Constant, nullptr, nullptr);

  // Is the value synthesizable? If the user has been pruned
  // (UserStmt == nullptr), it is either not used anywhere or is synthesizable.
  // We assume synthesizable which practically should have the same effect.
  auto *SE = S->getSE();
  if (SE->isSCEVable(Val->getType())) {
    auto *ScevExpr = SE->getSCEVAtScope(Val, UserScope);
    if (!UserStmt || canSynthesize(Val, *UserStmt->getParent(), SE, UserScope))
      return VirtualUse(UserStmt, Val, Synthesizable, ScevExpr, nullptr);
  }

  // FIXME: Inconsistency between lookupInvariantEquivClass and
  // getRequiredInvariantLoads. Querying one of them should be enough.
  auto &RIL = S->getRequiredInvariantLoads();
  if (S->lookupInvariantEquivClass(Val) || RIL.count(dyn_cast<LoadInst>(Val)))
    return VirtualUse(UserStmt, Val, Hoisted, nullptr, nullptr);

  // ReadOnly uses may have MemoryAccesses that we want to associate with the
  // use. This is why we look for a MemoryAccess here already.
  MemoryAccess *InputMA = nullptr;
  if (UserStmt && Virtual)
    InputMA = UserStmt->lookupValueReadOf(Val);

  // Uses are read-only if they have been defined before the SCoP, i.e., they
  // cannot be written to inside the SCoP. Arguments are defined before any
  // instructions, hence also before the SCoP. If the user has been pruned
  // (UserStmt == nullptr) and is not SCEVable, assume it is read-only as it is
  // neither an intra- nor an inter-use.
  if (!UserStmt || isa<Argument>(Val))
    return VirtualUse(UserStmt, Val, ReadOnly, nullptr, InputMA);

  auto Inst = cast<Instruction>(Val);
  if (!S->contains(Inst))
    return VirtualUse(UserStmt, Val, ReadOnly, nullptr, InputMA);

  // A use is inter-statement if either it is defined in another statement, or
  // there is a MemoryAccess that reads its value that has been written by
  // another statement.
  if (InputMA || (!Virtual && !UserStmt->contains(Inst->getParent())))
    return VirtualUse(UserStmt, Val, Inter, nullptr, InputMA);

  return VirtualUse(UserStmt, Val, Intra, nullptr, nullptr);
}

VirtualInstruction VirtualUse:: getDefinition() const {
	switch (getKind()) {
	case Intra:
		return VirtualInstruction(User, cast<Instruction>(Val));
	case Inter: {
		auto *S = User->getParent();
		auto *Inst = cast<Instruction>(Val);
		ScalarDefUseChains DefUse; DefUse.compute(S);
		auto SAI = InputMA->getOriginalScopArrayInfo();
		auto *DefStmt = DefUse.getValueDef(SAI)->getStatement();
		return VirtualInstruction(DefStmt, Inst);
	}
	default:
		llvm_unreachable("Only non-synthesizable instructions are represented by as VirtualInstructions");
	}
}

void VirtualUse::print(raw_ostream &OS, bool Reproducible) const {
  OS << "User: [" << User->getBaseName() << "] ";
  switch (Kind) {
  case VirtualUse::Constant:
    OS << "Constant Op:";
    break;
  case VirtualUse::Block:
    OS << "BasicBlock Op:";
    break;
  case VirtualUse::Synthesizable:
    OS << "Synthesizable Op:";
    break;
  case VirtualUse::Hoisted:
    OS << "Hoisted load Op:";
    break;
  case VirtualUse::ReadOnly:
    OS << "Read-Only Op:";
    break;
  case VirtualUse::Intra:
    OS << "Intra Op:";
    break;
  case VirtualUse::Inter:
    OS << "Inter Op:";
    break;
  }

  if (Val) {
    OS << ' ';
    if (Reproducible)
      OS << '"' << Val->getName() << '"';
    else
      Val->print(OS, true);
  }
  if (ScevExpr) {
    OS << ' ';
    ScevExpr->print(OS);
  }
  if (InputMA && !Reproducible)
    OS << ' ' << InputMA;
}

#if !defined(NDEBUG) || defined(LLVM_ENABLE_DUMP)
void VirtualUse::dump() const {
  print(errs(), false);
  errs() << '\n';
}
#endif

void VirtualInstruction::dump() const {
  errs() << "[" << getStmt()->getBaseName() << "]";
  getInstruction()->dump();
}
