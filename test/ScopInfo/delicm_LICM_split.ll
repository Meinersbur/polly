; RUN: opt %loadPolly -polly-scops -analyze < %s | FileCheck %s
;
;    void func(int n, double A[static const restrict n], int m, double B[static const restrict m]) {
;      for (int j = 0; j < n; j += 1) { /* parallel loop */
;        double red = A[j];
;        for (int i = 0; i < m; i += 1) { /* reduction loop */
;          red += B[i]; /* assume B[i] non-rematerializable */
;          <split>
;          red += B[m-i]; /* assume B[m-i] non-rematerializable */
;        }
;        A[j] = red;
;    }

; Body is split into multiple blocks
; Some more complicated could between body and body.split might keep the block from being joind into one
; Possible difficulties:
; - Does body and body.split get their own stores?
; - If not, does a scalar dependency between them remain?

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
  %i = phi i32 [0, %parallel.for], [%i.inc, %reduction.inc]
  %phi = phi double [%ld, %parallel.for], [%add2, %reduction.inc]
  %i.cmp = icmp slt i32 %i, %m
  br i1 %i.cmp, label %body, label %parallel.inc

body:
  %arrayidxB1 = getelementptr inbounds double, double* %B, i32 %i
  %B1 = load double, double* %arrayidxB1  ; assume non-rematerializable
  %add1 = fadd double %phi, %B1
  br label %body.split

body.split:
  %minusi = sub nuw nsw i32 %m, %i
  %arrayidxB2 = getelementptr inbounds double, double* %B, i32 %minusi
  %B2 = load double, double* %arrayidxB2  ; assume non-rematerializable
  %add2 = fadd double %add1, %B2
  br label %reduction.inc

reduction.inc:
  %i.inc = add nuw nsw i32 %i, 1
  br label %reduction.for
  
parallel.inc:
  store double %phi, double* %arrayidx
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
; CHECK-NEXT:         double MemRef_phi__phi; // Element size 8
; CHECK-NEXT:         double MemRef_add1; // Element size 8
; CHECK-NEXT:         double MemRef_add2; // Element size 8
; CHECK-NEXT:     }
; CHECK-NEXT:     Arrays (Bounds as pw_affs) {
; CHECK-NEXT:         double MemRef_A[*]; // Element size 8
; CHECK-NEXT:         double MemRef_B[*]; // Element size 8
; CHECK-NEXT:         double MemRef_phi__phi; // Element size 8
; CHECK-NEXT:         double MemRef_add1; // Element size 8
; CHECK-NEXT:         double MemRef_add2; // Element size 8
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
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [n, m] -> { Stmt_body[i0, i1] -> MemRef_B[i1] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0] [MAPPED]
; CHECK-NEXT:                 [n, m] -> { Stmt_body[i0, i1] -> MemRef_A[i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_body[i0, i1] -> MemRef_add1[] };
; CHECK-NEXT:         Stmt_body_split
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_body_split[i0, i1] : 0 <= i0 < n and 0 <= i1 < m };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_body_split[i0, i1] -> [i0, 1, i1, 2] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_body_split[i0, i1] -> MemRef_add2[] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [n, m] -> { Stmt_body_split[i0, i1] -> MemRef_B[m - i1] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_body_split[i0, i1] -> MemRef_add1[] };
; CHECK-NEXT:         Stmt_reduction_inc
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_inc[i0, i1] : 0 <= i0 < n and 0 <= i1 < m };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_inc[i0, i1] -> [i0, 1, i1, 3] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_inc[i0, i1] -> MemRef_add2[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 [n, m] -> { Stmt_reduction_inc[i0, i1] -> MemRef_phi__phi[] };
; CHECK-NEXT:     }
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'entry => <Function Return>' in function 'func':
; CHECK-NEXT: Invalid Scop!
