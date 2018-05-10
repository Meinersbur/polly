; ModuleID = 'bugpoint-reduced-simplified.bc'
source_filename = "bugpoint-output-9d72c1e.bc"
target datalayout = "e-m:e-i8:8:32-i16:16:32-i64:64-i128:128-n32:64-S128"
target triple = "aarch64--linux-android"

; Function Attrs: nounwind
define dso_local fastcc void @write_component_probs() unnamed_addr #0 {
entry:
  %bit_ct = alloca [10 x [2 x i32]], align 4
  br label %do.body

do.body:                                          ; preds = %do.body, %entry
  %indvars.iv = phi i64 [ %indvars.iv.next, %do.body ], [ 2, %entry ]
  %shr.8 = lshr i64 %indvars.iv, 1
  %and.8 = and i64 %shr.8, 1
  %arrayidx30.8 = getelementptr inbounds [10 x [2 x i32]], [10 x [2 x i32]]* %bit_ct, i64 0, i64 1, i64 %and.8
  %0 = load i32, i32* %arrayidx30.8, align 4, !tbaa !1
  %add31.8 = add i32 %0, undef
  store i32 %add31.8, i32* %arrayidx30.8, align 4, !tbaa !1
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1
  %exitcond = icmp eq i64 %indvars.iv.next, 14
  br i1 %exitcond, label %do.end35, label %do.body

do.end35:                                         ; preds = %do.body
  ret void
}

attributes #0 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="cortex-a53" "target-features"="+crc,+crypto,+fp-armv8,+neon" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 7.0.0 (trunk 329667)"}
!1 = !{!2, !2, i64 0}
!2 = !{!"int", !3, i64 0}
!3 = !{!"omnipotent char", !4, i64 0}
!4 = !{!"Simple C/C++ TBAA"}
