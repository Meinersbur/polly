; RUN: opt %loadPolly -basicaa -scoped-noalias -tbaa -polly-delicm -analyze < %s

; Derived from test-suite/../../../../../mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/oggenc/oggenc.c

; ModuleID = '/tmp/bugpoint-m4umgwu_/bugpoint-reduced-simplified.bc'
source_filename = "bugpoint-output-7ffe896.bc"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define void @local_book_besterror() #0 {
entry:
  %0 = load i64, i64* undef, align 8
  %conv = trunc i64 %0 to i32
  br label %for.body64

for.body64:                                       ; preds = %if.end92, %entry
  %bestf.011 = phi float [ 0.000000e+00, %entry ], [ %this.0.bestf.0, %if.end92 ]
  br label %for.body74

for.body74:                                       ; preds = %for.body74, %for.body64
  br i1 false, label %for.body74, label %for.cond71.for.end85_crit_edge

for.cond71.for.end85_crit_edge:                   ; preds = %for.body74
  %cmp88 = fcmp olt float undef, %bestf.011
  %this.0.bestf.0 = select i1 undef, float undef, float %bestf.011
  br label %if.end92

if.end92:                                         ; preds = %for.cond71.for.end85_crit_edge
  br i1 undef, label %for.body64, label %for.cond60.if.end96.loopexit_crit_edge

for.cond60.if.end96.loopexit_crit_edge:           ; preds = %if.end92
  ret void
}

attributes #0 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (trunk 283725) (llvm/trunk 283723)"}
