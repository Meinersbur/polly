; RUN: opt %loadPolly -basicaa -scoped-noalias -tbaa -polly-delicm -analyze < %s

; Derived from test-suite/../../../../../mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/SingleSource/Benchmarks/Misc-C++/stepanov_container.cpp

; ModuleID = '/tmp/bugpoint-h9oaz7fr/bugpoint-reduced-simplified.bc'
source_filename = "bugpoint-output-f608da4.bc"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define void @_Z10initializePdS_(double* %first, double* %last) #0 {
entry:
  br label %entry.split

entry.split:                                      ; preds = %entry
  br i1 false, label %while.end, label %while.body.lr.ph

while.body.lr.ph:                                 ; preds = %entry.split
  br label %while.body

while.body:                                       ; preds = %while.body, %while.body.lr.ph
  %value.03 = phi double [ 0.000000e+00, %while.body.lr.ph ], [ undef, %while.body ]
  %first.addr.02 = phi double* [ %first, %while.body.lr.ph ], [ %incdec.ptr, %while.body ]
  %incdec.ptr = getelementptr inbounds double, double* %first.addr.02, i64 1
  store double %value.03, double* %first.addr.02, align 8
  %cmp = icmp eq double* %incdec.ptr, %last
  br i1 %cmp, label %while.cond.while.end_crit_edge, label %while.body

while.cond.while.end_crit_edge:                   ; preds = %while.body
  br label %while.end

while.end:                                        ; preds = %while.cond.while.end_crit_edge, %entry.split
  ret void
}

attributes #0 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (trunk 283725) (llvm/trunk 283723)"}
