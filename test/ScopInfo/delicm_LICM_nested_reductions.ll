; RUN: opt %loadPolly -polly-scops -analyze < %s | FileCheck %s
;
;    void func(int n, double A[static const restrict n], int m) {
;      for (int j = 0; j < n; j += 1) { /* parallel loop */
;        double red = A[j];
;        for (int i = 0; i < m; i += 1) /* reduction loop */
;          for (int k = 0; k < m; k += 1) /* reduction loop */
;            red += 4.2;
;        A[j] = red;
;    }

; Two nested loop-carried phis able to reuse the same %arrayidx
; Possible difficulties:
; - Identify that both phis can use the same %arrayidx as scratch space
; - Needs edge-level writes

define void @func(i32 %n, double* noalias nonnull %A, i32 %m) {
entry:
  br label %parallel.for

parallel.for:
  %j = phi i32 [0, %entry], [%j.inc, %parallel.inc]
  %arrayidx = getelementptr inbounds double, double* %A, i32 %j
  %ld = load double, double* %arrayidx
  %j.cmp = icmp slt i32 %j, %n
  br i1 %j.cmp, label %reduction_outer.for, label %return

reduction_outer.for:
  %i_outer = phi i32 [0, %parallel.for], [%i_outer.inc, %reduction_outer.inc]
  %phi_outer = phi double [%ld, %parallel.for], [%phi_inner, %reduction_outer.inc]
  %i_outer.cmp = icmp slt i32 %i_outer, %m
  br i1 %i_outer.cmp, label %reduction_inner.for, label %parallel.inc

reduction_inner.for:
  %i_inner = phi i32 [0, %reduction_outer.for], [%i_inner.inc, %reduction_inner.inc]
  %phi_inner = phi double [%ld, %reduction_outer.for], [%add, %reduction_inner.inc]
  %i_inner.cmp = icmp slt i32 %i_inner, %m
  br i1 %i_inner.cmp, label %body, label %reduction_outer.inc

body:
  %add = fadd double %phi_inner, 4.2
  br label %reduction_inner.inc

reduction_inner.inc:
  %i_inner.inc = add nuw nsw i32 %i_inner, 1
  br label %reduction_inner.for

reduction_outer.inc:
  %i_outer.inc = add nuw nsw i32 %i_outer, 1
  br label %reduction_outer.for

parallel.inc:
  store double %phi_outer, double* %arrayidx
  %j.inc = add nuw nsw i32 %j, 1
  br label %parallel.for

return:
  ret void
}


; CHECK:      Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'reduction_inner.for => reduction_outer.inc' in function 'func':
; CHECK-NEXT: Invalid Scop!
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'reduction_outer.for => parallel.inc' in function 'func':
; CHECK-NEXT: Invalid Scop!
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'parallel.for => return' in function 'func':
; CHECK-NEXT:     Function: func
; CHECK-NEXT:     Region: %parallel.for---%return
; CHECK-NEXT:     Max Loop Depth:  3
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
; CHECK-NEXT:         double MemRef_phi_outer__phi; // Element size 8
; CHECK-NEXT:         double MemRef_ld; [BasePtrOrigin: MemRef_A] // Element size 8
; CHECK-NEXT:         double MemRef_phi_inner__phi; // Element size 8
; CHECK-NEXT:         double MemRef_phi_inner; // Element size 8
; CHECK-NEXT:         double MemRef_add; // Element size 8
; CHECK-NEXT:     }
; CHECK-NEXT:     Arrays (Bounds as pw_affs) {
; CHECK-NEXT:         double MemRef_A[*]; // Element size 8
; CHECK-NEXT:         double MemRef_phi_outer__phi; // Element size 8
; CHECK-NEXT:         double MemRef_ld; [BasePtrOrigin: MemRef_A] // Element size 8
; CHECK-NEXT:         double MemRef_phi_inner__phi; // Element size 8
; CHECK-NEXT:         double MemRef_phi_inner; // Element size 8
; CHECK-NEXT:         double MemRef_add; // Element size 8
; CHECK-NEXT:     }
; CHECK-NEXT:     Alias Groups (0):
; CHECK-NEXT:         n/a
; CHECK-NEXT:     Statements {
; CHECK-NEXT:         Stmt_parallel_for
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_parallel_for[i0] : 0 <= i0 <= n; Stmt_parallel_for[0] : n < 0 };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_parallel_for[i0] -> [i0, 0, 0, 0, 0, 0] : i0 <= n; Stmt_parallel_for[0] -> [0, 0, 0, 0, 0, 0] : n < 0 };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [n, m] -> { Stmt_parallel_for[i0] -> MemRef_A[i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_parallel_for[i0] -> MemRef_phi_outer__phi[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_parallel_for[i0] -> MemRef_ld[] };
; CHECK-NEXT:         Stmt_reduction_outer_for
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_outer_for[i0, i1] : 0 <= i0 < n and 0 <= i1 <= m; Stmt_reduction_outer_for[i0, 0] : m < 0 and 0 <= i0 < n };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_outer_for[i0, i1] -> [i0, 1, i1, 0, 0, 0] : i1 <= m; Stmt_reduction_outer_for[i0, 0] -> [i0, 1, 0, 0, 0, 0] : m < 0 };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_outer_for[i0, i1] -> MemRef_phi_outer__phi[] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_outer_for[i0, i1] -> MemRef_ld[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_outer_for[i0, i1] -> MemRef_phi_inner__phi[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0] [MAPPED]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_outer_for[i0, i1] -> MemRef_A[i0] };
; CHECK-NEXT:         Stmt_reduction_inner_for
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_inner_for[i0, i1, i2] : 0 <= i0 < n and 0 <= i1 < m and 0 <= i2 <= m };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_inner_for[i0, i1, i2] -> [i0, 1, i1, 1, i2, 0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_inner_for[i0, i1, i2] -> MemRef_phi_inner[] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_inner_for[i0, i1, i2] -> MemRef_phi_inner__phi[] };
; CHECK-NEXT:         Stmt_body
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_body[i0, i1, i2] : 0 <= i0 < n and 0 <= i1 < m and 0 <= i2 < m };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_body[i0, i1, i2] -> [i0, 1, i1, 1, i2, 1] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_body[i0, i1, i2] -> MemRef_add[] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_body[i0, i1, i2] -> MemRef_phi_inner[] };
; CHECK-NEXT:         Stmt_reduction_inner_inc
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_inner_inc[i0, i1, i2] : 0 <= i0 < n and 0 <= i1 < m and 0 <= i2 < m };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_inner_inc[i0, i1, i2] -> [i0, 1, i1, 1, i2, 2] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_inner_inc[i0, i1, i2] -> MemRef_add[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_inner_inc[i0, i1, i2] -> MemRef_phi_inner__phi[] };
; CHECK-NEXT:         Stmt_reduction_outer_inc
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_outer_inc[i0, i1] : 0 <= i0 < n and 0 <= i1 < m };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_outer_inc[i0, i1] -> [i0, 1, i1, 2, 0, 0] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_outer_inc[i0, i1] -> MemRef_phi_inner[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_outer_inc[i0, i1] -> MemRef_phi_outer__phi[] };
; CHECK-NEXT:     }
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'entry => <Function Return>' in function 'func':
; CHECK-NEXT: Invalid Scop!
