; RUN: opt %loadPolly -basicaa -scoped-noalias -tbaa -polly-delicm -analyze < %s

; Derived from test-suite/../../../../../mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/datamining/correlation/correlation.c

; ModuleID = '/tmp/bugpoint-xo0jvlru/bugpoint-reduced-simplified.bc'
source_filename = "bugpoint-output-62fa5d1.bc"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define void @kernel_correlation(i32 %m, i32 %n, double* %mean) #0 {
entry:
  br label %for.body

for.cond.for.cond15.preheader_crit_edge:          ; preds = %for.end
  unreachable

for.body:                                         ; preds = %for.end, %entry
  %indvars.iv31 = phi i64 [ %indvars.iv.next32, %for.end ], [ 0, %entry ]
  %arrayidx = getelementptr inbounds double, double* %mean, i64 %indvars.iv31
  br label %for.body3

for.body3:                                        ; preds = %for.body3, %for.body
  %indvars.iv27 = phi i64 [ %indvars.iv.next28, %for.body3 ], [ 0, %for.body ]
  %0 = phi double [ 0.000000e+00, %for.body ], [ undef, %for.body3 ]
  store double undef, double* %arrayidx, align 8
  %indvars.iv.next28 = add nuw nsw i64 %indvars.iv27, 1
  %wide.trip.count29 = zext i32 %n to i64
  %exitcond30 = icmp ne i64 %indvars.iv.next28, %wide.trip.count29
  br i1 %exitcond30, label %for.body3, label %for.cond1.for.end_crit_edge

for.cond1.for.end_crit_edge:                      ; preds = %for.body3
  br label %for.end

for.end:                                          ; preds = %for.cond1.for.end_crit_edge
  %indvars.iv.next32 = add nuw nsw i64 %indvars.iv31, 1
  %wide.trip.count33 = zext i32 %m to i64
  %exitcond34 = icmp ne i64 %indvars.iv.next32, %wide.trip.count33
  br i1 %exitcond34, label %for.body, label %for.cond.for.cond15.preheader_crit_edge
}

attributes #0 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (trunk 283725) (llvm/trunk 283723)"}
