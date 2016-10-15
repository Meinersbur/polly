; RUN: opt %loadPolly -basicaa -scoped-noalias -tbaa -polly-delicm -analyze < %s

; Derived from test-suite/../../../../../mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/SingleSource/UnitTests/Vectorizer/gcc-loops.cpp

; ModuleID = '/tmp/bugpoint-kr6hts1h/bugpoint-reduced-simplified.bc'
source_filename = "bugpoint-output-b1774e2.bc"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define void @_Z17init_memory_floatPfS_(float* %start, float* %end) #0 {
entry:
  br label %entry.split

entry.split:                                      ; preds = %entry
  br i1 false, label %while.end, label %while.body.lr.ph

while.body.lr.ph:                                 ; preds = %entry.split
  br label %while.body

while.body:                                       ; preds = %while.body, %while.body.lr.ph
  %state.03 = phi float [ 1.000000e+00, %while.body.lr.ph ], [ undef, %while.body ]
  %start.addr.02 = phi float* [ %start, %while.body.lr.ph ], [ %incdec.ptr, %while.body ]
  store float undef, float* %start.addr.02, align 4
  %incdec.ptr = getelementptr inbounds float, float* %start.addr.02, i64 1
  %cmp = icmp eq float* %incdec.ptr, %end
  br i1 %cmp, label %while.cond.while.end_crit_edge, label %while.body

while.cond.while.end_crit_edge:                   ; preds = %while.body
  br label %while.end

while.end:                                        ; preds = %while.cond.while.end_crit_edge, %entry.split
  ret void
}

attributes #0 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (trunk 283725) (llvm/trunk 283723)"}
