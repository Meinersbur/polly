; RUN: opt %loadPolly -polly-flatten-schedule -polly-known -analyze < %s | FileCheck %s --check-prefix=KNOWN
; RUN: opt %loadPolly -polly-flatten-schedule -polly-delicm -analyze < %s | FileCheck %s --check-prefix=DELICM
; XFAIL: *
;    void func(double *A) {
;      for (int j = 0; j < 1; j += 1) { /* outer */
;        double a = A[j];
;        for (int i = 0; i < 4; i += 1) /* reduction */
;          phi += 4.2;
;        A[j] = phi;
;      }
;    }

define void @func(double* noalias nonnull %A, double* noalias nonnull %B) {
entry:
  br label %outer.for

outer.for:
  %j = phi i32 [0, %entry], [%j.inc, %outer.inc]
  %j.cmp = icmp slt i32 %j, 2
  br i1 %j.cmp, label %outer.body, label %outer.exit
  
  
    outer.body:
      %A_idx = getelementptr inbounds double, double* %A, i32 %j
      %a = load double, double* %A_idx
      br label %reduction.for
 
    reduction.for:
      %i = phi i32 [0, %outer.body], [%i.inc, %reduction.inc]
      %i.cmp = icmp slt i32 %i, 4
      br i1 %i.cmp, label %body, label %reduction.exit

        body:
          %B_idx = getelementptr inbounds double, double* %B, i32 %i
          store double %a, double* %B_idx
          br label %reduction.inc

    reduction.inc:
      %i.inc = add nuw nsw i32 %i, 1
      br label %reduction.for

    reduction.exit:
      br label %outer.inc
  
  
outer.inc:
  %j.inc = add nuw nsw i32 %j, 1
  br label %outer.for

outer.exit:
  br label %return

return:
  ret void
}

; [0] <- Stmt_outer_body[0]
; [1] <- Stmt_body[0, 0]
; [2] <- Stmt_body[0, 1]
; [3] <- Stmt_body[0, 2]
; [4] <- Stmt_body[0, 3]
; [5] <- Stmt_outer_body[1]
; [6] <- Stmt_body[1, 0]
; [7] <- Stmt_body[1, 1]
; [8] <- Stmt_body[1, 2]
; [9] <- Stmt_body[1, 3]


; KNOWN:      Printing analysis 'Polly - Flatten schedule' for region: 'reduction.for => reduction.exit' in function 'func':
; KNOWN-NEXT: Printing analysis 'Polly - Scalar accesses to explicit' for region: 'reduction.for => reduction.exit' in function 'func':
; KNOWN-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'outer.for => outer.exit' in function 'func':
; KNOWN-NEXT: Printing analysis 'Polly - Scalar accesses to explicit' for region: 'outer.for => outer.exit' in function 'func':
; KNOWN-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'outer.for => return' in function 'func':
; KNOWN-NEXT: Schedule before flattening {
; KNOWN-NEXT:     { Stmt_body[i0, i1] -> [i0, 1, i1] }
; KNOWN-NEXT:     { Stmt_outer_body[i0] -> [i0, 0, 0] }
; KNOWN-NEXT: }
;
; KNOWN:      Schedule after flattening {
; KNOWN-NEXT:     { Stmt_body[i0, i1] -> [1 + 5i0 + i1] }
; KNOWN-NEXT:     { Stmt_outer_body[i0] -> [5i0] }
; KNOWN-NEXT: }
; KNOWN-NEXT: Printing analysis 'Polly - Scalar accesses to explicit' for region: 'outer.for => return' in function 'func':
; KNOWN-NEXT: Mapped Knowns {
; KNOWN-NEXT:     Known occurrence {
; KNOWN-NEXT:         MA: Stmt_body_Read1_MemRef_a MK_Value Use MemRef_a [new: { Stmt_body[i0, i1] -> MemRef_A[i0] : 0 <= i0 <= 1 and 0 <= i1 <= 3 }]
; KNOWN-NEXT:         Taken from: { Stmt_body[i0, i1] -> MemRef_A[i0] : 0 <= i0 <= 1 and 0 <= i1 <= 3 }
; KNOWN-NEXT:         New location: { Stmt_body[i0, i1] -> MemRef_A[i0] : 0 <= i0 <= 1 and 0 <= i1 <= 3 }
; KNOWN-NEXT:     }
; KNOWN-NEXT: }
; KNOWN-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'entry => <Function Return>' in function 'func':
; KNOWN-NEXT: Printing analysis 'Polly - Scalar accesses to explicit' for region: 'entry => <Function Return>' in function 'func':

; DELICM:      Printing analysis 'Polly - Flatten schedule' for region: 'reduction.for => reduction.exit' in function 'func':
; DELICM-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'reduction.for => reduction.exit' in function 'func':
; DELICM-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'outer.for => outer.exit' in function 'func':
; DELICM-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'outer.for => outer.exit' in function 'func':
; DELICM-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'outer.for => return' in function 'func':
; DELICM-NEXT: Schedule before flattening {
; DELICM-NEXT:     { Stmt_body[i0, i1] -> [i0, 1, i1] }
; DELICM-NEXT:     { Stmt_outer_body[i0] -> [i0, 0, 0] }
; DELICM-NEXT: }
;
; DELICM:      Schedule after flattening {
; DELICM-NEXT:     { Stmt_body[i0, i1] -> [1 + 5i0 + i1] }
; DELICM-NEXT:     { Stmt_outer_body[i0] -> [5i0] }
; DELICM-NEXT: }
; DELICM-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'outer.for => return' in function 'func':
; DELICM-NEXT: Original Zone {
; DELICM-NEXT:     Lifetime: { [MemRef_B[i0] -> [i1{{\]\]}} -> [Stmt_outer_body[1] -> Val_double__a[{{\]\]}} : 0 <= i0 <= 3 and i1 >= 7 + i0; [MemRef_B[i0] -> [i1{{\]\]}} -> Undef[] : 0 <= i0 <= 3 and i1 <= 6 + i0 }
; DELICM-NEXT:     Written:  { [MemRef_B[i0] -> [i1{{\]\]}} -> [Stmt_outer_body[o0] -> Val_double__a[{{\]\]}} : 5o0 = -1 - i0 + i1 and 0 <= i0 <= 3 and i0 < i1 <= 6 + i0 }
; DELICM-NEXT: }
; DELICM-NEXT: Mapped 0x24e8b7a6e10:
; DELICM-NEXT:     Accesses:  2
; DELICM-NEXT:     Target:    { Stmt_outer_body[i0] -> MemRef_B[0] : 0 <= i0 <= 1 }
; DELICM-NEXT:     Lifetime:  { Stmt_outer_body[1] -> [o0] : 6 <= o0 <= 9; Stmt_outer_body[0] -> [o0] : 0 < o0 <= 4 }
; DELICM-NEXT:     Zone {
; DELICM-NEXT:         Lifetime: { [MemRef_B[0] -> [i1{{\]\]}} -> [Stmt_outer_body[1] -> Val_double__a[{{\]\]}} : 6 <= i1 <= 9; [MemRef_B[0] -> [i1{{\]\]}} -> [Stmt_outer_body[0] -> Val_double__a[{{\]\]}} : 0 < i1 <= 4 }
; DELICM-NEXT:         Written:  { [MemRef_B[0] -> [i1{{\]\]}} -> [Stmt_outer_body[o0] -> Val_double__a[{{\]\]}} : 5o0 = i1 and 0 <= i1 <= 5 }
; DELICM-NEXT:     }
; DELICM-NEXT: After Zone {
; DELICM-NEXT:     Lifetime: { [MemRef_B[i0] -> [i1{{\]\]}} -> [Stmt_outer_body[1] -> Val_double__a[{{\]\]}} : 0 < i0 <= 3 and i1 >= 7 + i0; [MemRef_B[0] -> [i1{{\]\]}} -> [Stmt_outer_body[1] -> Val_double__a[{{\]\]}} : i1 >= 6 and (i1 >= 10 or i1 <= 9); [MemRef_B[0] -> [i1{{\]\]}} -> [Stmt_outer_body[0] -> Val_double__a[{{\]\]}} : 0 < i1 <= 4; [MemRef_B[i0] -> [i1{{\]\]}} -> Undef[] : 0 < i0 <= 3 and i1 <= 6 + i0; [MemRef_B[0] -> [i1{{\]\]}} -> Undef[] : i1 <= 0; [MemRef_B[0] -> [5{{\]\]}} -> Undef[] }
; DELICM-NEXT:     Written:  { [MemRef_B[i0] -> [i1{{\]\]}} -> [Stmt_outer_body[o0] -> Val_double__a[{{\]\]}} : 5o0 = -1 - i0 + i1 and 0 <= i0 <= 3 and i0 < i1 <= 6 + i0; [MemRef_B[0] -> [i1{{\]\]}} -> [Stmt_outer_body[o0] -> Val_double__a[{{\]\]}} : 5o0 = i1 and 0 <= i1 <= 5 }
; DELICM-NEXT: }
; DELICM-NEXT: After Statements {
; DELICM-NEXT:     Stmt_outer_body
; DELICM-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; DELICM-NEXT:                 { Stmt_outer_body[i0] -> MemRef_A[i0] };
; DELICM-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; DELICM-NEXT:                 { Stmt_outer_body[i0] -> MemRef_a[] };
; DELICM-NEXT:            new: { Stmt_outer_body[i0] -> MemRef_B[0] : 0 <= i0 <= 1 };
; DELICM-NEXT:     Stmt_body
; DELICM-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; DELICM-NEXT:                 { Stmt_body[i0, i1] -> MemRef_B[i1] };
; DELICM-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; DELICM-NEXT:                 { Stmt_body[i0, i1] -> MemRef_a[] };
; DELICM-NEXT:            new: { Stmt_body[i0, i1] -> MemRef_B[0] : 0 <= i0 <= 1 and i1 >= 0 and -5i0 <= i1 <= 3 };
; DELICM-NEXT: }
; DELICM-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'entry => <Function Return>' in function 'func':
; DELICM-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'entry => <Function Return>' in function 'func':
