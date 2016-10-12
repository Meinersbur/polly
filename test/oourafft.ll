; RUN: opt %loadPolly -basicaa -scoped-noalias -tbaa -polly-delicm -analyze < %s

; Derived from test-suite/../../../../../mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/SingleSource/Benchmarks/Misc/oourafft.c

; ModuleID = '/tmp/bugpoint-dw4h9zhh/bugpoint-reduced-simplified.bc'
source_filename = "bugpoint-output-7b19655.bc"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define void @putdata(i32 %nend, double* %a) #0 {
entry:
  br label %entry.split

entry.split:                                      ; preds = %entry
  br i1 false, label %for.end, label %for.body.lr.ph

for.body.lr.ph:                                   ; preds = %entry.split
  %0 = sext i32 %nend to i64
  br label %for.body

for.body:                                         ; preds = %for.body, %for.body.lr.ph
  %indvars.iv = phi i64 [ %indvars.iv.next, %for.body ], [ 0, %for.body.lr.ph ]
  %seed.03 = phi i32 [ 0, %for.body.lr.ph ], [ %rem, %for.body ]
  %rem = srem i32 undef, 259200
  %arrayidx = getelementptr inbounds double, double* %a, i64 %indvars.iv
  store double undef, double* %arrayidx, align 8
  %indvars.iv.next = add nsw i64 %indvars.iv, 1
  %cmp = icmp slt i64 %indvars.iv, %0
  br i1 %cmp, label %for.body, label %for.cond.for.end_crit_edge

for.cond.for.end_crit_edge:                       ; preds = %for.body
  br label %for.end

for.end:                                          ; preds = %for.cond.for.end_crit_edge, %entry.split
  ret void
}

attributes #0 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (trunk 283725) (llvm/trunk 283723)"}
