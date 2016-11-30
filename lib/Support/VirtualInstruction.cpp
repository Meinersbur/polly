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

			ScalarValueDeps=0;
			ScalarValueLoopDeps=0;
			ScalarPHIDeps=0;
			ScalarPHILoopDeps=0;
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
  MemoryAccess * polly::getInputAccessOf(Value * InputVal, ScopStmt * Stmt, bool AllowArrayLoads) {
	  for (auto *MA : *Stmt) {
		  if (!MA->isRead())
			  continue;
		  if (!(MA->isLatestScalarKind() || (AllowArrayLoads && MA->isLatestArrayKind())))
			  continue;

		  if (MA->getAccessValue() == InputVal)
			  return MA;
	  }
	  return nullptr;
  }

  MemoryAccess * polly::getOutputAccessFor(Value * OutputVal, ScopStmt * Stmt) {
	  for (auto *MA : *Stmt) {
		  if (!MA->isWrite())
			  continue;
		  if (!MA->isLatestValueKind())
			  continue;

		  assert(MA->getAccessValue() == MA->getBaseAddr());
		  if (MA->getAccessValue() == OutputVal)
			  return MA;
	  }
	  return nullptr;
  }


  static bool isRoot(Instruction *Inst) {
	  if (isa<LoadInst>(Inst) || isa<StoreInst>(Inst))
		  return false;

	  if (Inst->mayReadOrWriteMemory())
		  return true;

	  return false;
  }

  static void addRoots(ScopStmt *Stmt, BasicBlock *BB, SmallVectorImpl<VirtualInstruction> &RootInsts) {
  	for (auto  &Inst : *BB) {
			if (isRoot(&Inst))
				RootInsts.emplace_back(Stmt, &Inst);
		}
	}

  static void addRoots(ScopStmt *Stmt,SmallVectorImpl<VirtualInstruction> &RootInsts,SmallVectorImpl<MemoryAccess*> &RootAccs, bool Local) {
	  if (Stmt->isBlockStmt()) {
			addRoots(Stmt, Stmt->getBasicBlock(), RootInsts);
	  } else {
		  for (auto *BB : Stmt->getRegion()->blocks()) 
			addRoots(Stmt, Stmt->getBasicBlock(), RootInsts);
	  }

	  auto *S = Stmt->getParent();
      for (auto *MA : *Stmt) {
		  if (!MA->isWrite())
			  continue;

		  // Writes to arrays are always used
		  if (MA->isLatestArrayKind()) {
			  //auto Inst = MA->getAccessInstruction();
			  //RootInsts.emplace_back(&Stmt, Inst);
			  RootAccs.push_back(MA);
		  }

		  // Values are roots if they are escaping
		  if (MA->isLatestValueKind()) {
			  if (!Local) {
			   auto ComputingInst = cast<Instruction>( MA->getAccessValue());
			   bool IsEscaping = false;
			   for (auto &Use : ComputingInst->uses()) {
				  auto User = cast<Instruction>( Use.getUser());
				  if (!S->contains(User) ) {
					  IsEscaping= true;
					break;
				  }
			   }

			   if (IsEscaping) {
				   continue;
			   }
				  RootAccs.push_back(MA);
			   }
		  }

		  // Exit phis are, by definition, escaping
		  if (MA->isLatestExitPHIKind()) {
			  //auto ComputingInst=  dyn_cast<Instruction>( MA->getAccessValue());
			  //if (ComputingInst) 
				//Worklist.emplace_back(&Stmt, ComputingInst);
			  RootAccs.push_back(MA);
		  }

		  if (MA->isLatestPHIKind() && Local) 
			  RootAccs.push_back(MA);
	  }
  }


  static void follow(ScopStmt *Stmt, Instruction *Inst,  SmallVectorImpl<Instruction*> &InstList) {
    VirtualInstruction VInst(Stmt,Inst);
  }

  void polly:: computeStmtInstructions(ScopStmt *Stmt, SmallVectorImpl<Instruction*> &InstList)  {
	  SmallVector<Instruction *, 16> Roots;

	  for (auto *MA : *Stmt) {
		  if (MA->isLatestValueKind() && MA->isWrite()) {
			  Roots.push_back(MA->getAccessInstruction());
		  }

		  if (MA->isLatestArrayKind() && MA->isWrite()) {
			  Roots.push_back( MA->getAccessInstruction());
		  }

		  if (MA->isLatestExitPHIKind() && MA->isWrite()) {
			  for (auto Incoming : MA->getIncoming()) {
				  auto IncomingInst = dyn_cast<Instruction>(Incoming.second);
				  if (!IncomingInst)
					  continue;
				  Roots.push_back(IncomingInst);
			  }
		  }
	  }

	  if (Stmt->isBlockStmt()) {
		for (auto  &Inst : *Stmt->getBasicBlock()) {
			if (isRoot(&Inst))
				Roots.push_back(&Inst);
		}
	  } else {
		  for (auto *BB : Stmt->getRegion()->blocks()) {
			  for (auto  &Inst : *Stmt->getBasicBlock()) {
				  if (isRoot(&Inst))
					  Roots.push_back(&Inst);
			  }
		  }
	  }

	  
	  for ( auto *Root : Roots) {
		  //follow(Root);
	  }
	  
	  DenseSet<Instruction * > Visited;



	  std::reverse(InstList.begin(), InstList.end());
  }
