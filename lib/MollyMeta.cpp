#include "polly/MollyMeta.h"

#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>

using namespace molly;
using namespace llvm;

bool molly::isGetter(Function *func) {
  return func->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_get");
}

bool molly::isSetter(Function *func) {
  return func->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_set");
}

bool molly::isGetterCall(Instruction *Inst) {
  if (CallInst *callInst = dyn_cast<CallInst>(Inst)) {
    Function *func = callInst->getCalledFunction();
    return isGetter(func);
  }
  return false;
}

bool molly::isSetterCall(Instruction *Inst) {
  if (CallInst *callInst = dyn_cast<CallInst>(Inst)) {
    Function *func = callInst->getCalledFunction();
    return isSetter(func);
  }
  return false;
}


bool molly::isRefFunc(llvm::Function *func) {
  return func->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_ref");
  //TODO: Assert signature
}

bool molly::isRefCall(llvm::Value *Inst) {
  if (CallInst *callInst = dyn_cast<CallInst>(Inst)) {
    Function *func = callInst->getCalledFunction();
    return isRefFunc(func);
  }
  return false;
}


bool molly::isAccessFunc(llvm::Function *func) {
  return isGetter(func) || isSetter(func) || isRefFunc(func);
}


bool molly::isAccessCall(llvm::Instruction *Inst) {
  if (CallInst *callInst = dyn_cast<CallInst>(Inst)) {
    Function *func = callInst->getCalledFunction();
    return isAccessFunc(func);
  }
  return false;
}

bool molly::isLengthFunc(llvm::Function *func) {
  return func->getAttributes().hasAttribute(AttributeSet::FunctionIndex, "molly_length");
}


llvm::Type *molly::getElementType(llvm::Function *func) {
  if (isGetter(func)) {
    return func->getReturnType();
  } else if (isSetter(func)) {
    auto &args = func->getArgumentList();
    assert(args.size() > 0);
    return args.back().getType();
  } else if (isRefFunc(func)) {
    return func->getReturnType()->getPointerElementType();
  } else {
    llvm_unreachable("Dont know how to extract element type"); //TODO: Get the field class type, and find its template paremeter somehow; or add a metadata reference to a specific function (e.g. ref)
  }
}






static Type *getFieldType(Function *func) {
  const auto &args = func->getArgumentList();
  auto &thisArg = args.front();
  auto thisPtrTy = thisArg.getType();
  auto thisTy = thisPtrTy->getPointerElementType();
  return thisTy;
}
