; RUN: opt %loadPolly -polly-scops -analyze < %s | FileCheck %s
;
;    void func(int n, double A[static const restrict n], int m) {
;      for (int j = 0; j < n; j += 1) { /* parallel loop */
;        double red = A[j];
;        for (int i = 0; i < m; i += 1) /* reduction loop */
;          if (i % 2 == 0)
;            red += 4.2;
;        A[j] = red;
;    }

; Body executed conditionally
; Possible difficulties:
; - %reduction.inc non-existing, where to put the store?

define void @func(i32 %n, double* noalias nonnull %A, i32 %m, double* noalias nonnull %B) {
entry:
  br label %parallel.for

parallel.for:
  %j = phi i32 [0, %entry], [%j.inc, %parallel.inc]
  %arrayidx = getelementptr inbounds double, double* %A, i32 %j
  %ld = load double, double* %arrayidx
  %j.cmp = icmp slt i32 %j, %n
  br i1 %j.cmp, label %reduction.for, label %return

reduction.for:
  %i = phi i32 [0, %parallel.for], [%i.inc, %body], [%i.inc, %body.true]
  %phi = phi double [%ld, %parallel.for], [%phi, %body], [%add, %body.true]
  %i.cmp = icmp slt i32 %i, %m
  %i.inc = add nuw nsw i32 %i, 1
  br i1 %i.cmp, label %body, label %parallel.inc

body:
  %rem = and i32 %i, 1
  %cond = icmp eq i32 %rem, 0
  br i1 %cond, label %body.true, label %reduction.for

body.true:
  %add = fadd double %phi, 4.2
  br label %reduction.for

parallel.inc:
  store double %phi, double* %arrayidx
  %j.inc = add nuw nsw i32 %j, 1
  br label %parallel.for

return:
  ret void
}


; CHECK:      Statements {
; CHECK-NEXT:     Stmt_body
; CHECK-NEXT:         Domain :=
; CHECK-NEXT:             [p_0] -> { Stmt_body[] };
; CHECK-NEXT:         Schedule :=
; CHECK-NEXT:             [p_0] -> { Stmt_body[] -> [0] };
; CHECK-NEXT:         MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:             [p_0] -> { Stmt_body[] -> MemRef_i[] };
; CHECK-NEXT:         ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:             [p_0] -> { Stmt_body[] -> MemRef_phi[] };
; CHECK-NEXT:         MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:             [p_0] -> { Stmt_body[] -> MemRef_phi[] };
; CHECK-NEXT:     Stmt_body_true
; CHECK-NEXT:         Domain :=
; CHECK-NEXT:             [p_0] -> { Stmt_body_true[] : p_0 = 0 };
; CHECK-NEXT:         Schedule :=
; CHECK-NEXT:             [p_0] -> { Stmt_body_true[] -> [1] };
; CHECK-NEXT:         ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:             [p_0] -> { Stmt_body_true[] -> MemRef_phi[] };
; CHECK-NEXT:         MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:             [p_0] -> { Stmt_body_true[] -> MemRef_i[] };
; CHECK-NEXT:         MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:             [p_0] -> { Stmt_body_true[] -> MemRef_phi[] };
; CHECK-NEXT: }
