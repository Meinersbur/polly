; RUN: opt %loadPolly -basicaa -scoped-noalias -tbaa -polly-delicm -analyze < %s

; Derived from test-suite/../../../../../mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/ClamAV/libclamav_autoit.c

; ModuleID = '/tmp/bugpoint-ja1nfpyv/bugpoint-reduced-simplified.bc'
source_filename = "bugpoint-output-35be842.bc"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.MT.7.17.27.54.81.126.135.144.153.180.207.279.288.297.306.495.596 = type { [624 x i32], i32, i32* }

; Function Attrs: nounwind uwtable
define void @MT_getnext(%struct.MT.7.17.27.54.81.126.135.144.153.180.207.279.288.297.306.495.596* %MT) #0 {
entry:
  br label %for.body

for.cond20.preheader:                             ; preds = %for.body
  %0 = trunc i64 227 to i32
  %1 = zext i32 %0 to i64
  br label %for.body22

for.body:                                         ; preds = %for.body, %entry
  %indvars.iv1 = phi i64 [ %indvars.iv.next2, %for.body ], [ 0, %entry ]
  %indvars.iv.next2 = add nuw nsw i64 %indvars.iv1, 1
  br i1 false, label %for.body, label %for.cond20.preheader

for.body22:                                       ; preds = %for.body22, %for.cond20.preheader
  %indvars.iv = phi i64 [ %indvars.iv.next, %for.body22 ], [ %1, %for.cond20.preheader ]
  %2 = phi i32 [ undef, %for.cond20.preheader ], [ %5, %for.body22 ]
  %arrayidx24 = getelementptr inbounds %struct.MT.7.17.27.54.81.126.135.144.153.180.207.279.288.297.306.495.596, %struct.MT.7.17.27.54.81.126.135.144.153.180.207.279.288.297.306.495.596* %MT, i64 0, i32 0, i64 %indvars.iv
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1
  store i32 undef, i32* %arrayidx24, align 4
  %3 = trunc i64 %indvars.iv to i32
  %sub41 = add i32 %3, -226
  %idxprom42 = zext i32 %sub41 to i64
  %4 = getelementptr inbounds %struct.MT.7.17.27.54.81.126.135.144.153.180.207.279.288.297.306.495.596, %struct.MT.7.17.27.54.81.126.135.144.153.180.207.279.288.297.306.495.596* %MT, i64 0, i32 0, i64 %idxprom42
  %5 = load i32, i32* %4, align 4
  %exitcond = icmp ne i64 %indvars.iv.next, 623
  br i1 %exitcond, label %for.body22, label %for.cond20.for.end49_crit_edge

for.cond20.for.end49_crit_edge:                   ; preds = %for.body22
  ret void
}

attributes #0 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (trunk 283725) (llvm/trunk 283723)"}
