; RUN: opt %loadPolly -polly-simplify -analyze < %s | FileCheck %s

define void @func(double* noalias nonnull %A, double* noalias nonnull %B) {
entry:
  br label %outer.for

outer.for:
  %j = phi i32 [0, %entry], [%j.inc, %outer.inc]
  %j.cmp = icmp slt i32 %j, 5
  br i1 %j.cmp, label %body, label %outer.exit


    body:
      %A_idx = getelementptr inbounds double, double* %A, i32 %j
      %val = load double, double* %A_idx
      store double %val, double* %A_idx
      br label %outer.inc


outer.inc:
  %j.inc = add nuw nsw i32 %j, 1
  br label %outer.for

outer.exit:
  br label %return

return:
  ret void
}


; CHECK:      Cleanups {
; CHECK-NEXT:     Cleanup {
; CHECK-NEXT:         Stmt: Stmt_body
; CHECK-NEXT:         Scalar:   %val = load double, double* %A_idx
; CHECK-NEXT:         AccRel: { Stmt_body[i0] -> MemRef_A[i0] }
; CHECK-NEXT:     }
; CHECK-NEXT: }
; CHECK:      After accesses {
; CHECK-NEXT: }
