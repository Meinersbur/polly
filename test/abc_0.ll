; RUN: opt %loadPolly -polly-scops -S < %s
; Derived from C:\Users\Meinersbur\src\llvm\tools\polly\test\abc.c
; Original command: clang -mllvm -enable-newgvn -mllvm -polly -O3 abc.c -c

; ModuleID = 'C:\Users\MEINER~1\AppData\Local\Temp\reproduce-wfjbu5cx\bugpoint-reduced-simplified.bc'
source_filename = "C:\5CUsers\5CMeinersbur\5Csrc\5Cllvm\5Ctools\5Cpolly\5Ctest\5Cabc.c"
target datalayout = "e-m:w-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-windows-msvc19.0.24215"

@f = external dso_local local_unnamed_addr global i8, align 1

; Function Attrs: norecurse nounwind uwtable
define dso_local void @fn1() local_unnamed_addr #0 {
for.body:
  %cmp1.33 = icmp sgt i16 undef, 0
  %conv2.33 = zext i1 %cmp1.33 to i16
  %sub.33 = sub i16 undef, %conv2.33
  %cmp1.34 = icmp sgt i16 %sub.33, 0
  %conv2.34 = zext i1 %cmp1.34 to i16
  %sub.34 = sub i16 %sub.33, %conv2.34
  %cmp1.35 = icmp sgt i16 %sub.34, 0
  %conv2.35 = zext i1 %cmp1.35 to i16
  %sub.35 = sub i16 %sub.34, %conv2.35
  %sub.36 = sub i16 %sub.35, undef
  %cmp1.37 = icmp sgt i16 %sub.36, 0
  %conv2.37 = zext i1 %cmp1.37 to i16
  %sub.37 = sub i16 %sub.36, %conv2.37
  %cmp1.38 = icmp sgt i16 %sub.37, 0
  %conv2.38 = zext i1 %cmp1.38 to i16
  %sub.38 = sub i16 %sub.37, %conv2.38
  %cmp1.39 = icmp sgt i16 %sub.38, 0
  %conv2.39 = zext i1 %cmp1.39 to i16
  %sub.39 = sub i16 %sub.38, %conv2.39
  %cmp1.40 = icmp sgt i16 %sub.39, 0
  %conv2.40 = zext i1 %cmp1.40 to i16
  %sub.40 = sub i16 %sub.39, %conv2.40
  %tobool13 = icmp eq i16 %sub.40, 0
  br label %for.body9.lr.ph

for.body9.lr.ph:                                  ; preds = %for.body
  %f.promoted = load i8, i8* @f, align 1, !tbaa !1
  br i1 %tobool13, label %for.body9.lr.ph.split.us, label %for.body9.lr.ph.split

for.body9.lr.ph.split.us:                         ; preds = %for.body9.lr.ph
  br label %for.body9.us

for.body9.us:                                     ; preds = %for.body9.us, %for.body9.lr.ph.split.us
  %inc19.us = add nsw i32 0, 1
  br i1 false, label %for.cond7.for.cond21thread-pre-split_crit_edge.loopexit74, label %for.body9.us

for.body9.lr.ph.split:                            ; preds = %for.body9.lr.ph
  br label %for.body9.us29

for.body9.us29:                                   ; preds = %for.body9.us29, %for.body9.lr.ph.split
  %inc19.us36 = add nsw i32 0, 1
  br i1 false, label %for.cond7.for.cond21thread-pre-split_crit_edge.loopexit75, label %for.body9.us29

for.cond7.for.cond21thread-pre-split_crit_edge.loopexit74: ; preds = %for.body9.us
  br label %for.cond7.for.cond21thread-pre-split_crit_edge

for.cond7.for.cond21thread-pre-split_crit_edge.loopexit75: ; preds = %for.body9.us29
  br label %for.cond7.for.cond21thread-pre-split_crit_edge

for.cond7.for.cond21thread-pre-split_crit_edge:   ; preds = %for.cond7.for.cond21thread-pre-split_crit_edge.loopexit75, %for.cond7.for.cond21thread-pre-split_crit_edge.loopexit74
  store i8 0, i8* @f, align 1, !tbaa !1
  br label %for.cond21

for.cond21:                                       ; preds = %for.cond21, %for.cond7.for.cond21thread-pre-split_crit_edge
  br label %for.cond21
}

attributes #0 = { norecurse nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 7.0.0 (trunk 331768) (llvm/trunk 331769)"}
!1 = !{!2, !2, i64 0}
!2 = !{!"omnipotent char", !3, i64 0}
!3 = !{!"Simple C/C++ TBAA"}
