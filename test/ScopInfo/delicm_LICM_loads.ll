; RUN: opt %loadPolly -polly-scops -analyze < %s | FileCheck %s
;
;    void func(int n, double A[static const restrict n], int m, double B[static const restrict n], double C[static const restrict n]) {
;      for (int j = 0; j < n; j += 1) { /* parallel loop */
;        B[j] = A[j];
;        double red = A[j];
;        red += 5.1;
;        for (int i = 0; i < m; i += 1) /* reduction loop */
;          red += 4.2;
;        A[j] = red;
;        C[j] = A[j];
;    }

; Value of A[j] used, outside of reduction
; Possible difficulties:
; - Distinguish from case where uses of A[j] is between the reduction initial load and writeback.

define void @func(i32 %n, double* noalias nonnull %A, i32 %m, double* noalias nonnull %B, double* noalias nonnull %C) {
entry:
  br label %parallel.for

parallel.for:
  %j = phi i32 [0, %entry], [%j.inc, %parallel.inc]
  %arrayidx = getelementptr inbounds double, double* %A, i32 %j
  %arrayidxB = getelementptr inbounds double, double* %B, i32 %j
  %arrayidxC = getelementptr inbounds double, double* %C, i32 %j
  %ld = load double, double* %arrayidx
  %prep = fadd double %ld, 5.1
  store double %ld, double* %arrayidxB
  %j.cmp = icmp slt i32 %j, %n
  br i1 %j.cmp, label %reduction.for, label %return

reduction.for:
  %i = phi i32 [0, %parallel.for], [%i.inc, %reduction.inc]
  %phi = phi double [%ld, %parallel.for], [%add, %reduction.inc]
  %i.cmp = icmp slt i32 %i, %m
  br i1 %i.cmp, label %body, label %parallel.inc

body:
  %add = fadd double %phi, 4.2
  br label %reduction.inc

reduction.inc:
  %i.inc = add nuw nsw i32 %i, 1
  br label %reduction.for

parallel.inc:
  store double %phi, double* %arrayidx
  store double %phi, double* %arrayidxC
  %j.inc = add nuw nsw i32 %j, 1
  br label %parallel.for

return:
  ret void
}


; CHECK:      Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'reduction.for => parallel.inc' in function 'func':
; CHECK-NEXT: Invalid Scop!
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'parallel.for => return' in function 'func':
; CHECK-NEXT:     Function: func
; CHECK-NEXT:     Region: %parallel.for---%return
; CHECK-NEXT:     Max Loop Depth:  2
; CHECK-NEXT:     Invariant Accesses: {
; CHECK-NEXT:     }
; CHECK-NEXT:     Context:
; CHECK-NEXT:     [n, m] -> {  : -2147483648 <= n <= 2147483647 and -2147483648 <= m <= 2147483647 }
; CHECK-NEXT:     Assumed Context:
; CHECK-NEXT:     [n, m] -> {  :  }
; CHECK-NEXT:     Invalid Context:
; CHECK-NEXT:     [n, m] -> {  : 1 = 0 }
; CHECK-NEXT:     p0: %n
; CHECK-NEXT:     p1: %m
; CHECK-NEXT:     Arrays {
; CHECK-NEXT:         double MemRef_A[*]; // Element size 8
; CHECK-NEXT:         double MemRef_B[*]; // Element size 8
; CHECK-NEXT:         double MemRef_C[*]; // Element size 8
; CHECK-NEXT:         double MemRef_phi__phi; // Element size 8
; CHECK-NEXT:         double MemRef_add; // Element size 8
; CHECK-NEXT:     }
; CHECK-NEXT:     Arrays (Bounds as pw_affs) {
; CHECK-NEXT:         double MemRef_A[*]; // Element size 8
; CHECK-NEXT:         double MemRef_B[*]; // Element size 8
; CHECK-NEXT:         double MemRef_C[*]; // Element size 8
; CHECK-NEXT:         double MemRef_phi__phi; // Element size 8
; CHECK-NEXT:         double MemRef_add; // Element size 8
; CHECK-NEXT:     }
; CHECK-NEXT:     Alias Groups (0):
; CHECK-NEXT:         n/a
; CHECK-NEXT:     Statements {
; CHECK-NEXT:         Stmt_parallel_for
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_parallel_for[i0] : 0 <= i0 <= n; Stmt_parallel_for[0] : n < 0 };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_parallel_for[i0] -> [i0, 0, 0, 0] : i0 <= n; Stmt_parallel_for[0] -> [0, 0, 0, 0] : n < 0 };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [n, m] -> { Stmt_parallel_for[i0] -> MemRef_A[i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [n, m] -> { Stmt_parallel_for[i0] -> MemRef_B[i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_parallel_for[i0] -> MemRef_phi__phi[] };
; CHECK-NEXT:         Stmt_reduction_for
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_for[i0, i1] : 0 <= i0 < n and 0 <= i1 <= m; Stmt_reduction_for[i0, 0] : m < 0 and 0 <= i0 < n };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_for[i0, i1] -> [i0, 1, i1, 0] : i1 <= m; Stmt_reduction_for[i0, 0] -> [i0, 1, 0, 0] : m < 0 };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_for[i0, i1] -> MemRef_phi__phi[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0] [MAPPED]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_for[i0, i1] -> MemRef_A[i0] };
; CHECK-NEXT:         Stmt_body
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_body[i0, i1] : 0 <= i0 < n and 0 <= i1 < m };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_body[i0, i1] -> [i0, 1, i1, 1] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_body[i0, i1] -> MemRef_add[] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0] [MAPPED]
; CHECK-NEXT:                 [n, m] -> { Stmt_body[i0, i1] -> MemRef_A[i0] };
; CHECK-NEXT:         Stmt_reduction_inc
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_inc[i0, i1] : 0 <= i0 < n and 0 <= i1 < m };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_inc[i0, i1] -> [i0, 1, i1, 2] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_inc[i0, i1] -> MemRef_add[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_inc[i0, i1] -> MemRef_phi__phi[] };
; CHECK-NEXT:         Stmt_parallel_inc
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_parallel_inc[i0] : 0 <= i0 < n };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_parallel_inc[i0] -> [i0, 2, 0, 0] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0] [MAPPED]
; CHECK-NEXT:                 [n, m] -> { Stmt_parallel_inc[i0] -> MemRef_A[i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [n, m] -> { Stmt_parallel_inc[i0] -> MemRef_C[i0] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0] [MAPPED]
; CHECK-NEXT:                 [n, m] -> { Stmt_parallel_inc[i0] -> MemRef_A[i0] };
; CHECK-NEXT:     }
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'entry => <Function Return>' in function 'func':
; CHECK-NEXT: Invalid Scop!
