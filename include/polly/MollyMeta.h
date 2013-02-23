#ifndef MOLLY_MOLLYMETA_H
#define MOLLY_MOLLYMETA_H

namespace llvm {
  class Function;
  class Instruction;
  class Type;
  class Value;
} // namespace llvm

namespace molly {

  bool isGetter(llvm::Function *func);
  bool isGetterCall(llvm::Instruction *Inst);

  bool isSetter(llvm::Function *func);
  bool isSetterCall(llvm::Instruction *Inst);

  bool isRefFunc(llvm::Function *func);
  bool isRefCall(llvm::Value *Inst);

  bool isAccessFunc(llvm::Function *func);
  bool isAccessCall(llvm::Instruction *Inst);

  bool isLengthFunc(llvm::Function *func);

  llvm::Type *getElementType(llvm::Function *func);

} // namespace molly
#endif /* MOLLY_MOLLYMETA_H */
