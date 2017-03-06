//===------ CodeGeneration.cpp - Code generate the Scops using ISL. ----======//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// The CodeGeneration pass takes a Scop created by ScopInfo and translates it
// back to LLVM-IR using the ISL code generator.
//
// The Scop describes the high level memory behaviour of a control flow region.
// Transformation passes can update the schedule (execution order) of statements
// in the Scop. ISL is used to generate an abstract syntax tree that reflects
// the updated execution order. This clast is used to create new LLVM-IR that is
// computationally equivalent to the original control flow region, but executes
// its code in the new execution order defined by the changed schedule.
//
//===----------------------------------------------------------------------===//

#include "polly/CodeGen/IslAst.h"
#include "polly/CodeGen/IslNodeBuilder.h"
#include "polly/CodeGen/Utils.h"
#include "polly/DependenceInfo.h"
#include "polly/LinkAllPasses.h"
#include "polly/Options.h"
#include "polly/ScopInfo.h"
#include "polly/Support/ScopHelper.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/BasicAliasAnalysis.h"
#include "llvm/Analysis/GlobalsModRef.h"
#include "llvm/Analysis/ScalarEvolutionAliasAnalysis.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/Debug.h"

using namespace polly;
using namespace llvm;

#define DEBUG_TYPE "polly-codegen"

static cl::opt<bool> Verify("polly-codegen-verify",
                            cl::desc("Verify the function generated by Polly"),
                            cl::Hidden, cl::init(true), cl::ZeroOrMore,
                            cl::cat(PollyCategory));

STATISTIC(NumGenerationSkips, "Number of skipped SCoPs");
STATISTIC(NumGeneratedScops, "Number of successfully generated SCoPs");
STATISTIC(NumGeneratedFails, "Number of unsuccessfully generated SCoPs");

namespace {
class CodeGeneration : public ScopPass {
public:
  static char ID;

  CodeGeneration() : ScopPass(ID) {}

  /// The datalayout used
  const DataLayout *DL;

  /// @name The analysis passes we need to generate code.
  ///
  ///{
  LoopInfo *LI;
  IslAstInfo *AI;
  DominatorTree *DT;
  ScalarEvolution *SE;
  RegionInfo *RI;
  ///}

  void verifyGeneratedFunction(Scop &S, Function &F) {
    if (!verifyFunction(F, &errs()) || !Verify)
      return;

    DEBUG({
      errs() << "== ISL Codegen created an invalid function ==\n\n== The "
                "SCoP ==\n";
      S.print(errs());
      errs() << "\n== The isl AST ==\n";
      AI->printScop(errs(), S);
      errs() << "\n== The invalid function ==\n";
      F.print(errs());
    });

    llvm_unreachable("Polly generated function could not be verified. Add "
                     "-polly-codegen-verify=false to disable this assertion.");
  }

  // CodeGeneration adds a lot of BBs without updating the RegionInfo
  // We make all created BBs belong to the scop's parent region without any
  // nested structure to keep the RegionInfo verifier happy.
  void fixRegionInfo(Function *F, Region *ParentRegion) {
    for (BasicBlock &BB : *F) {
      if (RI->getRegionFor(&BB))
        continue;

      RI->setRegionFor(&BB, ParentRegion);
    }
  }

  /// Mark a basic block unreachable.
  ///
  /// Marks the basic block @p Block unreachable by equipping it with an
  /// UnreachableInst.
  void markBlockUnreachable(BasicBlock &Block, PollyIRBuilder &Builder) {
    auto *OrigTerminator = Block.getTerminator();
    Builder.SetInsertPoint(OrigTerminator);
    Builder.CreateUnreachable();
    OrigTerminator->eraseFromParent();
  }

  /// Generate LLVM-IR for the SCoP @p S.
  bool runOnScop(Scop &S) override {
    AI = &getAnalysis<IslAstInfo>();

    // Check if we created an isl_ast root node, otherwise exit.
    isl_ast_node *AstRoot = AI->getAst();
    if (!AstRoot) {
      NumGenerationSkips++;
      return false;
    }

    LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
    DT = &getAnalysis<DominatorTreeWrapperPass>().getDomTree();
    SE = &getAnalysis<ScalarEvolutionWrapperPass>().getSE();
    DL = &S.getFunction().getParent()->getDataLayout();
    RI = &getAnalysis<RegionInfoPass>().getRegionInfo();
    Region *R = &S.getRegion();
    assert(!R->isTopLevelRegion() && "Top level regions are not supported");

    ScopAnnotator Annotator;
    Annotator.buildAliasScopes(S);

    simplifyRegion(R, DT, LI, RI);
    assert(R->isSimple());
    BasicBlock *EnteringBB = S.getEnteringBlock();
    assert(EnteringBB);
    PollyIRBuilder Builder = createPollyIRBuilder(EnteringBB, Annotator);

    // Only build the run-time condition and parameters _after_ having
    // introduced the conditional branch. This is important as the conditional
    // branch will guard the original scop from new induction variables that
    // the SCEVExpander may introduce while code generating the parameters and
    // which may introduce scalar dependences that prevent us from correctly
    // code generating this scop.
    BasicBlock *StartBlock =
        executeScopConditionally(S, this, Builder.getTrue());
    auto *SplitBlock = StartBlock->getSinglePredecessor();

    IslNodeBuilder NodeBuilder(Builder, Annotator, this, *DL, *LI, *SE, *DT, S,
                               StartBlock);

    // First generate code for the hoisted invariant loads and transitively the
    // parameters they reference. Afterwards, for the remaining parameters that
    // might reference the hoisted loads. Finally, build the runtime check
    // that might reference both hoisted loads as well as parameters.
    // If the hoisting fails we have to bail and execute the original code.
    Builder.SetInsertPoint(SplitBlock->getTerminator());
    if (!NodeBuilder.preloadInvariantLoads()) {

      // Patch the introduced branch condition to ensure that we always execute
      // the original SCoP.
      auto *FalseI1 = Builder.getFalse();
      auto *SplitBBTerm = Builder.GetInsertBlock()->getTerminator();
      SplitBBTerm->setOperand(0, FalseI1);

      // Since the other branch is hence ignored we mark it as unreachable and
      // adjust the dominator tree accordingly.
      auto *ExitingBlock = StartBlock->getUniqueSuccessor();
      assert(ExitingBlock);
      auto *MergeBlock = ExitingBlock->getUniqueSuccessor();
      assert(MergeBlock);
      markBlockUnreachable(*StartBlock, Builder);
      markBlockUnreachable(*ExitingBlock, Builder);
      auto *ExitingBB = S.getExitingBlock();
      assert(ExitingBB);
      DT->changeImmediateDominator(MergeBlock, ExitingBB);
      DT->eraseNode(ExitingBlock);

      isl_ast_node_free(AstRoot);
      NumGeneratedFails++;
    } else {
      NodeBuilder.allocateNewArrays();
      NodeBuilder.addParameters(S.getContext());
      Value *RTC = NodeBuilder.createRTC(AI->getRunCondition());

      Builder.GetInsertBlock()->getTerminator()->setOperand(0, RTC);
      Builder.SetInsertPoint(&StartBlock->front());

      NodeBuilder.create(AstRoot);
      NodeBuilder.finalize();
      fixRegionInfo(EnteringBB->getParent(), R->getParent());
      NumGeneratedScops++;
    }

    Function *F = EnteringBB->getParent();
    verifyGeneratedFunction(S, *F);
    for (auto *SubF : NodeBuilder.getParallelSubfunctions())
      verifyGeneratedFunction(S, *SubF);

    // Mark the function such that we run additional cleanup passes on this
    // function (e.g. mem2reg to rediscover phi nodes).
    F->addFnAttr("polly-optimized");

    return true;
  }

  /// Register all analyses and transformation required.
  void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.addRequired<DominatorTreeWrapperPass>();
    AU.addRequired<IslAstInfo>();
    AU.addRequired<RegionInfoPass>();
    AU.addRequired<ScalarEvolutionWrapperPass>();
    AU.addRequired<ScopDetection>();
    AU.addRequired<ScopInfoRegionPass>();
    AU.addRequired<LoopInfoWrapperPass>();

    AU.addPreserved<DependenceInfo>();

    AU.addPreserved<AAResultsWrapperPass>();
    AU.addPreserved<BasicAAWrapperPass>();
    AU.addPreserved<LoopInfoWrapperPass>();
    AU.addPreserved<DominatorTreeWrapperPass>();
    AU.addPreserved<GlobalsAAWrapperPass>();
    AU.addPreserved<IslAstInfo>();
    AU.addPreserved<ScopDetection>();
    AU.addPreserved<ScalarEvolutionWrapperPass>();
    AU.addPreserved<SCEVAAWrapperPass>();

    // FIXME: We do not yet add regions for the newly generated code to the
    //        region tree.
    AU.addPreserved<RegionInfoPass>();
    AU.addPreserved<ScopInfoRegionPass>();
  }
};
} // namespace

char CodeGeneration::ID = 1;

Pass *polly::createCodeGenerationPass() { return new CodeGeneration(); }

INITIALIZE_PASS_BEGIN(CodeGeneration, "polly-codegen",
                      "Polly - Create LLVM-IR from SCoPs", false, false);
INITIALIZE_PASS_DEPENDENCY(DependenceInfo);
INITIALIZE_PASS_DEPENDENCY(DominatorTreeWrapperPass);
INITIALIZE_PASS_DEPENDENCY(LoopInfoWrapperPass);
INITIALIZE_PASS_DEPENDENCY(RegionInfoPass);
INITIALIZE_PASS_DEPENDENCY(ScalarEvolutionWrapperPass);
INITIALIZE_PASS_DEPENDENCY(ScopDetection);
INITIALIZE_PASS_END(CodeGeneration, "polly-codegen",
                    "Polly - Create LLVM-IR from SCoPs", false, false)
