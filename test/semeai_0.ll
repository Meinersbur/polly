; RUN: opt %loadPolly -polly-enable-known -polly-enable-delicm -polly-enable-simplify -polly-enable-late-prune -polly-delicm-partial-writes -polly-delicm-compute-phi -polly-codegen-virtual-statements -polly-position=after-loopopt -domtree -loops -scalar-evolution -basicaa -aa -postdomtree -domfrontier -regions -polly-detect -polly-scops -polly-known -polly-delicm -polly-simplify -polly-unprofitable -polly-dependences -polly-opt-isl -polly-ast -polly-codegen -barrier -polly-cleanup -domtree -basicaa -aa -mldst-motion -aa -memdep -loops -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -gvn -basicaa -aa -memdep -memcpyopt -sccp -domtree -demanded-bits -bdce -basicaa -aa -instcombine -lazy-value-info -jump-threading -correlated-propagation -domtree -basicaa -aa -memdep -dse -loops -loop-simplify -lcssa-verification -lcssa -aa -scalar-evolution -licm -postdomtree -adce -simplifycfg -domtree -basicaa -aa -instcombine -barrier -elim-avail-extern -basiccg -rpo-functionattrs -globals-aa -float2int -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -loop-rotate -loop-accesses -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -loop-distribute -branch-prob -block-freq -scalar-evolution -basicaa -aa -loop-accesses -demanded-bits -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -loop-vectorize -loop-simplify -scalar-evolution -aa -loop-accesses -loop-load-elim -basicaa -aa -instcombine -scalar-evolution -demanded-bits -slp-vectorizer -simplifycfg -domtree -basicaa -aa -instcombine -loops -loop-simplify -lcssa-verification -lcssa -scalar-evolution -loop-unroll -instcombine -loop-simplify -lcssa-verification -lcssa -scalar-evolution -licm -alignment-from-assumptions -strip-dead-prototypes -globaldce -constmerge -domtree -loops -branch-prob -block-freq -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -branch-prob -block-freq -loop-sink -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -instsimplify -barrier -domtree -barrier -scoped-noalias -tbaa -assumption-cache-tracker -targetlibinfo -tti -domtree -basicaa -aa -simplifycfg -domtree -sroa -early-cse -basicaa -aa -instcombine -lazy-value-info -jump-threading -correlated-propagation -simplifycfg -domtree -basicaa -aa -instcombine -simplifycfg -reassociate -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -loop-rotate -licm -loop-unswitch -simplifycfg -domtree -basicaa -aa -instcombine -loops -loop-simplify -lcssa-verification -lcssa -scalar-evolution -indvars -loop-idiom -loop-deletion -simplifycfg -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -loop-unroll -mldst-motion -aa -memdep -memcpyopt -demanded-bits -bdce -aa -instcombine -lazy-value-info -jump-threading -correlated-propagation -domtree -basicaa -aa -memdep -dse -loops -loop-simplify -lcssa-verification -lcssa -aa -scalar-evolution -licm -loop-reroll -postdomtree -adce -simplifycfg -domtree -basicaa -aa -instcombine -barrier -tti -barrier -S < %s
; Derived from C:\Users\Meinersbur\src\llvm\tools\polly\test\semeai.c
; Original command: /root/build/llvm/release/bin/clang -DNDEBUG -I/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/sgf -I/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine -I/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/interface -I/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/patterns -I/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/utils -I/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src -I/root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/include -mllvm -polly -mllvm -polly-process-unprofitable -mllvm -polly-enable-known -mllvm -polly-enable-delicm -mllvm -polly-enable-simplify -mllvm -polly-enable-late-prune -mllvm -polly-delicm-partial-writes -mllvm -polly-delicm-compute-phi -mllvm -polly-codegen-virtual-statements -mllvm -polly-position=after-loopopt -O3 -fomit-frame-pointer -DNDEBUG -w -Werror=date-time -DSPEC_CPU -DSPEC_CPU_LINUX -DSPEC_CPU_X64 -DSPEC_CPU_LITTLEENDIAN -DSPEC_CPU_LP64 -o CMakeFiles/445.gobmk.dir/__/__/__/__/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/semeai.c.o -c /root/src/llvm/projects/test-suite/test-suite-externals/speccpu2006/benchspec/CPU2006/445.gobmk/src/engine/semeai.c

; ModuleID = 'C:\Users\Meinersbur\src\llvm\tools\polly\test\semeai.c'
source_filename = "C:\5CUsers\5CMeinersbur\5Csrc\5Cllvm\5Ctools\5Cpolly\5Ctest\5Csemeai.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.dragon_data = type { i32, i32, i32, i32, float, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32 }
%struct.dragon_data2 = type { i32, [10 x i32], i32, i32, i32, float, i32, float, float, i32, %struct.eyevalue, i32, i32, i32, i32, i32, i32 }
%struct.eyevalue = type { i8, i8, i8, i8 }
%struct.worm_data = type { i32, i32, float, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, [10 x i32], [10 x i32], [10 x i32], [10 x i32], [10 x i32], [10 x i32], [10 x i32], [10 x i32] }

@verbose = external local_unnamed_addr global i32, align 4
@.str = private unnamed_addr constant [35 x i8] c"Semeai Player is THINKING for %s!\0A\00", align 1
@number_of_dragons = external local_unnamed_addr global i32, align 4
@dragon = external local_unnamed_addr global [400 x %struct.dragon_data], align 16
@dragon2 = external local_unnamed_addr global %struct.dragon_data2*, align 8
@worm = external local_unnamed_addr global [400 x %struct.worm_data], align 16
@.str.1 = private unnamed_addr constant [48 x i8] c"Experimental Semeai Module is THINKING for %s!\0A\00", align 1
@debug = external local_unnamed_addr global i32, align 4
@.str.2 = private unnamed_addr constant [40 x i8] c"Considering semeai between %1m and %1m\0A\00", align 1
@.str.3 = private unnamed_addr constant [21 x i8] c"Result1: %s %s %1m, \00", align 1
@.str.4 = private unnamed_addr constant [16 x i8] c"Result2 %s %s.\0A\00", align 1
@.str.5 = private unnamed_addr constant [39 x i8] c"Changing status of %1m from %s to %s.\0A\00", align 1
@board = external local_unnamed_addr global [421 x i8], align 16
@.str.6 = private unnamed_addr constant [39 x i8] c"Changing safety of %1m from %s to %s.\0A\00", align 1
@.str.7 = private unnamed_addr constant [41 x i8] c"semeai_analyzer: %1m (me) vs %1m (them)\0A\00", align 1
@.str.8 = private unnamed_addr constant [45 x i8] c"added owl attack of %1m at %1m with code %d\0A\00", align 1
@.str.9 = private unnamed_addr constant [46 x i8] c"added owl defense of %1m at %1m with code %d\0A\00", align 1
@.str.10 = private unnamed_addr constant [50 x i8] c"changed owl_status and status of %1m to CRITICAL\0A\00", align 1
@.str.11 = private unnamed_addr constant [51 x i8] c"...owl code sufficient to resolve semeai, exiting\0A\00", align 1
@.str.12 = private unnamed_addr constant [41 x i8] c"...tactical situation detected, exiting\0A\00", align 1

; Function Attrs: nounwind uwtable
define void @semeai(i32 %color) local_unnamed_addr #0 {
entry:
  %adjs.i = alloca [160 x i32], align 16
  br label %entry.split

entry.split:                                      ; preds = %entry
  %sub = sub nsw i32 3, %color
  %0 = load i32, i32* @verbose, align 4, !tbaa !1
  %tobool = icmp eq i32 %0, 0
  br i1 %tobool, label %for.cond.preheader, label %cond.false

cond.false:                                       ; preds = %entry.split
  %call = tail call i8* @color_to_string(i32 %color) #3
  %call1 = tail call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str, i64 0, i64 0), i8* %call) #3
  br label %for.cond.preheader

for.cond.preheader:                               ; preds = %entry.split, %cond.false
  %1 = load i32, i32* @number_of_dragons, align 4, !tbaa !1
  %cmp122 = icmp sgt i32 %1, 0
  br i1 %cmp122, label %for.body.lr.ph, label %for.end91

for.body.lr.ph:                                   ; preds = %for.cond.preheader
  %2 = bitcast [160 x i32]* %adjs.i to i8*
  %arraydecay.i = getelementptr inbounds [160 x i32], [160 x i32]* %adjs.i, i64 0, i64 0
  br label %for.body

for.body:                                         ; preds = %for.body.lr.ph, %for.inc89
  %indvars.iv131 = phi i64 [ 0, %for.body.lr.ph ], [ %indvars.iv.next132, %for.inc89 ]
  %3 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %origin = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %3, i64 %indvars.iv131, i32 0
  %4 = load i32, i32* %origin, align 4, !tbaa !7
  %idxprom2 = sext i32 %4 to i64
  %color4 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom2, i32 0
  %5 = load i32, i32* %color4, align 4, !tbaa !11
  %cmp5 = icmp eq i32 %5, %color
  br i1 %cmp5, label %lor.lhs.false, label %for.inc89

lor.lhs.false:                                    ; preds = %for.body
  %status = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom2, i32 16
  %6 = load i32, i32* %status, align 4, !tbaa !13
  switch i32 %6, label %for.inc89 [
    i32 0, label %for.cond19.preheader
    i32 2, label %for.cond19.preheader
  ]

for.cond19.preheader:                             ; preds = %lor.lhs.false, %lor.lhs.false
  %7 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %neighbors119 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %7, i64 %indvars.iv131, i32 2
  %8 = load i32, i32* %neighbors119, align 4, !tbaa !14
  %cmp22120 = icmp sgt i32 %8, 0
  br i1 %cmp22120, label %for.body23.preheader, label %for.inc89

for.body23.preheader:                             ; preds = %for.cond19.preheader
  br label %for.body23

for.body23:                                       ; preds = %for.body23.preheader, %for.inc
  %indvars.iv = phi i64 [ 0, %for.body23.preheader ], [ %indvars.iv.next, %for.inc ]
  %9 = phi %struct.dragon_data2* [ %238, %for.inc ], [ %7, %for.body23.preheader ]
  %arrayidx27 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %9, i64 %indvars.iv131, i32 1, i64 %indvars.iv
  %10 = load i32, i32* %arrayidx27, align 4, !tbaa !1
  %idxprom28 = sext i32 %10 to i64
  %origin30 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %9, i64 %idxprom28, i32 0
  %11 = load i32, i32* %origin30, align 4, !tbaa !7
  %idxprom31 = sext i32 %11 to i64
  %color33 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom31, i32 0
  %12 = load i32, i32* %color33, align 4, !tbaa !11
  %cmp34 = icmp eq i32 %12, %sub
  br i1 %cmp34, label %lor.lhs.false35, label %for.inc

lor.lhs.false35:                                  ; preds = %for.body23
  %status41 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom31, i32 16
  %13 = load i32, i32* %status41, align 4, !tbaa !13
  switch i32 %13, label %for.inc [
    i32 0, label %if.end52
    i32 2, label %if.end52
  ]

if.end52:                                         ; preds = %lor.lhs.false35, %lor.lhs.false35
  %origin55 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %9, i64 %indvars.iv131, i32 0
  %14 = load i32, i32* %origin55, align 4, !tbaa !7
  %idxprom56 = sext i32 %14 to i64
  %origin58 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom56, i32 2
  %15 = load i32, i32* %origin58, align 4, !tbaa !15
  %origin64 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom31, i32 2
  %16 = load i32, i32* %origin64, align 4, !tbaa !15
  %idxprom65 = sext i32 %15 to i64
  %inessential = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom65, i32 12
  %17 = load i32, i32* %inessential, align 4, !tbaa !16
  %tobool67 = icmp eq i32 %17, 0
  br i1 %tobool67, label %lor.lhs.false68, label %for.inc

lor.lhs.false68:                                  ; preds = %if.end52
  %id = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom65, i32 1
  %18 = load i32, i32* %id, align 4, !tbaa !18
  %idxprom71 = sext i32 %18 to i64
  %safety = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %9, i64 %idxprom71, i32 6
  %19 = load i32, i32* %safety, align 4, !tbaa !19
  %cmp73 = icmp eq i32 %19, 5
  br i1 %cmp73, label %for.inc, label %lor.lhs.false74

lor.lhs.false74:                                  ; preds = %lor.lhs.false68
  %idxprom75 = sext i32 %16 to i64
  %inessential77 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom75, i32 12
  %20 = load i32, i32* %inessential77, align 4, !tbaa !16
  %tobool78 = icmp eq i32 %20, 0
  br i1 %tobool78, label %lor.lhs.false79, label %for.inc

lor.lhs.false79:                                  ; preds = %lor.lhs.false74
  %id82 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom75, i32 1
  %21 = load i32, i32* %id82, align 4, !tbaa !18
  %idxprom83 = sext i32 %21 to i64
  %safety85 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %9, i64 %idxprom83, i32 6
  %22 = load i32, i32* %safety85, align 4, !tbaa !19
  %cmp86 = icmp eq i32 %22, 5
  br i1 %cmp86, label %for.inc, label %if.end88

if.end88:                                         ; preds = %lor.lhs.false79
  %arrayidx.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom65
  %23 = load i8, i8* %arrayidx.i, align 1, !tbaa !20
  %conv.i = zext i8 %23 to i32
  %24 = load i32, i32* @debug, align 4, !tbaa !1
  %and.i = and i32 %24, 64
  %tobool.i = icmp eq i32 %and.i, 0
  br i1 %tobool.i, label %cond.end.i, label %cond.false.i

cond.false.i:                                     ; preds = %if.end88
  %call.i = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.7, i64 0, i64 0), i32 %15, i32 %16) #3
  br label %cond.end.i

cond.end.i:                                       ; preds = %cond.false.i, %if.end88
  %owl_status.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom65, i32 7
  %25 = load i32, i32* %owl_status.i, align 4, !tbaa !21
  %cmp.i = icmp eq i32 %25, 2
  br i1 %cmp.i, label %land.lhs.true.i, label %if.end43.i

land.lhs.true.i:                                  ; preds = %cond.end.i
  %owl_status6.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom75, i32 7
  %26 = load i32, i32* %owl_status6.i, align 4, !tbaa !21
  %cmp7.i = icmp eq i32 %26, 2
  br i1 %cmp7.i, label %if.then.i, label %if.end43thread-pre-split.i

if.then.i:                                        ; preds = %land.lhs.true.i
  %owl_attack_point.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom75, i32 8
  %27 = load i32, i32* %owl_attack_point.i, align 4, !tbaa !22
  %owl_defense_point.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom65, i32 12
  %28 = load i32, i32* %owl_defense_point.i, align 4, !tbaa !23
  %cmp13.i = icmp eq i32 %27, %28
  br i1 %cmp13.i, label %for.inc, label %if.end.i

if.end.i:                                         ; preds = %if.then.i
  %cmp19.i = icmp eq i32 %28, 0
  br i1 %cmp19.i, label %if.end43thread-pre-split.i, label %if.then21.i

if.then21.i:                                      ; preds = %if.end.i
  %call25.i = call i32 @owl_does_attack(i32 %28, i32 %16, i32* null) #3
  %cmp26.i = icmp eq i32 %call25.i, 0
  br i1 %cmp26.i, label %if.end43thread-pre-split.i, label %if.then28.i

if.then28.i:                                      ; preds = %if.then21.i
  %29 = load i32, i32* %owl_defense_point.i, align 4, !tbaa !23
  call void @add_owl_attack_move(i32 %29, i32 %16, i32 %call25.i) #3
  %30 = load i32, i32* @debug, align 4, !tbaa !1
  %and32.i = and i32 %30, 64
  %tobool33.i = icmp eq i32 %and32.i, 0
  br i1 %tobool33.i, label %if.end43thread-pre-split.i, label %cond.false35.i

cond.false35.i:                                   ; preds = %if.then28.i
  %31 = load i32, i32* %owl_defense_point.i, align 4, !tbaa !23
  %call39.i = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.8, i64 0, i64 0), i32 %16, i32 %31, i32 %call25.i) #3
  br label %if.end43thread-pre-split.i

if.end43thread-pre-split.i:                       ; preds = %cond.false35.i, %if.then28.i, %if.then21.i, %if.end.i, %land.lhs.true.i
  %owl_code_sufficient.1.ph.i = phi i32 [ 1, %cond.false35.i ], [ 1, %if.then28.i ], [ 0, %if.then21.i ], [ 0, %land.lhs.true.i ], [ 0, %if.end.i ]
  %.pr.i = load i32, i32* %owl_status.i, align 4, !tbaa !21
  br label %if.end43.i

if.end43.i:                                       ; preds = %if.end43thread-pre-split.i, %cond.end.i
  %32 = phi i32 [ %.pr.i, %if.end43thread-pre-split.i ], [ %25, %cond.end.i ]
  %owl_code_sufficient.1.i = phi i32 [ %owl_code_sufficient.1.ph.i, %if.end43thread-pre-split.i ], [ 0, %cond.end.i ]
  switch i32 %32, label %if.end139.i [
    i32 2, label %land.lhs.true54.i
    i32 0, label %land.lhs.true54.i
  ]

land.lhs.true54.i:                                ; preds = %if.end43.i, %if.end43.i
  %owl_status57.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom75, i32 7
  %33 = load i32, i32* %owl_status57.i, align 4, !tbaa !21
  %cmp58.i = icmp eq i32 %33, 2
  br i1 %cmp58.i, label %if.then60.i, label %if.end139.i

if.then60.i:                                      ; preds = %land.lhs.true54.i
  %owl_attack_point63.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom75, i32 8
  %34 = load i32, i32* %owl_attack_point63.i, align 4, !tbaa !22
  %owl_defense_point66.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom65, i32 12
  %35 = load i32, i32* %owl_defense_point66.i, align 4, !tbaa !23
  %cmp67.i = icmp eq i32 %34, %35
  br i1 %cmp67.i, label %for.inc, label %if.end70.i

if.end70.i:                                       ; preds = %if.then60.i
  %cmp74.i = icmp eq i32 %34, 0
  br i1 %cmp74.i, label %if.end139.i, label %if.then76.i

if.then76.i:                                      ; preds = %if.end70.i
  %call80.i = call i32 @owl_does_defend(i32 %34, i32 %15, i32* null) #3
  %cmp81.i = icmp eq i32 %call80.i, 0
  br i1 %cmp81.i, label %if.end139.i, label %if.then83.i

if.then83.i:                                      ; preds = %if.then76.i
  %36 = load i32, i32* %owl_attack_point63.i, align 4, !tbaa !22
  call void @add_owl_defense_move(i32 %36, i32 %15, i32 %call80.i) #3
  %37 = load i32, i32* @debug, align 4, !tbaa !1
  %and87.i = and i32 %37, 64
  %tobool88.i = icmp eq i32 %and87.i, 0
  br i1 %tobool88.i, label %cond.end95.i, label %cond.false90.i

cond.false90.i:                                   ; preds = %if.then83.i
  %38 = load i32, i32* %owl_attack_point63.i, align 4, !tbaa !22
  %call94.i = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([46 x i8], [46 x i8]* @.str.9, i64 0, i64 0), i32 %15, i32 %38, i32 %call80.i) #3
  br label %cond.end95.i

cond.end95.i:                                     ; preds = %cond.false90.i, %if.then83.i
  %39 = load i32, i32* %owl_status.i, align 4, !tbaa !21
  %cmp99.i = icmp eq i32 %39, 0
  br i1 %cmp99.i, label %for.body.i.preheader, label %if.then141.i

for.body.i.preheader:                             ; preds = %cond.end95.i
  br label %for.body.i

for.body.i:                                       ; preds = %for.body.i.preheader, %for.inc.i
  %indvars.iv1406.i = phi i64 [ %indvars.iv.next1407.i, %for.inc.i ], [ 21, %for.body.i.preheader ]
  %arrayidx106.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %indvars.iv1406.i
  %40 = load i8, i8* %arrayidx106.i, align 1, !tbaa !20
  %cmp108.i = icmp eq i8 %40, 3
  br i1 %cmp108.i, label %for.inc.i, label %if.end111.i

if.end111.i:                                      ; preds = %for.body.i
  %41 = load i8, i8* %arrayidx.i, align 1, !tbaa !20
  %cmp118.i = icmp eq i8 %40, %41
  br i1 %cmp118.i, label %land.lhs.true120.i, label %for.inc.i

land.lhs.true120.i:                               ; preds = %if.end111.i
  %42 = trunc i64 %indvars.iv1406.i to i32
  %call121.i = call i32 @is_same_dragon(i32 %42, i32 %15) #3
  %tobool122.i = icmp eq i32 %call121.i, 0
  br i1 %tobool122.i, label %for.inc.i, label %if.then123.i

if.then123.i:                                     ; preds = %land.lhs.true120.i
  %owl_status126.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %indvars.iv1406.i, i32 7
  store i32 2, i32* %owl_status126.i, align 4, !tbaa !21
  %status.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %indvars.iv1406.i, i32 16
  store i32 2, i32* %status.i, align 4, !tbaa !13
  br label %for.inc.i

for.inc.i:                                        ; preds = %if.then123.i, %land.lhs.true120.i, %if.end111.i, %for.body.i
  %indvars.iv.next1407.i = add nuw nsw i64 %indvars.iv1406.i, 1
  %exitcond1408.i = icmp eq i64 %indvars.iv.next1407.i, 400
  br i1 %exitcond1408.i, label %for.end.i, label %for.body.i

for.end.i:                                        ; preds = %for.inc.i
  %43 = load i32, i32* @debug, align 4, !tbaa !1
  %and130.i = and i32 %43, 64
  %tobool131.i = icmp eq i32 %and130.i, 0
  br i1 %tobool131.i, label %if.then141.i, label %cond.false133.i

cond.false133.i:                                  ; preds = %for.end.i
  %call134.i = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.10, i64 0, i64 0), i32 %15) #3
  br label %if.then141.i

if.end139.i:                                      ; preds = %if.then76.i, %if.end70.i, %land.lhs.true54.i, %if.end43.i
  %tobool140.i = icmp eq i32 %owl_code_sufficient.1.i, 0
  br i1 %tobool140.i, label %for.body152.i.preheader, label %if.then141.i

for.body152.i.preheader:                          ; preds = %if.end139.i
  br label %for.body152.i

if.then141.i:                                     ; preds = %if.end139.i, %cond.false133.i, %for.end.i, %cond.end95.i
  %44 = load i32, i32* @debug, align 4, !tbaa !1
  %and142.i = and i32 %44, 64
  %tobool143.i = icmp eq i32 %and142.i, 0
  br i1 %tobool143.i, label %for.inc, label %cond.false145.i

cond.false145.i:                                  ; preds = %if.then141.i
  %call146.i = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.11, i64 0, i64 0)) #3
  br label %for.inc

for.body152.i:                                    ; preds = %for.body152.i.preheader, %for.inc223.i
  %indvars.iv1404.i = phi i64 [ %indvars.iv.next1405.i, %for.inc223.i ], [ 21, %for.body152.i.preheader ]
  %arrayidx154.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %indvars.iv1404.i
  %45 = load i8, i8* %arrayidx154.i, align 1, !tbaa !20
  %cmp156.i = icmp eq i8 %45, 3
  br i1 %cmp156.i, label %for.inc223.i, label %if.end159.i

if.end159.i:                                      ; preds = %for.body152.i
  %origin.i = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %indvars.iv1404.i, i32 3
  %46 = load i32, i32* %origin.i, align 4, !tbaa !24
  %47 = zext i32 %46 to i64
  %cmp162.i = icmp eq i64 %indvars.iv1404.i, %47
  br i1 %cmp162.i, label %land.lhs.true164.i, label %for.inc223.i

land.lhs.true164.i:                               ; preds = %if.end159.i
  %arrayidx167.i = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %indvars.iv1404.i, i32 16, i64 0
  %48 = load i32, i32* %arrayidx167.i, align 4, !tbaa !1
  %cmp168.i = icmp eq i32 %48, 5
  br i1 %cmp168.i, label %if.then170.i, label %for.inc223.i

if.then170.i:                                     ; preds = %land.lhs.true164.i
  %origin173.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %indvars.iv1404.i, i32 2
  %49 = load i32, i32* %origin173.i, align 4, !tbaa !15
  %cmp174.i = icmp eq i32 %49, %15
  %cmp180.i = icmp eq i32 %49, %16
  %or.cond1054.i = or i1 %cmp174.i, %cmp180.i
  br i1 %or.cond1054.i, label %if.then182.i, label %for.inc223.i

if.then182.i:                                     ; preds = %if.then170.i
  call void @llvm.lifetime.start(i64 640, i8* nonnull %2) #3
  %50 = trunc i64 %indvars.iv1404.i to i32
  %call183.i = call i32 @chainlinks(i32 %50, i32* nonnull %arraydecay.i) #3
  %cmp1851355.i = icmp sgt i32 %call183.i, 0
  br i1 %cmp1851355.i, label %for.body187.preheader.i, label %cleanup216.i

for.body187.preheader.i:                          ; preds = %if.then182.i
  %51 = sext i32 %call183.i to i64
  br label %for.body187.i

for.body187.i:                                    ; preds = %for.inc213.i, %for.body187.preheader.i
  %indvars.iv1402.i = phi i64 [ 0, %for.body187.preheader.i ], [ %indvars.iv.next1403.i, %for.inc213.i ]
  %arrayidx189.i = getelementptr inbounds [160 x i32], [160 x i32]* %adjs.i, i64 0, i64 %indvars.iv1402.i
  %52 = load i32, i32* %arrayidx189.i, align 4, !tbaa !1
  %idxprom190.i = sext i32 %52 to i64
  %origin192.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom190.i, i32 2
  %53 = load i32, i32* %origin192.i, align 4, !tbaa !15
  %cmp193.i = icmp eq i32 %53, %15
  %cmp199.i = icmp eq i32 %53, %16
  %or.cond1055.i = or i1 %cmp193.i, %cmp199.i
  br i1 %or.cond1055.i, label %if.then201.i, label %for.inc213.i

if.then201.i:                                     ; preds = %for.body187.i
  %call202.i = call i32 @owl_substantial(i32 %50) #3
  %tobool203.i = icmp eq i32 %call202.i, 0
  br i1 %tobool203.i, label %for.inc213.i, label %if.then204.i

if.then204.i:                                     ; preds = %if.then201.i
  %54 = load i32, i32* @debug, align 4, !tbaa !1
  %and205.i = and i32 %54, 64
  %tobool206.i = icmp eq i32 %and205.i, 0
  br i1 %tobool206.i, label %cleanup216.thread.i, label %cond.false208.i

cond.false208.i:                                  ; preds = %if.then204.i
  %call209.i = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.12, i64 0, i64 0)) #3
  br label %cleanup216.thread.i

for.inc213.i:                                     ; preds = %if.then201.i, %for.body187.i
  %indvars.iv.next1403.i = add nuw nsw i64 %indvars.iv1402.i, 1
  %cmp185.i = icmp slt i64 %indvars.iv.next1403.i, %51
  br i1 %cmp185.i, label %for.body187.i, label %cleanup216.i.loopexit

cleanup216.thread.i:                              ; preds = %cond.false208.i, %if.then204.i
  call void @llvm.lifetime.end(i64 640, i8* nonnull %2) #3
  br label %for.inc

cleanup216.i.loopexit:                            ; preds = %for.inc213.i
  br label %cleanup216.i

cleanup216.i:                                     ; preds = %cleanup216.i.loopexit, %if.then182.i
  call void @llvm.lifetime.end(i64 640, i8* nonnull %2) #3
  br label %for.inc223.i

for.inc223.i:                                     ; preds = %cleanup216.i, %if.then170.i, %land.lhs.true164.i, %if.end159.i, %for.body152.i
  %indvars.iv.next1405.i = add nuw nsw i64 %indvars.iv1404.i, 1
  %cmp150.i = icmp slt i64 %indvars.iv1404.i, 399
  br i1 %cmp150.i, label %for.body152.i, label %for.body229.i.preheader

for.body229.i.preheader:                          ; preds = %for.inc223.i
  br label %for.body229.i

for.body229.i:                                    ; preds = %for.body229.i.preheader, %for.inc247.i
  %indvars.iv1399.i = phi i64 [ %indvars.iv.next1400.i, %for.inc247.i ], [ 21, %for.body229.i.preheader ]
  %arrayidx231.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %indvars.iv1399.i
  %55 = load i8, i8* %arrayidx231.i, align 1, !tbaa !20
  %cmp233.i = icmp eq i8 %55, 3
  br i1 %cmp233.i, label %for.inc247.i, label %land.lhs.true235.i

land.lhs.true235.i:                               ; preds = %for.body229.i
  %56 = trunc i64 %indvars.iv1399.i to i32
  %call236.i = call i32 @is_same_dragon(i32 %56, i32 %15) #3
  %tobool237.i = icmp eq i32 %call236.i, 0
  br i1 %tobool237.i, label %lor.lhs.false238.i, label %if.then241.i

lor.lhs.false238.i:                               ; preds = %land.lhs.true235.i
  %call239.i = call i32 @is_same_dragon(i32 %56, i32 %16) #3
  %tobool240.i = icmp eq i32 %call239.i, 0
  br i1 %tobool240.i, label %for.inc247.i, label %if.then241.i

if.then241.i:                                     ; preds = %lor.lhs.false238.i, %land.lhs.true235.i
  %57 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %id.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %indvars.iv1399.i, i32 1
  %58 = load i32, i32* %id.i, align 4, !tbaa !18
  %idxprom244.i = sext i32 %58 to i64
  %semeai.i = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %57, i64 %idxprom244.i, i32 13
  store i32 1, i32* %semeai.i, align 4, !tbaa !25
  br label %for.inc247.i

for.inc247.i:                                     ; preds = %if.then241.i, %lor.lhs.false238.i, %for.body229.i
  %indvars.iv.next1400.i = add nuw nsw i64 %indvars.iv1399.i, 1
  %exitcond1401.i = icmp eq i64 %indvars.iv.next1400.i, 400
  br i1 %exitcond1401.i, label %for.body253.i.preheader, label %for.body229.i

for.body253.i.preheader:                          ; preds = %for.inc247.i
  br label %for.body253.i

for.body253.i:                                    ; preds = %for.body253.i.preheader, %for.inc314.i
  %indvars.iv1384.i = phi i64 [ %indvars.iv.next1385.i, %for.inc314.i ], [ 21, %for.body253.i.preheader ]
  %mylibs.01351.i = phi i32 [ %mylibs.2.i, %for.inc314.i ], [ 1, %for.body253.i.preheader ]
  %yourlibs.01349.i = phi i32 [ %yourlibs.1.i, %for.inc314.i ], [ 1, %for.body253.i.preheader ]
  %commonlibs.01346.i = phi i32 [ %commonlibs.1.i, %for.inc314.i ], [ 0, %for.body253.i.preheader ]
  %arrayidx255.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %indvars.iv1384.i
  %59 = load i8, i8* %arrayidx255.i, align 1, !tbaa !20
  switch i8 %59, label %for.inc314.i [
    i8 0, label %if.end4.i.i
    i8 1, label %land.lhs.true272.i
    i8 2, label %land.lhs.true272.i
  ]

land.lhs.true272.i:                               ; preds = %for.body253.i, %for.body253.i
  %origin275.i = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %indvars.iv1384.i, i32 3
  %60 = load i32, i32* %origin275.i, align 4, !tbaa !24
  %61 = zext i32 %60 to i64
  %cmp276.i = icmp eq i64 %indvars.iv1384.i, %61
  br i1 %cmp276.i, label %if.then278.i, label %for.inc314.i

if.then278.i:                                     ; preds = %land.lhs.true272.i
  %62 = trunc i64 %indvars.iv1384.i to i32
  %call279.i = call i32 @is_same_dragon(i32 %62, i32 %15) #3
  %not.tobool280.i = icmp ne i32 %call279.i, 0
  %dec.i = sext i1 %not.tobool280.i to i32
  %mylibs.0.dec.i = add nsw i32 %mylibs.01351.i, %dec.i
  %call283.i = call i32 @is_same_dragon(i32 %62, i32 %16) #3
  %not.tobool284.i = icmp ne i32 %call283.i, 0
  %dec286.i = sext i1 %not.tobool284.i to i32
  %yourlibs.0.dec286.i = add nsw i32 %yourlibs.01349.i, %dec286.i
  br label %for.inc314.i

if.end4.i.i:                                      ; preds = %for.body253.i
  %63 = add nuw nsw i64 %indvars.iv1384.i, 20
  %arrayidx6.i.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %63
  %64 = load i8, i8* %arrayidx6.i.i, align 1, !tbaa !20
  %cmp8.i.i = icmp eq i8 %64, 3
  br i1 %cmp8.i.i, label %lor.lhs.false.i.i, label %land.lhs.true.i.i

land.lhs.true.i.i:                                ; preds = %if.end4.i.i
  %origin13.i.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %63, i32 2
  %65 = load i32, i32* %origin13.i.i, align 4, !tbaa !15
  %cmp14.i.i = icmp eq i32 %65, %16
  br i1 %cmp14.i.i, label %if.then296.i, label %lor.lhs.false.i.i

lor.lhs.false.i.i:                                ; preds = %land.lhs.true.i.i, %if.end4.i.i
  %66 = add nsw i64 %indvars.iv1384.i, -1
  %arrayidx17.i.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %66
  %67 = load i8, i8* %arrayidx17.i.i, align 1, !tbaa !20
  %cmp19.i.i = icmp eq i8 %67, 3
  br i1 %cmp19.i.i, label %lor.lhs.false28.i.i, label %land.lhs.true21.i.i

land.lhs.true21.i.i:                              ; preds = %lor.lhs.false.i.i
  %origin25.i.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %66, i32 2
  %68 = load i32, i32* %origin25.i.i, align 4, !tbaa !15
  %cmp26.i.i = icmp eq i32 %68, %16
  br i1 %cmp26.i.i, label %if.then296.i, label %lor.lhs.false28.i.i

lor.lhs.false28.i.i:                              ; preds = %land.lhs.true21.i.i, %lor.lhs.false.i.i
  %69 = add nsw i64 %indvars.iv1384.i, -20
  %arrayidx31.i.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %69
  %70 = load i8, i8* %arrayidx31.i.i, align 1, !tbaa !20
  %cmp33.i.i = icmp eq i8 %70, 3
  br i1 %cmp33.i.i, label %lor.lhs.false42.i.i, label %land.lhs.true35.i.i

land.lhs.true35.i.i:                              ; preds = %lor.lhs.false28.i.i
  %origin39.i.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %69, i32 2
  %71 = load i32, i32* %origin39.i.i, align 4, !tbaa !15
  %cmp40.i.i = icmp eq i32 %71, %16
  br i1 %cmp40.i.i, label %if.then296.i, label %lor.lhs.false42.i.i

lor.lhs.false42.i.i:                              ; preds = %land.lhs.true35.i.i, %lor.lhs.false28.i.i
  %72 = add nuw nsw i64 %indvars.iv1384.i, 1
  %arrayidx45.i.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %72
  %73 = load i8, i8* %arrayidx45.i.i, align 1, !tbaa !20
  %cmp47.i.i = icmp eq i8 %73, 3
  br i1 %cmp47.i.i, label %if.else305.i, label %land.lhs.true49.i.i

land.lhs.true49.i.i:                              ; preds = %lor.lhs.false42.i.i
  %origin53.i.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %72, i32 2
  %74 = load i32, i32* %origin53.i.i, align 4, !tbaa !15
  %cmp54.i.i = icmp eq i32 %74, %16
  br i1 %cmp54.i.i, label %if.then296.i, label %if.else305.i

if.then296.i:                                     ; preds = %land.lhs.true49.i.i, %land.lhs.true35.i.i, %land.lhs.true21.i.i, %land.lhs.true.i.i
  %inc297.i = add nsw i32 %yourlibs.01349.i, 1
  %75 = load i8, i8* %arrayidx255.i, align 1, !tbaa !20
  %cmp1.i1069.i = icmp eq i8 %75, 0
  br i1 %cmp1.i1069.i, label %if.end4.i1074.i, label %for.inc314.i

if.end4.i1074.i:                                  ; preds = %if.then296.i
  %76 = load i8, i8* %arrayidx6.i.i, align 1, !tbaa !20
  %cmp8.i1073.i = icmp eq i8 %76, 3
  br i1 %cmp8.i1073.i, label %lor.lhs.false.i1082.i, label %land.lhs.true.i1077.i

land.lhs.true.i1077.i:                            ; preds = %if.end4.i1074.i
  %origin13.i1075.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %63, i32 2
  %77 = load i32, i32* %origin13.i1075.i, align 4, !tbaa !15
  %cmp14.i1076.i = icmp eq i32 %77, %15
  br i1 %cmp14.i1076.i, label %if.then300.i, label %lor.lhs.false.i1082.i

lor.lhs.false.i1082.i:                            ; preds = %land.lhs.true.i1077.i, %if.end4.i1074.i
  %78 = add nsw i64 %indvars.iv1384.i, -1
  %arrayidx17.i1080.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %78
  %79 = load i8, i8* %arrayidx17.i1080.i, align 1, !tbaa !20
  %cmp19.i1081.i = icmp eq i8 %79, 3
  br i1 %cmp19.i1081.i, label %lor.lhs.false28.i1090.i, label %land.lhs.true21.i1085.i

land.lhs.true21.i1085.i:                          ; preds = %lor.lhs.false.i1082.i
  %origin25.i1083.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %78, i32 2
  %80 = load i32, i32* %origin25.i1083.i, align 4, !tbaa !15
  %cmp26.i1084.i = icmp eq i32 %80, %15
  br i1 %cmp26.i1084.i, label %if.then300.i, label %lor.lhs.false28.i1090.i

lor.lhs.false28.i1090.i:                          ; preds = %land.lhs.true21.i1085.i, %lor.lhs.false.i1082.i
  %81 = add nsw i64 %indvars.iv1384.i, -20
  %arrayidx31.i1088.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %81
  %82 = load i8, i8* %arrayidx31.i1088.i, align 1, !tbaa !20
  %cmp33.i1089.i = icmp eq i8 %82, 3
  br i1 %cmp33.i1089.i, label %lor.lhs.false42.i1098.i, label %land.lhs.true35.i1093.i

land.lhs.true35.i1093.i:                          ; preds = %lor.lhs.false28.i1090.i
  %origin39.i1091.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %81, i32 2
  %83 = load i32, i32* %origin39.i1091.i, align 4, !tbaa !15
  %cmp40.i1092.i = icmp eq i32 %83, %15
  br i1 %cmp40.i1092.i, label %if.then300.i, label %lor.lhs.false42.i1098.i

lor.lhs.false42.i1098.i:                          ; preds = %land.lhs.true35.i1093.i, %lor.lhs.false28.i1090.i
  %84 = add nuw nsw i64 %indvars.iv1384.i, 1
  %arrayidx45.i1096.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %84
  %85 = load i8, i8* %arrayidx45.i1096.i, align 1, !tbaa !20
  %cmp47.i1097.i = icmp eq i8 %85, 3
  br i1 %cmp47.i1097.i, label %for.inc314.i, label %land.lhs.true49.i1101.i

land.lhs.true49.i1101.i:                          ; preds = %lor.lhs.false42.i1098.i
  %origin53.i1099.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %84, i32 2
  %86 = load i32, i32* %origin53.i1099.i, align 4, !tbaa !15
  %cmp54.i1100.i = icmp eq i32 %86, %15
  br i1 %cmp54.i1100.i, label %if.then300.i, label %for.inc314.i

if.then300.i:                                     ; preds = %land.lhs.true49.i1101.i, %land.lhs.true35.i1093.i, %land.lhs.true21.i1085.i, %land.lhs.true.i1077.i
  %inc301.i = add nsw i32 %commonlibs.01346.i, 1
  %inc302.i = add nsw i32 %mylibs.01351.i, 1
  br label %for.inc314.i

if.else305.i:                                     ; preds = %land.lhs.true49.i.i, %lor.lhs.false42.i.i
  %.pr1322.i = load i8, i8* %arrayidx255.i, align 1, !tbaa !20
  %cmp1.i1107.i = icmp eq i8 %.pr1322.i, 0
  br i1 %cmp1.i1107.i, label %if.end4.i1112.i, label %liberty_of_dragon.exit1142.i

if.end4.i1112.i:                                  ; preds = %if.else305.i
  %87 = load i8, i8* %arrayidx6.i.i, align 1, !tbaa !20
  %cmp8.i1111.i = icmp eq i8 %87, 3
  br i1 %cmp8.i1111.i, label %lor.lhs.false.i1120.i, label %land.lhs.true.i1115.i

land.lhs.true.i1115.i:                            ; preds = %if.end4.i1112.i
  %origin13.i1113.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %63, i32 2
  %88 = load i32, i32* %origin13.i1113.i, align 4, !tbaa !15
  %cmp14.i1114.i = icmp eq i32 %88, %15
  br i1 %cmp14.i1114.i, label %liberty_of_dragon.exit1142.i, label %lor.lhs.false.i1120.i

lor.lhs.false.i1120.i:                            ; preds = %land.lhs.true.i1115.i, %if.end4.i1112.i
  %89 = load i8, i8* %arrayidx17.i.i, align 1, !tbaa !20
  %cmp19.i1119.i = icmp eq i8 %89, 3
  br i1 %cmp19.i1119.i, label %lor.lhs.false28.i1128.i, label %land.lhs.true21.i1123.i

land.lhs.true21.i1123.i:                          ; preds = %lor.lhs.false.i1120.i
  %origin25.i1121.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %66, i32 2
  %90 = load i32, i32* %origin25.i1121.i, align 4, !tbaa !15
  %cmp26.i1122.i = icmp eq i32 %90, %15
  br i1 %cmp26.i1122.i, label %liberty_of_dragon.exit1142.i, label %lor.lhs.false28.i1128.i

lor.lhs.false28.i1128.i:                          ; preds = %land.lhs.true21.i1123.i, %lor.lhs.false.i1120.i
  %91 = load i8, i8* %arrayidx31.i.i, align 1, !tbaa !20
  %cmp33.i1127.i = icmp eq i8 %91, 3
  br i1 %cmp33.i1127.i, label %lor.lhs.false42.i1136.i, label %land.lhs.true35.i1131.i

land.lhs.true35.i1131.i:                          ; preds = %lor.lhs.false28.i1128.i
  %origin39.i1129.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %69, i32 2
  %92 = load i32, i32* %origin39.i1129.i, align 4, !tbaa !15
  %cmp40.i1130.i = icmp eq i32 %92, %15
  br i1 %cmp40.i1130.i, label %liberty_of_dragon.exit1142.i, label %lor.lhs.false42.i1136.i

lor.lhs.false42.i1136.i:                          ; preds = %land.lhs.true35.i1131.i, %lor.lhs.false28.i1128.i
  %93 = load i8, i8* %arrayidx45.i.i, align 1, !tbaa !20
  %cmp47.i1135.i = icmp eq i8 %93, 3
  br i1 %cmp47.i1135.i, label %if.end57.i1140.i, label %land.lhs.true49.i1139.i

land.lhs.true49.i1139.i:                          ; preds = %lor.lhs.false42.i1136.i
  %origin53.i1137.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %72, i32 2
  %94 = load i32, i32* %origin53.i1137.i, align 4, !tbaa !15
  %cmp54.i1138.i = icmp eq i32 %94, %15
  br i1 %cmp54.i1138.i, label %liberty_of_dragon.exit1142.i, label %if.end57.i1140.i

if.end57.i1140.i:                                 ; preds = %land.lhs.true49.i1139.i, %lor.lhs.false42.i1136.i
  br label %liberty_of_dragon.exit1142.i

liberty_of_dragon.exit1142.i:                     ; preds = %if.end57.i1140.i, %land.lhs.true49.i1139.i, %land.lhs.true35.i1131.i, %land.lhs.true21.i1123.i, %land.lhs.true.i1115.i, %if.else305.i
  %retval.0.i1141.i = phi i32 [ 0, %if.end57.i1140.i ], [ 0, %if.else305.i ], [ 1, %land.lhs.true49.i1139.i ], [ 1, %land.lhs.true35.i1131.i ], [ 1, %land.lhs.true21.i1123.i ], [ 1, %land.lhs.true.i1115.i ]
  %mylibs.0.inc309.i = add nsw i32 %retval.0.i1141.i, %mylibs.01351.i
  br label %for.inc314.i

for.inc314.i:                                     ; preds = %liberty_of_dragon.exit1142.i, %if.then300.i, %land.lhs.true49.i1101.i, %lor.lhs.false42.i1098.i, %if.then296.i, %if.then278.i, %land.lhs.true272.i, %for.body253.i
  %commonlibs.1.i = phi i32 [ %inc301.i, %if.then300.i ], [ %commonlibs.01346.i, %for.body253.i ], [ %commonlibs.01346.i, %liberty_of_dragon.exit1142.i ], [ %commonlibs.01346.i, %if.then278.i ], [ %commonlibs.01346.i, %land.lhs.true272.i ], [ %commonlibs.01346.i, %if.then296.i ], [ %commonlibs.01346.i, %land.lhs.true49.i1101.i ], [ %commonlibs.01346.i, %lor.lhs.false42.i1098.i ]
  %yourlibs.1.i = phi i32 [ %inc297.i, %if.then300.i ], [ %yourlibs.01349.i, %for.body253.i ], [ %yourlibs.01349.i, %liberty_of_dragon.exit1142.i ], [ %yourlibs.0.dec286.i, %if.then278.i ], [ %yourlibs.01349.i, %land.lhs.true272.i ], [ %inc297.i, %if.then296.i ], [ %inc297.i, %land.lhs.true49.i1101.i ], [ %inc297.i, %lor.lhs.false42.i1098.i ]
  %mylibs.2.i = phi i32 [ %inc302.i, %if.then300.i ], [ %mylibs.01351.i, %for.body253.i ], [ %mylibs.0.inc309.i, %liberty_of_dragon.exit1142.i ], [ %mylibs.0.dec.i, %if.then278.i ], [ %mylibs.01351.i, %land.lhs.true272.i ], [ %mylibs.01351.i, %if.then296.i ], [ %mylibs.01351.i, %land.lhs.true49.i1101.i ], [ %mylibs.01351.i, %lor.lhs.false42.i1098.i ]
  %indvars.iv.next1385.i = add nuw nsw i64 %indvars.iv1384.i, 1
  %exitcond1398.i = icmp eq i64 %indvars.iv.next1385.i, 400
  br i1 %exitcond1398.i, label %for.end316.i, label %for.body253.i

for.end316.i:                                     ; preds = %for.inc314.i
  %commonlibs.1.i.lcssa = phi i32 [ %commonlibs.1.i, %for.inc314.i ]
  %yourlibs.1.i.lcssa = phi i32 [ %yourlibs.1.i, %for.inc314.i ]
  %mylibs.2.i.lcssa = phi i32 [ %mylibs.2.i, %for.inc314.i ]
  %95 = load i32, i32* %owl_status.i, align 4, !tbaa !21
  %cmp320.i = icmp eq i32 %95, 2
  br i1 %cmp320.i, label %land.lhs.true322.i, label %if.end336.i

land.lhs.true322.i:                               ; preds = %for.end316.i
  %owl_attack_point325.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom65, i32 8
  %96 = load i32, i32* %owl_attack_point325.i, align 4, !tbaa !22
  %cmp326.i = icmp eq i32 %96, 0
  br i1 %cmp326.i, label %if.end336.i, label %land.lhs.true328.i

land.lhs.true328.i:                               ; preds = %land.lhs.true322.i
  %call332.i = call i32 @liberty_of_string(i32 %96, i32 %15) #3
  %tobool333.i = icmp eq i32 %call332.i, 0
  %inc335.i = zext i1 %tobool333.i to i32
  %inc335.mylibs.0.i = add nsw i32 %mylibs.2.i.lcssa, %inc335.i
  br label %if.end336.i

if.end336.i:                                      ; preds = %land.lhs.true328.i, %land.lhs.true322.i, %for.end316.i
  %mylibs.3.i = phi i32 [ %mylibs.2.i.lcssa, %land.lhs.true322.i ], [ %mylibs.2.i.lcssa, %for.end316.i ], [ %inc335.mylibs.0.i, %land.lhs.true328.i ]
  %owl_status339.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom75, i32 7
  %97 = load i32, i32* %owl_status339.i, align 4, !tbaa !21
  %cmp340.i = icmp eq i32 %97, 2
  br i1 %cmp340.i, label %land.lhs.true342.i, label %if.end356.i

land.lhs.true342.i:                               ; preds = %if.end336.i
  %owl_attack_point345.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom75, i32 8
  %98 = load i32, i32* %owl_attack_point345.i, align 4, !tbaa !22
  %cmp346.i = icmp eq i32 %98, 0
  br i1 %cmp346.i, label %if.end356.i, label %land.lhs.true348.i

land.lhs.true348.i:                               ; preds = %land.lhs.true342.i
  %call352.i = call i32 @liberty_of_string(i32 %98, i32 %16) #3
  %tobool353.i = icmp eq i32 %call352.i, 0
  %inc355.i = zext i1 %tobool353.i to i32
  %inc355.yourlibs.0.i = add nsw i32 %yourlibs.1.i.lcssa, %inc355.i
  br label %if.end356.i

if.end356.i:                                      ; preds = %land.lhs.true348.i, %land.lhs.true342.i, %if.end336.i
  %yourlibs.2.i = phi i32 [ %yourlibs.1.i.lcssa, %land.lhs.true342.i ], [ %yourlibs.1.i.lcssa, %if.end336.i ], [ %inc355.yourlibs.0.i, %land.lhs.true348.i ]
  %99 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %100 = load i32, i32* %id, align 4, !tbaa !18
  %idxprom360.i = sext i32 %100 to i64
  %genus.i = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %99, i64 %idxprom360.i, i32 10
  %call362.i = call i32 @min_eyes(%struct.eyevalue* %genus.i) #3
  %cmp363.i = icmp eq i32 %call362.i, 0
  br i1 %cmp363.i, label %land.lhs.true365.i, label %if.end440.i

land.lhs.true365.i:                               ; preds = %if.end356.i
  %101 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %102 = load i32, i32* %id82, align 4, !tbaa !18
  %idxprom369.i = sext i32 %102 to i64
  %genus371.i = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %101, i64 %idxprom369.i, i32 10
  %call372.i = call i32 @min_eyes(%struct.eyevalue* %genus371.i) #3
  %cmp373.i = icmp eq i32 %call372.i, 0
  br i1 %cmp373.i, label %if.then375.i, label %if.end440.i

if.then375.i:                                     ; preds = %land.lhs.true365.i
  %cmp376.i = icmp eq i32 %commonlibs.1.i.lcssa, 0
  br i1 %cmp376.i, label %if.then378.i, label %if.else390.i

if.then378.i:                                     ; preds = %if.then375.i
  %cmp379.i = icmp slt i32 %yourlibs.2.i, %mylibs.3.i
  br i1 %cmp379.i, label %if.then381.i, label %if.else382.i

if.then381.i:                                     ; preds = %if.then378.i
  %sub.i = sub nsw i32 %mylibs.3.i, %yourlibs.2.i
  br label %if.end440.i

if.else382.i:                                     ; preds = %if.then378.i
  %cmp383.i = icmp sgt i32 %yourlibs.2.i, %mylibs.3.i
  %sub386.i = sub nsw i32 %yourlibs.2.i, %mylibs.3.i
  %.1064.i = select i1 %cmp383.i, i32 0, i32 2
  %.1065.i = select i1 %cmp383.i, i32 1, i32 2
  %sub386..i = select i1 %cmp383.i, i32 %sub386.i, i32 0
  br label %if.end440.i

if.else390.i:                                     ; preds = %if.then375.i
  %add.i = add i32 %commonlibs.1.i.lcssa, -1
  %sub391.i = add i32 %yourlibs.2.i, %add.i
  %cmp392.i = icmp eq i32 %mylibs.3.i, %sub391.i
  br i1 %cmp392.i, label %if.then394.i, label %if.else400.i

if.then394.i:                                     ; preds = %if.else390.i
  %cmp395.i = icmp eq i32 %mylibs.3.i, 0
  %..i = select i1 %cmp395.i, i32 2, i32 1
  br label %if.end440.i

if.else400.i:                                     ; preds = %if.else390.i
  %cmp403.i = icmp slt i32 %mylibs.3.i, %sub391.i
  %sub407.i = add i32 %mylibs.3.i, %add.i
  %cmp408.i = icmp slt i32 %yourlibs.2.i, %sub407.i
  %or.cond = and i1 %cmp408.i, %cmp403.i
  br i1 %or.cond, label %if.end440.i, label %if.else411.i

if.else411.i:                                     ; preds = %if.else400.i
  %cmp412.i = icmp sgt i32 %commonlibs.1.i.lcssa, 0
  br i1 %cmp412.i, label %land.lhs.true414.i, label %if.end440.i

land.lhs.true414.i:                               ; preds = %if.else411.i
  %add415.i = add i32 %mylibs.3.i, %commonlibs.1.i.lcssa
  %sub416.i = add nsw i32 %add415.i, -1
  %cmp417.i = icmp eq i32 %yourlibs.2.i, %sub416.i
  br i1 %cmp417.i, label %if.then419.i, label %if.else425.i

if.then419.i:                                     ; preds = %land.lhs.true414.i
  %cmp420.i = icmp eq i32 %yourlibs.2.i, 0
  %.1056.i = select i1 %cmp420.i, i32 2, i32 1
  br label %if.end440.i

if.else425.i:                                     ; preds = %land.lhs.true414.i
  %cmp430.i = icmp sgt i32 %yourlibs.2.i, %add415.i
  %sub434.i = sub i32 %yourlibs.2.i, %add415.i
  %. = select i1 %cmp430.i, i32 0, i32 3
  %.116 = select i1 %cmp430.i, i32 1, i32 3
  %sub434.i. = select i1 %cmp430.i, i32 %sub434.i, i32 0
  br label %if.end440.i

if.end440.i:                                      ; preds = %if.else425.i, %if.else400.i, %if.then419.i, %if.else411.i, %if.then394.i, %if.else382.i, %if.then381.i, %land.lhs.true365.i, %if.end356.i
  %my_status.0.i = phi i32 [ 1, %if.then381.i ], [ 3, %land.lhs.true365.i ], [ 3, %if.end356.i ], [ %..i, %if.then394.i ], [ 2, %if.then419.i ], [ 3, %if.else411.i ], [ %.1064.i, %if.else382.i ], [ 1, %if.else400.i ], [ %., %if.else425.i ]
  %your_status.0.i = phi i32 [ 0, %if.then381.i ], [ 3, %land.lhs.true365.i ], [ 3, %if.end356.i ], [ 2, %if.then394.i ], [ %.1056.i, %if.then419.i ], [ 3, %if.else411.i ], [ %.1065.i, %if.else382.i ], [ 1, %if.else400.i ], [ %.116, %if.else425.i ]
  %margin_of_safety.0.i = phi i32 [ %sub.i, %if.then381.i ], [ 0, %land.lhs.true365.i ], [ 0, %if.end356.i ], [ 0, %if.then394.i ], [ 0, %if.then419.i ], [ 0, %if.else411.i ], [ %sub386..i, %if.else382.i ], [ 1000, %if.else400.i ], [ %sub434.i., %if.else425.i ]
  %103 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %104 = load i32, i32* %id, align 4, !tbaa !18
  %idxprom444.i = sext i32 %104 to i64
  %genus446.i = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %103, i64 %idxprom444.i, i32 10
  %call447.i = call i32 @min_eyes(%struct.eyevalue* %genus446.i) #3
  %cmp448.i = icmp sgt i32 %call447.i, 0
  br i1 %cmp448.i, label %land.lhs.true450.i, label %if.end515.i

land.lhs.true450.i:                               ; preds = %if.end440.i
  %105 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %106 = load i32, i32* %id82, align 4, !tbaa !18
  %idxprom454.i = sext i32 %106 to i64
  %genus456.i = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %105, i64 %idxprom454.i, i32 10
  %call457.i = call i32 @min_eyes(%struct.eyevalue* %genus456.i) #3
  %cmp458.i = icmp sgt i32 %call457.i, 0
  br i1 %cmp458.i, label %if.then460.i, label %if.end515.i

if.then460.i:                                     ; preds = %land.lhs.true450.i
  %add461.i = add nsw i32 %yourlibs.2.i, %commonlibs.1.i.lcssa
  %cmp462.i = icmp sgt i32 %mylibs.3.i, %add461.i
  br i1 %cmp462.i, label %if.then464.i, label %if.else467.i

if.then464.i:                                     ; preds = %if.then460.i
  %sub465.i = sub i32 %mylibs.3.i, %commonlibs.1.i.lcssa
  %sub466.i = sub i32 %sub465.i, %yourlibs.2.i
  br label %if.end515.i

if.else467.i:                                     ; preds = %if.then460.i
  %add468.i = add i32 %mylibs.3.i, %commonlibs.1.i.lcssa
  %cmp469.i = icmp sgt i32 %yourlibs.2.i, %add468.i
  br i1 %cmp469.i, label %if.then471.i, label %if.else474.i

if.then471.i:                                     ; preds = %if.else467.i
  %sub473.i = sub i32 %yourlibs.2.i, %add468.i
  br label %if.end515.i

if.else474.i:                                     ; preds = %if.else467.i
  %cmp475.i = icmp eq i32 %commonlibs.1.i.lcssa, 0
  %cmp478.i = icmp eq i32 %yourlibs.2.i, %mylibs.3.i
  %or.cond1058.i = and i1 %cmp475.i, %cmp478.i
  br i1 %or.cond1058.i, label %if.end515.i, label %if.else481.i

if.else481.i:                                     ; preds = %if.else474.i
  %cmp482.i = icmp sgt i32 %commonlibs.1.i.lcssa, 0
  %cmp486.i = icmp eq i32 %mylibs.3.i, %add461.i
  %or.cond1059.i = and i1 %cmp482.i, %cmp486.i
  br i1 %or.cond1059.i, label %if.end515.i, label %if.else489.i

if.else489.i:                                     ; preds = %if.else481.i
  %cmp494.i = icmp slt i32 %mylibs.3.i, %add461.i
  %or.cond1060.i = and i1 %cmp482.i, %cmp494.i
  %cmp498.i = icmp slt i32 %yourlibs.2.i, %add468.i
  %or.cond1061.i = and i1 %cmp498.i, %or.cond1060.i
  %cmp482.not.i = xor i1 %cmp482.i, true
  %brmerge.i = or i1 %or.cond1061.i, %cmp482.not.i
  %.mux.i = select i1 %or.cond1061.i, i32 1, i32 %my_status.0.i
  %.mux1062.i = select i1 %or.cond1061.i, i32 1, i32 %your_status.0.i
  %.mux1063.i = select i1 %or.cond1061.i, i32 1000, i32 %margin_of_safety.0.i
  br i1 %brmerge.i, label %if.end515.i, label %land.lhs.true504.i

land.lhs.true504.i:                               ; preds = %if.else489.i
  %cmp506.i = icmp eq i32 %yourlibs.2.i, %add468.i
  %.my_status.0.i = select i1 %cmp506.i, i32 2, i32 %my_status.0.i
  %.your_status.0.i = select i1 %cmp506.i, i32 1, i32 %your_status.0.i
  %.margin_of_safety.0.i = select i1 %cmp506.i, i32 0, i32 %margin_of_safety.0.i
  br label %if.end515.i

if.end515.i:                                      ; preds = %land.lhs.true504.i, %if.else489.i, %if.else481.i, %if.else474.i, %if.then471.i, %if.then464.i, %land.lhs.true450.i, %if.end440.i
  %my_status.1.i = phi i32 [ 1, %if.then464.i ], [ 0, %if.then471.i ], [ %my_status.0.i, %land.lhs.true450.i ], [ %my_status.0.i, %if.end440.i ], [ 2, %if.else474.i ], [ 1, %if.else481.i ], [ %.mux.i, %if.else489.i ], [ %.my_status.0.i, %land.lhs.true504.i ]
  %your_status.1.i = phi i32 [ 0, %if.then464.i ], [ 1, %if.then471.i ], [ %your_status.0.i, %land.lhs.true450.i ], [ %your_status.0.i, %if.end440.i ], [ 2, %if.else474.i ], [ 2, %if.else481.i ], [ %.mux1062.i, %if.else489.i ], [ %.your_status.0.i, %land.lhs.true504.i ]
  %margin_of_safety.1.i = phi i32 [ %sub466.i, %if.then464.i ], [ %sub473.i, %if.then471.i ], [ %margin_of_safety.0.i, %land.lhs.true450.i ], [ %margin_of_safety.0.i, %if.end440.i ], [ 0, %if.else474.i ], [ 0, %if.else481.i ], [ %.mux1063.i, %if.else489.i ], [ %.margin_of_safety.0.i, %land.lhs.true504.i ]
  %107 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %108 = load i32, i32* %id, align 4, !tbaa !18
  %idxprom519.i = sext i32 %108 to i64
  %genus521.i = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %107, i64 %idxprom519.i, i32 10
  %call522.i = call i32 @min_eyes(%struct.eyevalue* %genus521.i) #3
  %cmp523.i = icmp sgt i32 %call522.i, 0
  br i1 %cmp523.i, label %land.lhs.true525.i, label %if.end557.i

land.lhs.true525.i:                               ; preds = %if.end515.i
  %109 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %110 = load i32, i32* %id82, align 4, !tbaa !18
  %idxprom529.i = sext i32 %110 to i64
  %genus531.i = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %109, i64 %idxprom529.i, i32 10
  %call532.i = call i32 @min_eyes(%struct.eyevalue* %genus531.i) #3
  %cmp533.i = icmp eq i32 %call532.i, 0
  br i1 %cmp533.i, label %if.then535.i, label %if.end557.i

if.then535.i:                                     ; preds = %land.lhs.true525.i
  %add536.i = add nsw i32 %yourlibs.2.i, %commonlibs.1.i.lcssa
  %cmp537.i = icmp sgt i32 %mylibs.3.i, %add536.i
  br i1 %cmp537.i, label %if.then539.i, label %if.else542.i

if.then539.i:                                     ; preds = %if.then535.i
  %sub540.i = sub i32 %mylibs.3.i, %commonlibs.1.i.lcssa
  %sub541.i = sub i32 %sub540.i, %yourlibs.2.i
  br label %if.end557.i

if.else542.i:                                     ; preds = %if.then535.i
  %add543.i = add nsw i32 %mylibs.3.i, %commonlibs.1.i.lcssa
  %cmp544.i = icmp eq i32 %add543.i, %yourlibs.2.i
  br i1 %cmp544.i, label %if.end557.i, label %if.else547.i

if.else547.i:                                     ; preds = %if.else542.i
  %cmp549.i = icmp slt i32 %add543.i, %yourlibs.2.i
  %sub553.i = sub nsw i32 %add543.i, %yourlibs.2.i
  %.my_status.1.i = select i1 %cmp549.i, i32 0, i32 %my_status.1.i
  %.your_status.1.i = select i1 %cmp549.i, i32 1, i32 %your_status.1.i
  %sub553.margin_of_safety.1.i = select i1 %cmp549.i, i32 %sub553.i, i32 %margin_of_safety.1.i
  br label %if.end557.i

if.end557.i:                                      ; preds = %if.else547.i, %if.else542.i, %if.then539.i, %land.lhs.true525.i, %if.end515.i
  %my_status.2.i = phi i32 [ 1, %if.then539.i ], [ %my_status.1.i, %land.lhs.true525.i ], [ %my_status.1.i, %if.end515.i ], [ 2, %if.else542.i ], [ %.my_status.1.i, %if.else547.i ]
  %your_status.2.i = phi i32 [ 0, %if.then539.i ], [ %your_status.1.i, %land.lhs.true525.i ], [ %your_status.1.i, %if.end515.i ], [ 2, %if.else542.i ], [ %.your_status.1.i, %if.else547.i ]
  %margin_of_safety.2.i = phi i32 [ %sub541.i, %if.then539.i ], [ %margin_of_safety.1.i, %land.lhs.true525.i ], [ %margin_of_safety.1.i, %if.end515.i ], [ %margin_of_safety.1.i, %if.else542.i ], [ %sub553.margin_of_safety.1.i, %if.else547.i ]
  %111 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %112 = load i32, i32* %id, align 4, !tbaa !18
  %idxprom561.i = sext i32 %112 to i64
  %genus563.i = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %111, i64 %idxprom561.i, i32 10
  %call564.i = call i32 @min_eyes(%struct.eyevalue* %genus563.i) #3
  %cmp565.i = icmp eq i32 %call564.i, 0
  br i1 %cmp565.i, label %land.lhs.true567.i, label %if.end599.i

land.lhs.true567.i:                               ; preds = %if.end557.i
  %113 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %114 = load i32, i32* %id82, align 4, !tbaa !18
  %idxprom571.i = sext i32 %114 to i64
  %genus573.i = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %113, i64 %idxprom571.i, i32 10
  %call574.i = call i32 @min_eyes(%struct.eyevalue* %genus573.i) #3
  %cmp575.i = icmp sgt i32 %call574.i, 0
  br i1 %cmp575.i, label %if.then577.i, label %if.end599.i

if.then577.i:                                     ; preds = %land.lhs.true567.i
  %add578.i = add nsw i32 %yourlibs.2.i, %commonlibs.1.i.lcssa
  %cmp579.i = icmp sgt i32 %add578.i, %mylibs.3.i
  br i1 %cmp579.i, label %if.then581.i, label %if.else584.i

if.then581.i:                                     ; preds = %if.then577.i
  %sub583.i = sub nsw i32 %add578.i, %mylibs.3.i
  br label %if.end599.i

if.else584.i:                                     ; preds = %if.then577.i
  %cmp586.i = icmp eq i32 %add578.i, %mylibs.3.i
  %.my_status.2.i = select i1 %cmp586.i, i32 2, i32 %my_status.2.i
  %.your_status.2.i = select i1 %cmp586.i, i32 2, i32 %your_status.2.i
  %.margin_of_safety.2.i = select i1 %cmp586.i, i32 0, i32 %margin_of_safety.2.i
  br label %if.end599.i

if.end599.i:                                      ; preds = %if.else584.i, %if.then581.i, %land.lhs.true567.i, %if.end557.i
  %my_status.3.i = phi i32 [ 0, %if.then581.i ], [ %my_status.2.i, %land.lhs.true567.i ], [ %my_status.2.i, %if.end557.i ], [ %.my_status.2.i, %if.else584.i ]
  %your_status.3.i = phi i32 [ 1, %if.then581.i ], [ %your_status.2.i, %land.lhs.true567.i ], [ %your_status.2.i, %if.end557.i ], [ %.your_status.2.i, %if.else584.i ]
  %margin_of_safety.3.i = phi i32 [ %sub583.i, %if.then581.i ], [ %margin_of_safety.2.i, %land.lhs.true567.i ], [ %margin_of_safety.2.i, %if.end557.i ], [ %.margin_of_safety.2.i, %if.else584.i ]
  %115 = load i32, i32* %owl_status.i, align 4, !tbaa !21
  %cmp603.i = icmp eq i32 %115, 2
  br i1 %cmp603.i, label %if.end620.i, label %if.then605.i

if.then605.i:                                     ; preds = %if.end599.i
  switch i32 %my_status.3.i, label %if.end620.i [
    i32 1, label %if.then608.i
    i32 2, label %if.then612.i
    i32 0, label %if.then616.i
  ]

if.then608.i:                                     ; preds = %if.then605.i
  call fastcc void @update_status(i32 %15, i32 1, i32 7) #3
  br label %if.end620.i

if.then612.i:                                     ; preds = %if.then605.i
  call fastcc void @update_status(i32 %15, i32 2, i32 2) #3
  br label %if.end620.i

if.then616.i:                                     ; preds = %if.then605.i
  call fastcc void @update_status(i32 %15, i32 0, i32 0) #3
  br label %if.end620.i

if.end620.i:                                      ; preds = %if.then616.i, %if.then612.i, %if.then608.i, %if.then605.i, %if.end599.i
  switch i32 %your_status.3.i, label %if.end634.i [
    i32 1, label %if.then623.i
    i32 2, label %if.end634.thread.i
    i32 0, label %if.then631.i
  ]

if.then623.i:                                     ; preds = %if.end620.i
  call fastcc void @update_status(i32 %16, i32 1, i32 7) #3
  br label %if.end634.i

if.end634.thread.i:                               ; preds = %if.end620.i
  call fastcc void @update_status(i32 %16, i32 2, i32 2) #3
  %cmp6351324.i = icmp eq i32 %my_status.3.i, 2
  br label %if.then640.i

if.then631.i:                                     ; preds = %if.end620.i
  call fastcc void @update_status(i32 %16, i32 0, i32 0) #3
  br label %if.end634.i

if.end634.i:                                      ; preds = %if.then631.i, %if.then623.i, %if.end620.i
  %cmp635.i = icmp eq i32 %my_status.3.i, 2
  br i1 %cmp635.i, label %if.then640.i, label %for.inc

if.then640.i:                                     ; preds = %if.end634.i, %if.end634.thread.i
  %cmp6381328.i = phi i1 [ true, %if.end634.thread.i ], [ false, %if.end634.i ]
  %cmp6351327.i = phi i1 [ %cmp6351324.i, %if.end634.thread.i ], [ true, %if.end634.i ]
  %116 = load i32, i32* %owl_status.i, align 4, !tbaa !21
  %cmp644.i = icmp eq i32 %116, 2
  br i1 %cmp644.i, label %land.lhs.true646.i, label %if.else656.i

land.lhs.true646.i:                               ; preds = %if.then640.i
  %owl_defense_point649.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom65, i32 12
  %117 = load i32, i32* %owl_defense_point649.i, align 4, !tbaa !23
  %cmp650.i = icmp eq i32 %117, 0
  br i1 %cmp650.i, label %if.else656.i, label %if.then652.i

if.then652.i:                                     ; preds = %land.lhs.true646.i
  br i1 %cmp6351327.i, label %if.then.i1144.i, label %if.else.i1146.i

if.then.i1144.i:                                  ; preds = %if.then652.i
  call void @add_semeai_move(i32 %117, i32 %15) #3
  br label %if.end3.i1149.i

if.else.i1146.i:                                  ; preds = %if.then652.i
  %cmp1.i1145.i = icmp eq i32 %margin_of_safety.3.i, 1
  br i1 %cmp1.i1145.i, label %if.then2.i1147.i, label %if.end3.i1149.i

if.then2.i1147.i:                                 ; preds = %if.else.i1146.i
  call void @add_semeai_threat(i32 %117, i32 %15) #3
  br label %if.end3.i1149.i

if.end3.i1149.i:                                  ; preds = %if.then2.i1147.i, %if.else.i1146.i, %if.then.i1144.i
  br i1 %cmp6381328.i, label %if.then5.i1150.i, label %if.else6.i1152.i

if.then5.i1150.i:                                 ; preds = %if.end3.i1149.i
  call void @add_semeai_move(i32 %117, i32 %16) #3
  br label %for.inc

if.else6.i1152.i:                                 ; preds = %if.end3.i1149.i
  %cmp7.i1151.i = icmp eq i32 %margin_of_safety.3.i, 1
  br i1 %cmp7.i1151.i, label %if.then8.i1153.i, label %for.inc

if.then8.i1153.i:                                 ; preds = %if.else6.i1152.i
  call void @add_semeai_threat(i32 %117, i32 %16) #3
  br label %for.inc

if.else656.i:                                     ; preds = %land.lhs.true646.i, %if.then640.i
  %118 = load i32, i32* %owl_status339.i, align 4, !tbaa !21
  %cmp660.i = icmp eq i32 %118, 2
  br i1 %cmp660.i, label %land.lhs.true662.i, label %if.else672.i

land.lhs.true662.i:                               ; preds = %if.else656.i
  %owl_attack_point665.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom75, i32 8
  %119 = load i32, i32* %owl_attack_point665.i, align 4, !tbaa !22
  %cmp666.i = icmp eq i32 %119, 0
  br i1 %cmp666.i, label %if.else672.i, label %if.then668.i

if.then668.i:                                     ; preds = %land.lhs.true662.i
  br i1 %cmp6351327.i, label %if.then.i1156.i, label %if.else.i1158.i

if.then.i1156.i:                                  ; preds = %if.then668.i
  call void @add_semeai_move(i32 %119, i32 %15) #3
  br label %if.end3.i1161.i

if.else.i1158.i:                                  ; preds = %if.then668.i
  %cmp1.i1157.i = icmp eq i32 %margin_of_safety.3.i, 1
  br i1 %cmp1.i1157.i, label %if.then2.i1159.i, label %if.end3.i1161.i

if.then2.i1159.i:                                 ; preds = %if.else.i1158.i
  call void @add_semeai_threat(i32 %119, i32 %15) #3
  br label %if.end3.i1161.i

if.end3.i1161.i:                                  ; preds = %if.then2.i1159.i, %if.else.i1158.i, %if.then.i1156.i
  br i1 %cmp6381328.i, label %if.then5.i1162.i, label %if.else6.i1164.i

if.then5.i1162.i:                                 ; preds = %if.end3.i1161.i
  call void @add_semeai_move(i32 %119, i32 %16) #3
  br label %for.inc

if.else6.i1164.i:                                 ; preds = %if.end3.i1161.i
  %cmp7.i1163.i = icmp eq i32 %margin_of_safety.3.i, 1
  br i1 %cmp7.i1163.i, label %if.then8.i1165.i, label %for.inc

if.then8.i1165.i:                                 ; preds = %if.else6.i1164.i
  call void @add_semeai_threat(i32 %119, i32 %16) #3
  br label %for.inc

if.else672.i:                                     ; preds = %land.lhs.true662.i, %if.else656.i
  %cmp673.i = icmp sgt i32 %commonlibs.1.i.lcssa, 1
  br i1 %cmp673.i, label %if.then675.i, label %for.cond709.preheader.i

for.cond709.preheader.i:                          ; preds = %if.else672.i
  %cmp7.i1275.i = icmp eq i32 %margin_of_safety.3.i, 1
  br i1 %cmp6351327.i, label %for.body712.i.us.preheader, label %for.body712.i.preheader

for.body712.i.preheader:                          ; preds = %for.cond709.preheader.i
  br label %for.body712.i

for.body712.i.us.preheader:                       ; preds = %for.cond709.preheader.i
  br label %for.body712.i.us

for.body712.i.us:                                 ; preds = %for.body712.i.us.preheader, %for.inc730.i.us
  %indvars.iv1373.i.us = phi i64 [ %indvars.iv.next1374.i.us, %for.inc730.i.us ], [ 21, %for.body712.i.us.preheader ]
  %found_one.01339.i.us = phi i32 [ %found_one.1.i.us, %for.inc730.i.us ], [ 0, %for.body712.i.us.preheader ]
  %arrayidx714.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %indvars.iv1373.i.us
  %120 = load i8, i8* %arrayidx714.i.us, align 1, !tbaa !20
  %cond.i.us = icmp eq i8 %120, 0
  br i1 %cond.i.us, label %if.end4.i1198.i.us, label %for.inc730.i.us

if.end4.i1198.i.us:                               ; preds = %for.body712.i.us
  %121 = add nuw nsw i64 %indvars.iv1373.i.us, 20
  %arrayidx6.i1196.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %121
  %122 = load i8, i8* %arrayidx6.i1196.i.us, align 1, !tbaa !20
  %cmp8.i1197.i.us = icmp eq i8 %122, 3
  br i1 %cmp8.i1197.i.us, label %lor.lhs.false.i1206.i.us, label %land.lhs.true.i1201.i.us

land.lhs.true.i1201.i.us:                         ; preds = %if.end4.i1198.i.us
  %origin13.i1199.i.us = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %121, i32 2
  %123 = load i32, i32* %origin13.i1199.i.us, align 4, !tbaa !15
  %cmp14.i1200.i.us = icmp eq i32 %123, %16
  br i1 %cmp14.i1200.i.us, label %land.lhs.true722.i.us, label %lor.lhs.false.i1206.i.us

lor.lhs.false.i1206.i.us:                         ; preds = %land.lhs.true.i1201.i.us, %if.end4.i1198.i.us
  %124 = add nsw i64 %indvars.iv1373.i.us, -1
  %arrayidx17.i1204.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %124
  %125 = load i8, i8* %arrayidx17.i1204.i.us, align 1, !tbaa !20
  %cmp19.i1205.i.us = icmp eq i8 %125, 3
  br i1 %cmp19.i1205.i.us, label %lor.lhs.false28.i1214.i.us, label %land.lhs.true21.i1209.i.us

land.lhs.true21.i1209.i.us:                       ; preds = %lor.lhs.false.i1206.i.us
  %origin25.i1207.i.us = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %124, i32 2
  %126 = load i32, i32* %origin25.i1207.i.us, align 4, !tbaa !15
  %cmp26.i1208.i.us = icmp eq i32 %126, %16
  br i1 %cmp26.i1208.i.us, label %land.lhs.true722.i.us, label %lor.lhs.false28.i1214.i.us

lor.lhs.false28.i1214.i.us:                       ; preds = %land.lhs.true21.i1209.i.us, %lor.lhs.false.i1206.i.us
  %127 = add nsw i64 %indvars.iv1373.i.us, -20
  %arrayidx31.i1212.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %127
  %128 = load i8, i8* %arrayidx31.i1212.i.us, align 1, !tbaa !20
  %cmp33.i1213.i.us = icmp eq i8 %128, 3
  br i1 %cmp33.i1213.i.us, label %lor.lhs.false42.i1222.i.us, label %land.lhs.true35.i1217.i.us

land.lhs.true35.i1217.i.us:                       ; preds = %lor.lhs.false28.i1214.i.us
  %origin39.i1215.i.us = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %127, i32 2
  %129 = load i32, i32* %origin39.i1215.i.us, align 4, !tbaa !15
  %cmp40.i1216.i.us = icmp eq i32 %129, %16
  br i1 %cmp40.i1216.i.us, label %land.lhs.true722.i.us, label %lor.lhs.false42.i1222.i.us

lor.lhs.false42.i1222.i.us:                       ; preds = %land.lhs.true35.i1217.i.us, %lor.lhs.false28.i1214.i.us
  %130 = add nuw nsw i64 %indvars.iv1373.i.us, 1
  %arrayidx45.i1220.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %130
  %131 = load i8, i8* %arrayidx45.i1220.i.us, align 1, !tbaa !20
  %cmp47.i1221.i.us = icmp eq i8 %131, 3
  br i1 %cmp47.i1221.i.us, label %for.inc730.i.us, label %land.lhs.true49.i1225.i.us

land.lhs.true49.i1225.i.us:                       ; preds = %lor.lhs.false42.i1222.i.us
  %origin53.i1223.i.us = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %130, i32 2
  %132 = load i32, i32* %origin53.i1223.i.us, align 4, !tbaa !15
  %cmp54.i1224.i.us = icmp eq i32 %132, %16
  br i1 %cmp54.i1224.i.us, label %land.lhs.true722.i.us, label %for.inc730.i.us

land.lhs.true722.i.us:                            ; preds = %land.lhs.true49.i1225.i.us, %land.lhs.true35.i1217.i.us, %land.lhs.true21.i1209.i.us, %land.lhs.true.i1201.i.us
  %133 = load i8, i8* %arrayidx714.i.us, align 1, !tbaa !20
  %cmp1.i1231.i.us = icmp eq i8 %133, 0
  br i1 %cmp1.i1231.i.us, label %if.end4.i1236.i.us, label %land.lhs.true725.i.us

if.end4.i1236.i.us:                               ; preds = %land.lhs.true722.i.us
  %134 = load i8, i8* %arrayidx6.i1196.i.us, align 1, !tbaa !20
  %cmp8.i1235.i.us = icmp eq i8 %134, 3
  br i1 %cmp8.i1235.i.us, label %lor.lhs.false.i1244.i.us, label %land.lhs.true.i1239.i.us

land.lhs.true.i1239.i.us:                         ; preds = %if.end4.i1236.i.us
  %origin13.i1237.i.us = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %121, i32 2
  %135 = load i32, i32* %origin13.i1237.i.us, align 4, !tbaa !15
  %cmp14.i1238.i.us = icmp eq i32 %135, %15
  br i1 %cmp14.i1238.i.us, label %for.inc730.i.us, label %lor.lhs.false.i1244.i.us

lor.lhs.false.i1244.i.us:                         ; preds = %land.lhs.true.i1239.i.us, %if.end4.i1236.i.us
  %136 = add nsw i64 %indvars.iv1373.i.us, -1
  %arrayidx17.i1242.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %136
  %137 = load i8, i8* %arrayidx17.i1242.i.us, align 1, !tbaa !20
  %cmp19.i1243.i.us = icmp eq i8 %137, 3
  br i1 %cmp19.i1243.i.us, label %lor.lhs.false28.i1252.i.us, label %land.lhs.true21.i1247.i.us

land.lhs.true21.i1247.i.us:                       ; preds = %lor.lhs.false.i1244.i.us
  %origin25.i1245.i.us = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %136, i32 2
  %138 = load i32, i32* %origin25.i1245.i.us, align 4, !tbaa !15
  %cmp26.i1246.i.us = icmp eq i32 %138, %15
  br i1 %cmp26.i1246.i.us, label %for.inc730.i.us, label %lor.lhs.false28.i1252.i.us

lor.lhs.false28.i1252.i.us:                       ; preds = %land.lhs.true21.i1247.i.us, %lor.lhs.false.i1244.i.us
  %139 = add nsw i64 %indvars.iv1373.i.us, -20
  %arrayidx31.i1250.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %139
  %140 = load i8, i8* %arrayidx31.i1250.i.us, align 1, !tbaa !20
  %cmp33.i1251.i.us = icmp eq i8 %140, 3
  br i1 %cmp33.i1251.i.us, label %lor.lhs.false42.i1260.i.us, label %land.lhs.true35.i1255.i.us

land.lhs.true35.i1255.i.us:                       ; preds = %lor.lhs.false28.i1252.i.us
  %origin39.i1253.i.us = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %139, i32 2
  %141 = load i32, i32* %origin39.i1253.i.us, align 4, !tbaa !15
  %cmp40.i1254.i.us = icmp eq i32 %141, %15
  br i1 %cmp40.i1254.i.us, label %for.inc730.i.us, label %lor.lhs.false42.i1260.i.us

lor.lhs.false42.i1260.i.us:                       ; preds = %land.lhs.true35.i1255.i.us, %lor.lhs.false28.i1252.i.us
  %142 = add nuw nsw i64 %indvars.iv1373.i.us, 1
  %arrayidx45.i1258.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %142
  %143 = load i8, i8* %arrayidx45.i1258.i.us, align 1, !tbaa !20
  %cmp47.i1259.i.us = icmp eq i8 %143, 3
  br i1 %cmp47.i1259.i.us, label %land.lhs.true725.i.us, label %land.lhs.true49.i1263.i.us

land.lhs.true49.i1263.i.us:                       ; preds = %lor.lhs.false42.i1260.i.us
  %origin53.i1261.i.us = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %142, i32 2
  %144 = load i32, i32* %origin53.i1261.i.us, align 4, !tbaa !15
  %cmp54.i1262.i.us = icmp eq i32 %144, %15
  br i1 %cmp54.i1262.i.us, label %for.inc730.i.us, label %land.lhs.true725.i.us

land.lhs.true725.i.us:                            ; preds = %land.lhs.true49.i1263.i.us, %lor.lhs.false42.i1260.i.us, %land.lhs.true722.i.us
  %145 = trunc i64 %indvars.iv1373.i.us to i32
  %call726.i.us = call i32 @safe_move(i32 %145, i32 %conv.i) #3
  %tobool727.i.us = icmp eq i32 %call726.i.us, 0
  br i1 %tobool727.i.us, label %for.inc730.i.us, label %if.then.i1268.i.us

if.then.i1268.i.us:                               ; preds = %land.lhs.true725.i.us
  call void @add_semeai_move(i32 %145, i32 %15) #3
  br i1 %cmp6381328.i, label %if.then5.i1274.i.us, label %if.else6.i1276.i.us

if.else6.i1276.i.us:                              ; preds = %if.then.i1268.i.us
  br i1 %cmp7.i1275.i, label %if.then8.i1277.i.us, label %for.inc730.i.us

if.then8.i1277.i.us:                              ; preds = %if.else6.i1276.i.us
  call void @add_semeai_threat(i32 %145, i32 %16) #3
  br label %for.inc730.i.us

if.then5.i1274.i.us:                              ; preds = %if.then.i1268.i.us
  call void @add_semeai_move(i32 %145, i32 %16) #3
  br label %for.inc730.i.us

for.inc730.i.us:                                  ; preds = %if.then5.i1274.i.us, %if.then8.i1277.i.us, %if.else6.i1276.i.us, %land.lhs.true725.i.us, %land.lhs.true49.i1263.i.us, %land.lhs.true35.i1255.i.us, %land.lhs.true21.i1247.i.us, %land.lhs.true.i1239.i.us, %land.lhs.true49.i1225.i.us, %lor.lhs.false42.i1222.i.us, %for.body712.i.us
  %found_one.1.i.us = phi i32 [ %found_one.01339.i.us, %land.lhs.true725.i.us ], [ 1, %if.then5.i1274.i.us ], [ 1, %if.else6.i1276.i.us ], [ 1, %if.then8.i1277.i.us ], [ %found_one.01339.i.us, %land.lhs.true49.i1225.i.us ], [ %found_one.01339.i.us, %lor.lhs.false42.i1222.i.us ], [ %found_one.01339.i.us, %land.lhs.true49.i1263.i.us ], [ %found_one.01339.i.us, %land.lhs.true35.i1255.i.us ], [ %found_one.01339.i.us, %land.lhs.true21.i1247.i.us ], [ %found_one.01339.i.us, %land.lhs.true.i1239.i.us ], [ %found_one.01339.i.us, %for.body712.i.us ]
  %indvars.iv.next1374.i.us = add nuw nsw i64 %indvars.iv1373.i.us, 1
  %exitcond1383.i.us = icmp eq i64 %indvars.iv.next1374.i.us, 400
  br i1 %exitcond1383.i.us, label %for.end732.i.loopexit, label %for.body712.i.us

if.then675.i:                                     ; preds = %if.else672.i
  %146 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %147 = load i32, i32* %id, align 4, !tbaa !18
  %idxprom679.i = sext i32 %147 to i64
  %genus681.i = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %146, i64 %idxprom679.i, i32 10
  %call682.i = call i32 @eye_move_urgency(%struct.eyevalue* %genus681.i) #3
  %cmp683.i = icmp sgt i32 %call682.i, 0
  br i1 %cmp683.i, label %if.then685.i, label %if.end691.i

if.then685.i:                                     ; preds = %if.then675.i
  %148 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %149 = load i32, i32* %id, align 4, !tbaa !18
  %idxprom689.i = sext i32 %149 to i64
  %heye.i = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %148, i64 %idxprom689.i, i32 11
  %150 = load i32, i32* %heye.i, align 4, !tbaa !26
  br i1 %cmp6351327.i, label %if.then.i1168.i, label %if.else.i1170.i

if.then.i1168.i:                                  ; preds = %if.then685.i
  call void @add_semeai_move(i32 %150, i32 %15) #3
  br label %if.end3.i1173.i

if.else.i1170.i:                                  ; preds = %if.then685.i
  %cmp1.i1169.i = icmp eq i32 %margin_of_safety.3.i, 1
  br i1 %cmp1.i1169.i, label %if.then2.i1171.i, label %if.end3.i1173.i

if.then2.i1171.i:                                 ; preds = %if.else.i1170.i
  call void @add_semeai_threat(i32 %150, i32 %15) #3
  br label %if.end3.i1173.i

if.end3.i1173.i:                                  ; preds = %if.then2.i1171.i, %if.else.i1170.i, %if.then.i1168.i
  br i1 %cmp6381328.i, label %if.then5.i1174.i, label %if.else6.i1176.i

if.then5.i1174.i:                                 ; preds = %if.end3.i1173.i
  call void @add_semeai_move(i32 %150, i32 %16) #3
  br label %if.end691.i

if.else6.i1176.i:                                 ; preds = %if.end3.i1173.i
  %cmp7.i1175.i = icmp eq i32 %margin_of_safety.3.i, 1
  br i1 %cmp7.i1175.i, label %if.then8.i1177.i, label %if.end691.i

if.then8.i1177.i:                                 ; preds = %if.else6.i1176.i
  call void @add_semeai_threat(i32 %150, i32 %16) #3
  br label %if.end691.i

if.end691.i:                                      ; preds = %if.then8.i1177.i, %if.else6.i1176.i, %if.then5.i1174.i, %if.then675.i
  %cmp6381329.i = phi i1 [ %cmp6381328.i, %if.then675.i ], [ true, %if.then5.i1174.i ], [ false, %if.else6.i1176.i ], [ false, %if.then8.i1177.i ]
  %151 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %152 = load i32, i32* %id82, align 4, !tbaa !18
  %idxprom695.i = sext i32 %152 to i64
  %genus697.i = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %151, i64 %idxprom695.i, i32 10
  %call698.i = call i32 @eye_move_urgency(%struct.eyevalue* %genus697.i) #3
  %tobool699.i = icmp eq i32 %call698.i, 0
  br i1 %tobool699.i, label %for.inc, label %if.then700.i

if.then700.i:                                     ; preds = %if.end691.i
  %153 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %154 = load i32, i32* %id82, align 4, !tbaa !18
  %idxprom704.i = sext i32 %154 to i64
  %heye706.i = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %153, i64 %idxprom704.i, i32 11
  %155 = load i32, i32* %heye706.i, align 4, !tbaa !26
  br i1 %cmp6351327.i, label %if.then.i1180.i, label %if.else.i1182.i

if.then.i1180.i:                                  ; preds = %if.then700.i
  call void @add_semeai_move(i32 %155, i32 %15) #3
  br label %if.end3.i1185.i

if.else.i1182.i:                                  ; preds = %if.then700.i
  %cmp1.i1181.i = icmp eq i32 %margin_of_safety.3.i, 1
  br i1 %cmp1.i1181.i, label %if.then2.i1183.i, label %if.end3.i1185.i

if.then2.i1183.i:                                 ; preds = %if.else.i1182.i
  call void @add_semeai_threat(i32 %155, i32 %15) #3
  br label %if.end3.i1185.i

if.end3.i1185.i:                                  ; preds = %if.then2.i1183.i, %if.else.i1182.i, %if.then.i1180.i
  br i1 %cmp6381329.i, label %if.then5.i1186.i, label %if.else6.i1188.i

if.then5.i1186.i:                                 ; preds = %if.end3.i1185.i
  call void @add_semeai_move(i32 %155, i32 %16) #3
  br label %for.inc

if.else6.i1188.i:                                 ; preds = %if.end3.i1185.i
  %cmp7.i1187.i = icmp eq i32 %margin_of_safety.3.i, 1
  br i1 %cmp7.i1187.i, label %if.then8.i1189.i, label %for.inc

if.then8.i1189.i:                                 ; preds = %if.else6.i1188.i
  call void @add_semeai_threat(i32 %155, i32 %16) #3
  br label %for.inc

for.body712.i:                                    ; preds = %for.body712.i.preheader, %for.inc730.i
  %indvars.iv1373.i = phi i64 [ %indvars.iv.next1374.i, %for.inc730.i ], [ 21, %for.body712.i.preheader ]
  %found_one.01339.i = phi i32 [ %found_one.1.i, %for.inc730.i ], [ 0, %for.body712.i.preheader ]
  %arrayidx714.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %indvars.iv1373.i
  %156 = load i8, i8* %arrayidx714.i, align 1, !tbaa !20
  %cond.i = icmp eq i8 %156, 0
  br i1 %cond.i, label %if.end4.i1198.i, label %for.inc730.i

if.end4.i1198.i:                                  ; preds = %for.body712.i
  %157 = add nuw nsw i64 %indvars.iv1373.i, 20
  %arrayidx6.i1196.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %157
  %158 = load i8, i8* %arrayidx6.i1196.i, align 1, !tbaa !20
  %cmp8.i1197.i = icmp eq i8 %158, 3
  br i1 %cmp8.i1197.i, label %lor.lhs.false.i1206.i, label %land.lhs.true.i1201.i

land.lhs.true.i1201.i:                            ; preds = %if.end4.i1198.i
  %origin13.i1199.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %157, i32 2
  %159 = load i32, i32* %origin13.i1199.i, align 4, !tbaa !15
  %cmp14.i1200.i = icmp eq i32 %159, %16
  br i1 %cmp14.i1200.i, label %land.lhs.true722.i, label %lor.lhs.false.i1206.i

lor.lhs.false.i1206.i:                            ; preds = %land.lhs.true.i1201.i, %if.end4.i1198.i
  %160 = add nsw i64 %indvars.iv1373.i, -1
  %arrayidx17.i1204.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %160
  %161 = load i8, i8* %arrayidx17.i1204.i, align 1, !tbaa !20
  %cmp19.i1205.i = icmp eq i8 %161, 3
  br i1 %cmp19.i1205.i, label %lor.lhs.false28.i1214.i, label %land.lhs.true21.i1209.i

land.lhs.true21.i1209.i:                          ; preds = %lor.lhs.false.i1206.i
  %origin25.i1207.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %160, i32 2
  %162 = load i32, i32* %origin25.i1207.i, align 4, !tbaa !15
  %cmp26.i1208.i = icmp eq i32 %162, %16
  br i1 %cmp26.i1208.i, label %land.lhs.true722.i, label %lor.lhs.false28.i1214.i

lor.lhs.false28.i1214.i:                          ; preds = %land.lhs.true21.i1209.i, %lor.lhs.false.i1206.i
  %163 = add nsw i64 %indvars.iv1373.i, -20
  %arrayidx31.i1212.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %163
  %164 = load i8, i8* %arrayidx31.i1212.i, align 1, !tbaa !20
  %cmp33.i1213.i = icmp eq i8 %164, 3
  br i1 %cmp33.i1213.i, label %lor.lhs.false42.i1222.i, label %land.lhs.true35.i1217.i

land.lhs.true35.i1217.i:                          ; preds = %lor.lhs.false28.i1214.i
  %origin39.i1215.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %163, i32 2
  %165 = load i32, i32* %origin39.i1215.i, align 4, !tbaa !15
  %cmp40.i1216.i = icmp eq i32 %165, %16
  br i1 %cmp40.i1216.i, label %land.lhs.true722.i, label %lor.lhs.false42.i1222.i

lor.lhs.false42.i1222.i:                          ; preds = %land.lhs.true35.i1217.i, %lor.lhs.false28.i1214.i
  %166 = add nuw nsw i64 %indvars.iv1373.i, 1
  %arrayidx45.i1220.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %166
  %167 = load i8, i8* %arrayidx45.i1220.i, align 1, !tbaa !20
  %cmp47.i1221.i = icmp eq i8 %167, 3
  br i1 %cmp47.i1221.i, label %for.inc730.i, label %land.lhs.true49.i1225.i

land.lhs.true49.i1225.i:                          ; preds = %lor.lhs.false42.i1222.i
  %origin53.i1223.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %166, i32 2
  %168 = load i32, i32* %origin53.i1223.i, align 4, !tbaa !15
  %cmp54.i1224.i = icmp eq i32 %168, %16
  br i1 %cmp54.i1224.i, label %land.lhs.true722.i, label %for.inc730.i

land.lhs.true722.i:                               ; preds = %land.lhs.true49.i1225.i, %land.lhs.true35.i1217.i, %land.lhs.true21.i1209.i, %land.lhs.true.i1201.i
  %169 = load i8, i8* %arrayidx714.i, align 1, !tbaa !20
  %cmp1.i1231.i = icmp eq i8 %169, 0
  br i1 %cmp1.i1231.i, label %if.end4.i1236.i, label %land.lhs.true725.i

if.end4.i1236.i:                                  ; preds = %land.lhs.true722.i
  %170 = load i8, i8* %arrayidx6.i1196.i, align 1, !tbaa !20
  %cmp8.i1235.i = icmp eq i8 %170, 3
  br i1 %cmp8.i1235.i, label %lor.lhs.false.i1244.i, label %land.lhs.true.i1239.i

land.lhs.true.i1239.i:                            ; preds = %if.end4.i1236.i
  %origin13.i1237.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %157, i32 2
  %171 = load i32, i32* %origin13.i1237.i, align 4, !tbaa !15
  %cmp14.i1238.i = icmp eq i32 %171, %15
  br i1 %cmp14.i1238.i, label %for.inc730.i, label %lor.lhs.false.i1244.i

lor.lhs.false.i1244.i:                            ; preds = %land.lhs.true.i1239.i, %if.end4.i1236.i
  %172 = add nsw i64 %indvars.iv1373.i, -1
  %arrayidx17.i1242.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %172
  %173 = load i8, i8* %arrayidx17.i1242.i, align 1, !tbaa !20
  %cmp19.i1243.i = icmp eq i8 %173, 3
  br i1 %cmp19.i1243.i, label %lor.lhs.false28.i1252.i, label %land.lhs.true21.i1247.i

land.lhs.true21.i1247.i:                          ; preds = %lor.lhs.false.i1244.i
  %origin25.i1245.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %172, i32 2
  %174 = load i32, i32* %origin25.i1245.i, align 4, !tbaa !15
  %cmp26.i1246.i = icmp eq i32 %174, %15
  br i1 %cmp26.i1246.i, label %for.inc730.i, label %lor.lhs.false28.i1252.i

lor.lhs.false28.i1252.i:                          ; preds = %land.lhs.true21.i1247.i, %lor.lhs.false.i1244.i
  %175 = add nsw i64 %indvars.iv1373.i, -20
  %arrayidx31.i1250.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %175
  %176 = load i8, i8* %arrayidx31.i1250.i, align 1, !tbaa !20
  %cmp33.i1251.i = icmp eq i8 %176, 3
  br i1 %cmp33.i1251.i, label %lor.lhs.false42.i1260.i, label %land.lhs.true35.i1255.i

land.lhs.true35.i1255.i:                          ; preds = %lor.lhs.false28.i1252.i
  %origin39.i1253.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %175, i32 2
  %177 = load i32, i32* %origin39.i1253.i, align 4, !tbaa !15
  %cmp40.i1254.i = icmp eq i32 %177, %15
  br i1 %cmp40.i1254.i, label %for.inc730.i, label %lor.lhs.false42.i1260.i

lor.lhs.false42.i1260.i:                          ; preds = %land.lhs.true35.i1255.i, %lor.lhs.false28.i1252.i
  %178 = add nuw nsw i64 %indvars.iv1373.i, 1
  %arrayidx45.i1258.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %178
  %179 = load i8, i8* %arrayidx45.i1258.i, align 1, !tbaa !20
  %cmp47.i1259.i = icmp eq i8 %179, 3
  br i1 %cmp47.i1259.i, label %land.lhs.true725.i, label %land.lhs.true49.i1263.i

land.lhs.true49.i1263.i:                          ; preds = %lor.lhs.false42.i1260.i
  %origin53.i1261.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %178, i32 2
  %180 = load i32, i32* %origin53.i1261.i, align 4, !tbaa !15
  %cmp54.i1262.i = icmp eq i32 %180, %15
  br i1 %cmp54.i1262.i, label %for.inc730.i, label %land.lhs.true725.i

land.lhs.true725.i:                               ; preds = %land.lhs.true49.i1263.i, %lor.lhs.false42.i1260.i, %land.lhs.true722.i
  %181 = trunc i64 %indvars.iv1373.i to i32
  %call726.i = call i32 @safe_move(i32 %181, i32 %conv.i) #3
  %tobool727.i = icmp eq i32 %call726.i, 0
  br i1 %tobool727.i, label %for.inc730.i, label %if.else.i1270.i

if.else.i1270.i:                                  ; preds = %land.lhs.true725.i
  br i1 %cmp7.i1275.i, label %if.then2.i1271.i, label %if.end3.i1273.i

if.then2.i1271.i:                                 ; preds = %if.else.i1270.i
  call void @add_semeai_threat(i32 %181, i32 %15) #3
  br label %if.end3.i1273.i

if.end3.i1273.i:                                  ; preds = %if.then2.i1271.i, %if.else.i1270.i
  br i1 %cmp6381328.i, label %if.then5.i1274.i, label %if.else6.i1276.i

if.then5.i1274.i:                                 ; preds = %if.end3.i1273.i
  call void @add_semeai_move(i32 %181, i32 %16) #3
  br label %for.inc730.i

if.else6.i1276.i:                                 ; preds = %if.end3.i1273.i
  br i1 %cmp7.i1275.i, label %if.then8.i1277.i, label %for.inc730.i

if.then8.i1277.i:                                 ; preds = %if.else6.i1276.i
  call void @add_semeai_threat(i32 %181, i32 %16) #3
  br label %for.inc730.i

for.inc730.i:                                     ; preds = %if.then8.i1277.i, %if.else6.i1276.i, %if.then5.i1274.i, %land.lhs.true725.i, %land.lhs.true49.i1263.i, %land.lhs.true35.i1255.i, %land.lhs.true21.i1247.i, %land.lhs.true.i1239.i, %land.lhs.true49.i1225.i, %lor.lhs.false42.i1222.i, %for.body712.i
  %found_one.1.i = phi i32 [ %found_one.01339.i, %land.lhs.true725.i ], [ 1, %if.then5.i1274.i ], [ 1, %if.else6.i1276.i ], [ 1, %if.then8.i1277.i ], [ %found_one.01339.i, %land.lhs.true49.i1225.i ], [ %found_one.01339.i, %lor.lhs.false42.i1222.i ], [ %found_one.01339.i, %land.lhs.true49.i1263.i ], [ %found_one.01339.i, %land.lhs.true35.i1255.i ], [ %found_one.01339.i, %land.lhs.true21.i1247.i ], [ %found_one.01339.i, %land.lhs.true.i1239.i ], [ %found_one.01339.i, %for.body712.i ]
  %indvars.iv.next1374.i = add nuw nsw i64 %indvars.iv1373.i, 1
  %exitcond1383.i = icmp eq i64 %indvars.iv.next1374.i, 400
  br i1 %exitcond1383.i, label %for.end732.i.loopexit129, label %for.body712.i

for.end732.i.loopexit:                            ; preds = %for.inc730.i.us
  %found_one.1.i.us.lcssa = phi i32 [ %found_one.1.i.us, %for.inc730.i.us ]
  br label %for.end732.i

for.end732.i.loopexit129:                         ; preds = %for.inc730.i
  %found_one.1.i.lcssa130 = phi i32 [ %found_one.1.i, %for.inc730.i ]
  br label %for.end732.i

for.end732.i:                                     ; preds = %for.end732.i.loopexit129, %for.end732.i.loopexit
  %found_one.1.i.lcssa = phi i32 [ %found_one.1.i.us.lcssa, %for.end732.i.loopexit ], [ %found_one.1.i.lcssa130, %for.end732.i.loopexit129 ]
  %tobool733.i = icmp eq i32 %found_one.1.i.lcssa, 0
  br i1 %tobool733.i, label %for.cond735.preheader.i, label %for.inc

for.cond735.preheader.i:                          ; preds = %for.end732.i
  br i1 %cmp6351327.i, label %for.body738.us.i.preheader, label %for.body738.i.preheader

for.body738.i.preheader:                          ; preds = %for.cond735.preheader.i
  br i1 %cmp7.i1275.i, label %for.body738.i.us.preheader, label %for.body738.i.preheader127

for.body738.i.preheader127:                       ; preds = %for.body738.i.preheader
  br label %for.body738.i

for.body738.i.us.preheader:                       ; preds = %for.body738.i.preheader
  br label %for.body738.i.us

for.body738.i.us:                                 ; preds = %for.body738.i.us.preheader, %for.inc752.i.us
  %indvars.iv1366.i.us = phi i64 [ %indvars.iv.next1367.i.us, %for.inc752.i.us ], [ 21, %for.body738.i.us.preheader ]
  %arrayidx740.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %indvars.iv1366.i.us
  %182 = load i8, i8* %arrayidx740.i.us, align 1, !tbaa !20
  %cond1333.i.us = icmp eq i8 %182, 0
  br i1 %cond1333.i.us, label %if.end4.i1286.i.us, label %for.inc752.i.us

if.end4.i1286.i.us:                               ; preds = %for.body738.i.us
  %183 = add nuw nsw i64 %indvars.iv1366.i.us, 20
  %arrayidx6.i1284.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %183
  %184 = load i8, i8* %arrayidx6.i1284.i.us, align 1, !tbaa !20
  %cmp8.i1285.i.us = icmp eq i8 %184, 3
  br i1 %cmp8.i1285.i.us, label %lor.lhs.false.i1294.i.us, label %land.lhs.true.i1289.i.us

land.lhs.true.i1289.i.us:                         ; preds = %if.end4.i1286.i.us
  %origin13.i1287.i.us = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %183, i32 2
  %185 = load i32, i32* %origin13.i1287.i.us, align 4, !tbaa !15
  %cmp14.i1288.i.us = icmp eq i32 %185, %16
  br i1 %cmp14.i1288.i.us, label %land.lhs.true747.i.us, label %lor.lhs.false.i1294.i.us

lor.lhs.false.i1294.i.us:                         ; preds = %land.lhs.true.i1289.i.us, %if.end4.i1286.i.us
  %186 = add nsw i64 %indvars.iv1366.i.us, -1
  %arrayidx17.i1292.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %186
  %187 = load i8, i8* %arrayidx17.i1292.i.us, align 1, !tbaa !20
  %cmp19.i1293.i.us = icmp eq i8 %187, 3
  br i1 %cmp19.i1293.i.us, label %lor.lhs.false28.i1302.i.us, label %land.lhs.true21.i1297.i.us

land.lhs.true21.i1297.i.us:                       ; preds = %lor.lhs.false.i1294.i.us
  %origin25.i1295.i.us = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %186, i32 2
  %188 = load i32, i32* %origin25.i1295.i.us, align 4, !tbaa !15
  %cmp26.i1296.i.us = icmp eq i32 %188, %16
  br i1 %cmp26.i1296.i.us, label %land.lhs.true747.i.us, label %lor.lhs.false28.i1302.i.us

lor.lhs.false28.i1302.i.us:                       ; preds = %land.lhs.true21.i1297.i.us, %lor.lhs.false.i1294.i.us
  %189 = add nsw i64 %indvars.iv1366.i.us, -20
  %arrayidx31.i1300.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %189
  %190 = load i8, i8* %arrayidx31.i1300.i.us, align 1, !tbaa !20
  %cmp33.i1301.i.us = icmp eq i8 %190, 3
  br i1 %cmp33.i1301.i.us, label %lor.lhs.false42.i1310.i.us, label %land.lhs.true35.i1305.i.us

land.lhs.true35.i1305.i.us:                       ; preds = %lor.lhs.false28.i1302.i.us
  %origin39.i1303.i.us = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %189, i32 2
  %191 = load i32, i32* %origin39.i1303.i.us, align 4, !tbaa !15
  %cmp40.i1304.i.us = icmp eq i32 %191, %16
  br i1 %cmp40.i1304.i.us, label %land.lhs.true747.i.us, label %lor.lhs.false42.i1310.i.us

lor.lhs.false42.i1310.i.us:                       ; preds = %land.lhs.true35.i1305.i.us, %lor.lhs.false28.i1302.i.us
  %192 = add nuw nsw i64 %indvars.iv1366.i.us, 1
  %arrayidx45.i1308.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %192
  %193 = load i8, i8* %arrayidx45.i1308.i.us, align 1, !tbaa !20
  %cmp47.i1309.i.us = icmp eq i8 %193, 3
  br i1 %cmp47.i1309.i.us, label %for.inc752.i.us, label %land.lhs.true49.i1313.i.us

land.lhs.true49.i1313.i.us:                       ; preds = %lor.lhs.false42.i1310.i.us
  %origin53.i1311.i.us = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %192, i32 2
  %194 = load i32, i32* %origin53.i1311.i.us, align 4, !tbaa !15
  %cmp54.i1312.i.us = icmp eq i32 %194, %16
  br i1 %cmp54.i1312.i.us, label %land.lhs.true747.i.us, label %for.inc752.i.us

land.lhs.true747.i.us:                            ; preds = %land.lhs.true49.i1313.i.us, %land.lhs.true35.i1305.i.us, %land.lhs.true21.i1297.i.us, %land.lhs.true.i1289.i.us
  %195 = trunc i64 %indvars.iv1366.i.us to i32
  %call748.i.us = call i32 @safe_move(i32 %195, i32 %conv.i) #3
  %tobool749.i.us = icmp eq i32 %call748.i.us, 0
  br i1 %tobool749.i.us, label %for.inc752.i.us, label %if.then2.i.i.us

if.then2.i.i.us:                                  ; preds = %land.lhs.true747.i.us
  call void @add_semeai_threat(i32 %195, i32 %15) #3
  br i1 %cmp6381328.i, label %if.then5.i.i.us, label %if.then8.i.i.us

if.then8.i.i.us:                                  ; preds = %if.then2.i.i.us
  call void @add_semeai_threat(i32 %195, i32 %16) #3
  br label %for.inc752.i.us

if.then5.i.i.us:                                  ; preds = %if.then2.i.i.us
  call void @add_semeai_move(i32 %195, i32 %16) #3
  br label %for.inc752.i.us

for.inc752.i.us:                                  ; preds = %if.then5.i.i.us, %if.then8.i.i.us, %land.lhs.true747.i.us, %land.lhs.true49.i1313.i.us, %lor.lhs.false42.i1310.i.us, %for.body738.i.us
  %indvars.iv.next1367.i.us = add nuw nsw i64 %indvars.iv1366.i.us, 1
  %exitcond1372.i.us = icmp eq i64 %indvars.iv.next1367.i.us, 400
  br i1 %exitcond1372.i.us, label %for.inc.loopexit126, label %for.body738.i.us

for.body738.us.i.preheader:                       ; preds = %for.cond735.preheader.i
  br i1 %cmp6381328.i, label %for.body738.us.i.us.preheader, label %for.body738.us.i.preheader124

for.body738.us.i.preheader124:                    ; preds = %for.body738.us.i.preheader
  br label %for.body738.us.i

for.body738.us.i.us.preheader:                    ; preds = %for.body738.us.i.preheader
  br label %for.body738.us.i.us

for.body738.us.i.us:                              ; preds = %for.body738.us.i.us.preheader, %for.inc752.us.i.us
  %indvars.iv.i.us = phi i64 [ %indvars.iv.next.i.us, %for.inc752.us.i.us ], [ 21, %for.body738.us.i.us.preheader ]
  %arrayidx740.us.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %indvars.iv.i.us
  %196 = load i8, i8* %arrayidx740.us.i.us, align 1, !tbaa !20
  %cond1333.us.i.us = icmp eq i8 %196, 0
  br i1 %cond1333.us.i.us, label %if.end4.i1286.us.i.us, label %for.inc752.us.i.us

if.end4.i1286.us.i.us:                            ; preds = %for.body738.us.i.us
  %197 = add nuw nsw i64 %indvars.iv.i.us, 20
  %arrayidx6.i1284.us.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %197
  %198 = load i8, i8* %arrayidx6.i1284.us.i.us, align 1, !tbaa !20
  %cmp8.i1285.us.i.us = icmp eq i8 %198, 3
  br i1 %cmp8.i1285.us.i.us, label %lor.lhs.false.i1294.us.i.us, label %land.lhs.true.i1289.us.i.us

land.lhs.true.i1289.us.i.us:                      ; preds = %if.end4.i1286.us.i.us
  %origin13.i1287.us.i.us = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %197, i32 2
  %199 = load i32, i32* %origin13.i1287.us.i.us, align 4, !tbaa !15
  %cmp14.i1288.us.i.us = icmp eq i32 %199, %16
  br i1 %cmp14.i1288.us.i.us, label %land.lhs.true747.us.i.us, label %lor.lhs.false.i1294.us.i.us

lor.lhs.false.i1294.us.i.us:                      ; preds = %land.lhs.true.i1289.us.i.us, %if.end4.i1286.us.i.us
  %200 = add nsw i64 %indvars.iv.i.us, -1
  %arrayidx17.i1292.us.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %200
  %201 = load i8, i8* %arrayidx17.i1292.us.i.us, align 1, !tbaa !20
  %cmp19.i1293.us.i.us = icmp eq i8 %201, 3
  br i1 %cmp19.i1293.us.i.us, label %lor.lhs.false28.i1302.us.i.us, label %land.lhs.true21.i1297.us.i.us

land.lhs.true21.i1297.us.i.us:                    ; preds = %lor.lhs.false.i1294.us.i.us
  %origin25.i1295.us.i.us = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %200, i32 2
  %202 = load i32, i32* %origin25.i1295.us.i.us, align 4, !tbaa !15
  %cmp26.i1296.us.i.us = icmp eq i32 %202, %16
  br i1 %cmp26.i1296.us.i.us, label %land.lhs.true747.us.i.us, label %lor.lhs.false28.i1302.us.i.us

lor.lhs.false28.i1302.us.i.us:                    ; preds = %land.lhs.true21.i1297.us.i.us, %lor.lhs.false.i1294.us.i.us
  %203 = add nsw i64 %indvars.iv.i.us, -20
  %arrayidx31.i1300.us.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %203
  %204 = load i8, i8* %arrayidx31.i1300.us.i.us, align 1, !tbaa !20
  %cmp33.i1301.us.i.us = icmp eq i8 %204, 3
  br i1 %cmp33.i1301.us.i.us, label %lor.lhs.false42.i1310.us.i.us, label %land.lhs.true35.i1305.us.i.us

land.lhs.true35.i1305.us.i.us:                    ; preds = %lor.lhs.false28.i1302.us.i.us
  %origin39.i1303.us.i.us = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %203, i32 2
  %205 = load i32, i32* %origin39.i1303.us.i.us, align 4, !tbaa !15
  %cmp40.i1304.us.i.us = icmp eq i32 %205, %16
  br i1 %cmp40.i1304.us.i.us, label %land.lhs.true747.us.i.us, label %lor.lhs.false42.i1310.us.i.us

lor.lhs.false42.i1310.us.i.us:                    ; preds = %land.lhs.true35.i1305.us.i.us, %lor.lhs.false28.i1302.us.i.us
  %206 = add nuw nsw i64 %indvars.iv.i.us, 1
  %arrayidx45.i1308.us.i.us = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %206
  %207 = load i8, i8* %arrayidx45.i1308.us.i.us, align 1, !tbaa !20
  %cmp47.i1309.us.i.us = icmp eq i8 %207, 3
  br i1 %cmp47.i1309.us.i.us, label %for.inc752.us.i.us, label %land.lhs.true49.i1313.us.i.us

land.lhs.true49.i1313.us.i.us:                    ; preds = %lor.lhs.false42.i1310.us.i.us
  %origin53.i1311.us.i.us = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %206, i32 2
  %208 = load i32, i32* %origin53.i1311.us.i.us, align 4, !tbaa !15
  %cmp54.i1312.us.i.us = icmp eq i32 %208, %16
  br i1 %cmp54.i1312.us.i.us, label %land.lhs.true747.us.i.us, label %for.inc752.us.i.us

land.lhs.true747.us.i.us:                         ; preds = %land.lhs.true49.i1313.us.i.us, %land.lhs.true35.i1305.us.i.us, %land.lhs.true21.i1297.us.i.us, %land.lhs.true.i1289.us.i.us
  %209 = trunc i64 %indvars.iv.i.us to i32
  %call748.us.i.us = call i32 @safe_move(i32 %209, i32 %conv.i) #3
  %tobool749.us.i.us = icmp eq i32 %call748.us.i.us, 0
  br i1 %tobool749.us.i.us, label %for.inc752.us.i.us, label %if.then.i.us.i.us

if.then.i.us.i.us:                                ; preds = %land.lhs.true747.us.i.us
  call void @add_semeai_move(i32 %209, i32 %15) #3
  call void @add_semeai_move(i32 %209, i32 %16) #3
  br label %for.inc752.us.i.us

for.inc752.us.i.us:                               ; preds = %if.then.i.us.i.us, %land.lhs.true747.us.i.us, %land.lhs.true49.i1313.us.i.us, %lor.lhs.false42.i1310.us.i.us, %for.body738.us.i.us
  %indvars.iv.next.i.us = add nuw nsw i64 %indvars.iv.i.us, 1
  %exitcond.i.us = icmp eq i64 %indvars.iv.next.i.us, 400
  br i1 %exitcond.i.us, label %for.inc.loopexit, label %for.body738.us.i.us

for.body738.us.i:                                 ; preds = %for.body738.us.i.preheader124, %for.inc752.us.i
  %indvars.iv.i = phi i64 [ %indvars.iv.next.i, %for.inc752.us.i ], [ 21, %for.body738.us.i.preheader124 ]
  %arrayidx740.us.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %indvars.iv.i
  %210 = load i8, i8* %arrayidx740.us.i, align 1, !tbaa !20
  %cond1333.us.i = icmp eq i8 %210, 0
  br i1 %cond1333.us.i, label %if.end4.i1286.us.i, label %for.inc752.us.i

if.end4.i1286.us.i:                               ; preds = %for.body738.us.i
  %211 = add nuw nsw i64 %indvars.iv.i, 20
  %arrayidx6.i1284.us.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %211
  %212 = load i8, i8* %arrayidx6.i1284.us.i, align 1, !tbaa !20
  %cmp8.i1285.us.i = icmp eq i8 %212, 3
  br i1 %cmp8.i1285.us.i, label %lor.lhs.false.i1294.us.i, label %land.lhs.true.i1289.us.i

land.lhs.true.i1289.us.i:                         ; preds = %if.end4.i1286.us.i
  %origin13.i1287.us.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %211, i32 2
  %213 = load i32, i32* %origin13.i1287.us.i, align 4, !tbaa !15
  %cmp14.i1288.us.i = icmp eq i32 %213, %16
  br i1 %cmp14.i1288.us.i, label %land.lhs.true747.us.i, label %lor.lhs.false.i1294.us.i

lor.lhs.false.i1294.us.i:                         ; preds = %land.lhs.true.i1289.us.i, %if.end4.i1286.us.i
  %214 = add nsw i64 %indvars.iv.i, -1
  %arrayidx17.i1292.us.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %214
  %215 = load i8, i8* %arrayidx17.i1292.us.i, align 1, !tbaa !20
  %cmp19.i1293.us.i = icmp eq i8 %215, 3
  br i1 %cmp19.i1293.us.i, label %lor.lhs.false28.i1302.us.i, label %land.lhs.true21.i1297.us.i

land.lhs.true21.i1297.us.i:                       ; preds = %lor.lhs.false.i1294.us.i
  %origin25.i1295.us.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %214, i32 2
  %216 = load i32, i32* %origin25.i1295.us.i, align 4, !tbaa !15
  %cmp26.i1296.us.i = icmp eq i32 %216, %16
  br i1 %cmp26.i1296.us.i, label %land.lhs.true747.us.i, label %lor.lhs.false28.i1302.us.i

lor.lhs.false28.i1302.us.i:                       ; preds = %land.lhs.true21.i1297.us.i, %lor.lhs.false.i1294.us.i
  %217 = add nsw i64 %indvars.iv.i, -20
  %arrayidx31.i1300.us.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %217
  %218 = load i8, i8* %arrayidx31.i1300.us.i, align 1, !tbaa !20
  %cmp33.i1301.us.i = icmp eq i8 %218, 3
  br i1 %cmp33.i1301.us.i, label %lor.lhs.false42.i1310.us.i, label %land.lhs.true35.i1305.us.i

land.lhs.true35.i1305.us.i:                       ; preds = %lor.lhs.false28.i1302.us.i
  %origin39.i1303.us.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %217, i32 2
  %219 = load i32, i32* %origin39.i1303.us.i, align 4, !tbaa !15
  %cmp40.i1304.us.i = icmp eq i32 %219, %16
  br i1 %cmp40.i1304.us.i, label %land.lhs.true747.us.i, label %lor.lhs.false42.i1310.us.i

lor.lhs.false42.i1310.us.i:                       ; preds = %land.lhs.true35.i1305.us.i, %lor.lhs.false28.i1302.us.i
  %220 = add nuw nsw i64 %indvars.iv.i, 1
  %arrayidx45.i1308.us.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %220
  %221 = load i8, i8* %arrayidx45.i1308.us.i, align 1, !tbaa !20
  %cmp47.i1309.us.i = icmp eq i8 %221, 3
  br i1 %cmp47.i1309.us.i, label %for.inc752.us.i, label %land.lhs.true49.i1313.us.i

land.lhs.true49.i1313.us.i:                       ; preds = %lor.lhs.false42.i1310.us.i
  %origin53.i1311.us.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %220, i32 2
  %222 = load i32, i32* %origin53.i1311.us.i, align 4, !tbaa !15
  %cmp54.i1312.us.i = icmp eq i32 %222, %16
  br i1 %cmp54.i1312.us.i, label %land.lhs.true747.us.i, label %for.inc752.us.i

land.lhs.true747.us.i:                            ; preds = %land.lhs.true49.i1313.us.i, %land.lhs.true35.i1305.us.i, %land.lhs.true21.i1297.us.i, %land.lhs.true.i1289.us.i
  %223 = trunc i64 %indvars.iv.i to i32
  %call748.us.i = call i32 @safe_move(i32 %223, i32 %conv.i) #3
  %tobool749.us.i = icmp eq i32 %call748.us.i, 0
  br i1 %tobool749.us.i, label %for.inc752.us.i, label %if.then.i.us.i

if.then.i.us.i:                                   ; preds = %land.lhs.true747.us.i
  call void @add_semeai_move(i32 %223, i32 %15) #3
  br i1 %cmp7.i1275.i, label %if.then8.i.us.i, label %for.inc752.us.i

if.then8.i.us.i:                                  ; preds = %if.then.i.us.i
  call void @add_semeai_threat(i32 %223, i32 %16) #3
  br label %for.inc752.us.i

for.inc752.us.i:                                  ; preds = %if.then8.i.us.i, %if.then.i.us.i, %land.lhs.true747.us.i, %land.lhs.true49.i1313.us.i, %lor.lhs.false42.i1310.us.i, %for.body738.us.i
  %indvars.iv.next.i = add nuw nsw i64 %indvars.iv.i, 1
  %exitcond.i = icmp eq i64 %indvars.iv.next.i, 400
  br i1 %exitcond.i, label %for.inc.loopexit125, label %for.body738.us.i

for.body738.i:                                    ; preds = %for.body738.i.preheader127, %for.inc752.i
  %indvars.iv1366.i = phi i64 [ %indvars.iv.next1367.i, %for.inc752.i ], [ 21, %for.body738.i.preheader127 ]
  %arrayidx740.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %indvars.iv1366.i
  %224 = load i8, i8* %arrayidx740.i, align 1, !tbaa !20
  %cond1333.i = icmp eq i8 %224, 0
  br i1 %cond1333.i, label %if.end4.i1286.i, label %for.inc752.i

if.end4.i1286.i:                                  ; preds = %for.body738.i
  %225 = add nuw nsw i64 %indvars.iv1366.i, 20
  %arrayidx6.i1284.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %225
  %226 = load i8, i8* %arrayidx6.i1284.i, align 1, !tbaa !20
  %cmp8.i1285.i = icmp eq i8 %226, 3
  br i1 %cmp8.i1285.i, label %lor.lhs.false.i1294.i, label %land.lhs.true.i1289.i

land.lhs.true.i1289.i:                            ; preds = %if.end4.i1286.i
  %origin13.i1287.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %225, i32 2
  %227 = load i32, i32* %origin13.i1287.i, align 4, !tbaa !15
  %cmp14.i1288.i = icmp eq i32 %227, %16
  br i1 %cmp14.i1288.i, label %land.lhs.true747.i, label %lor.lhs.false.i1294.i

lor.lhs.false.i1294.i:                            ; preds = %land.lhs.true.i1289.i, %if.end4.i1286.i
  %228 = add nsw i64 %indvars.iv1366.i, -1
  %arrayidx17.i1292.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %228
  %229 = load i8, i8* %arrayidx17.i1292.i, align 1, !tbaa !20
  %cmp19.i1293.i = icmp eq i8 %229, 3
  br i1 %cmp19.i1293.i, label %lor.lhs.false28.i1302.i, label %land.lhs.true21.i1297.i

land.lhs.true21.i1297.i:                          ; preds = %lor.lhs.false.i1294.i
  %origin25.i1295.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %228, i32 2
  %230 = load i32, i32* %origin25.i1295.i, align 4, !tbaa !15
  %cmp26.i1296.i = icmp eq i32 %230, %16
  br i1 %cmp26.i1296.i, label %land.lhs.true747.i, label %lor.lhs.false28.i1302.i

lor.lhs.false28.i1302.i:                          ; preds = %land.lhs.true21.i1297.i, %lor.lhs.false.i1294.i
  %231 = add nsw i64 %indvars.iv1366.i, -20
  %arrayidx31.i1300.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %231
  %232 = load i8, i8* %arrayidx31.i1300.i, align 1, !tbaa !20
  %cmp33.i1301.i = icmp eq i8 %232, 3
  br i1 %cmp33.i1301.i, label %lor.lhs.false42.i1310.i, label %land.lhs.true35.i1305.i

land.lhs.true35.i1305.i:                          ; preds = %lor.lhs.false28.i1302.i
  %origin39.i1303.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %231, i32 2
  %233 = load i32, i32* %origin39.i1303.i, align 4, !tbaa !15
  %cmp40.i1304.i = icmp eq i32 %233, %16
  br i1 %cmp40.i1304.i, label %land.lhs.true747.i, label %lor.lhs.false42.i1310.i

lor.lhs.false42.i1310.i:                          ; preds = %land.lhs.true35.i1305.i, %lor.lhs.false28.i1302.i
  %234 = add nuw nsw i64 %indvars.iv1366.i, 1
  %arrayidx45.i1308.i = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %234
  %235 = load i8, i8* %arrayidx45.i1308.i, align 1, !tbaa !20
  %cmp47.i1309.i = icmp eq i8 %235, 3
  br i1 %cmp47.i1309.i, label %for.inc752.i, label %land.lhs.true49.i1313.i

land.lhs.true49.i1313.i:                          ; preds = %lor.lhs.false42.i1310.i
  %origin53.i1311.i = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %234, i32 2
  %236 = load i32, i32* %origin53.i1311.i, align 4, !tbaa !15
  %cmp54.i1312.i = icmp eq i32 %236, %16
  br i1 %cmp54.i1312.i, label %land.lhs.true747.i, label %for.inc752.i

land.lhs.true747.i:                               ; preds = %land.lhs.true49.i1313.i, %land.lhs.true35.i1305.i, %land.lhs.true21.i1297.i, %land.lhs.true.i1289.i
  %237 = trunc i64 %indvars.iv1366.i to i32
  %call748.i = call i32 @safe_move(i32 %237, i32 %conv.i) #3
  %tobool749.i = icmp eq i32 %call748.i, 0
  %cmp6381328.i.not = xor i1 %cmp6381328.i, true
  %brmerge = or i1 %tobool749.i, %cmp6381328.i.not
  br i1 %brmerge, label %for.inc752.i, label %if.then5.i.i

if.then5.i.i:                                     ; preds = %land.lhs.true747.i
  call void @add_semeai_move(i32 %237, i32 %16) #3
  br label %for.inc752.i

for.inc752.i:                                     ; preds = %land.lhs.true747.i, %if.then5.i.i, %land.lhs.true49.i1313.i, %lor.lhs.false42.i1310.i, %for.body738.i
  %indvars.iv.next1367.i = add nuw nsw i64 %indvars.iv1366.i, 1
  %exitcond1372.i = icmp eq i64 %indvars.iv.next1367.i, 400
  br i1 %exitcond1372.i, label %for.inc.loopexit128, label %for.body738.i

for.inc.loopexit:                                 ; preds = %for.inc752.us.i.us
  br label %for.inc

for.inc.loopexit125:                              ; preds = %for.inc752.us.i
  br label %for.inc

for.inc.loopexit126:                              ; preds = %for.inc752.i.us
  br label %for.inc

for.inc.loopexit128:                              ; preds = %for.inc752.i
  br label %for.inc

for.inc:                                          ; preds = %for.inc.loopexit128, %for.inc.loopexit126, %for.inc.loopexit125, %for.inc.loopexit, %for.end732.i, %if.then8.i1189.i, %if.else6.i1188.i, %if.then5.i1186.i, %if.end691.i, %if.then8.i1165.i, %if.else6.i1164.i, %if.then5.i1162.i, %if.then8.i1153.i, %if.else6.i1152.i, %if.then5.i1150.i, %if.end634.i, %cleanup216.thread.i, %cond.false145.i, %if.then141.i, %if.then60.i, %if.then.i, %lor.lhs.false35, %lor.lhs.false74, %if.end52, %for.body23, %lor.lhs.false68, %lor.lhs.false79
  %indvars.iv.next = add nuw i64 %indvars.iv, 1
  %238 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %neighbors = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %238, i64 %indvars.iv131, i32 2
  %239 = load i32, i32* %neighbors, align 4, !tbaa !14
  %240 = sext i32 %239 to i64
  %cmp22 = icmp slt i64 %indvars.iv.next, %240
  br i1 %cmp22, label %for.body23, label %for.inc89.loopexit

for.inc89.loopexit:                               ; preds = %for.inc
  br label %for.inc89

for.inc89:                                        ; preds = %for.inc89.loopexit, %for.cond19.preheader, %lor.lhs.false, %for.body
  %indvars.iv.next132 = add nuw i64 %indvars.iv131, 1
  %241 = load i32, i32* @number_of_dragons, align 4, !tbaa !1
  %242 = sext i32 %241 to i64
  %cmp = icmp slt i64 %indvars.iv.next132, %242
  br i1 %cmp, label %for.body, label %for.end91.loopexit

for.end91.loopexit:                               ; preds = %for.inc89
  br label %for.end91

for.end91:                                        ; preds = %for.end91.loopexit, %for.cond.preheader
  ret void
}

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start(i64, i8* nocapture) #1

declare i32 @gprintf(i8*, ...) local_unnamed_addr #2

declare i8* @color_to_string(i32) local_unnamed_addr #2

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.end(i64, i8* nocapture) #1

; Function Attrs: nounwind uwtable
define void @new_semeai(i32 %color) local_unnamed_addr #0 {
entry:
  %best_result_a = alloca [10 x i32], align 16
  %best_result_b = alloca [10 x i32], align 16
  %worst_result_a = alloca [10 x i32], align 16
  %worst_result_b = alloca [10 x i32], align 16
  %move = alloca [10 x i32], align 16
  br label %entry.split

entry.split:                                      ; preds = %entry
  %sub = sub nsw i32 3, %color
  %0 = bitcast [10 x i32]* %best_result_a to i8*
  call void @llvm.lifetime.start(i64 40, i8* nonnull %0) #3
  %1 = bitcast [10 x i32]* %best_result_b to i8*
  call void @llvm.lifetime.start(i64 40, i8* nonnull %1) #3
  %2 = bitcast [10 x i32]* %worst_result_a to i8*
  call void @llvm.lifetime.start(i64 40, i8* nonnull %2) #3
  %3 = bitcast [10 x i32]* %worst_result_b to i8*
  call void @llvm.lifetime.start(i64 40, i8* nonnull %3) #3
  %4 = bitcast [10 x i32]* %move to i8*
  call void @llvm.lifetime.start(i64 40, i8* nonnull %4) #3
  %5 = load i32, i32* @verbose, align 4, !tbaa !1
  %tobool = icmp eq i32 %5, 0
  br i1 %tobool, label %for.cond.preheader, label %cond.false

cond.false:                                       ; preds = %entry.split
  %call = tail call i8* @color_to_string(i32 %color) #3
  %call1 = tail call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.1, i64 0, i64 0), i8* %call) #3
  br label %for.cond.preheader

for.cond.preheader:                               ; preds = %entry.split, %cond.false
  %6 = load i32, i32* @number_of_dragons, align 4, !tbaa !1
  %cmp412 = icmp sgt i32 %6, 0
  br i1 %cmp412, label %for.body.preheader, label %for.end285

for.body.preheader:                               ; preds = %for.cond.preheader
  br label %for.body

for.body:                                         ; preds = %for.body.preheader, %cleanup
  %indvars.iv422 = phi i64 [ 0, %for.body.preheader ], [ %indvars.iv.next423, %cleanup ]
  %b_best_status.0418 = phi i32 [ %b_best_status.4, %cleanup ], [ 3, %for.body.preheader ]
  %a_worst_status.0417 = phi i32 [ %a_worst_status.4, %cleanup ], [ 3, %for.body.preheader ]
  %b_worst_status.0416 = phi i32 [ %b_worst_status.5, %cleanup ], [ 3, %for.body.preheader ]
  %a_best_status.0415 = phi i32 [ %a_best_status.5, %cleanup ], [ 3, %for.body.preheader ]
  %apos.0414 = phi i32 [ %apos.4, %cleanup ], [ 0, %for.body.preheader ]
  %bpos.0413 = phi i32 [ %bpos.4, %cleanup ], [ 0, %for.body.preheader ]
  %7 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %origin = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %7, i64 %indvars.iv422, i32 0
  %8 = load i32, i32* %origin, align 4, !tbaa !7
  %idxprom2 = sext i32 %8 to i64
  %color4 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom2, i32 0
  %9 = load i32, i32* %color4, align 4, !tbaa !11
  %cmp5 = icmp eq i32 %9, %color
  br i1 %cmp5, label %lor.lhs.false, label %cleanup

lor.lhs.false:                                    ; preds = %for.body
  %status = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom2, i32 16
  %10 = load i32, i32* %status, align 4, !tbaa !13
  switch i32 %10, label %cleanup [
    i32 0, label %for.cond19.preheader
    i32 2, label %for.cond19.preheader
  ]

for.cond19.preheader:                             ; preds = %lor.lhs.false, %lor.lhs.false
  %11 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %neighbors385 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %11, i64 %indvars.iv422, i32 2
  %12 = load i32, i32* %neighbors385, align 4, !tbaa !14
  %cmp22386 = icmp sgt i32 %12, 0
  br i1 %cmp22386, label %for.body23.lr.ph, label %for.cond33.preheader.preheader

for.body23.lr.ph:                                 ; preds = %for.cond19.preheader
  %13 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %neighbors = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %13, i64 %indvars.iv422, i32 2
  br label %for.body23

for.body23:                                       ; preds = %for.body23.lr.ph, %for.body23
  %indvars.iv = phi i64 [ 0, %for.body23.lr.ph ], [ %indvars.iv.next, %for.body23 ]
  %arrayidx25 = getelementptr inbounds [10 x i32], [10 x i32]* %best_result_a, i64 0, i64 %indvars.iv
  store i32 0, i32* %arrayidx25, align 4, !tbaa !1
  %arrayidx27 = getelementptr inbounds [10 x i32], [10 x i32]* %worst_result_b, i64 0, i64 %indvars.iv
  store i32 1, i32* %arrayidx27, align 4, !tbaa !1
  %arrayidx29 = getelementptr inbounds [10 x i32], [10 x i32]* %move, i64 0, i64 %indvars.iv
  store i32 0, i32* %arrayidx29, align 4, !tbaa !1
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1
  %14 = load i32, i32* %neighbors, align 4, !tbaa !14
  %15 = sext i32 %14 to i64
  %cmp22 = icmp slt i64 %indvars.iv.next, %15
  br i1 %cmp22, label %for.body23, label %for.cond33.preheader.preheader.loopexit

for.cond33.preheader.preheader.loopexit:          ; preds = %for.body23
  br label %for.cond33.preheader.preheader

for.cond33.preheader.preheader:                   ; preds = %for.cond33.preheader.preheader.loopexit, %for.cond19.preheader
  br label %for.cond33.preheader

for.cond33.preheader:                             ; preds = %for.cond33.preheader.preheader, %for.inc280
  %semeai_found.0411 = phi i32 [ %semeai_found.1.lcssa, %for.inc280 ], [ 0, %for.cond33.preheader.preheader ]
  %pass.0410 = phi i32 [ %inc281, %for.inc280 ], [ 0, %for.cond33.preheader.preheader ]
  %b_best_status.1409 = phi i32 [ %b_best_status.2.lcssa, %for.inc280 ], [ %b_best_status.0418, %for.cond33.preheader.preheader ]
  %a_worst_status.1408 = phi i32 [ %a_worst_status.2.lcssa, %for.inc280 ], [ %a_worst_status.0417, %for.cond33.preheader.preheader ]
  %b_worst_status.1407 = phi i32 [ %b_worst_status.2.lcssa, %for.inc280 ], [ %b_worst_status.0416, %for.cond33.preheader.preheader ]
  %a_best_status.1406 = phi i32 [ %a_best_status.2.lcssa, %for.inc280 ], [ %a_best_status.0415, %for.cond33.preheader.preheader ]
  %apos.1405 = phi i32 [ %apos.2.lcssa, %for.inc280 ], [ %apos.0414, %for.cond33.preheader.preheader ]
  %bpos.1404 = phi i32 [ %bpos.2.lcssa, %for.inc280 ], [ %bpos.0413, %for.cond33.preheader.preheader ]
  %16 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %neighbors36388 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %16, i64 %indvars.iv422, i32 2
  %17 = load i32, i32* %neighbors36388, align 4, !tbaa !14
  %cmp37389 = icmp sgt i32 %17, 0
  br i1 %cmp37389, label %for.body38.lr.ph, label %for.end254

for.body38.lr.ph:                                 ; preds = %for.cond33.preheader
  %cmp158 = icmp eq i32 %pass.0410, 0
  br label %for.body38

for.body38:                                       ; preds = %for.body38.lr.ph, %for.inc252
  %indvars.iv420 = phi i64 [ 0, %for.body38.lr.ph ], [ %indvars.iv.next421, %for.inc252 ]
  %18 = phi %struct.dragon_data2* [ %16, %for.body38.lr.ph ], [ %55, %for.inc252 ]
  %semeai_found.1397 = phi i32 [ %semeai_found.0411, %for.body38.lr.ph ], [ %semeai_found.2, %for.inc252 ]
  %b_best_status.2395 = phi i32 [ %b_best_status.1409, %for.body38.lr.ph ], [ %b_best_status.3, %for.inc252 ]
  %a_worst_status.2394 = phi i32 [ %a_worst_status.1408, %for.body38.lr.ph ], [ %a_worst_status.3, %for.inc252 ]
  %b_worst_status.2393 = phi i32 [ %b_worst_status.1407, %for.body38.lr.ph ], [ %b_worst_status.4, %for.inc252 ]
  %a_best_status.2392 = phi i32 [ %a_best_status.1406, %for.body38.lr.ph ], [ %a_best_status.4, %for.inc252 ]
  %apos.2391 = phi i32 [ %apos.1405, %for.body38.lr.ph ], [ %apos.3, %for.inc252 ]
  %bpos.2390 = phi i32 [ %bpos.1404, %for.body38.lr.ph ], [ %bpos.3, %for.inc252 ]
  %arrayidx42 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %18, i64 %indvars.iv422, i32 1, i64 %indvars.iv420
  %19 = load i32, i32* %arrayidx42, align 4, !tbaa !1
  %idxprom43 = sext i32 %19 to i64
  %origin45 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %18, i64 %idxprom43, i32 0
  %20 = load i32, i32* %origin45, align 4, !tbaa !7
  %idxprom46 = sext i32 %20 to i64
  %color48 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom46, i32 0
  %21 = load i32, i32* %color48, align 4, !tbaa !11
  %cmp49 = icmp eq i32 %21, %sub
  br i1 %cmp49, label %lor.lhs.false50, label %for.inc252

lor.lhs.false50:                                  ; preds = %for.body38
  %status56 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom46, i32 16
  %22 = load i32, i32* %status56, align 4, !tbaa !13
  switch i32 %22, label %for.inc252 [
    i32 0, label %if.end67
    i32 2, label %if.end67
  ]

if.end67:                                         ; preds = %lor.lhs.false50, %lor.lhs.false50
  %origin70 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %18, i64 %indvars.iv422, i32 0
  %23 = load i32, i32* %origin70, align 4, !tbaa !7
  %idxprom71 = sext i32 %23 to i64
  %origin73 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom71, i32 2
  %24 = load i32, i32* %origin73, align 4, !tbaa !15
  %origin79 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom46, i32 2
  %25 = load i32, i32* %origin79, align 4, !tbaa !15
  %idxprom80 = sext i32 %24 to i64
  %inessential = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom80, i32 12
  %26 = load i32, i32* %inessential, align 4, !tbaa !16
  %tobool82 = icmp eq i32 %26, 0
  br i1 %tobool82, label %lor.lhs.false83, label %for.inc252

lor.lhs.false83:                                  ; preds = %if.end67
  %id = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom80, i32 1
  %27 = load i32, i32* %id, align 4, !tbaa !18
  %idxprom86 = sext i32 %27 to i64
  %safety = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %18, i64 %idxprom86, i32 6
  %28 = load i32, i32* %safety, align 4, !tbaa !19
  %cmp88 = icmp eq i32 %28, 5
  br i1 %cmp88, label %for.inc252, label %lor.lhs.false89

lor.lhs.false89:                                  ; preds = %lor.lhs.false83
  %idxprom90 = sext i32 %25 to i64
  %inessential92 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom90, i32 12
  %29 = load i32, i32* %inessential92, align 4, !tbaa !16
  %tobool93 = icmp eq i32 %29, 0
  br i1 %tobool93, label %lor.lhs.false94, label %for.inc252

lor.lhs.false94:                                  ; preds = %lor.lhs.false89
  %id97 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom90, i32 1
  %30 = load i32, i32* %id97, align 4, !tbaa !18
  %idxprom98 = sext i32 %30 to i64
  %safety100 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %18, i64 %idxprom98, i32 6
  %31 = load i32, i32* %safety100, align 4, !tbaa !19
  %cmp101 = icmp eq i32 %31, 5
  br i1 %cmp101, label %for.inc252, label %if.end103

if.end103:                                        ; preds = %lor.lhs.false94
  %size = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom80, i32 3
  %32 = load i32, i32* %size, align 4, !tbaa !27
  %size108 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom80, i32 1
  %33 = load i32, i32* %size108, align 4, !tbaa !28
  %cmp109 = icmp eq i32 %32, %33
  br i1 %cmp109, label %land.lhs.true110, label %if.end123

land.lhs.true110:                                 ; preds = %if.end103
  %arrayidx113 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom80, i32 16, i64 0
  %34 = load i32, i32* %arrayidx113, align 4, !tbaa !1
  %cmp114 = icmp eq i32 %34, 5
  br i1 %cmp114, label %land.lhs.true115, label %if.end123

land.lhs.true115:                                 ; preds = %land.lhs.true110
  %hostile_neighbors = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %18, i64 %idxprom86, i32 3
  %35 = load i32, i32* %hostile_neighbors, align 4, !tbaa !29
  %cmp121 = icmp eq i32 %35, 1
  br i1 %cmp121, label %for.inc252, label %if.end123

if.end123:                                        ; preds = %land.lhs.true115, %land.lhs.true110, %if.end103
  %size126 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom90, i32 3
  %36 = load i32, i32* %size126, align 4, !tbaa !27
  %size129 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom90, i32 1
  %37 = load i32, i32* %size129, align 4, !tbaa !28
  %cmp130 = icmp eq i32 %36, %37
  br i1 %cmp130, label %land.lhs.true131, label %if.end146

land.lhs.true131:                                 ; preds = %if.end123
  %arrayidx135 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom90, i32 16, i64 0
  %38 = load i32, i32* %arrayidx135, align 4, !tbaa !1
  %cmp136 = icmp eq i32 %38, 5
  br i1 %cmp136, label %land.lhs.true137, label %if.end146

land.lhs.true137:                                 ; preds = %land.lhs.true131
  %39 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %40 = load i32, i32* %id97, align 4, !tbaa !18
  %idxprom141 = sext i32 %40 to i64
  %hostile_neighbors143 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %39, i64 %idxprom141, i32 3
  %41 = load i32, i32* %hostile_neighbors143, align 4, !tbaa !29
  %cmp144 = icmp eq i32 %41, 1
  br i1 %cmp144, label %for.inc252, label %if.end146

if.end146:                                        ; preds = %land.lhs.true137, %land.lhs.true131, %if.end123
  %42 = load i32, i32* %size, align 4, !tbaa !27
  %cmp150 = icmp eq i32 %42, 1
  %cmp155 = icmp eq i32 %36, 1
  %or.cond = or i1 %cmp155, %cmp150
  br i1 %or.cond, label %for.inc252, label %if.end157

if.end157:                                        ; preds = %if.end146
  br i1 %cmp158, label %if.then159, label %for.inc252

if.then159:                                       ; preds = %if.end157
  %43 = load i32, i32* @debug, align 4, !tbaa !1
  %and = and i32 %43, 64
  %tobool160 = icmp eq i32 %and, 0
  br i1 %tobool160, label %cond.end164, label %cond.false162

cond.false162:                                    ; preds = %if.then159
  %call163 = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.2, i64 0, i64 0), i32 %24, i32 %25) #3
  br label %cond.end164

cond.end164:                                      ; preds = %if.then159, %cond.false162
  %add.ptr = getelementptr inbounds [10 x i32], [10 x i32]* %best_result_a, i64 0, i64 %indvars.iv420
  %add.ptr167 = getelementptr inbounds [10 x i32], [10 x i32]* %worst_result_b, i64 0, i64 %indvars.iv420
  %add.ptr170 = getelementptr inbounds [10 x i32], [10 x i32]* %move, i64 0, i64 %indvars.iv420
  call void @owl_analyze_semeai(i32 %24, i32 %25, i32* %add.ptr, i32* %add.ptr167, i32* %add.ptr170, i32 1) #3
  %44 = load i32, i32* @debug, align 4, !tbaa !1
  %and171 = and i32 %44, 64
  %tobool172 = icmp eq i32 %and171, 0
  br i1 %tobool172, label %if.then194, label %cond.false174

cond.false174:                                    ; preds = %cond.end164
  %45 = load i32, i32* %add.ptr, align 4, !tbaa !1
  %call177 = call i8* @safety_to_string(i32 %45) #3
  %46 = load i32, i32* %add.ptr167, align 4, !tbaa !1
  %call180 = call i8* @safety_to_string(i32 %46) #3
  %47 = load i32, i32* %add.ptr170, align 4, !tbaa !1
  %call183 = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.3, i64 0, i64 0), i8* %call177, i8* %call180, i32 %47) #3
  br label %if.then194

if.then194:                                       ; preds = %cond.false174, %cond.end164
  %48 = load i32, i32* %add.ptr, align 4, !tbaa !1
  %49 = load i32, i32* %add.ptr167, align 4, !tbaa !1
  %add.ptr202 = getelementptr inbounds [10 x i32], [10 x i32]* %best_result_b, i64 0, i64 %indvars.iv420
  %add.ptr205 = getelementptr inbounds [10 x i32], [10 x i32]* %worst_result_a, i64 0, i64 %indvars.iv420
  call void @owl_analyze_semeai(i32 %25, i32 %24, i32* %add.ptr202, i32* %add.ptr205, i32* null, i32 1) #3
  %50 = load i32, i32* @debug, align 4, !tbaa !1
  %and206 = and i32 %50, 64
  %tobool207 = icmp eq i32 %and206, 0
  br i1 %tobool207, label %if.then227, label %cond.false209

cond.false209:                                    ; preds = %if.then194
  %51 = load i32, i32* %add.ptr202, align 4, !tbaa !1
  %call212 = call i8* @safety_to_string(i32 %51) #3
  %52 = load i32, i32* %add.ptr205, align 4, !tbaa !1
  %call215 = call i8* @safety_to_string(i32 %52) #3
  %call216 = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.4, i64 0, i64 0), i8* %call212, i8* %call215) #3
  br label %if.then227

if.then227:                                       ; preds = %cond.false209, %if.then194
  %53 = load i32, i32* %add.ptr202, align 4, !tbaa !1
  %54 = load i32, i32* %add.ptr205, align 4, !tbaa !1
  br label %for.inc252

for.inc252:                                       ; preds = %if.end157, %lor.lhs.false50, %lor.lhs.false89, %if.end67, %for.body38, %if.then227, %if.end146, %land.lhs.true137, %land.lhs.true115, %lor.lhs.false83, %lor.lhs.false94
  %bpos.3 = phi i32 [ %bpos.2390, %for.body38 ], [ %25, %if.end67 ], [ %25, %lor.lhs.false83 ], [ %25, %lor.lhs.false89 ], [ %25, %lor.lhs.false94 ], [ %25, %land.lhs.true115 ], [ %25, %land.lhs.true137 ], [ %25, %if.end146 ], [ %25, %if.then227 ], [ %bpos.2390, %lor.lhs.false50 ], [ %25, %if.end157 ]
  %apos.3 = phi i32 [ %apos.2391, %for.body38 ], [ %24, %if.end67 ], [ %24, %lor.lhs.false83 ], [ %24, %lor.lhs.false89 ], [ %24, %lor.lhs.false94 ], [ %24, %land.lhs.true115 ], [ %24, %land.lhs.true137 ], [ %24, %if.end146 ], [ %24, %if.then227 ], [ %apos.2391, %lor.lhs.false50 ], [ %24, %if.end157 ]
  %a_best_status.4 = phi i32 [ %a_best_status.2392, %for.body38 ], [ %a_best_status.2392, %if.end67 ], [ %a_best_status.2392, %lor.lhs.false83 ], [ %a_best_status.2392, %lor.lhs.false89 ], [ %a_best_status.2392, %lor.lhs.false94 ], [ %a_best_status.2392, %land.lhs.true115 ], [ %a_best_status.2392, %land.lhs.true137 ], [ %a_best_status.2392, %if.end146 ], [ %48, %if.then227 ], [ %a_best_status.2392, %lor.lhs.false50 ], [ 3, %if.end157 ]
  %b_worst_status.4 = phi i32 [ %b_worst_status.2393, %for.body38 ], [ %b_worst_status.2393, %if.end67 ], [ %b_worst_status.2393, %lor.lhs.false83 ], [ %b_worst_status.2393, %lor.lhs.false89 ], [ %b_worst_status.2393, %lor.lhs.false94 ], [ %b_worst_status.2393, %land.lhs.true115 ], [ %b_worst_status.2393, %land.lhs.true137 ], [ %b_worst_status.2393, %if.end146 ], [ %49, %if.then227 ], [ %b_worst_status.2393, %lor.lhs.false50 ], [ 3, %if.end157 ]
  %a_worst_status.3 = phi i32 [ %a_worst_status.2394, %for.body38 ], [ %a_worst_status.2394, %if.end67 ], [ %a_worst_status.2394, %lor.lhs.false83 ], [ %a_worst_status.2394, %lor.lhs.false89 ], [ %a_worst_status.2394, %lor.lhs.false94 ], [ %a_worst_status.2394, %land.lhs.true115 ], [ %a_worst_status.2394, %land.lhs.true137 ], [ %a_worst_status.2394, %if.end146 ], [ %54, %if.then227 ], [ %a_worst_status.2394, %lor.lhs.false50 ], [ 3, %if.end157 ]
  %b_best_status.3 = phi i32 [ %b_best_status.2395, %for.body38 ], [ %b_best_status.2395, %if.end67 ], [ %b_best_status.2395, %lor.lhs.false83 ], [ %b_best_status.2395, %lor.lhs.false89 ], [ %b_best_status.2395, %lor.lhs.false94 ], [ %b_best_status.2395, %land.lhs.true115 ], [ %b_best_status.2395, %land.lhs.true137 ], [ %b_best_status.2395, %if.end146 ], [ %53, %if.then227 ], [ %b_best_status.2395, %lor.lhs.false50 ], [ 3, %if.end157 ]
  %semeai_found.2 = phi i32 [ %semeai_found.1397, %for.body38 ], [ %semeai_found.1397, %if.end67 ], [ %semeai_found.1397, %lor.lhs.false83 ], [ %semeai_found.1397, %lor.lhs.false89 ], [ %semeai_found.1397, %lor.lhs.false94 ], [ %semeai_found.1397, %land.lhs.true115 ], [ %semeai_found.1397, %land.lhs.true137 ], [ %semeai_found.1397, %if.end146 ], [ 1, %if.then227 ], [ %semeai_found.1397, %lor.lhs.false50 ], [ 1, %if.end157 ]
  %indvars.iv.next421 = add nuw i64 %indvars.iv420, 1
  %55 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %neighbors36 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %55, i64 %indvars.iv422, i32 2
  %56 = load i32, i32* %neighbors36, align 4, !tbaa !14
  %57 = sext i32 %56 to i64
  %cmp37 = icmp slt i64 %indvars.iv.next421, %57
  br i1 %cmp37, label %for.body38, label %for.end254.loopexit

for.end254.loopexit:                              ; preds = %for.inc252
  %bpos.3.lcssa = phi i32 [ %bpos.3, %for.inc252 ]
  %apos.3.lcssa = phi i32 [ %apos.3, %for.inc252 ]
  %a_best_status.4.lcssa = phi i32 [ %a_best_status.4, %for.inc252 ]
  %b_worst_status.4.lcssa = phi i32 [ %b_worst_status.4, %for.inc252 ]
  %a_worst_status.3.lcssa = phi i32 [ %a_worst_status.3, %for.inc252 ]
  %b_best_status.3.lcssa = phi i32 [ %b_best_status.3, %for.inc252 ]
  %semeai_found.2.lcssa = phi i32 [ %semeai_found.2, %for.inc252 ]
  br label %for.end254

for.end254:                                       ; preds = %for.end254.loopexit, %for.cond33.preheader
  %bpos.2.lcssa = phi i32 [ %bpos.1404, %for.cond33.preheader ], [ %bpos.3.lcssa, %for.end254.loopexit ]
  %apos.2.lcssa = phi i32 [ %apos.1405, %for.cond33.preheader ], [ %apos.3.lcssa, %for.end254.loopexit ]
  %a_best_status.2.lcssa = phi i32 [ %a_best_status.1406, %for.cond33.preheader ], [ %a_best_status.4.lcssa, %for.end254.loopexit ]
  %b_worst_status.2.lcssa = phi i32 [ %b_worst_status.1407, %for.cond33.preheader ], [ %b_worst_status.4.lcssa, %for.end254.loopexit ]
  %a_worst_status.2.lcssa = phi i32 [ %a_worst_status.1408, %for.cond33.preheader ], [ %a_worst_status.3.lcssa, %for.end254.loopexit ]
  %b_best_status.2.lcssa = phi i32 [ %b_best_status.1409, %for.cond33.preheader ], [ %b_best_status.3.lcssa, %for.end254.loopexit ]
  %semeai_found.1.lcssa = phi i32 [ %semeai_found.0411, %for.cond33.preheader ], [ %semeai_found.2.lcssa, %for.end254.loopexit ]
  %cmp255 = icmp eq i32 %pass.0410, 0
  %tobool257 = icmp ne i32 %semeai_found.1.lcssa, 0
  %or.cond287 = and i1 %cmp255, %tobool257
  br i1 %or.cond287, label %if.then258, label %for.inc280

if.then258:                                       ; preds = %for.end254
  %cmp261 = icmp ne i32 %a_best_status.2.lcssa, 0
  %cmp263 = icmp eq i32 %a_worst_status.2.lcssa, 0
  %or.cond288 = and i1 %cmp261, %cmp263
  %.a_worst_status.2 = select i1 %or.cond288, i32 2, i32 %a_worst_status.2.lcssa
  %cmp267 = icmp ne i32 %b_best_status.2.lcssa, 0
  %cmp269 = icmp eq i32 %b_worst_status.2.lcssa, 0
  %or.cond289 = and i1 %cmp269, %cmp267
  %b_status260.0 = select i1 %or.cond289, i32 2, i32 %b_worst_status.2.lcssa
  %cmp273 = icmp eq i32 %.a_worst_status.2, 7
  %..a_worst_status.2 = select i1 %cmp273, i32 1, i32 %.a_worst_status.2
  %cmp276 = icmp eq i32 %b_status260.0, 7
  %b_status260.1 = select i1 %cmp276, i32 1, i32 %b_status260.0
  call fastcc void @update_status(i32 %apos.2.lcssa, i32 %..a_worst_status.2, i32 %..a_worst_status.2)
  call fastcc void @update_status(i32 %bpos.2.lcssa, i32 %b_status260.1, i32 %b_status260.1)
  br label %for.inc280

for.inc280:                                       ; preds = %for.end254, %if.then258
  %inc281 = add nuw nsw i32 %pass.0410, 1
  %exitcond = icmp ne i32 %inc281, 2
  br i1 %exitcond, label %for.cond33.preheader, label %cleanup.loopexit

cleanup.loopexit:                                 ; preds = %for.inc280
  %bpos.2.lcssa.lcssa = phi i32 [ %bpos.2.lcssa, %for.inc280 ]
  %apos.2.lcssa.lcssa = phi i32 [ %apos.2.lcssa, %for.inc280 ]
  %a_best_status.2.lcssa.lcssa = phi i32 [ %a_best_status.2.lcssa, %for.inc280 ]
  %b_worst_status.2.lcssa.lcssa = phi i32 [ %b_worst_status.2.lcssa, %for.inc280 ]
  %a_worst_status.2.lcssa.lcssa = phi i32 [ %a_worst_status.2.lcssa, %for.inc280 ]
  %b_best_status.2.lcssa.lcssa = phi i32 [ %b_best_status.2.lcssa, %for.inc280 ]
  br label %cleanup

cleanup:                                          ; preds = %cleanup.loopexit, %for.body, %lor.lhs.false
  %bpos.4 = phi i32 [ %bpos.0413, %lor.lhs.false ], [ %bpos.0413, %for.body ], [ %bpos.2.lcssa.lcssa, %cleanup.loopexit ]
  %apos.4 = phi i32 [ %apos.0414, %lor.lhs.false ], [ %apos.0414, %for.body ], [ %apos.2.lcssa.lcssa, %cleanup.loopexit ]
  %a_best_status.5 = phi i32 [ %a_best_status.0415, %lor.lhs.false ], [ %a_best_status.0415, %for.body ], [ %a_best_status.2.lcssa.lcssa, %cleanup.loopexit ]
  %b_worst_status.5 = phi i32 [ %b_worst_status.0416, %lor.lhs.false ], [ %b_worst_status.0416, %for.body ], [ %b_worst_status.2.lcssa.lcssa, %cleanup.loopexit ]
  %a_worst_status.4 = phi i32 [ %a_worst_status.0417, %lor.lhs.false ], [ %a_worst_status.0417, %for.body ], [ %a_worst_status.2.lcssa.lcssa, %cleanup.loopexit ]
  %b_best_status.4 = phi i32 [ %b_best_status.0418, %lor.lhs.false ], [ %b_best_status.0418, %for.body ], [ %b_best_status.2.lcssa.lcssa, %cleanup.loopexit ]
  %indvars.iv.next423 = add nuw i64 %indvars.iv422, 1
  %58 = load i32, i32* @number_of_dragons, align 4, !tbaa !1
  %59 = sext i32 %58 to i64
  %cmp = icmp slt i64 %indvars.iv.next423, %59
  br i1 %cmp, label %for.body, label %for.end285.loopexit

for.end285.loopexit:                              ; preds = %cleanup
  br label %for.end285

for.end285:                                       ; preds = %for.end285.loopexit, %for.cond.preheader
  call void @llvm.lifetime.end(i64 40, i8* nonnull %4) #3
  call void @llvm.lifetime.end(i64 40, i8* nonnull %3) #3
  call void @llvm.lifetime.end(i64 40, i8* nonnull %2) #3
  call void @llvm.lifetime.end(i64 40, i8* nonnull %1) #3
  call void @llvm.lifetime.end(i64 40, i8* nonnull %0) #3
  ret void
}

declare void @owl_analyze_semeai(i32, i32, i32*, i32*, i32*, i32) local_unnamed_addr #2

declare i8* @safety_to_string(i32) local_unnamed_addr #2

declare void @add_owl_defense_move(i32, i32, i32) local_unnamed_addr #2

declare void @add_owl_attack_move(i32, i32, i32) local_unnamed_addr #2

; Function Attrs: nounwind uwtable
define internal fastcc void @update_status(i32 %dr, i32 %new_status, i32 %new_safety) unnamed_addr #0 {
entry:
  br label %entry.split

entry.split:                                      ; preds = %entry
  %idxprom = sext i32 %dr to i64
  %status = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom, i32 16
  %0 = load i32, i32* %status, align 4, !tbaa !13
  %cmp = icmp eq i32 %0, %new_status
  br i1 %cmp, label %if.end29, label %land.lhs.true

land.lhs.true:                                    ; preds = %entry.split
  %cmp4 = icmp ne i32 %0, 2
  %cmp5 = icmp ne i32 %new_status, 0
  %or.cond = or i1 %cmp5, %cmp4
  br i1 %or.cond, label %if.then, label %if.end29

if.then:                                          ; preds = %land.lhs.true
  %1 = load i32, i32* @debug, align 4, !tbaa !1
  %and = and i32 %1, 64
  %tobool = icmp eq i32 %and, 0
  br i1 %tobool, label %for.body.preheader, label %cond.false

cond.false:                                       ; preds = %if.then
  %call = tail call i8* @status_to_string(i32 %0) #3
  %call9 = tail call i8* @status_to_string(i32 %new_status) #3
  %call10 = tail call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.5, i64 0, i64 0), i32 %dr, i8* %call, i8* %call9) #3
  br label %for.body.preheader

for.body.preheader:                               ; preds = %if.then, %cond.false
  br label %for.body

for.body:                                         ; preds = %for.body.preheader, %for.inc
  %indvars.iv = phi i64 [ 21, %for.body.preheader ], [ %indvars.iv.next, %for.inc ]
  %arrayidx13 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %indvars.iv
  %2 = load i8, i8* %arrayidx13, align 1, !tbaa !20
  %.off = add i8 %2, -1
  %switch = icmp ult i8 %.off, 2
  br i1 %switch, label %land.lhs.true22, label %for.inc

land.lhs.true22:                                  ; preds = %for.body
  %3 = trunc i64 %indvars.iv to i32
  %call23 = tail call i32 @is_same_dragon(i32 %dr, i32 %3) #3
  %tobool24 = icmp eq i32 %call23, 0
  br i1 %tobool24, label %for.inc, label %if.then25

if.then25:                                        ; preds = %land.lhs.true22
  %status28 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %indvars.iv, i32 16
  store i32 %new_status, i32* %status28, align 4, !tbaa !13
  br label %for.inc

for.inc:                                          ; preds = %for.body, %land.lhs.true22, %if.then25
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1
  %exitcond = icmp ne i64 %indvars.iv.next, 400
  br i1 %exitcond, label %for.body, label %if.end29.loopexit

if.end29.loopexit:                                ; preds = %for.inc
  br label %if.end29

if.end29:                                         ; preds = %if.end29.loopexit, %entry.split, %land.lhs.true
  %4 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %id = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom, i32 1
  %5 = load i32, i32* %id, align 4, !tbaa !18
  %idxprom32 = sext i32 %5 to i64
  %safety = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %4, i64 %idxprom32, i32 6
  %6 = load i32, i32* %safety, align 4, !tbaa !19
  %cmp34 = icmp eq i32 %6, %new_safety
  br i1 %cmp34, label %if.end69, label %land.lhs.true36

land.lhs.true36:                                  ; preds = %if.end29
  %cmp43 = icmp ne i32 %6, 2
  %cmp46 = icmp ne i32 %new_safety, 0
  %or.cond70 = or i1 %cmp46, %cmp43
  br i1 %or.cond70, label %if.then48, label %if.end69

if.then48:                                        ; preds = %land.lhs.true36
  %7 = load i32, i32* @debug, align 4, !tbaa !1
  %and49 = and i32 %7, 64
  %tobool50 = icmp eq i32 %and49, 0
  br i1 %tobool50, label %cond.end62, label %cond.false52

cond.false52:                                     ; preds = %if.then48
  %call59 = tail call i8* @safety_to_string(i32 %6) #3
  %call60 = tail call i8* @safety_to_string(i32 %new_safety) #3
  %call61 = tail call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.6, i64 0, i64 0), i32 %dr, i8* %call59, i8* %call60) #3
  br label %cond.end62

cond.end62:                                       ; preds = %if.then48, %cond.false52
  %8 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8, !tbaa !5
  %9 = load i32, i32* %id, align 4, !tbaa !18
  %idxprom66 = sext i32 %9 to i64
  %safety68 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %8, i64 %idxprom66, i32 6
  store i32 %new_safety, i32* %safety68, align 4, !tbaa !19
  br label %if.end69

if.end69:                                         ; preds = %if.end29, %land.lhs.true36, %cond.end62
  ret void
}

declare i8* @status_to_string(i32) local_unnamed_addr #2

declare i32 @is_same_dragon(i32, i32) local_unnamed_addr #2

declare i32 @owl_does_attack(i32, i32, i32*) local_unnamed_addr #2

declare i32 @owl_does_defend(i32, i32, i32*) local_unnamed_addr #2

declare i32 @chainlinks(i32, i32*) local_unnamed_addr #2

declare i32 @owl_substantial(i32) local_unnamed_addr #2

declare i32 @liberty_of_string(i32, i32) local_unnamed_addr #2

declare i32 @min_eyes(%struct.eyevalue*) local_unnamed_addr #2

declare i32 @eye_move_urgency(%struct.eyevalue*) local_unnamed_addr #2

declare i32 @safe_move(i32, i32) local_unnamed_addr #2

declare void @add_semeai_move(i32, i32) local_unnamed_addr #2

declare void @add_semeai_threat(i32, i32) local_unnamed_addr #2

attributes #0 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 5.0.0 "}
!1 = !{!2, !2, i64 0}
!2 = !{!"int", !3, i64 0}
!3 = !{!"omnipotent char", !4, i64 0}
!4 = !{!"Simple C/C++ TBAA"}
!5 = !{!6, !6, i64 0}
!6 = !{!"any pointer", !3, i64 0}
!7 = !{!8, !2, i64 0}
!8 = !{!"dragon_data2", !2, i64 0, !3, i64 4, !2, i64 44, !2, i64 48, !2, i64 52, !9, i64 56, !2, i64 60, !9, i64 64, !9, i64 68, !2, i64 72, !10, i64 76, !2, i64 80, !2, i64 84, !2, i64 88, !2, i64 92, !2, i64 96, !2, i64 100}
!9 = !{!"float", !3, i64 0}
!10 = !{!"eyevalue", !3, i64 0, !3, i64 1, !3, i64 2, !3, i64 3}
!11 = !{!12, !2, i64 0}
!12 = !{!"dragon_data", !2, i64 0, !2, i64 4, !2, i64 8, !2, i64 12, !9, i64 16, !2, i64 20, !2, i64 24, !2, i64 28, !2, i64 32, !2, i64 36, !2, i64 40, !2, i64 44, !2, i64 48, !2, i64 52, !2, i64 56, !2, i64 60, !2, i64 64, !2, i64 68, !2, i64 72}
!13 = !{!12, !2, i64 64}
!14 = !{!8, !2, i64 44}
!15 = !{!12, !2, i64 8}
!16 = !{!17, !2, i64 48}
!17 = !{!"worm_data", !2, i64 0, !2, i64 4, !9, i64 8, !2, i64 12, !2, i64 16, !2, i64 20, !2, i64 24, !2, i64 28, !2, i64 32, !2, i64 36, !2, i64 40, !2, i64 44, !2, i64 48, !2, i64 52, !2, i64 56, !3, i64 60, !3, i64 100, !3, i64 140, !3, i64 180, !3, i64 220, !3, i64 260, !3, i64 300, !3, i64 340}
!18 = !{!12, !2, i64 4}
!19 = !{!8, !2, i64 60}
!20 = !{!3, !3, i64 0}
!21 = !{!12, !2, i64 28}
!22 = !{!12, !2, i64 32}
!23 = !{!12, !2, i64 48}
!24 = !{!17, !2, i64 12}
!25 = !{!8, !2, i64 88}
!26 = !{!8, !2, i64 80}
!27 = !{!12, !2, i64 12}
!28 = !{!17, !2, i64 4}
!29 = !{!8, !2, i64 48}
