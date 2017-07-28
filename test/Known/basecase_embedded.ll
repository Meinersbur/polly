; RUN: opt %loadPolly -polly-flatten-schedule -polly-optree -analyze < %s

define void @func(double* noalias nonnull %A, double* noalias nonnull %B) {
entry:
  br label %outer.for

outer.for:
  %j = phi i32 [0, %entry], [%j.inc, %outer.inc]
  %j.cmp = icmp slt i32 %j, 5
  br i1 %j.cmp, label %body1, label %outer.exit


    body1:
      %A_idx = getelementptr inbounds double, double* %A, i32 %j
      %val = load double, double* %A_idx
      store double %val, double* %A_idx
      br label %body2
      
    body2:
      %B_idx = getelementptr inbounds double, double* %B, i32 %j
      store double %val, double* %B_idx
      br label %outer.inc


outer.inc:
  %j.inc = add nuw nsw i32 %j, 1
  br label %outer.for

outer.exit:
  br label %return

return:
  ret void
}


; Unrolled statement instances:
; [0] Stmt_body1[0]
;         A[0] := %val[0]
; [1] Stmt_body2[0]
;         B[0] := A[0] = %val[0]
; [2] Stmt_body1[1]
;         A[1] := %val[1]
; [3] Stmt_body2[1]
;         B[1] := A[1] = %val[1]
; [4] Stmt_body1[2]
;         A[2] := %val[2]
; [5] Stmt_body2[2]
;         B[2] := A[2] = %val[2]
; [6] Stmt_body1[3]
;         A[3] := %val[3]
; [7] Stmt_body2[3]
;         B[3] := A[3] = %val[3]
; [8] Stmt_body1[4]
;         A[4] := %val[4]
; [9] Stmt_body2[4]
;         B[4] := A[4] = %val[4]


; CHECK:      Schedule after flattening {
; CHECK-NEXT:     { Stmt_body1[i0] -> [2i0] }
; CHECK-NEXT:     { Stmt_body2[i0] -> [1 + 2i0] }
; CHECK-NEXT: }
; CHECK:      Known zone: { [MemRef_A[i0] -> [i1{{\]\]}} -> [Stmt_body1[i0] -> Val_val[{{\]\]}} : 0 <= i0 <= 4; [MemRef_B[i0] -> [i1{{\]\]}} -> [Stmt_body1[i0] -> Val_val[{{\]\]}} : 0 <= i0 <= 4 and i1 >= 2 + 2i0 }
; CHECK:      Redirected knowns {
; CHECK-NEXT:     Redirect Stmt_body1 Array Load %val from { Stmt_body1[i0] -> MemRef_A[i0] } {
; CHECK-NEXT:         Expects   : { Stmt_body2[i0] -> [Stmt_body1[i0] -> Val_val[{{\]\]}} : 0 <= i0 <= 3; Stmt_body2[4] -> [Stmt_body1[4] -> Val_val[{{\]\]}} }
; CHECK-NEXT:         Candidates: { Stmt_body2[i0] -> MemRef_A[i0] : 0 <= i0 <= 4 }
; CHECK-NEXT:         Chosen    : { Stmt_body2[i0] -> MemRef_A[i0] : 0 <= i0 <= 4 }
; CHECK-NEXT:     }
; CHECK-NEXT: }
; CHECK:      After accesses {
; CHECK-NEXT:     Stmt_body1
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_body1[i0] -> MemRef_A[i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_body1[i0] -> MemRef_A[i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_body1[i0] -> MemRef_val[] };
; CHECK-NEXT:     Stmt_body2
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_body2[i0] -> MemRef_B[i0] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_body2[i0] -> MemRef_val[] };
; CHECK-NEXT:            new: { Stmt_body2[i0] -> MemRef_A[i0] : 0 <= i0 <= 4 };
; CHECK-NEXT: }
