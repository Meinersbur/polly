; RUN: opt %loadPolly -polly-delicm -analyze < %s

; Derived from test-suite/../../../../../mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/JM/lencod/block.c

; ModuleID = '/tmp/bugpoint-6hqpl5e0/bugpoint-reduced-simplified.bc'
source_filename = "bugpoint-output-6a61b2a.bc"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: norecurse nounwind uwtable
define void @dct_luma_sp2(i32* nocapture %coeff_cost) local_unnamed_addr #0 {
entry:
  br label %for.body186

for.body186:                                      ; preds = %if.end252, %entry
  br label %if.end

if.end:                                           ; preds = %for.body186
  br label %if.then233

if.then233:                                       ; preds = %if.end
  %0 = load i32, i32* %coeff_cost, align 4
  br i1 false, label %if.end245, label %if.else238

if.else238:                                       ; preds = %if.then233
  br label %if.end245

if.end245:                                        ; preds = %if.else238, %if.then233
  %storemerge = add nsw i32 undef, %0
  store i32 %storemerge, i32* %coeff_cost, align 4
  br label %if.end252

if.end252:                                        ; preds = %if.end245
  br i1 undef, label %for.end274, label %for.body186

for.end274:                                       ; preds = %if.end252
  ret void
}

attributes #0 = { norecurse nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (trunk 278052) (llvm/trunk 278053)"}
