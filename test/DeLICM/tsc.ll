; RUN: opt %loadPolly -polly-known -polly-delicm -analyze < %s

; Derived from test-suite/../../../../../mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/MultiSource/Benchmarks/TSVC/ControlFlow-flt/tsc.c

source_filename = "bugpoint-output-6a47ed9.bc"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%structA = type { [32000 x float], [3 x i32], [4 x i8], [32000 x float], [5 x i32], [12 x i8], [32000 x float], [7 x i32], [4 x i8], [32000 x float], [11 x i32], [4 x i8], [32000 x float], [13 x i32], [12 x i8], [256 x [256 x float]], [17 x i32], [12 x i8], [256 x [256 x float]], [19 x i32], [4 x i8], [256 x [256 x float]], [23 x i32], [4 x i8], [256 x [256 x float]] }

@global_data = external global %structA, align 16

; Function Attrs: nounwind uwtable
define void @init()  {
entry:
  br label %for.body28.i943

for.body28.i943:                                  ; preds = %for.body28.i943, %entry
  %indvars.iv1038 = phi i64 [ %indvars.iv.next1039.9, %for.body28.i943 ], [ 0, %entry ]
  %indvars.iv.next1039.3 = add nsw i64 %indvars.iv1038, 4
  %arrayidx30.i941.4 = getelementptr inbounds %structA, %structA* @global_data, i64 0, i32 0, i64 %indvars.iv.next1039.3
  store float 1.000000e+00, float* %arrayidx30.i941.4, align 8
  %indvars.iv.next1039.4 = add nsw i64 %indvars.iv1038, 5
  %arrayidx30.i941.5 = getelementptr inbounds %structA, %structA* @global_data, i64 0, i32 0, i64 %indvars.iv.next1039.4
  store float 1.000000e+00, float* %arrayidx30.i941.5, align 4
  %indvars.iv.next1039.5 = add nsw i64 %indvars.iv1038, 6
  %arrayidx30.i941.6 = getelementptr inbounds %structA, %structA* @global_data, i64 0, i32 0, i64 %indvars.iv.next1039.5
  store float 1.000000e+00, float* %arrayidx30.i941.6, align 8
  %indvars.iv.next1039.6 = add nsw i64 %indvars.iv1038, 7
  %arrayidx30.i941.7 = getelementptr inbounds %structA, %structA* @global_data, i64 0, i32 0, i64 %indvars.iv.next1039.6
  store float 1.000000e+00, float* %arrayidx30.i941.7, align 4
  %indvars.iv.next1039.7 = add nsw i64 %indvars.iv1038, 8
  %arrayidx30.i941.8 = getelementptr inbounds %structA, %structA* @global_data, i64 0, i32 0, i64 %indvars.iv.next1039.7
  store float 1.000000e+00, float* %arrayidx30.i941.8, align 8
  %indvars.iv.next1039.8 = add nsw i64 %indvars.iv1038, 9
  %arrayidx30.i941.9 = getelementptr inbounds %structA, %structA* @global_data, i64 0, i32 0, i64 %indvars.iv.next1039.8

  store float 1.000000e+00, float* %arrayidx30.i941.9, align 4
  %indvars.iv.next1039.9 = add nsw i64 %indvars.iv1038, 10
  %exitcond1040.9 = icmp eq i64 %indvars.iv.next1039.9, 32000
  br i1 %exitcond1040.9, label %for.body.i935, label %for.body28.i943

for.body.i935:                                    ; preds = %for.body28.i943
  %arrayidx.i934 = getelementptr inbounds %structA, %structA* @global_data, i64 0, i32 3, i64 0
  store float undef, float* %arrayidx.i934, align 8
  store float -1.000000e+00, float* getelementptr inbounds (%structA, %structA* @global_data, i64 0, i32 0, i64 31999), align 4
  br label %if.end1110

if.end1110:                                       ; preds = %for.body.i935
  ret void
}
