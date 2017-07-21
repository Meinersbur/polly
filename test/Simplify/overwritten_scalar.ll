; RUN: opt %loadPolly -polly-import-jscop -polly-import-jscop-postfix=transformed -polly-simplify -polly-analyze-scop -analyze < %s | FileCheck -match-full-lines %s
;
; Remove identical writes
; (two stores in the same statement that write the same value to the same
; destination)
;
; for (int j = 0; j < n; j += 1) {
; body:
;   val = 21.0 + 21.0;
;   A[1] = val;
;   A[1] = val;
;
; user:
;   A[0] = A[1];
; }
;
define void @overwritten_scalar(i32 %n, double* noalias nonnull %A) {
entry:
  br label %for

for:
  %j = phi i32 [0, %entry], [%j.inc, %inc]
  %j.cmp = icmp slt i32 %j, %n
  br i1 %j.cmp, label %body, label %exit

    body:
      %val = fadd double 21.0, 21.0
      br label %user

    user:
      %phi = phi double [%val, %body]
      %add = fadd double %val, %phi
      store double %add, double* %A
      br label %inc

inc:
  %j.inc = add nuw nsw i32 %j, 1
  br label %for

exit:
  br label %return

return:
  ret void
}


; CHECK: Statistics {
; CHECK:     Overwrites removed: 1
; CHECK: }

; CHECK:      Stmt_body
; CHECK-NEXT:     MustWriteAccess :=  [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:            [n] -> { Stmt_body[i0] ->  MemRef_val[] };
; CHECK-NEXT:       new: [n] -> { Stmt_body[i0] -> MemRef_A[1] };
; CHECK-NEXT: Stmt_user

; CHECK-NEXT: Statements {
; CHECK-NEXT:     Stmt_body
; CHECK-NEXT:         Domain :=
; CHECK-NEXT:             [n] -> { Stmt_body[i0] : 0 <= i0 < n };
; CHECK-NEXT:         Schedule :=
; CHECK-NEXT:             [n] -> { Stmt_body[i0] -> [i0, 0] };
; CHECK-NEXT:         MustWriteAccess :=  [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:             [n] -> { Stmt_body[i0] -> MemRef_val[] };
; CHECK-NEXT:        new: [n] -> { Stmt_body[i0] -> MemRef_A[1] };
; CHECK-NEXT:         Instructions {
; CHECK-NEXT:               %val = fadd double 2.100000e+01, 2.100000e+01
; CHECK-NEXT:             }
; CHECK-NEXT:     Stmt_user
; CHECK-NEXT:         Domain :=
; CHECK-NEXT:             [n] -> { Stmt_user[i0] : 0 <= i0 < n };
; CHECK-NEXT:         Schedule :=
; CHECK-NEXT:             [n] -> { Stmt_user[i0] -> [i0, 1] };
; CHECK-NEXT:         ReadAccess :=       [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:             [n] -> { Stmt_user[i0] -> MemRef_phi__phi[] };
; CHECK-NEXT:        new: [n] -> { Stmt_user[i0] -> MemRef_A[1] };
; CHECK-NEXT:         ReadAccess :=       [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:             [n] -> { Stmt_user[i0] -> MemRef_val[] };
; CHECK-NEXT:        new: [n] -> { Stmt_user[i0] -> MemRef_A[1] };
; CHECK-NEXT:         MustWriteAccess :=  [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:             [n] -> { Stmt_user[i0] -> MemRef_A[0] };
; CHECK-NEXT:         Instructions {
; CHECK-NEXT:               %phi = phi double [ %val, %body ]
; CHECK-NEXT:               %add = fadd double %val, %phi
; CHECK-NEXT:               store double %add, double* %A
; CHECK-NEXT:             }
; CHECK-NEXT: }
