#ifndef MOLLY_FIELDACCESS_H
#define MOLLY_FIELDACCESS_H

#include <polly/ScopInfo.h>

#define __isl_give 
struct isl_space;
struct isl_map;
struct isl_ctx;

namespace llvm {
  class Instruction;
  class CallInst;
  class Function;
  class Value;
  template<typename T> class SmallVectorImpl;
} // namespace llvm

namespace polly {
  class MemoryAccess;
} // namespace polly

namespace molly {
  class MollyContext;
  class FieldDetectionAnalysis;
  class FieldVariable;
  class FieldType;
} // namespace molly

namespace isl {
  class Space;
  class Map;
  class Aff;
  class Ctx;
} // namespace isl


namespace molly {
  class FieldAccess {
    friend class FieldDetectionAnalysis;

    //MollyContext *mollyContext;
    //FieldDetection *detector;
    llvm::Instruction *accessor;
    llvm::CallInst *fieldCall;
    llvm::Function *mollyfunc;
    FieldVariable *fieldvar;
    bool reads;
    bool writes;

    polly::MemoryAccess *scopAccess;

  public:
    FieldAccess() : accessor(NULL) {  }
    //FieldAccess(llvm::Instruction *accessor, llvm::CallInst *fieldCall, FieldVariable *fieldvar, bool isRead, bool isWrite);

    static bool isPtrFunc(llvm::Function *func);
    static bool isGetFunc(llvm::Function *func);
    static bool isSetFunc(llvm::Function *func);
    static bool isIslocalFunc(llvm::Function *func);
    static bool isRankofFunc(llvm::Function *func);
    static bool isFieldFunc(llvm::Function *func);

    static bool isFieldCall(llvm::CallInst *call) ;

    static FieldAccess fromMemoryAccess(polly::MemoryAccess *memacc);
    static FieldAccess fromAccessInstruction(llvm::Instruction *instr);

    bool isValid() { return accessor; }
    bool isNull() { return !accessor; }

    llvm::Instruction *getAccessor() { return accessor; }
    llvm::CallInst *getFieldCall() { return fieldCall; }
    llvm::Function *getFieldFunc();
    bool isPtrCall();
    FieldVariable *getFieldVariable() { return fieldvar; }
    FieldType *getFieldType();
    bool isRead() { return reads; }
    bool isWrite() { return writes; }
    llvm::Value *getBaseField();

    polly::MemoryAccess *getScopAccess() { return scopAccess; }
    void setScopAccess(polly::MemoryAccess *memacc) { this->scopAccess = memacc; }

    llvm::Value *getSubscript();//TODO: Multi-dimensional

    unsigned getNumDims();
    llvm::Value *getCoordinate(unsigned dim);
    llvm::Value *getFieldPtr();

    __isl_give isl_space *isl_getLogicalSpace(isl_ctx *); 
    isl::Space getLogicalSpace(isl::Ctx *); // returns a set space with getNumDims() dimensions
    
    void getCoordinates(llvm::SmallVectorImpl<llvm::Value*> &list);

    //isl::Space getIterationSpace(isl::Ctx *, ScopStmt *); // returns set space
    //isl::Space getAccessSpace(isl::Ctx *, ScopStmt *); // map space: teration -> Logical

    //isl::MultiPwAff getAffineAccessRelation(isl::Ctx *, ScopStmt *);
    //isl::Map getAccessRelation();


    void LinkFailTestRef();
    void unusedMethod_LinkFailTest();
  }; // class FieldAccess
} // namepsace molly
#endif /* MOLLY_FIELDACCESS_H */
