; RUN: opt %loadPolly -polly-scops -polly-analyze-scop -analyze < %s | FileCheck %s -match-full-lines
; RUN: opt %loadPolly              -polly-analyze-scop -analyze < %s | FileCheck %s -match-full-lines -check-prefix=UNAVAILABLE
;
; Test the basic functionality of the -polly-analyze-scop pass.
;
; for (int j = 0; j < n; j += 1)
;   A[0] = 42.0;
;
define void @func(i32 %n, double* noalias nonnull %A) {
entry:
  br label %for

for:
  %j = phi i32 [0, %entry], [%j.inc, %inc]
  %j.cmp = icmp slt i32 %j, %n
  br i1 %j.cmp, label %body, label %exit

    body:
      store double 42.0, double* %A
      br label %inc

inc:
  %j.inc = add nuw nsw i32 %j, 1
  br label %for

exit:
  br label %return

return:
  ret void
}


; CHECK:      Function: func
; CHECK-NEXT: Region: %for---%return

; UNAVAILABLE: No SCoP analysis available
