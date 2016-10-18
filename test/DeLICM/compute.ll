; RUN: opt %loadPolly -basicaa -scoped-noalias -tbaa -polly-delicm -analyze < %s

; Derived from test-suite/../../../../../mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/MultiSource/Benchmarks/Olden/power/compute.c

; ModuleID = '/tmp/bugpoint-ms_vln77/bugpoint-reduced-simplified.bc'
source_filename = "bugpoint-output-a8d50b5.bc"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define void @make_orthogonal(double* %v_mod) #0 {
entry:
  br label %for.body

for.cond3.preheader:                              ; preds = %for.body
  br label %for.body5

for.body:                                         ; preds = %for.body, %entry
  %indvars.iv4 = phi i64 [ %indvars.iv.next5, %for.body ], [ 0, %entry ]
  %indvars.iv.next5 = add nuw nsw i64 %indvars.iv4, 1
  br i1 false, label %for.body, label %for.cond3.preheader

for.body5:                                        ; preds = %for.body5, %for.cond3.preheader
  %indvars.iv1 = phi i64 [ %indvars.iv.next2, %for.body5 ], [ 0, %for.cond3.preheader ]
  %length.03 = phi double [ 0.000000e+00, %for.cond3.preheader ], [ undef, %for.body5 ]
  %arrayidx10 = getelementptr inbounds double, double* %v_mod, i64 %indvars.iv1
  store double undef, double* %arrayidx10, align 8
  %indvars.iv.next2 = add nuw nsw i64 %indvars.iv1, 1
  %exitcond3 = icmp ne i64 %indvars.iv.next2, 2
  br i1 %exitcond3, label %for.body5, label %for.end19

for.end19:                                        ; preds = %for.body5
  unreachable
}

attributes #0 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (trunk 283725) (llvm/trunk 283723)"}
