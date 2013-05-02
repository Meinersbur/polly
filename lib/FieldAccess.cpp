// This file contains implementations of FieldAccess methods that are independent of Molly
#include "polly/FieldAccess.h"

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Function.h>
#include <llvm/Analysis/ScalarEvolution.h>
#include <llvm/IR/Intrinsics.h>

#include <isl/space.h>

using namespace polly;
using namespace llvm;
using namespace std;




llvm::Function *FieldAccess::getFieldFunc()  {
  return getFieldCall()->getCalledFunction();
}

bool FieldAccess::isPtrCall() {
  return getFieldFunc()->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_ptr");
}



llvm::Value *FieldAccess::getBaseField() {
  return fieldCall->getArgOperand(0);
}


llvm::Value *FieldAccess::getSubscript() {
  if (isPtrCall())  {
    auto call = getFieldCall();
    assert(call->getNumArgOperands() == 2); // Arg [0] is 'this'-pointer
    auto arg = call->getArgOperand(1);
    return arg;
  }
}

bool FieldAccess::isPtrFunc(llvm::Function *func) {
  bool result = func->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_ptr");
#ifndef NDEBUG
  if (result) {
    auto nArgs = func->getArgumentList().size();
    assert(nArgs >= 2); // At least the reference to field + one coordinate
  }
#endif
  return result;
}
bool FieldAccess::isGetFunc(llvm::Function *func) {
  return func->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_get");
}
bool FieldAccess::isSetFunc(llvm::Function *func) {
  return func->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_set");
}
bool FieldAccess::isIslocalFunc(llvm::Function *func) {
  return func->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_islocal");
}
bool FieldAccess::isRankofFunc(llvm::Function *func) {
  return func->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_rankof");
}


bool FieldAccess::isFieldFunc(llvm::Function *func) {
  if (func->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_memberfunc"))
    return true;
  return isPtrFunc(func) || isGetFunc(func) || isSetFunc(func) || isIslocalFunc(func) || isRankofFunc(func); // TODO: There is a special attribute "molly_memberfunc"
}


bool FieldAccess::isFieldCall(llvm::CallInst *call)  {
  auto func = call->getCalledFunction();
  if (!func)
    return false;
  return isFieldFunc(func);
}


FieldAccess FieldAccess::fromMemoryAccess(polly::MemoryAccess *memacc) {
  FieldAccess result = fromAccessInstruction(const_cast<Instruction*>(memacc->getAccessInstruction()));
  result.scopAccess = memacc;
  return result;
}


FieldAccess FieldAccess::fromAccessInstruction(llvm::Instruction *instr) {
  if (auto call = dyn_cast<CallInst>(instr)) {
    auto func = call->getCalledFunction();
    if (!func)
       return FieldAccess(); 
    if (func->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_get")) { 
      assert(false);
    }
    if (func->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_set")){
      assert(false);
    }
    return FieldAccess(); // Call of something else
  }

  const Value *ptr;
  bool isRead = false;
  bool isWrite = false;
  if (auto ld = dyn_cast<LoadInst>(instr)) {
    ptr = ld->getPointerOperand();
    isRead = true;
  } else if (auto st = dyn_cast<StoreInst>(instr)) {
    ptr = st->getPointerOperand();
    isWrite = true;
  } else {
    return FieldAccess(); // Not an access
  }

  auto ptrcall = const_cast<CallInst*>(dyn_cast<CallInst>(ptr)); //TODO: A constant offset might be added to the ptr to access a struct member
  if (!ptrcall)
    return FieldAccess(); // access to something else
  assert(ptrcall->getParent() == instr->getParent() && "At the moment we depend on both being in the same BasicBlock");

  auto func = ptrcall->getCalledFunction();
  if (!func)
    return FieldAccess(); // field functions are never called dynamically

  auto intrID = func->getIntrinsicID(); 
  if (intrID == Intrinsic::molly_ptr) {
  } else if (func->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_ptr")) {
  } else
    return FieldAccess(); // Not a reference to a field


  auto nArgs = ptrcall->getNumArgOperands();
  assert(nArgs >= 2); // At least the reference to field + one coordinate
  auto field = ptrcall->getArgOperand(0);

  auto llvmEltPtrTy = func->getReturnType();
  auto llvmEltTy = cast<llvm::PointerType>(llvmEltPtrTy)->getElementType(); 

  FieldAccess result;
  result.accessor = instr;
  result.fieldCall = ptrcall;
  result.mollyfunc = func;
  //result.fieldvar = NULL;
  result.reads = isRead;
  result.writes = isWrite;
  result.scopAccess = NULL;
  result.elttype = llvmEltTy;
  return result;
}


unsigned FieldAccess::getNumDims() {
  auto nArgs = fieldCall->getNumArgOperands(); 
  assert(nArgs == mollyfunc->getArgumentList().size());
  //auto nArgs = mollyfunc->getArgumentList().size();
  if (isSetFunc(mollyfunc)) {
    assert(nArgs >= 2);
    return nArgs - 2; // this + coords + value
  }
  assert(nArgs >= 1);
  return nArgs - 1; // this + coords
}


llvm::Value *FieldAccess::getCoordinate(unsigned dim) {
  assert(dim < getNumDims());
  return fieldCall->getOperand(1 + dim);
}


llvm::Value *FieldAccess::getFieldPtr() {
  return fieldCall->getOperand(0);
}


__isl_give isl_space *FieldAccess::isl_getLogicalSpace(isl_ctx *ctx) {
  return isl_space_set_alloc(ctx, 0, getNumDims());
}


void FieldAccess::getCoordinates(llvm::SmallVectorImpl<llvm::Value*> &list) {
  auto nDims = getNumDims();
  assert(fieldCall->getNumArgOperands()>= nDims);
  for (auto i = nDims-nDims; i < nDims; i+=1) {
    auto arg = getCoordinate(i);
    list.push_back(arg);
  }
}


void FieldAccess::LinkFailTestRef() {
  void unusedMethod_LinkFailTest();
}

