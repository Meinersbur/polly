; RUN: opt %loadPolly -polly-delicm -analyze < %s | FileCheck %s
;
;    void func(int n, double A[static const restrict n], int m) {
;      for (int j = 0; j < n; j += 1) /* parallel loop */
;        for (int i = 0; i < m; i += 1) /* reduction loop */
;          A[j] += 4.2;
;    }
;

; Nested reduction standard case
; Before DeLICM/LICM-Pre
; Possible difficulties:
; - No changes, code not to be modified

define void @func(i32 %n, double* noalias nonnull %A, i32 %m) {
entry:
  br label %parallel.for

parallel.for:
  %j = phi i32 [0, %entry], [%j.inc, %parallel.inc]
  %j.cmp = icmp slt i32 %j, %n
  br i1 %j.cmp, label %reduction.for, label %return

reduction.for:
  %i = phi i32 [0, %parallel.for], [%i.inc, %reduction.inc]
  %i.cmp = icmp slt i32 %i, %m
  br i1 %i.cmp, label %body, label %parallel.inc

body:
  %arrayidx = getelementptr inbounds double, double* %A, i32 %j
  %ld = load double, double* %arrayidx
  %add = fadd double %ld, 4.2
  store double %add, double* %arrayidx
  br label %reduction.inc

reduction.inc:
  %i.inc = add nuw nsw i32 %i, 1
  br label %reduction.for

parallel.inc:
  %j.inc = add nuw nsw i32 %j, 1
  br label %parallel.for

return:
  ret void
}


; CHECK:      Original knowledge {
; CHECK-NEXT:     Lifetime: [n, m] -> { [MemRef_A[i0] -> [i1, i2{{\]\]}} -> [Stmt_body[i0, -1 + m] -> Val_add[{{\]\]}} : m > 0 and 0 <= i0 < n and i1 > i0; [MemRef_A[i0] -> [i0, i2{{\]\]}} -> [Stmt_body[i0, -1 + m] -> Val_add[{{\]\]}} : m > 0 and 0 <= i0 < n and i2 > m; [MemRef_A[i0] -> [i0, i2{{\]\]}} -> [Stmt_body[i0, -1 + i2] -> Val_add[{{\]\]}} : 0 <= i0 < n and 0 < i2 <= m } + Unknown
; CHECK-NEXT:     Written : [n, m] -> { [MemRef_A[i0] -> [i0, i2{{\]\]}} -> [Stmt_body[i0, i2] -> Val_add[{{\]\]}} : 0 <= i0 < n and 0 <= i2 < m }
; CHECK-NEXT: }
; CHECK:      Mapped scalars {
; CHECK-NEXT: }
; CHECK:      After knowledge {
; CHECK-NEXT:     Lifetime: [n, m] -> { [MemRef_A[i0] -> [i1, i2{{\]\]}} -> [Stmt_body[i0, -1 + m] -> Val_add[{{\]\]}} : m > 0 and 0 <= i0 < n and i1 > i0; [MemRef_A[i0] -> [i0, i2{{\]\]}} -> [Stmt_body[i0, -1 + m] -> Val_add[{{\]\]}} : m > 0 and 0 <= i0 < n and i2 > m; [MemRef_A[i0] -> [i0, i2{{\]\]}} -> [Stmt_body[i0, -1 + i2] -> Val_add[{{\]\]}} : 0 <= i0 < n and 0 < i2 <= m } + Unknown
; CHECK-NEXT:     Written : [n, m] -> { [MemRef_A[i0] -> [i0, i2{{\]\]}} -> [Stmt_body[i0, i2] -> Val_add[{{\]\]}} : 0 <= i0 < n and 0 <= i2 < m }
; CHECK-NEXT: }
; CHECK:      After accesses {
; CHECK-NEXT:     Stmt_body
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [n, m] -> { Stmt_body[i0, i1] -> MemRef_A[i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [n, m] -> { Stmt_body[i0, i1] -> MemRef_A[i0] };
; CHECK-NEXT: }
