; RUN: opt %loadPolly -polly-delicm -analyze < %s

; Derived from test-suite/../../../../../mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/linear-algebra/solvers/durbin/durbin.c

; ModuleID = '/tmp/bugpoint-91g4tr4u/bugpoint-reduced-simplified.bc'
source_filename = "bugpoint-output-bd5b139.bc"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define void @kernel_durbin(i32 %n, [4000 x double]* %y, double* %beta) #0 {
entry:
  br label %entry.split

entry.split:                                      ; preds = %entry
  br i1 undef, label %for.body.lr.ph, label %for.cond94.preheader

for.body.lr.ph:                                   ; preds = %entry.split
  br label %for.body

for.cond.for.cond94.preheader_crit_edge:          ; preds = %for.end84
  br label %for.cond94.preheader

for.cond94.preheader:                             ; preds = %for.cond.for.cond94.preheader_crit_edge, %entry.split
  br i1 undef, label %for.body96.lr.ph, label %for.end106

for.body96.lr.ph:                                 ; preds = %for.cond94.preheader
  br label %for.body96

for.body:                                         ; preds = %for.end84, %for.body.lr.ph
  %indvars.iv15 = phi i64 [ %indvars.iv.next16, %for.end84 ], [ 1, %for.body.lr.ph ]
  %indvars.iv11 = phi i32 [ undef, %for.end84 ], [ 1, %for.body.lr.ph ]
  %arrayidx19 = getelementptr inbounds double, double* %beta, i64 %indvars.iv15
  store double undef, double* %arrayidx19, align 8
  br i1 true, label %for.body28.lr.ph, label %for.end

for.body28.lr.ph:                                 ; preds = %for.body
  br label %for.body28

for.body28:                                       ; preds = %for.body28, %for.body28.lr.ph
  %arrayidx41 = getelementptr inbounds [4000 x double], [4000 x double]* %y, i64 0, i64 0
  %0 = load double, double* %arrayidx41, align 8
  %indvars.iv.next2 = add nuw nsw i64 0, 1
  %lftr.wideiv6 = trunc i64 %indvars.iv.next2 to i32
  br i1 false, label %for.body28, label %for.cond25.for.end_crit_edge

for.cond25.for.end_crit_edge:                     ; preds = %for.body28
  br label %for.end

for.end:                                          ; preds = %for.cond25.for.end_crit_edge, %for.body
  br i1 true, label %for.body61.lr.ph, label %for.end84

for.body61.lr.ph:                                 ; preds = %for.end
  br label %for.body61

for.body61:                                       ; preds = %for.body61, %for.body61.lr.ph
  %indvars.iv.next9 = add nuw nsw i64 0, 1
  %lftr.wideiv13 = trunc i64 %indvars.iv.next9 to i32
  br i1 false, label %for.body61, label %for.cond58.for.end84_crit_edge

for.cond58.for.end84_crit_edge:                   ; preds = %for.body61
  br label %for.end84

for.end84:                                        ; preds = %for.cond58.for.end84_crit_edge, %for.end
  %.lcssa = phi double [ undef, %for.cond58.for.end84_crit_edge ], [ undef, %for.end ]
  %arrayidx90 = getelementptr inbounds [4000 x double], [4000 x double]* %y, i64 %indvars.iv15, i64 %indvars.iv15
  store double %.lcssa, double* %arrayidx90, align 8
  %indvars.iv.next16 = add nuw nsw i64 %indvars.iv15, 1
  %exitcond22 = icmp ne i32 0, %n
  br i1 %exitcond22, label %for.body, label %for.cond.for.cond94.preheader_crit_edge

for.body96:                                       ; preds = %for.body96, %for.body96.lr.ph
  br i1 undef, label %for.body96, label %for.cond94.for.end106_crit_edge

for.cond94.for.end106_crit_edge:                  ; preds = %for.body96
  br label %for.end106

for.end106:                                       ; preds = %for.cond94.for.end106_crit_edge, %for.cond94.preheader
  ret void
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (trunk 276370)"}
