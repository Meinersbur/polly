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



void  FieldAccess::loadFromInstruction(llvm::Instruction *instr) {
  //FIXME: These variants should be recognized as accesses to a field:
  // 1a. %p = call llvm.molly.ptr;  % = LoadInst %p
  // 1b. %p = call llvm.molly.ptr;  StoreInst %p
  // 2a. %val = call llvm.molly.get
  // 2b. call llvm.molly.set %val

  assert(instr);
  clear();
    if (auto call = dyn_cast<CallInst>(instr)) {
    auto func = call->getCalledFunction();
    if (!func)
      return ; 
    if (func->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_get")) { 
      assert(false);
    }
    if (func->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_set")){
      assert(false);
    }
    return ; // Call of something else
  }

  const Value *ptr;
  bool isRead = false;
  bool isWrite = false;
  //uint64_t size;
  if (auto ld = dyn_cast<LoadInst>(instr)) {
    ptr = ld->getPointerOperand();
    isRead = true;
  } else if (auto st = dyn_cast<StoreInst>(instr)) {
    ptr = st->getPointerOperand();
    isWrite = true;
  } else 
    return ; // Not an access

  auto ptrcall = const_cast<CallInst*>(dyn_cast<CallInst>(ptr)); //TODO: A constant offset might be added to the ptr to access a struct member
  if (!ptrcall)
    return ; // access to something else
  //assert(ptrcall->getParent() == instr->getParent() && "At the moment we depend on both being in the same BasicBlock");

  auto func = ptrcall->getCalledFunction();
  if (!func)
    return ; // field functions are never called dynamically

  auto intrID = func->getIntrinsicID(); 
  if (intrID == Intrinsic::molly_ptr) {
  } else if (func->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_ptr")) {
  } else
    return ; // Not a reference to a field


  auto nArgs = ptrcall->getNumArgOperands();
  assert(nArgs >= 2); // At least the reference to field + one coordinate
  auto field = ptrcall->getArgOperand(0);

  auto llvmEltPtrTy = func->getReturnType();
  auto llvmEltTy = cast<llvm::PointerType>(llvmEltPtrTy)->getElementType(); 

  this->accessor = instr;
  this->fieldCall = ptrcall;
  this->mollyfunc = func;
  //result.fieldvar = NULL;
  this->reads = isRead;
  this->writes = isWrite;
  //result.scopAccess = NULL;
  this->elttype = llvmEltTy;
}


llvm::LoadInst *FieldAccess::getLoadInst() { 
  assert(isRead());
  assert(isa<LoadInst>(accessor)); 
  return cast<LoadInst>(accessor); 
}


llvm::StoreInst *FieldAccess::getStoreInst() { 
  assert(isWrite());
  assert(isa<StoreInst>(accessor)); 
  return cast<StoreInst>(accessor); 
}


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

#if 0
FieldAccess FieldAccess::fromMemoryAccess(polly::MemoryAccess *memacc) {
  FieldAccess result = fromAccessInstruction(const_cast<Instruction*>(memacc->getAccessInstruction()));
  result.scopAccess = memacc;
  return result;
}
#endif

FieldAccess FieldAccess::fromAccessInstruction(llvm::Instruction *instr) {
 FieldAccess result;
 result.loadFromInstruction(instr);
 return result;
}


unsigned FieldAccess::getNumDims() const {
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


llvm::Value *FieldAccess::getCoordinate(unsigned dim) const {
  assert(dim < getNumDims());
  return fieldCall->getOperand(1 + dim);
}


llvm::Value *FieldAccess::getFieldPtr() {
  return fieldCall->getOperand(0);
}


__isl_give isl_space *FieldAccess::isl_getLogicalSpace(isl_ctx *ctx) {
  return isl_space_set_alloc(ctx, 0, getNumDims());
}


 std::vector<llvm::Value*> FieldAccess::getCoordinates() const {
   std::vector<llvm::Value*> result;
   auto nDims = getNumDims();
   result.reserve(nDims);
   assert(fieldCall->getNumArgOperands() >= nDims);
   for (auto i = nDims-nDims; i < nDims; i+=1) {
     auto arg = getCoordinate(i);
     result.push_back(arg);
   }
   return result;
 }


void FieldAccess::getCoordinates(llvm::SmallVectorImpl<llvm::Value*> &list) {
  auto nDims = getNumDims();
  assert(fieldCall->getNumArgOperands() >= nDims);
  for (auto i = nDims-nDims; i < nDims; i+=1) {
    auto arg = getCoordinate(i);
    list.push_back(arg);
  }
}
