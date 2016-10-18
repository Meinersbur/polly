; RUN: opt %loadPolly -polly-delicm -polly-ast -analyze < %s | FileCheck %s
; RUN: opt %loadPolly -polly-flatten-schedule -polly-delicm -polly-ast -analyze < %s | FileCheck %s --check-prefix=FLAT

; RUN: opt %loadPolly -polly-delicm -polly-codegen -S < %s | FileCheck %s --check-prefix=PREIR
; RUN: opt %loadPolly -polly-delicm -polly-opt-isl -polly-codegen -S < %s | FileCheck %s --check-prefix=IR
; XFAIL: *
; ModuleID = '/mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/linear-algebra/kernels/gemm/gemm.c'
source_filename = "/mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/linear-algebra/kernels/gemm/gemm.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }

@polybench_papi_counters_threadid = local_unnamed_addr global i32 0, align 4
@polybench_program_total_flops = local_unnamed_addr global double 0.000000e+00, align 8
@polybench_t_start = common local_unnamed_addr global double 0.000000e+00, align 8
@polybench_t_end = common local_unnamed_addr global double 0.000000e+00, align 8
@.str = private unnamed_addr constant [7 x i8] c"%0.6f\0A\00", align 1
@polybench_c_start = common local_unnamed_addr global i64 0, align 8
@polybench_c_end = common local_unnamed_addr global i64 0, align 8
@stderr = external local_unnamed_addr global %struct._IO_FILE*, align 8
@.str.1 = private unnamed_addr constant [51 x i8] c"[PolyBench] posix_memalign: cannot allocate memory\00", align 1

; Function Attrs: norecurse nounwind readnone uwtable
define void @polybench_flush_cache() local_unnamed_addr #0 {
entry:
  br label %entry.split

entry.split:                                      ; preds = %entry
  ret void
}

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start(i64, i8* nocapture) #1

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) local_unnamed_addr #2

; Function Attrs: nounwind
declare void @free(i8* nocapture) local_unnamed_addr #2

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.end(i64, i8* nocapture) #1

; Function Attrs: norecurse nounwind readnone uwtable
define void @polybench_prepare_instruments() local_unnamed_addr #0 {
entry:
  br label %entry.split

entry.split:                                      ; preds = %entry
  ret void
}

; Function Attrs: norecurse nounwind uwtable
define void @polybench_timer_start() local_unnamed_addr #3 {
entry:
  br label %entry.split

entry.split:                                      ; preds = %entry
  store double 0.000000e+00, double* @polybench_t_start, align 8, !tbaa !1
  ret void
}

; Function Attrs: norecurse nounwind uwtable
define void @polybench_timer_stop() local_unnamed_addr #3 {
entry:
  br label %entry.split

entry.split:                                      ; preds = %entry
  store double 0.000000e+00, double* @polybench_t_end, align 8, !tbaa !1
  ret void
}

; Function Attrs: nounwind uwtable
define void @polybench_timer_print() local_unnamed_addr #4 {
entry:
  br label %entry.split

entry.split:                                      ; preds = %entry
  %0 = load double, double* @polybench_t_end, align 8, !tbaa !1
  %1 = load double, double* @polybench_t_start, align 8, !tbaa !1
  %sub = fsub double %0, %1
  %call = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i64 0, i64 0), double %sub)
  ret void
}

; Function Attrs: nounwind
declare i32 @printf(i8* nocapture readonly, ...) local_unnamed_addr #2

; Function Attrs: nounwind uwtable
define i8* @polybench_alloc_data(i64 %n, i32 %elt_size) local_unnamed_addr #4 {
entry:
  %new.i = alloca i8*, align 8
  br label %entry.split

entry.split:                                      ; preds = %entry
  %conv = sext i32 %elt_size to i64
  %mul = mul i64 %conv, %n
  %0 = bitcast i8** %new.i to i8*
  call void @llvm.lifetime.start(i64 8, i8* %0) #6
  store i8* null, i8** %new.i, align 8, !tbaa !5
  %call.i = call i32 @posix_memalign(i8** nonnull %new.i, i64 32, i64 %mul) #6
  %1 = load i8*, i8** %new.i, align 8, !tbaa !5
  %tobool.i = icmp eq i8* %1, null
  %tobool1.i = icmp ne i32 %call.i, 0
  %or.cond.i = or i1 %tobool1.i, %tobool.i
  br i1 %or.cond.i, label %if.then.i, label %xmalloc.exit

if.then.i:                                        ; preds = %entry.split
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !5
  %3 = call i64 @fwrite(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.1, i64 0, i64 0), i64 50, i64 1, %struct._IO_FILE* %2) #7
  call void @exit(i32 1) #8
  unreachable

xmalloc.exit:                                     ; preds = %entry.split
  call void @llvm.lifetime.end(i64 8, i8* %0) #6
  ret i8* %1
}

; Function Attrs: nounwind uwtable
define i32 @main(i32 %argc, i8** nocapture readnone %argv) local_unnamed_addr #4 {
entry:
  %new.i.i34 = alloca i8*, align 8
  %new.i.i27 = alloca i8*, align 8
  %new.i.i = alloca i8*, align 8
  br label %entry.split

entry.split:                                      ; preds = %entry
  %0 = bitcast i8** %new.i.i to i8*
  call void @llvm.lifetime.start(i64 8, i8* %0) #6
  store i8* null, i8** %new.i.i, align 8, !tbaa !5
  %call.i.i = call i32 @posix_memalign(i8** nonnull %new.i.i, i64 32, i64 8388608) #6
  %1 = load i8*, i8** %new.i.i, align 8, !tbaa !5
  %tobool.i.i = icmp eq i8* %1, null
  %tobool1.i.i = icmp ne i32 %call.i.i, 0
  %or.cond.i.i = or i1 %tobool1.i.i, %tobool.i.i
  br i1 %or.cond.i.i, label %if.then.i.i, label %polybench_alloc_data.exit

if.then.i.i:                                      ; preds = %entry.split
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !5
  %3 = call i64 @fwrite(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.1, i64 0, i64 0), i64 50, i64 1, %struct._IO_FILE* %2) #7
  call void @exit(i32 1) #8
  unreachable

polybench_alloc_data.exit:                        ; preds = %entry.split
  call void @llvm.lifetime.end(i64 8, i8* %0) #6
  %4 = bitcast i8** %new.i.i27 to i8*
  call void @llvm.lifetime.start(i64 8, i8* %4) #6
  store i8* null, i8** %new.i.i27, align 8, !tbaa !5
  %call.i.i28 = call i32 @posix_memalign(i8** nonnull %new.i.i27, i64 32, i64 8388608) #6
  %5 = load i8*, i8** %new.i.i27, align 8, !tbaa !5
  %tobool.i.i29 = icmp eq i8* %5, null
  %tobool1.i.i30 = icmp ne i32 %call.i.i28, 0
  %or.cond.i.i31 = or i1 %tobool1.i.i30, %tobool.i.i29
  br i1 %or.cond.i.i31, label %if.then.i.i32, label %polybench_alloc_data.exit33

if.then.i.i32:                                    ; preds = %polybench_alloc_data.exit
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !5
  %7 = call i64 @fwrite(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.1, i64 0, i64 0), i64 50, i64 1, %struct._IO_FILE* %6) #7
  call void @exit(i32 1) #8
  unreachable

polybench_alloc_data.exit33:                      ; preds = %polybench_alloc_data.exit
  call void @llvm.lifetime.end(i64 8, i8* %4) #6
  %8 = bitcast i8** %new.i.i34 to i8*
  call void @llvm.lifetime.start(i64 8, i8* %8) #6
  store i8* null, i8** %new.i.i34, align 8, !tbaa !5
  %call.i.i35 = call i32 @posix_memalign(i8** nonnull %new.i.i34, i64 32, i64 8388608) #6
  %9 = load i8*, i8** %new.i.i34, align 8, !tbaa !5
  %tobool.i.i36 = icmp eq i8* %9, null
  %tobool1.i.i37 = icmp ne i32 %call.i.i35, 0
  %or.cond.i.i38 = or i1 %tobool1.i.i37, %tobool.i.i36
  br i1 %or.cond.i.i38, label %if.then.i.i39, label %polybench_alloc_data.exit40

if.then.i.i39:                                    ; preds = %polybench_alloc_data.exit33
  %10 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !5
  %11 = call i64 @fwrite(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.1, i64 0, i64 0), i64 50, i64 1, %struct._IO_FILE* %10) #7
  call void @exit(i32 1) #8
  unreachable

polybench_alloc_data.exit40:                      ; preds = %polybench_alloc_data.exit33
  call void @llvm.lifetime.end(i64 8, i8* %8) #6
  %arraydecay = bitcast i8* %1 to [1024 x double]*
  %arraydecay3 = bitcast i8* %5 to [1024 x double]*
  br label %for.cond1.preheader.i

for.cond1.preheader.i:                            ; preds = %for.inc8.i, %polybench_alloc_data.exit40
  %indvars.iv19.i = phi i64 [ 0, %polybench_alloc_data.exit40 ], [ %indvars.iv.next20.i, %for.inc8.i ]
  %12 = trunc i64 %indvars.iv19.i to i32
  %conv.i = sitofp i32 %12 to double
  br label %for.body3.i

for.body3.i:                                      ; preds = %for.body3.i, %for.cond1.preheader.i
  %indvars.iv16.i = phi i64 [ 0, %for.cond1.preheader.i ], [ %indvars.iv.next17.i, %for.body3.i ]
  %13 = trunc i64 %indvars.iv16.i to i32
  %conv4.i = sitofp i32 %13 to double
  %mul.i = fmul double %conv.i, %conv4.i
  %div.i = fmul double %mul.i, 9.765625e-04
  %arrayidx7.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay, i64 %indvars.iv19.i, i64 %indvars.iv16.i
  store double %div.i, double* %arrayidx7.i, align 8, !tbaa !1
  %indvars.iv.next17.i = add nuw nsw i64 %indvars.iv16.i, 1
  %exitcond18.i = icmp eq i64 %indvars.iv.next17.i, 1024
  br i1 %exitcond18.i, label %for.inc8.i, label %for.body3.i

for.inc8.i:                                       ; preds = %for.body3.i
  %indvars.iv.next20.i = add nuw nsw i64 %indvars.iv19.i, 1
  %exitcond21.i = icmp eq i64 %indvars.iv.next20.i, 1024
  br i1 %exitcond21.i, label %for.cond15.preheader.i.preheader, label %for.cond1.preheader.i

for.cond15.preheader.i.preheader:                 ; preds = %for.inc8.i
  %arraydecay4 = bitcast i8* %9 to [1024 x double]*
  br label %for.cond15.preheader.i

for.cond15.preheader.i:                           ; preds = %for.cond15.preheader.i.preheader, %for.inc31.i
  %indvars.iv13.i = phi i64 [ %indvars.iv.next14.i, %for.inc31.i ], [ 0, %for.cond15.preheader.i.preheader ]
  %14 = trunc i64 %indvars.iv13.i to i32
  %conv19.i = sitofp i32 %14 to double
  br label %for.body18.i

for.body18.i:                                     ; preds = %for.body18.i, %for.cond15.preheader.i
  %indvars.iv10.i = phi i64 [ 0, %for.cond15.preheader.i ], [ %indvars.iv.next11.i, %for.body18.i ]
  %15 = trunc i64 %indvars.iv10.i to i32
  %conv20.i = sitofp i32 %15 to double
  %mul21.i = fmul double %conv19.i, %conv20.i
  %div23.i = fmul double %mul21.i, 9.765625e-04
  %arrayidx27.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay3, i64 %indvars.iv13.i, i64 %indvars.iv10.i
  store double %div23.i, double* %arrayidx27.i, align 8, !tbaa !1
  %indvars.iv.next11.i = add nuw nsw i64 %indvars.iv10.i, 1
  %exitcond12.i = icmp eq i64 %indvars.iv.next11.i, 1024
  br i1 %exitcond12.i, label %for.inc31.i, label %for.body18.i

for.inc31.i:                                      ; preds = %for.body18.i
  %indvars.iv.next14.i = add nuw nsw i64 %indvars.iv13.i, 1
  %exitcond15.i = icmp eq i64 %indvars.iv.next14.i, 1024
  br i1 %exitcond15.i, label %for.cond38.preheader.i, label %for.cond15.preheader.i

for.cond38.preheader.i:                           ; preds = %for.inc31.i, %for.inc54.i
  %indvars.iv7.i = phi i64 [ %indvars.iv.next8.i, %for.inc54.i ], [ 0, %for.inc31.i ]
  %16 = trunc i64 %indvars.iv7.i to i32
  %conv42.i = sitofp i32 %16 to double
  br label %for.body41.i

for.body41.i:                                     ; preds = %for.body41.i, %for.cond38.preheader.i
  %indvars.iv.i = phi i64 [ 0, %for.cond38.preheader.i ], [ %indvars.iv.next.i, %for.body41.i ]
  %17 = trunc i64 %indvars.iv.i to i32
  %conv43.i = sitofp i32 %17 to double
  %mul44.i = fmul double %conv42.i, %conv43.i
  %div46.i = fmul double %mul44.i, 9.765625e-04
  %arrayidx50.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay4, i64 %indvars.iv7.i, i64 %indvars.iv.i
  store double %div46.i, double* %arrayidx50.i, align 8, !tbaa !1
  %indvars.iv.next.i = add nuw nsw i64 %indvars.iv.i, 1
  %exitcond.i = icmp eq i64 %indvars.iv.next.i, 1024
  br i1 %exitcond.i, label %for.inc54.i, label %for.body41.i

for.inc54.i:                                      ; preds = %for.body41.i
  %indvars.iv.next8.i = add nuw nsw i64 %indvars.iv7.i, 1
  %exitcond9.i = icmp eq i64 %indvars.iv.next8.i, 1024
  br i1 %exitcond9.i, label %for.cond1.preheader.i42, label %for.cond38.preheader.i

for.cond1.preheader.i42:                          ; preds = %for.inc54.i, %for.inc26.i
  %indvars.iv7.i41 = phi i64 [ %indvars.iv.next8.i48, %for.inc26.i ], [ 0, %for.inc54.i ]
  br label %for.body3.i44

for.body3.i44:                                    ; preds = %for.inc23.i, %for.cond1.preheader.i42
  %indvars.iv4.i = phi i64 [ 0, %for.cond1.preheader.i42 ], [ %indvars.iv.next5.i, %for.inc23.i ]
  %arrayidx5.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay, i64 %indvars.iv7.i41, i64 %indvars.iv4.i
  %18 = load double, double* %arrayidx5.i, align 8, !tbaa !1
  %mul.i43 = fmul double %18, 2.123000e+03
  store double %mul.i43, double* %arrayidx5.i, align 8, !tbaa !1
  br label %for.body8.i

for.body8.i:                                      ; preds = %for.body8.i, %for.body3.i44
  %19 = phi double [ %mul.i43, %for.body3.i44 ], [ %add.i, %for.body8.i ]
  %indvars.iv.i45 = phi i64 [ 0, %for.body3.i44 ], [ %indvars.iv.next.i46, %for.body8.i ]
  %arrayidx12.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay3, i64 %indvars.iv7.i41, i64 %indvars.iv.i45
  %20 = load double, double* %arrayidx12.i, align 8, !tbaa !1
  %mul13.i = fmul double %20, 3.241200e+04
  %arrayidx17.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay4, i64 %indvars.iv.i45, i64 %indvars.iv4.i
  %21 = load double, double* %arrayidx17.i, align 8, !tbaa !1
  %mul18.i = fmul double %mul13.i, %21
  %add.i = fadd double %19, %mul18.i
  store double %add.i, double* %arrayidx5.i, align 8, !tbaa !1
  %indvars.iv.next.i46 = add nuw nsw i64 %indvars.iv.i45, 1
  %exitcond.i47 = icmp eq i64 %indvars.iv.next.i46, 1024
  br i1 %exitcond.i47, label %for.inc23.i, label %for.body8.i

for.inc23.i:                                      ; preds = %for.body8.i
  %indvars.iv.next5.i = add nuw nsw i64 %indvars.iv4.i, 1
  %exitcond6.i = icmp eq i64 %indvars.iv.next5.i, 1024
  br i1 %exitcond6.i, label %for.inc26.i, label %for.body3.i44

for.inc26.i:                                      ; preds = %for.inc23.i
  %indvars.iv.next8.i48 = add nuw nsw i64 %indvars.iv7.i41, 1
  %exitcond9.i49 = icmp eq i64 %indvars.iv.next8.i48, 1024
  br i1 %exitcond9.i49, label %kernel_gemm.exit, label %for.cond1.preheader.i42

kernel_gemm.exit:                                 ; preds = %for.inc26.i
  %call.i = call noalias i8* @malloc(i64 16385) #6
  %arrayidx.i = getelementptr inbounds i8, i8* %call.i, i64 16384
  store i8 0, i8* %arrayidx.i, align 1, !tbaa !7
  br label %for.cond3.preheader.i

for.cond3.preheader.i:                            ; preds = %for.end.i, %kernel_gemm.exit
  %indvars.iv4.i50 = phi i64 [ 0, %kernel_gemm.exit ], [ %indvars.iv.next5.i54, %for.end.i ]
  br label %for.body6.i

for.body6.i:                                      ; preds = %for.body6.i, %for.cond3.preheader.i
  %indvars.iv.i51 = phi i64 [ 0, %for.cond3.preheader.i ], [ %indvars.iv.next.i52, %for.body6.i ]
  %arrayidx10.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay, i64 %indvars.iv4.i50, i64 %indvars.iv.i51
  %22 = bitcast double* %arrayidx10.i to i64*
  %23 = load i64, i64* %22, align 8, !tbaa !1
  %24 = shl nsw i64 %indvars.iv.i51, 4
  %block.sroa.0.0.extract.trunc138.i.i = trunc i64 %23 to i8
  %and.i.i = and i8 %block.sroa.0.0.extract.trunc138.i.i, 15
  %add.i.i = or i8 %and.i.i, 48
  %add.ptr.i.i = getelementptr inbounds i8, i8* %call.i, i64 %24
  store i8 %add.i.i, i8* %add.ptr.i.i, align 1, !tbaa !7
  %add.ptr10.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 1
  store i8 %add.i.i, i8* %add.ptr10.i.i, align 1, !tbaa !7
  %block.sroa.0.1.extract.shift.i.i = lshr i64 %23, 8
  %conv13195.i.i = trunc i64 %block.sroa.0.1.extract.shift.i.i to i8
  %and14.i.i = and i8 %conv13195.i.i, 15
  %add15.i.i = or i8 %and14.i.i, 48
  %add.ptr19.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 2
  store i8 %add15.i.i, i8* %add.ptr19.i.i, align 1, !tbaa !7
  %add.ptr28.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 3
  store i8 %add15.i.i, i8* %add.ptr28.i.i, align 1, !tbaa !7
  %block.sroa.0.2.extract.shift.i.i = lshr i64 %23, 16
  %conv31201.i.i = trunc i64 %block.sroa.0.2.extract.shift.i.i to i8
  %and32.i.i = and i8 %conv31201.i.i, 15
  %add33.i.i = or i8 %and32.i.i, 48
  %add.ptr37.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 4
  store i8 %add33.i.i, i8* %add.ptr37.i.i, align 1, !tbaa !7
  %add.ptr46.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 5
  store i8 %add33.i.i, i8* %add.ptr46.i.i, align 1, !tbaa !7
  %.tr.i.i = trunc i64 %23 to i32
  %sext204207.i.i = lshr i32 %.tr.i.i, 24
  %and50.i.i = and i32 %sext204207.i.i, 15
  %add51.i.i = or i32 %and50.i.i, 48
  %conv52.i.i = trunc i32 %add51.i.i to i8
  %add.ptr55.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 6
  store i8 %conv52.i.i, i8* %add.ptr55.i.i, align 1, !tbaa !7
  %add.ptr64.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 7
  store i8 %conv52.i.i, i8* %add.ptr64.i.i, align 1, !tbaa !7
  %block.sroa.0.4.extract.shift.i.i = lshr i64 %23, 32
  %conv67211.i.i = trunc i64 %block.sroa.0.4.extract.shift.i.i to i8
  %and68.i.i = and i8 %conv67211.i.i, 15
  %add69.i.i = or i8 %and68.i.i, 48
  %add.ptr73.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 8
  store i8 %add69.i.i, i8* %add.ptr73.i.i, align 1, !tbaa !7
  %add.ptr82.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 9
  store i8 %add69.i.i, i8* %add.ptr82.i.i, align 1, !tbaa !7
  %block.sroa.0.5.extract.shift.i.i = lshr i64 %23, 40
  %conv85217.i.i = trunc i64 %block.sroa.0.5.extract.shift.i.i to i8
  %and86.i.i = and i8 %conv85217.i.i, 15
  %add87.i.i = or i8 %and86.i.i, 48
  %add.ptr91.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 10
  store i8 %add87.i.i, i8* %add.ptr91.i.i, align 1, !tbaa !7
  %add.ptr100.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 11
  store i8 %add87.i.i, i8* %add.ptr100.i.i, align 1, !tbaa !7
  %block.sroa.0.6.extract.shift.i.i = lshr i64 %23, 48
  %conv103223.i.i = trunc i64 %block.sroa.0.6.extract.shift.i.i to i8
  %and104.i.i = and i8 %conv103223.i.i, 15
  %add105.i.i = or i8 %and104.i.i, 48
  %add.ptr109.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 12
  store i8 %add105.i.i, i8* %add.ptr109.i.i, align 1, !tbaa !7
  %add.ptr118.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 13
  store i8 %add105.i.i, i8* %add.ptr118.i.i, align 1, !tbaa !7
  %block.sroa.0.7.extract.shift.i.i = lshr i64 %23, 56
  %conv121229.i.i = trunc i64 %block.sroa.0.7.extract.shift.i.i to i8
  %and122.i.i = and i8 %conv121229.i.i, 15
  %add123.i.i = or i8 %and122.i.i, 48
  %add.ptr127.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 14
  store i8 %add123.i.i, i8* %add.ptr127.i.i, align 1, !tbaa !7
  %add.ptr136.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 15
  store i8 %add123.i.i, i8* %add.ptr136.i.i, align 1, !tbaa !7
  %indvars.iv.next.i52 = add nuw nsw i64 %indvars.iv.i51, 1
  %exitcond.i53 = icmp eq i64 %indvars.iv.next.i52, 1024
  br i1 %exitcond.i53, label %for.end.i, label %for.body6.i

for.end.i:                                        ; preds = %for.body6.i
  %25 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !5
  %call12.i = call i32 @fputs(i8* nonnull %call.i, %struct._IO_FILE* %25) #7
  %indvars.iv.next5.i54 = add nuw nsw i64 %indvars.iv4.i50, 1
  %exitcond6.i55 = icmp eq i64 %indvars.iv.next5.i54, 1024
  br i1 %exitcond6.i55, label %print_array.exit, label %for.cond3.preheader.i

print_array.exit:                                 ; preds = %for.end.i
  call void @free(i8* nonnull %call.i) #6
  call void @free(i8* nonnull %1) #6
  call void @free(i8* %5) #6
  call void @free(i8* %9) #6
  ret i32 0
}

; Function Attrs: nounwind
declare i32 @posix_memalign(i8**, i64, i64) local_unnamed_addr #2

; Function Attrs: nounwind
declare i32 @fprintf(%struct._IO_FILE* nocapture, i8* nocapture readonly, ...) local_unnamed_addr #2

; Function Attrs: noreturn nounwind
declare void @exit(i32) local_unnamed_addr #5

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) local_unnamed_addr #2

; Function Attrs: nounwind
declare i32 @fputs(i8* nocapture readonly, %struct._IO_FILE* nocapture) local_unnamed_addr #2

; Function Attrs: nounwind
declare i64 @fwrite(i8* nocapture, i64, i64, %struct._IO_FILE* nocapture) #6

attributes #0 = { norecurse nounwind readnone uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { norecurse nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }
attributes #7 = { cold nounwind }
attributes #8 = { noreturn nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (trunk 278052) (llvm/trunk 278053)"}
!1 = !{!2, !2, i64 0}
!2 = !{!"double", !3, i64 0}
!3 = !{!"omnipotent char", !4, i64 0}
!4 = !{!"Simple C/C++ TBAA"}
!5 = !{!6, !6, i64 0}
!6 = !{!"any pointer", !3, i64 0}
!7 = !{!3, !3, i64 0}


; CHECK:      Printing analysis 'Polly - DeLICM/DePRE' for region: 'entry => <Function Return>' in function 'polybench_flush_cache':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'entry => <Function Return>' in function 'polybench_flush_cache':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'entry => <Function Return>' in function 'polybench_prepare_instruments':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'entry => <Function Return>' in function 'polybench_prepare_instruments':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'entry => <Function Return>' in function 'polybench_timer_start':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'entry => <Function Return>' in function 'polybench_timer_start':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'entry => <Function Return>' in function 'polybench_timer_stop':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'entry => <Function Return>' in function 'polybench_timer_stop':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'entry => <Function Return>' in function 'polybench_timer_print':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'entry => <Function Return>' in function 'polybench_timer_print':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'entry => <Function Return>' in function 'polybench_alloc_data':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'entry => <Function Return>' in function 'polybench_alloc_data':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.body8.i => for.inc23.i' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.body8.i => for.inc23.i' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.body3.i44 => for.inc26.i' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.body3.i44 => for.inc26.i' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.cond1.preheader.i42 => kernel_gemm.exit' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.cond1.preheader.i42 => kernel_gemm.exit' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.body41.i => for.inc54.i' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.body41.i => for.inc54.i' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.cond38.preheader.i => for.cond1.preheader.i42' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.cond38.preheader.i => for.cond1.preheader.i42' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.body18.i => for.inc31.i' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.body18.i => for.inc31.i' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.cond15.preheader.i => for.cond38.preheader.i' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.cond15.preheader.i => for.cond38.preheader.i' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.body3.i => for.inc8.i' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.body3.i => for.inc8.i' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.cond1.preheader.i => for.cond15.preheader.i.preheader' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.cond1.preheader.i => for.cond15.preheader.i.preheader' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.cond1.preheader.i => kernel_gemm.exit' in function 'main':
; CHECK-NEXT: Original Zone {
; CHECK-NEXT:     Lifetime: { [MemRef_9[i0, i1] -> [i2, i3, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 <= 1; [MemRef_9[i0, i1] -> [2, i3, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i3 < i0; [MemRef_9[i0, i1] -> [2, i0, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i4 <= 0; [MemRef_9[i0, i1] -> [2, i0, 1, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i5 < i1; [MemRef_9[i0, i1] -> [2, i0, 1, i1, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 <= 0; [MemRef_9[i0, i1] -> [i2, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body41_i[i0, i1] -> Val_double__div46_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 >= 3; [MemRef_9[i0, i1] -> [2, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body41_i[i0, i1] -> Val_double__div46_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i3 > i0; [MemRef_9[i0, i1] -> [2, i0, i4, i5, i6{{\]\]}} -> [Stmt_for_body41_i[i0, i1] -> Val_double__div46_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i4 >= 2; [MemRef_9[i0, i1] -> [2, i0, 1, i5, i6{{\]\]}} -> [Stmt_for_body41_i[i0, i1] -> Val_double__div46_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i5 > i1; [MemRef_9[i0, i1] -> [2, i0, 1, i1, i6{{\]\]}} -> [Stmt_for_body41_i[i0, i1] -> Val_double__div46_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 > 0; [MemRef_1[i0, i1] -> [i2, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 0 < i2 <= 2; [MemRef_1[i0, i1] -> [3, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i3 < i0; [MemRef_1[i0, i1] -> [0, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i3 > i0; [MemRef_1[i0, i1] -> [3, i0, i4, i5, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i4 < i1; [MemRef_1[i0, i1] -> [0, i0, i4, i5, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i4 >= 2; [MemRef_1[i0, i1] -> [0, i0, 1, i5, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i5 > i1; [MemRef_1[i0, i1] -> [3, i0, i1, i5, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i5 < 0; [MemRef_1[i0, i1] -> [0, i0, 1, i1, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 > 0; [MemRef_1[i0, i1] -> [3, i0, i1, 0, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 <= 0; [MemRef_1[i0, i1] -> [i2, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body8_i[i0, i1, 1023] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 >= 4; [MemRef_1[i0, i1] -> [3, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body8_i[i0, i1, 1023] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i3 > i0; [MemRef_1[i0, i1] -> [3, i0, i4, i5, i6{{\]\]}} -> [Stmt_for_body8_i[i0, i1, 1023] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i4 > i1; [MemRef_1[i0, i1] -> [3, i0, i1, i5, i6{{\]\]}} -> [Stmt_for_body8_i[i0, i1, 1023] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i5 >= 2; [MemRef_1[i0, i1] -> [3, i0, i1, 1, i6{{\]\]}} -> [Stmt_for_body8_i[i0, i1, 1023] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 >= 1024; [MemRef_1[i0, i1] -> [3, i0, i1, 1, i6{{\]\]}} -> [Stmt_for_body8_i[i0, i1, -1 + i6] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 0 < i6 <= 1023; [MemRef_1[i0, i1] -> [i2, i3, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 < 0; [MemRef_1[i0, i1] -> [0, i3, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i3 < i0; [MemRef_1[i0, i1] -> [0, i0, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i4 <= 0; [MemRef_1[i0, i1] -> [0, i0, 1, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i5 < i1; [MemRef_1[i0, i1] -> [0, i0, 1, i1, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 <= 0; [MemRef_5[i0, i1] -> [i2, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body18_i[i0, i1] -> Val_double__div23_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 >= 2; [MemRef_5[i0, i1] -> [1, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body18_i[i0, i1] -> Val_double__div23_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i3 > i0; [MemRef_5[i0, i1] -> [1, i0, i4, i5, i6{{\]\]}} -> [Stmt_for_body18_i[i0, i1] -> Val_double__div23_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i4 >= 2; [MemRef_5[i0, i1] -> [1, i0, 1, i5, i6{{\]\]}} -> [Stmt_for_body18_i[i0, i1] -> Val_double__div23_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i5 > i1; [MemRef_5[i0, i1] -> [1, i0, 1, i1, i6{{\]\]}} -> [Stmt_for_body18_i[i0, i1] -> Val_double__div23_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 > 0; [MemRef_1[i0, i1] -> [3, i0, i1, 1, i6{{\]\]}} -> [Stmt_for_body3_i44[i0, i1] -> Val_double__mul_i43[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 <= 0; [MemRef_1[i0, i1] -> [3, i0, i1, 0, i6{{\]\]}} -> [Stmt_for_body3_i44[i0, i1] -> Val_double__mul_i43[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 > 0; [MemRef_5[i0, i1] -> [i2, i3, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 <= 0; [MemRef_5[i0, i1] -> [1, i3, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i3 < i0; [MemRef_5[i0, i1] -> [1, i0, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i4 <= 0; [MemRef_5[i0, i1] -> [1, i0, 1, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i5 < i1; [MemRef_5[i0, i1] -> [1, i0, 1, i1, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 <= 0 }
; CHECK-NEXT:     Written:  { [MemRef_5[i0, i1] -> [1, i0, 1, i1, 0{{\]\]}} -> [Stmt_for_body18_i[i0, i1] -> Val_double__div23_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023; [MemRef_1[i0, i1] -> [3, i0, i1, 1, i6{{\]\]}} -> [Stmt_for_body8_i[i0, i1, i6] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 0 <= i6 <= 1023; [MemRef_1[i0, i1] -> [3, i0, i1, 0, 0{{\]\]}} -> [Stmt_for_body3_i44[i0, i1] -> Val_double__mul_i43[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023; [MemRef_9[i0, i1] -> [2, i0, 1, i1, 0{{\]\]}} -> [Stmt_for_body41_i[i0, i1] -> Val_double__div46_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023; [MemRef_1[i0, i1] -> [0, i0, 1, i1, 0{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 }
; CHECK-NEXT: }
; CHECK-NEXT: Mapped 0x2951663ca20:
; CHECK-NEXT:     Accesses:  3
; CHECK-NEXT:     Target:    { Stmt_for_body8_i[i0, i1, i2] -> MemRef_1[i0, i1] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 0 <= i2 <= 1023 }
; CHECK-NEXT:     Lifetime:  { Stmt_for_body8_i[i0, i1, 0] -> [3, i0, i1, 1, o4] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and o4 <= 0; Stmt_for_body8_i[i0, i1, i2] -> [3, i0, i1, 1, i2] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 0 < i2 <= 1023; Stmt_for_body8_i[i0, i1, 0] -> [3, i0, i1, 0, o4] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and o4 > 0 }
; CHECK-NEXT:     Zone {
; CHECK-NEXT:         Lifetime: { [MemRef_1[i0, i1] -> [3, i0, i1, 1, i6{{\]\]}} -> [Stmt_for_body8_i[i0, i1, -1 + i6] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 0 < i6 <= 1023; [MemRef_1[i0, i1] -> [3, i0, i1, 1, i6{{\]\]}} -> [Stmt_for_body3_i44[i0, i1] -> Val_double__mul_i43[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 <= 0; [MemRef_1[i0, i1] -> [3, i0, i1, 0, i6{{\]\]}} -> [Stmt_for_body3_i44[i0, i1] -> Val_double__mul_i43[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 > 0 }
; CHECK-NEXT:         Written:  { [MemRef_1[i0, i1] -> [3, i0, i1, 1, i6{{\]\]}} -> [Stmt_for_body8_i[i0, i1, i6] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 0 <= i6 <= 1023; [MemRef_1[i0, i1] -> [3, i0, i1, 0, 0{{\]\]}} -> [Stmt_for_body3_i44[i0, i1] -> Val_double__mul_i43[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 }
; CHECK-NEXT:     }
; CHECK-NEXT: After Zone {
; CHECK-NEXT:     Lifetime: { [MemRef_9[i0, i1] -> [i2, i3, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 <= 1; [MemRef_9[i0, i1] -> [2, i3, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i3 < i0; [MemRef_9[i0, i1] -> [2, i0, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i4 <= 0; [MemRef_9[i0, i1] -> [2, i0, 1, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i5 < i1; [MemRef_9[i0, i1] -> [2, i0, 1, i1, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 <= 0; [MemRef_9[i0, i1] -> [i2, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body41_i[i0, i1] -> Val_double__div46_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 >= 3; [MemRef_9[i0, i1] -> [2, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body41_i[i0, i1] -> Val_double__div46_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i3 > i0; [MemRef_9[i0, i1] -> [2, i0, i4, i5, i6{{\]\]}} -> [Stmt_for_body41_i[i0, i1] -> Val_double__div46_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i4 >= 2; [MemRef_9[i0, i1] -> [2, i0, 1, i5, i6{{\]\]}} -> [Stmt_for_body41_i[i0, i1] -> Val_double__div46_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i5 > i1; [MemRef_9[i0, i1] -> [2, i0, 1, i1, i6{{\]\]}} -> [Stmt_for_body41_i[i0, i1] -> Val_double__div46_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 > 0; [MemRef_1[i0, i1] -> [i2, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 0 < i2 <= 2; [MemRef_1[i0, i1] -> [3, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i3 < i0; [MemRef_1[i0, i1] -> [0, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i3 > i0; [MemRef_1[i0, i1] -> [3, i0, i4, i5, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i4 < i1; [MemRef_1[i0, i1] -> [0, i0, i4, i5, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i4 >= 2; [MemRef_1[i0, i1] -> [0, i0, 1, i5, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i5 > i1; [MemRef_1[i0, i1] -> [3, i0, i1, i5, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i5 < 0; [MemRef_1[i0, i1] -> [0, i0, 1, i1, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 > 0; [MemRef_1[i0, i1] -> [3, i0, i1, 0, i6{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 <= 0; [MemRef_1[i0, i1] -> [i2, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body8_i[i0, i1, 1023] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 >= 4; [MemRef_1[i0, i1] -> [3, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body8_i[i0, i1, 1023] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i3 > i0; [MemRef_1[i0, i1] -> [3, i0, i4, i5, i6{{\]\]}} -> [Stmt_for_body8_i[i0, i1, 1023] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i4 > i1; [MemRef_1[i0, i1] -> [3, i0, i1, i5, i6{{\]\]}} -> [Stmt_for_body8_i[i0, i1, 1023] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i5 >= 2; [MemRef_1[i0, i1] -> [3, i0, i1, 1, i6{{\]\]}} -> [Stmt_for_body8_i[i0, i1, 1023] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 >= 1024; [MemRef_1[i0, i1] -> [3, i0, i1, 1, i6{{\]\]}} -> [Stmt_for_body8_i[i0, i1, -1 + i6] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 0 < i6 <= 1023; [MemRef_1[i0, i1] -> [i2, i3, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 < 0; [MemRef_1[i0, i1] -> [0, i3, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i3 < i0; [MemRef_1[i0, i1] -> [0, i0, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i4 <= 0; [MemRef_1[i0, i1] -> [0, i0, 1, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i5 < i1; [MemRef_1[i0, i1] -> [0, i0, 1, i1, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 <= 0; [MemRef_5[i0, i1] -> [i2, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body18_i[i0, i1] -> Val_double__div23_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 >= 2; [MemRef_5[i0, i1] -> [1, i3, i4, i5, i6{{\]\]}} -> [Stmt_for_body18_i[i0, i1] -> Val_double__div23_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i3 > i0; [MemRef_5[i0, i1] -> [1, i0, i4, i5, i6{{\]\]}} -> [Stmt_for_body18_i[i0, i1] -> Val_double__div23_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i4 >= 2; [MemRef_5[i0, i1] -> [1, i0, 1, i5, i6{{\]\]}} -> [Stmt_for_body18_i[i0, i1] -> Val_double__div23_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i5 > i1; [MemRef_5[i0, i1] -> [1, i0, 1, i1, i6{{\]\]}} -> [Stmt_for_body18_i[i0, i1] -> Val_double__div23_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 > 0; [MemRef_1[i0, i1] -> [3, i0, i1, 1, i6{{\]\]}} -> [Stmt_for_body3_i44[i0, i1] -> Val_double__mul_i43[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 <= 0; [MemRef_1[i0, i1] -> [3, i0, i1, 0, i6{{\]\]}} -> [Stmt_for_body3_i44[i0, i1] -> Val_double__mul_i43[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 > 0; [MemRef_5[i0, i1] -> [i2, i3, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 <= 0; [MemRef_5[i0, i1] -> [1, i3, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i3 < i0; [MemRef_5[i0, i1] -> [1, i0, i4, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i4 <= 0; [MemRef_5[i0, i1] -> [1, i0, 1, i5, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i5 < i1; [MemRef_5[i0, i1] -> [1, i0, 1, i1, i6{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i6 <= 0 }
; CHECK-NEXT:     Written:  { [MemRef_5[i0, i1] -> [1, i0, 1, i1, 0{{\]\]}} -> [Stmt_for_body18_i[i0, i1] -> Val_double__div23_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023; [MemRef_1[i0, i1] -> [3, i0, i1, 1, i6{{\]\]}} -> [Stmt_for_body8_i[i0, i1, i6] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 0 <= i6 <= 1023; [MemRef_1[i0, i1] -> [3, i0, i1, 0, 0{{\]\]}} -> [Stmt_for_body3_i44[i0, i1] -> Val_double__mul_i43[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023; [MemRef_9[i0, i1] -> [2, i0, 1, i1, 0{{\]\]}} -> [Stmt_for_body41_i[i0, i1] -> Val_double__div46_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023; [MemRef_1[i0, i1] -> [0, i0, 1, i1, 0{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 }
; CHECK-NEXT: }
; CHECK-NEXT: After Statements {
; CHECK-NEXT:     Stmt_for_cond1_preheader_i
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_for_cond1_preheader_i[i0] -> MemRef_conv_i[] };
; CHECK-NEXT:     Stmt_for_body3_i
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_for_body3_i[i0, i1] -> MemRef_conv_i[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_for_body3_i[i0, i1] -> MemRef_1[i0, i1] };
; CHECK-NEXT:     Stmt_for_cond15_preheader_i
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_for_cond15_preheader_i[i0] -> MemRef_conv19_i[] };
; CHECK-NEXT:     Stmt_for_body18_i
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_for_body18_i[i0, i1] -> MemRef_conv19_i[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_for_body18_i[i0, i1] -> MemRef_5[i0, i1] };
; CHECK-NEXT:     Stmt_for_cond38_preheader_i
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_for_cond38_preheader_i[i0] -> MemRef_conv42_i[] };
; CHECK-NEXT:     Stmt_for_body41_i
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_for_body41_i[i0, i1] -> MemRef_conv42_i[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_for_body41_i[i0, i1] -> MemRef_9[i0, i1] };
; CHECK-NEXT:     Stmt_for_body3_i44
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_for_body3_i44[i0, i1] -> MemRef_1[i0, i1] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_for_body3_i44[i0, i1] -> MemRef_1[i0, i1] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_for_body3_i44[i0, i1] -> MemRef_19__phi[] };
; CHECK-NEXT:            new: { Stmt_for_body3_i44[i0, i1] -> MemRef_1[i0, i1] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 };
; CHECK-NEXT:     Stmt_for_body8_i
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_for_body8_i[i0, i1, i2] -> MemRef_19__phi[] };
; CHECK-NEXT:            new: { Stmt_for_body8_i[i0, i1, i2] -> MemRef_1[i0, i1] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 0 <= i2 <= 1023 };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_for_body8_i[i0, i1, i2] -> MemRef_19__phi[] };
; CHECK-NEXT:            new: { Stmt_for_body8_i[i0, i1, i2] -> MemRef_1[i0, i1] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 0 <= i2 <= 1023 };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_for_body8_i[i0, i1, i2] -> MemRef_5[i0, i2] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_for_body8_i[i0, i1, i2] -> MemRef_9[i2, i1] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_for_body8_i[i0, i1, i2] -> MemRef_1[i0, i1] };
; CHECK-NEXT: }
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.cond1.preheader.i => kernel_gemm.exit' in function 'main':
; CHECK-NEXT: :: isl ast :: main :: %for.cond1.preheader.i---%kernel_gemm.exit
;
; CHECK:      if (1 && (&MemRef_9[1023][1024] <= &MemRef_5[0][0] || &MemRef_5[1023][1024] <= &MemRef_9[0][0]) && (&MemRef_1[1023][1024] <= &MemRef_5[0][0] || &MemRef_5[1023][1024] <= &MemRef_1[0][0]) && (&MemRef_1[1023][1024] <= &MemRef_9[0][0] || &MemRef_9[1023][1024] <= &MemRef_1[0][0]))
;
; CHECK:          {
; CHECK-NEXT:       for (int c0 = 0; c0 <= 1023; c0 += 1) {
; CHECK-NEXT:         Stmt_for_cond1_preheader_i(c0);
; CHECK-NEXT:         for (int c1 = 0; c1 <= 1023; c1 += 1)
; CHECK-NEXT:           Stmt_for_body3_i(c0, c1);
; CHECK-NEXT:       }
; CHECK-NEXT:       for (int c0 = 0; c0 <= 1023; c0 += 1) {
; CHECK-NEXT:         Stmt_for_cond15_preheader_i(c0);
; CHECK-NEXT:         for (int c1 = 0; c1 <= 1023; c1 += 1)
; CHECK-NEXT:           Stmt_for_body18_i(c0, c1);
; CHECK-NEXT:       }
; CHECK-NEXT:       for (int c0 = 0; c0 <= 1023; c0 += 1) {
; CHECK-NEXT:         Stmt_for_cond38_preheader_i(c0);
; CHECK-NEXT:         for (int c1 = 0; c1 <= 1023; c1 += 1)
; CHECK-NEXT:           Stmt_for_body41_i(c0, c1);
; CHECK-NEXT:       }
; CHECK-NEXT:       for (int c0 = 0; c0 <= 1023; c0 += 1)
; CHECK-NEXT:         for (int c1 = 0; c1 <= 1023; c1 += 1) {
; CHECK-NEXT:           Stmt_for_body3_i44(c0, c1);
; CHECK-NEXT:           for (int c2 = 0; c2 <= 1023; c2 += 1)
; CHECK-NEXT:             Stmt_for_body8_i(c0, c1, c2);
; CHECK-NEXT:         }
; CHECK-NEXT:     }
;
; CHECK:      else
; CHECK-NEXT:     {  /* original code */ }
;
; CHECK:      Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.body6.i => for.end.i' in function 'main':
; CHECK-NEXT: Original Zone {
; CHECK-NEXT:     Lifetime: [p_0] -> { [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add123_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -15 + i0 <= 16o0 <= -14 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -1 + i0 <= 16o0 <= i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add15_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -3 + i0 <= 16o0 <= -2 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__conv52_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -7 + i0 <= 16o0 <= -6 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add33_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -5 + i0 <= 16o0 <= -4 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add105_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -13 + i0 <= 16o0 <= -12 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add69_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -9 + i0 <= 16o0 <= -8 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add87_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -11 + i0 <= 16o0 <= -10 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> Undef[] : -14 <= i0 <= 16383 and 16i1 <= 14 + i0 and ((16*floor((2 + i0)/16) = 2 + i0 and 14 <= i0 <= 16382 and 16i1 <= -14 + i0) or (-2 <= i0 <= 16381 and 16i1 <= 2 + i0 and 16*floor((2 + i0)/16) <= -12 + i0) or (-5 <= i0 <= 16378 and 16i1 <= 5 + i0 and 16*floor((5 + i0)/16) <= -9 + i0) or (-8 <= i0 <= 16375 and 16i1 <= 8 + i0 and 16*floor((8 + i0)/16) <= -6 + i0) or (-11 <= i0 <= 16372 and 16i1 <= 11 + i0 and 16*floor((11 + i0)/16) <= -3 + i0) or (i0 <= 16369 and 16*floor((14 + i0)/16) <= i0) or (16*floor((14 + i0)/16) = 14 + i0 and 2 <= i0 <= 16370 and 16i1 <= -2 + i0) or (16*floor((11 + i0)/16) = 11 + i0 and 5 <= i0 <= 16373 and 16i1 <= -5 + i0) or (16*floor((8 + i0)/16) = 8 + i0 and 8 <= i0 <= 16376 and 16i1 <= -8 + i0) or (16*floor((5 + i0)/16) = 5 + i0 and 11 <= i0 <= 16379 and 16i1 <= -11 + i0) or (16*floor((-15 + i0)/16) = -15 + i0 and i0 >= 15 and 16i1 <= -15 + i0)) }
; CHECK-NEXT:     Written:  [p_0] -> { [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add123_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -15 + i0 <= 16i1 <= -14 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__conv52_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -7 + i0 <= 16i1 <= -6 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -1 + i0 <= 16i1 <= i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add33_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -5 + i0 <= 16i1 <= -4 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add69_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -9 + i0 <= 16i1 <= -8 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add105_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -13 + i0 <= 16i1 <= -12 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add15_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -3 + i0 <= 16i1 <= -2 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add87_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -11 + i0 <= 16i1 <= -10 + i0 }
; CHECK-NEXT: }
; CHECK-NEXT: After Zone {
; CHECK-NEXT:     Lifetime: [p_0] -> { [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add123_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -15 + i0 <= 16o0 <= -14 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -1 + i0 <= 16o0 <= i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add15_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -3 + i0 <= 16o0 <= -2 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__conv52_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -7 + i0 <= 16o0 <= -6 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add33_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -5 + i0 <= 16o0 <= -4 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add105_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -13 + i0 <= 16o0 <= -12 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add69_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -9 + i0 <= 16o0 <= -8 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add87_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -11 + i0 <= 16o0 <= -10 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> Undef[] : -14 <= i0 <= 16383 and 16i1 <= 14 + i0 and ((16*floor((2 + i0)/16) = 2 + i0 and 14 <= i0 <= 16382 and 16i1 <= -14 + i0) or (-2 <= i0 <= 16381 and 16i1 <= 2 + i0 and 16*floor((2 + i0)/16) <= -12 + i0) or (-5 <= i0 <= 16378 and 16i1 <= 5 + i0 and 16*floor((5 + i0)/16) <= -9 + i0) or (-8 <= i0 <= 16375 and 16i1 <= 8 + i0 and 16*floor((8 + i0)/16) <= -6 + i0) or (-11 <= i0 <= 16372 and 16i1 <= 11 + i0 and 16*floor((11 + i0)/16) <= -3 + i0) or (i0 <= 16369 and 16*floor((14 + i0)/16) <= i0) or (16*floor((14 + i0)/16) = 14 + i0 and 2 <= i0 <= 16370 and 16i1 <= -2 + i0) or (16*floor((11 + i0)/16) = 11 + i0 and 5 <= i0 <= 16373 and 16i1 <= -5 + i0) or (16*floor((8 + i0)/16) = 8 + i0 and 8 <= i0 <= 16376 and 16i1 <= -8 + i0) or (16*floor((5 + i0)/16) = 5 + i0 and 11 <= i0 <= 16379 and 16i1 <= -11 + i0) or (16*floor((-15 + i0)/16) = -15 + i0 and i0 >= 15 and 16i1 <= -15 + i0)) }
; CHECK-NEXT:     Written:  [p_0] -> { [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add123_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -15 + i0 <= 16i1 <= -14 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__conv52_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -7 + i0 <= 16i1 <= -6 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -1 + i0 <= 16i1 <= i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add33_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -5 + i0 <= 16i1 <= -4 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add69_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -9 + i0 <= 16i1 <= -8 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add105_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -13 + i0 <= 16i1 <= -12 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add15_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -3 + i0 <= 16i1 <= -2 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add87_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -11 + i0 <= 16i1 <= -10 + i0 }
; CHECK-NEXT: }
; CHECK-NEXT: After Statements {
; CHECK-NEXT:     Stmt_for_body6_i
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_1[p_0, i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[16i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[1 + 16i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[2 + 16i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[3 + 16i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[4 + 16i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[5 + 16i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[6 + 16i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[7 + 16i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[8 + 16i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[9 + 16i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[10 + 16i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[11 + 16i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[12 + 16i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[13 + 16i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[14 + 16i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[15 + 16i0] };
; CHECK-NEXT: }
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.body6.i => for.end.i' in function 'main':
; CHECK-NEXT: :: isl ast :: main :: %for.body6.i---%for.end.i
;
; CHECK:      if (1)
;
; CHECK:          for (int c0 = 0; c0 <= 1023; c0 += 1)
; CHECK-NEXT:       Stmt_for_body6_i(c0);
;
; CHECK:      else
; CHECK-NEXT:     {  /* original code */ }
;
; CHECK:      Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.cond3.preheader.i => print_array.exit' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.cond3.preheader.i => print_array.exit' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'entry => <Function Return>' in function 'main':
; CHECK-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'entry => <Function Return>' in function 'main':

; FLAT:      Printing analysis 'Polly - Flatten schedule' for region: 'entry => <Function Return>' in function 'polybench_flush_cache':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'entry => <Function Return>' in function 'polybench_flush_cache':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'entry => <Function Return>' in function 'polybench_flush_cache':
; FLAT-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'entry => <Function Return>' in function 'polybench_prepare_instruments':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'entry => <Function Return>' in function 'polybench_prepare_instruments':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'entry => <Function Return>' in function 'polybench_prepare_instruments':
; FLAT-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'entry => <Function Return>' in function 'polybench_timer_start':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'entry => <Function Return>' in function 'polybench_timer_start':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'entry => <Function Return>' in function 'polybench_timer_start':
; FLAT-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'entry => <Function Return>' in function 'polybench_timer_stop':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'entry => <Function Return>' in function 'polybench_timer_stop':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'entry => <Function Return>' in function 'polybench_timer_stop':
; FLAT-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'entry => <Function Return>' in function 'polybench_timer_print':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'entry => <Function Return>' in function 'polybench_timer_print':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'entry => <Function Return>' in function 'polybench_timer_print':
; FLAT-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'entry => <Function Return>' in function 'polybench_alloc_data':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'entry => <Function Return>' in function 'polybench_alloc_data':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'entry => <Function Return>' in function 'polybench_alloc_data':
; FLAT-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'for.body8.i => for.inc23.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.body8.i => for.inc23.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.body8.i => for.inc23.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'for.body3.i44 => for.inc26.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.body3.i44 => for.inc26.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.body3.i44 => for.inc26.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'for.cond1.preheader.i42 => kernel_gemm.exit' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.cond1.preheader.i42 => kernel_gemm.exit' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.cond1.preheader.i42 => kernel_gemm.exit' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'for.body41.i => for.inc54.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.body41.i => for.inc54.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.body41.i => for.inc54.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'for.cond38.preheader.i => for.cond1.preheader.i42' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.cond38.preheader.i => for.cond1.preheader.i42' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.cond38.preheader.i => for.cond1.preheader.i42' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'for.body18.i => for.inc31.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.body18.i => for.inc31.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.body18.i => for.inc31.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'for.cond15.preheader.i => for.cond38.preheader.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.cond15.preheader.i => for.cond38.preheader.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.cond15.preheader.i => for.cond38.preheader.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'for.body3.i => for.inc8.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.body3.i => for.inc8.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.body3.i => for.inc8.i' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'for.cond1.preheader.i => for.cond15.preheader.i.preheader' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.cond1.preheader.i => for.cond15.preheader.i.preheader' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.cond1.preheader.i => for.cond15.preheader.i.preheader' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'for.cond1.preheader.i => kernel_gemm.exit' in function 'main':
; FLAT-NEXT: Schedule before flattening {
; FLAT-NEXT:     { Stmt_for_cond15_preheader_i[i0] -> [1, i0, 0, 0, 0] }
; FLAT-NEXT:     { Stmt_for_cond1_preheader_i[i0] -> [0, i0, 0, 0, 0] }
; FLAT-NEXT:     { Stmt_for_cond38_preheader_i[i0] -> [2, i0, 0, 0, 0] }
; FLAT-NEXT:     { Stmt_for_body3_i44[i0, i1] -> [3, i0, i1, 0, 0] }
; FLAT-NEXT:     { Stmt_for_body8_i[i0, i1, i2] -> [3, i0, i1, 1, i2] }
; FLAT-NEXT:     { Stmt_for_body41_i[i0, i1] -> [2, i0, 1, i1, 0] }
; FLAT-NEXT:     { Stmt_for_body3_i[i0, i1] -> [0, i0, 1, i1, 0] }
; FLAT-NEXT:     { Stmt_for_body18_i[i0, i1] -> [1, i0, 1, i1, 0] }
; FLAT-NEXT: }
;
; FLAT:      Schedule after flattening {
; FLAT-NEXT:     { Stmt_for_body8_i[i0, i1, i2] -> [3148801 + 1049600i0 + 1025i1 + i2] }
; FLAT-NEXT:     { Stmt_for_body3_i44[i0, i1] -> [3148800 + 1049600i0 + 1025i1] }
; FLAT-NEXT:     { Stmt_for_cond15_preheader_i[i0] -> [1049600 + 1025i0] }
; FLAT-NEXT:     { Stmt_for_body3_i[i0, i1] -> [1 + 1025i0 + i1] }
; FLAT-NEXT:     { Stmt_for_body41_i[i0, i1] -> [2099201 + 1025i0 + i1] }
; FLAT-NEXT:     { Stmt_for_body18_i[i0, i1] -> [1049601 + 1025i0 + i1] }
; FLAT-NEXT:     { Stmt_for_cond1_preheader_i[i0] -> [1025i0] }
; FLAT-NEXT:     { Stmt_for_cond38_preheader_i[i0] -> [2099200 + 1025i0] }
; FLAT-NEXT: }
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.cond1.preheader.i => kernel_gemm.exit' in function 'main':
; FLAT-NEXT: Original Zone {
; FLAT-NEXT:     Lifetime: { [MemRef_1[i0, i1] -> [i2{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 2 + 1025i0 + i1 <= i2 <= 3148800 + 1049600i0 + 1025i1; [MemRef_5[i0, i1] -> [i2{{\]\]}} -> [Stmt_for_body18_i[i0, i1] -> Val_double__div23_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 >= 1049602 + 1025i0 + i1; [MemRef_9[i0, i1] -> [i2{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 <= 2099201 + 1025i0 + i1; [MemRef_1[i0, i1] -> [3148801 + 1049600i0 + 1025i1{{\]\]}} -> [Stmt_for_body3_i44[i0, i1] -> Val_double__mul_i43[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023; [MemRef_1[i0, i1] -> [i2{{\]\]}} -> [Stmt_for_body8_i[i0, i1, 1023] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 >= 3149826 + 1049600i0 + 1025i1; [MemRef_1[i0, i1] -> [i2{{\]\]}} -> [Stmt_for_body8_i[i0, i1, -3148802 - 1049600i0 - 1025i1 + i2] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 3148802 + 1049600i0 + 1025i1 <= i2 <= 3149825 + 1049600i0 + 1025i1; [MemRef_1[i0, i1] -> [i2{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 <= 1 + 1025i0 + i1; [MemRef_9[i0, i1] -> [i2{{\]\]}} -> [Stmt_for_body41_i[i0, i1] -> Val_double__div46_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 >= 2099202 + 1025i0 + i1; [MemRef_5[i0, i1] -> [i2{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 <= 1049601 + 1025i0 + i1 }
; FLAT-NEXT:     Written:  { [MemRef_1[i0, i1] -> [1 + 1025i0 + i1{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023; [MemRef_1[i0, i1] -> [3148800 + 1049600i0 + 1025i1{{\]\]}} -> [Stmt_for_body3_i44[i0, i1] -> Val_double__mul_i43[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023; [MemRef_5[i0, i1] -> [1049601 + 1025i0 + i1{{\]\]}} -> [Stmt_for_body18_i[i0, i1] -> Val_double__div23_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023; [MemRef_9[i0, i1] -> [2099201 + 1025i0 + i1{{\]\]}} -> [Stmt_for_body41_i[i0, i1] -> Val_double__div46_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023; [MemRef_1[i0, i1] -> [i2{{\]\]}} -> [Stmt_for_body8_i[i0, i1, -3148801 - 1049600i0 - 1025i1 + i2] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 3148801 + 1049600i0 + 1025i1 <= i2 <= 3149824 + 1049600i0 + 1025i1 }
; FLAT-NEXT: }
; FLAT-NEXT: Mapped 0x2e70cd4db60:
; FLAT-NEXT:     Accesses:  3
; FLAT-NEXT:     Target:    { Stmt_for_body8_i[i0, i1, i2] -> MemRef_1[i0, i1] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 >= 0 and -1 - 1049600i0 - 1025i1 <= i2 <= 1074790398 - 1049600i0 - 1025i1 and i2 <= 1023 }
; FLAT-NEXT:     Lifetime:  { Stmt_for_body8_i[i0, i1, i2] -> [3148801 + 1049600i0 + 1025i1 + i2] : i0 >= 0 and i1 >= 0 and 0 <= i2 <= 1074789375 - 1049600i0 - 1025i1 and i2 <= 1048575 - 1025i1 and i2 <= 1023; Stmt_for_body8_i[i0, 1023, i2] -> [4197376 + 1049600i0 + i2] : i2 > 0 and -1048574 - 1049600i0 <= i2 <= 1073740800 - 1049600i0 and i2 <= 1023; Stmt_for_body8_i[1023, 1023, i2] -> [1077938176 + i2] : 0 < i2 <= 1023 }
; FLAT-NEXT:     Zone {
; FLAT-NEXT:         Lifetime: { [MemRef_1[i0, i1] -> [3148801 + 1049600i0 + 1025i1{{\]\]}} -> [Stmt_for_body3_i44[i0, i1] -> Val_double__mul_i43[{{\]\]}} : 0 <= i0 <= 1023 and i1 >= 0 and -1024i0 <= i1 <= 1048574 - 1024i0 and i1 <= 1023; [MemRef_1[1023, 1023] -> [1077938176{{\]\]}} -> [Stmt_for_body3_i44[1023, 1023] -> Val_double__mul_i43[{{\]\]}}; [MemRef_1[i0, i1] -> [i2{{\]\]}} -> [Stmt_for_body8_i[i0, i1, -3148802 - 1049600i0 - 1025i1 + i2] -> Val_double__add_i[{{\]\]}} : exists (e2, e3: 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 >= 3148802 + 1049600i0 + 1025i1 and 3148802 <= i2 <= 1077938176 and i2 <= 4197376 + 1049600i0 and i2 <= 3149825 + 1049600i0 + 1025i1 and 1025*floor((-3148802 - 1049600i0 - 1025i1 + i2)/1025) >= -3149825 - 1049600i0 - 1025i1 + i2 and 1025*floor((-3148801 - 1049600i0 - 1025i1 + i2)/1025) <= -3148802 - 1049600i0 - 1025i1 + i2 and 0 <= e2 <= 1023 and 1049600e2 >= -4197376 + i2 and 0 <= e3 <= 1023 and -3149824 + i2 - 1049600e2 <= 1025e3 <= -3148801 + i2 - 1049600e2); [MemRef_1[i0, 1023] -> [i2{{\]\]}} -> [Stmt_for_body8_i[i0, 1023, -4197377 - 1049600i0 + i2] -> Val_double__add_i[{{\]\]}} : i0 >= 0 and 4197377 + 1049600i0 <= i2 <= 1077938176 and i2 <= 4198400 + 1049600i0 and 1025*floor((-5245951 - 1049600i0 + i2)/1025) <= -5245952 - 1049600i0 + i2 and 1049600*floor((-1049600i0 + i2)/1049600) <= -1048577 - 1049600i0 + i2 and 1025*floor((-4197377 - 1049600i0 + i2)/1025) >= -4198400 - 1049600i0 + i2; [MemRef_1[1023, 1023] -> [i2{{\]\]}} -> [Stmt_for_body8_i[1023, 1023, -1077938177 + i2] -> Val_double__add_i[{{\]\]}} : 1077938177 <= i2 <= 1077939199 and 1025*floor((-1077938177 + i2)/1025) >= -1077939200 + i2 }
; FLAT-NEXT:         Written:  { [MemRef_1[i0, i1] -> [3148800 + 1049600i0 + 1025i1{{\]\]}} -> [Stmt_for_body3_i44[i0, i1] -> Val_double__mul_i43[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1048574 - 1024i0 and i1 <= 1023; [MemRef_1[1023, 1023] -> [1077938175{{\]\]}} -> [Stmt_for_body3_i44[1023, 1023] -> Val_double__mul_i43[{{\]\]}}; [MemRef_1[i0, i1] -> [i2{{\]\]}} -> [Stmt_for_body8_i[i0, i1, -3148801 - 1049600i0 - 1025i1 + i2] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 3148801 + 1049600i0 + 1025i1 <= i2 <= 4197375 + 1049600i0 and i2 <= 3149824 + 1049600i0 + 1025i1; [MemRef_1[i0, 1023] -> [i2{{\]\]}} -> [Stmt_for_body8_i[i0, 1023, -4197376 - 1049600i0 + i2] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 4197376 + 1049600i0 <= i2 <= 1077938175 and i2 <= 4198399 + 1049600i0; [MemRef_1[1023, 1023] -> [i2{{\]\]}} -> [Stmt_for_body8_i[1023, 1023, -1077938176 + i2] -> Val_double__add_i[{{\]\]}} : 1077938176 <= i2 <= 1077939199 }
; FLAT-NEXT:     }
; FLAT-NEXT: After Zone {
; FLAT-NEXT:     Lifetime: { [MemRef_1[i0, i1] -> [i2{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 2 + 1025i0 + i1 <= i2 <= 3148800 + 1049600i0 + 1025i1; [MemRef_5[i0, i1] -> [i2{{\]\]}} -> [Stmt_for_body18_i[i0, i1] -> Val_double__div23_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 >= 1049602 + 1025i0 + i1; [MemRef_9[i0, i1] -> [i2{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 <= 2099201 + 1025i0 + i1; [MemRef_1[i0, i1] -> [3148801 + 1049600i0 + 1025i1{{\]\]}} -> [Stmt_for_body3_i44[i0, i1] -> Val_double__mul_i43[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023; [MemRef_1[i0, i1] -> [i2{{\]\]}} -> [Stmt_for_body8_i[i0, i1, 1023] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 >= 3149826 + 1049600i0 + 1025i1; [MemRef_1[i0, i1] -> [i2{{\]\]}} -> [Stmt_for_body8_i[i0, i1, -3148802 - 1049600i0 - 1025i1 + i2] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 3148802 + 1049600i0 + 1025i1 <= i2 <= 3149825 + 1049600i0 + 1025i1; [MemRef_1[i0, i1] -> [i2{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 <= 1 + 1025i0 + i1; [MemRef_9[i0, i1] -> [i2{{\]\]}} -> [Stmt_for_body41_i[i0, i1] -> Val_double__div46_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 >= 2099202 + 1025i0 + i1; [MemRef_5[i0, i1] -> [i2{{\]\]}} -> Undef[] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 <= 1049601 + 1025i0 + i1 }
; FLAT-NEXT:     Written:  { [MemRef_1[i0, i1] -> [1 + 1025i0 + i1{{\]\]}} -> [Stmt_for_body3_i[i0, i1] -> Val_double__div_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023; [MemRef_1[i0, i1] -> [3148800 + 1049600i0 + 1025i1{{\]\]}} -> [Stmt_for_body3_i44[i0, i1] -> Val_double__mul_i43[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023; [MemRef_5[i0, i1] -> [1049601 + 1025i0 + i1{{\]\]}} -> [Stmt_for_body18_i[i0, i1] -> Val_double__div23_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023; [MemRef_9[i0, i1] -> [2099201 + 1025i0 + i1{{\]\]}} -> [Stmt_for_body41_i[i0, i1] -> Val_double__div46_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023; [MemRef_1[i0, i1] -> [i2{{\]\]}} -> [Stmt_for_body8_i[i0, i1, -3148801 - 1049600i0 - 1025i1 + i2] -> Val_double__add_i[{{\]\]}} : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and 3148801 + 1049600i0 + 1025i1 <= i2 <= 3149824 + 1049600i0 + 1025i1 }
; FLAT-NEXT: }
; FLAT-NEXT: After Statements {
; FLAT-NEXT:     Stmt_for_cond1_preheader_i
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; FLAT-NEXT:                 { Stmt_for_cond1_preheader_i[i0] -> MemRef_conv_i[] };
; FLAT-NEXT:     Stmt_for_body3_i
; FLAT-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; FLAT-NEXT:                 { Stmt_for_body3_i[i0, i1] -> MemRef_conv_i[] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 { Stmt_for_body3_i[i0, i1] -> MemRef_1[i0, i1] };
; FLAT-NEXT:     Stmt_for_cond15_preheader_i
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; FLAT-NEXT:                 { Stmt_for_cond15_preheader_i[i0] -> MemRef_conv19_i[] };
; FLAT-NEXT:     Stmt_for_body18_i
; FLAT-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; FLAT-NEXT:                 { Stmt_for_body18_i[i0, i1] -> MemRef_conv19_i[] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 { Stmt_for_body18_i[i0, i1] -> MemRef_5[i0, i1] };
; FLAT-NEXT:     Stmt_for_cond38_preheader_i
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; FLAT-NEXT:                 { Stmt_for_cond38_preheader_i[i0] -> MemRef_conv42_i[] };
; FLAT-NEXT:     Stmt_for_body41_i
; FLAT-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; FLAT-NEXT:                 { Stmt_for_body41_i[i0, i1] -> MemRef_conv42_i[] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 { Stmt_for_body41_i[i0, i1] -> MemRef_9[i0, i1] };
; FLAT-NEXT:     Stmt_for_body3_i44
; FLAT-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 { Stmt_for_body3_i44[i0, i1] -> MemRef_1[i0, i1] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 { Stmt_for_body3_i44[i0, i1] -> MemRef_1[i0, i1] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; FLAT-NEXT:                 { Stmt_for_body3_i44[i0, i1] -> MemRef_19__phi[] };
; FLAT-NEXT:            new: { Stmt_for_body3_i44[i0, i1] -> MemRef_1[i0, i1] : i0 >= 0 and 0 <= i1 <= 1048574 - 1024i0 and i1 <= 1023; Stmt_for_body3_i44[1023, 1023] -> MemRef_1[1023, 1023] };
; FLAT-NEXT:     Stmt_for_body8_i
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; FLAT-NEXT:                 { Stmt_for_body8_i[i0, i1, i2] -> MemRef_19__phi[] };
; FLAT-NEXT:            new: { Stmt_for_body8_i[i0, i1, i2] -> MemRef_1[i0, i1] : 0 <= i0 <= 1023 and i1 >= 0 and 0 <= i2 <= 1048574 - 1025i1 and i2 <= 1023; Stmt_for_body8_i[i0, 1023, i2] -> MemRef_1[i0, 1023] : i0 >= 0 and 0 <= i2 <= 1073740799 - 1049600i0 and i2 <= 1023; Stmt_for_body8_i[1023, 1023, i2] -> MemRef_1[1023, 1023] : 0 <= i2 <= 1023 };
; FLAT-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; FLAT-NEXT:                 { Stmt_for_body8_i[i0, i1, i2] -> MemRef_19__phi[] };
; FLAT-NEXT:            new: { Stmt_for_body8_i[i0, i1, i2] -> MemRef_1[i0, i1] : 0 <= i0 <= 1023 and 0 <= i1 <= 1023 and i2 >= 0 and -1 - 1049600i0 - 1025i1 <= i2 <= 1074790398 - 1049600i0 - 1025i1 and i2 <= 1023 };
; FLAT-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 { Stmt_for_body8_i[i0, i1, i2] -> MemRef_5[i0, i2] };
; FLAT-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 { Stmt_for_body8_i[i0, i1, i2] -> MemRef_9[i2, i1] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 { Stmt_for_body8_i[i0, i1, i2] -> MemRef_1[i0, i1] };
; FLAT-NEXT: }
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.cond1.preheader.i => kernel_gemm.exit' in function 'main':
; FLAT-NEXT: :: isl ast :: main :: %for.cond1.preheader.i---%kernel_gemm.exit
;
; FLAT:      if (1 && (&MemRef_9[1023][1024] <= &MemRef_5[0][0] || &MemRef_5[1023][1024] <= &MemRef_9[0][0]) && (&MemRef_1[1023][1024] <= &MemRef_5[0][0] || &MemRef_5[1023][1024] <= &MemRef_1[0][0]) && (&MemRef_1[1023][1024] <= &MemRef_9[0][0] || &MemRef_9[1023][1024] <= &MemRef_1[0][0]))
;
; FLAT:          {
; FLAT-NEXT:       for (int c0 = 0; c0 <= 1049599; c0 += 1) {
; FLAT-NEXT:         if (c0 % 1025 == 0) {
; FLAT-NEXT:           Stmt_for_cond1_preheader_i(c0 / 1025);
; FLAT-NEXT:         } else {
; FLAT-NEXT:           Stmt_for_body3_i((c0 - 1) / 1025, (c0 + 1024) % 1025);
; FLAT-NEXT:         }
; FLAT-NEXT:       }
; FLAT-NEXT:       for (int c0 = 1049600; c0 <= 2099199; c0 += 1) {
; FLAT-NEXT:         if (c0 % 1025 == 0) {
; FLAT-NEXT:           Stmt_for_cond15_preheader_i((c0 / 1025) - 1024);
; FLAT-NEXT:         } else {
; FLAT-NEXT:           Stmt_for_body18_i((c0 - 1) / 1025 - 1024, (c0 - 1) % 1025);
; FLAT-NEXT:         }
; FLAT-NEXT:       }
; FLAT-NEXT:       for (int c0 = 2099200; c0 <= 1077939199; c0 += 1) {
; FLAT-NEXT:         if ((c0 >= 3148801 && c0 <= 3149824) || (c0 >= 3149825 && (1024 * c0 + 1024) % 1025 <= 1023)) {
; FLAT-NEXT:           Stmt_for_body8_i(c0 - (1049599 * c0 + 1049599) / 1049600 - 3, c0 <= 3149824 || ((1049599 * c0 + 1049599) % 1049600 <= 1049598 && (1049599 * c0 + 1049599) % 1049600 >= 1048576) ? 0 : -1023 * c0 - (1024 * c0 + 1024) / 1025 + 1024 * ((1049599 * c0 + 1049599) / 1049600), -((1024 * c0 + 1024) % 1025) + 1023);
; FLAT-NEXT:         } else if (c0 <= 3148799 && c0 % 1025 >= 1) {
; FLAT-NEXT:           Stmt_for_body41_i((c0 - 1) / 1025 - 2048, (c0 - 1) % 1025);
; FLAT-NEXT:         } else if (c0 <= 3147775 && c0 % 1025 == 0) {
; FLAT-NEXT:           Stmt_for_cond38_preheader_i((c0 / 1025) - 2048);
; FLAT-NEXT:         } else {
; FLAT-NEXT:           Stmt_for_body3_i44(c0 / 1049600 - 3, (c0 / 1025) - 1024 * (c0 / 1049600));
; FLAT-NEXT:         }
; FLAT-NEXT:       }
; FLAT-NEXT:     }
;
; FLAT:      else
; FLAT-NEXT:     {  /* original code */ }
;
; FLAT:      Printing analysis 'Polly - Flatten schedule' for region: 'for.body6.i => for.end.i' in function 'main':
; FLAT-NEXT: Schedule before flattening {
; FLAT-NEXT:     { Stmt_for_body6_i[i0] -> [i0] }
; FLAT-NEXT: }
;
; FLAT:      Schedule after flattening {
; FLAT-NEXT:     [p_0] -> { Stmt_for_body6_i[i0] -> [i0] }
; FLAT-NEXT: }
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.body6.i => for.end.i' in function 'main':
; FLAT-NEXT: Original Zone {
; FLAT-NEXT:     Lifetime: [p_0] -> { [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add123_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -15 + i0 <= 16o0 <= -14 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -1 + i0 <= 16o0 <= i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add15_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -3 + i0 <= 16o0 <= -2 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__conv52_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -7 + i0 <= 16o0 <= -6 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add33_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -5 + i0 <= 16o0 <= -4 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add105_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -13 + i0 <= 16o0 <= -12 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add69_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -9 + i0 <= 16o0 <= -8 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add87_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -11 + i0 <= 16o0 <= -10 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> Undef[] : -14 <= i0 <= 16383 and 16i1 <= 14 + i0 and ((16*floor((2 + i0)/16) = 2 + i0 and 14 <= i0 <= 16382 and 16i1 <= -14 + i0) or (-2 <= i0 <= 16381 and 16i1 <= 2 + i0 and 16*floor((2 + i0)/16) <= -12 + i0) or (-5 <= i0 <= 16378 and 16i1 <= 5 + i0 and 16*floor((5 + i0)/16) <= -9 + i0) or (-8 <= i0 <= 16375 and 16i1 <= 8 + i0 and 16*floor((8 + i0)/16) <= -6 + i0) or (-11 <= i0 <= 16372 and 16i1 <= 11 + i0 and 16*floor((11 + i0)/16) <= -3 + i0) or (i0 <= 16369 and 16*floor((14 + i0)/16) <= i0) or (16*floor((14 + i0)/16) = 14 + i0 and 2 <= i0 <= 16370 and 16i1 <= -2 + i0) or (16*floor((11 + i0)/16) = 11 + i0 and 5 <= i0 <= 16373 and 16i1 <= -5 + i0) or (16*floor((8 + i0)/16) = 8 + i0 and 8 <= i0 <= 16376 and 16i1 <= -8 + i0) or (16*floor((5 + i0)/16) = 5 + i0 and 11 <= i0 <= 16379 and 16i1 <= -11 + i0) or (16*floor((-15 + i0)/16) = -15 + i0 and i0 >= 15 and 16i1 <= -15 + i0)) }
; FLAT-NEXT:     Written:  [p_0] -> { [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add123_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -15 + i0 <= 16i1 <= -14 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__conv52_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -7 + i0 <= 16i1 <= -6 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -1 + i0 <= 16i1 <= i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add33_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -5 + i0 <= 16i1 <= -4 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add69_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -9 + i0 <= 16i1 <= -8 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add105_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -13 + i0 <= 16i1 <= -12 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add15_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -3 + i0 <= 16i1 <= -2 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add87_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -11 + i0 <= 16i1 <= -10 + i0 }
; FLAT-NEXT: }
; FLAT-NEXT: After Zone {
; FLAT-NEXT:     Lifetime: [p_0] -> { [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add123_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -15 + i0 <= 16o0 <= -14 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -1 + i0 <= 16o0 <= i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add15_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -3 + i0 <= 16o0 <= -2 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__conv52_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -7 + i0 <= 16o0 <= -6 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add33_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -5 + i0 <= 16o0 <= -4 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add105_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -13 + i0 <= 16o0 <= -12 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add69_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -9 + i0 <= 16o0 <= -8 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[o0] -> Val_i8__add87_i_i[{{\]\]}} : 0 <= o0 <= 1023 and o0 < i1 and -11 + i0 <= 16o0 <= -10 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> Undef[] : -14 <= i0 <= 16383 and 16i1 <= 14 + i0 and ((16*floor((2 + i0)/16) = 2 + i0 and 14 <= i0 <= 16382 and 16i1 <= -14 + i0) or (-2 <= i0 <= 16381 and 16i1 <= 2 + i0 and 16*floor((2 + i0)/16) <= -12 + i0) or (-5 <= i0 <= 16378 and 16i1 <= 5 + i0 and 16*floor((5 + i0)/16) <= -9 + i0) or (-8 <= i0 <= 16375 and 16i1 <= 8 + i0 and 16*floor((8 + i0)/16) <= -6 + i0) or (-11 <= i0 <= 16372 and 16i1 <= 11 + i0 and 16*floor((11 + i0)/16) <= -3 + i0) or (i0 <= 16369 and 16*floor((14 + i0)/16) <= i0) or (16*floor((14 + i0)/16) = 14 + i0 and 2 <= i0 <= 16370 and 16i1 <= -2 + i0) or (16*floor((11 + i0)/16) = 11 + i0 and 5 <= i0 <= 16373 and 16i1 <= -5 + i0) or (16*floor((8 + i0)/16) = 8 + i0 and 8 <= i0 <= 16376 and 16i1 <= -8 + i0) or (16*floor((5 + i0)/16) = 5 + i0 and 11 <= i0 <= 16379 and 16i1 <= -11 + i0) or (16*floor((-15 + i0)/16) = -15 + i0 and i0 >= 15 and 16i1 <= -15 + i0)) }
; FLAT-NEXT:     Written:  [p_0] -> { [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add123_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -15 + i0 <= 16i1 <= -14 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__conv52_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -7 + i0 <= 16i1 <= -6 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -1 + i0 <= 16i1 <= i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add33_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -5 + i0 <= 16i1 <= -4 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add69_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -9 + i0 <= 16i1 <= -8 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add105_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -13 + i0 <= 16i1 <= -12 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add15_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -3 + i0 <= 16i1 <= -2 + i0; [MemRef_call_i[i0] -> [i1{{\]\]}} -> [Stmt_for_body6_i[i1] -> Val_i8__add87_i_i[{{\]\]}} : 0 <= i1 <= 1023 and -11 + i0 <= 16i1 <= -10 + i0 }
; FLAT-NEXT: }
; FLAT-NEXT: After Statements {
; FLAT-NEXT:     Stmt_for_body6_i
; FLAT-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_1[p_0, i0] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[16i0] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[1 + 16i0] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[2 + 16i0] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[3 + 16i0] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[4 + 16i0] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[5 + 16i0] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[6 + 16i0] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[7 + 16i0] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[8 + 16i0] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[9 + 16i0] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[10 + 16i0] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[11 + 16i0] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[12 + 16i0] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[13 + 16i0] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[14 + 16i0] };
; FLAT-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; FLAT-NEXT:                 [p_0] -> { Stmt_for_body6_i[i0] -> MemRef_call_i[15 + 16i0] };
; FLAT-NEXT: }
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.body6.i => for.end.i' in function 'main':
; FLAT-NEXT: :: isl ast :: main :: %for.body6.i---%for.end.i
;
; FLAT:      if (1)
;
; FLAT:          for (int c0 = 0; c0 <= 1023; c0 += 1)
; FLAT-NEXT:       Stmt_for_body6_i(c0);
;
; FLAT:      else
; FLAT-NEXT:     {  /* original code */ }
;
; FLAT:      Printing analysis 'Polly - Flatten schedule' for region: 'for.cond3.preheader.i => print_array.exit' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'for.cond3.preheader.i => print_array.exit' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'for.cond3.preheader.i => print_array.exit' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Flatten schedule' for region: 'entry => <Function Return>' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - DeLICM/DePRE' for region: 'entry => <Function Return>' in function 'main':
; FLAT-NEXT: Printing analysis 'Polly - Generate an AST from the SCoP (isl)' for region: 'entry => <Function Return>' in function 'main':

; PREIR:      ; ModuleID = '<stdin>'
; PREIR-NEXT: source_filename = "/mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/linear-algebra/kernels/gemm/gemm.c"
; PREIR-NEXT: target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
; PREIR-NEXT: target triple = "x86_64-unknown-linux-gnu"
;
; PREIR:      %struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
; PREIR-NEXT: %struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
;
; PREIR:      @polybench_papi_counters_threadid = local_unnamed_addr global i32 0, align 4
; PREIR-NEXT: @polybench_program_total_flops = local_unnamed_addr global double 0.000000e+00, align 8
; PREIR-NEXT: @polybench_t_start = common local_unnamed_addr global double 0.000000e+00, align 8
; PREIR-NEXT: @polybench_t_end = common local_unnamed_addr global double 0.000000e+00, align 8
; PREIR-NEXT: @.str = private unnamed_addr constant [7 x i8] c"%0.6f\0A\00", align 1
; PREIR-NEXT: @polybench_c_start = common local_unnamed_addr global i64 0, align 8
; PREIR-NEXT: @polybench_c_end = common local_unnamed_addr global i64 0, align 8
; PREIR-NEXT: @stderr = external local_unnamed_addr global %struct._IO_FILE*, align 8
; PREIR-NEXT: @.str.1 = private unnamed_addr constant [51 x i8] c"[PolyBench] posix_memalign: cannot allocate memory\00", align 1
;
; PREIR:      ; Function Attrs: norecurse nounwind readnone uwtable
; PREIR-NEXT: define void @polybench_flush_cache() local_unnamed_addr #0 {
; PREIR-NEXT: entry:
; PREIR-NEXT:   br label %entry.split
;
; PREIR:      entry.split:                                      ; preds = %entry
; PREIR-NEXT:   ret void
; PREIR-NEXT: }
;
; PREIR:      ; Function Attrs: argmemonly nounwind
; PREIR-NEXT: declare void @llvm.lifetime.start(i64, i8* nocapture) #1
;
; PREIR:      ; Function Attrs: nounwind
; PREIR-NEXT: declare noalias i8* @calloc(i64, i64) local_unnamed_addr #2
;
; PREIR:      ; Function Attrs: nounwind
; PREIR-NEXT: declare void @free(i8* nocapture) local_unnamed_addr #2
;
; PREIR:      ; Function Attrs: argmemonly nounwind
; PREIR-NEXT: declare void @llvm.lifetime.end(i64, i8* nocapture) #1
;
; PREIR:      ; Function Attrs: norecurse nounwind readnone uwtable
; PREIR-NEXT: define void @polybench_prepare_instruments() local_unnamed_addr #0 {
; PREIR-NEXT: entry:
; PREIR-NEXT:   br label %entry.split
;
; PREIR:      entry.split:                                      ; preds = %entry
; PREIR-NEXT:   ret void
; PREIR-NEXT: }
;
; PREIR:      ; Function Attrs: norecurse nounwind uwtable
; PREIR-NEXT: define void @polybench_timer_start() local_unnamed_addr #3 {
; PREIR-NEXT: entry:
; PREIR-NEXT:   br label %entry.split
;
; PREIR:      entry.split:                                      ; preds = %entry
; PREIR-NEXT:   store double 0.000000e+00, double* @polybench_t_start, align 8, !tbaa !1
; PREIR-NEXT:   ret void
; PREIR-NEXT: }
;
; PREIR:      ; Function Attrs: norecurse nounwind uwtable
; PREIR-NEXT: define void @polybench_timer_stop() local_unnamed_addr #3 {
; PREIR-NEXT: entry:
; PREIR-NEXT:   br label %entry.split
;
; PREIR:      entry.split:                                      ; preds = %entry
; PREIR-NEXT:   store double 0.000000e+00, double* @polybench_t_end, align 8, !tbaa !1
; PREIR-NEXT:   ret void
; PREIR-NEXT: }
;
; PREIR:      ; Function Attrs: nounwind uwtable
; PREIR-NEXT: define void @polybench_timer_print() local_unnamed_addr #4 {
; PREIR-NEXT: entry:
; PREIR-NEXT:   br label %entry.split
;
; PREIR:      entry.split:                                      ; preds = %entry
; PREIR-NEXT:   %0 = load double, double* @polybench_t_end, align 8, !tbaa !1
; PREIR-NEXT:   %1 = load double, double* @polybench_t_start, align 8, !tbaa !1
; PREIR-NEXT:   %sub = fsub double %0, %1
; PREIR-NEXT:   %call = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i64 0, i64 0), double %sub)
; PREIR-NEXT:   ret void
; PREIR-NEXT: }
;
; PREIR:      ; Function Attrs: nounwind
; PREIR-NEXT: declare i32 @printf(i8* nocapture readonly, ...) local_unnamed_addr #2
;
; PREIR:      ; Function Attrs: nounwind uwtable
; PREIR-NEXT: define i8* @polybench_alloc_data(i64 %n, i32 %elt_size) local_unnamed_addr #4 {
; PREIR-NEXT: entry:
; PREIR-NEXT:   %new.i = alloca i8*, align 8
; PREIR-NEXT:   br label %entry.split
;
; PREIR:      entry.split:                                      ; preds = %entry
; PREIR-NEXT:   %conv = sext i32 %elt_size to i64
; PREIR-NEXT:   %mul = mul i64 %conv, %n
; PREIR-NEXT:   %0 = bitcast i8** %new.i to i8*
; PREIR-NEXT:   call void @llvm.lifetime.start(i64 8, i8* %0) #7
; PREIR-NEXT:   store i8* null, i8** %new.i, align 8, !tbaa !5
; PREIR-NEXT:   %call.i = call i32 @posix_memalign(i8** nonnull %new.i, i64 32, i64 %mul) #7
; PREIR-NEXT:   %1 = load i8*, i8** %new.i, align 8, !tbaa !5
; PREIR-NEXT:   %tobool.i = icmp eq i8* %1, null
; PREIR-NEXT:   %tobool1.i = icmp ne i32 %call.i, 0
; PREIR-NEXT:   %or.cond.i = or i1 %tobool1.i, %tobool.i
; PREIR-NEXT:   br i1 %or.cond.i, label %if.then.i, label %xmalloc.exit
;
; PREIR:      if.then.i:                                        ; preds = %entry.split
; PREIR-NEXT:   %2 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !5
; PREIR-NEXT:   %3 = call i64 @fwrite(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.1, i64 0, i64 0), i64 50, i64 1, %struct._IO_FILE* %2) #9
; PREIR-NEXT:   call void @exit(i32 1) #10
; PREIR-NEXT:   unreachable
;
; PREIR:      xmalloc.exit:                                     ; preds = %entry.split
; PREIR-NEXT:   call void @llvm.lifetime.end(i64 8, i8* %0) #7
; PREIR-NEXT:   ret i8* %1
; PREIR-NEXT: }
;
; PREIR:      ; Function Attrs: nounwind uwtable
; PREIR-NEXT: define i32 @main(i32 %argc, i8** nocapture readnone %argv) local_unnamed_addr #5 {
; PREIR-NEXT: entry:
; PREIR-NEXT:   %conv42.i.s2a = alloca double
; PREIR-NEXT:   %conv19.i.s2a = alloca double
; PREIR-NEXT:   %conv.i.s2a = alloca double
; PREIR-NEXT:   %new.i.i34 = alloca i8*, align 8
; PREIR-NEXT:   %new.i.i27 = alloca i8*, align 8
; PREIR-NEXT:   %new.i.i = alloca i8*, align 8
; PREIR-NEXT:   br label %entry.split
;
; PREIR:      entry.split:                                      ; preds = %entry
; PREIR-NEXT:   %0 = bitcast i8** %new.i.i to i8*
; PREIR-NEXT:   call void @llvm.lifetime.start(i64 8, i8* %0) #7
; PREIR-NEXT:   store i8* null, i8** %new.i.i, align 8, !tbaa !5
; PREIR-NEXT:   %call.i.i = call i32 @posix_memalign(i8** nonnull %new.i.i, i64 32, i64 8388608) #7
; PREIR-NEXT:   %1 = load i8*, i8** %new.i.i, align 8, !tbaa !5
; PREIR-NEXT:   %tobool.i.i = icmp eq i8* %1, null
; PREIR-NEXT:   %tobool1.i.i = icmp ne i32 %call.i.i, 0
; PREIR-NEXT:   %or.cond.i.i = or i1 %tobool1.i.i, %tobool.i.i
; PREIR-NEXT:   br i1 %or.cond.i.i, label %if.then.i.i, label %polybench_alloc_data.exit
;
; PREIR:      if.then.i.i:                                      ; preds = %entry.split
; PREIR-NEXT:   %2 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !5
; PREIR-NEXT:   %3 = call i64 @fwrite(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.1, i64 0, i64 0), i64 50, i64 1, %struct._IO_FILE* %2) #9
; PREIR-NEXT:   call void @exit(i32 1) #10
; PREIR-NEXT:   unreachable
;
; PREIR:      polybench_alloc_data.exit:                        ; preds = %entry.split
; PREIR-NEXT:   call void @llvm.lifetime.end(i64 8, i8* %0) #7
; PREIR-NEXT:   %4 = bitcast i8** %new.i.i27 to i8*
; PREIR-NEXT:   call void @llvm.lifetime.start(i64 8, i8* %4) #7
; PREIR-NEXT:   store i8* null, i8** %new.i.i27, align 8, !tbaa !5
; PREIR-NEXT:   %call.i.i28 = call i32 @posix_memalign(i8** nonnull %new.i.i27, i64 32, i64 8388608) #7
; PREIR-NEXT:   %5 = load i8*, i8** %new.i.i27, align 8, !tbaa !5
; PREIR-NEXT:   %tobool.i.i29 = icmp eq i8* %5, null
; PREIR-NEXT:   %tobool1.i.i30 = icmp ne i32 %call.i.i28, 0
; PREIR-NEXT:   %or.cond.i.i31 = or i1 %tobool1.i.i30, %tobool.i.i29
; PREIR-NEXT:   br i1 %or.cond.i.i31, label %if.then.i.i32, label %polybench_alloc_data.exit33
;
; PREIR:      if.then.i.i32:                                    ; preds = %polybench_alloc_data.exit
; PREIR-NEXT:   %6 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !5
; PREIR-NEXT:   %7 = call i64 @fwrite(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.1, i64 0, i64 0), i64 50, i64 1, %struct._IO_FILE* %6) #9
; PREIR-NEXT:   call void @exit(i32 1) #10
; PREIR-NEXT:   unreachable
;
; PREIR:      polybench_alloc_data.exit33:                      ; preds = %polybench_alloc_data.exit
; PREIR-NEXT:   call void @llvm.lifetime.end(i64 8, i8* %4) #7
; PREIR-NEXT:   %8 = bitcast i8** %new.i.i34 to i8*
; PREIR-NEXT:   call void @llvm.lifetime.start(i64 8, i8* %8) #7
; PREIR-NEXT:   store i8* null, i8** %new.i.i34, align 8, !tbaa !5
; PREIR-NEXT:   %call.i.i35 = call i32 @posix_memalign(i8** nonnull %new.i.i34, i64 32, i64 8388608) #7
; PREIR-NEXT:   %9 = load i8*, i8** %new.i.i34, align 8, !tbaa !5
; PREIR-NEXT:   %tobool.i.i36 = icmp eq i8* %9, null
; PREIR-NEXT:   %tobool1.i.i37 = icmp ne i32 %call.i.i35, 0
; PREIR-NEXT:   %or.cond.i.i38 = or i1 %tobool1.i.i37, %tobool.i.i36
; PREIR-NEXT:   br i1 %or.cond.i.i38, label %if.then.i.i39, label %polybench_alloc_data.exit40
;
; PREIR:      if.then.i.i39:                                    ; preds = %polybench_alloc_data.exit33
; PREIR-NEXT:   %10 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !5
; PREIR-NEXT:   %11 = call i64 @fwrite(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.1, i64 0, i64 0), i64 50, i64 1, %struct._IO_FILE* %10) #9
; PREIR-NEXT:   call void @exit(i32 1) #10
; PREIR-NEXT:   unreachable
;
; PREIR:      polybench_alloc_data.exit40:                      ; preds = %polybench_alloc_data.exit33
; PREIR-NEXT:   call void @llvm.lifetime.end(i64 8, i8* %8) #7
; PREIR-NEXT:   %arraydecay = bitcast i8* %1 to [1024 x double]*
; PREIR-NEXT:   %arraydecay3 = bitcast i8* %5 to [1024 x double]*
; PREIR-NEXT:   br label %polly.split_new_and_old
;
; PREIR:      polly.split_new_and_old:                          ; preds = %polybench_alloc_data.exit40
; PREIR-NEXT:   %polly.access.cast. = bitcast i8* %9 to double*
; PREIR-NEXT:   %polly.access.mul. = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 1023, i64 1024)
; PREIR-NEXT:   %polly.access.mul..obit = extractvalue { i64, i1 } %polly.access.mul., 1
; PREIR-NEXT:   %polly.overflow.state = or i1 false, %polly.access.mul..obit
; PREIR-NEXT:   %polly.access.mul..res = extractvalue { i64, i1 } %polly.access.mul., 0
; PREIR-NEXT:   %polly.access.add. = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res, i64 1024)
; PREIR-NEXT:   %polly.access.add..obit = extractvalue { i64, i1 } %polly.access.add., 1
; PREIR-NEXT:   %polly.overflow.state1 = or i1 %polly.overflow.state, %polly.access.add..obit
; PREIR-NEXT:   %polly.access.add..res = extractvalue { i64, i1 } %polly.access.add., 0
; PREIR-NEXT:   %polly.access. = getelementptr double, double* %polly.access.cast., i64 %polly.access.add..res
; PREIR-NEXT:   %polly.access.cast.2 = bitcast i8* %5 to double*
; PREIR-NEXT:   %polly.access.mul.3 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 0, i64 1024)
; PREIR-NEXT:   %polly.access.mul..obit4 = extractvalue { i64, i1 } %polly.access.mul.3, 1
; PREIR-NEXT:   %polly.overflow.state5 = or i1 %polly.overflow.state1, %polly.access.mul..obit4
; PREIR-NEXT:   %polly.access.mul..res6 = extractvalue { i64, i1 } %polly.access.mul.3, 0
; PREIR-NEXT:   %polly.access.add.7 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res6, i64 0)
; PREIR-NEXT:   %polly.access.add..obit8 = extractvalue { i64, i1 } %polly.access.add.7, 1
; PREIR-NEXT:   %polly.overflow.state9 = or i1 %polly.overflow.state5, %polly.access.add..obit8
; PREIR-NEXT:   %polly.access.add..res10 = extractvalue { i64, i1 } %polly.access.add.7, 0
; PREIR-NEXT:   %polly.access.11 = getelementptr double, double* %polly.access.cast.2, i64 %polly.access.add..res10
; PREIR-NEXT:   %12 = ptrtoint double* %polly.access. to i64
; PREIR-NEXT:   %13 = ptrtoint double* %polly.access.11 to i64
; PREIR-NEXT:   %14 = icmp ule i64 %12, %13
; PREIR-NEXT:   %polly.access.cast.12 = bitcast i8* %5 to double*
; PREIR-NEXT:   %polly.access.mul.13 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 1023, i64 1024)
; PREIR-NEXT:   %polly.access.mul..obit14 = extractvalue { i64, i1 } %polly.access.mul.13, 1
; PREIR-NEXT:   %polly.overflow.state15 = or i1 %polly.overflow.state9, %polly.access.mul..obit14
; PREIR-NEXT:   %polly.access.mul..res16 = extractvalue { i64, i1 } %polly.access.mul.13, 0
; PREIR-NEXT:   %polly.access.add.17 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res16, i64 1024)
; PREIR-NEXT:   %polly.access.add..obit18 = extractvalue { i64, i1 } %polly.access.add.17, 1
; PREIR-NEXT:   %polly.overflow.state19 = or i1 %polly.overflow.state15, %polly.access.add..obit18
; PREIR-NEXT:   %polly.access.add..res20 = extractvalue { i64, i1 } %polly.access.add.17, 0
; PREIR-NEXT:   %polly.access.21 = getelementptr double, double* %polly.access.cast.12, i64 %polly.access.add..res20
; PREIR-NEXT:   %polly.access.cast.22 = bitcast i8* %9 to double*
; PREIR-NEXT:   %polly.access.mul.23 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 0, i64 1024)
; PREIR-NEXT:   %polly.access.mul..obit24 = extractvalue { i64, i1 } %polly.access.mul.23, 1
; PREIR-NEXT:   %polly.overflow.state25 = or i1 %polly.overflow.state19, %polly.access.mul..obit24
; PREIR-NEXT:   %polly.access.mul..res26 = extractvalue { i64, i1 } %polly.access.mul.23, 0
; PREIR-NEXT:   %polly.access.add.27 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res26, i64 0)
; PREIR-NEXT:   %polly.access.add..obit28 = extractvalue { i64, i1 } %polly.access.add.27, 1
; PREIR-NEXT:   %polly.overflow.state29 = or i1 %polly.overflow.state25, %polly.access.add..obit28
; PREIR-NEXT:   %polly.access.add..res30 = extractvalue { i64, i1 } %polly.access.add.27, 0
; PREIR-NEXT:   %polly.access.31 = getelementptr double, double* %polly.access.cast.22, i64 %polly.access.add..res30
; PREIR-NEXT:   %15 = ptrtoint double* %polly.access.21 to i64
; PREIR-NEXT:   %16 = ptrtoint double* %polly.access.31 to i64
; PREIR-NEXT:   %17 = icmp ule i64 %15, %16
; PREIR-NEXT:   %18 = or i1 %14, %17
; PREIR-NEXT:   %19 = and i1 true, %18
; PREIR-NEXT:   %polly.access.cast.32 = bitcast i8* %1 to double*
; PREIR-NEXT:   %polly.access.mul.33 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 1023, i64 1024)
; PREIR-NEXT:   %polly.access.mul..obit34 = extractvalue { i64, i1 } %polly.access.mul.33, 1
; PREIR-NEXT:   %polly.overflow.state35 = or i1 %polly.overflow.state29, %polly.access.mul..obit34
; PREIR-NEXT:   %polly.access.mul..res36 = extractvalue { i64, i1 } %polly.access.mul.33, 0
; PREIR-NEXT:   %polly.access.add.37 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res36, i64 1024)
; PREIR-NEXT:   %polly.access.add..obit38 = extractvalue { i64, i1 } %polly.access.add.37, 1
; PREIR-NEXT:   %polly.overflow.state39 = or i1 %polly.overflow.state35, %polly.access.add..obit38
; PREIR-NEXT:   %polly.access.add..res40 = extractvalue { i64, i1 } %polly.access.add.37, 0
; PREIR-NEXT:   %polly.access.41 = getelementptr double, double* %polly.access.cast.32, i64 %polly.access.add..res40
; PREIR-NEXT:   %polly.access.cast.42 = bitcast i8* %5 to double*
; PREIR-NEXT:   %polly.access.mul.43 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 0, i64 1024)
; PREIR-NEXT:   %polly.access.mul..obit44 = extractvalue { i64, i1 } %polly.access.mul.43, 1
; PREIR-NEXT:   %polly.overflow.state45 = or i1 %polly.overflow.state39, %polly.access.mul..obit44
; PREIR-NEXT:   %polly.access.mul..res46 = extractvalue { i64, i1 } %polly.access.mul.43, 0
; PREIR-NEXT:   %polly.access.add.47 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res46, i64 0)
; PREIR-NEXT:   %polly.access.add..obit48 = extractvalue { i64, i1 } %polly.access.add.47, 1
; PREIR-NEXT:   %polly.overflow.state49 = or i1 %polly.overflow.state45, %polly.access.add..obit48
; PREIR-NEXT:   %polly.access.add..res50 = extractvalue { i64, i1 } %polly.access.add.47, 0
; PREIR-NEXT:   %polly.access.51 = getelementptr double, double* %polly.access.cast.42, i64 %polly.access.add..res50
; PREIR-NEXT:   %20 = ptrtoint double* %polly.access.41 to i64
; PREIR-NEXT:   %21 = ptrtoint double* %polly.access.51 to i64
; PREIR-NEXT:   %22 = icmp ule i64 %20, %21
; PREIR-NEXT:   %polly.access.cast.52 = bitcast i8* %5 to double*
; PREIR-NEXT:   %polly.access.mul.53 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 1023, i64 1024)
; PREIR-NEXT:   %polly.access.mul..obit54 = extractvalue { i64, i1 } %polly.access.mul.53, 1
; PREIR-NEXT:   %polly.overflow.state55 = or i1 %polly.overflow.state49, %polly.access.mul..obit54
; PREIR-NEXT:   %polly.access.mul..res56 = extractvalue { i64, i1 } %polly.access.mul.53, 0
; PREIR-NEXT:   %polly.access.add.57 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res56, i64 1024)
; PREIR-NEXT:   %polly.access.add..obit58 = extractvalue { i64, i1 } %polly.access.add.57, 1
; PREIR-NEXT:   %polly.overflow.state59 = or i1 %polly.overflow.state55, %polly.access.add..obit58
; PREIR-NEXT:   %polly.access.add..res60 = extractvalue { i64, i1 } %polly.access.add.57, 0
; PREIR-NEXT:   %polly.access.61 = getelementptr double, double* %polly.access.cast.52, i64 %polly.access.add..res60
; PREIR-NEXT:   %polly.access.cast.62 = bitcast i8* %1 to double*
; PREIR-NEXT:   %polly.access.mul.63 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 0, i64 1024)
; PREIR-NEXT:   %polly.access.mul..obit64 = extractvalue { i64, i1 } %polly.access.mul.63, 1
; PREIR-NEXT:   %polly.overflow.state65 = or i1 %polly.overflow.state59, %polly.access.mul..obit64
; PREIR-NEXT:   %polly.access.mul..res66 = extractvalue { i64, i1 } %polly.access.mul.63, 0
; PREIR-NEXT:   %polly.access.add.67 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res66, i64 0)
; PREIR-NEXT:   %polly.access.add..obit68 = extractvalue { i64, i1 } %polly.access.add.67, 1
; PREIR-NEXT:   %polly.overflow.state69 = or i1 %polly.overflow.state65, %polly.access.add..obit68
; PREIR-NEXT:   %polly.access.add..res70 = extractvalue { i64, i1 } %polly.access.add.67, 0
; PREIR-NEXT:   %polly.access.71 = getelementptr double, double* %polly.access.cast.62, i64 %polly.access.add..res70
; PREIR-NEXT:   %23 = ptrtoint double* %polly.access.61 to i64
; PREIR-NEXT:   %24 = ptrtoint double* %polly.access.71 to i64
; PREIR-NEXT:   %25 = icmp ule i64 %23, %24
; PREIR-NEXT:   %26 = or i1 %22, %25
; PREIR-NEXT:   %27 = and i1 %19, %26
; PREIR-NEXT:   %polly.access.cast.72 = bitcast i8* %1 to double*
; PREIR-NEXT:   %polly.access.mul.73 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 1023, i64 1024)
; PREIR-NEXT:   %polly.access.mul..obit74 = extractvalue { i64, i1 } %polly.access.mul.73, 1
; PREIR-NEXT:   %polly.overflow.state75 = or i1 %polly.overflow.state69, %polly.access.mul..obit74
; PREIR-NEXT:   %polly.access.mul..res76 = extractvalue { i64, i1 } %polly.access.mul.73, 0
; PREIR-NEXT:   %polly.access.add.77 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res76, i64 1024)
; PREIR-NEXT:   %polly.access.add..obit78 = extractvalue { i64, i1 } %polly.access.add.77, 1
; PREIR-NEXT:   %polly.overflow.state79 = or i1 %polly.overflow.state75, %polly.access.add..obit78
; PREIR-NEXT:   %polly.access.add..res80 = extractvalue { i64, i1 } %polly.access.add.77, 0
; PREIR-NEXT:   %polly.access.81 = getelementptr double, double* %polly.access.cast.72, i64 %polly.access.add..res80
; PREIR-NEXT:   %polly.access.cast.82 = bitcast i8* %9 to double*
; PREIR-NEXT:   %polly.access.mul.83 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 0, i64 1024)
; PREIR-NEXT:   %polly.access.mul..obit84 = extractvalue { i64, i1 } %polly.access.mul.83, 1
; PREIR-NEXT:   %polly.overflow.state85 = or i1 %polly.overflow.state79, %polly.access.mul..obit84
; PREIR-NEXT:   %polly.access.mul..res86 = extractvalue { i64, i1 } %polly.access.mul.83, 0
; PREIR-NEXT:   %polly.access.add.87 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res86, i64 0)
; PREIR-NEXT:   %polly.access.add..obit88 = extractvalue { i64, i1 } %polly.access.add.87, 1
; PREIR-NEXT:   %polly.overflow.state89 = or i1 %polly.overflow.state85, %polly.access.add..obit88
; PREIR-NEXT:   %polly.access.add..res90 = extractvalue { i64, i1 } %polly.access.add.87, 0
; PREIR-NEXT:   %polly.access.91 = getelementptr double, double* %polly.access.cast.82, i64 %polly.access.add..res90
; PREIR-NEXT:   %28 = ptrtoint double* %polly.access.81 to i64
; PREIR-NEXT:   %29 = ptrtoint double* %polly.access.91 to i64
; PREIR-NEXT:   %30 = icmp ule i64 %28, %29
; PREIR-NEXT:   %polly.access.cast.92 = bitcast i8* %9 to double*
; PREIR-NEXT:   %polly.access.mul.93 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 1023, i64 1024)
; PREIR-NEXT:   %polly.access.mul..obit94 = extractvalue { i64, i1 } %polly.access.mul.93, 1
; PREIR-NEXT:   %polly.overflow.state95 = or i1 %polly.overflow.state89, %polly.access.mul..obit94
; PREIR-NEXT:   %polly.access.mul..res96 = extractvalue { i64, i1 } %polly.access.mul.93, 0
; PREIR-NEXT:   %polly.access.add.97 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res96, i64 1024)
; PREIR-NEXT:   %polly.access.add..obit98 = extractvalue { i64, i1 } %polly.access.add.97, 1
; PREIR-NEXT:   %polly.overflow.state99 = or i1 %polly.overflow.state95, %polly.access.add..obit98
; PREIR-NEXT:   %polly.access.add..res100 = extractvalue { i64, i1 } %polly.access.add.97, 0
; PREIR-NEXT:   %polly.access.101 = getelementptr double, double* %polly.access.cast.92, i64 %polly.access.add..res100
; PREIR-NEXT:   %polly.access.cast.102 = bitcast i8* %1 to double*
; PREIR-NEXT:   %polly.access.mul.103 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 0, i64 1024)
; PREIR-NEXT:   %polly.access.mul..obit104 = extractvalue { i64, i1 } %polly.access.mul.103, 1
; PREIR-NEXT:   %polly.overflow.state105 = or i1 %polly.overflow.state99, %polly.access.mul..obit104
; PREIR-NEXT:   %polly.access.mul..res106 = extractvalue { i64, i1 } %polly.access.mul.103, 0
; PREIR-NEXT:   %polly.access.add.107 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res106, i64 0)
; PREIR-NEXT:   %polly.access.add..obit108 = extractvalue { i64, i1 } %polly.access.add.107, 1
; PREIR-NEXT:   %polly.overflow.state109 = or i1 %polly.overflow.state105, %polly.access.add..obit108
; PREIR-NEXT:   %polly.access.add..res110 = extractvalue { i64, i1 } %polly.access.add.107, 0
; PREIR-NEXT:   %polly.access.111 = getelementptr double, double* %polly.access.cast.102, i64 %polly.access.add..res110
; PREIR-NEXT:   %31 = ptrtoint double* %polly.access.101 to i64
; PREIR-NEXT:   %32 = ptrtoint double* %polly.access.111 to i64
; PREIR-NEXT:   %33 = icmp ule i64 %31, %32
; PREIR-NEXT:   %34 = or i1 %30, %33
; PREIR-NEXT:   %35 = and i1 %27, %34
; PREIR-NEXT:   %polly.rtc.overflown = xor i1 %polly.overflow.state109, true
; PREIR-NEXT:   %polly.rtc.result = and i1 %35, %polly.rtc.overflown
; PREIR-NEXT:   br i1 %polly.rtc.result, label %polly.start, label %for.cond1.preheader.i
;
; PREIR:      for.cond1.preheader.i:                            ; preds = %polly.split_new_and_old, %for.inc8.i
; PREIR-NEXT:   %indvars.iv19.i = phi i64 [ %indvars.iv.next20.i, %for.inc8.i ], [ 0, %polly.split_new_and_old ]
; PREIR-NEXT:   %36 = trunc i64 %indvars.iv19.i to i32
; PREIR-NEXT:   %conv.i = sitofp i32 %36 to double
; PREIR-NEXT:   br label %for.body3.i
;
; PREIR:      for.body3.i:                                      ; preds = %for.body3.i, %for.cond1.preheader.i
; PREIR-NEXT:   %indvars.iv16.i = phi i64 [ 0, %for.cond1.preheader.i ], [ %indvars.iv.next17.i, %for.body3.i ]
; PREIR-NEXT:   %37 = trunc i64 %indvars.iv16.i to i32
; PREIR-NEXT:   %conv4.i = sitofp i32 %37 to double
; PREIR-NEXT:   %mul.i = fmul double %conv.i, %conv4.i
; PREIR-NEXT:   %div.i = fmul double %mul.i, 9.765625e-04
; PREIR-NEXT:   %arrayidx7.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay, i64 %indvars.iv19.i, i64 %indvars.iv16.i
; PREIR-NEXT:   store double %div.i, double* %arrayidx7.i, align 8, !tbaa !1
; PREIR-NEXT:   %indvars.iv.next17.i = add nuw nsw i64 %indvars.iv16.i, 1
; PREIR-NEXT:   %exitcond18.i = icmp eq i64 %indvars.iv.next17.i, 1024
; PREIR-NEXT:   br i1 %exitcond18.i, label %for.inc8.i, label %for.body3.i
;
; PREIR:      for.inc8.i:                                       ; preds = %for.body3.i
; PREIR-NEXT:   %indvars.iv.next20.i = add nuw nsw i64 %indvars.iv19.i, 1
; PREIR-NEXT:   %exitcond21.i = icmp eq i64 %indvars.iv.next20.i, 1024
; PREIR-NEXT:   br i1 %exitcond21.i, label %for.cond15.preheader.i.preheader, label %for.cond1.preheader.i
;
; PREIR:      for.cond15.preheader.i.preheader:                 ; preds = %for.inc8.i
; PREIR-NEXT:   %arraydecay4 = bitcast i8* %9 to [1024 x double]*
; PREIR-NEXT:   br label %for.cond15.preheader.i
;
; PREIR:      for.cond15.preheader.i:                           ; preds = %for.inc31.i, %for.cond15.preheader.i.preheader
; PREIR-NEXT:   %indvars.iv13.i = phi i64 [ %indvars.iv.next14.i, %for.inc31.i ], [ 0, %for.cond15.preheader.i.preheader ]
; PREIR-NEXT:   %38 = trunc i64 %indvars.iv13.i to i32
; PREIR-NEXT:   %conv19.i = sitofp i32 %38 to double
; PREIR-NEXT:   br label %for.body18.i
;
; PREIR:      for.body18.i:                                     ; preds = %for.body18.i, %for.cond15.preheader.i
; PREIR-NEXT:   %indvars.iv10.i = phi i64 [ 0, %for.cond15.preheader.i ], [ %indvars.iv.next11.i, %for.body18.i ]
; PREIR-NEXT:   %39 = trunc i64 %indvars.iv10.i to i32
; PREIR-NEXT:   %conv20.i = sitofp i32 %39 to double
; PREIR-NEXT:   %mul21.i = fmul double %conv19.i, %conv20.i
; PREIR-NEXT:   %div23.i = fmul double %mul21.i, 9.765625e-04
; PREIR-NEXT:   %arrayidx27.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay3, i64 %indvars.iv13.i, i64 %indvars.iv10.i
; PREIR-NEXT:   store double %div23.i, double* %arrayidx27.i, align 8, !tbaa !1
; PREIR-NEXT:   %indvars.iv.next11.i = add nuw nsw i64 %indvars.iv10.i, 1
; PREIR-NEXT:   %exitcond12.i = icmp eq i64 %indvars.iv.next11.i, 1024
; PREIR-NEXT:   br i1 %exitcond12.i, label %for.inc31.i, label %for.body18.i
;
; PREIR:      for.inc31.i:                                      ; preds = %for.body18.i
; PREIR-NEXT:   %indvars.iv.next14.i = add nuw nsw i64 %indvars.iv13.i, 1
; PREIR-NEXT:   %exitcond15.i = icmp eq i64 %indvars.iv.next14.i, 1024
; PREIR-NEXT:   br i1 %exitcond15.i, label %for.cond38.preheader.i, label %for.cond15.preheader.i
;
; PREIR:      for.cond38.preheader.i:                           ; preds = %for.inc54.i, %for.inc31.i
; PREIR-NEXT:   %indvars.iv7.i = phi i64 [ %indvars.iv.next8.i, %for.inc54.i ], [ 0, %for.inc31.i ]
; PREIR-NEXT:   %40 = trunc i64 %indvars.iv7.i to i32
; PREIR-NEXT:   %conv42.i = sitofp i32 %40 to double
; PREIR-NEXT:   br label %for.body41.i
;
; PREIR:      for.body41.i:                                     ; preds = %for.body41.i, %for.cond38.preheader.i
; PREIR-NEXT:   %indvars.iv.i = phi i64 [ 0, %for.cond38.preheader.i ], [ %indvars.iv.next.i, %for.body41.i ]
; PREIR-NEXT:   %41 = trunc i64 %indvars.iv.i to i32
; PREIR-NEXT:   %conv43.i = sitofp i32 %41 to double
; PREIR-NEXT:   %mul44.i = fmul double %conv42.i, %conv43.i
; PREIR-NEXT:   %div46.i = fmul double %mul44.i, 9.765625e-04
; PREIR-NEXT:   %arrayidx50.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay4, i64 %indvars.iv7.i, i64 %indvars.iv.i
; PREIR-NEXT:   store double %div46.i, double* %arrayidx50.i, align 8, !tbaa !1
; PREIR-NEXT:   %indvars.iv.next.i = add nuw nsw i64 %indvars.iv.i, 1
; PREIR-NEXT:   %exitcond.i = icmp eq i64 %indvars.iv.next.i, 1024
; PREIR-NEXT:   br i1 %exitcond.i, label %for.inc54.i, label %for.body41.i
;
; PREIR:      for.inc54.i:                                      ; preds = %for.body41.i
; PREIR-NEXT:   %indvars.iv.next8.i = add nuw nsw i64 %indvars.iv7.i, 1
; PREIR-NEXT:   %exitcond9.i = icmp eq i64 %indvars.iv.next8.i, 1024
; PREIR-NEXT:   br i1 %exitcond9.i, label %for.cond1.preheader.i42, label %for.cond38.preheader.i
;
; PREIR:      for.cond1.preheader.i42:                          ; preds = %for.inc26.i, %for.inc54.i
; PREIR-NEXT:   %indvars.iv7.i41 = phi i64 [ %indvars.iv.next8.i48, %for.inc26.i ], [ 0, %for.inc54.i ]
; PREIR-NEXT:   br label %for.body3.i44
;
; PREIR:      for.body3.i44:                                    ; preds = %for.inc23.i, %for.cond1.preheader.i42
; PREIR-NEXT:   %indvars.iv4.i = phi i64 [ 0, %for.cond1.preheader.i42 ], [ %indvars.iv.next5.i, %for.inc23.i ]
; PREIR-NEXT:   %arrayidx5.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay, i64 %indvars.iv7.i41, i64 %indvars.iv4.i
; PREIR-NEXT:   %42 = load double, double* %arrayidx5.i, align 8, !tbaa !1
; PREIR-NEXT:   %mul.i43 = fmul double %42, 2.123000e+03
; PREIR-NEXT:   store double %mul.i43, double* %arrayidx5.i, align 8, !tbaa !1
; PREIR-NEXT:   br label %for.body8.i
;
; PREIR:      for.body8.i:                                      ; preds = %for.body8.i, %for.body3.i44
; PREIR-NEXT:   %43 = phi double [ %mul.i43, %for.body3.i44 ], [ %add.i, %for.body8.i ]
; PREIR-NEXT:   %indvars.iv.i45 = phi i64 [ 0, %for.body3.i44 ], [ %indvars.iv.next.i46, %for.body8.i ]
; PREIR-NEXT:   %arrayidx12.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay3, i64 %indvars.iv7.i41, i64 %indvars.iv.i45
; PREIR-NEXT:   %44 = load double, double* %arrayidx12.i, align 8, !tbaa !1
; PREIR-NEXT:   %mul13.i = fmul double %44, 3.241200e+04
; PREIR-NEXT:   %arrayidx17.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay4, i64 %indvars.iv.i45, i64 %indvars.iv4.i
; PREIR-NEXT:   %45 = load double, double* %arrayidx17.i, align 8, !tbaa !1
; PREIR-NEXT:   %mul18.i = fmul double %mul13.i, %45
; PREIR-NEXT:   %add.i = fadd double %43, %mul18.i
; PREIR-NEXT:   store double %add.i, double* %arrayidx5.i, align 8, !tbaa !1
; PREIR-NEXT:   %indvars.iv.next.i46 = add nuw nsw i64 %indvars.iv.i45, 1
; PREIR-NEXT:   %exitcond.i47 = icmp eq i64 %indvars.iv.next.i46, 1024
; PREIR-NEXT:   br i1 %exitcond.i47, label %for.inc23.i, label %for.body8.i
;
; PREIR:      for.inc23.i:                                      ; preds = %for.body8.i
; PREIR-NEXT:   %indvars.iv.next5.i = add nuw nsw i64 %indvars.iv4.i, 1
; PREIR-NEXT:   %exitcond6.i = icmp eq i64 %indvars.iv.next5.i, 1024
; PREIR-NEXT:   br i1 %exitcond6.i, label %for.inc26.i, label %for.body3.i44
;
; PREIR:      for.inc26.i:                                      ; preds = %for.inc23.i
; PREIR-NEXT:   %indvars.iv.next8.i48 = add nuw nsw i64 %indvars.iv7.i41, 1
; PREIR-NEXT:   %exitcond9.i49 = icmp eq i64 %indvars.iv.next8.i48, 1024
; PREIR-NEXT:   br i1 %exitcond9.i49, label %polly.merge_new_and_old, label %for.cond1.preheader.i42
;
; PREIR:      polly.merge_new_and_old:                          ; preds = %polly.exiting, %for.inc26.i
; PREIR-NEXT:   br label %kernel_gemm.exit
;
; PREIR:      kernel_gemm.exit:                                 ; preds = %polly.merge_new_and_old
; PREIR-NEXT:   %call.i = call noalias i8* @malloc(i64 16385) #7
; PREIR-NEXT:   %arrayidx.i = getelementptr inbounds i8, i8* %call.i, i64 16384
; PREIR-NEXT:   store i8 0, i8* %arrayidx.i, align 1, !tbaa !7
; PREIR-NEXT:   %scevgep209 = getelementptr i8, i8* %call.i, i64 1
; PREIR-NEXT:   %scevgep211 = getelementptr i8, i8* %call.i, i64 2
; PREIR-NEXT:   %scevgep213 = getelementptr i8, i8* %call.i, i64 3
; PREIR-NEXT:   %scevgep215 = getelementptr i8, i8* %call.i, i64 4
; PREIR-NEXT:   %scevgep217 = getelementptr i8, i8* %call.i, i64 5
; PREIR-NEXT:   %scevgep219 = getelementptr i8, i8* %call.i, i64 6
; PREIR-NEXT:   %scevgep221 = getelementptr i8, i8* %call.i, i64 7
; PREIR-NEXT:   %scevgep223 = getelementptr i8, i8* %call.i, i64 8
; PREIR-NEXT:   %scevgep225 = getelementptr i8, i8* %call.i, i64 9
; PREIR-NEXT:   %scevgep227 = getelementptr i8, i8* %call.i, i64 10
; PREIR-NEXT:   %scevgep229 = getelementptr i8, i8* %call.i, i64 11
; PREIR-NEXT:   %scevgep231 = getelementptr i8, i8* %call.i, i64 12
; PREIR-NEXT:   %scevgep233 = getelementptr i8, i8* %call.i, i64 13
; PREIR-NEXT:   %scevgep235 = getelementptr i8, i8* %call.i, i64 14
; PREIR-NEXT:   %scevgep237 = getelementptr i8, i8* %call.i, i64 15
; PREIR-NEXT:   br label %for.cond3.preheader.i
;
; PREIR:      for.cond3.preheader.i:                            ; preds = %for.end.i, %kernel_gemm.exit
; PREIR-NEXT:   %indvars.iv4.i50 = phi i64 [ 0, %kernel_gemm.exit ], [ %indvars.iv.next5.i54, %for.end.i ]
; PREIR-NEXT:   %46 = shl i64 %indvars.iv4.i50, 0
; PREIR-NEXT:   %47 = add i64 %46, 0
; PREIR-NEXT:   br label %polly.split_new_and_old194
;
; PREIR:      polly.split_new_and_old194:                       ; preds = %for.cond3.preheader.i
; PREIR-NEXT:   br i1 true, label %polly.start196, label %for.body6.i
;
; PREIR:      for.body6.i:                                      ; preds = %polly.split_new_and_old194, %for.body6.i
; PREIR-NEXT:   %indvars.iv.i51 = phi i64 [ %indvars.iv.next.i52, %for.body6.i ], [ 0, %polly.split_new_and_old194 ]
; PREIR-NEXT:   %arrayidx10.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay, i64 %indvars.iv4.i50, i64 %indvars.iv.i51
; PREIR-NEXT:   %48 = bitcast double* %arrayidx10.i to i64*
; PREIR-NEXT:   %49 = load i64, i64* %48, align 8, !tbaa !1
; PREIR-NEXT:   %50 = shl nsw i64 %indvars.iv.i51, 4
; PREIR-NEXT:   %block.sroa.0.0.extract.trunc138.i.i = trunc i64 %49 to i8
; PREIR-NEXT:   %and.i.i = and i8 %block.sroa.0.0.extract.trunc138.i.i, 15
; PREIR-NEXT:   %add.i.i = or i8 %and.i.i, 48
; PREIR-NEXT:   %add.ptr.i.i = getelementptr inbounds i8, i8* %call.i, i64 %50
; PREIR-NEXT:   store i8 %add.i.i, i8* %add.ptr.i.i, align 1, !tbaa !7
; PREIR-NEXT:   %add.ptr10.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 1
; PREIR-NEXT:   store i8 %add.i.i, i8* %add.ptr10.i.i, align 1, !tbaa !7
; PREIR-NEXT:   %block.sroa.0.1.extract.shift.i.i = lshr i64 %49, 8
; PREIR-NEXT:   %conv13195.i.i = trunc i64 %block.sroa.0.1.extract.shift.i.i to i8
; PREIR-NEXT:   %and14.i.i = and i8 %conv13195.i.i, 15
; PREIR-NEXT:   %add15.i.i = or i8 %and14.i.i, 48
; PREIR-NEXT:   %add.ptr19.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 2
; PREIR-NEXT:   store i8 %add15.i.i, i8* %add.ptr19.i.i, align 1, !tbaa !7
; PREIR-NEXT:   %add.ptr28.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 3
; PREIR-NEXT:   store i8 %add15.i.i, i8* %add.ptr28.i.i, align 1, !tbaa !7
; PREIR-NEXT:   %block.sroa.0.2.extract.shift.i.i = lshr i64 %49, 16
; PREIR-NEXT:   %conv31201.i.i = trunc i64 %block.sroa.0.2.extract.shift.i.i to i8
; PREIR-NEXT:   %and32.i.i = and i8 %conv31201.i.i, 15
; PREIR-NEXT:   %add33.i.i = or i8 %and32.i.i, 48
; PREIR-NEXT:   %add.ptr37.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 4
; PREIR-NEXT:   store i8 %add33.i.i, i8* %add.ptr37.i.i, align 1, !tbaa !7
; PREIR-NEXT:   %add.ptr46.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 5
; PREIR-NEXT:   store i8 %add33.i.i, i8* %add.ptr46.i.i, align 1, !tbaa !7
; PREIR-NEXT:   %.tr.i.i = trunc i64 %49 to i32
; PREIR-NEXT:   %sext204207.i.i = lshr i32 %.tr.i.i, 24
; PREIR-NEXT:   %and50.i.i = and i32 %sext204207.i.i, 15
; PREIR-NEXT:   %add51.i.i = or i32 %and50.i.i, 48
; PREIR-NEXT:   %conv52.i.i = trunc i32 %add51.i.i to i8
; PREIR-NEXT:   %add.ptr55.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 6
; PREIR-NEXT:   store i8 %conv52.i.i, i8* %add.ptr55.i.i, align 1, !tbaa !7
; PREIR-NEXT:   %add.ptr64.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 7
; PREIR-NEXT:   store i8 %conv52.i.i, i8* %add.ptr64.i.i, align 1, !tbaa !7
; PREIR-NEXT:   %block.sroa.0.4.extract.shift.i.i = lshr i64 %49, 32
; PREIR-NEXT:   %conv67211.i.i = trunc i64 %block.sroa.0.4.extract.shift.i.i to i8
; PREIR-NEXT:   %and68.i.i = and i8 %conv67211.i.i, 15
; PREIR-NEXT:   %add69.i.i = or i8 %and68.i.i, 48
; PREIR-NEXT:   %add.ptr73.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 8
; PREIR-NEXT:   store i8 %add69.i.i, i8* %add.ptr73.i.i, align 1, !tbaa !7
; PREIR-NEXT:   %add.ptr82.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 9
; PREIR-NEXT:   store i8 %add69.i.i, i8* %add.ptr82.i.i, align 1, !tbaa !7
; PREIR-NEXT:   %block.sroa.0.5.extract.shift.i.i = lshr i64 %49, 40
; PREIR-NEXT:   %conv85217.i.i = trunc i64 %block.sroa.0.5.extract.shift.i.i to i8
; PREIR-NEXT:   %and86.i.i = and i8 %conv85217.i.i, 15
; PREIR-NEXT:   %add87.i.i = or i8 %and86.i.i, 48
; PREIR-NEXT:   %add.ptr91.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 10
; PREIR-NEXT:   store i8 %add87.i.i, i8* %add.ptr91.i.i, align 1, !tbaa !7
; PREIR-NEXT:   %add.ptr100.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 11
; PREIR-NEXT:   store i8 %add87.i.i, i8* %add.ptr100.i.i, align 1, !tbaa !7
; PREIR-NEXT:   %block.sroa.0.6.extract.shift.i.i = lshr i64 %49, 48
; PREIR-NEXT:   %conv103223.i.i = trunc i64 %block.sroa.0.6.extract.shift.i.i to i8
; PREIR-NEXT:   %and104.i.i = and i8 %conv103223.i.i, 15
; PREIR-NEXT:   %add105.i.i = or i8 %and104.i.i, 48
; PREIR-NEXT:   %add.ptr109.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 12
; PREIR-NEXT:   store i8 %add105.i.i, i8* %add.ptr109.i.i, align 1, !tbaa !7
; PREIR-NEXT:   %add.ptr118.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 13
; PREIR-NEXT:   store i8 %add105.i.i, i8* %add.ptr118.i.i, align 1, !tbaa !7
; PREIR-NEXT:   %block.sroa.0.7.extract.shift.i.i = lshr i64 %49, 56
; PREIR-NEXT:   %conv121229.i.i = trunc i64 %block.sroa.0.7.extract.shift.i.i to i8
; PREIR-NEXT:   %and122.i.i = and i8 %conv121229.i.i, 15
; PREIR-NEXT:   %add123.i.i = or i8 %and122.i.i, 48
; PREIR-NEXT:   %add.ptr127.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 14
; PREIR-NEXT:   store i8 %add123.i.i, i8* %add.ptr127.i.i, align 1, !tbaa !7
; PREIR-NEXT:   %add.ptr136.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 15
; PREIR-NEXT:   store i8 %add123.i.i, i8* %add.ptr136.i.i, align 1, !tbaa !7
; PREIR-NEXT:   %indvars.iv.next.i52 = add nuw nsw i64 %indvars.iv.i51, 1
; PREIR-NEXT:   %exitcond.i53 = icmp eq i64 %indvars.iv.next.i52, 1024
; PREIR-NEXT:   br i1 %exitcond.i53, label %polly.merge_new_and_old195, label %for.body6.i
;
; PREIR:      polly.merge_new_and_old195:                       ; preds = %polly.exiting197, %for.body6.i
; PREIR-NEXT:   br label %for.end.i
;
; PREIR:      for.end.i:                                        ; preds = %polly.merge_new_and_old195
; PREIR-NEXT:   %51 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !5
; PREIR-NEXT:   %call12.i = call i32 @fputs(i8* nonnull %call.i, %struct._IO_FILE* %51) #9
; PREIR-NEXT:   %indvars.iv.next5.i54 = add nuw nsw i64 %indvars.iv4.i50, 1
; PREIR-NEXT:   %exitcond6.i55 = icmp eq i64 %indvars.iv.next5.i54, 1024
; PREIR-NEXT:   br i1 %exitcond6.i55, label %print_array.exit, label %for.cond3.preheader.i
;
; PREIR:      print_array.exit:                                 ; preds = %for.end.i
; PREIR-NEXT:   call void @free(i8* nonnull %call.i) #7
; PREIR-NEXT:   call void @free(i8* nonnull %1) #7
; PREIR-NEXT:   call void @free(i8* %5) #7
; PREIR-NEXT:   call void @free(i8* %9) #7
; PREIR-NEXT:   ret i32 0
;
; PREIR:      polly.start:                                      ; preds = %polly.split_new_and_old
; PREIR-NEXT:   br label %polly.loop_preheader
;
; PREIR:      polly.loop_exit:                                  ; preds = %polly.loop_exit114
; PREIR-NEXT:   br label %polly.loop_preheader121
;
; PREIR:      polly.loop_exit122:                               ; preds = %polly.loop_exit128
; PREIR-NEXT:   br label %polly.loop_preheader136
;
; PREIR:      polly.loop_exit137:                               ; preds = %polly.loop_exit143
; PREIR-NEXT:   br label %polly.loop_preheader151
;
; PREIR:      polly.loop_exit152:                               ; preds = %polly.loop_exit158
; PREIR-NEXT:   br label %polly.exiting
;
; PREIR:      polly.exiting:                                    ; preds = %polly.loop_exit152
; PREIR-NEXT:   br label %polly.merge_new_and_old
;
; PREIR:      polly.loop_header:                                ; preds = %polly.loop_exit114, %polly.loop_preheader
; PREIR-NEXT:   %polly.indvar = phi i64 [ 0, %polly.loop_preheader ], [ %polly.indvar_next, %polly.loop_exit114 ]
; PREIR-NEXT:   br label %polly.stmt.for.cond1.preheader.i
;
; PREIR:      polly.stmt.for.cond1.preheader.i:                 ; preds = %polly.loop_header
; PREIR-NEXT:   %52 = trunc i64 %polly.indvar to i32
; PREIR-NEXT:   %p_conv.i = sitofp i32 %52 to double
; PREIR-NEXT:   store double %p_conv.i, double* %conv.i.s2a
; PREIR-NEXT:   br label %polly.loop_preheader113
;
; PREIR:      polly.loop_exit114:                               ; preds = %polly.stmt.for.body3.i
; PREIR-NEXT:   %polly.indvar_next = add nsw i64 %polly.indvar, 1
; PREIR-NEXT:   %polly.loop_cond = icmp sle i64 %polly.indvar, 1022
; PREIR-NEXT:   br i1 %polly.loop_cond, label %polly.loop_header, label %polly.loop_exit
;
; PREIR:      polly.loop_preheader:                             ; preds = %polly.start
; PREIR-NEXT:   br label %polly.loop_header
;
; PREIR:      polly.loop_header112:                             ; preds = %polly.stmt.for.body3.i, %polly.loop_preheader113
; PREIR-NEXT:   %polly.indvar115 = phi i64 [ 0, %polly.loop_preheader113 ], [ %polly.indvar_next116, %polly.stmt.for.body3.i ]
; PREIR-NEXT:   br label %polly.stmt.for.body3.i
;
; PREIR:      polly.stmt.for.body3.i:                           ; preds = %polly.loop_header112
; PREIR-NEXT:   %conv.i.s2a.reload = load double, double* %conv.i.s2a
; PREIR-NEXT:   %53 = trunc i64 %polly.indvar115 to i32
; PREIR-NEXT:   %p_conv4.i = sitofp i32 %53 to double
; PREIR-NEXT:   %p_mul.i = fmul double %conv.i.s2a.reload, %p_conv4.i
; PREIR-NEXT:   %p_div.i = fmul double %p_mul.i, 9.765625e-04
; PREIR-NEXT:   %54 = shl i64 %polly.indvar115, 3
; PREIR-NEXT:   %scevgep118 = getelementptr i8, i8* %scevgep, i64 %54
; PREIR-NEXT:   %scevgep118119 = bitcast i8* %scevgep118 to double*
; PREIR-NEXT:   store double %p_div.i, double* %scevgep118119, align 8, !alias.scope !8, !noalias !10
; PREIR-NEXT:   %polly.indvar_next116 = add nsw i64 %polly.indvar115, 1
; PREIR-NEXT:   %polly.loop_cond117 = icmp sle i64 %polly.indvar115, 1022
; PREIR-NEXT:   br i1 %polly.loop_cond117, label %polly.loop_header112, label %polly.loop_exit114
;
; PREIR:      polly.loop_preheader113:                          ; preds = %polly.stmt.for.cond1.preheader.i
; PREIR-NEXT:   %55 = shl i64 %polly.indvar, 13
; PREIR-NEXT:   %scevgep = getelementptr i8, i8* %1, i64 %55
; PREIR-NEXT:   br label %polly.loop_header112
;
; PREIR:      polly.loop_header120:                             ; preds = %polly.loop_exit128, %polly.loop_preheader121
; PREIR-NEXT:   %polly.indvar123 = phi i64 [ 0, %polly.loop_preheader121 ], [ %polly.indvar_next124, %polly.loop_exit128 ]
; PREIR-NEXT:   br label %polly.stmt.for.cond15.preheader.i
;
; PREIR:      polly.stmt.for.cond15.preheader.i:                ; preds = %polly.loop_header120
; PREIR-NEXT:   %56 = trunc i64 %polly.indvar123 to i32
; PREIR-NEXT:   %p_conv19.i = sitofp i32 %56 to double
; PREIR-NEXT:   store double %p_conv19.i, double* %conv19.i.s2a
; PREIR-NEXT:   br label %polly.loop_preheader127
;
; PREIR:      polly.loop_exit128:                               ; preds = %polly.stmt.for.body18.i
; PREIR-NEXT:   %polly.indvar_next124 = add nsw i64 %polly.indvar123, 1
; PREIR-NEXT:   %polly.loop_cond125 = icmp sle i64 %polly.indvar123, 1022
; PREIR-NEXT:   br i1 %polly.loop_cond125, label %polly.loop_header120, label %polly.loop_exit122
;
; PREIR:      polly.loop_preheader121:                          ; preds = %polly.loop_exit
; PREIR-NEXT:   br label %polly.loop_header120
;
; PREIR:      polly.loop_header126:                             ; preds = %polly.stmt.for.body18.i, %polly.loop_preheader127
; PREIR-NEXT:   %polly.indvar129 = phi i64 [ 0, %polly.loop_preheader127 ], [ %polly.indvar_next130, %polly.stmt.for.body18.i ]
; PREIR-NEXT:   br label %polly.stmt.for.body18.i
;
; PREIR:      polly.stmt.for.body18.i:                          ; preds = %polly.loop_header126
; PREIR-NEXT:   %conv19.i.s2a.reload = load double, double* %conv19.i.s2a
; PREIR-NEXT:   %57 = trunc i64 %polly.indvar129 to i32
; PREIR-NEXT:   %p_conv20.i = sitofp i32 %57 to double
; PREIR-NEXT:   %p_mul21.i = fmul double %conv19.i.s2a.reload, %p_conv20.i
; PREIR-NEXT:   %p_div23.i = fmul double %p_mul21.i, 9.765625e-04
; PREIR-NEXT:   %58 = shl i64 %polly.indvar129, 3
; PREIR-NEXT:   %scevgep133 = getelementptr i8, i8* %scevgep132, i64 %58
; PREIR-NEXT:   %scevgep133134 = bitcast i8* %scevgep133 to double*
; PREIR-NEXT:   store double %p_div23.i, double* %scevgep133134, align 8, !alias.scope !16, !noalias !17
; PREIR-NEXT:   %polly.indvar_next130 = add nsw i64 %polly.indvar129, 1
; PREIR-NEXT:   %polly.loop_cond131 = icmp sle i64 %polly.indvar129, 1022
; PREIR-NEXT:   br i1 %polly.loop_cond131, label %polly.loop_header126, label %polly.loop_exit128
;
; PREIR:      polly.loop_preheader127:                          ; preds = %polly.stmt.for.cond15.preheader.i
; PREIR-NEXT:   %59 = shl i64 %polly.indvar123, 13
; PREIR-NEXT:   %scevgep132 = getelementptr i8, i8* %5, i64 %59
; PREIR-NEXT:   br label %polly.loop_header126
;
; PREIR:      polly.loop_header135:                             ; preds = %polly.loop_exit143, %polly.loop_preheader136
; PREIR-NEXT:   %polly.indvar138 = phi i64 [ 0, %polly.loop_preheader136 ], [ %polly.indvar_next139, %polly.loop_exit143 ]
; PREIR-NEXT:   br label %polly.stmt.for.cond38.preheader.i
;
; PREIR:      polly.stmt.for.cond38.preheader.i:                ; preds = %polly.loop_header135
; PREIR-NEXT:   %60 = trunc i64 %polly.indvar138 to i32
; PREIR-NEXT:   %p_conv42.i = sitofp i32 %60 to double
; PREIR-NEXT:   store double %p_conv42.i, double* %conv42.i.s2a
; PREIR-NEXT:   br label %polly.loop_preheader142
;
; PREIR:      polly.loop_exit143:                               ; preds = %polly.stmt.for.body41.i
; PREIR-NEXT:   %polly.indvar_next139 = add nsw i64 %polly.indvar138, 1
; PREIR-NEXT:   %polly.loop_cond140 = icmp sle i64 %polly.indvar138, 1022
; PREIR-NEXT:   br i1 %polly.loop_cond140, label %polly.loop_header135, label %polly.loop_exit137
;
; PREIR:      polly.loop_preheader136:                          ; preds = %polly.loop_exit122
; PREIR-NEXT:   br label %polly.loop_header135
;
; PREIR:      polly.loop_header141:                             ; preds = %polly.stmt.for.body41.i, %polly.loop_preheader142
; PREIR-NEXT:   %polly.indvar144 = phi i64 [ 0, %polly.loop_preheader142 ], [ %polly.indvar_next145, %polly.stmt.for.body41.i ]
; PREIR-NEXT:   br label %polly.stmt.for.body41.i
;
; PREIR:      polly.stmt.for.body41.i:                          ; preds = %polly.loop_header141
; PREIR-NEXT:   %conv42.i.s2a.reload = load double, double* %conv42.i.s2a
; PREIR-NEXT:   %61 = trunc i64 %polly.indvar144 to i32
; PREIR-NEXT:   %p_conv43.i = sitofp i32 %61 to double
; PREIR-NEXT:   %p_mul44.i = fmul double %conv42.i.s2a.reload, %p_conv43.i
; PREIR-NEXT:   %p_div46.i = fmul double %p_mul44.i, 9.765625e-04
; PREIR-NEXT:   %62 = shl i64 %polly.indvar144, 3
; PREIR-NEXT:   %scevgep148 = getelementptr i8, i8* %scevgep147, i64 %62
; PREIR-NEXT:   %scevgep148149 = bitcast i8* %scevgep148 to double*
; PREIR-NEXT:   store double %p_div46.i, double* %scevgep148149, align 8, !alias.scope !11, !noalias !18
; PREIR-NEXT:   %polly.indvar_next145 = add nsw i64 %polly.indvar144, 1
; PREIR-NEXT:   %polly.loop_cond146 = icmp sle i64 %polly.indvar144, 1022
; PREIR-NEXT:   br i1 %polly.loop_cond146, label %polly.loop_header141, label %polly.loop_exit143
;
; PREIR:      polly.loop_preheader142:                          ; preds = %polly.stmt.for.cond38.preheader.i
; PREIR-NEXT:   %63 = shl i64 %polly.indvar138, 13
; PREIR-NEXT:   %scevgep147 = getelementptr i8, i8* %9, i64 %63
; PREIR-NEXT:   br label %polly.loop_header141
;
; PREIR:      polly.loop_header150:                             ; preds = %polly.loop_exit158, %polly.loop_preheader151
; PREIR-NEXT:   %polly.indvar153 = phi i64 [ 0, %polly.loop_preheader151 ], [ %polly.indvar_next154, %polly.loop_exit158 ]
; PREIR-NEXT:   br label %polly.loop_preheader157
;
; PREIR:      polly.loop_exit158:                               ; preds = %polly.loop_exit171
; PREIR-NEXT:   %polly.indvar_next154 = add nsw i64 %polly.indvar153, 1
; PREIR-NEXT:   %polly.loop_cond155 = icmp sle i64 %polly.indvar153, 1022
; PREIR-NEXT:   br i1 %polly.loop_cond155, label %polly.loop_header150, label %polly.loop_exit152
;
; PREIR:      polly.loop_preheader151:                          ; preds = %polly.loop_exit137
; PREIR-NEXT:   br label %polly.loop_header150
;
; PREIR:      polly.loop_header156:                             ; preds = %polly.loop_exit171, %polly.loop_preheader157
; PREIR-NEXT:   %polly.indvar159 = phi i64 [ 0, %polly.loop_preheader157 ], [ %polly.indvar_next160, %polly.loop_exit171 ]
; PREIR-NEXT:   br label %polly.stmt.for.body3.i44
;
; PREIR:      polly.stmt.for.body3.i44:                         ; preds = %polly.loop_header156
; PREIR-NEXT:   %64 = shl i64 %polly.indvar159, 3
; PREIR-NEXT:   %scevgep163 = getelementptr i8, i8* %scevgep162, i64 %64
; PREIR-NEXT:   %scevgep163164 = bitcast i8* %scevgep163 to double*
; PREIR-NEXT:   %_p_scalar_ = load double, double* %scevgep163164, align 8, !alias.scope !8, !noalias !10
; PREIR-NEXT:   %p_mul.i43 = fmul double %_p_scalar_, 2.123000e+03
; PREIR-NEXT:   store double %p_mul.i43, double* %scevgep163164, align 8, !alias.scope !8, !noalias !10
; PREIR-NEXT:   %polly.access.cast.165 = bitcast i8* %1 to double*
; PREIR-NEXT:   %polly.access.mul.166 = mul nsw i64 %polly.indvar153, 1024
; PREIR-NEXT:   %polly.access.add.167 = add nsw i64 %polly.access.mul.166, %polly.indvar159
; PREIR-NEXT:   %polly.access.168 = getelementptr double, double* %polly.access.cast.165, i64 %polly.access.add.167
; PREIR-NEXT:   store double %p_mul.i43, double* %polly.access.168, !alias.scope !8, !noalias !10
; PREIR-NEXT:   br label %polly.loop_preheader170
;
; PREIR:      polly.loop_exit171:                               ; preds = %polly.stmt.for.body8.i
; PREIR-NEXT:   %polly.indvar_next160 = add nsw i64 %polly.indvar159, 1
; PREIR-NEXT:   %polly.loop_cond161 = icmp sle i64 %polly.indvar159, 1022
; PREIR-NEXT:   br i1 %polly.loop_cond161, label %polly.loop_header156, label %polly.loop_exit158
;
; PREIR:      polly.loop_preheader157:                          ; preds = %polly.loop_header150
; PREIR-NEXT:   %65 = shl i64 %polly.indvar153, 13
; PREIR-NEXT:   %scevgep162 = getelementptr i8, i8* %1, i64 %65
; PREIR-NEXT:   %scevgep179 = getelementptr i8, i8* %5, i64 %65
; PREIR-NEXT:   %scevgep187 = getelementptr i8, i8* %1, i64 %65
; PREIR-NEXT:   br label %polly.loop_header156
;
; PREIR:      polly.loop_header169:                             ; preds = %polly.stmt.for.body8.i, %polly.loop_preheader170
; PREIR-NEXT:   %polly.indvar172 = phi i64 [ 0, %polly.loop_preheader170 ], [ %polly.indvar_next173, %polly.stmt.for.body8.i ]
; PREIR-NEXT:   br label %polly.stmt.for.body8.i
;
; PREIR:      polly.stmt.for.body8.i:                           ; preds = %polly.loop_header169
; PREIR-NEXT:   %polly.access.cast.175 = bitcast i8* %1 to double*
; PREIR-NEXT:   %polly.access.mul.176 = mul nsw i64 %polly.indvar153, 1024
; PREIR-NEXT:   %polly.access.add.177 = add nsw i64 %polly.access.mul.176, %polly.indvar159
; PREIR-NEXT:   %polly.access.178 = getelementptr double, double* %polly.access.cast.175, i64 %polly.access.add.177
; PREIR-NEXT:   %polly.access.178.reload = load double, double* %polly.access.178, !alias.scope !8, !noalias !10
; PREIR-NEXT:   %66 = shl i64 %polly.indvar172, 3
; PREIR-NEXT:   %scevgep180 = getelementptr i8, i8* %scevgep179, i64 %66
; PREIR-NEXT:   %scevgep180181 = bitcast i8* %scevgep180 to double*
; PREIR-NEXT:   %_p_scalar_182 = load double, double* %scevgep180181, align 8, !alias.scope !16, !noalias !17
; PREIR-NEXT:   %p_mul13.i = fmul double %_p_scalar_182, 3.241200e+04
; PREIR-NEXT:   %67 = shl i64 %polly.indvar172, 13
; PREIR-NEXT:   %scevgep184 = getelementptr i8, i8* %scevgep183, i64 %67
; PREIR-NEXT:   %scevgep184185 = bitcast i8* %scevgep184 to double*
; PREIR-NEXT:   %_p_scalar_186 = load double, double* %scevgep184185, align 8, !alias.scope !11, !noalias !18
; PREIR-NEXT:   %p_mul18.i = fmul double %p_mul13.i, %_p_scalar_186
; PREIR-NEXT:   %p_add.i = fadd double %polly.access.178.reload, %p_mul18.i
; PREIR-NEXT:   store double %p_add.i, double* %scevgep188189, align 8, !alias.scope !8, !noalias !10
; PREIR-NEXT:   %polly.access.cast.190 = bitcast i8* %1 to double*
; PREIR-NEXT:   %polly.access.mul.191 = mul nsw i64 %polly.indvar153, 1024
; PREIR-NEXT:   %polly.access.add.192 = add nsw i64 %polly.access.mul.191, %polly.indvar159
; PREIR-NEXT:   %polly.access.193 = getelementptr double, double* %polly.access.cast.190, i64 %polly.access.add.192
; PREIR-NEXT:   store double %p_add.i, double* %polly.access.193, !alias.scope !8, !noalias !10
; PREIR-NEXT:   %polly.indvar_next173 = add nsw i64 %polly.indvar172, 1
; PREIR-NEXT:   %polly.loop_cond174 = icmp sle i64 %polly.indvar172, 1022
; PREIR-NEXT:   br i1 %polly.loop_cond174, label %polly.loop_header169, label %polly.loop_exit171
;
; PREIR:      polly.loop_preheader170:                          ; preds = %polly.stmt.for.body3.i44
; PREIR-NEXT:   %68 = shl i64 %polly.indvar159, 3
; PREIR-NEXT:   %scevgep183 = getelementptr i8, i8* %9, i64 %68
; PREIR-NEXT:   %scevgep188 = getelementptr i8, i8* %scevgep187, i64 %68
; PREIR-NEXT:   %scevgep188189 = bitcast i8* %scevgep188 to double*
; PREIR-NEXT:   br label %polly.loop_header169
;
; PREIR:      polly.start196:                                   ; preds = %polly.split_new_and_old194
; PREIR-NEXT:   br label %polly.loop_preheader199
;
; PREIR:      polly.loop_exit200:                               ; preds = %polly.stmt.for.body6.i
; PREIR-NEXT:   br label %polly.exiting197
;
; PREIR:      polly.exiting197:                                 ; preds = %polly.loop_exit200
; PREIR-NEXT:   br label %polly.merge_new_and_old195
;
; PREIR:      polly.loop_header198:                             ; preds = %polly.stmt.for.body6.i, %polly.loop_preheader199
; PREIR-NEXT:   %polly.indvar201 = phi i64 [ 0, %polly.loop_preheader199 ], [ %polly.indvar_next202, %polly.stmt.for.body6.i ]
; PREIR-NEXT:   br label %polly.stmt.for.body6.i
;
; PREIR:      polly.stmt.for.body6.i:                           ; preds = %polly.loop_header198
; PREIR-NEXT:   %69 = shl i64 %polly.indvar201, 3
; PREIR-NEXT:   %scevgep205 = getelementptr i8, i8* %scevgep204, i64 %69
; PREIR-NEXT:   %scevgep205206 = bitcast i8* %scevgep205 to i64*
; PREIR-NEXT:   %_p_scalar_207 = load i64, i64* %scevgep205206, align 8, !alias.scope !19, !noalias !21
; PREIR-NEXT:   %p_block.sroa.0.0.extract.trunc138.i.i = trunc i64 %_p_scalar_207 to i8
; PREIR-NEXT:   %p_and.i.i = and i8 %p_block.sroa.0.0.extract.trunc138.i.i, 15
; PREIR-NEXT:   %p_add.i.i = or i8 %p_and.i.i, 48
; PREIR-NEXT:   %70 = shl i64 %polly.indvar201, 4
; PREIR-NEXT:   %scevgep208 = getelementptr i8, i8* %call.i, i64 %70
; PREIR-NEXT:   store i8 %p_add.i.i, i8* %scevgep208, align 1, !alias.scope !22, !noalias !23
; PREIR-NEXT:   %scevgep210 = getelementptr i8, i8* %scevgep209, i64 %70
; PREIR-NEXT:   store i8 %p_add.i.i, i8* %scevgep210, align 1, !alias.scope !22, !noalias !23
; PREIR-NEXT:   %p_block.sroa.0.1.extract.shift.i.i = lshr i64 %_p_scalar_207, 8
; PREIR-NEXT:   %p_conv13195.i.i = trunc i64 %p_block.sroa.0.1.extract.shift.i.i to i8
; PREIR-NEXT:   %p_and14.i.i = and i8 %p_conv13195.i.i, 15
; PREIR-NEXT:   %p_add15.i.i = or i8 %p_and14.i.i, 48
; PREIR-NEXT:   %71 = shl i64 %polly.indvar201, 4
; PREIR-NEXT:   %scevgep212 = getelementptr i8, i8* %scevgep211, i64 %71
; PREIR-NEXT:   store i8 %p_add15.i.i, i8* %scevgep212, align 1, !alias.scope !22, !noalias !23
; PREIR-NEXT:   %scevgep214 = getelementptr i8, i8* %scevgep213, i64 %71
; PREIR-NEXT:   store i8 %p_add15.i.i, i8* %scevgep214, align 1, !alias.scope !22, !noalias !23
; PREIR-NEXT:   %p_block.sroa.0.2.extract.shift.i.i = lshr i64 %_p_scalar_207, 16
; PREIR-NEXT:   %p_conv31201.i.i = trunc i64 %p_block.sroa.0.2.extract.shift.i.i to i8
; PREIR-NEXT:   %p_and32.i.i = and i8 %p_conv31201.i.i, 15
; PREIR-NEXT:   %p_add33.i.i = or i8 %p_and32.i.i, 48
; PREIR-NEXT:   %72 = shl i64 %polly.indvar201, 4
; PREIR-NEXT:   %scevgep216 = getelementptr i8, i8* %scevgep215, i64 %72
; PREIR-NEXT:   store i8 %p_add33.i.i, i8* %scevgep216, align 1, !alias.scope !22, !noalias !23
; PREIR-NEXT:   %scevgep218 = getelementptr i8, i8* %scevgep217, i64 %72
; PREIR-NEXT:   store i8 %p_add33.i.i, i8* %scevgep218, align 1, !alias.scope !22, !noalias !23
; PREIR-NEXT:   %p_.tr.i.i = trunc i64 %_p_scalar_207 to i32
; PREIR-NEXT:   %p_sext204207.i.i = lshr i32 %p_.tr.i.i, 24
; PREIR-NEXT:   %p_and50.i.i = and i32 %p_sext204207.i.i, 15
; PREIR-NEXT:   %p_add51.i.i = or i32 %p_and50.i.i, 48
; PREIR-NEXT:   %p_conv52.i.i = trunc i32 %p_add51.i.i to i8
; PREIR-NEXT:   %73 = shl i64 %polly.indvar201, 4
; PREIR-NEXT:   %scevgep220 = getelementptr i8, i8* %scevgep219, i64 %73
; PREIR-NEXT:   store i8 %p_conv52.i.i, i8* %scevgep220, align 1, !alias.scope !22, !noalias !23
; PREIR-NEXT:   %scevgep222 = getelementptr i8, i8* %scevgep221, i64 %73
; PREIR-NEXT:   store i8 %p_conv52.i.i, i8* %scevgep222, align 1, !alias.scope !22, !noalias !23
; PREIR-NEXT:   %p_block.sroa.0.4.extract.shift.i.i = lshr i64 %_p_scalar_207, 32
; PREIR-NEXT:   %p_conv67211.i.i = trunc i64 %p_block.sroa.0.4.extract.shift.i.i to i8
; PREIR-NEXT:   %p_and68.i.i = and i8 %p_conv67211.i.i, 15
; PREIR-NEXT:   %p_add69.i.i = or i8 %p_and68.i.i, 48
; PREIR-NEXT:   %74 = shl i64 %polly.indvar201, 4
; PREIR-NEXT:   %scevgep224 = getelementptr i8, i8* %scevgep223, i64 %74
; PREIR-NEXT:   store i8 %p_add69.i.i, i8* %scevgep224, align 1, !alias.scope !22, !noalias !23
; PREIR-NEXT:   %scevgep226 = getelementptr i8, i8* %scevgep225, i64 %74
; PREIR-NEXT:   store i8 %p_add69.i.i, i8* %scevgep226, align 1, !alias.scope !22, !noalias !23
; PREIR-NEXT:   %p_block.sroa.0.5.extract.shift.i.i = lshr i64 %_p_scalar_207, 40
; PREIR-NEXT:   %p_conv85217.i.i = trunc i64 %p_block.sroa.0.5.extract.shift.i.i to i8
; PREIR-NEXT:   %p_and86.i.i = and i8 %p_conv85217.i.i, 15
; PREIR-NEXT:   %p_add87.i.i = or i8 %p_and86.i.i, 48
; PREIR-NEXT:   %75 = shl i64 %polly.indvar201, 4
; PREIR-NEXT:   %scevgep228 = getelementptr i8, i8* %scevgep227, i64 %75
; PREIR-NEXT:   store i8 %p_add87.i.i, i8* %scevgep228, align 1, !alias.scope !22, !noalias !23
; PREIR-NEXT:   %scevgep230 = getelementptr i8, i8* %scevgep229, i64 %75
; PREIR-NEXT:   store i8 %p_add87.i.i, i8* %scevgep230, align 1, !alias.scope !22, !noalias !23
; PREIR-NEXT:   %p_block.sroa.0.6.extract.shift.i.i = lshr i64 %_p_scalar_207, 48
; PREIR-NEXT:   %p_conv103223.i.i = trunc i64 %p_block.sroa.0.6.extract.shift.i.i to i8
; PREIR-NEXT:   %p_and104.i.i = and i8 %p_conv103223.i.i, 15
; PREIR-NEXT:   %p_add105.i.i = or i8 %p_and104.i.i, 48
; PREIR-NEXT:   %76 = shl i64 %polly.indvar201, 4
; PREIR-NEXT:   %scevgep232 = getelementptr i8, i8* %scevgep231, i64 %76
; PREIR-NEXT:   store i8 %p_add105.i.i, i8* %scevgep232, align 1, !alias.scope !22, !noalias !23
; PREIR-NEXT:   %scevgep234 = getelementptr i8, i8* %scevgep233, i64 %76
; PREIR-NEXT:   store i8 %p_add105.i.i, i8* %scevgep234, align 1, !alias.scope !22, !noalias !23
; PREIR-NEXT:   %p_block.sroa.0.7.extract.shift.i.i = lshr i64 %_p_scalar_207, 56
; PREIR-NEXT:   %p_conv121229.i.i = trunc i64 %p_block.sroa.0.7.extract.shift.i.i to i8
; PREIR-NEXT:   %p_and122.i.i = and i8 %p_conv121229.i.i, 15
; PREIR-NEXT:   %p_add123.i.i = or i8 %p_and122.i.i, 48
; PREIR-NEXT:   %77 = shl i64 %polly.indvar201, 4
; PREIR-NEXT:   %scevgep236 = getelementptr i8, i8* %scevgep235, i64 %77
; PREIR-NEXT:   store i8 %p_add123.i.i, i8* %scevgep236, align 1, !alias.scope !22, !noalias !23
; PREIR-NEXT:   %scevgep238 = getelementptr i8, i8* %scevgep237, i64 %77
; PREIR-NEXT:   store i8 %p_add123.i.i, i8* %scevgep238, align 1, !alias.scope !22, !noalias !23
; PREIR-NEXT:   %polly.indvar_next202 = add nsw i64 %polly.indvar201, 1
; PREIR-NEXT:   %polly.loop_cond203 = icmp sle i64 %polly.indvar201, 1022
; PREIR-NEXT:   br i1 %polly.loop_cond203, label %polly.loop_header198, label %polly.loop_exit200
;
; PREIR:      polly.loop_preheader199:                          ; preds = %polly.start196
; PREIR-NEXT:   %78 = shl i64 %47, 13
; PREIR-NEXT:   %scevgep204 = getelementptr i8, i8* %1, i64 %78
; PREIR-NEXT:   br label %polly.loop_header198
; PREIR-NEXT: }
;
; PREIR:      ; Function Attrs: nounwind
; PREIR-NEXT: declare i32 @posix_memalign(i8**, i64, i64) local_unnamed_addr #2
;
; PREIR:      ; Function Attrs: nounwind
; PREIR-NEXT: declare i32 @fprintf(%struct._IO_FILE* nocapture, i8* nocapture readonly, ...) local_unnamed_addr #2
;
; PREIR:      ; Function Attrs: noreturn nounwind
; PREIR-NEXT: declare void @exit(i32) local_unnamed_addr #6
;
; PREIR:      ; Function Attrs: nounwind
; PREIR-NEXT: declare noalias i8* @malloc(i64) local_unnamed_addr #2
;
; PREIR:      ; Function Attrs: nounwind
; PREIR-NEXT: declare i32 @fputs(i8* nocapture readonly, %struct._IO_FILE* nocapture) local_unnamed_addr #2
;
; PREIR:      ; Function Attrs: nounwind
; PREIR-NEXT: declare i64 @fwrite(i8* nocapture, i64, i64, %struct._IO_FILE* nocapture) #7
;
; PREIR:      ; Function Attrs: nounwind readnone
; PREIR-NEXT: declare { i64, i1 } @llvm.smul.with.overflow.i64(i64, i64) #8
;
; PREIR:      ; Function Attrs: nounwind readnone
; PREIR-NEXT: declare { i64, i1 } @llvm.sadd.with.overflow.i64(i64, i64) #8
;
; PREIR:      attributes #0 = { norecurse nounwind readnone uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
; PREIR-NEXT: attributes #1 = { argmemonly nounwind }
; PREIR-NEXT: attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
; PREIR-NEXT: attributes #3 = { norecurse nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
; PREIR-NEXT: attributes #4 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
; PREIR-NEXT: attributes #5 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "polly-optimized" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
; PREIR-NEXT: attributes #6 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
; PREIR-NEXT: attributes #7 = { nounwind }
; PREIR-NEXT: attributes #8 = { nounwind readnone }
; PREIR-NEXT: attributes #9 = { cold nounwind }
; PREIR-NEXT: attributes #10 = { noreturn nounwind }
;
; PREIR:      !llvm.ident = !{!0}
;
; PREIR:      !0 = !{!"clang version 4.0.0 (trunk 278052) (llvm/trunk 278053)"}
; PREIR-NEXT: !1 = !{!2, !2, i64 0}
; PREIR-NEXT: !2 = !{!"double", !3, i64 0}
; PREIR-NEXT: !3 = !{!"omnipotent char", !4, i64 0}
; PREIR-NEXT: !4 = !{!"Simple C/C++ TBAA"}
; PREIR-NEXT: !5 = !{!6, !6, i64 0}
; PREIR-NEXT: !6 = !{!"any pointer", !3, i64 0}
; PREIR-NEXT: !7 = !{!3, !3, i64 0}
; PREIR-NEXT: !8 = distinct !{!8, !9, !"polly.alias.scope."}
; PREIR-NEXT: !9 = distinct !{!9, !"polly.alias.scope.domain"}
; PREIR-NEXT: !10 = !{!11, !12, !13, !14, !15, !16}
; PREIR-NEXT: !11 = distinct !{!11, !9, !"polly.alias.scope."}
; PREIR-NEXT: !12 = distinct !{!12, !9, !"polly.alias.scope.conv42.i"}
; PREIR-NEXT: !13 = distinct !{!13, !9, !"polly.alias.scope.conv.i"}
; PREIR-NEXT: !14 = distinct !{!14, !9, !"polly.alias.scope."}
; PREIR-NEXT: !15 = distinct !{!15, !9, !"polly.alias.scope.conv19.i"}
; PREIR-NEXT: !16 = distinct !{!16, !9, !"polly.alias.scope."}
; PREIR-NEXT: !17 = !{!11, !12, !13, !14, !8, !15}
; PREIR-NEXT: !18 = !{!12, !13, !14, !8, !15, !16}
; PREIR-NEXT: !19 = distinct !{!19, !20, !"polly.alias.scope."}
; PREIR-NEXT: !20 = distinct !{!20, !"polly.alias.scope.domain"}
; PREIR-NEXT: !21 = !{!22}
; PREIR-NEXT: !22 = distinct !{!22, !20, !"polly.alias.scope.call.i"}
; PREIR-NEXT: !23 = !{!19}

; IR:      ; ModuleID = '<stdin>'
; IR-NEXT: source_filename = "/mnt/c/Users/Meinersbur/src/llvm/projects/test-suite/SingleSource/Benchmarks/Polybench/linear-algebra/kernels/gemm/gemm.c"
; IR-NEXT: target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
; IR-NEXT: target triple = "x86_64-unknown-linux-gnu"
;
; IR:      %struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
; IR-NEXT: %struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
;
; IR:      @polybench_papi_counters_threadid = local_unnamed_addr global i32 0, align 4
; IR-NEXT: @polybench_program_total_flops = local_unnamed_addr global double 0.000000e+00, align 8
; IR-NEXT: @polybench_t_start = common local_unnamed_addr global double 0.000000e+00, align 8
; IR-NEXT: @polybench_t_end = common local_unnamed_addr global double 0.000000e+00, align 8
; IR-NEXT: @.str = private unnamed_addr constant [7 x i8] c"%0.6f\0A\00", align 1
; IR-NEXT: @polybench_c_start = common local_unnamed_addr global i64 0, align 8
; IR-NEXT: @polybench_c_end = common local_unnamed_addr global i64 0, align 8
; IR-NEXT: @stderr = external local_unnamed_addr global %struct._IO_FILE*, align 8
; IR-NEXT: @.str.1 = private unnamed_addr constant [51 x i8] c"[PolyBench] posix_memalign: cannot allocate memory\00", align 1
;
; IR:      ; Function Attrs: norecurse nounwind readnone uwtable
; IR-NEXT: define void @polybench_flush_cache() local_unnamed_addr #0 {
; IR-NEXT: entry:
; IR-NEXT:   br label %entry.split
;
; IR:      entry.split:                                      ; preds = %entry
; IR-NEXT:   ret void
; IR-NEXT: }
;
; IR:      ; Function Attrs: argmemonly nounwind
; IR-NEXT: declare void @llvm.lifetime.start(i64, i8* nocapture) #1
;
; IR:      ; Function Attrs: nounwind
; IR-NEXT: declare noalias i8* @calloc(i64, i64) local_unnamed_addr #2
;
; IR:      ; Function Attrs: nounwind
; IR-NEXT: declare void @free(i8* nocapture) local_unnamed_addr #2
;
; IR:      ; Function Attrs: argmemonly nounwind
; IR-NEXT: declare void @llvm.lifetime.end(i64, i8* nocapture) #1
;
; IR:      ; Function Attrs: norecurse nounwind readnone uwtable
; IR-NEXT: define void @polybench_prepare_instruments() local_unnamed_addr #0 {
; IR-NEXT: entry:
; IR-NEXT:   br label %entry.split
;
; IR:      entry.split:                                      ; preds = %entry
; IR-NEXT:   ret void
; IR-NEXT: }
;
; IR:      ; Function Attrs: norecurse nounwind uwtable
; IR-NEXT: define void @polybench_timer_start() local_unnamed_addr #3 {
; IR-NEXT: entry:
; IR-NEXT:   br label %entry.split
;
; IR:      entry.split:                                      ; preds = %entry
; IR-NEXT:   store double 0.000000e+00, double* @polybench_t_start, align 8, !tbaa !1
; IR-NEXT:   ret void
; IR-NEXT: }
;
; IR:      ; Function Attrs: norecurse nounwind uwtable
; IR-NEXT: define void @polybench_timer_stop() local_unnamed_addr #3 {
; IR-NEXT: entry:
; IR-NEXT:   br label %entry.split
;
; IR:      entry.split:                                      ; preds = %entry
; IR-NEXT:   store double 0.000000e+00, double* @polybench_t_end, align 8, !tbaa !1
; IR-NEXT:   ret void
; IR-NEXT: }
;
; IR:      ; Function Attrs: nounwind uwtable
; IR-NEXT: define void @polybench_timer_print() local_unnamed_addr #4 {
; IR-NEXT: entry:
; IR-NEXT:   br label %entry.split
;
; IR:      entry.split:                                      ; preds = %entry
; IR-NEXT:   %0 = load double, double* @polybench_t_end, align 8, !tbaa !1
; IR-NEXT:   %1 = load double, double* @polybench_t_start, align 8, !tbaa !1
; IR-NEXT:   %sub = fsub double %0, %1
; IR-NEXT:   %call = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i64 0, i64 0), double %sub)
; IR-NEXT:   ret void
; IR-NEXT: }
;
; IR:      ; Function Attrs: nounwind
; IR-NEXT: declare i32 @printf(i8* nocapture readonly, ...) local_unnamed_addr #2
;
; IR:      ; Function Attrs: nounwind uwtable
; IR-NEXT: define i8* @polybench_alloc_data(i64 %n, i32 %elt_size) local_unnamed_addr #4 {
; IR-NEXT: entry:
; IR-NEXT:   %new.i = alloca i8*, align 8
; IR-NEXT:   br label %entry.split
;
; IR:      entry.split:                                      ; preds = %entry
; IR-NEXT:   %conv = sext i32 %elt_size to i64
; IR-NEXT:   %mul = mul i64 %conv, %n
; IR-NEXT:   %0 = bitcast i8** %new.i to i8*
; IR-NEXT:   call void @llvm.lifetime.start(i64 8, i8* %0) #7
; IR-NEXT:   store i8* null, i8** %new.i, align 8, !tbaa !5
; IR-NEXT:   %call.i = call i32 @posix_memalign(i8** nonnull %new.i, i64 32, i64 %mul) #7
; IR-NEXT:   %1 = load i8*, i8** %new.i, align 8, !tbaa !5
; IR-NEXT:   %tobool.i = icmp eq i8* %1, null
; IR-NEXT:   %tobool1.i = icmp ne i32 %call.i, 0
; IR-NEXT:   %or.cond.i = or i1 %tobool1.i, %tobool.i
; IR-NEXT:   br i1 %or.cond.i, label %if.then.i, label %xmalloc.exit
;
; IR:      if.then.i:                                        ; preds = %entry.split
; IR-NEXT:   %2 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !5
; IR-NEXT:   %3 = call i64 @fwrite(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.1, i64 0, i64 0), i64 50, i64 1, %struct._IO_FILE* %2) #9
; IR-NEXT:   call void @exit(i32 1) #10
; IR-NEXT:   unreachable
;
; IR:      xmalloc.exit:                                     ; preds = %entry.split
; IR-NEXT:   call void @llvm.lifetime.end(i64 8, i8* %0) #7
; IR-NEXT:   ret i8* %1
; IR-NEXT: }
;
; IR:      ; Function Attrs: nounwind uwtable
; IR-NEXT: define i32 @main(i32 %argc, i8** nocapture readnone %argv) local_unnamed_addr #5 {
; IR-NEXT: entry:
; IR-NEXT:   %conv19.i.s2a = alloca double
; IR-NEXT:   %conv.i.s2a = alloca double
; IR-NEXT:   %conv42.i.s2a = alloca double
; IR-NEXT:   %new.i.i34 = alloca i8*, align 8
; IR-NEXT:   %new.i.i27 = alloca i8*, align 8
; IR-NEXT:   %new.i.i = alloca i8*, align 8
; IR-NEXT:   br label %entry.split
;
; IR:      entry.split:                                      ; preds = %entry
; IR-NEXT:   %0 = bitcast i8** %new.i.i to i8*
; IR-NEXT:   call void @llvm.lifetime.start(i64 8, i8* %0) #7
; IR-NEXT:   store i8* null, i8** %new.i.i, align 8, !tbaa !5
; IR-NEXT:   %call.i.i = call i32 @posix_memalign(i8** nonnull %new.i.i, i64 32, i64 8388608) #7
; IR-NEXT:   %1 = load i8*, i8** %new.i.i, align 8, !tbaa !5
; IR-NEXT:   %tobool.i.i = icmp eq i8* %1, null
; IR-NEXT:   %tobool1.i.i = icmp ne i32 %call.i.i, 0
; IR-NEXT:   %or.cond.i.i = or i1 %tobool1.i.i, %tobool.i.i
; IR-NEXT:   br i1 %or.cond.i.i, label %if.then.i.i, label %polybench_alloc_data.exit
;
; IR:      if.then.i.i:                                      ; preds = %entry.split
; IR-NEXT:   %2 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !5
; IR-NEXT:   %3 = call i64 @fwrite(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.1, i64 0, i64 0), i64 50, i64 1, %struct._IO_FILE* %2) #9
; IR-NEXT:   call void @exit(i32 1) #10
; IR-NEXT:   unreachable
;
; IR:      polybench_alloc_data.exit:                        ; preds = %entry.split
; IR-NEXT:   call void @llvm.lifetime.end(i64 8, i8* %0) #7
; IR-NEXT:   %4 = bitcast i8** %new.i.i27 to i8*
; IR-NEXT:   call void @llvm.lifetime.start(i64 8, i8* %4) #7
; IR-NEXT:   store i8* null, i8** %new.i.i27, align 8, !tbaa !5
; IR-NEXT:   %call.i.i28 = call i32 @posix_memalign(i8** nonnull %new.i.i27, i64 32, i64 8388608) #7
; IR-NEXT:   %5 = load i8*, i8** %new.i.i27, align 8, !tbaa !5
; IR-NEXT:   %tobool.i.i29 = icmp eq i8* %5, null
; IR-NEXT:   %tobool1.i.i30 = icmp ne i32 %call.i.i28, 0
; IR-NEXT:   %or.cond.i.i31 = or i1 %tobool1.i.i30, %tobool.i.i29
; IR-NEXT:   br i1 %or.cond.i.i31, label %if.then.i.i32, label %polybench_alloc_data.exit33
;
; IR:      if.then.i.i32:                                    ; preds = %polybench_alloc_data.exit
; IR-NEXT:   %6 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !5
; IR-NEXT:   %7 = call i64 @fwrite(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.1, i64 0, i64 0), i64 50, i64 1, %struct._IO_FILE* %6) #9
; IR-NEXT:   call void @exit(i32 1) #10
; IR-NEXT:   unreachable
;
; IR:      polybench_alloc_data.exit33:                      ; preds = %polybench_alloc_data.exit
; IR-NEXT:   call void @llvm.lifetime.end(i64 8, i8* %4) #7
; IR-NEXT:   %8 = bitcast i8** %new.i.i34 to i8*
; IR-NEXT:   call void @llvm.lifetime.start(i64 8, i8* %8) #7
; IR-NEXT:   store i8* null, i8** %new.i.i34, align 8, !tbaa !5
; IR-NEXT:   %call.i.i35 = call i32 @posix_memalign(i8** nonnull %new.i.i34, i64 32, i64 8388608) #7
; IR-NEXT:   %9 = load i8*, i8** %new.i.i34, align 8, !tbaa !5
; IR-NEXT:   %tobool.i.i36 = icmp eq i8* %9, null
; IR-NEXT:   %tobool1.i.i37 = icmp ne i32 %call.i.i35, 0
; IR-NEXT:   %or.cond.i.i38 = or i1 %tobool1.i.i37, %tobool.i.i36
; IR-NEXT:   br i1 %or.cond.i.i38, label %if.then.i.i39, label %polybench_alloc_data.exit40
;
; IR:      if.then.i.i39:                                    ; preds = %polybench_alloc_data.exit33
; IR-NEXT:   %10 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !5
; IR-NEXT:   %11 = call i64 @fwrite(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.1, i64 0, i64 0), i64 50, i64 1, %struct._IO_FILE* %10) #9
; IR-NEXT:   call void @exit(i32 1) #10
; IR-NEXT:   unreachable
;
; IR:      polybench_alloc_data.exit40:                      ; preds = %polybench_alloc_data.exit33
; IR-NEXT:   call void @llvm.lifetime.end(i64 8, i8* %8) #7
; IR-NEXT:   %arraydecay = bitcast i8* %1 to [1024 x double]*
; IR-NEXT:   %arraydecay3 = bitcast i8* %5 to [1024 x double]*
; IR-NEXT:   br label %polly.split_new_and_old
;
; IR:      polly.split_new_and_old:                          ; preds = %polybench_alloc_data.exit40
; IR-NEXT:   %polly.access.cast. = bitcast i8* %9 to double*
; IR-NEXT:   %polly.access.mul. = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 1023, i64 1024)
; IR-NEXT:   %polly.access.mul..obit = extractvalue { i64, i1 } %polly.access.mul., 1
; IR-NEXT:   %polly.overflow.state = or i1 false, %polly.access.mul..obit
; IR-NEXT:   %polly.access.mul..res = extractvalue { i64, i1 } %polly.access.mul., 0
; IR-NEXT:   %polly.access.add. = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res, i64 1024)
; IR-NEXT:   %polly.access.add..obit = extractvalue { i64, i1 } %polly.access.add., 1
; IR-NEXT:   %polly.overflow.state1 = or i1 %polly.overflow.state, %polly.access.add..obit
; IR-NEXT:   %polly.access.add..res = extractvalue { i64, i1 } %polly.access.add., 0
; IR-NEXT:   %polly.access. = getelementptr double, double* %polly.access.cast., i64 %polly.access.add..res
; IR-NEXT:   %polly.access.cast.2 = bitcast i8* %5 to double*
; IR-NEXT:   %polly.access.mul.3 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 0, i64 1024)
; IR-NEXT:   %polly.access.mul..obit4 = extractvalue { i64, i1 } %polly.access.mul.3, 1
; IR-NEXT:   %polly.overflow.state5 = or i1 %polly.overflow.state1, %polly.access.mul..obit4
; IR-NEXT:   %polly.access.mul..res6 = extractvalue { i64, i1 } %polly.access.mul.3, 0
; IR-NEXT:   %polly.access.add.7 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res6, i64 0)
; IR-NEXT:   %polly.access.add..obit8 = extractvalue { i64, i1 } %polly.access.add.7, 1
; IR-NEXT:   %polly.overflow.state9 = or i1 %polly.overflow.state5, %polly.access.add..obit8
; IR-NEXT:   %polly.access.add..res10 = extractvalue { i64, i1 } %polly.access.add.7, 0
; IR-NEXT:   %polly.access.11 = getelementptr double, double* %polly.access.cast.2, i64 %polly.access.add..res10
; IR-NEXT:   %12 = ptrtoint double* %polly.access. to i64
; IR-NEXT:   %13 = ptrtoint double* %polly.access.11 to i64
; IR-NEXT:   %14 = icmp ule i64 %12, %13
; IR-NEXT:   %polly.access.cast.12 = bitcast i8* %5 to double*
; IR-NEXT:   %polly.access.mul.13 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 1023, i64 1024)
; IR-NEXT:   %polly.access.mul..obit14 = extractvalue { i64, i1 } %polly.access.mul.13, 1
; IR-NEXT:   %polly.overflow.state15 = or i1 %polly.overflow.state9, %polly.access.mul..obit14
; IR-NEXT:   %polly.access.mul..res16 = extractvalue { i64, i1 } %polly.access.mul.13, 0
; IR-NEXT:   %polly.access.add.17 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res16, i64 1024)
; IR-NEXT:   %polly.access.add..obit18 = extractvalue { i64, i1 } %polly.access.add.17, 1
; IR-NEXT:   %polly.overflow.state19 = or i1 %polly.overflow.state15, %polly.access.add..obit18
; IR-NEXT:   %polly.access.add..res20 = extractvalue { i64, i1 } %polly.access.add.17, 0
; IR-NEXT:   %polly.access.21 = getelementptr double, double* %polly.access.cast.12, i64 %polly.access.add..res20
; IR-NEXT:   %polly.access.cast.22 = bitcast i8* %9 to double*
; IR-NEXT:   %polly.access.mul.23 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 0, i64 1024)
; IR-NEXT:   %polly.access.mul..obit24 = extractvalue { i64, i1 } %polly.access.mul.23, 1
; IR-NEXT:   %polly.overflow.state25 = or i1 %polly.overflow.state19, %polly.access.mul..obit24
; IR-NEXT:   %polly.access.mul..res26 = extractvalue { i64, i1 } %polly.access.mul.23, 0
; IR-NEXT:   %polly.access.add.27 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res26, i64 0)
; IR-NEXT:   %polly.access.add..obit28 = extractvalue { i64, i1 } %polly.access.add.27, 1
; IR-NEXT:   %polly.overflow.state29 = or i1 %polly.overflow.state25, %polly.access.add..obit28
; IR-NEXT:   %polly.access.add..res30 = extractvalue { i64, i1 } %polly.access.add.27, 0
; IR-NEXT:   %polly.access.31 = getelementptr double, double* %polly.access.cast.22, i64 %polly.access.add..res30
; IR-NEXT:   %15 = ptrtoint double* %polly.access.21 to i64
; IR-NEXT:   %16 = ptrtoint double* %polly.access.31 to i64
; IR-NEXT:   %17 = icmp ule i64 %15, %16
; IR-NEXT:   %18 = or i1 %14, %17
; IR-NEXT:   %19 = and i1 true, %18
; IR-NEXT:   %polly.access.cast.32 = bitcast i8* %1 to double*
; IR-NEXT:   %polly.access.mul.33 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 1023, i64 1024)
; IR-NEXT:   %polly.access.mul..obit34 = extractvalue { i64, i1 } %polly.access.mul.33, 1
; IR-NEXT:   %polly.overflow.state35 = or i1 %polly.overflow.state29, %polly.access.mul..obit34
; IR-NEXT:   %polly.access.mul..res36 = extractvalue { i64, i1 } %polly.access.mul.33, 0
; IR-NEXT:   %polly.access.add.37 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res36, i64 1024)
; IR-NEXT:   %polly.access.add..obit38 = extractvalue { i64, i1 } %polly.access.add.37, 1
; IR-NEXT:   %polly.overflow.state39 = or i1 %polly.overflow.state35, %polly.access.add..obit38
; IR-NEXT:   %polly.access.add..res40 = extractvalue { i64, i1 } %polly.access.add.37, 0
; IR-NEXT:   %polly.access.41 = getelementptr double, double* %polly.access.cast.32, i64 %polly.access.add..res40
; IR-NEXT:   %polly.access.cast.42 = bitcast i8* %5 to double*
; IR-NEXT:   %polly.access.mul.43 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 0, i64 1024)
; IR-NEXT:   %polly.access.mul..obit44 = extractvalue { i64, i1 } %polly.access.mul.43, 1
; IR-NEXT:   %polly.overflow.state45 = or i1 %polly.overflow.state39, %polly.access.mul..obit44
; IR-NEXT:   %polly.access.mul..res46 = extractvalue { i64, i1 } %polly.access.mul.43, 0
; IR-NEXT:   %polly.access.add.47 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res46, i64 0)
; IR-NEXT:   %polly.access.add..obit48 = extractvalue { i64, i1 } %polly.access.add.47, 1
; IR-NEXT:   %polly.overflow.state49 = or i1 %polly.overflow.state45, %polly.access.add..obit48
; IR-NEXT:   %polly.access.add..res50 = extractvalue { i64, i1 } %polly.access.add.47, 0
; IR-NEXT:   %polly.access.51 = getelementptr double, double* %polly.access.cast.42, i64 %polly.access.add..res50
; IR-NEXT:   %20 = ptrtoint double* %polly.access.41 to i64
; IR-NEXT:   %21 = ptrtoint double* %polly.access.51 to i64
; IR-NEXT:   %22 = icmp ule i64 %20, %21
; IR-NEXT:   %polly.access.cast.52 = bitcast i8* %5 to double*
; IR-NEXT:   %polly.access.mul.53 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 1023, i64 1024)
; IR-NEXT:   %polly.access.mul..obit54 = extractvalue { i64, i1 } %polly.access.mul.53, 1
; IR-NEXT:   %polly.overflow.state55 = or i1 %polly.overflow.state49, %polly.access.mul..obit54
; IR-NEXT:   %polly.access.mul..res56 = extractvalue { i64, i1 } %polly.access.mul.53, 0
; IR-NEXT:   %polly.access.add.57 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res56, i64 1024)
; IR-NEXT:   %polly.access.add..obit58 = extractvalue { i64, i1 } %polly.access.add.57, 1
; IR-NEXT:   %polly.overflow.state59 = or i1 %polly.overflow.state55, %polly.access.add..obit58
; IR-NEXT:   %polly.access.add..res60 = extractvalue { i64, i1 } %polly.access.add.57, 0
; IR-NEXT:   %polly.access.61 = getelementptr double, double* %polly.access.cast.52, i64 %polly.access.add..res60
; IR-NEXT:   %polly.access.cast.62 = bitcast i8* %1 to double*
; IR-NEXT:   %polly.access.mul.63 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 0, i64 1024)
; IR-NEXT:   %polly.access.mul..obit64 = extractvalue { i64, i1 } %polly.access.mul.63, 1
; IR-NEXT:   %polly.overflow.state65 = or i1 %polly.overflow.state59, %polly.access.mul..obit64
; IR-NEXT:   %polly.access.mul..res66 = extractvalue { i64, i1 } %polly.access.mul.63, 0
; IR-NEXT:   %polly.access.add.67 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res66, i64 0)
; IR-NEXT:   %polly.access.add..obit68 = extractvalue { i64, i1 } %polly.access.add.67, 1
; IR-NEXT:   %polly.overflow.state69 = or i1 %polly.overflow.state65, %polly.access.add..obit68
; IR-NEXT:   %polly.access.add..res70 = extractvalue { i64, i1 } %polly.access.add.67, 0
; IR-NEXT:   %polly.access.71 = getelementptr double, double* %polly.access.cast.62, i64 %polly.access.add..res70
; IR-NEXT:   %23 = ptrtoint double* %polly.access.61 to i64
; IR-NEXT:   %24 = ptrtoint double* %polly.access.71 to i64
; IR-NEXT:   %25 = icmp ule i64 %23, %24
; IR-NEXT:   %26 = or i1 %22, %25
; IR-NEXT:   %27 = and i1 %19, %26
; IR-NEXT:   %polly.access.cast.72 = bitcast i8* %1 to double*
; IR-NEXT:   %polly.access.mul.73 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 1023, i64 1024)
; IR-NEXT:   %polly.access.mul..obit74 = extractvalue { i64, i1 } %polly.access.mul.73, 1
; IR-NEXT:   %polly.overflow.state75 = or i1 %polly.overflow.state69, %polly.access.mul..obit74
; IR-NEXT:   %polly.access.mul..res76 = extractvalue { i64, i1 } %polly.access.mul.73, 0
; IR-NEXT:   %polly.access.add.77 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res76, i64 1024)
; IR-NEXT:   %polly.access.add..obit78 = extractvalue { i64, i1 } %polly.access.add.77, 1
; IR-NEXT:   %polly.overflow.state79 = or i1 %polly.overflow.state75, %polly.access.add..obit78
; IR-NEXT:   %polly.access.add..res80 = extractvalue { i64, i1 } %polly.access.add.77, 0
; IR-NEXT:   %polly.access.81 = getelementptr double, double* %polly.access.cast.72, i64 %polly.access.add..res80
; IR-NEXT:   %polly.access.cast.82 = bitcast i8* %9 to double*
; IR-NEXT:   %polly.access.mul.83 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 0, i64 1024)
; IR-NEXT:   %polly.access.mul..obit84 = extractvalue { i64, i1 } %polly.access.mul.83, 1
; IR-NEXT:   %polly.overflow.state85 = or i1 %polly.overflow.state79, %polly.access.mul..obit84
; IR-NEXT:   %polly.access.mul..res86 = extractvalue { i64, i1 } %polly.access.mul.83, 0
; IR-NEXT:   %polly.access.add.87 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res86, i64 0)
; IR-NEXT:   %polly.access.add..obit88 = extractvalue { i64, i1 } %polly.access.add.87, 1
; IR-NEXT:   %polly.overflow.state89 = or i1 %polly.overflow.state85, %polly.access.add..obit88
; IR-NEXT:   %polly.access.add..res90 = extractvalue { i64, i1 } %polly.access.add.87, 0
; IR-NEXT:   %polly.access.91 = getelementptr double, double* %polly.access.cast.82, i64 %polly.access.add..res90
; IR-NEXT:   %28 = ptrtoint double* %polly.access.81 to i64
; IR-NEXT:   %29 = ptrtoint double* %polly.access.91 to i64
; IR-NEXT:   %30 = icmp ule i64 %28, %29
; IR-NEXT:   %polly.access.cast.92 = bitcast i8* %9 to double*
; IR-NEXT:   %polly.access.mul.93 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 1023, i64 1024)
; IR-NEXT:   %polly.access.mul..obit94 = extractvalue { i64, i1 } %polly.access.mul.93, 1
; IR-NEXT:   %polly.overflow.state95 = or i1 %polly.overflow.state89, %polly.access.mul..obit94
; IR-NEXT:   %polly.access.mul..res96 = extractvalue { i64, i1 } %polly.access.mul.93, 0
; IR-NEXT:   %polly.access.add.97 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res96, i64 1024)
; IR-NEXT:   %polly.access.add..obit98 = extractvalue { i64, i1 } %polly.access.add.97, 1
; IR-NEXT:   %polly.overflow.state99 = or i1 %polly.overflow.state95, %polly.access.add..obit98
; IR-NEXT:   %polly.access.add..res100 = extractvalue { i64, i1 } %polly.access.add.97, 0
; IR-NEXT:   %polly.access.101 = getelementptr double, double* %polly.access.cast.92, i64 %polly.access.add..res100
; IR-NEXT:   %polly.access.cast.102 = bitcast i8* %1 to double*
; IR-NEXT:   %polly.access.mul.103 = call { i64, i1 } @llvm.smul.with.overflow.i64(i64 0, i64 1024)
; IR-NEXT:   %polly.access.mul..obit104 = extractvalue { i64, i1 } %polly.access.mul.103, 1
; IR-NEXT:   %polly.overflow.state105 = or i1 %polly.overflow.state99, %polly.access.mul..obit104
; IR-NEXT:   %polly.access.mul..res106 = extractvalue { i64, i1 } %polly.access.mul.103, 0
; IR-NEXT:   %polly.access.add.107 = call { i64, i1 } @llvm.sadd.with.overflow.i64(i64 %polly.access.mul..res106, i64 0)
; IR-NEXT:   %polly.access.add..obit108 = extractvalue { i64, i1 } %polly.access.add.107, 1
; IR-NEXT:   %polly.overflow.state109 = or i1 %polly.overflow.state105, %polly.access.add..obit108
; IR-NEXT:   %polly.access.add..res110 = extractvalue { i64, i1 } %polly.access.add.107, 0
; IR-NEXT:   %polly.access.111 = getelementptr double, double* %polly.access.cast.102, i64 %polly.access.add..res110
; IR-NEXT:   %31 = ptrtoint double* %polly.access.101 to i64
; IR-NEXT:   %32 = ptrtoint double* %polly.access.111 to i64
; IR-NEXT:   %33 = icmp ule i64 %31, %32
; IR-NEXT:   %34 = or i1 %30, %33
; IR-NEXT:   %35 = and i1 %27, %34
; IR-NEXT:   %polly.rtc.overflown = xor i1 %polly.overflow.state109, true
; IR-NEXT:   %polly.rtc.result = and i1 %35, %polly.rtc.overflown
; IR-NEXT:   br i1 %polly.rtc.result, label %polly.start, label %for.cond1.preheader.i
;
; IR:      for.cond1.preheader.i:                            ; preds = %polly.split_new_and_old, %for.inc8.i
; IR-NEXT:   %indvars.iv19.i = phi i64 [ %indvars.iv.next20.i, %for.inc8.i ], [ 0, %polly.split_new_and_old ]
; IR-NEXT:   %36 = trunc i64 %indvars.iv19.i to i32
; IR-NEXT:   %conv.i = sitofp i32 %36 to double
; IR-NEXT:   br label %for.body3.i
;
; IR:      for.body3.i:                                      ; preds = %for.body3.i, %for.cond1.preheader.i
; IR-NEXT:   %indvars.iv16.i = phi i64 [ 0, %for.cond1.preheader.i ], [ %indvars.iv.next17.i, %for.body3.i ]
; IR-NEXT:   %37 = trunc i64 %indvars.iv16.i to i32
; IR-NEXT:   %conv4.i = sitofp i32 %37 to double
; IR-NEXT:   %mul.i = fmul double %conv.i, %conv4.i
; IR-NEXT:   %div.i = fmul double %mul.i, 9.765625e-04
; IR-NEXT:   %arrayidx7.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay, i64 %indvars.iv19.i, i64 %indvars.iv16.i
; IR-NEXT:   store double %div.i, double* %arrayidx7.i, align 8, !tbaa !1
; IR-NEXT:   %indvars.iv.next17.i = add nuw nsw i64 %indvars.iv16.i, 1
; IR-NEXT:   %exitcond18.i = icmp eq i64 %indvars.iv.next17.i, 1024
; IR-NEXT:   br i1 %exitcond18.i, label %for.inc8.i, label %for.body3.i
;
; IR:      for.inc8.i:                                       ; preds = %for.body3.i
; IR-NEXT:   %indvars.iv.next20.i = add nuw nsw i64 %indvars.iv19.i, 1
; IR-NEXT:   %exitcond21.i = icmp eq i64 %indvars.iv.next20.i, 1024
; IR-NEXT:   br i1 %exitcond21.i, label %for.cond15.preheader.i.preheader, label %for.cond1.preheader.i
;
; IR:      for.cond15.preheader.i.preheader:                 ; preds = %for.inc8.i
; IR-NEXT:   %arraydecay4 = bitcast i8* %9 to [1024 x double]*
; IR-NEXT:   br label %for.cond15.preheader.i
;
; IR:      for.cond15.preheader.i:                           ; preds = %for.inc31.i, %for.cond15.preheader.i.preheader
; IR-NEXT:   %indvars.iv13.i = phi i64 [ %indvars.iv.next14.i, %for.inc31.i ], [ 0, %for.cond15.preheader.i.preheader ]
; IR-NEXT:   %38 = trunc i64 %indvars.iv13.i to i32
; IR-NEXT:   %conv19.i = sitofp i32 %38 to double
; IR-NEXT:   br label %for.body18.i
;
; IR:      for.body18.i:                                     ; preds = %for.body18.i, %for.cond15.preheader.i
; IR-NEXT:   %indvars.iv10.i = phi i64 [ 0, %for.cond15.preheader.i ], [ %indvars.iv.next11.i, %for.body18.i ]
; IR-NEXT:   %39 = trunc i64 %indvars.iv10.i to i32
; IR-NEXT:   %conv20.i = sitofp i32 %39 to double
; IR-NEXT:   %mul21.i = fmul double %conv19.i, %conv20.i
; IR-NEXT:   %div23.i = fmul double %mul21.i, 9.765625e-04
; IR-NEXT:   %arrayidx27.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay3, i64 %indvars.iv13.i, i64 %indvars.iv10.i
; IR-NEXT:   store double %div23.i, double* %arrayidx27.i, align 8, !tbaa !1
; IR-NEXT:   %indvars.iv.next11.i = add nuw nsw i64 %indvars.iv10.i, 1
; IR-NEXT:   %exitcond12.i = icmp eq i64 %indvars.iv.next11.i, 1024
; IR-NEXT:   br i1 %exitcond12.i, label %for.inc31.i, label %for.body18.i
;
; IR:      for.inc31.i:                                      ; preds = %for.body18.i
; IR-NEXT:   %indvars.iv.next14.i = add nuw nsw i64 %indvars.iv13.i, 1
; IR-NEXT:   %exitcond15.i = icmp eq i64 %indvars.iv.next14.i, 1024
; IR-NEXT:   br i1 %exitcond15.i, label %for.cond38.preheader.i, label %for.cond15.preheader.i
;
; IR:      for.cond38.preheader.i:                           ; preds = %for.inc54.i, %for.inc31.i
; IR-NEXT:   %indvars.iv7.i = phi i64 [ %indvars.iv.next8.i, %for.inc54.i ], [ 0, %for.inc31.i ]
; IR-NEXT:   %40 = trunc i64 %indvars.iv7.i to i32
; IR-NEXT:   %conv42.i = sitofp i32 %40 to double
; IR-NEXT:   br label %for.body41.i
;
; IR:      for.body41.i:                                     ; preds = %for.body41.i, %for.cond38.preheader.i
; IR-NEXT:   %indvars.iv.i = phi i64 [ 0, %for.cond38.preheader.i ], [ %indvars.iv.next.i, %for.body41.i ]
; IR-NEXT:   %41 = trunc i64 %indvars.iv.i to i32
; IR-NEXT:   %conv43.i = sitofp i32 %41 to double
; IR-NEXT:   %mul44.i = fmul double %conv42.i, %conv43.i
; IR-NEXT:   %div46.i = fmul double %mul44.i, 9.765625e-04
; IR-NEXT:   %arrayidx50.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay4, i64 %indvars.iv7.i, i64 %indvars.iv.i
; IR-NEXT:   store double %div46.i, double* %arrayidx50.i, align 8, !tbaa !1
; IR-NEXT:   %indvars.iv.next.i = add nuw nsw i64 %indvars.iv.i, 1
; IR-NEXT:   %exitcond.i = icmp eq i64 %indvars.iv.next.i, 1024
; IR-NEXT:   br i1 %exitcond.i, label %for.inc54.i, label %for.body41.i
;
; IR:      for.inc54.i:                                      ; preds = %for.body41.i
; IR-NEXT:   %indvars.iv.next8.i = add nuw nsw i64 %indvars.iv7.i, 1
; IR-NEXT:   %exitcond9.i = icmp eq i64 %indvars.iv.next8.i, 1024
; IR-NEXT:   br i1 %exitcond9.i, label %for.cond1.preheader.i42, label %for.cond38.preheader.i
;
; IR:      for.cond1.preheader.i42:                          ; preds = %for.inc26.i, %for.inc54.i
; IR-NEXT:   %indvars.iv7.i41 = phi i64 [ %indvars.iv.next8.i48, %for.inc26.i ], [ 0, %for.inc54.i ]
; IR-NEXT:   br label %for.body3.i44
;
; IR:      for.body3.i44:                                    ; preds = %for.inc23.i, %for.cond1.preheader.i42
; IR-NEXT:   %indvars.iv4.i = phi i64 [ 0, %for.cond1.preheader.i42 ], [ %indvars.iv.next5.i, %for.inc23.i ]
; IR-NEXT:   %arrayidx5.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay, i64 %indvars.iv7.i41, i64 %indvars.iv4.i
; IR-NEXT:   %42 = load double, double* %arrayidx5.i, align 8, !tbaa !1
; IR-NEXT:   %mul.i43 = fmul double %42, 2.123000e+03
; IR-NEXT:   store double %mul.i43, double* %arrayidx5.i, align 8, !tbaa !1
; IR-NEXT:   br label %for.body8.i
;
; IR:      for.body8.i:                                      ; preds = %for.body8.i, %for.body3.i44
; IR-NEXT:   %43 = phi double [ %mul.i43, %for.body3.i44 ], [ %add.i, %for.body8.i ]
; IR-NEXT:   %indvars.iv.i45 = phi i64 [ 0, %for.body3.i44 ], [ %indvars.iv.next.i46, %for.body8.i ]
; IR-NEXT:   %arrayidx12.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay3, i64 %indvars.iv7.i41, i64 %indvars.iv.i45
; IR-NEXT:   %44 = load double, double* %arrayidx12.i, align 8, !tbaa !1
; IR-NEXT:   %mul13.i = fmul double %44, 3.241200e+04
; IR-NEXT:   %arrayidx17.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay4, i64 %indvars.iv.i45, i64 %indvars.iv4.i
; IR-NEXT:   %45 = load double, double* %arrayidx17.i, align 8, !tbaa !1
; IR-NEXT:   %mul18.i = fmul double %mul13.i, %45
; IR-NEXT:   %add.i = fadd double %43, %mul18.i
; IR-NEXT:   store double %add.i, double* %arrayidx5.i, align 8, !tbaa !1
; IR-NEXT:   %indvars.iv.next.i46 = add nuw nsw i64 %indvars.iv.i45, 1
; IR-NEXT:   %exitcond.i47 = icmp eq i64 %indvars.iv.next.i46, 1024
; IR-NEXT:   br i1 %exitcond.i47, label %for.inc23.i, label %for.body8.i
;
; IR:      for.inc23.i:                                      ; preds = %for.body8.i
; IR-NEXT:   %indvars.iv.next5.i = add nuw nsw i64 %indvars.iv4.i, 1
; IR-NEXT:   %exitcond6.i = icmp eq i64 %indvars.iv.next5.i, 1024
; IR-NEXT:   br i1 %exitcond6.i, label %for.inc26.i, label %for.body3.i44
;
; IR:      for.inc26.i:                                      ; preds = %for.inc23.i
; IR-NEXT:   %indvars.iv.next8.i48 = add nuw nsw i64 %indvars.iv7.i41, 1
; IR-NEXT:   %exitcond9.i49 = icmp eq i64 %indvars.iv.next8.i48, 1024
; IR-NEXT:   br i1 %exitcond9.i49, label %polly.merge_new_and_old, label %for.cond1.preheader.i42
;
; IR:      polly.merge_new_and_old:                          ; preds = %polly.exiting, %for.inc26.i
; IR-NEXT:   br label %kernel_gemm.exit
;
; IR:      kernel_gemm.exit:                                 ; preds = %polly.merge_new_and_old
; IR-NEXT:   %call.i = call noalias i8* @malloc(i64 16385) #7
; IR-NEXT:   %arrayidx.i = getelementptr inbounds i8, i8* %call.i, i64 16384
; IR-NEXT:   store i8 0, i8* %arrayidx.i, align 1, !tbaa !7
; IR-NEXT:   %scevgep247 = getelementptr i8, i8* %call.i, i64 1
; IR-NEXT:   %scevgep249 = getelementptr i8, i8* %call.i, i64 2
; IR-NEXT:   %scevgep251 = getelementptr i8, i8* %call.i, i64 3
; IR-NEXT:   %scevgep253 = getelementptr i8, i8* %call.i, i64 4
; IR-NEXT:   %scevgep255 = getelementptr i8, i8* %call.i, i64 5
; IR-NEXT:   %scevgep257 = getelementptr i8, i8* %call.i, i64 6
; IR-NEXT:   %scevgep259 = getelementptr i8, i8* %call.i, i64 7
; IR-NEXT:   %scevgep261 = getelementptr i8, i8* %call.i, i64 8
; IR-NEXT:   %scevgep263 = getelementptr i8, i8* %call.i, i64 9
; IR-NEXT:   %scevgep265 = getelementptr i8, i8* %call.i, i64 10
; IR-NEXT:   %scevgep267 = getelementptr i8, i8* %call.i, i64 11
; IR-NEXT:   %scevgep269 = getelementptr i8, i8* %call.i, i64 12
; IR-NEXT:   %scevgep271 = getelementptr i8, i8* %call.i, i64 13
; IR-NEXT:   %scevgep273 = getelementptr i8, i8* %call.i, i64 14
; IR-NEXT:   %scevgep275 = getelementptr i8, i8* %call.i, i64 15
; IR-NEXT:   br label %for.cond3.preheader.i
;
; IR:      for.cond3.preheader.i:                            ; preds = %for.end.i, %kernel_gemm.exit
; IR-NEXT:   %indvars.iv4.i50 = phi i64 [ 0, %kernel_gemm.exit ], [ %indvars.iv.next5.i54, %for.end.i ]
; IR-NEXT:   %46 = shl i64 %indvars.iv4.i50, 0
; IR-NEXT:   %47 = add i64 %46, 0
; IR-NEXT:   br label %polly.split_new_and_old232
;
; IR:      polly.split_new_and_old232:                       ; preds = %for.cond3.preheader.i
; IR-NEXT:   br i1 true, label %polly.start234, label %for.body6.i
;
; IR:      for.body6.i:                                      ; preds = %polly.split_new_and_old232, %for.body6.i
; IR-NEXT:   %indvars.iv.i51 = phi i64 [ %indvars.iv.next.i52, %for.body6.i ], [ 0, %polly.split_new_and_old232 ]
; IR-NEXT:   %arrayidx10.i = getelementptr inbounds [1024 x double], [1024 x double]* %arraydecay, i64 %indvars.iv4.i50, i64 %indvars.iv.i51
; IR-NEXT:   %48 = bitcast double* %arrayidx10.i to i64*
; IR-NEXT:   %49 = load i64, i64* %48, align 8, !tbaa !1
; IR-NEXT:   %50 = shl nsw i64 %indvars.iv.i51, 4
; IR-NEXT:   %block.sroa.0.0.extract.trunc138.i.i = trunc i64 %49 to i8
; IR-NEXT:   %and.i.i = and i8 %block.sroa.0.0.extract.trunc138.i.i, 15
; IR-NEXT:   %add.i.i = or i8 %and.i.i, 48
; IR-NEXT:   %add.ptr.i.i = getelementptr inbounds i8, i8* %call.i, i64 %50
; IR-NEXT:   store i8 %add.i.i, i8* %add.ptr.i.i, align 1, !tbaa !7
; IR-NEXT:   %add.ptr10.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 1
; IR-NEXT:   store i8 %add.i.i, i8* %add.ptr10.i.i, align 1, !tbaa !7
; IR-NEXT:   %block.sroa.0.1.extract.shift.i.i = lshr i64 %49, 8
; IR-NEXT:   %conv13195.i.i = trunc i64 %block.sroa.0.1.extract.shift.i.i to i8
; IR-NEXT:   %and14.i.i = and i8 %conv13195.i.i, 15
; IR-NEXT:   %add15.i.i = or i8 %and14.i.i, 48
; IR-NEXT:   %add.ptr19.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 2
; IR-NEXT:   store i8 %add15.i.i, i8* %add.ptr19.i.i, align 1, !tbaa !7
; IR-NEXT:   %add.ptr28.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 3
; IR-NEXT:   store i8 %add15.i.i, i8* %add.ptr28.i.i, align 1, !tbaa !7
; IR-NEXT:   %block.sroa.0.2.extract.shift.i.i = lshr i64 %49, 16
; IR-NEXT:   %conv31201.i.i = trunc i64 %block.sroa.0.2.extract.shift.i.i to i8
; IR-NEXT:   %and32.i.i = and i8 %conv31201.i.i, 15
; IR-NEXT:   %add33.i.i = or i8 %and32.i.i, 48
; IR-NEXT:   %add.ptr37.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 4
; IR-NEXT:   store i8 %add33.i.i, i8* %add.ptr37.i.i, align 1, !tbaa !7
; IR-NEXT:   %add.ptr46.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 5
; IR-NEXT:   store i8 %add33.i.i, i8* %add.ptr46.i.i, align 1, !tbaa !7
; IR-NEXT:   %.tr.i.i = trunc i64 %49 to i32
; IR-NEXT:   %sext204207.i.i = lshr i32 %.tr.i.i, 24
; IR-NEXT:   %and50.i.i = and i32 %sext204207.i.i, 15
; IR-NEXT:   %add51.i.i = or i32 %and50.i.i, 48
; IR-NEXT:   %conv52.i.i = trunc i32 %add51.i.i to i8
; IR-NEXT:   %add.ptr55.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 6
; IR-NEXT:   store i8 %conv52.i.i, i8* %add.ptr55.i.i, align 1, !tbaa !7
; IR-NEXT:   %add.ptr64.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 7
; IR-NEXT:   store i8 %conv52.i.i, i8* %add.ptr64.i.i, align 1, !tbaa !7
; IR-NEXT:   %block.sroa.0.4.extract.shift.i.i = lshr i64 %49, 32
; IR-NEXT:   %conv67211.i.i = trunc i64 %block.sroa.0.4.extract.shift.i.i to i8
; IR-NEXT:   %and68.i.i = and i8 %conv67211.i.i, 15
; IR-NEXT:   %add69.i.i = or i8 %and68.i.i, 48
; IR-NEXT:   %add.ptr73.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 8
; IR-NEXT:   store i8 %add69.i.i, i8* %add.ptr73.i.i, align 1, !tbaa !7
; IR-NEXT:   %add.ptr82.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 9
; IR-NEXT:   store i8 %add69.i.i, i8* %add.ptr82.i.i, align 1, !tbaa !7
; IR-NEXT:   %block.sroa.0.5.extract.shift.i.i = lshr i64 %49, 40
; IR-NEXT:   %conv85217.i.i = trunc i64 %block.sroa.0.5.extract.shift.i.i to i8
; IR-NEXT:   %and86.i.i = and i8 %conv85217.i.i, 15
; IR-NEXT:   %add87.i.i = or i8 %and86.i.i, 48
; IR-NEXT:   %add.ptr91.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 10
; IR-NEXT:   store i8 %add87.i.i, i8* %add.ptr91.i.i, align 1, !tbaa !7
; IR-NEXT:   %add.ptr100.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 11
; IR-NEXT:   store i8 %add87.i.i, i8* %add.ptr100.i.i, align 1, !tbaa !7
; IR-NEXT:   %block.sroa.0.6.extract.shift.i.i = lshr i64 %49, 48
; IR-NEXT:   %conv103223.i.i = trunc i64 %block.sroa.0.6.extract.shift.i.i to i8
; IR-NEXT:   %and104.i.i = and i8 %conv103223.i.i, 15
; IR-NEXT:   %add105.i.i = or i8 %and104.i.i, 48
; IR-NEXT:   %add.ptr109.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 12
; IR-NEXT:   store i8 %add105.i.i, i8* %add.ptr109.i.i, align 1, !tbaa !7
; IR-NEXT:   %add.ptr118.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 13
; IR-NEXT:   store i8 %add105.i.i, i8* %add.ptr118.i.i, align 1, !tbaa !7
; IR-NEXT:   %block.sroa.0.7.extract.shift.i.i = lshr i64 %49, 56
; IR-NEXT:   %conv121229.i.i = trunc i64 %block.sroa.0.7.extract.shift.i.i to i8
; IR-NEXT:   %and122.i.i = and i8 %conv121229.i.i, 15
; IR-NEXT:   %add123.i.i = or i8 %and122.i.i, 48
; IR-NEXT:   %add.ptr127.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 14
; IR-NEXT:   store i8 %add123.i.i, i8* %add.ptr127.i.i, align 1, !tbaa !7
; IR-NEXT:   %add.ptr136.i.i = getelementptr inbounds i8, i8* %add.ptr.i.i, i64 15
; IR-NEXT:   store i8 %add123.i.i, i8* %add.ptr136.i.i, align 1, !tbaa !7
; IR-NEXT:   %indvars.iv.next.i52 = add nuw nsw i64 %indvars.iv.i51, 1
; IR-NEXT:   %exitcond.i53 = icmp eq i64 %indvars.iv.next.i52, 1024
; IR-NEXT:   br i1 %exitcond.i53, label %polly.merge_new_and_old233, label %for.body6.i
;
; IR:      polly.merge_new_and_old233:                       ; preds = %polly.exiting235, %for.body6.i
; IR-NEXT:   br label %for.end.i
;
; IR:      for.end.i:                                        ; preds = %polly.merge_new_and_old233
; IR-NEXT:   %51 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !5
; IR-NEXT:   %call12.i = call i32 @fputs(i8* nonnull %call.i, %struct._IO_FILE* %51) #9
; IR-NEXT:   %indvars.iv.next5.i54 = add nuw nsw i64 %indvars.iv4.i50, 1
; IR-NEXT:   %exitcond6.i55 = icmp eq i64 %indvars.iv.next5.i54, 1024
; IR-NEXT:   br i1 %exitcond6.i55, label %print_array.exit, label %for.cond3.preheader.i
;
; IR:      print_array.exit:                                 ; preds = %for.end.i
; IR-NEXT:   call void @free(i8* nonnull %call.i) #7
; IR-NEXT:   call void @free(i8* nonnull %1) #7
; IR-NEXT:   call void @free(i8* %5) #7
; IR-NEXT:   call void @free(i8* %9) #7
; IR-NEXT:   ret i32 0
;
; IR:      polly.start:                                      ; preds = %polly.split_new_and_old
; IR-NEXT:   br label %polly.loop_preheader
;
; IR:      polly.loop_exit:                                  ; preds = %polly.loop_exit114
; IR-NEXT:   br label %polly.loop_preheader121
;
; IR:      polly.loop_exit122:                               ; preds = %polly.loop_exit128
; IR-NEXT:   br label %polly.loop_preheader136
;
; IR:      polly.loop_exit137:                               ; preds = %polly.loop_exit143
; IR-NEXT:   br label %polly.loop_preheader166
;
; IR:      polly.loop_exit167:                               ; preds = %polly.loop_exit173
; IR-NEXT:   br label %polly.loop_preheader181
;
; IR:      polly.loop_exit182:                               ; preds = %polly.loop_exit188
; IR-NEXT:   br label %polly.exiting
;
; IR:      polly.exiting:                                    ; preds = %polly.loop_exit182
; IR-NEXT:   br label %polly.merge_new_and_old
;
; IR:      polly.loop_header:                                ; preds = %polly.loop_exit114, %polly.loop_preheader
; IR-NEXT:   %polly.indvar = phi i64 [ 0, %polly.loop_preheader ], [ %polly.indvar_next, %polly.loop_exit114 ]
; IR-NEXT:   br label %polly.stmt.for.cond38.preheader.i
;
; IR:      polly.stmt.for.cond38.preheader.i:                ; preds = %polly.loop_header
; IR-NEXT:   %52 = trunc i64 %polly.indvar to i32
; IR-NEXT:   %p_conv42.i = sitofp i32 %52 to double
; IR-NEXT:   store double %p_conv42.i, double* %conv42.i.s2a
; IR-NEXT:   br label %polly.loop_preheader113
;
; IR:      polly.loop_exit114:                               ; preds = %polly.stmt.for.body41.i
; IR-NEXT:   %polly.indvar_next = add nsw i64 %polly.indvar, 1
; IR-NEXT:   %polly.loop_cond = icmp sle i64 %polly.indvar, 1022
; IR-NEXT:   br i1 %polly.loop_cond, label %polly.loop_header, label %polly.loop_exit
;
; IR:      polly.loop_preheader:                             ; preds = %polly.start
; IR-NEXT:   br label %polly.loop_header
;
; IR:      polly.loop_header112:                             ; preds = %polly.stmt.for.body41.i, %polly.loop_preheader113
; IR-NEXT:   %polly.indvar115 = phi i64 [ 0, %polly.loop_preheader113 ], [ %polly.indvar_next116, %polly.stmt.for.body41.i ]
; IR-NEXT:   br label %polly.stmt.for.body41.i
;
; IR:      polly.stmt.for.body41.i:                          ; preds = %polly.loop_header112
; IR-NEXT:   %conv42.i.s2a.reload = load double, double* %conv42.i.s2a
; IR-NEXT:   %53 = trunc i64 %polly.indvar115 to i32
; IR-NEXT:   %p_conv43.i = sitofp i32 %53 to double
; IR-NEXT:   %p_mul44.i = fmul double %conv42.i.s2a.reload, %p_conv43.i
; IR-NEXT:   %p_div46.i = fmul double %p_mul44.i, 9.765625e-04
; IR-NEXT:   %54 = shl i64 %polly.indvar115, 3
; IR-NEXT:   %scevgep118 = getelementptr i8, i8* %scevgep, i64 %54
; IR-NEXT:   %scevgep118119 = bitcast i8* %scevgep118 to double*
; IR-NEXT:   store double %p_div46.i, double* %scevgep118119, align 8, !alias.scope !8, !noalias !10
; IR-NEXT:   %polly.indvar_next116 = add nsw i64 %polly.indvar115, 1
; IR-NEXT:   %polly.loop_cond117 = icmp sle i64 %polly.indvar115, 1022
; IR-NEXT:   br i1 %polly.loop_cond117, label %polly.loop_header112, label %polly.loop_exit114
;
; IR:      polly.loop_preheader113:                          ; preds = %polly.stmt.for.cond38.preheader.i
; IR-NEXT:   %55 = shl i64 %polly.indvar, 13
; IR-NEXT:   %scevgep = getelementptr i8, i8* %9, i64 %55
; IR-NEXT:   br label %polly.loop_header112
;
; IR:      polly.loop_header120:                             ; preds = %polly.loop_exit128, %polly.loop_preheader121
; IR-NEXT:   %polly.indvar123 = phi i64 [ 0, %polly.loop_preheader121 ], [ %polly.indvar_next124, %polly.loop_exit128 ]
; IR-NEXT:   br label %polly.stmt.for.cond1.preheader.i
;
; IR:      polly.stmt.for.cond1.preheader.i:                 ; preds = %polly.loop_header120
; IR-NEXT:   %56 = trunc i64 %polly.indvar123 to i32
; IR-NEXT:   %p_conv.i = sitofp i32 %56 to double
; IR-NEXT:   store double %p_conv.i, double* %conv.i.s2a
; IR-NEXT:   br label %polly.loop_preheader127
;
; IR:      polly.loop_exit128:                               ; preds = %polly.stmt.for.body3.i
; IR-NEXT:   %polly.indvar_next124 = add nsw i64 %polly.indvar123, 1
; IR-NEXT:   %polly.loop_cond125 = icmp sle i64 %polly.indvar123, 1022
; IR-NEXT:   br i1 %polly.loop_cond125, label %polly.loop_header120, label %polly.loop_exit122
;
; IR:      polly.loop_preheader121:                          ; preds = %polly.loop_exit
; IR-NEXT:   br label %polly.loop_header120
;
; IR:      polly.loop_header126:                             ; preds = %polly.stmt.for.body3.i, %polly.loop_preheader127
; IR-NEXT:   %polly.indvar129 = phi i64 [ 0, %polly.loop_preheader127 ], [ %polly.indvar_next130, %polly.stmt.for.body3.i ]
; IR-NEXT:   br label %polly.stmt.for.body3.i
;
; IR:      polly.stmt.for.body3.i:                           ; preds = %polly.loop_header126
; IR-NEXT:   %conv.i.s2a.reload = load double, double* %conv.i.s2a
; IR-NEXT:   %57 = trunc i64 %polly.indvar129 to i32
; IR-NEXT:   %p_conv4.i = sitofp i32 %57 to double
; IR-NEXT:   %p_mul.i = fmul double %conv.i.s2a.reload, %p_conv4.i
; IR-NEXT:   %p_div.i = fmul double %p_mul.i, 9.765625e-04
; IR-NEXT:   %58 = shl i64 %polly.indvar129, 3
; IR-NEXT:   %scevgep133 = getelementptr i8, i8* %scevgep132, i64 %58
; IR-NEXT:   %scevgep133134 = bitcast i8* %scevgep133 to double*
; IR-NEXT:   store double %p_div.i, double* %scevgep133134, align 8, !alias.scope !11, !noalias !17
; IR-NEXT:   %polly.indvar_next130 = add nsw i64 %polly.indvar129, 1
; IR-NEXT:   %polly.loop_cond131 = icmp sle i64 %polly.indvar129, 1022
; IR-NEXT:   br i1 %polly.loop_cond131, label %polly.loop_header126, label %polly.loop_exit128
;
; IR:      polly.loop_preheader127:                          ; preds = %polly.stmt.for.cond1.preheader.i
; IR-NEXT:   %59 = shl i64 %polly.indvar123, 13
; IR-NEXT:   %scevgep132 = getelementptr i8, i8* %1, i64 %59
; IR-NEXT:   br label %polly.loop_header126
;
; IR:      polly.loop_header135:                             ; preds = %polly.loop_exit143, %polly.loop_preheader136
; IR-NEXT:   %polly.indvar138 = phi i64 [ 0, %polly.loop_preheader136 ], [ %polly.indvar_next139, %polly.loop_exit143 ]
; IR-NEXT:   br label %polly.loop_preheader142
;
; IR:      polly.loop_exit143:                               ; preds = %polly.loop_exit149
; IR-NEXT:   %polly.indvar_next139 = add nsw i64 %polly.indvar138, 1
; IR-NEXT:   %polly.loop_cond140 = icmp sle i64 %polly.indvar138, 30
; IR-NEXT:   br i1 %polly.loop_cond140, label %polly.loop_header135, label %polly.loop_exit137
;
; IR:      polly.loop_preheader136:                          ; preds = %polly.loop_exit122
; IR-NEXT:   br label %polly.loop_header135
;
; IR:      polly.loop_header141:                             ; preds = %polly.loop_exit149, %polly.loop_preheader142
; IR-NEXT:   %polly.indvar144 = phi i64 [ 0, %polly.loop_preheader142 ], [ %polly.indvar_next145, %polly.loop_exit149 ]
; IR-NEXT:   br label %polly.loop_preheader148
;
; IR:      polly.loop_exit149:                               ; preds = %polly.loop_exit155
; IR-NEXT:   %polly.indvar_next145 = add nsw i64 %polly.indvar144, 1
; IR-NEXT:   %polly.loop_cond146 = icmp sle i64 %polly.indvar144, 30
; IR-NEXT:   br i1 %polly.loop_cond146, label %polly.loop_header141, label %polly.loop_exit143
;
; IR:      polly.loop_preheader142:                          ; preds = %polly.loop_header135
; IR-NEXT:   br label %polly.loop_header141
;
; IR:      polly.loop_header147:                             ; preds = %polly.loop_exit155, %polly.loop_preheader148
; IR-NEXT:   %polly.indvar150 = phi i64 [ 0, %polly.loop_preheader148 ], [ %polly.indvar_next151, %polly.loop_exit155 ]
; IR-NEXT:   br label %polly.loop_preheader154
;
; IR:      polly.loop_exit155:                               ; preds = %polly.stmt.for.body3.i44
; IR-NEXT:   %polly.indvar_next151 = add nsw i64 %polly.indvar150, 1
; IR-NEXT:   %polly.loop_cond152 = icmp sle i64 %polly.indvar150, 30
; IR-NEXT:   br i1 %polly.loop_cond152, label %polly.loop_header147, label %polly.loop_exit149
;
; IR:      polly.loop_preheader148:                          ; preds = %polly.loop_header141
; IR-NEXT:   br label %polly.loop_header147
;
; IR:      polly.loop_header153:                             ; preds = %polly.stmt.for.body3.i44, %polly.loop_preheader154
; IR-NEXT:   %polly.indvar156 = phi i64 [ 0, %polly.loop_preheader154 ], [ %polly.indvar_next157, %polly.stmt.for.body3.i44 ]
; IR-NEXT:   %60 = mul nsw i64 32, %polly.indvar138
; IR-NEXT:   %61 = add nsw i64 %60, %polly.indvar150
; IR-NEXT:   %62 = mul nsw i64 32, %polly.indvar144
; IR-NEXT:   %63 = add nsw i64 %62, %polly.indvar156
; IR-NEXT:   br label %polly.stmt.for.body3.i44
;
; IR:      polly.stmt.for.body3.i44:                         ; preds = %polly.loop_header153
; IR-NEXT:   %64 = shl i64 %61, 13
; IR-NEXT:   %65 = shl i64 %63, 3
; IR-NEXT:   %66 = add i64 %64, %65
; IR-NEXT:   %scevgep159 = getelementptr i8, i8* %1, i64 %66
; IR-NEXT:   %scevgep159160 = bitcast i8* %scevgep159 to double*
; IR-NEXT:   %_p_scalar_ = load double, double* %scevgep159160, align 8, !alias.scope !11, !noalias !17
; IR-NEXT:   %p_mul.i43 = fmul double %_p_scalar_, 2.123000e+03
; IR-NEXT:   store double %p_mul.i43, double* %scevgep159160, align 8, !alias.scope !11, !noalias !17
; IR-NEXT:   %polly.access.cast.161 = bitcast i8* %1 to double*
; IR-NEXT:   %67 = mul nsw i64 32, %polly.indvar138
; IR-NEXT:   %68 = add nsw i64 %67, %polly.indvar150
; IR-NEXT:   %polly.access.mul.162 = mul nsw i64 %68, 1024
; IR-NEXT:   %69 = mul nsw i64 32, %polly.indvar144
; IR-NEXT:   %70 = add nsw i64 %69, %polly.indvar156
; IR-NEXT:   %polly.access.add.163 = add nsw i64 %polly.access.mul.162, %70
; IR-NEXT:   %polly.access.164 = getelementptr double, double* %polly.access.cast.161, i64 %polly.access.add.163
; IR-NEXT:   store double %p_mul.i43, double* %polly.access.164, !alias.scope !11, !noalias !17
; IR-NEXT:   %polly.indvar_next157 = add nsw i64 %polly.indvar156, 1
; IR-NEXT:   %polly.loop_cond158 = icmp sle i64 %polly.indvar156, 30
; IR-NEXT:   br i1 %polly.loop_cond158, label %polly.loop_header153, label %polly.loop_exit155
;
; IR:      polly.loop_preheader154:                          ; preds = %polly.loop_header147
; IR-NEXT:   br label %polly.loop_header153
;
; IR:      polly.loop_header165:                             ; preds = %polly.loop_exit173, %polly.loop_preheader166
; IR-NEXT:   %polly.indvar168 = phi i64 [ 0, %polly.loop_preheader166 ], [ %polly.indvar_next169, %polly.loop_exit173 ]
; IR-NEXT:   br label %polly.stmt.for.cond15.preheader.i
;
; IR:      polly.stmt.for.cond15.preheader.i:                ; preds = %polly.loop_header165
; IR-NEXT:   %71 = trunc i64 %polly.indvar168 to i32
; IR-NEXT:   %p_conv19.i = sitofp i32 %71 to double
; IR-NEXT:   store double %p_conv19.i, double* %conv19.i.s2a
; IR-NEXT:   br label %polly.loop_preheader172
;
; IR:      polly.loop_exit173:                               ; preds = %polly.stmt.for.body18.i
; IR-NEXT:   %polly.indvar_next169 = add nsw i64 %polly.indvar168, 1
; IR-NEXT:   %polly.loop_cond170 = icmp sle i64 %polly.indvar168, 1022
; IR-NEXT:   br i1 %polly.loop_cond170, label %polly.loop_header165, label %polly.loop_exit167
;
; IR:      polly.loop_preheader166:                          ; preds = %polly.loop_exit137
; IR-NEXT:   br label %polly.loop_header165
;
; IR:      polly.loop_header171:                             ; preds = %polly.stmt.for.body18.i, %polly.loop_preheader172
; IR-NEXT:   %polly.indvar174 = phi i64 [ 0, %polly.loop_preheader172 ], [ %polly.indvar_next175, %polly.stmt.for.body18.i ]
; IR-NEXT:   br label %polly.stmt.for.body18.i
;
; IR:      polly.stmt.for.body18.i:                          ; preds = %polly.loop_header171
; IR-NEXT:   %conv19.i.s2a.reload = load double, double* %conv19.i.s2a
; IR-NEXT:   %72 = trunc i64 %polly.indvar174 to i32
; IR-NEXT:   %p_conv20.i = sitofp i32 %72 to double
; IR-NEXT:   %p_mul21.i = fmul double %conv19.i.s2a.reload, %p_conv20.i
; IR-NEXT:   %p_div23.i = fmul double %p_mul21.i, 9.765625e-04
; IR-NEXT:   %73 = shl i64 %polly.indvar174, 3
; IR-NEXT:   %scevgep178 = getelementptr i8, i8* %scevgep177, i64 %73
; IR-NEXT:   %scevgep178179 = bitcast i8* %scevgep178 to double*
; IR-NEXT:   store double %p_div23.i, double* %scevgep178179, align 8, !alias.scope !16, !noalias !18
; IR-NEXT:   %polly.indvar_next175 = add nsw i64 %polly.indvar174, 1
; IR-NEXT:   %polly.loop_cond176 = icmp sle i64 %polly.indvar174, 1022
; IR-NEXT:   br i1 %polly.loop_cond176, label %polly.loop_header171, label %polly.loop_exit173
;
; IR:      polly.loop_preheader172:                          ; preds = %polly.stmt.for.cond15.preheader.i
; IR-NEXT:   %74 = shl i64 %polly.indvar168, 13
; IR-NEXT:   %scevgep177 = getelementptr i8, i8* %5, i64 %74
; IR-NEXT:   br label %polly.loop_header171
;
; IR:      polly.loop_header180:                             ; preds = %polly.loop_exit188, %polly.loop_preheader181
; IR-NEXT:   %polly.indvar183 = phi i64 [ 0, %polly.loop_preheader181 ], [ %polly.indvar_next184, %polly.loop_exit188 ]
; IR-NEXT:   br label %polly.loop_preheader187
;
; IR:      polly.loop_exit188:                               ; preds = %polly.loop_exit194
; IR-NEXT:   %polly.indvar_next184 = add nsw i64 %polly.indvar183, 1
; IR-NEXT:   %polly.loop_cond185 = icmp sle i64 %polly.indvar183, 30
; IR-NEXT:   br i1 %polly.loop_cond185, label %polly.loop_header180, label %polly.loop_exit182
;
; IR:      polly.loop_preheader181:                          ; preds = %polly.loop_exit167
; IR-NEXT:   br label %polly.loop_header180
;
; IR:      polly.loop_header186:                             ; preds = %polly.loop_exit194, %polly.loop_preheader187
; IR-NEXT:   %polly.indvar189 = phi i64 [ 0, %polly.loop_preheader187 ], [ %polly.indvar_next190, %polly.loop_exit194 ]
; IR-NEXT:   br label %polly.loop_preheader193
;
; IR:      polly.loop_exit194:                               ; preds = %polly.loop_exit200
; IR-NEXT:   %polly.indvar_next190 = add nsw i64 %polly.indvar189, 1
; IR-NEXT:   %polly.loop_cond191 = icmp sle i64 %polly.indvar189, 30
; IR-NEXT:   br i1 %polly.loop_cond191, label %polly.loop_header186, label %polly.loop_exit188
;
; IR:      polly.loop_preheader187:                          ; preds = %polly.loop_header180
; IR-NEXT:   br label %polly.loop_header186
;
; IR:      polly.loop_header192:                             ; preds = %polly.loop_exit200, %polly.loop_preheader193
; IR-NEXT:   %polly.indvar195 = phi i64 [ 0, %polly.loop_preheader193 ], [ %polly.indvar_next196, %polly.loop_exit200 ]
; IR-NEXT:   br label %polly.loop_preheader199
;
; IR:      polly.loop_exit200:                               ; preds = %polly.loop_exit206
; IR-NEXT:   %polly.indvar_next196 = add nsw i64 %polly.indvar195, 1
; IR-NEXT:   %polly.loop_cond197 = icmp sle i64 %polly.indvar195, 30
; IR-NEXT:   br i1 %polly.loop_cond197, label %polly.loop_header192, label %polly.loop_exit194
;
; IR:      polly.loop_preheader193:                          ; preds = %polly.loop_header186
; IR-NEXT:   br label %polly.loop_header192
;
; IR:      polly.loop_header198:                             ; preds = %polly.loop_exit206, %polly.loop_preheader199
; IR-NEXT:   %polly.indvar201 = phi i64 [ 0, %polly.loop_preheader199 ], [ %polly.indvar_next202, %polly.loop_exit206 ]
; IR-NEXT:   br label %polly.loop_preheader205
;
; IR:      polly.loop_exit206:                               ; preds = %polly.loop_exit212
; IR-NEXT:   %polly.indvar_next202 = add nsw i64 %polly.indvar201, 1
; IR-NEXT:   %polly.loop_cond203 = icmp sle i64 %polly.indvar201, 30
; IR-NEXT:   br i1 %polly.loop_cond203, label %polly.loop_header198, label %polly.loop_exit200
;
; IR:      polly.loop_preheader199:                          ; preds = %polly.loop_header192
; IR-NEXT:   br label %polly.loop_header198
;
; IR:      polly.loop_header204:                             ; preds = %polly.loop_exit212, %polly.loop_preheader205
; IR-NEXT:   %polly.indvar207 = phi i64 [ 0, %polly.loop_preheader205 ], [ %polly.indvar_next208, %polly.loop_exit212 ]
; IR-NEXT:   br label %polly.loop_preheader211
;
; IR:      polly.loop_exit212:                               ; preds = %polly.stmt.for.body8.i
; IR-NEXT:   %polly.indvar_next208 = add nsw i64 %polly.indvar207, 1
; IR-NEXT:   %polly.loop_cond209 = icmp sle i64 %polly.indvar207, 30
; IR-NEXT:   br i1 %polly.loop_cond209, label %polly.loop_header204, label %polly.loop_exit206
;
; IR:      polly.loop_preheader205:                          ; preds = %polly.loop_header198
; IR-NEXT:   br label %polly.loop_header204
;
; IR:      polly.loop_header210:                             ; preds = %polly.stmt.for.body8.i, %polly.loop_preheader211
; IR-NEXT:   %polly.indvar213 = phi i64 [ 0, %polly.loop_preheader211 ], [ %polly.indvar_next214, %polly.stmt.for.body8.i ]
; IR-NEXT:   %75 = mul nsw i64 32, %polly.indvar183
; IR-NEXT:   %76 = add nsw i64 %75, %polly.indvar201
; IR-NEXT:   %77 = mul nsw i64 32, %polly.indvar189
; IR-NEXT:   %78 = add nsw i64 %77, %polly.indvar207
; IR-NEXT:   %79 = mul nsw i64 32, %polly.indvar195
; IR-NEXT:   %80 = add nsw i64 %79, %polly.indvar213
; IR-NEXT:   br label %polly.stmt.for.body8.i
;
; IR:      polly.stmt.for.body8.i:                           ; preds = %polly.loop_header210
; IR-NEXT:   %polly.access.cast.216 = bitcast i8* %1 to double*
; IR-NEXT:   %81 = mul nsw i64 32, %polly.indvar183
; IR-NEXT:   %82 = add nsw i64 %81, %polly.indvar201
; IR-NEXT:   %polly.access.mul.217 = mul nsw i64 %82, 1024
; IR-NEXT:   %83 = mul nsw i64 32, %polly.indvar189
; IR-NEXT:   %84 = add nsw i64 %83, %polly.indvar207
; IR-NEXT:   %polly.access.add.218 = add nsw i64 %polly.access.mul.217, %84
; IR-NEXT:   %polly.access.219 = getelementptr double, double* %polly.access.cast.216, i64 %polly.access.add.218
; IR-NEXT:   %polly.access.219.reload = load double, double* %polly.access.219, !alias.scope !11, !noalias !17
; IR-NEXT:   %85 = shl i64 %76, 13
; IR-NEXT:   %86 = shl i64 %80, 3
; IR-NEXT:   %87 = add i64 %85, %86
; IR-NEXT:   %scevgep220 = getelementptr i8, i8* %5, i64 %87
; IR-NEXT:   %scevgep220221 = bitcast i8* %scevgep220 to double*
; IR-NEXT:   %_p_scalar_222 = load double, double* %scevgep220221, align 8, !alias.scope !16, !noalias !18
; IR-NEXT:   %p_mul13.i = fmul double %_p_scalar_222, 3.241200e+04
; IR-NEXT:   %88 = shl i64 %80, 13
; IR-NEXT:   %89 = shl i64 %78, 3
; IR-NEXT:   %90 = add i64 %88, %89
; IR-NEXT:   %scevgep223 = getelementptr i8, i8* %9, i64 %90
; IR-NEXT:   %scevgep223224 = bitcast i8* %scevgep223 to double*
; IR-NEXT:   %_p_scalar_225 = load double, double* %scevgep223224, align 8, !alias.scope !8, !noalias !10
; IR-NEXT:   %p_mul18.i = fmul double %p_mul13.i, %_p_scalar_225
; IR-NEXT:   %p_add.i = fadd double %polly.access.219.reload, %p_mul18.i
; IR-NEXT:   %91 = shl i64 %76, 13
; IR-NEXT:   %92 = shl i64 %78, 3
; IR-NEXT:   %93 = add i64 %91, %92
; IR-NEXT:   %scevgep226 = getelementptr i8, i8* %1, i64 %93
; IR-NEXT:   %scevgep226227 = bitcast i8* %scevgep226 to double*
; IR-NEXT:   store double %p_add.i, double* %scevgep226227, align 8, !alias.scope !11, !noalias !17
; IR-NEXT:   %polly.access.cast.228 = bitcast i8* %1 to double*
; IR-NEXT:   %94 = mul nsw i64 32, %polly.indvar183
; IR-NEXT:   %95 = add nsw i64 %94, %polly.indvar201
; IR-NEXT:   %polly.access.mul.229 = mul nsw i64 %95, 1024
; IR-NEXT:   %96 = mul nsw i64 32, %polly.indvar189
; IR-NEXT:   %97 = add nsw i64 %96, %polly.indvar207
; IR-NEXT:   %polly.access.add.230 = add nsw i64 %polly.access.mul.229, %97
; IR-NEXT:   %polly.access.231 = getelementptr double, double* %polly.access.cast.228, i64 %polly.access.add.230
; IR-NEXT:   store double %p_add.i, double* %polly.access.231, !alias.scope !11, !noalias !17
; IR-NEXT:   %polly.indvar_next214 = add nsw i64 %polly.indvar213, 1
; IR-NEXT:   %polly.loop_cond215 = icmp sle i64 %polly.indvar213, 30
; IR-NEXT:   br i1 %polly.loop_cond215, label %polly.loop_header210, label %polly.loop_exit212
;
; IR:      polly.loop_preheader211:                          ; preds = %polly.loop_header204
; IR-NEXT:   br label %polly.loop_header210
;
; IR:      polly.start234:                                   ; preds = %polly.split_new_and_old232
; IR-NEXT:   br label %polly.loop_preheader237
;
; IR:      polly.loop_exit238:                               ; preds = %polly.stmt.for.body6.i
; IR-NEXT:   br label %polly.exiting235
;
; IR:      polly.exiting235:                                 ; preds = %polly.loop_exit238
; IR-NEXT:   br label %polly.merge_new_and_old233
;
; IR:      polly.loop_header236:                             ; preds = %polly.stmt.for.body6.i, %polly.loop_preheader237
; IR-NEXT:   %polly.indvar239 = phi i64 [ 0, %polly.loop_preheader237 ], [ %polly.indvar_next240, %polly.stmt.for.body6.i ]
; IR-NEXT:   br label %polly.stmt.for.body6.i
;
; IR:      polly.stmt.for.body6.i:                           ; preds = %polly.loop_header236
; IR-NEXT:   %98 = shl i64 %polly.indvar239, 3
; IR-NEXT:   %scevgep243 = getelementptr i8, i8* %scevgep242, i64 %98
; IR-NEXT:   %scevgep243244 = bitcast i8* %scevgep243 to i64*
; IR-NEXT:   %_p_scalar_245 = load i64, i64* %scevgep243244, align 8, !alias.scope !19, !noalias !21
; IR-NEXT:   %p_block.sroa.0.0.extract.trunc138.i.i = trunc i64 %_p_scalar_245 to i8
; IR-NEXT:   %p_and.i.i = and i8 %p_block.sroa.0.0.extract.trunc138.i.i, 15
; IR-NEXT:   %p_add.i.i = or i8 %p_and.i.i, 48
; IR-NEXT:   %99 = shl i64 %polly.indvar239, 4
; IR-NEXT:   %scevgep246 = getelementptr i8, i8* %call.i, i64 %99
; IR-NEXT:   store i8 %p_add.i.i, i8* %scevgep246, align 1, !alias.scope !22, !noalias !23
; IR-NEXT:   %scevgep248 = getelementptr i8, i8* %scevgep247, i64 %99
; IR-NEXT:   store i8 %p_add.i.i, i8* %scevgep248, align 1, !alias.scope !22, !noalias !23
; IR-NEXT:   %p_block.sroa.0.1.extract.shift.i.i = lshr i64 %_p_scalar_245, 8
; IR-NEXT:   %p_conv13195.i.i = trunc i64 %p_block.sroa.0.1.extract.shift.i.i to i8
; IR-NEXT:   %p_and14.i.i = and i8 %p_conv13195.i.i, 15
; IR-NEXT:   %p_add15.i.i = or i8 %p_and14.i.i, 48
; IR-NEXT:   %100 = shl i64 %polly.indvar239, 4
; IR-NEXT:   %scevgep250 = getelementptr i8, i8* %scevgep249, i64 %100
; IR-NEXT:   store i8 %p_add15.i.i, i8* %scevgep250, align 1, !alias.scope !22, !noalias !23
; IR-NEXT:   %scevgep252 = getelementptr i8, i8* %scevgep251, i64 %100
; IR-NEXT:   store i8 %p_add15.i.i, i8* %scevgep252, align 1, !alias.scope !22, !noalias !23
; IR-NEXT:   %p_block.sroa.0.2.extract.shift.i.i = lshr i64 %_p_scalar_245, 16
; IR-NEXT:   %p_conv31201.i.i = trunc i64 %p_block.sroa.0.2.extract.shift.i.i to i8
; IR-NEXT:   %p_and32.i.i = and i8 %p_conv31201.i.i, 15
; IR-NEXT:   %p_add33.i.i = or i8 %p_and32.i.i, 48
; IR-NEXT:   %101 = shl i64 %polly.indvar239, 4
; IR-NEXT:   %scevgep254 = getelementptr i8, i8* %scevgep253, i64 %101
; IR-NEXT:   store i8 %p_add33.i.i, i8* %scevgep254, align 1, !alias.scope !22, !noalias !23
; IR-NEXT:   %scevgep256 = getelementptr i8, i8* %scevgep255, i64 %101
; IR-NEXT:   store i8 %p_add33.i.i, i8* %scevgep256, align 1, !alias.scope !22, !noalias !23
; IR-NEXT:   %p_.tr.i.i = trunc i64 %_p_scalar_245 to i32
; IR-NEXT:   %p_sext204207.i.i = lshr i32 %p_.tr.i.i, 24
; IR-NEXT:   %p_and50.i.i = and i32 %p_sext204207.i.i, 15
; IR-NEXT:   %p_add51.i.i = or i32 %p_and50.i.i, 48
; IR-NEXT:   %p_conv52.i.i = trunc i32 %p_add51.i.i to i8
; IR-NEXT:   %102 = shl i64 %polly.indvar239, 4
; IR-NEXT:   %scevgep258 = getelementptr i8, i8* %scevgep257, i64 %102
; IR-NEXT:   store i8 %p_conv52.i.i, i8* %scevgep258, align 1, !alias.scope !22, !noalias !23
; IR-NEXT:   %scevgep260 = getelementptr i8, i8* %scevgep259, i64 %102
; IR-NEXT:   store i8 %p_conv52.i.i, i8* %scevgep260, align 1, !alias.scope !22, !noalias !23
; IR-NEXT:   %p_block.sroa.0.4.extract.shift.i.i = lshr i64 %_p_scalar_245, 32
; IR-NEXT:   %p_conv67211.i.i = trunc i64 %p_block.sroa.0.4.extract.shift.i.i to i8
; IR-NEXT:   %p_and68.i.i = and i8 %p_conv67211.i.i, 15
; IR-NEXT:   %p_add69.i.i = or i8 %p_and68.i.i, 48
; IR-NEXT:   %103 = shl i64 %polly.indvar239, 4
; IR-NEXT:   %scevgep262 = getelementptr i8, i8* %scevgep261, i64 %103
; IR-NEXT:   store i8 %p_add69.i.i, i8* %scevgep262, align 1, !alias.scope !22, !noalias !23
; IR-NEXT:   %scevgep264 = getelementptr i8, i8* %scevgep263, i64 %103
; IR-NEXT:   store i8 %p_add69.i.i, i8* %scevgep264, align 1, !alias.scope !22, !noalias !23
; IR-NEXT:   %p_block.sroa.0.5.extract.shift.i.i = lshr i64 %_p_scalar_245, 40
; IR-NEXT:   %p_conv85217.i.i = trunc i64 %p_block.sroa.0.5.extract.shift.i.i to i8
; IR-NEXT:   %p_and86.i.i = and i8 %p_conv85217.i.i, 15
; IR-NEXT:   %p_add87.i.i = or i8 %p_and86.i.i, 48
; IR-NEXT:   %104 = shl i64 %polly.indvar239, 4
; IR-NEXT:   %scevgep266 = getelementptr i8, i8* %scevgep265, i64 %104
; IR-NEXT:   store i8 %p_add87.i.i, i8* %scevgep266, align 1, !alias.scope !22, !noalias !23
; IR-NEXT:   %scevgep268 = getelementptr i8, i8* %scevgep267, i64 %104
; IR-NEXT:   store i8 %p_add87.i.i, i8* %scevgep268, align 1, !alias.scope !22, !noalias !23
; IR-NEXT:   %p_block.sroa.0.6.extract.shift.i.i = lshr i64 %_p_scalar_245, 48
; IR-NEXT:   %p_conv103223.i.i = trunc i64 %p_block.sroa.0.6.extract.shift.i.i to i8
; IR-NEXT:   %p_and104.i.i = and i8 %p_conv103223.i.i, 15
; IR-NEXT:   %p_add105.i.i = or i8 %p_and104.i.i, 48
; IR-NEXT:   %105 = shl i64 %polly.indvar239, 4
; IR-NEXT:   %scevgep270 = getelementptr i8, i8* %scevgep269, i64 %105
; IR-NEXT:   store i8 %p_add105.i.i, i8* %scevgep270, align 1, !alias.scope !22, !noalias !23
; IR-NEXT:   %scevgep272 = getelementptr i8, i8* %scevgep271, i64 %105
; IR-NEXT:   store i8 %p_add105.i.i, i8* %scevgep272, align 1, !alias.scope !22, !noalias !23
; IR-NEXT:   %p_block.sroa.0.7.extract.shift.i.i = lshr i64 %_p_scalar_245, 56
; IR-NEXT:   %p_conv121229.i.i = trunc i64 %p_block.sroa.0.7.extract.shift.i.i to i8
; IR-NEXT:   %p_and122.i.i = and i8 %p_conv121229.i.i, 15
; IR-NEXT:   %p_add123.i.i = or i8 %p_and122.i.i, 48
; IR-NEXT:   %106 = shl i64 %polly.indvar239, 4
; IR-NEXT:   %scevgep274 = getelementptr i8, i8* %scevgep273, i64 %106
; IR-NEXT:   store i8 %p_add123.i.i, i8* %scevgep274, align 1, !alias.scope !22, !noalias !23
; IR-NEXT:   %scevgep276 = getelementptr i8, i8* %scevgep275, i64 %106
; IR-NEXT:   store i8 %p_add123.i.i, i8* %scevgep276, align 1, !alias.scope !22, !noalias !23
; IR-NEXT:   %polly.indvar_next240 = add nsw i64 %polly.indvar239, 1
; IR-NEXT:   %polly.loop_cond241 = icmp sle i64 %polly.indvar239, 1022
; IR-NEXT:   br i1 %polly.loop_cond241, label %polly.loop_header236, label %polly.loop_exit238
;
; IR:      polly.loop_preheader237:                          ; preds = %polly.start234
; IR-NEXT:   %107 = shl i64 %47, 13
; IR-NEXT:   %scevgep242 = getelementptr i8, i8* %1, i64 %107
; IR-NEXT:   br label %polly.loop_header236
; IR-NEXT: }
;
; IR:      ; Function Attrs: nounwind
; IR-NEXT: declare i32 @posix_memalign(i8**, i64, i64) local_unnamed_addr #2
;
; IR:      ; Function Attrs: nounwind
; IR-NEXT: declare i32 @fprintf(%struct._IO_FILE* nocapture, i8* nocapture readonly, ...) local_unnamed_addr #2
;
; IR:      ; Function Attrs: noreturn nounwind
; IR-NEXT: declare void @exit(i32) local_unnamed_addr #6
;
; IR:      ; Function Attrs: nounwind
; IR-NEXT: declare noalias i8* @malloc(i64) local_unnamed_addr #2
;
; IR:      ; Function Attrs: nounwind
; IR-NEXT: declare i32 @fputs(i8* nocapture readonly, %struct._IO_FILE* nocapture) local_unnamed_addr #2
;
; IR:      ; Function Attrs: nounwind
; IR-NEXT: declare i64 @fwrite(i8* nocapture, i64, i64, %struct._IO_FILE* nocapture) #7
;
; IR:      ; Function Attrs: nounwind readnone
; IR-NEXT: declare { i64, i1 } @llvm.smul.with.overflow.i64(i64, i64) #8
;
; IR:      ; Function Attrs: nounwind readnone
; IR-NEXT: declare { i64, i1 } @llvm.sadd.with.overflow.i64(i64, i64) #8
;
; IR:      attributes #0 = { norecurse nounwind readnone uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
; IR-NEXT: attributes #1 = { argmemonly nounwind }
; IR-NEXT: attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
; IR-NEXT: attributes #3 = { norecurse nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
; IR-NEXT: attributes #4 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
; IR-NEXT: attributes #5 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "polly-optimized" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
; IR-NEXT: attributes #6 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
; IR-NEXT: attributes #7 = { nounwind }
; IR-NEXT: attributes #8 = { nounwind readnone }
; IR-NEXT: attributes #9 = { cold nounwind }
; IR-NEXT: attributes #10 = { noreturn nounwind }
;
; IR:      !llvm.ident = !{!0}
;
; IR:      !0 = !{!"clang version 4.0.0 (trunk 278052) (llvm/trunk 278053)"}
; IR-NEXT: !1 = !{!2, !2, i64 0}
; IR-NEXT: !2 = !{!"double", !3, i64 0}
; IR-NEXT: !3 = !{!"omnipotent char", !4, i64 0}
; IR-NEXT: !4 = !{!"Simple C/C++ TBAA"}
; IR-NEXT: !5 = !{!6, !6, i64 0}
; IR-NEXT: !6 = !{!"any pointer", !3, i64 0}
; IR-NEXT: !7 = !{!3, !3, i64 0}
; IR-NEXT: !8 = distinct !{!8, !9, !"polly.alias.scope."}
; IR-NEXT: !9 = distinct !{!9, !"polly.alias.scope.domain"}
; IR-NEXT: !10 = !{!11, !12, !13, !14, !15, !16}
; IR-NEXT: !11 = distinct !{!11, !9, !"polly.alias.scope."}
; IR-NEXT: !12 = distinct !{!12, !9, !"polly.alias.scope.conv.i"}
; IR-NEXT: !13 = distinct !{!13, !9, !"polly.alias.scope.conv42.i"}
; IR-NEXT: !14 = distinct !{!14, !9, !"polly.alias.scope."}
; IR-NEXT: !15 = distinct !{!15, !9, !"polly.alias.scope.conv19.i"}
; IR-NEXT: !16 = distinct !{!16, !9, !"polly.alias.scope."}
; IR-NEXT: !17 = !{!8, !12, !13, !14, !15, !16}
; IR-NEXT: !18 = !{!11, !8, !12, !13, !14, !15}
; IR-NEXT: !19 = distinct !{!19, !20, !"polly.alias.scope."}
; IR-NEXT: !20 = distinct !{!20, !"polly.alias.scope.domain"}
; IR-NEXT: !21 = !{!22}
; IR-NEXT: !22 = distinct !{!22, !20, !"polly.alias.scope.call.i"}
; IR-NEXT: !23 = !{!19}
