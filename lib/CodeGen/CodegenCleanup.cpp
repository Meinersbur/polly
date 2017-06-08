//===- CodegenCleanup.cpp -------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "polly/CodeGen/CodegenCleanup.h"

#include "llvm/Analysis/ScopedNoAliasAA.h"
#include "llvm/Analysis/TypeBasedAliasAnalysis.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/PassInfo.h"
#include "llvm/PassRegistry.h"
#include "llvm/PassSupport.h"
#include "llvm/Support/Debug.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Analysis/LoopPass.h"
//#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#define DEBUG_TYPE "polly-cleanup"

using namespace llvm;
using namespace polly;

namespace {

class CodegenCleanup : public FunctionPass {
private:
  CodegenCleanup(const CodegenCleanup &) = delete;
  const CodegenCleanup &operator=(const CodegenCleanup &) = delete;

  llvm::legacy::FunctionPassManager *FPM;

public:
  static char ID;
  explicit CodegenCleanup() : FunctionPass(ID), FPM(nullptr) {}

  /// @name FunctionPass interface
  //@{
  virtual void getAnalysisUsage(llvm::AnalysisUsage &AU) const override {}

  virtual bool doInitialization(Module &M) override {
    assert(!FPM);

    FPM = new llvm::legacy::FunctionPassManager(&M);

    // TODO: How to make parent passes discoverable?
    // TODO: Should be sensitive to compiler options in PassManagerBuilder, to
    // which we do not have access here.
    FPM->add(createScopedNoAliasAAWrapperPass());
    FPM->add(createTypeBasedAAWrapperPass());
    FPM->add(createAAResultsWrapperPass());

    // TODO: These are non-conditional passes that run between
    // EP_ModuleOptimizerEarly and EP_VectorizerStart just to ensure we do not
    // miss any optimization that would have run after Polly with
    // -polly-position=early. This can probably be reduced to a more compact set
    // of passes.
    FPM->add(createCFGSimplificationPass());
    FPM->add(createSROAPass());
    FPM->add(createEarlyCSEPass());
    FPM->add(createInstructionCombiningPass());
    FPM->add(createJumpThreadingPass());
    FPM->add(createCorrelatedValuePropagationPass());
    FPM->add(createCFGSimplificationPass());
    FPM->add(createInstructionCombiningPass());
    FPM->add(createCFGSimplificationPass());
    FPM->add(createReassociatePass());
    FPM->add(createLoopRotatePass());
    FPM->add(createLICMPass());
    FPM->add(createLoopUnswitchPass());
    FPM->add(createCFGSimplificationPass());
    FPM->add(createInstructionCombiningPass());
    FPM->add(createIndVarSimplifyPass());
    FPM->add(createLoopIdiomPass());
    FPM->add(createLoopDeletionPass());
    FPM->add(createCFGSimplificationPass());
    FPM->add(createSimpleLoopUnrollPass());
    FPM->add(createMergedLoadStoreMotionPass());
    FPM->add(createMemCpyOptPass());
    FPM->add(createBitTrackingDCEPass());
    FPM->add(createInstructionCombiningPass());
    FPM->add(createJumpThreadingPass());
    FPM->add(createCorrelatedValuePropagationPass());
    FPM->add(createDeadStoreEliminationPass());
    FPM->add(createLICMPass());
    FPM->add(createLoopRerollPass());
    FPM->add(createAggressiveDCEPass());
    FPM->add(createCFGSimplificationPass());
    FPM->add(createInstructionCombiningPass());

    return FPM->doInitialization();
  }

  virtual bool doFinalization(Module &M) override {
    bool Result = FPM->doFinalization();

    delete FPM;
    FPM = nullptr;

    return Result;
  }

  virtual bool runOnFunction(llvm::Function &F) override {
    if (!F.hasFnAttribute("polly-optimized")) {
      DEBUG(dbgs() << F.getName()
                   << ": Skipping cleanup because Polly did not optimize it.");
      return false;
    }

    DEBUG(dbgs() << F.getName() << ": Running codegen cleanup...");
    return FPM->run(F);
  }
  //@}
};

char CodegenCleanup::ID;
} // namespace

FunctionPass *polly::createCodegenCleanupPass() { return new CodegenCleanup(); }

INITIALIZE_PASS_BEGIN(CodegenCleanup, "polly-cleanup",
                      "Polly - Cleanup after code generation", false, false)
INITIALIZE_PASS_END(CodegenCleanup, "polly-cleanup",
                    "Polly - Cleanup after code generation", false, false)

namespace {


class FunctionPassWrapper : public FunctionPass {
private:
  FunctionPassWrapper(const FunctionPassWrapper &) = delete;
  const FunctionPassWrapper &operator=(const FunctionPassWrapper &) = delete;

  std::unique_ptr<FunctionPass> InnerPass;
  std::string PassName;

public:
  explicit FunctionPassWrapper(char &ID, std::unique_ptr<FunctionPass> Inner)
      : FunctionPass(ID), InnerPass(Inner.release()),
        PassName((Twine(InnerPass->getPassName()) + " (wrapped)").str()) {}

  virtual StringRef getPassName() const override { return PassName; }

  virtual void print(raw_ostream &O, const Module *M) const override {
    InnerPass->print(O, M);
  }

  virtual void getAnalysisUsage(llvm::AnalysisUsage &AU) const override {
    return InnerPass->getAnalysisUsage(AU);
  }

  virtual bool doInitialization(Module &M) override {
    return InnerPass->doInitialization(M);
  }

  virtual bool doFinalization(Module &M) override {
    return InnerPass->doFinalization(M);
  }

  virtual bool runOnFunction(llvm::Function &F) override {
    if (!F.hasFnAttribute("polly-optimized")) {
      DEBUG(dbgs() << F.getName()
                   << ": Skipping cleanup because Polly did not optimize it.");
      return false;
    }

    InnerPass->setResolver(getResolver());
    return InnerPass->runOnFunction(F);
  }

  virtual void releaseMemory() override { InnerPass->releaseMemory(); }

  virtual void verifyAnalysis() const override {
	  return InnerPass->verifyAnalysis();
  }



  virtual Pass *createPrinterPass(raw_ostream &O,
                                  const std::string &Banner) const override {
    return InnerPass->createPrinterPass(O, Banner);
  }

#if 0
  virtual void assignPassManager(PMStack &Stack,
                                 PassManagerType PMType) override {
    return InnerPass->assignPassManager(Stack, PMType);
  }

  /// Check if available pass managers are suitable for this pass or not.
  virtual void preparePassManager(PMStack &Stack) {
    return InnerPass->preparePassManager(Stack);
  }

  ///  Return what kind of Pass Manager can manage this pass.
  virtual PassManagerType getPotentialPassManagerType() const {
    return InnerPass->getPotentialPassManagerType();
  }
#endif 

#if 0
  virtual ImmutablePass *getAsImmutablePass() override {
	  return InnerPass->getAsImmutablePass();
  }
  virtual PMDataManager *getAsPMDataManager() override {
	  return InnerPass->getAsPMDataManager();
  }
#endif

  /// getAdjustedAnalysisPointer - This method is used when a pass implements
  /// an analysis interface through multiple inheritance.  If needed, it should
  /// override this to adjust the this pointer as needed for the specified pass
  /// info.
  virtual void *getAdjustedAnalysisPointer(AnalysisID ID) override {
    return InnerPass->getAdjustedAnalysisPointer(ID);
  }



  // dumpPassStructure - Implement the -debug-passes=PassStructure option
  virtual void dumpPassStructure(unsigned Offset) {
    return InnerPass->dumpPassStructure(Offset);
  }
};


class LoopPassWrapper : public LoopPass {
private:
	LoopPassWrapper(const LoopPassWrapper &) = delete;
	const LoopPassWrapper &operator=(const LoopPassWrapper &) = delete;

	std::unique_ptr<LoopPass> InnerPass;
	std::string PassName;

public:
	explicit LoopPassWrapper(char &ID, std::unique_ptr<LoopPass> Inner)
		: LoopPass(ID), InnerPass(Inner.release()),
		PassName((Twine(InnerPass->getPassName()) + " (wrapped)").str()) {}

	virtual StringRef getPassName() const override { return PassName; }

	virtual void print(raw_ostream &O, const Module *M) const override {
		InnerPass->print(O, M);
	}

	virtual void getAnalysisUsage(llvm::AnalysisUsage &AU) const override {
		return InnerPass->getAnalysisUsage(AU);
	}

	virtual bool doInitialization(Module &M) override {
		return InnerPass->doInitialization(M);
	}

	virtual bool doFinalization(Module &M) override {
		return InnerPass->doFinalization(M);
	}

	virtual bool runOnLoop(Loop *L, LPPassManager &LPM) override {
		auto  *F = L->getHeader()->getParent();
		if (!F->hasFnAttribute("polly-optimized")) {
			DEBUG(dbgs() << F->getName()
				<< ": Skipping cleanup because Polly did not optimize it.");
			return false;
		}

		InnerPass->setResolver(getResolver());
		return InnerPass->runOnLoop(L, LPM);
	}

	virtual void releaseMemory() override { InnerPass->releaseMemory(); }

	virtual void verifyAnalysis() const override {
		return InnerPass->verifyAnalysis();
	}



	virtual Pass *createPrinterPass(raw_ostream &O,
		const std::string &Banner) const override {
		return InnerPass->createPrinterPass(O, Banner);
	}

#if 0
	virtual void assignPassManager(PMStack &Stack,
		PassManagerType PMType) override {
		return InnerPass->assignPassManager(Stack, PMType);
	}

	/// Check if available pass managers are suitable for this pass or not.
	virtual void preparePassManager(PMStack &Stack) {
		return InnerPass->preparePassManager(Stack);
	}

	///  Return what kind of Pass Manager can manage this pass.
	virtual PassManagerType getPotentialPassManagerType() const {
		return InnerPass->getPotentialPassManagerType();
	}
#endif 

#if 0
	virtual ImmutablePass *getAsImmutablePass() override {
		return InnerPass->getAsImmutablePass();
	}
	virtual PMDataManager *getAsPMDataManager() override {
		return InnerPass->getAsPMDataManager();
	}
#endif

	/// getAdjustedAnalysisPointer - This method is used when a pass implements
	/// an analysis interface through multiple inheritance.  If needed, it should
	/// override this to adjust the this pointer as needed for the specified pass
	/// info.
	virtual void *getAdjustedAnalysisPointer(AnalysisID ID) override {
		return InnerPass->getAdjustedAnalysisPointer(ID);
	}



	// dumpPassStructure - Implement the -debug-passes=PassStructure option
	virtual void dumpPassStructure(unsigned Offset) {
		return InnerPass->dumpPassStructure(Offset);
	}
};


DenseMap<AnalysisID, std::unique_ptr<char>> ExistingWrappers;

FunctionPassWrapper *wrapCleanupPass(FunctionPass *Pass) {
  auto &WrapperID = ExistingWrappers[Pass->getPassID()];
  if (!WrapperID) {
    WrapperID.reset(new char());
  }

  return new FunctionPassWrapper(*WrapperID.get(), std::unique_ptr<FunctionPass>(Pass));
}

LoopPassWrapper *wrapCleanupPass(LoopPass *Pass) {
	auto &WrapperID = ExistingWrappers[Pass->getPassID()];
	if (!WrapperID) {
		WrapperID.reset(new char());
	}

	return new LoopPassWrapper(*WrapperID.get(), std::unique_ptr<LoopPass>(Pass));
}
}

void polly::addCleanupPasses(llvm::legacy::PassManagerBase &PM) {
// From PassManagerBuilder::populateFunctionPassManager
	// -tti -targetlibinfo -tbaa -scoped-noalias -assumption-cache-tracker -verify -simplifycfg -domtree -sroa -early-cse -lower-expect
	PM.add(wrapCleanupPass(createCFGSimplificationPass()));
	PM.add(wrapCleanupPass(createSROAPass()));
	PM.add(wrapCleanupPass(createEarlyCSEPass()));
	PM.add(wrapCleanupPass(createLowerExpectIntrinsicPass()));

	// From PassManagerBuilder::populateModulePassManager (polly-position=early)
	// -tti -targetlibinfo -tbaa -scoped-noalias -assumption-cache-tracker -profile-summary-info -forceattrs -inferattrs -domtree -mem2reg -basicaa -aa -instcombine -simplifycfg -tailcallelim -simplifycfg -reassociate -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -loop-rotate -instcombine -loop-simplify -lcssa-verification -lcssa -scalar-evolution -indvars -polly-prepare -polly-dump-module -domtree -loops -scalar-evolution -basicaa -aa -postdomtree -domfrontier -regions -polly-detect -polly-scops -polly-prune-unprofitable -polly-dependences -polly-opt-isl -polly-ast -polly-codegen -barrier -ipsccp -globalopt -domtree -mem2reg -deadargelim -domtree -basicaa -aa -instcombine -simplifycfg -basiccg -globals-aa -prune-eh -inline -functionattrs -argpromotion -domtree -sroa -early-cse -domtree -basicaa -aa -lazy-value-info -jump-threading -correlated-propagation -simplifycfg -domtree -basicaa -aa -instcombine -libcalls-shrinkwrap -loops -branch-prob -block-freq -pgo-memop-opt -tailcallelim -simplifycfg -reassociate -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -loop-rotate -licm -loop-unswitch -simplifycfg -domtree -basicaa -aa -instcombine -loops -loop-simplify -lcssa-verification -lcssa -scalar-evolution -indvars -loop-idiom -loop-deletion -loop-unroll -mldst-motion -aa -memdep -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -gvn -basicaa -aa -memdep -memcpyopt -sccp -domtree -demanded-bits -bdce -basicaa -aa -instcombine -lazy-value-info -jump-threading -correlated-propagation -domtree -basicaa -aa -memdep -dse -loops -loop-simplify -lcssa-verification -lcssa -aa -scalar-evolution -licm -postdomtree -adce -simplifycfg -domtree -basicaa -aa -instcombine -barrier -elim-avail-extern -basiccg -rpo-functionattrs -globals-aa -float2int -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -loop-rotate -loop-accesses -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -loop-distribute -branch-prob -block-freq -scalar-evolution -basicaa -aa -loop-accesses -demanded-bits -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -loop-vectorize -loop-simplify -scalar-evolution -aa -loop-accesses -loop-load-elim -basicaa -aa -instcombine -scalar-evolution -demanded-bits -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -slp-vectorizer -latesimplifycfg -domtree -basicaa -aa -instcombine -loops -loop-simplify -lcssa-verification -lcssa -scalar-evolution -loop-unroll -instcombine -loop-simplify -lcssa-verification -lcssa -scalar-evolution -licm -alignment-from-assumptions -strip-dead-prototypes -globaldce -constmerge -domtree -loops -branch-prob -block-freq -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -branch-prob -block-freq -loop-sink -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -instsimplify -simplifycfg
	
	// From PassManagerBuilder::populateModulePassManager (polly-position=before-vectorizer)
	// -tti -targetlibinfo -tbaa -scoped-noalias -assumption-cache-tracker -profile-summary-info -forceattrs -inferattrs -ipsccp -globalopt -domtree -mem2reg -deadargelim -domtree -basicaa -aa -instcombine -simplifycfg -basiccg -globals-aa -prune-eh -inline -functionattrs -argpromotion -domtree -sroa -early-cse -domtree -basicaa -aa -lazy-value-info -jump-threading -correlated-propagation -simplifycfg -domtree -basicaa -aa -instcombine -libcalls-shrinkwrap -loops -branch-prob -block-freq -pgo-memop-opt -tailcallelim -simplifycfg -reassociate -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -loop-rotate -licm -loop-unswitch -simplifycfg -domtree -basicaa -aa -instcombine -loops -loop-simplify -lcssa-verification -lcssa -scalar-evolution -indvars -loop-idiom -loop-deletion -loop-unroll -mldst-motion -aa -memdep -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -gvn -basicaa -aa -memdep -memcpyopt -sccp -domtree -demanded-bits -bdce -basicaa -aa -instcombine -lazy-value-info -jump-threading -correlated-propagation -domtree -basicaa -aa -memdep -dse -loops -loop-simplify -lcssa-verification -lcssa -aa -scalar-evolution -licm -postdomtree -adce -simplifycfg -domtree -basicaa -aa -instcombine -barrier -elim-avail-extern -basiccg -rpo-functionattrs -globals-aa -float2int -domtree -loops -scalar-evolution -polly-prepare -scalar-evolution -basicaa -aa -postdomtree -domfrontier -regions -polly-detect -polly-scops -polly-prune-unprofitable -polly-dependences -polly-opt-isl -polly-ast -polly-codegen -barrier -polly-cleanup -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -loop-rotate -loop-accesses -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -loop-distribute -branch-prob -block-freq -scalar-evolution -basicaa -aa -loop-accesses -demanded-bits -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -loop-vectorize -loop-simplify -scalar-evolution -aa -loop-accesses -loop-load-elim -basicaa -aa -instcombine -scalar-evolution -demanded-bits -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -slp-vectorizer -latesimplifycfg -domtree -basicaa -aa -instcombine -loops -loop-simplify -lcssa-verification -lcssa -scalar-evolution -loop-unroll -instcombine -loop-simplify -lcssa-verification -lcssa -scalar-evolution -licm -alignment-from-assumptions -strip-dead-prototypes -globaldce -constmerge -domtree -loops -branch-prob -block-freq -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -branch-prob -block-freq -loop-sink -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -instsimplify -simplifycfg
 
	// From PassManagerBuilder::populateModulePassManager (without Polly)
	// -tti -targetlibinfo -tbaa -scoped-noalias -assumption-cache-tracker -profile-summary-info -forceattrs -inferattrs -ipsccp -globalopt -domtree -mem2reg -deadargelim -domtree -basicaa -aa -instcombine -simplifycfg -basiccg -globals-aa -prune-eh -inline -functionattrs -argpromotion -domtree -sroa -early-cse -domtree -basicaa -aa -lazy-value-info -jump-threading -correlated-propagation -simplifycfg -domtree -basicaa -aa -instcombine -libcalls-shrinkwrap -loops -branch-prob -block-freq -pgo-memop-opt -tailcallelim -simplifycfg -reassociate -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -loop-rotate -licm -loop-unswitch -simplifycfg -domtree -basicaa -aa -instcombine -loops -loop-simplify -lcssa-verification -lcssa -scalar-evolution -indvars -loop-idiom -loop-deletion -loop-unroll -mldst-motion -aa -memdep -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -gvn -basicaa -aa -memdep -memcpyopt -sccp -domtree -demanded-bits -bdce -basicaa -aa -instcombine -lazy-value-info -jump-threading -correlated-propagation -domtree -basicaa -aa -memdep -dse -loops -loop-simplify -lcssa-verification -lcssa -aa -scalar-evolution -licm -postdomtree -adce -simplifycfg -domtree -basicaa -aa -instcombine -barrier -elim-avail-extern -basiccg -rpo-functionattrs -globals-aa -float2int -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -loop-rotate -loop-accesses -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -loop-distribute -branch-prob -block-freq -scalar-evolution -basicaa -aa -loop-accesses -demanded-bits -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -loop-vectorize -loop-simplify -scalar-evolution -aa -loop-accesses -loop-load-elim -basicaa -aa -instcombine -scalar-evolution -demanded-bits -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -slp-vectorizer -latesimplifycfg -domtree -basicaa -aa -instcombine -loops -loop-simplify -lcssa-verification -lcssa -scalar-evolution -loop-unroll -instcombine -loop-simplify -lcssa-verification -lcssa -scalar-evolution -licm -alignment-from-assumptions -strip-dead-prototypes -globaldce -constmerge -domtree -loops -branch-prob -block-freq -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -branch-prob -block-freq -loop-sink -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -instsimplify -simplifycfg

// Polly normalization passes (without inliner)
	PM.add(wrapCleanupPass(llvm::createPromoteMemoryToRegisterPass()));
	PM.add(wrapCleanupPass(llvm::createInstructionCombiningPass()));
	PM.add(wrapCleanupPass(llvm::createCFGSimplificationPass()));
	PM.add(wrapCleanupPass(llvm::createTailCallEliminationPass()));
	PM.add(wrapCleanupPass(llvm::createCFGSimplificationPass()));
	PM.add(wrapCleanupPass(llvm::createReassociatePass()));
	PM.add(wrapCleanupPass(static_cast<LoopPass*>( llvm::createLoopRotatePass())));
	PM.add(wrapCleanupPass(llvm::createInstructionCombiningPass()));
	PM.add(wrapCleanupPass(static_cast<LoopPass*>(llvm::createIndVarSimplifyPass())));

	// Between Polly-early and Polly-before-vectorizer
	// -ipsccp -globalopt -domtree -mem2reg -deadargelim -domtree -basicaa -aa -instcombine -simplifycfg -basiccg -globals-aa -prune-eh -inline -functionattrs -argpromotion -domtree -sroa -early-cse -domtree -basicaa -aa -lazy-value-info -jump-threading -correlated-propagation -simplifycfg -domtree -basicaa -aa -instcombine -libcalls-shrinkwrap -loops -branch-prob -block-freq -pgo-memop-opt -tailcallelim -simplifycfg -reassociate -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -loop-rotate -licm -loop-unswitch -simplifycfg -domtree -basicaa -aa -instcombine -loops -loop-simplify -lcssa-verification -lcssa -scalar-evolution -indvars -loop-idiom -loop-deletion -loop-unroll -mldst-motion -aa -memdep -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -gvn -basicaa -aa -memdep -memcpyopt -sccp -domtree -demanded-bits -bdce -basicaa -aa -instcombine -lazy-value-info -jump-threading -correlated-propagation -domtree -basicaa -aa -memdep -dse -loops -loop-simplify -lcssa-verification -lcssa -aa -scalar-evolution -licm -postdomtree -adce -simplifycfg -domtree -basicaa -aa -instcombine -barrier -elim-avail-extern -basiccg -rpo-functionattrs -globals-aa -float2int -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution 

	// After Polly-before-vectorizer
	// -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -loop-rotate -loop-accesses -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -loop-distribute -branch-prob -block-freq -scalar-evolution -basicaa -aa -loop-accesses -demanded-bits -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -loop-vectorize -loop-simplify -scalar-evolution -aa -loop-accesses -loop-load-elim -basicaa -aa -instcombine -scalar-evolution -demanded-bits -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -slp-vectorizer -latesimplifycfg -domtree -basicaa -aa -instcombine -loops -loop-simplify -lcssa-verification -lcssa -scalar-evolution -loop-unroll -instcombine -loop-simplify -lcssa-verification -lcssa -scalar-evolution -licm -alignment-from-assumptions -strip-dead-prototypes -globaldce -constmerge -domtree -loops -branch-prob -block-freq -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -branch-prob -block-freq -loop-sink -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -instsimplify -simplifycfg


}
