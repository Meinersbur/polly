; RUN: opt %loadPolly -polly-scops -analyze < %s | FileCheck %s -check-prefix=SCOPS
; RUN: opt %loadPolly -polly-codegen -S < %s | FileCheck %s -check-prefix=CODEGEN
;
;    void foo(long n, float A[n]) {
;      for (long i = 0; i < n; i += 1) {
;        A[i] += 1;
;        A[i] += 1;
;      }
;    }

target datalayout = "e-m:w-i64:64-f80:128-n8:16:32:64-S128"

define void @foo(i32 %n, float* %A) #1 {
entry:
  %tmp = sext i32 %n to i64
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %indvars.iv = phi i64 [ %indvars.iv.next, %for.inc ], [ 0, %entry ]
  %cmp = icmp slt i64 %indvars.iv, %tmp
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %arrayidx = getelementptr inbounds float, float* %A, i64 %indvars.iv
  %tmp1 = load float, float* %arrayidx, align 4
  %add = fadd float %tmp1, 1.000000e+00
  store float %add, float* %arrayidx, align 4
  %arrayidx2 = getelementptr inbounds float, float* %A, i64 %indvars.iv
  %tmp2 = load float, float* %arrayidx2, align 4
  %add3 = fadd float %tmp2, 1.000000e+00
  store float %add3, float* %arrayidx2, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret void
}

attributes #1 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

; SCOPS:      Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'for.cond => for.end' in function 'foo':
; SCOPS-NEXT:     Function: foo
; SCOPS-NEXT:     Region: %for.cond---%for.end
; SCOPS-NEXT:     Max Loop Depth:  1
; SCOPS-NEXT:     Invariant Accesses: {
; SCOPS-NEXT:     }
; SCOPS-NEXT:     Context:
; SCOPS-NEXT:     [n] -> {  : -2147483648 <= n <= 2147483647 }
; SCOPS-NEXT:     Assumed Context:
; SCOPS-NEXT:     [n] -> {  :  }
; SCOPS-NEXT:     Invalid Context:
; SCOPS-NEXT:     [n] -> {  : 1 = 0 }
; SCOPS-NEXT:     p0: %n
; SCOPS-NEXT:     Arrays {
; SCOPS-NEXT:         float MemRef_A[*]; // Element size 4
; SCOPS-NEXT:     }
; SCOPS-NEXT:     Arrays (Bounds as pw_affs) {
; SCOPS-NEXT:         float MemRef_A[*]; // Element size 4
; SCOPS-NEXT:     }
; SCOPS-NEXT:     Alias Groups (0):
; SCOPS-NEXT:         n/a
; SCOPS-NEXT:     Statements {
; SCOPS-NEXT:         Stmt_for_body
; SCOPS-NEXT:             Domain :=
; SCOPS-NEXT:                 [n] -> { Stmt_for_body[i0] : 0 <= i0 < n };
; SCOPS-NEXT:             Schedule :=
; SCOPS-NEXT:                 [n] -> { Stmt_for_body[i0] -> [i0] };
; SCOPS-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; SCOPS-NEXT:                 [n] -> { Stmt_for_body[i0] -> MemRef_A[i0] };
; SCOPS-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; SCOPS-NEXT:                 [n] -> { Stmt_for_body[i0] -> MemRef_A[i0] };
; SCOPS-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; SCOPS-NEXT:                 [n] -> { Stmt_for_body[i0] -> MemRef_A[i0] };
; SCOPS-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; SCOPS-NEXT:                 [n] -> { Stmt_for_body[i0] -> MemRef_A[i0] };
; SCOPS-NEXT:     }
; SCOPS-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'entry => <Function Return>' in function 'foo':
; SCOPS-NEXT: Invalid Scop!

; CODEGEN:      ; ModuleID = '<stdin>'
; CODEGEN-NEXT: target datalayout = "e-m:w-i64:64-f80:128-n8:16:32:64-S128"
;
; CODEGEN:      ; Function Attrs: nounwind uwtable
; CODEGEN-NEXT: define void @foo(i32 %n, float* %A) #0 {
; CODEGEN-NEXT: entry:
; CODEGEN-NEXT:   %tmp = sext i32 %n to i64
; CODEGEN-NEXT:   br label %polly.split_new_and_old
;
; CODEGEN:      polly.split_new_and_old:                          ; preds = %entry
; CODEGEN-NEXT:   br i1 true, label %polly.start, label %for.cond
;
; CODEGEN:      for.cond:                                         ; preds = %polly.split_new_and_old, %for.inc
; CODEGEN-NEXT:   %indvars.iv = phi i64 [ %indvars.iv.next, %for.inc ], [ 0, %polly.split_new_and_old ]
; CODEGEN-NEXT:   %cmp = icmp slt i64 %indvars.iv, %tmp
; CODEGEN-NEXT:   br i1 %cmp, label %for.body, label %polly.merge_new_and_old
;
; CODEGEN:      for.body:                                         ; preds = %for.cond
; CODEGEN-NEXT:   %arrayidx = getelementptr inbounds float, float* %A, i64 %indvars.iv
; CODEGEN-NEXT:   %tmp1 = load float, float* %arrayidx, align 4
; CODEGEN-NEXT:   %add = fadd float %tmp1, 1.000000e+00
; CODEGEN-NEXT:   store float %add, float* %arrayidx, align 4
; CODEGEN-NEXT:   %arrayidx2 = getelementptr inbounds float, float* %A, i64 %indvars.iv
; CODEGEN-NEXT:   %tmp2 = load float, float* %arrayidx2, align 4
; CODEGEN-NEXT:   %add3 = fadd float %tmp2, 1.000000e+00
; CODEGEN-NEXT:   store float %add3, float* %arrayidx2, align 4
; CODEGEN-NEXT:   br label %for.inc
;
; CODEGEN:      for.inc:                                          ; preds = %for.body
; CODEGEN-NEXT:   %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1
; CODEGEN-NEXT:   br label %for.cond
;
; CODEGEN:      polly.merge_new_and_old:                          ; preds = %polly.exiting, %for.cond
; CODEGEN-NEXT:   br label %for.end
;
; CODEGEN:      for.end:                                          ; preds = %polly.merge_new_and_old
; CODEGEN-NEXT:   ret void
;
; CODEGEN:      polly.start:                                      ; preds = %polly.split_new_and_old
; CODEGEN-NEXT:   %0 = sext i32 %n to i64
; CODEGEN-NEXT:   br label %polly.loop_if
;
; CODEGEN:      polly.loop_exit:                                  ; preds = %polly.stmt.for.body, %polly.loop_if
; CODEGEN-NEXT:   br label %polly.exiting
;
; CODEGEN:      polly.exiting:                                    ; preds = %polly.loop_exit
; CODEGEN-NEXT:   br label %polly.merge_new_and_old
;
; CODEGEN:      polly.loop_if:                                    ; preds = %polly.start
; CODEGEN-NEXT:   %polly.loop_guard = icmp slt i64 0, %0
; CODEGEN-NEXT:   br i1 %polly.loop_guard, label %polly.loop_preheader, label %polly.loop_exit
;
; CODEGEN:      polly.loop_header:                                ; preds = %polly.stmt.for.body, %polly.loop_preheader
; CODEGEN-NEXT:   %polly.indvar = phi i64 [ 0, %polly.loop_preheader ], [ %polly.indvar_next, %polly.stmt.for.body ]
; CODEGEN-NEXT:   br label %polly.stmt.for.body
;
; CODEGEN:      polly.stmt.for.body:                              ; preds = %polly.loop_header
; CODEGEN-NEXT:   %scevgep = getelementptr float, float* %A, i64 %polly.indvar
; CODEGEN-NEXT:   %tmp1_p_scalar_ = load float, float* %scevgep, align 4, !alias.scope !0, !noalias !2
; CODEGEN-NEXT:   %p_add = fadd float %tmp1_p_scalar_, 1.000000e+00
; CODEGEN-NEXT:   store float %p_add, float* %scevgep, align 4, !alias.scope !0, !noalias !2
; CODEGEN-NEXT:   %scevgep1 = getelementptr float, float* %A, i64 %polly.indvar
; CODEGEN-NEXT:   %tmp2_p_scalar_ = load float, float* %scevgep1, align 4, !alias.scope !0, !noalias !2
; CODEGEN-NEXT:   %p_add3 = fadd float %tmp2_p_scalar_, 1.000000e+00
; CODEGEN-NEXT:   store float %p_add3, float* %scevgep1, align 4, !alias.scope !0, !noalias !2
; CODEGEN-NEXT:   %polly.indvar_next = add nsw i64 %polly.indvar, 1
; CODEGEN-NEXT:   %polly.adjust_ub = sub i64 %0, 1
; CODEGEN-NEXT:   %polly.loop_cond = icmp slt i64 %polly.indvar, %polly.adjust_ub
; CODEGEN-NEXT:   br i1 %polly.loop_cond, label %polly.loop_header, label %polly.loop_exit
;
; CODEGEN:      polly.loop_preheader:                             ; preds = %polly.loop_if
; CODEGEN-NEXT:   br label %polly.loop_header
; CODEGEN-NEXT: }
;
; CODEGEN:      attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "polly-optimized" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
;
; CODEGEN:      !0 = distinct !{!0, !1, !"polly.alias.scope.A"}
; CODEGEN-NEXT: !1 = distinct !{!1, !"polly.alias.scope.domain"}
; CODEGEN-NEXT: !2 = !{}
