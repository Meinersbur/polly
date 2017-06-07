; RUN: opt %loadPolly -polly-flatten-schedule -polly-known -analyze < %s


define void @func(double* noalias nonnull %B) {
entry:
  br label %outer.for

outer.for:
  %j = phi i32 [0, %entry], [%j.inc, %outer.inc]
  %j.cmp = icmp slt i32 %j, 5
  br i1 %j.cmp, label %body1, label %outer.exit


    body1:
      %val = fadd double 1.2, 1.3
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


; CHECK:      Schedule after flattening {
; CHECK-NEXT:     { Stmt_body1[i0] -> [2i0] }
; CHECK-NEXT:     { Stmt_body2[i0] -> [1 + 2i0] }
; CHECK-NEXT: }
; CHECK:      Known zone: { [MemRef_B[i0] -> [i1{{\]\]}} -> [Stmt_body1[i0] -> Val_val[{{\]\]}} : 0 <= i0 <= 4 and i1 >= 2 + 2i0 }
; CHECK:      Redirected knowns {
; CHECK-NEXT: }
; CHECK:      After accesses {
; CHECK-NEXT:     Stmt_body1
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_body1[i0] -> MemRef_val[] };
; CHECK-NEXT:     Stmt_body2
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_body2[i0] -> MemRef_B[i0] };
; CHECK-NEXT: }
