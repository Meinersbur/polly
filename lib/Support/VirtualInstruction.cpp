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

  void polly:: computeStmtInstructions(ScopStmt *Stmt, SmallVectorImpl<Instruction*> &InstList)  {

	  
	  DenseSet<Instruction * > Visited;


	  std::reverse(InstList.begin(), InstList.end());
  }
