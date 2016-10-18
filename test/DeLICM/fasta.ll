; RUN: opt %loadPolly -basicaa -scoped-noalias -tbaa -polly-delicm -analyze < %s

; Derived from test-suite/../../../../../mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/SingleSource/Benchmarks/BenchmarkGame/Large/fasta.c

; ModuleID = '/tmp/bugpoint-rup_b6vx/bugpoint-reduced-simplified.bc'
source_filename = "bugpoint-output-59d46bf.bc"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.aminoacid_t.0.3.6.15.30.36.42.54.105.126 = type { float, i8 }

; Function Attrs: inlinehint nounwind uwtable
define void @accumulate_probabilities(%struct.aminoacid_t.0.3.6.15.30.36.42.54.105.126* %genelist, i64 %len) #0 {
entry:
  br label %entry.split

entry.split:                                      ; preds = %entry
  br i1 false, label %for.end, label %for.body.lr.ph

for.body.lr.ph:                                   ; preds = %entry.split
  br label %for.body

for.body:                                         ; preds = %for.body, %for.body.lr.ph
  %i.03 = phi i64 [ 0, %for.body.lr.ph ], [ %inc, %for.body ]
  %cp.02 = phi float [ 0.000000e+00, %for.body.lr.ph ], [ undef, %for.body ]
  %p = getelementptr inbounds %struct.aminoacid_t.0.3.6.15.30.36.42.54.105.126, %struct.aminoacid_t.0.3.6.15.30.36.42.54.105.126* %genelist, i64 %i.03, i32 0
  store float undef, float* %p, align 4
  %inc = add nuw i64 %i.03, 1
  %exitcond = icmp ne i64 %inc, %len
  br i1 %exitcond, label %for.body, label %for.cond.for.end_crit_edge

for.cond.for.end_crit_edge:                       ; preds = %for.body
  br label %for.end

for.end:                                          ; preds = %for.cond.for.end_crit_edge, %entry.split
  ret void
}

attributes #0 = { inlinehint nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (trunk 283725) (llvm/trunk 283723)"}
