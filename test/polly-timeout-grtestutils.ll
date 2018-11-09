; RUN: opt %loadPolly -polly-optree < %s

target datalayout = "e-m:e-i8:8:32-i16:16:32-i64:64-i128:128-n32:64-S128"
target triple = "aarch64--linux-android"

%class.GrStrokeInfo = type { %class.SkStrokeRec, i32, float, %class.SkAutoSTArray }
%class.SkStrokeRec = type { float, float, float, i32 }
%class.SkAutoSTArray = type { i32, float*, [8 x i8] }
%class.SkRandom = type { i32, i32 }

declare i32 @__gxx_personality_v0(...)

; Function Attrs: sspstrong uwtable
define void @_ZN6GrTest14TestStrokeInfoEP8SkRandom(%class.GrStrokeInfo* noalias sret %agg.result, %class.SkRandom* nocapture %random) local_unnamed_addr #0 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
call1.i.noexc:
  br label %call1.i.noexc.split

call1.i.noexc.split:                              ; preds = %call1.i.noexc
  %fK.i.i.i = getelementptr inbounds %class.SkRandom, %class.SkRandom* %random, i64 0, i32 0
  %0 = load i32, i32* %fK.i.i.i, align 4
  %and.i.i.i = and i32 %0, 65535
  %mul.i.i.i = mul nuw nsw i32 %and.i.i.i, 30345
  %shr.i.i.i = lshr i32 %0, 16
  %add.i.i.i = add nuw i32 %mul.i.i.i, %shr.i.i.i
  store i32 %add.i.i.i, i32* %fK.i.i.i, align 4
  %fJ.i.i.i = getelementptr inbounds %class.SkRandom, %class.SkRandom* %random, i64 0, i32 1
  %1 = load i32, i32* %fJ.i.i.i, align 4
  %and4.i.i.i = and i32 %1, 65535
  %mul5.i.i.i = mul nuw nsw i32 %and4.i.i.i, 18000
  %shr7.i.i.i = lshr i32 %1, 16
  %add8.i.i.i = add nuw i32 %mul5.i.i.i, %shr7.i.i.i
  store i32 %add8.i.i.i, i32* %fJ.i.i.i, align 4
  %shr12.i.i.i = lshr i32 %add.i.i.i, 16
  %add14.i.i.i = add i32 %add8.i.i.i, %shr12.i.i.i
  %rem.i.i = and i32 %add14.i.i.i, 1
  %2 = getelementptr inbounds %class.GrStrokeInfo, %class.GrStrokeInfo* %agg.result, i64 0, i32 0
  tail call void @_ZN11SkStrokeRecC2ENS_9InitStyleE(%class.SkStrokeRec* %2, i32 %rem.i.i)
  %fDashType.i = getelementptr inbounds %class.GrStrokeInfo, %class.GrStrokeInfo* %agg.result, i64 0, i32 1
  store i32 0, i32* %fDashType.i, align 8
  %fArray.i.i = getelementptr inbounds %class.GrStrokeInfo, %class.GrStrokeInfo* %agg.result, i64 0, i32 3, i32 1
  store float* null, float** %fArray.i.i, align 8
  %fCount.i.i = getelementptr inbounds %class.GrStrokeInfo, %class.GrStrokeInfo* %agg.result, i64 0, i32 3, i32 0
  store i32 0, i32* %fCount.i.i, align 8
  %3 = load i32, i32* %fK.i.i.i, align 4
  %and.i.i.i18 = and i32 %3, 65535
  %mul.i.i.i19 = mul nuw nsw i32 %and.i.i.i18, 30345
  %shr.i.i.i20 = lshr i32 %3, 16
  %add.i.i.i21 = add nuw i32 %mul.i.i.i19, %shr.i.i.i20
  %4 = load i32, i32* %fJ.i.i.i, align 4
  %and4.i.i.i23 = and i32 %4, 65535
  %mul5.i.i.i24 = mul nuw nsw i32 %and4.i.i.i23, 18000
  %shr7.i.i.i25 = lshr i32 %4, 16
  %add8.i.i.i26 = add nuw i32 %mul5.i.i.i24, %shr7.i.i.i25
  %shl.i.i.i27 = shl i32 %add.i.i.i21, 16
  %shr12.i.i.i28 = lshr i32 %add.i.i.i21, 16
  %or.i.i.i29 = or i32 %shl.i.i.i27, %shr12.i.i.i28
  %add14.i.i.i30 = add i32 %or.i.i.i29, %add8.i.i.i26
  %cmp.i.i = icmp slt i32 %add14.i.i.i30, 0
  %and.i.i = and i32 %add.i.i.i21, 65535
  %mul.i.i = mul nuw nsw i32 %and.i.i, 30345
  %add.i.i = add nuw i32 %mul.i.i, %shr12.i.i.i28
  store i32 %add.i.i, i32* %fK.i.i.i, align 4
  %and4.i.i = and i32 %add8.i.i.i26, 65535
  %mul5.i.i = mul nuw nsw i32 %and4.i.i, 18000
  %shr7.i.i = lshr i32 %add8.i.i.i26, 16
  %add8.i.i = add nuw i32 %mul5.i.i, %shr7.i.i
  store i32 %add8.i.i, i32* %fJ.i.i.i, align 4
  %shl.i.i = shl i32 %add.i.i, 16
  %shr12.i.i = lshr i32 %add.i.i, 16
  %or.i.i = or i32 %shl.i.i, %shr12.i.i
  %add14.i.i = add i32 %or.i.i, %add8.i.i
  %cmp.i = icmp slt i32 %add14.i.i, 0
  %cond.i = select i1 %cmp.i, float 0.000000e+00, float 1.000000e+00
  invoke void @_ZN11SkStrokeRec14setStrokeStyleEfb(%class.SkStrokeRec* %2, float %cond.i, i1 %cmp.i.i)
          to label %invoke.cont unwind label %lpad

invoke.cont:                                      ; preds = %call1.i.noexc.split
  %5 = load i32, i32* %fK.i.i.i, align 4
  %and.i.i.i51 = and i32 %5, 65535
  %mul.i.i.i52 = mul nuw nsw i32 %and.i.i.i51, 30345
  %shr.i.i.i53 = lshr i32 %5, 16
  %add.i.i.i54 = add nuw i32 %mul.i.i.i52, %shr.i.i.i53
  %6 = load i32, i32* %fJ.i.i.i, align 4
  %and4.i.i.i56 = and i32 %6, 65535
  %mul5.i.i.i57 = mul nuw nsw i32 %and4.i.i.i56, 18000
  %shr7.i.i.i58 = lshr i32 %6, 16
  %add8.i.i.i59 = add nuw i32 %mul5.i.i.i57, %shr7.i.i.i58
  %shl.i.i.i60 = shl i32 %add.i.i.i54, 16
  %shr12.i.i.i61 = lshr i32 %add.i.i.i54, 16
  %or.i.i.i62 = or i32 %shl.i.i.i60, %shr12.i.i.i61
  %add14.i.i.i63 = add i32 %or.i.i.i62, %add8.i.i.i59
  %rem.i.i64 = urem i32 %add14.i.i.i63, 3
  %and.i.i.i36 = and i32 %add.i.i.i54, 65535
  %mul.i.i.i37 = mul nuw nsw i32 %and.i.i.i36, 30345
  %add.i.i.i39 = add nuw i32 %mul.i.i.i37, %shr12.i.i.i61
  %and4.i.i.i41 = and i32 %add8.i.i.i59, 65535
  %mul5.i.i.i42 = mul nuw nsw i32 %and4.i.i.i41, 18000
  %shr7.i.i.i43 = lshr i32 %add8.i.i.i59, 16
  %add8.i.i.i44 = add nuw i32 %mul5.i.i.i42, %shr7.i.i.i43
  %shl.i.i.i45 = shl i32 %add.i.i.i39, 16
  %shr12.i.i.i46 = lshr i32 %add.i.i.i39, 16
  %or.i.i.i47 = or i32 %shl.i.i.i45, %shr12.i.i.i46
  %add14.i.i.i48 = add i32 %or.i.i.i47, %add8.i.i.i44
  %rem.i.i49 = urem i32 %add14.i.i.i48, 3
  %and.i.i.i.i = and i32 %add.i.i.i39, 65535
  %mul.i.i.i.i = mul nuw nsw i32 %and.i.i.i.i, 30345
  %add.i.i.i.i = add nuw i32 %mul.i.i.i.i, %shr12.i.i.i46
  %and4.i.i.i.i = and i32 %add8.i.i.i44, 65535
  %mul5.i.i.i.i = mul nuw nsw i32 %and4.i.i.i.i, 18000
  %shr7.i.i.i.i = lshr i32 %add8.i.i.i44, 16
  %add8.i.i.i.i = add nuw i32 %mul5.i.i.i.i, %shr7.i.i.i.i
  %shl.i.i.i.i = shl i32 %add.i.i.i.i, 16
  %shr12.i.i.i.i = lshr i32 %add.i.i.i.i, 16
  %or.i.i.i.i = or i32 %shl.i.i.i.i, %shr12.i.i.i.i
  %add14.i.i.i.i = add i32 %or.i.i.i.i, %add8.i.i.i.i
  %shr.i.i.i65 = lshr i32 %add14.i.i.i.i, 16
  %conv.i.i = sitofp i32 %shr.i.i.i65 to float
  %mul.i.i66 = fmul float %conv.i.i, 0x3EF0000000000000
  %mul.i = fmul float %mul.i.i66, 4.000000e+00
  %add.i = fadd float %mul.i, 1.000000e+00
  %fCap.i.i = getelementptr inbounds %class.GrStrokeInfo, %class.GrStrokeInfo* %agg.result, i64 0, i32 0, i32 3
  %bf.load.i.i = load i32, i32* %fCap.i.i, align 4
  %bf.value.i.i = and i32 %rem.i.i64, 3
  %bf.clear.i.i = and i32 %bf.load.i.i, -2147483648
  %bf.value3.i.i = shl nuw nsw i32 %rem.i.i49, 16
  %bf.set.i.i = or i32 %bf.clear.i.i, %bf.value.i.i
  %bf.set5.i.i = or i32 %bf.set.i.i, %bf.value3.i.i
  store i32 %bf.set5.i.i, i32* %fCap.i.i, align 4
  %fMiterLimit.i.i = getelementptr inbounds %class.GrStrokeInfo, %class.GrStrokeInfo* %agg.result, i64 0, i32 0, i32 2
  store float %add.i, float* %fMiterLimit.i.i, align 8
  %and.i.i68 = and i32 %add.i.i.i.i, 65535
  %mul.i.i69 = mul nuw nsw i32 %and.i.i68, 30345
  %add.i.i71 = add nuw i32 %mul.i.i69, %shr12.i.i.i.i
  store i32 %add.i.i71, i32* %fK.i.i.i, align 4
  %and4.i.i73 = and i32 %add8.i.i.i.i, 65535
  %mul5.i.i74 = mul nuw nsw i32 %and4.i.i73, 18000
  %shr7.i.i75 = lshr i32 %add8.i.i.i.i, 16
  %add8.i.i76 = add nuw i32 %mul5.i.i74, %shr7.i.i75
  store i32 %add8.i.i76, i32* %fJ.i.i.i, align 4
  %shl.i.i77 = shl i32 %add.i.i71, 16
  %shr12.i.i78 = lshr i32 %add.i.i71, 16
  %or.i.i79 = or i32 %shl.i.i77, %shr12.i.i78
  %add14.i.i80 = add i32 %or.i.i79, %add8.i.i76
  %rem.i = urem i32 %add14.i.i80, 50
  %add3.i = shl nuw nsw i32 %rem.i, 1
  %mul = add nuw nsw i32 %add3.i, 2
  %7 = shl nuw nsw i32 %mul, 2
  %8 = zext i32 %7 to i64
  %call7 = invoke i8* @_Znam(i64 %8) #5
          to label %invoke.cont6 unwind label %lpad1

invoke.cont6:                                     ; preds = %invoke.cont
  %9 = bitcast i8* %call7 to float*
  %10 = zext i32 %mul to i64
  br label %for.cond

for.cond:                                         ; preds = %invoke.cont10, %invoke.cont6
  %indvars.iv = phi i64 [ %indvars.iv.next, %invoke.cont10 ], [ 0, %invoke.cont6 ]
  %11 = phi i32 [ %add8.i.i.i.i119, %invoke.cont10 ], [ %add8.i.i76, %invoke.cont6 ]
  %12 = phi i32 [ %add.i.i.i.i114, %invoke.cont10 ], [ %add.i.i71, %invoke.cont6 ]
  %sum.0 = phi float [ %add, %invoke.cont10 ], [ 0.000000e+00, %invoke.cont6 ]
  %cmp = icmp slt i64 %indvars.iv, %10
  %and.i.i.i.i111 = and i32 %12, 65535
  %mul.i.i.i.i112 = mul nuw nsw i32 %and.i.i.i.i111, 30345
  %shr.i.i.i.i113 = lshr i32 %12, 16
  %add.i.i.i.i114 = add nuw i32 %mul.i.i.i.i112, %shr.i.i.i.i113
  %and4.i.i.i.i116 = and i32 %11, 65535
  %mul5.i.i.i.i117 = mul nuw nsw i32 %and4.i.i.i.i116, 18000
  %shr7.i.i.i.i118 = lshr i32 %11, 16
  %add8.i.i.i.i119 = add nuw i32 %mul5.i.i.i.i117, %shr7.i.i.i.i118
  %shl.i.i.i.i120 = shl i32 %add.i.i.i.i114, 16
  %shr12.i.i.i.i121 = lshr i32 %add.i.i.i.i114, 16
  %or.i.i.i.i122 = or i32 %shl.i.i.i.i120, %shr12.i.i.i.i121
  %add14.i.i.i.i123 = add i32 %or.i.i.i.i122, %add8.i.i.i.i119
  %shr.i.i.i124 = lshr i32 %add14.i.i.i.i123, 16
  %conv.i.i125 = sitofp i32 %shr.i.i.i124 to float
  %mul.i.i126 = fmul float %conv.i.i125, 0x3EF0000000000000
  br i1 %cmp, label %invoke.cont10, label %invoke.cont17

lpad:                                             ; preds = %call1.i.noexc.split
  %13 = landingpad { i8*, i32 }
          cleanup
  br label %ehcleanup23

lpad1:                                            ; preds = %invoke.cont
  %14 = landingpad { i8*, i32 }
          cleanup
  br label %ehcleanup23

invoke.cont10:                                    ; preds = %for.cond
  %mul.i127 = fmul float %mul.i.i126, 0x4023FAE140000000
  %add.i128 = fadd float %mul.i127, 0x3F847AE140000000
  %arrayidx = getelementptr inbounds float, float* %9, i64 %indvars.iv
  store float %add.i128, float* %arrayidx, align 4
  %add = fadd float %sum.0, %add.i128
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1
  br label %for.cond

invoke.cont17:                                    ; preds = %for.cond
  %sum.0.lcssa = phi float [ %sum.0, %for.cond ]
  %add.i.i.i.i114.lcssa = phi i32 [ %add.i.i.i.i114, %for.cond ]
  %add8.i.i.i.i119.lcssa = phi i32 [ %add8.i.i.i.i119, %for.cond ]
  %mul.i.i126.lcssa = phi float [ %mul.i.i126, %for.cond ]
  store i32 %add.i.i.i.i114.lcssa, i32* %fK.i.i.i, align 4
  store i32 %add8.i.i.i.i119.lcssa, i32* %fJ.i.i.i, align 4
  %mul.i108 = fmul float %sum.0.lcssa, %mul.i.i126.lcssa
  %add.i109 = fadd float %mul.i108, 0.000000e+00
  %call.i.i88 = invoke i32 @_ZNK11SkStrokeRec8getStyleEv(%class.SkStrokeRec* %2)
          to label %call.i.i.noexc unwind label %lpad16

call.i.i.noexc:                                   ; preds = %invoke.cont17
  %cmp.i.i81 = icmp eq i32 %call.i.i88, 1
  br i1 %cmp.i.i81, label %delete.end, label %if.then.i

if.then.i:                                        ; preds = %call.i.i.noexc
  store i32 1, i32* %fDashType.i, align 8
  %fDashPhase.i = getelementptr inbounds %class.GrStrokeInfo, %class.GrStrokeInfo* %agg.result, i64 0, i32 2
  store float %add.i109, float* %fDashPhase.i, align 4
  %15 = load float*, float** %fArray.i.i, align 8
  %16 = load i32, i32* %fCount.i.i, align 8
  %idx.ext.i.i = sext i32 %16 to i64
  %add.ptr.i.i = getelementptr inbounds float, float* %15, i64 %idx.ext.i.i
  br label %while.cond.i.i

while.cond.i.i:                                   ; preds = %while.cond.i.i, %if.then.i
  %iter.0.i.i = phi float* [ %add.ptr.i.i, %if.then.i ], [ %incdec.ptr.i.i, %while.cond.i.i ]
  %cmp.i7.i = icmp ugt float* %iter.0.i.i, %15
  %incdec.ptr.i.i = getelementptr inbounds float, float* %iter.0.i.i, i64 -1
  br i1 %cmp.i7.i, label %while.cond.i.i, label %while.end.i.i

while.end.i.i:                                    ; preds = %while.cond.i.i
  %17 = bitcast float* %15 to i8*
  %cmp3.i.i = icmp eq i32 %16, %mul
  br i1 %cmp3.i.i, label %for.body.lr.ph.i, label %if.then.i.i

if.then.i.i:                                      ; preds = %while.end.i.i
  %cmp5.i.i = icmp sgt i32 %16, 2
  br i1 %cmp5.i.i, label %if.then6.i.i, label %if.end.i.i

if.then6.i.i:                                     ; preds = %if.then.i.i
  invoke void @_Z7sk_freePv(i8* %17)
          to label %if.end.i.i unwind label %lpad16

if.end.i.i:                                       ; preds = %if.then6.i.i, %if.then.i.i
  %cmp8.i.i = icmp eq i32 %rem.i, 0
  br i1 %cmp8.i.i, label %if.else.i.i, label %if.then9.i.i

if.then9.i.i:                                     ; preds = %if.end.i.i
  %call13.i.i90 = invoke i8* @_Z15sk_malloc_throwm(i64 %8)
          to label %if.end21.i.i unwind label %lpad16

if.else.i.i:                                      ; preds = %if.end.i.i
  %arraydecay.i.i = getelementptr inbounds %class.GrStrokeInfo, %class.GrStrokeInfo* %agg.result, i64 0, i32 3, i32 2, i64 0
  br label %if.end21.i.i

if.end21.i.i:                                     ; preds = %if.then9.i.i, %if.else.i.i
  %storemerge.i.i.in = phi i8* [ %arraydecay.i.i, %if.else.i.i ], [ %call13.i.i90, %if.then9.i.i ]
  %storemerge.i.i = bitcast i8* %storemerge.i.i.in to float*
  %18 = bitcast float** %fArray.i.i to i8**
  store i8* %storemerge.i.i.in, i8** %18, align 8
  store i32 %mul, i32* %fCount.i.i, align 8
  br label %for.body.lr.ph.i

for.body.lr.ph.i:                                 ; preds = %while.end.i.i, %if.end21.i.i
  %19 = phi float* [ %15, %while.end.i.i ], [ %storemerge.i.i, %if.end21.i.i ]
  %20 = bitcast i8* %call7 to i32*
  %21 = load i32, i32* %20, align 4
  %22 = bitcast float* %19 to i32*
  store i32 %21, i32* %22, align 4
  %23 = load i32, i32* %fCount.i.i, align 8
  %cmp.i87140 = icmp sgt i32 %23, 1
  br i1 %cmp.i87140, label %for.body.for.body_crit_edge.i.lr.ph, label %delete.end

for.body.for.body_crit_edge.i.lr.ph:              ; preds = %for.body.lr.ph.i
  br label %for.body.for.body_crit_edge.i

for.body.for.body_crit_edge.i:                    ; preds = %for.body.for.body_crit_edge.i.lr.ph, %for.body.for.body_crit_edge.i
  %indvars.iv.next.i141 = phi i64 [ 1, %for.body.for.body_crit_edge.i.lr.ph ], [ %indvars.iv.next.i, %for.body.for.body_crit_edge.i ]
  %.pre.i = load float*, float** %fArray.i.i, align 8
  %arrayidx.i = getelementptr inbounds float, float* %9, i64 %indvars.iv.next.i141
  %24 = bitcast float* %arrayidx.i to i32*
  %25 = load i32, i32* %24, align 4
  %arrayidx.i.i = getelementptr inbounds float, float* %.pre.i, i64 %indvars.iv.next.i141
  %26 = bitcast float* %arrayidx.i.i to i32*
  store i32 %25, i32* %26, align 4
  %indvars.iv.next.i = add nuw nsw i64 %indvars.iv.next.i141, 1
  %27 = load i32, i32* %fCount.i.i, align 8
  %28 = sext i32 %27 to i64
  %cmp.i87 = icmp slt i64 %indvars.iv.next.i, %28
  br i1 %cmp.i87, label %for.body.for.body_crit_edge.i, label %delete.end.loopexit

delete.end.loopexit:                              ; preds = %for.body.for.body_crit_edge.i
  br label %delete.end

delete.end:                                       ; preds = %delete.end.loopexit, %for.body.lr.ph.i, %call.i.i.noexc
  tail call void @_ZdaPv(i8* nonnull %call7) #6
  ret void

lpad16:                                           ; preds = %if.then9.i.i, %if.then6.i.i, %invoke.cont17
  %29 = landingpad { i8*, i32 }
          cleanup
  br label %ehcleanup23

ehcleanup23:                                      ; preds = %lpad1, %lpad16, %lpad
  %.sink15.sink16.sink139 = phi { i8*, i32 } [ %13, %lpad ], [ %14, %lpad1 ], [ %29, %lpad16 ]
  %30 = load float*, float** %fArray.i.i, align 8
  %31 = load i32, i32* %fCount.i.i, align 8
  %idx.ext.i.i.i = sext i32 %31 to i64
  %add.ptr.i.i.i = getelementptr inbounds float, float* %30, i64 %idx.ext.i.i.i
  br label %while.cond.i.i.i

while.cond.i.i.i:                                 ; preds = %while.cond.i.i.i, %ehcleanup23
  %iter.0.i.i.i = phi float* [ %add.ptr.i.i.i, %ehcleanup23 ], [ %incdec.ptr.i.i.i, %while.cond.i.i.i ]
  %cmp.i.i.i = icmp ugt float* %iter.0.i.i.i, %30
  %incdec.ptr.i.i.i = getelementptr inbounds float, float* %iter.0.i.i.i, i64 -1
  br i1 %cmp.i.i.i, label %while.cond.i.i.i, label %while.end.i.i.i

while.end.i.i.i:                                  ; preds = %while.cond.i.i.i
  %32 = bitcast float* %30 to i8*
  %cmp3.i.i.i = icmp eq i32 %31, 0
  br i1 %cmp3.i.i.i, label %_ZN12GrStrokeInfoD2Ev.exit, label %if.then.i.i.i

if.then.i.i.i:                                    ; preds = %while.end.i.i.i
  %cmp5.i.i.i = icmp sgt i32 %31, 2
  br i1 %cmp5.i.i.i, label %if.then6.i.i.i, label %if.end.i.i.i

if.then6.i.i.i:                                   ; preds = %if.then.i.i.i
  invoke void @_Z7sk_freePv(i8* %32)
          to label %if.end.i.i.i unwind label %terminate.lpad.i.i

if.end.i.i.i:                                     ; preds = %if.then6.i.i.i, %if.then.i.i.i
  store float* null, float** %fArray.i.i, align 8
  store i32 0, i32* %fCount.i.i, align 8
  br label %_ZN12GrStrokeInfoD2Ev.exit

terminate.lpad.i.i:                               ; preds = %if.then6.i.i.i
  %33 = landingpad { i8*, i32 }
          catch i8* null
  %34 = extractvalue { i8*, i32 } %33, 0
  tail call void @__clang_call_terminate(i8* %34) #7
  unreachable

_ZN12GrStrokeInfoD2Ev.exit:                       ; preds = %while.end.i.i.i, %if.end.i.i.i
  resume { i8*, i32 } %.sink15.sink16.sink139
}

; Function Attrs: nobuiltin
declare noalias nonnull i8* @_Znam(i64) local_unnamed_addr #1

; Function Attrs: nobuiltin nounwind
declare void @_ZdaPv(i8*) local_unnamed_addr #2

declare void @_ZN11SkStrokeRec14setStrokeStyleEfb(%class.SkStrokeRec*, float, i1) local_unnamed_addr #3

declare void @_ZN11SkStrokeRecC2ENS_9InitStyleE(%class.SkStrokeRec*, i32) unnamed_addr #3

declare i32 @_ZNK11SkStrokeRec8getStyleEv(%class.SkStrokeRec*) local_unnamed_addr #3

declare void @_Z7sk_freePv(i8*) local_unnamed_addr #3

declare i8* @_Z15sk_malloc_throwm(i64) local_unnamed_addr #3

; Function Attrs: noinline noreturn nounwind
declare hidden void @__clang_call_terminate(i8*) local_unnamed_addr #4
