; RUN: opt %loadPolly -polly-flatten-schedule -polly-delicm -analyze < %s | FileCheck %s
; 
;    void func(double *A, int m) {
;      double red = A[0];
;      for (int i = 0; i < m; i += 1) /* reduction loop */
;        red += 4.2;
;      A[0] = red;
;    }

define void @func(double* noalias nonnull %A, i32 %m) {
entry:
  br label %reduction.for

; Domain:     { Stmt_reduction_for[i0] : 0 <= i0 <= 4 };
; Schedule:   { Stmt_reduction_for[i0] -> [3i0] : 0 <= i0 <= 4 };
; Read:       { Stmt_reduction_for[i0] -> MemRef_phi__phi[] };
; MustWrite:  { Stmt_reduction_for[i0] -> MemRef_phi[] };
reduction.for:
  %i = phi i32 [0, %entry], [%i.inc, %reduction.inc]
  %phi = phi double [0.0, %entry], [%add, %reduction.inc]
  %i.cmp = icmp slt i32 %i, 4
  br i1 %i.cmp, label %body, label %reduction.exit

; Domain:    { Stmt_body[i0] : 0 <= i0 <= 3 };
; Schedule:  { Stmt_body[i0] -> [1 + 3i0] : 0 <= i0 <= 3 };
; Read:      { Stmt_body[i0] -> MemRef_phi[] };
; MustWrite: { Stmt_body[i0] -> MemRef_add[] };
body:
  %add = fadd double %phi, 4.2
  br label %reduction.inc

; Domain:    { Stmt_reduction_inc[i0] : 0 <= i0 <= 3 };
; Schedule:  { Stmt_reduction_inc[i0] -> [2 + 3i0] : 0 <= i0 <= 3 };
; Read:      { Stmt_reduction_inc[i0] -> MemRef_add[] };
; MustWrite: { Stmt_reduction_inc[i0] -> MemRef_phi__phi[] };
reduction.inc:
  %i.inc = add nuw nsw i32 %i, 1
  br label %reduction.for

; Domain:    { Stmt_reduction_exit[] };
; Scatter:   { Stmt_reduction_exit[] -> [13] };
; Read:      { Stmt_reduction_exit[] -> MemRef_phi[] };
; MustWrite: { Stmt_reduction_exit[] -> MemRef_A[0] };
reduction.exit:
  store double %phi, double* %A
  br label %return

return:
  ret void
}

; [ 0] Stmt_reduction_for[0]
; ( 1) Def: %phi

; [ 1] body[0]

; [ 2] Stmt_reduction_inc[0]

; [ 3] Stmt_reduction_for[1]
; ( 4) Def: %phi

; [ 4] body[1]

; [ 5] Stmt_reduction_inc[1]

; [ 6] Stmt_reduction_for[2]
; ( 7) Def: %phi

; [ 7] body[2]

; [ 8] Stmt_reduction_inc[2]

; [ 9] Stmt_reduction_for[3]
; (10) Def: %phi

; [10] body[3]

; [11] Stmt_reduction_inc[3]


; [12] Stmt_reduction_for[4]
; (13) Def: %phi

; (< 13) Overwritten: A[0] (???)
; (< 13) NoUse: A[0]       (???)

; [13] reduction.exit[]
;      MustOverwrite: A[0] 
; (14) Known: A[0] = %phi


; CHECK:      Schedule after flattening {
; CHECK-NEXT:     { Stmt_body[i0] -> [1 + 3i0] }
; CHECK-NEXT:     { Stmt_reduction_inc[i0] -> [2 + 3i0] }
; CHECK-NEXT:     { Stmt_reduction_for[i0] -> [3i0] }
; CHECK-NEXT:     { Stmt_reduction_exit[] -> [13] }
; CHECK-NEXT: }
; CHECK:      Original zone:
; CHECK-NEXT:     Lifetime: { [MemRef_A[0] -> [i1{{\]\]}} -> [Stmt_reduction_for[4] -> Val_phi[{{\]\]}} : i1 >= 14; [MemRef_A[0] -> [i1{{\]\]}} -> Undef[] : i1 <= 13 } + Unknown
; CHECK-NEXT:     Written : { [MemRef_A[0] -> [13{{\]\]}} -> [Stmt_reduction_for[4] -> Val_phi[{{\]\]}} }
; CHECK:      Mapped scalars {
; CHECK-NEXT: }
; CHECK:      After zone:
; CHECK-NEXT:     Lifetime: { [MemRef_A[0] -> [i1{{\]\]}} -> [Stmt_reduction_for[4] -> Val_phi[{{\]\]}} : i1 >= 14; [MemRef_A[0] -> [i1{{\]\]}} -> Undef[] : i1 <= 13 } + Unknown
; CHECK-NEXT:     Written : { [MemRef_A[0] -> [13{{\]\]}} -> [Stmt_reduction_for[4] -> Val_phi[{{\]\]}} }
; CHECK:      After Statements {
; CHECK-NEXT:     Stmt_reduction_for
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_reduction_for[i0] -> MemRef_phi__phi[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_reduction_for[i0] -> MemRef_phi[] };
; CHECK-NEXT:     Stmt_body
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_body[i0] -> MemRef_add[] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_body[i0] -> MemRef_phi[] };
; CHECK-NEXT:     Stmt_reduction_inc
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_reduction_inc[i0] -> MemRef_add[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_reduction_inc[i0] -> MemRef_phi__phi[] };
; CHECK-NEXT:     Stmt_reduction_exit
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_reduction_exit[] -> MemRef_A[0] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_reduction_exit[] -> MemRef_phi[] };
; CHECK-NEXT: }
