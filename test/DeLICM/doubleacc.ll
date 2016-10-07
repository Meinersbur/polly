; RUN: opt %loadPolly -polly-scops -analyze < %s
; RUN: opt %loadPolly -polly-codegen -S < %s
;
;    void foo(long n, float A[n]) {
;      for (long i = 0; i < n; i += 1) {
;        A[i] += 1;
;        A[i] += 1;
;      }
;    }

target datalayout = "e-m:w-i64:64-f80:128-n8:16:32:64-S128"

define void @foo(i32 %n, float* %A) #1 {
entry:
  %tmp = sext i32 %n to i64
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %indvars.iv = phi i64 [ %indvars.iv.next, %for.inc ], [ 0, %entry ]
  %cmp = icmp slt i64 %indvars.iv, %tmp
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %arrayidx = getelementptr inbounds float, float* %A, i64 %indvars.iv
  %tmp1 = load float, float* %arrayidx, align 4
  %add = fadd float %tmp1, 1.000000e+00
  store float %add, float* %arrayidx, align 4
  %arrayidx2 = getelementptr inbounds float, float* %A, i64 %indvars.iv
  %tmp2 = load float, float* %arrayidx2, align 4
  %add3 = fadd float %tmp2, 1.000000e+00
  store float %add3, float* %arrayidx2, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret void
}

attributes #1 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }




