; RUN: opt %loadPolly -polly-known -polly-delicm -analyze < %s

; Derived from test-suite/../../../../../mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/oggenc/oggenc.c

; ModuleID = '/tmp/bugpoint-6hr85lwk/bugpoint-reduced-simplified.bc'
source_filename = "bugpoint-output-78c5572.bc"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.vorbis_info_floor1.19.199.319.739.799.919.979.1159.1219.1279.1399.1459.1759.1879.1939.1999.2779.2839.2899.2959.4027.4195.4363.4475.4531.4568 = type { i32, [31 x i32], [16 x i32], [16 x i32], [16 x i32], [16 x [8 x i32]], i32, [65 x i32], float, float, float, float, float, i32 }

; Function Attrs: nounwind uwtable
define void @floor1_encode(i32* %post) local_unnamed_addr #0 {
entry:
  %0 = load %struct.vorbis_info_floor1.19.199.319.739.799.919.979.1159.1219.1279.1399.1459.1759.1879.1939.1999.2779.2839.2899.2959.4027.4195.4363.4475.4531.4568*, %struct.vorbis_info_floor1.19.199.319.739.799.919.979.1159.1219.1279.1399.1459.1759.1879.1939.1999.2779.2839.2899.2959.4027.4195.4363.4475.4531.4568** undef, align 8
  %1 = load i32, i32* undef, align 4
  %conv = sext i32 %1 to i64
  %mult = getelementptr inbounds %struct.vorbis_info_floor1.19.199.319.739.799.919.979.1159.1219.1279.1399.1459.1759.1879.1939.1999.2779.2839.2899.2959.4027.4195.4363.4475.4531.4568, %struct.vorbis_info_floor1.19.199.319.739.799.919.979.1159.1219.1279.1399.1459.1759.1879.1939.1999.2779.2839.2899.2959.4027.4195.4363.4475.4531.4568* %0, i64 0, i32 6
  br label %for.body

for.body:                                         ; preds = %sw.epilog, %entry
  %arrayidx = getelementptr inbounds i32, i32* %post, i64 0
  %2 = load i32, i32* %arrayidx, align 4
  switch i32 0, label %sw.epilog [
    i32 1, label %sw.bb
    i32 2, label %sw.bb4
    i32 3, label %sw.bb6
    i32 4, label %sw.bb7
  ]

sw.bb:                                            ; preds = %for.body
  br label %sw.epilog

sw.bb4:                                           ; preds = %for.body
  br label %sw.epilog

sw.bb6:                                           ; preds = %for.body
  br label %sw.epilog

sw.bb7:                                           ; preds = %for.body
  br label %sw.epilog

sw.epilog:                                        ; preds = %sw.bb7, %sw.bb6, %sw.bb4, %sw.bb, %for.body
  %and10 = and i32 %2, 32768
  store i32 undef, i32* %arrayidx, align 4
  %exitcond17 = icmp eq i64 0, %conv
  br i1 %exitcond17, label %for.end, label %for.body

for.end:                                          ; preds = %sw.epilog
  ret void
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (trunk 278052) (llvm/trunk 278053)"}
