; RUN: opt %loadPolly -polly-scops -analyze < %s | FileCheck %s
;
;    void func(int n, double A[static const restrict n], int m) {
;      for (int j = 0; j < n; j += 1) { /* parallel loop */
;        double red = A[j];
;        for (int i1 = 0; i1 < m; i1 += 1) /* reduction loop */
;          red += 4.2;
;        for (int i2 = 0; i2 < m; i2 += 1) /* reduction loop */
;          red += 5.3;
;        A[j] = red;
;    }

; Two reductions executed sequentially 
; Possible difficulties:
; - Two loop-carrying phis that can use the same %arrayidx

define void @func(i32 %n, double* noalias nonnull %A, i32 %m) {
entry:
  br label %parallel.for

parallel.for:
  %j = phi i32 [0, %entry], [%j.inc, %parallel.inc]
  %arrayidx = getelementptr inbounds double, double* %A, i32 %j
  %ld = load double, double* %arrayidx
  %j.cmp = icmp slt i32 %j, %n
  br i1 %j.cmp, label %reduction1.for, label %return

reduction1.for:
  %i1 = phi i32 [0, %parallel.for], [%i1.inc, %reduction1.inc]
  %phi1 = phi double [%ld, %parallel.for], [%add1, %reduction1.inc]
  %i1.cmp = icmp slt i32 %i1, %m
  br i1 %i1.cmp, label %body1, label %reduction2.for

body1:
  %add1 = fadd double %phi1, 4.2
  br label %reduction1.inc

reduction1.inc:
  %i1.inc = add nuw nsw i32 %i1, 1
  br label %reduction1.for

reduction2.for:
  %i2 = phi i32 [0, %reduction1.for], [%i2.inc, %reduction2.inc]
  %phi2 = phi double [%phi1, %reduction1.for], [%add2, %reduction2.inc]
  %i2.cmp = icmp slt i32 %i2, %m
  br i1 %i2.cmp, label %body2, label %parallel.inc

body2:
  %add2 = fadd double %phi2, 5.3
  br label %reduction2.inc

reduction2.inc:
  %i2.inc = add nuw nsw i32 %i2, 1
  br label %reduction2.for

parallel.inc:
  store double %phi2, double* %arrayidx
  %j.inc = add nuw nsw i32 %j, 1
  br label %parallel.for

return:
  ret void
}


; CHECK:      Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'reduction2.for => parallel.inc' in function 'func':
; CHECK-NEXT: Invalid Scop!
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'reduction1.for => reduction2.for' in function 'func':
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
; CHECK-NEXT:         double MemRef_phi1__phi; // Element size 8
; CHECK-NEXT:         double MemRef_add1; // Element size 8
; CHECK-NEXT:     }
; CHECK-NEXT:     Arrays (Bounds as pw_affs) {
; CHECK-NEXT:         double MemRef_A[*]; // Element size 8
; CHECK-NEXT:         double MemRef_phi1__phi; // Element size 8
; CHECK-NEXT:         double MemRef_add1; // Element size 8
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
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_parallel_for[i0] -> MemRef_phi1__phi[] };
; CHECK-NEXT:         Stmt_reduction1_for
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction1_for[i0, i1] : 0 <= i0 < n and 0 <= i1 <= m; Stmt_reduction1_for[i0, 0] : m < 0 and 0 <= i0 < n };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction1_for[i0, i1] -> [i0, 1, i1, 0] : i1 <= m; Stmt_reduction1_for[i0, 0] -> [i0, 1, 0, 0] : m < 0 };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction1_for[i0, i1] -> MemRef_phi1__phi[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0] [MAPPED]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction1_for[i0, i1] -> MemRef_A[i0] };
; CHECK-NEXT:         Stmt_body1
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_body1[i0, i1] : 0 <= i0 < n and 0 <= i1 < m };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_body1[i0, i1] -> [i0, 1, i1, 1] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_body1[i0, i1] -> MemRef_add1[] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0] [MAPPED]
; CHECK-NEXT:                 [n, m] -> { Stmt_body1[i0, i1] -> MemRef_A[i0] };
; CHECK-NEXT:         Stmt_reduction1_inc
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction1_inc[i0, i1] : 0 <= i0 < n and 0 <= i1 < m };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction1_inc[i0, i1] -> [i0, 1, i1, 2] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction1_inc[i0, i1] -> MemRef_add1[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction1_inc[i0, i1] -> MemRef_phi1__phi[] };
; CHECK-NEXT:         Stmt_body2
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_body2[i0, i1] : 0 <= i0 < n and 0 <= i1 < m };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_body2[i0, i1] -> [i0, 2, i1, 0] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0] [MAPPED]
; CHECK-NEXT:                 [n, m] -> { Stmt_body2[i0, i1] -> MemRef_A[i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0] [MAPPED]
; CHECK-NEXT:                 [n, m] -> { Stmt_body2[i0, i1] -> MemRef_A[i0] };
; CHECK-NEXT:     }
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'entry => <Function Return>' in function 'func':
; CHECK-NEXT: Invalid Scop!
