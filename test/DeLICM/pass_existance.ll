; RUN: opt %loadPolly -polly-delicm -analyze < %s | FileCheck %s
;
; Simple test for the existence of the DeLICM pass.
;
; // Simplest detected SCoP to run DeLICM on.
; for (int j = 0; j < n; j += 1) {
;   body: A[0] = 0.0;
; }
;
define void @func(i32 %n, double* noalias nonnull %A) {
entry:
  br label %for

for:
  %j = phi i32 [0, %entry], [%j.inc, %inc]
  %j.cmp = icmp slt i32 %j, %n
  br i1 %j.cmp, label %body, label %exit

    body:
      store double 0.0, double* %A
      br label %inc

inc:
  %j.inc = add nuw nsw i32 %j, 1
  br label %for

exit:
  br label %return

return:
  ret void
}


; Verify that the DeLICM has a custom printScop() function.
; CHECK:      Original knowledge {
; CHECK-NEXT:     Lifetime: [n] -> { [MemRef_A[0] -> [i1{{\]\]}} -> Val__000000e_00[] : n > 0 and i1 >= n; [MemRef_A[0] -> [i1{{\]\]}} -> Undef[] : n > 0 and i1 < n } + Unknown
; CHECK-NEXT:     Written : [n] -> { [MemRef_A[0] -> [i1{{\]\]}} -> Val__000000e_00[] : 0 <= i1 < n }
; CHECK-NEXT: }
; CHECK:      Mapped scalars {
; CHECK-NEXT: }
; CHECK:      After knowledge {
; CHECK-NEXT:     Lifetime: [n] -> { [MemRef_A[0] -> [i1{{\]\]}} -> Val__000000e_00[] : n > 0 and i1 >= n; [MemRef_A[0] -> [i1{{\]\]}} -> Undef[] : n > 0 and i1 < n } + Unknown
; CHECK-NEXT:     Written : [n] -> { [MemRef_A[0] -> [i1{{\]\]}} -> Val__000000e_00[] : 0 <= i1 < n }
; CHECK-NEXT: }
; CHECK:      After accesses {
; CHECK-NEXT:     Stmt_body
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [n] -> { Stmt_body[i0] -> MemRef_A[0] };
; CHECK-NEXT: }
