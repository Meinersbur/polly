; RUN: opt %loadPolly -basicaa -scoped-noalias -tbaa -polly-delicm -analyze < %s

; Derived from test-suite/../../../../../mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/medley/reg_detect/reg_detect.c

; ModuleID = '/tmp/bugpoint-7x143zjs/bugpoint-reduced-simplified.bc'
source_filename = "bugpoint-output-319da19.bc"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define void @kernel_reg_detect(i32 %niter, i32 %maxgrid, i32 %length, [6 x i32]* %mean, [6 x i32]* %path, [6 x [64 x i32]]* %diff, [6 x [64 x i32]]* %sum_diff) #0 {
entry:
  br label %for.cond1.preheader

for.cond1.preheader:                              ; preds = %for.inc126, %entry
  %t.020 = phi i32 [ 0, %entry ], [ %inc130, %for.inc126 ]
  br label %for.cond4.preheader

for.cond4.preheader:                              ; preds = %for.cond8.for.inc20_crit_edge, %for.cond1.preheader
  %indvars.iv7 = phi i64 [ %indvars.iv.next8, %for.cond8.for.inc20_crit_edge ], [ 0, %for.cond1.preheader ]
  br label %for.body11

for.body11:                                       ; preds = %for.body11, %for.cond4.preheader
  %indvars.iv = phi i64 [ %indvars.iv.next, %for.body11 ], [ 0, %for.cond4.preheader ]
  %arrayidx19 = getelementptr inbounds [6 x [64 x i32]], [6 x [64 x i32]]* %diff, i64 %indvars.iv7, i64 %indvars.iv7, i64 %indvars.iv
  store i32 0, i32* %arrayidx19, align 4
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1
  %wide.trip.count = zext i32 %length to i64
  %exitcond = icmp ne i64 %indvars.iv.next, %wide.trip.count
  br i1 %exitcond, label %for.body11, label %for.cond8.for.inc20_crit_edge

for.cond8.for.inc20_crit_edge:                    ; preds = %for.body11
  %indvars.iv.next8 = add nuw nsw i64 %indvars.iv7, 1
  %wide.trip.count9 = zext i32 %maxgrid to i64
  %exitcond10 = icmp ne i64 %indvars.iv.next8, %wide.trip.count9
  br i1 %exitcond10, label %for.cond4.preheader, label %for.body33

for.body33:                                       ; preds = %for.end69, %for.cond8.for.inc20_crit_edge
  %indvars.iv18 = phi i64 [ %indvars.iv.next19, %for.end69 ], [ 0, %for.cond8.for.inc20_crit_edge ]
  br label %for.body47

for.body47:                                       ; preds = %for.body47, %for.body33
  %indvars.iv11 = phi i64 [ %indvars.iv.next12, %for.body47 ], [ 1, %for.body33 ]
  %arrayidx60 = getelementptr inbounds [6 x [64 x i32]], [6 x [64 x i32]]* %diff, i64 0, i64 %indvars.iv18, i64 %indvars.iv11
  %0 = load i32, i32* %arrayidx60, align 4
  %arrayidx66 = getelementptr inbounds [6 x [64 x i32]], [6 x [64 x i32]]* %sum_diff, i64 0, i64 %indvars.iv18, i64 %indvars.iv11
  store i32 undef, i32* %arrayidx66, align 4
  %indvars.iv.next12 = add nuw nsw i64 %indvars.iv11, 1
  %wide.trip.count14 = zext i32 %length to i64
  %exitcond15 = icmp ne i64 %indvars.iv.next12, %wide.trip.count14
  br i1 %exitcond15, label %for.body47, label %for.end69

for.end69:                                        ; preds = %for.body47
  %arrayidx80 = getelementptr inbounds [6 x i32], [6 x i32]* %mean, i64 0, i64 %indvars.iv18
  store i32 undef, i32* %arrayidx80, align 4
  %indvars.iv.next19 = add nuw nsw i64 %indvars.iv18, 1
  %wide.trip.count20 = zext i32 %maxgrid to i64
  %exitcond21 = icmp ne i64 %indvars.iv.next19, %wide.trip.count20
  br i1 %exitcond21, label %for.body33, label %for.body90

for.body90:                                       ; preds = %for.body90, %for.end69
  %indvars.iv26 = phi i64 [ %indvars.iv.next27, %for.body90 ], [ 0, %for.end69 ]
  %arrayidx96 = getelementptr inbounds [6 x i32], [6 x i32]* %path, i64 0, i64 %indvars.iv26
  store i32 undef, i32* %arrayidx96, align 4
  %indvars.iv.next27 = add nuw nsw i64 %indvars.iv26, 1
  %wide.trip.count28 = zext i32 %maxgrid to i64
  %exitcond29 = icmp ne i64 %indvars.iv.next27, %wide.trip.count28
  br i1 %exitcond29, label %for.body90, label %for.body107

for.body107:                                      ; preds = %for.body107, %for.body90
  %indvars.iv32 = phi i64 [ %indvars.iv.next33, %for.body107 ], [ 1, %for.body90 ]
  %1 = add nsw i64 %indvars.iv32, -1
  %arrayidx113 = getelementptr inbounds [6 x i32], [6 x i32]* %path, i64 0, i64 %1
  %2 = load i32, i32* %arrayidx113, align 4
  %arrayidx122 = getelementptr inbounds [6 x i32], [6 x i32]* %path, i64 1, i64 %indvars.iv32
  store i32 undef, i32* %arrayidx122, align 4
  %indvars.iv.next33 = add nuw nsw i64 %indvars.iv32, 1
  %wide.trip.count35 = zext i32 %maxgrid to i64
  %exitcond36 = icmp ne i64 %indvars.iv.next33, %wide.trip.count35
  br i1 %exitcond36, label %for.body107, label %for.inc126

for.inc126:                                       ; preds = %for.body107
  %inc130 = add nuw nsw i32 %t.020, 1
  %exitcond42 = icmp ne i32 %inc130, %niter
  br i1 %exitcond42, label %for.cond1.preheader, label %for.cond.for.end131_crit_edge

for.cond.for.end131_crit_edge:                    ; preds = %for.inc126
  ret void
}

attributes #0 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (trunk 284019) (llvm/trunk 284022)"}
