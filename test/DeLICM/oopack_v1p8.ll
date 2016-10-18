; RUN: opt %loadPolly -basicaa -scoped-noalias -tbaa -polly-delicm -analyze < %s

; Derived from test-suite/../../../../../mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/SingleSource/Benchmarks/Misc-C++/oopack_v1p8.cpp

; ModuleID = '/tmp/bugpoint-lfqv27dw/bugpoint-reduced-simplified.bc'
source_filename = "bugpoint-output-327cbd4.bc"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@E = external global [2500 x double], align 16

; Function Attrs: nounwind uwtable
define void @_ZNK15MatrixBenchmark7c_styleEv() unnamed_addr #0 align 2 {
entry:
  br label %for.cond5.preheader

for.cond5.preheader:                              ; preds = %for.end, %entry
  %indvars.iv4 = phi i64 [ %indvars.iv.next5, %for.end ], [ 0, %entry ]
  br label %for.body7

for.body7:                                        ; preds = %for.body7, %for.cond5.preheader
  %indvars.iv = phi i64 [ %indvars.iv.next, %for.body7 ], [ 0, %for.cond5.preheader ]
  %sum.01 = phi double [ 0.000000e+00, %for.cond5.preheader ], [ undef, %for.body7 ]
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1
  %exitcond = icmp ne i64 %indvars.iv.next, 50
  br i1 %exitcond, label %for.body7, label %for.end

for.end:                                          ; preds = %for.body7
  %add13.lcssa = phi double [ undef, %for.body7 ]
  %0 = add nuw nsw i64 %indvars.iv4, 0
  %arrayidx17 = getelementptr inbounds [2500 x double], [2500 x double]* @E, i64 0, i64 %0
  store double %add13.lcssa, double* %arrayidx17, align 8
  %indvars.iv.next5 = add nuw nsw i64 %indvars.iv4, 1
  %exitcond7 = icmp ne i64 %indvars.iv.next5, 50
  br i1 %exitcond7, label %for.cond5.preheader, label %for.inc21

for.inc21:                                        ; preds = %for.end
  ret void
}

attributes #0 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (trunk 283725) (llvm/trunk 283723)"}
