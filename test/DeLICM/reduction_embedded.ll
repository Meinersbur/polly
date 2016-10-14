; RUN: opt %loadPolly -polly-flatten-schedule -polly-delicm -analyze < %s | FileCheck %s
;
;    void func(double *A {
;      for (int j = 0; j < 1; j += 1) { /* outer */
;        double phi = 0.0;
;        for (int i = 0; i < 4; i += 1) /* reduction */
;          phi += 4.2;
;        A[j] = phi;
;      }
;    }
; 
define void @func(double* noalias nonnull %A) {
entry:
  br label %outer.for

outer.for:
  %j = phi i32 [0, %entry], [%j.inc, %outer.inc]
  %j.cmp = icmp slt i32 %j, 2
  br i1 %j.cmp, label %reduction.for, label %outer.exit



    reduction.for:
      %i = phi i32 [0, %outer.for], [%i.inc, %reduction.inc]
      %phi = phi double [0.0, %outer.for], [%add, %reduction.inc]
      %i.cmp = icmp slt i32 %i, 4
      br i1 %i.cmp, label %body, label %reduction.exit

    body:
      %add = fadd double %phi, 4.2
      br label %reduction.inc

    reduction.inc:
      %i.inc = add nuw nsw i32 %i, 1
      br label %reduction.for

    reduction.exit:
      %A_idx = getelementptr inbounds double, double* %A, i32 %j
      store double %phi, double* %A_idx
      br label %outer.inc



outer.inc:
  %j.inc = add nuw nsw i32 %j, 1
  br label %outer.for

outer.exit:
  br label %return

return:
  ret void
}

; Unrolled flattened schedule:
; [0] Stmt_outer_for[0]
; [1] Stmt_reduction_for[0, 0]
; [2] Stmt_body[0, 0]
; [3] Stmt_reduction_inc[0, 0]
; [4] Stmt_reduction_for[0, 1]
; [5] Stmt_body[0, 1]
; [6] Stmt_reduction_inc[0, 1]
; [7] Stmt_reduction_for[0, 2]
; [8] Stmt_body[0, 2]
; [9] Stmt_reduction_inc[0, 2]
; [10] Stmt_reduction_for[0, 3]
; [11] Stmt_body[0, 3]
; [12] Stmt_reduction_inc[0, 3]
; [13] Stmt_reduction_for[0, 4]
; [14] Stmt_reduction_exit[0]
; [15] Stmt_outer_for[1]
; [16] Stmt_reduction_for[1, 0]
; [17] Stmt_body[1, 0]
; [18] Stmt_reduction_inc[1, 0]
; [19] Stmt_reduction_for[1, 1]
; [20] Stmt_body[1, 1]
; [21] Stmt_reduction_inc[1, 1]
; [22] Stmt_reduction_for[1, 2]
; [23] Stmt_body[1, 2]
; [24] Stmt_reduction_inc[1, 2]
; [25] Stmt_reduction_for[1, 3]
; [26] Stmt_body[1, 3]
; [27] Stmt_reduction_inc[1, 3]
; [28] Stmt_reduction_for[1, 4]
; [29] Stmt_reduction_exit[1]
; [30] Stmt_outer_for[2]

; CHECK:      Schedule after flattening {
; CHECK-NEXT:     { Stmt_reduction_for[i0, i1] -> [1 + 15i0 + 3i1] }
; CHECK-NEXT:     { Stmt_reduction_exit[i0] -> [14 + 15i0] }
; CHECK-NEXT:     { Stmt_body[i0, i1] -> [2 + 15i0 + 3i1] }
; CHECK-NEXT:     { Stmt_outer_for[i0] -> [15i0] }
; CHECK-NEXT:     { Stmt_reduction_inc[i0, i1] -> [3 + 15i0 + 3i1] }
; CHECK-NEXT: }
; CHECK:      Original zone:
; CHECK-NEXT:     Lifetime: { [MemRef_A[i0] -> [i1{{\]\]}} -> Undef[] : 0 <= i0 <= 1 and i1 <= 14 + 15i0; [MemRef_A[i0] -> [i1{{\]\]}} -> [Stmt_reduction_for[i0, 4] -> Val_phi[{{\]\]}} : 0 <= i0 <= 1 and i1 >= 15 + 15i0 } + Unknown
; CHECK-NEXT:     Written : { [MemRef_A[i0] -> [14 + 15i0{{\]\]}} -> [Stmt_reduction_for[i0, 4] -> Val_phi[{{\]\]}} : 0 <= i0 <= 1 }
; CHECK:      Mapped scalars {
; CHECK-NEXT:     Scalar access ScopArrayInfo:
; CHECK-NEXT:         Accesses:  3
; CHECK-NEXT:         Target:    { Stmt_reduction_for[i0, i1] -> MemRef_A[i0] : 0 <= i0 <= 1 and 0 <= i1 <= 4 }
; CHECK-NEXT:         Lifetime:  { Stmt_reduction_for[i0, i1] -> [2 + 15i0 + 3i1] : 0 <= i0 <= 1 and 0 <= i1 <= 3; Stmt_reduction_for[1, 4] -> [29]; Stmt_reduction_for[0, 4] -> [14] }
; CHECK-NEXT:         Zone:
; CHECK-NEXT:             Lifetime: { [MemRef_A[i0] -> [i1{{\]\]}} -> [Stmt_reduction_for[i0, o1] -> Val_phi[{{\]\]}} : 3o1 = -2 - 15i0 + i1 and 0 <= i0 <= 1 and 2 + 15i0 <= i1 <= 11 + 15i0; [MemRef_A[1] -> [29{{\]\]}} -> [Stmt_reduction_for[1, 4] -> Val_phi[{{\]\]}}; [MemRef_A[0] -> [14{{\]\]}} -> [Stmt_reduction_for[0, 4] -> Val_phi[{{\]\]}} } + Undef
; CHECK-NEXT:             Written : { [MemRef_A[i0] -> [i1{{\]\]}} -> [Stmt_reduction_for[i0, o1] -> Val_phi[{{\]\]}} : 3o1 = -1 - 15i0 + i1 and 0 <= i0 <= 1 and 15i0 < i1 <= 13 + 15i0 }
; CHECK-NEXT: }
; CHECK:      After zone:
; CHECK-NEXT:     Lifetime: { [MemRef_A[i0] -> [i1{{\]\]}} -> [Stmt_reduction_for[i0, o1] -> Val_phi[{{\]\]}} : 3o1 = -2 - 15i0 + i1 and 0 <= i0 <= 1 and 2 + 15i0 <= i1 <= 11 + 15i0; [MemRef_A[i0] -> [i1{{\]\]}} -> [Stmt_reduction_for[i0, 4] -> Val_phi[{{\]\]}} : 0 <= i0 <= 1 and i1 >= 15 + 15i0; [MemRef_A[1] -> [29{{\]\]}} -> [Stmt_reduction_for[1, 4] -> Val_phi[{{\]\]}}; [MemRef_A[0] -> [14{{\]\]}} -> [Stmt_reduction_for[0, 4] -> Val_phi[{{\]\]}}; [MemRef_A[i0] -> [i1{{\]\]}} -> Undef[] : 0 <= i0 <= 1 and ((i1 <= 13 and 3*floor((-2 + i1)/3) <= -3 + i1) or (3*floor((-2 + i1)/3) = -2 + i1 and i1 <= 1 + 15i0)); [MemRef_A[1] -> [i1{{\]\]}} -> Undef[] : 14 <= i1 <= 28 and 3*floor((-2 + i1)/3) <= -3 + i1 } + Unknown
; CHECK-NEXT:     Written : { [MemRef_A[i0] -> [i1{{\]\]}} -> [Stmt_reduction_for[i0, o1] -> Val_phi[{{\]\]}} : 3o1 = -1 - 15i0 + i1 and 0 <= i0 <= 1 and 15i0 < i1 <= 13 + 15i0; [MemRef_A[i0] -> [14 + 15i0{{\]\]}} -> [Stmt_reduction_for[i0, 4] -> Val_phi[{{\]\]}} : 0 <= i0 <= 1 }
; CHECK:      After Statements {
; CHECK-NEXT:     Stmt_outer_for
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_outer_for[i0] -> MemRef_phi__phi[] };
; CHECK-NEXT:     Stmt_reduction_for
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_reduction_for[i0, i1] -> MemRef_phi__phi[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_reduction_for[i0, i1] -> MemRef_phi[] };
; CHECK-NEXT:            new: { Stmt_reduction_for[i0, i1] -> MemRef_A[i0] : 0 <= i0 <= 1 and 0 <= i1 <= 4 };
; CHECK-NEXT:     Stmt_body
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_body[i0, i1] -> MemRef_add[] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_body[i0, i1] -> MemRef_phi[] };
; CHECK-NEXT:            new: { Stmt_body[i0, i1] -> MemRef_A[i0] : 0 <= i0 <= 1 and i1 >= 0 and -5i0 <= i1 <= 8 - 5i0 and i1 <= 3 };
; CHECK-NEXT:     Stmt_reduction_inc
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_reduction_inc[i0, i1] -> MemRef_add[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_reduction_inc[i0, i1] -> MemRef_phi__phi[] };
; CHECK-NEXT:     Stmt_reduction_exit
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_reduction_exit[i0] -> MemRef_A[i0] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_reduction_exit[i0] -> MemRef_phi[] };
; CHECK-NEXT:            new: { Stmt_reduction_exit[i0] -> MemRef_A[i0] : 0 <= i0 <= 1 };
; CHECK-NEXT: }
