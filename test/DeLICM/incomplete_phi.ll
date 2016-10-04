; RUN: opt %loadPolly -polly-flatten-schedule -polly-delicm -polly-scops -analyze < %s | FileCheck %s
; XFAIL: *
target datalayout = "e-m:x-p:32:32-i64:64-f80:32-n8:16:32-a:0:32-S32"

define void @func(double* noalias nonnull %C) {
entry:
  br label %outer.for


    outer.for:
      %i = phi i32 [0, %entry], [%i.inc, %outer.inc]
      %i.cmp = icmp slt i32 %i, 3
      br i1 %i.cmp, label %outer.body, label %outer.exit

    outer.body:
      br label %inner.for

        inner.for:
          %phi = phi double [0.0, %outer.body], [%sum, %inner.inc]
          %j = phi i32 [0, %outer.body], [%j.inc, %inner.inc]
          %j.cmp = icmp slt i32 %j, 3
          br i1 %j.cmp, label %inner.body, label %inner.exit
      
        inner.body:
          %sum = fadd double %phi, 1.0 
          br label %inner.inc
        
        inner.inc:
          %j.inc = add nuw nsw i32 %j, 1
          br label %inner.for
        
        inner.exit:
          %C_i = getelementptr inbounds double, double* %C, i32 %i
          store double %phi, double* %C_i
          br label %outer.inc
        
    outer.inc:
      %i.inc = add nuw nsw i32 %i, 1
      br label %outer.for

    outer.exit:
      br label %return
  
  
return:
  ret void
}


;
; 0) Stmt_outer_body[0]
; 
; 
; 1) Stmt_inner_for[0, 0]
; 2) Stmt_inner_body[0, 0]
; 3) Stmt_inner_inc[0, 0]
; 
; 4) Stmt_inner_for[0, 1]
; 5) Stmt_inner_body[0, 1]
; 6) Stmt_inner_inc[0, 1]
; 
; 7) Stmt_inner_for[0, 2]
; 8) Stmt_inner_body[0, 2]
; 9) Stmt_inner_inc[0, 2]
; 
;10) Stmt_inner_for[0, 3]
;
;
;11) Stmt_inner_exit[1]
;12) Stmt_outer_body[1]
;
;
;13) Stmt_inner_for[1, 0]
;14) Stmt_inner_body[1, 0]
;15) Stmt_inner_inc[1, 0]
;
;16) Stmt_inner_for[1, 1]
;17) Stmt_inner_body[1, 1]
;18) Stmt_inner_inc[1, 1]
;
;19) Stmt_inner_for[1, 2]
;20) Stmt_inner_body[1, 2]
;21) Stmt_inner_inc[1, 2]
;
;22) Stmt_inner_for[1, 3]
;
;
;23) Stmt_inner_exit[1]
;24) Stmt_outer_body[2]
;
;25) Stmt_inner_for[2, 0]
;26) Stmt_inner_body[2, 0]
;27) Stmt_inner_inc[2, 0]
;
;28) Stmt_inner_for[2, 1]
;29) Stmt_inner_body[2, 1]
;30) Stmt_inner_inc[2, 1]
;
;31) Stmt_inner_for[2, 2]
;32) Stmt_inner_body[2, 2]
;33) Stmt_inner_inc[2, 2]
;
;34) Stmt_inner_for[2, 3]
;
;
;35) Stmt_inner_exit[0]


; CHECK:      Printing analysis 'Polly - Flatten schedule' for region: 'inner.for => inner.exit' in function 'func':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'inner.for => inner.exit' in function 'func':
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'inner.for => inner.exit' in function 'func':
; CHECK-NEXT: Invalid Scop!
; CHECK-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'outer.for => outer.exit' in function 'func':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'outer.for => outer.exit' in function 'func':
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'outer.for => outer.exit' in function 'func':
; CHECK-NEXT: Invalid Scop!
; CHECK-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'outer.for => return' in function 'func':
; CHECK-NEXT: Schedule before flattening {
; CHECK-NEXT:     { Stmt_inner_exit[i0] -> [i0, 2, 0, 0] }
; CHECK-NEXT:     { Stmt_inner_for[i0, i1] -> [i0, 1, i1, 0] }
; CHECK-NEXT:     { Stmt_inner_body[i0, i1] -> [i0, 1, i1, 1] }
; CHECK-NEXT:     { Stmt_outer_body[i0] -> [i0, 0, 0, 0] }
; CHECK-NEXT:     { Stmt_inner_inc[i0, i1] -> [i0, 1, i1, 2] }
; CHECK-NEXT: }
;
; CHECK:      Schedule after flattening {
; CHECK-NEXT:     { Stmt_outer_body[i0] -> [12i0] }
; CHECK-NEXT:     { Stmt_inner_inc[i0, i1] -> [3 + 12i0 + 3i1] }
; CHECK-NEXT:     { Stmt_inner_exit[i0] -> [11 + 12i0] }
; CHECK-NEXT:     { Stmt_inner_body[i0, i1] -> [2 + 12i0 + 3i1] }
; CHECK-NEXT:     { Stmt_inner_for[i0, i1] -> [1 + 12i0 + 3i1] }
; CHECK-NEXT: }
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'outer.for => return' in function 'func':
; CHECK-NEXT: Original Zone {
; CHECK-NEXT:     Lifetime: { [MemRef_C[i0] -> [i1{{\]\]}} -> Undef[] : 0 <= i0 <= 2 and i1 <= 11 + 12i0; [MemRef_C[i0] -> [i1{{\]\]}} -> [Stmt_inner_for[i0, 3] -> Val_double__phi[{{\]\]}} : 0 <= i0 <= 2 and i1 >= 12 + 12i0 }
; CHECK-NEXT:     Written:  { [MemRef_C[i0] -> [11 + 12i0{{\]\]}} -> [Stmt_inner_for[i0, 3] -> Val_double__phi[{{\]\]}} : 0 <= i0 <= 2 }
; CHECK-NEXT: }
; CHECK-NEXT: Mapped 0x20d19f56b10:
; CHECK-NEXT:     Accesses:  3
; CHECK-NEXT:     Target:    { Stmt_inner_for[i0, i1] -> MemRef_C[i0] : i1 >= 0 and 4 - 4i0 <= i1 <= 11 - 4i0 and i1 <= 3; Stmt_inner_for[0, i1] -> MemRef_C[0] : 0 <= i1 <= 3 }
; CHECK-NEXT:     Lifetime:  { Stmt_inner_for[i0, i1] -> [2 + 12i0 + 3i1] : 0 <= i0 <= 2 and 0 <= i1 <= 4 - i0 and i1 <= 3; Stmt_inner_for[2, 3] -> [35] }
; CHECK-NEXT:     Zone {
; CHECK-NEXT:         Lifetime: { [MemRef_C[i0] -> [i1{{\]\]}} -> [Stmt_inner_for[i0, o1] -> Val_double__phi[{{\]\]}} : 3o1 = -2 - 12i0 + i1 and i0 <= 2 and i1 >= 2 + 12i0 and 14 <= i1 <= 14 + 9i0 and i1 <= 11 + 12i0; [MemRef_C[0] -> [i1{{\]\]}} -> [Stmt_inner_for[0, o1] -> Val_double__phi[{{\]\]}} : 3o1 = -2 + i1 and 2 <= i1 <= 11; [MemRef_C[2] -> [35{{\]\]}} -> [Stmt_inner_for[2, 3] -> Val_double__phi[{{\]\]}} }
; CHECK-NEXT:         Written:  { [MemRef_C[i0] -> [i1{{\]\]}} -> [Stmt_inner_for[i0, o1] -> Val_double__phi[{{\]\]}} : 3o1 = -1 - 12i0 + i1 and i0 <= 2 and i1 > 12i0 and 13 <= i1 <= 10 + 12i0; [MemRef_C[0] -> [i1{{\]\]}} -> [Stmt_inner_for[0, o1] -> Val_double__phi[{{\]\]}} : 3o1 = -1 + i1 and 0 < i1 <= 10 }
; CHECK-NEXT:     }
; CHECK-NEXT: Cleanup: 
; CHECK-NEXT:     Stmt: Stmt_inner_exit
; CHECK-NEXT:     Scalar:   %phi = phi double [ 0.000000e+00, %outer.body ], [ %sum, %inner.inc ]
; CHECK-NEXT:     AccRel: { Stmt_inner_exit[i0] -> MemRef_C[i0] : 0 <= i0 <= 2 }
; CHECK-NEXT: After Zone {
; CHECK-NEXT:     Lifetime: { [MemRef_C[i0] -> [i1{{\]\]}} -> Undef[] : 0 <= i0 <= 2 and i1 <= 11 + 12i0 and ((i1 <= 34 and 3*floor((-2 + i1)/3) <= -3 + i1) or (3*floor((-2 + i1)/3) = -2 + i1 and i1 <= 1 + 12i0)); [MemRef_C[i0] -> [i1{{\]\]}} -> [Stmt_inner_for[i0, o1] -> Val_double__phi[{{\]\]}} : 3o1 = -2 - 12i0 + i1 and i0 <= 2 and i1 >= 2 + 12i0 and 14 <= i1 <= 14 + 9i0 and i1 <= 11 + 12i0; [MemRef_C[i0] -> [i1{{\]\]}} -> [Stmt_inner_for[i0, 3] -> Val_double__phi[{{\]\]}} : 0 <= i0 <= 2 and i1 >= 12 + 12i0; [MemRef_C[0] -> [i1{{\]\]}} -> [Stmt_inner_for[0, o1] -> Val_double__phi[{{\]\]}} : 3o1 = -2 + i1 and 2 <= i1 <= 11; [MemRef_C[2] -> [35{{\]\]}} -> [Stmt_inner_for[2, 3] -> Val_double__phi[{{\]\]}} }
; CHECK-NEXT:     Written:  { [MemRef_C[i0] -> [i1{{\]\]}} -> [Stmt_inner_for[i0, o1] -> Val_double__phi[{{\]\]}} : 3o1 = -1 - 12i0 + i1 and i0 <= 2 and i1 > 12i0 and 13 <= i1 <= 10 + 12i0; [MemRef_C[0] -> [i1{{\]\]}} -> [Stmt_inner_for[0, o1] -> Val_double__phi[{{\]\]}} : 3o1 = -1 + i1 and 0 < i1 <= 10; [MemRef_C[i0] -> [11 + 12i0{{\]\]}} -> [Stmt_inner_for[i0, 3] -> Val_double__phi[{{\]\]}} : 0 <= i0 <= 2 }
; CHECK-NEXT: }
; CHECK-NEXT: After Statements {
; CHECK-NEXT:     Stmt_outer_body
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_outer_body[i0] -> MemRef_phi__phi[] };
; CHECK-NEXT:     Stmt_inner_for
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_inner_for[i0, i1] -> MemRef_phi__phi[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_inner_for[i0, i1] -> MemRef_phi[] };
; CHECK-NEXT:            new: { Stmt_inner_for[i0, i1] -> MemRef_C[i0] : i1 >= 0 and 4 - 4i0 <= i1 <= 11 - 4i0 and i1 <= 3; Stmt_inner_for[0, i1] -> MemRef_C[0] : 0 <= i1 <= 3 };
; CHECK-NEXT:     Stmt_inner_body
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_inner_body[i0, i1] -> MemRef_sum[] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_inner_body[i0, i1] -> MemRef_phi[] };
; CHECK-NEXT:            new: { Stmt_inner_body[i0, i1] -> MemRef_C[i0] : i0 <= 2 and i1 >= 0 and 4 - 4i0 <= i1 <= 2; Stmt_inner_body[0, i1] -> MemRef_C[0] : 0 <= i1 <= 2 };
; CHECK-NEXT:     Stmt_inner_inc
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_inner_inc[i0, i1] -> MemRef_sum[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_inner_inc[i0, i1] -> MemRef_phi__phi[] };
; CHECK-NEXT: }
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'outer.for => return' in function 'func':
; CHECK-NEXT:     Function: func
; CHECK-NEXT:     Region: %outer.for---%return
; CHECK-NEXT:     Max Loop Depth:  2
; CHECK-NEXT:     Invariant Accesses: {
; CHECK-NEXT:     }
; CHECK-NEXT:     Context:
; CHECK-NEXT:     {  :  }
; CHECK-NEXT:     Assumed Context:
; CHECK-NEXT:     {  :  }
; CHECK-NEXT:     Invalid Context:
; CHECK-NEXT:     {  : 1 = 0 }
; CHECK-NEXT:     Arrays {
; CHECK-NEXT:         double MemRef_phi__phi; // Element size 8
; CHECK-NEXT:         double MemRef_phi; // Element size 8
; CHECK-NEXT:         double MemRef_sum; // Element size 8
; CHECK-NEXT:         double MemRef_C[*]; // Element size 8
; CHECK-NEXT:     }
; CHECK-NEXT:     Arrays (Bounds as pw_affs) {
; CHECK-NEXT:         double MemRef_phi__phi; // Element size 8
; CHECK-NEXT:         double MemRef_phi; // Element size 8
; CHECK-NEXT:         double MemRef_sum; // Element size 8
; CHECK-NEXT:         double MemRef_C[*]; // Element size 8
; CHECK-NEXT:     }
; CHECK-NEXT:     Alias Groups (0):
; CHECK-NEXT:         n/a
; CHECK-NEXT:     Statements {
; CHECK-NEXT:         Stmt_outer_body
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 { Stmt_outer_body[i0] : 0 <= i0 <= 2 };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 { Stmt_outer_body[i0] -> [i0, 0, 0, 0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_outer_body[i0] -> MemRef_phi__phi[] };
; CHECK-NEXT:         Stmt_inner_for
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 { Stmt_inner_for[i0, i1] : 0 <= i0 <= 2 and 0 <= i1 <= 3 };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 { Stmt_inner_for[i0, i1] -> [i0, 1, i1, 0] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_inner_for[i0, i1] -> MemRef_phi__phi[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_inner_for[i0, i1] -> MemRef_phi[] };
; CHECK-NEXT:         Stmt_inner_body
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 { Stmt_inner_body[i0, i1] : 0 <= i0 <= 2 and 0 <= i1 <= 2 };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 { Stmt_inner_body[i0, i1] -> [i0, 1, i1, 1] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_inner_body[i0, i1] -> MemRef_sum[] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_inner_body[i0, i1] -> MemRef_phi[] };
; CHECK-NEXT:         Stmt_inner_inc
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 { Stmt_inner_inc[i0, i1] : 0 <= i0 <= 2 and 0 <= i1 <= 2 };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 { Stmt_inner_inc[i0, i1] -> [i0, 1, i1, 2] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_inner_inc[i0, i1] -> MemRef_sum[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_inner_inc[i0, i1] -> MemRef_phi__phi[] };
; CHECK-NEXT:         Stmt_inner_exit
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 { Stmt_inner_exit[i0] : 0 <= i0 <= 2 };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 { Stmt_inner_exit[i0] -> [i0, 2, 0, 0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_inner_exit[i0] -> MemRef_C[i0] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_inner_exit[i0] -> MemRef_phi[] };
; CHECK-NEXT:     }
; CHECK-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'entry => <Function Return>' in function 'func':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'entry => <Function Return>' in function 'func':
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'entry => <Function Return>' in function 'func':
; CHECK-NEXT: Invalid Scop!
