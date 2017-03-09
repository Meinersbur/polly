; RUN: opt %loadPolly -polly-enable-known -polly-enable-delicm -polly-enable-simplify -polly-enable-late-prune -polly-delicm-partial-writes -polly-delicm-compute-phi -polly-codegen-virtual-statements -polly-position=after-loopopt -tti -targetlibinfo -tbaa -scoped-noalias -assumption-cache-tracker -verify -simplifycfg -domtree -sroa -early-cse -basicaa -aa -memdep -memoryssa -gvn-hoist -lower-expect -barrier -tti -targetlibinfo -tbaa -scoped-noalias -assumption-cache-tracker -profile-summary-info -forceattrs -inferattrs -ipsccp -globalopt -domtree -mem2reg -deadargelim -domtree -basicaa -aa -instcombine -simplifycfg -pgo-icall-prom -basiccg -globals-aa -prune-eh -inline -functionattrs -argpromotion -domtree -sroa -early-cse -lazy-value-info -jump-threading -correlated-propagation -simplifycfg -domtree -basicaa -aa -instcombine -libcalls-shrinkwrap -tailcallelim -simplifycfg -reassociate -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -loop-rotate -licm -loop-unswitch -simplifycfg -domtree -basicaa -aa -instcombine -loops -loop-simplify -lcssa-verification -lcssa -scalar-evolution -indvars -loop-idiom -loop-deletion -loop-unroll -polly-prepare -scalar-evolution -basicaa -aa -postdomtree -domfrontier -regions -polly-detect -polly-scops -polly-known -polly-delicm -polly-simplify -polly-unprofitable -polly-dependences -polly-opt-isl -polly-ast -polly-codegen -barrier -polly-cleanup -domtree -basicaa -aa -mldst-motion -aa -memdep -loops -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -gvn -basicaa -aa -memdep -memcpyopt -sccp -domtree -demanded-bits -bdce -basicaa -aa -instcombine -lazy-value-info -jump-threading -correlated-propagation -domtree -basicaa -aa -memdep -dse -loops -loop-simplify -lcssa-verification -lcssa -aa -scalar-evolution -licm -postdomtree -adce -simplifycfg -domtree -basicaa -aa -instcombine -barrier -elim-avail-extern -basiccg -rpo-functionattrs -globals-aa -float2int -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -loop-rotate -loop-accesses -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -loop-distribute -branch-prob -block-freq -scalar-evolution -basicaa -aa -loop-accesses -demanded-bits -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -loop-vectorize -loop-simplify -scalar-evolution -aa -loop-accesses -loop-load-elim -basicaa -aa -instcombine -scalar-evolution -demanded-bits -slp-vectorizer -simplifycfg -domtree -basicaa -aa -instcombine -loops -loop-simplify -lcssa-verification -lcssa -scalar-evolution -loop-unroll -instcombine -loop-simplify -lcssa-verification -lcssa -scalar-evolution -licm -alignment-from-assumptions -strip-dead-prototypes -globaldce -constmerge -domtree -loops -branch-prob -block-freq -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -branch-prob -block-freq -loop-sink -lazy-branch-prob -lazy-block-freq -opt-remark-emitter -instsimplify -barrier -domtree -barrier -scoped-noalias -tbaa -assumption-cache-tracker -targetlibinfo -tti -domtree -basicaa -aa -simplifycfg -domtree -sroa -early-cse -basicaa -aa -instcombine -lazy-value-info -jump-threading -correlated-propagation -simplifycfg -domtree -basicaa -aa -instcombine -simplifycfg -reassociate -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -loop-rotate -licm -loop-unswitch -simplifycfg -domtree -basicaa -aa -instcombine -loops -loop-simplify -lcssa-verification -lcssa -scalar-evolution -indvars -loop-idiom -loop-deletion -simplifycfg -domtree -loops -loop-simplify -lcssa-verification -lcssa -basicaa -aa -scalar-evolution -loop-unroll -mldst-motion -aa -memdep -memcpyopt -demanded-bits -bdce -aa -instcombine -lazy-value-info -jump-threading -correlated-propagation -domtree -basicaa -aa -memdep -dse -loops -loop-simplify -lcssa-verification -lcssa -aa -scalar-evolution -licm -loop-reroll -postdomtree -adce -simplifycfg -domtree -basicaa -aa -instcombine -barrier -S < %s
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

@verbose = external global i32, align 4
@.str = private unnamed_addr constant [35 x i8] c"Semeai Player is THINKING for %s!\0A\00", align 1
@number_of_dragons = external global i32, align 4
@dragon = external global [400 x %struct.dragon_data], align 16
@dragon2 = external global %struct.dragon_data2*, align 8
@worm = external global [400 x %struct.worm_data], align 16
@.str.1 = private unnamed_addr constant [48 x i8] c"Experimental Semeai Module is THINKING for %s!\0A\00", align 1
@debug = external global i32, align 4
@.str.2 = private unnamed_addr constant [40 x i8] c"Considering semeai between %1m and %1m\0A\00", align 1
@.str.3 = private unnamed_addr constant [21 x i8] c"Result1: %s %s %1m, \00", align 1
@.str.4 = private unnamed_addr constant [16 x i8] c"Result2 %s %s.\0A\00", align 1
@.str.5 = private unnamed_addr constant [39 x i8] c"Changing status of %1m from %s to %s.\0A\00", align 1
@board = external global [421 x i8], align 16
@.str.6 = private unnamed_addr constant [39 x i8] c"Changing safety of %1m from %s to %s.\0A\00", align 1
@.str.7 = private unnamed_addr constant [41 x i8] c"semeai_analyzer: %1m (me) vs %1m (them)\0A\00", align 1
@.str.8 = private unnamed_addr constant [45 x i8] c"added owl attack of %1m at %1m with code %d\0A\00", align 1
@.str.9 = private unnamed_addr constant [46 x i8] c"added owl defense of %1m at %1m with code %d\0A\00", align 1
@.str.10 = private unnamed_addr constant [50 x i8] c"changed owl_status and status of %1m to CRITICAL\0A\00", align 1
@.str.11 = private unnamed_addr constant [51 x i8] c"...owl code sufficient to resolve semeai, exiting\0A\00", align 1
@.str.12 = private unnamed_addr constant [41 x i8] c"...tactical situation detected, exiting\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define void @semeai(i32 %color) #0 {
entry:
  %color.addr = alloca i32, align 4
  %d1 = alloca i32, align 4
  %d2 = alloca i32, align 4
  %k = alloca i32, align 4
  %apos = alloca i32, align 4
  %bpos = alloca i32, align 4
  %other = alloca i32, align 4
  store i32 %color, i32* %color.addr, align 4
  store i32 0, i32* %apos, align 4
  store i32 0, i32* %bpos, align 4
  %0 = load i32, i32* %color.addr, align 4
  %sub = sub nsw i32 3, %0
  store i32 %sub, i32* %other, align 4
  %1 = load i32, i32* @verbose, align 4
  %tobool = icmp ne i32 %1, 0
  br i1 %tobool, label %cond.false, label %cond.true

cond.true:                                        ; preds = %entry
  br label %cond.end

cond.false:                                       ; preds = %entry
  %2 = load i32, i32* %color.addr, align 4
  %call = call i8* @color_to_string(i32 %2)
  %call1 = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str, i32 0, i32 0), i8* %call)
  br label %cond.end

cond.end:                                         ; preds = %cond.false, %cond.true
  store i32 0, i32* %d1, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc89, %cond.end
  %3 = load i32, i32* %d1, align 4
  %4 = load i32, i32* @number_of_dragons, align 4
  %cmp = icmp slt i32 %3, %4
  br i1 %cmp, label %for.body, label %for.end91

for.body:                                         ; preds = %for.cond
  %5 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %6 = load i32, i32* %d1, align 4
  %idxprom = sext i32 %6 to i64
  %arrayidx = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %5, i64 %idxprom
  %origin = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx, i32 0, i32 0
  %7 = load i32, i32* %origin, align 4
  %idxprom2 = sext i32 %7 to i64
  %arrayidx3 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom2
  %color4 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx3, i32 0, i32 0
  %8 = load i32, i32* %color4, align 4
  %9 = load i32, i32* %color.addr, align 4
  %cmp5 = icmp ne i32 %8, %9
  br i1 %cmp5, label %if.then, label %lor.lhs.false

lor.lhs.false:                                    ; preds = %for.body
  %10 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %11 = load i32, i32* %d1, align 4
  %idxprom6 = sext i32 %11 to i64
  %arrayidx7 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %10, i64 %idxprom6
  %origin8 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx7, i32 0, i32 0
  %12 = load i32, i32* %origin8, align 4
  %idxprom9 = sext i32 %12 to i64
  %arrayidx10 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom9
  %status = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx10, i32 0, i32 16
  %13 = load i32, i32* %status, align 4
  %cmp11 = icmp ne i32 %13, 0
  br i1 %cmp11, label %land.lhs.true, label %if.end

land.lhs.true:                                    ; preds = %lor.lhs.false
  %14 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %15 = load i32, i32* %d1, align 4
  %idxprom12 = sext i32 %15 to i64
  %arrayidx13 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %14, i64 %idxprom12
  %origin14 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx13, i32 0, i32 0
  %16 = load i32, i32* %origin14, align 4
  %idxprom15 = sext i32 %16 to i64
  %arrayidx16 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom15
  %status17 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx16, i32 0, i32 16
  %17 = load i32, i32* %status17, align 4
  %cmp18 = icmp ne i32 %17, 2
  br i1 %cmp18, label %if.then, label %if.end

if.then:                                          ; preds = %land.lhs.true, %for.body
  br label %for.inc89

if.end:                                           ; preds = %land.lhs.true, %lor.lhs.false
  store i32 0, i32* %k, align 4
  br label %for.cond19

for.cond19:                                       ; preds = %for.inc, %if.end
  %18 = load i32, i32* %k, align 4
  %19 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %20 = load i32, i32* %d1, align 4
  %idxprom20 = sext i32 %20 to i64
  %arrayidx21 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %19, i64 %idxprom20
  %neighbors = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx21, i32 0, i32 2
  %21 = load i32, i32* %neighbors, align 4
  %cmp22 = icmp slt i32 %18, %21
  br i1 %cmp22, label %for.body23, label %for.end

for.body23:                                       ; preds = %for.cond19
  %22 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %23 = load i32, i32* %d1, align 4
  %idxprom24 = sext i32 %23 to i64
  %arrayidx25 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %22, i64 %idxprom24
  %adjacent = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx25, i32 0, i32 1
  %24 = load i32, i32* %k, align 4
  %idxprom26 = sext i32 %24 to i64
  %arrayidx27 = getelementptr inbounds [10 x i32], [10 x i32]* %adjacent, i64 0, i64 %idxprom26
  %25 = load i32, i32* %arrayidx27, align 4
  store i32 %25, i32* %d2, align 4
  %26 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %27 = load i32, i32* %d2, align 4
  %idxprom28 = sext i32 %27 to i64
  %arrayidx29 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %26, i64 %idxprom28
  %origin30 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx29, i32 0, i32 0
  %28 = load i32, i32* %origin30, align 4
  %idxprom31 = sext i32 %28 to i64
  %arrayidx32 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom31
  %color33 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx32, i32 0, i32 0
  %29 = load i32, i32* %color33, align 4
  %30 = load i32, i32* %other, align 4
  %cmp34 = icmp ne i32 %29, %30
  br i1 %cmp34, label %if.then51, label %lor.lhs.false35

lor.lhs.false35:                                  ; preds = %for.body23
  %31 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %32 = load i32, i32* %d2, align 4
  %idxprom36 = sext i32 %32 to i64
  %arrayidx37 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %31, i64 %idxprom36
  %origin38 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx37, i32 0, i32 0
  %33 = load i32, i32* %origin38, align 4
  %idxprom39 = sext i32 %33 to i64
  %arrayidx40 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom39
  %status41 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx40, i32 0, i32 16
  %34 = load i32, i32* %status41, align 4
  %cmp42 = icmp ne i32 %34, 0
  br i1 %cmp42, label %land.lhs.true43, label %if.end52

land.lhs.true43:                                  ; preds = %lor.lhs.false35
  %35 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %36 = load i32, i32* %d2, align 4
  %idxprom44 = sext i32 %36 to i64
  %arrayidx45 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %35, i64 %idxprom44
  %origin46 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx45, i32 0, i32 0
  %37 = load i32, i32* %origin46, align 4
  %idxprom47 = sext i32 %37 to i64
  %arrayidx48 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom47
  %status49 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx48, i32 0, i32 16
  %38 = load i32, i32* %status49, align 4
  %cmp50 = icmp ne i32 %38, 2
  br i1 %cmp50, label %if.then51, label %if.end52

if.then51:                                        ; preds = %land.lhs.true43, %for.body23
  br label %for.inc

if.end52:                                         ; preds = %land.lhs.true43, %lor.lhs.false35
  %39 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %40 = load i32, i32* %d1, align 4
  %idxprom53 = sext i32 %40 to i64
  %arrayidx54 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %39, i64 %idxprom53
  %origin55 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx54, i32 0, i32 0
  %41 = load i32, i32* %origin55, align 4
  %idxprom56 = sext i32 %41 to i64
  %arrayidx57 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom56
  %origin58 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx57, i32 0, i32 2
  %42 = load i32, i32* %origin58, align 4
  store i32 %42, i32* %apos, align 4
  %43 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %44 = load i32, i32* %d2, align 4
  %idxprom59 = sext i32 %44 to i64
  %arrayidx60 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %43, i64 %idxprom59
  %origin61 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx60, i32 0, i32 0
  %45 = load i32, i32* %origin61, align 4
  %idxprom62 = sext i32 %45 to i64
  %arrayidx63 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom62
  %origin64 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx63, i32 0, i32 2
  %46 = load i32, i32* %origin64, align 4
  store i32 %46, i32* %bpos, align 4
  %47 = load i32, i32* %apos, align 4
  %idxprom65 = sext i32 %47 to i64
  %arrayidx66 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom65
  %inessential = getelementptr inbounds %struct.worm_data, %struct.worm_data* %arrayidx66, i32 0, i32 12
  %48 = load i32, i32* %inessential, align 4
  %tobool67 = icmp ne i32 %48, 0
  br i1 %tobool67, label %if.then87, label %lor.lhs.false68

lor.lhs.false68:                                  ; preds = %if.end52
  %49 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %50 = load i32, i32* %apos, align 4
  %idxprom69 = sext i32 %50 to i64
  %arrayidx70 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom69
  %id = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx70, i32 0, i32 1
  %51 = load i32, i32* %id, align 4
  %idxprom71 = sext i32 %51 to i64
  %arrayidx72 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %49, i64 %idxprom71
  %safety = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx72, i32 0, i32 6
  %52 = load i32, i32* %safety, align 4
  %cmp73 = icmp eq i32 %52, 5
  br i1 %cmp73, label %if.then87, label %lor.lhs.false74

lor.lhs.false74:                                  ; preds = %lor.lhs.false68
  %53 = load i32, i32* %bpos, align 4
  %idxprom75 = sext i32 %53 to i64
  %arrayidx76 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom75
  %inessential77 = getelementptr inbounds %struct.worm_data, %struct.worm_data* %arrayidx76, i32 0, i32 12
  %54 = load i32, i32* %inessential77, align 4
  %tobool78 = icmp ne i32 %54, 0
  br i1 %tobool78, label %if.then87, label %lor.lhs.false79

lor.lhs.false79:                                  ; preds = %lor.lhs.false74
  %55 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %56 = load i32, i32* %bpos, align 4
  %idxprom80 = sext i32 %56 to i64
  %arrayidx81 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom80
  %id82 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx81, i32 0, i32 1
  %57 = load i32, i32* %id82, align 4
  %idxprom83 = sext i32 %57 to i64
  %arrayidx84 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %55, i64 %idxprom83
  %safety85 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx84, i32 0, i32 6
  %58 = load i32, i32* %safety85, align 4
  %cmp86 = icmp eq i32 %58, 5
  br i1 %cmp86, label %if.then87, label %if.end88

if.then87:                                        ; preds = %lor.lhs.false79, %lor.lhs.false74, %lor.lhs.false68, %if.end52
  br label %for.inc

if.end88:                                         ; preds = %lor.lhs.false79
  %59 = load i32, i32* %apos, align 4
  %60 = load i32, i32* %bpos, align 4
  call void @analyze_semeai(i32 %59, i32 %60)
  br label %for.inc

for.inc:                                          ; preds = %if.end88, %if.then87, %if.then51
  %61 = load i32, i32* %k, align 4
  %inc = add nsw i32 %61, 1
  store i32 %inc, i32* %k, align 4
  br label %for.cond19

for.end:                                          ; preds = %for.cond19
  br label %for.inc89

for.inc89:                                        ; preds = %for.end, %if.then
  %62 = load i32, i32* %d1, align 4
  %inc90 = add nsw i32 %62, 1
  store i32 %inc90, i32* %d1, align 4
  br label %for.cond

for.end91:                                        ; preds = %for.cond
  ret void
}

declare i32 @gprintf(i8*, ...) #1

declare i8* @color_to_string(i32) #1

; Function Attrs: noinline nounwind uwtable
define internal void @analyze_semeai(i32 %my_dragon, i32 %your_dragon) #0 {
entry:
  %my_dragon.addr = alloca i32, align 4
  %your_dragon.addr = alloca i32, align 4
  %mylibs = alloca i32, align 4
  %yourlibs = alloca i32, align 4
  %commonlibs = alloca i32, align 4
  %yourlib = alloca i32, align 4
  %commonlib = alloca i32, align 4
  %color = alloca i32, align 4
  %my_status = alloca i32, align 4
  %your_status = alloca i32, align 4
  %margin_of_safety = alloca i32, align 4
  %owl_code_sufficient = alloca i32, align 4
  %pos = alloca i32, align 4
  %acode = alloca i32, align 4
  %dcode = alloca i32, align 4
  %pos102 = alloca i32, align 4
  %adj = alloca i32, align 4
  %adjs = alloca [160 x i32], align 16
  %r = alloca i32, align 4
  %cpos = alloca i32, align 4
  %found_one = alloca i32, align 4
  store i32 %my_dragon, i32* %my_dragon.addr, align 4
  store i32 %your_dragon, i32* %your_dragon.addr, align 4
  store i32 1, i32* %mylibs, align 4
  store i32 1, i32* %yourlibs, align 4
  store i32 0, i32* %commonlibs, align 4
  store i32 0, i32* %yourlib, align 4
  store i32 0, i32* %commonlib, align 4
  %0 = load i32, i32* %my_dragon.addr, align 4
  %idxprom = sext i32 %0 to i64
  %arrayidx = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom
  %1 = load i8, i8* %arrayidx, align 1
  %conv = zext i8 %1 to i32
  store i32 %conv, i32* %color, align 4
  store i32 3, i32* %my_status, align 4
  store i32 3, i32* %your_status, align 4
  store i32 0, i32* %margin_of_safety, align 4
  store i32 0, i32* %owl_code_sufficient, align 4
  %2 = load i32, i32* @debug, align 4
  %and = and i32 %2, 64
  %tobool = icmp ne i32 %and, 0
  br i1 %tobool, label %cond.false, label %cond.true

cond.true:                                        ; preds = %entry
  br label %cond.end

cond.false:                                       ; preds = %entry
  %3 = load i32, i32* %my_dragon.addr, align 4
  %4 = load i32, i32* %your_dragon.addr, align 4
  %call = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.7, i32 0, i32 0), i32 %3, i32 %4)
  br label %cond.end

cond.end:                                         ; preds = %cond.false, %cond.true
  %5 = load i32, i32* %my_dragon.addr, align 4
  %idxprom1 = sext i32 %5 to i64
  %arrayidx2 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom1
  %owl_status = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx2, i32 0, i32 7
  %6 = load i32, i32* %owl_status, align 4
  %cmp = icmp eq i32 %6, 2
  br i1 %cmp, label %land.lhs.true, label %if.end43

land.lhs.true:                                    ; preds = %cond.end
  %7 = load i32, i32* %your_dragon.addr, align 4
  %idxprom4 = sext i32 %7 to i64
  %arrayidx5 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom4
  %owl_status6 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx5, i32 0, i32 7
  %8 = load i32, i32* %owl_status6, align 4
  %cmp7 = icmp eq i32 %8, 2
  br i1 %cmp7, label %if.then, label %if.end43

if.then:                                          ; preds = %land.lhs.true
  %9 = load i32, i32* %your_dragon.addr, align 4
  %idxprom9 = sext i32 %9 to i64
  %arrayidx10 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom9
  %owl_attack_point = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx10, i32 0, i32 8
  %10 = load i32, i32* %owl_attack_point, align 4
  %11 = load i32, i32* %my_dragon.addr, align 4
  %idxprom11 = sext i32 %11 to i64
  %arrayidx12 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom11
  %owl_defense_point = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx12, i32 0, i32 12
  %12 = load i32, i32* %owl_defense_point, align 4
  %cmp13 = icmp eq i32 %10, %12
  br i1 %cmp13, label %if.then15, label %if.end

if.then15:                                        ; preds = %if.then
  br label %if.end754

if.end:                                           ; preds = %if.then
  %13 = load i32, i32* %my_dragon.addr, align 4
  %idxprom16 = sext i32 %13 to i64
  %arrayidx17 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom16
  %owl_defense_point18 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx17, i32 0, i32 12
  %14 = load i32, i32* %owl_defense_point18, align 4
  %cmp19 = icmp ne i32 %14, 0
  br i1 %cmp19, label %if.then21, label %if.end42

if.then21:                                        ; preds = %if.end
  %15 = load i32, i32* %my_dragon.addr, align 4
  %idxprom22 = sext i32 %15 to i64
  %arrayidx23 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom22
  %owl_defense_point24 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx23, i32 0, i32 12
  %16 = load i32, i32* %owl_defense_point24, align 4
  %17 = load i32, i32* %your_dragon.addr, align 4
  %call25 = call i32 @owl_does_attack(i32 %16, i32 %17, i32* null)
  store i32 %call25, i32* %acode, align 4
  %18 = load i32, i32* %acode, align 4
  %cmp26 = icmp ne i32 %18, 0
  br i1 %cmp26, label %if.then28, label %if.end41

if.then28:                                        ; preds = %if.then21
  %19 = load i32, i32* %my_dragon.addr, align 4
  %idxprom29 = sext i32 %19 to i64
  %arrayidx30 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom29
  %owl_defense_point31 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx30, i32 0, i32 12
  %20 = load i32, i32* %owl_defense_point31, align 4
  %21 = load i32, i32* %your_dragon.addr, align 4
  %22 = load i32, i32* %acode, align 4
  call void @add_owl_attack_move(i32 %20, i32 %21, i32 %22)
  %23 = load i32, i32* @debug, align 4
  %and32 = and i32 %23, 64
  %tobool33 = icmp ne i32 %and32, 0
  br i1 %tobool33, label %cond.false35, label %cond.true34

cond.true34:                                      ; preds = %if.then28
  br label %cond.end40

cond.false35:                                     ; preds = %if.then28
  %24 = load i32, i32* %your_dragon.addr, align 4
  %25 = load i32, i32* %my_dragon.addr, align 4
  %idxprom36 = sext i32 %25 to i64
  %arrayidx37 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom36
  %owl_defense_point38 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx37, i32 0, i32 12
  %26 = load i32, i32* %owl_defense_point38, align 4
  %27 = load i32, i32* %acode, align 4
  %call39 = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.8, i32 0, i32 0), i32 %24, i32 %26, i32 %27)
  br label %cond.end40

cond.end40:                                       ; preds = %cond.false35, %cond.true34
  store i32 1, i32* %owl_code_sufficient, align 4
  br label %if.end41

if.end41:                                         ; preds = %cond.end40, %if.then21
  br label %if.end42

if.end42:                                         ; preds = %if.end41, %if.end
  br label %if.end43

if.end43:                                         ; preds = %if.end42, %land.lhs.true, %cond.end
  %28 = load i32, i32* %my_dragon.addr, align 4
  %idxprom44 = sext i32 %28 to i64
  %arrayidx45 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom44
  %owl_status46 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx45, i32 0, i32 7
  %29 = load i32, i32* %owl_status46, align 4
  %cmp47 = icmp eq i32 %29, 2
  br i1 %cmp47, label %land.lhs.true54, label %lor.lhs.false

lor.lhs.false:                                    ; preds = %if.end43
  %30 = load i32, i32* %my_dragon.addr, align 4
  %idxprom49 = sext i32 %30 to i64
  %arrayidx50 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom49
  %owl_status51 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx50, i32 0, i32 7
  %31 = load i32, i32* %owl_status51, align 4
  %cmp52 = icmp eq i32 %31, 0
  br i1 %cmp52, label %land.lhs.true54, label %if.end139

land.lhs.true54:                                  ; preds = %lor.lhs.false, %if.end43
  %32 = load i32, i32* %your_dragon.addr, align 4
  %idxprom55 = sext i32 %32 to i64
  %arrayidx56 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom55
  %owl_status57 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx56, i32 0, i32 7
  %33 = load i32, i32* %owl_status57, align 4
  %cmp58 = icmp eq i32 %33, 2
  br i1 %cmp58, label %if.then60, label %if.end139

if.then60:                                        ; preds = %land.lhs.true54
  %34 = load i32, i32* %your_dragon.addr, align 4
  %idxprom61 = sext i32 %34 to i64
  %arrayidx62 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom61
  %owl_attack_point63 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx62, i32 0, i32 8
  %35 = load i32, i32* %owl_attack_point63, align 4
  %36 = load i32, i32* %my_dragon.addr, align 4
  %idxprom64 = sext i32 %36 to i64
  %arrayidx65 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom64
  %owl_defense_point66 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx65, i32 0, i32 12
  %37 = load i32, i32* %owl_defense_point66, align 4
  %cmp67 = icmp eq i32 %35, %37
  br i1 %cmp67, label %if.then69, label %if.end70

if.then69:                                        ; preds = %if.then60
  br label %if.end754

if.end70:                                         ; preds = %if.then60
  %38 = load i32, i32* %your_dragon.addr, align 4
  %idxprom71 = sext i32 %38 to i64
  %arrayidx72 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom71
  %owl_attack_point73 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx72, i32 0, i32 8
  %39 = load i32, i32* %owl_attack_point73, align 4
  %cmp74 = icmp ne i32 %39, 0
  br i1 %cmp74, label %if.then76, label %if.end138

if.then76:                                        ; preds = %if.end70
  %40 = load i32, i32* %your_dragon.addr, align 4
  %idxprom77 = sext i32 %40 to i64
  %arrayidx78 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom77
  %owl_attack_point79 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx78, i32 0, i32 8
  %41 = load i32, i32* %owl_attack_point79, align 4
  %42 = load i32, i32* %my_dragon.addr, align 4
  %call80 = call i32 @owl_does_defend(i32 %41, i32 %42, i32* null)
  store i32 %call80, i32* %dcode, align 4
  %43 = load i32, i32* %dcode, align 4
  %cmp81 = icmp ne i32 %43, 0
  br i1 %cmp81, label %if.then83, label %if.end137

if.then83:                                        ; preds = %if.then76
  %44 = load i32, i32* %your_dragon.addr, align 4
  %idxprom84 = sext i32 %44 to i64
  %arrayidx85 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom84
  %owl_attack_point86 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx85, i32 0, i32 8
  %45 = load i32, i32* %owl_attack_point86, align 4
  %46 = load i32, i32* %my_dragon.addr, align 4
  %47 = load i32, i32* %dcode, align 4
  call void @add_owl_defense_move(i32 %45, i32 %46, i32 %47)
  %48 = load i32, i32* @debug, align 4
  %and87 = and i32 %48, 64
  %tobool88 = icmp ne i32 %and87, 0
  br i1 %tobool88, label %cond.false90, label %cond.true89

cond.true89:                                      ; preds = %if.then83
  br label %cond.end95

cond.false90:                                     ; preds = %if.then83
  %49 = load i32, i32* %my_dragon.addr, align 4
  %50 = load i32, i32* %your_dragon.addr, align 4
  %idxprom91 = sext i32 %50 to i64
  %arrayidx92 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom91
  %owl_attack_point93 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx92, i32 0, i32 8
  %51 = load i32, i32* %owl_attack_point93, align 4
  %52 = load i32, i32* %dcode, align 4
  %call94 = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([46 x i8], [46 x i8]* @.str.9, i32 0, i32 0), i32 %49, i32 %51, i32 %52)
  br label %cond.end95

cond.end95:                                       ; preds = %cond.false90, %cond.true89
  %53 = load i32, i32* %my_dragon.addr, align 4
  %idxprom96 = sext i32 %53 to i64
  %arrayidx97 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom96
  %owl_status98 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx97, i32 0, i32 7
  %54 = load i32, i32* %owl_status98, align 4
  %cmp99 = icmp eq i32 %54, 0
  br i1 %cmp99, label %if.then101, label %if.end136

if.then101:                                       ; preds = %cond.end95
  store i32 21, i32* %pos102, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %if.then101
  %55 = load i32, i32* %pos102, align 4
  %cmp103 = icmp slt i32 %55, 400
  br i1 %cmp103, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %56 = load i32, i32* %pos102, align 4
  %idxprom105 = sext i32 %56 to i64
  %arrayidx106 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom105
  %57 = load i8, i8* %arrayidx106, align 1
  %conv107 = zext i8 %57 to i32
  %cmp108 = icmp ne i32 %conv107, 3
  br i1 %cmp108, label %if.end111, label %if.then110

if.then110:                                       ; preds = %for.body
  br label %for.inc

if.end111:                                        ; preds = %for.body
  %58 = load i32, i32* %pos102, align 4
  %idxprom112 = sext i32 %58 to i64
  %arrayidx113 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom112
  %59 = load i8, i8* %arrayidx113, align 1
  %conv114 = zext i8 %59 to i32
  %60 = load i32, i32* %my_dragon.addr, align 4
  %idxprom115 = sext i32 %60 to i64
  %arrayidx116 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom115
  %61 = load i8, i8* %arrayidx116, align 1
  %conv117 = zext i8 %61 to i32
  %cmp118 = icmp eq i32 %conv114, %conv117
  br i1 %cmp118, label %land.lhs.true120, label %if.end129

land.lhs.true120:                                 ; preds = %if.end111
  %62 = load i32, i32* %pos102, align 4
  %63 = load i32, i32* %my_dragon.addr, align 4
  %call121 = call i32 @is_same_dragon(i32 %62, i32 %63)
  %tobool122 = icmp ne i32 %call121, 0
  br i1 %tobool122, label %if.then123, label %if.end129

if.then123:                                       ; preds = %land.lhs.true120
  %64 = load i32, i32* %pos102, align 4
  %idxprom124 = sext i32 %64 to i64
  %arrayidx125 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom124
  %owl_status126 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx125, i32 0, i32 7
  store i32 2, i32* %owl_status126, align 4
  %65 = load i32, i32* %pos102, align 4
  %idxprom127 = sext i32 %65 to i64
  %arrayidx128 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom127
  %status = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx128, i32 0, i32 16
  store i32 2, i32* %status, align 4
  br label %if.end129

if.end129:                                        ; preds = %if.then123, %land.lhs.true120, %if.end111
  br label %for.inc

for.inc:                                          ; preds = %if.end129, %if.then110
  %66 = load i32, i32* %pos102, align 4
  %inc = add nsw i32 %66, 1
  store i32 %inc, i32* %pos102, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %67 = load i32, i32* @debug, align 4
  %and130 = and i32 %67, 64
  %tobool131 = icmp ne i32 %and130, 0
  br i1 %tobool131, label %cond.false133, label %cond.true132

cond.true132:                                     ; preds = %for.end
  br label %cond.end135

cond.false133:                                    ; preds = %for.end
  %68 = load i32, i32* %my_dragon.addr, align 4
  %call134 = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.10, i32 0, i32 0), i32 %68)
  br label %cond.end135

cond.end135:                                      ; preds = %cond.false133, %cond.true132
  br label %if.end136

if.end136:                                        ; preds = %cond.end135, %cond.end95
  store i32 1, i32* %owl_code_sufficient, align 4
  br label %if.end137

if.end137:                                        ; preds = %if.end136, %if.then76
  br label %if.end138

if.end138:                                        ; preds = %if.end137, %if.end70
  br label %if.end139

if.end139:                                        ; preds = %if.end138, %land.lhs.true54, %lor.lhs.false
  %69 = load i32, i32* %owl_code_sufficient, align 4
  %tobool140 = icmp ne i32 %69, 0
  br i1 %tobool140, label %if.then141, label %if.end148

if.then141:                                       ; preds = %if.end139
  %70 = load i32, i32* @debug, align 4
  %and142 = and i32 %70, 64
  %tobool143 = icmp ne i32 %and142, 0
  br i1 %tobool143, label %cond.false145, label %cond.true144

cond.true144:                                     ; preds = %if.then141
  br label %cond.end147

cond.false145:                                    ; preds = %if.then141
  %call146 = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.11, i32 0, i32 0))
  br label %cond.end147

cond.end147:                                      ; preds = %cond.false145, %cond.true144
  br label %if.end754

if.end148:                                        ; preds = %if.end139
  store i32 21, i32* %pos, align 4
  br label %for.cond149

for.cond149:                                      ; preds = %for.inc218, %if.end148
  %71 = load i32, i32* %pos, align 4
  %cmp150 = icmp slt i32 %71, 400
  br i1 %cmp150, label %for.body152, label %for.end220

for.body152:                                      ; preds = %for.cond149
  %72 = load i32, i32* %pos, align 4
  %idxprom153 = sext i32 %72 to i64
  %arrayidx154 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom153
  %73 = load i8, i8* %arrayidx154, align 1
  %conv155 = zext i8 %73 to i32
  %cmp156 = icmp ne i32 %conv155, 3
  br i1 %cmp156, label %if.end159, label %if.then158

if.then158:                                       ; preds = %for.body152
  br label %for.inc218

if.end159:                                        ; preds = %for.body152
  %74 = load i32, i32* %pos, align 4
  %idxprom160 = sext i32 %74 to i64
  %arrayidx161 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom160
  %origin = getelementptr inbounds %struct.worm_data, %struct.worm_data* %arrayidx161, i32 0, i32 3
  %75 = load i32, i32* %origin, align 4
  %76 = load i32, i32* %pos, align 4
  %cmp162 = icmp eq i32 %75, %76
  br i1 %cmp162, label %land.lhs.true164, label %if.end217

land.lhs.true164:                                 ; preds = %if.end159
  %77 = load i32, i32* %pos, align 4
  %idxprom165 = sext i32 %77 to i64
  %arrayidx166 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom165
  %attack_codes = getelementptr inbounds %struct.worm_data, %struct.worm_data* %arrayidx166, i32 0, i32 16
  %arrayidx167 = getelementptr inbounds [10 x i32], [10 x i32]* %attack_codes, i64 0, i64 0
  %78 = load i32, i32* %arrayidx167, align 4
  %cmp168 = icmp eq i32 %78, 5
  br i1 %cmp168, label %if.then170, label %if.end217

if.then170:                                       ; preds = %land.lhs.true164
  %79 = load i32, i32* %pos, align 4
  %idxprom171 = sext i32 %79 to i64
  %arrayidx172 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom171
  %origin173 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx172, i32 0, i32 2
  %80 = load i32, i32* %origin173, align 4
  %81 = load i32, i32* %my_dragon.addr, align 4
  %cmp174 = icmp eq i32 %80, %81
  br i1 %cmp174, label %if.then182, label %lor.lhs.false176

lor.lhs.false176:                                 ; preds = %if.then170
  %82 = load i32, i32* %pos, align 4
  %idxprom177 = sext i32 %82 to i64
  %arrayidx178 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom177
  %origin179 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx178, i32 0, i32 2
  %83 = load i32, i32* %origin179, align 4
  %84 = load i32, i32* %your_dragon.addr, align 4
  %cmp180 = icmp eq i32 %83, %84
  br i1 %cmp180, label %if.then182, label %if.end216

if.then182:                                       ; preds = %lor.lhs.false176, %if.then170
  %85 = load i32, i32* %pos, align 4
  %arraydecay = getelementptr inbounds [160 x i32], [160 x i32]* %adjs, i32 0, i32 0
  %call183 = call i32 @chainlinks(i32 %85, i32* %arraydecay)
  store i32 %call183, i32* %adj, align 4
  store i32 0, i32* %r, align 4
  br label %for.cond184

for.cond184:                                      ; preds = %for.inc213, %if.then182
  %86 = load i32, i32* %r, align 4
  %87 = load i32, i32* %adj, align 4
  %cmp185 = icmp slt i32 %86, %87
  br i1 %cmp185, label %for.body187, label %for.end215

for.body187:                                      ; preds = %for.cond184
  %88 = load i32, i32* %r, align 4
  %idxprom188 = sext i32 %88 to i64
  %arrayidx189 = getelementptr inbounds [160 x i32], [160 x i32]* %adjs, i64 0, i64 %idxprom188
  %89 = load i32, i32* %arrayidx189, align 4
  store i32 %89, i32* %cpos, align 4
  %90 = load i32, i32* %cpos, align 4
  %idxprom190 = sext i32 %90 to i64
  %arrayidx191 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom190
  %origin192 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx191, i32 0, i32 2
  %91 = load i32, i32* %origin192, align 4
  %92 = load i32, i32* %my_dragon.addr, align 4
  %cmp193 = icmp eq i32 %91, %92
  br i1 %cmp193, label %if.then201, label %lor.lhs.false195

lor.lhs.false195:                                 ; preds = %for.body187
  %93 = load i32, i32* %cpos, align 4
  %idxprom196 = sext i32 %93 to i64
  %arrayidx197 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom196
  %origin198 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx197, i32 0, i32 2
  %94 = load i32, i32* %origin198, align 4
  %95 = load i32, i32* %your_dragon.addr, align 4
  %cmp199 = icmp eq i32 %94, %95
  br i1 %cmp199, label %if.then201, label %if.end212

if.then201:                                       ; preds = %lor.lhs.false195, %for.body187
  %96 = load i32, i32* %pos, align 4
  %call202 = call i32 @owl_substantial(i32 %96)
  %tobool203 = icmp ne i32 %call202, 0
  br i1 %tobool203, label %if.then204, label %if.end211

if.then204:                                       ; preds = %if.then201
  %97 = load i32, i32* @debug, align 4
  %and205 = and i32 %97, 64
  %tobool206 = icmp ne i32 %and205, 0
  br i1 %tobool206, label %cond.false208, label %cond.true207

cond.true207:                                     ; preds = %if.then204
  br label %cond.end210

cond.false208:                                    ; preds = %if.then204
  %call209 = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.12, i32 0, i32 0))
  br label %cond.end210

cond.end210:                                      ; preds = %cond.false208, %cond.true207
  br label %if.end754

if.end211:                                        ; preds = %if.then201
  br label %if.end212

if.end212:                                        ; preds = %if.end211, %lor.lhs.false195
  br label %for.inc213

for.inc213:                                       ; preds = %if.end212
  %98 = load i32, i32* %r, align 4
  %inc214 = add nsw i32 %98, 1
  store i32 %inc214, i32* %r, align 4
  br label %for.cond184

for.end215:                                       ; preds = %for.cond184
  br label %if.end216

if.end216:                                        ; preds = %for.end215, %lor.lhs.false176
  br label %if.end217

if.end217:                                        ; preds = %if.end216, %land.lhs.true164, %if.end159
  br label %for.inc218

for.inc218:                                       ; preds = %if.end217, %if.then158
  %99 = load i32, i32* %pos, align 4
  %inc219 = add nsw i32 %99, 1
  store i32 %inc219, i32* %pos, align 4
  br label %for.cond149

for.end220:                                       ; preds = %for.cond149
  store i32 21, i32* %pos, align 4
  br label %for.cond221

for.cond221:                                      ; preds = %for.inc242, %for.end220
  %100 = load i32, i32* %pos, align 4
  %cmp222 = icmp slt i32 %100, 400
  br i1 %cmp222, label %for.body224, label %for.end244

for.body224:                                      ; preds = %for.cond221
  %101 = load i32, i32* %pos, align 4
  %idxprom225 = sext i32 %101 to i64
  %arrayidx226 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom225
  %102 = load i8, i8* %arrayidx226, align 1
  %conv227 = zext i8 %102 to i32
  %cmp228 = icmp ne i32 %conv227, 3
  br i1 %cmp228, label %land.lhs.true230, label %if.end241

land.lhs.true230:                                 ; preds = %for.body224
  %103 = load i32, i32* %pos, align 4
  %104 = load i32, i32* %my_dragon.addr, align 4
  %call231 = call i32 @is_same_dragon(i32 %103, i32 %104)
  %tobool232 = icmp ne i32 %call231, 0
  br i1 %tobool232, label %if.then236, label %lor.lhs.false233

lor.lhs.false233:                                 ; preds = %land.lhs.true230
  %105 = load i32, i32* %pos, align 4
  %106 = load i32, i32* %your_dragon.addr, align 4
  %call234 = call i32 @is_same_dragon(i32 %105, i32 %106)
  %tobool235 = icmp ne i32 %call234, 0
  br i1 %tobool235, label %if.then236, label %if.end241

if.then236:                                       ; preds = %lor.lhs.false233, %land.lhs.true230
  %107 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %108 = load i32, i32* %pos, align 4
  %idxprom237 = sext i32 %108 to i64
  %arrayidx238 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom237
  %id = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx238, i32 0, i32 1
  %109 = load i32, i32* %id, align 4
  %idxprom239 = sext i32 %109 to i64
  %arrayidx240 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %107, i64 %idxprom239
  %semeai = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx240, i32 0, i32 13
  store i32 1, i32* %semeai, align 4
  br label %if.end241

if.end241:                                        ; preds = %if.then236, %lor.lhs.false233, %for.body224
  br label %for.inc242

for.inc242:                                       ; preds = %if.end241
  %110 = load i32, i32* %pos, align 4
  %inc243 = add nsw i32 %110, 1
  store i32 %inc243, i32* %pos, align 4
  br label %for.cond221

for.end244:                                       ; preds = %for.cond221
  store i32 21, i32* %pos, align 4
  br label %for.cond245

for.cond245:                                      ; preds = %for.inc309, %for.end244
  %111 = load i32, i32* %pos, align 4
  %cmp246 = icmp slt i32 %111, 400
  br i1 %cmp246, label %for.body248, label %for.end311

for.body248:                                      ; preds = %for.cond245
  %112 = load i32, i32* %pos, align 4
  %idxprom249 = sext i32 %112 to i64
  %arrayidx250 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom249
  %113 = load i8, i8* %arrayidx250, align 1
  %conv251 = zext i8 %113 to i32
  %cmp252 = icmp ne i32 %conv251, 3
  br i1 %cmp252, label %if.end255, label %if.then254

if.then254:                                       ; preds = %for.body248
  br label %for.inc309

if.end255:                                        ; preds = %for.body248
  %114 = load i32, i32* %pos, align 4
  %idxprom256 = sext i32 %114 to i64
  %arrayidx257 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom256
  %115 = load i8, i8* %arrayidx257, align 1
  %conv258 = zext i8 %115 to i32
  %cmp259 = icmp eq i32 %conv258, 1
  br i1 %cmp259, label %land.lhs.true267, label %lor.lhs.false261

lor.lhs.false261:                                 ; preds = %if.end255
  %116 = load i32, i32* %pos, align 4
  %idxprom262 = sext i32 %116 to i64
  %arrayidx263 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom262
  %117 = load i8, i8* %arrayidx263, align 1
  %conv264 = zext i8 %117 to i32
  %cmp265 = icmp eq i32 %conv264, 2
  br i1 %cmp265, label %land.lhs.true267, label %if.else

land.lhs.true267:                                 ; preds = %lor.lhs.false261, %if.end255
  %118 = load i32, i32* %pos, align 4
  %idxprom268 = sext i32 %118 to i64
  %arrayidx269 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom268
  %origin270 = getelementptr inbounds %struct.worm_data, %struct.worm_data* %arrayidx269, i32 0, i32 3
  %119 = load i32, i32* %origin270, align 4
  %120 = load i32, i32* %pos, align 4
  %cmp271 = icmp eq i32 %119, %120
  br i1 %cmp271, label %if.then273, label %if.else

if.then273:                                       ; preds = %land.lhs.true267
  %121 = load i32, i32* %pos, align 4
  %122 = load i32, i32* %my_dragon.addr, align 4
  %call274 = call i32 @is_same_dragon(i32 %121, i32 %122)
  %tobool275 = icmp ne i32 %call274, 0
  br i1 %tobool275, label %if.then276, label %if.end277

if.then276:                                       ; preds = %if.then273
  %123 = load i32, i32* %mylibs, align 4
  %dec = add nsw i32 %123, -1
  store i32 %dec, i32* %mylibs, align 4
  br label %if.end277

if.end277:                                        ; preds = %if.then276, %if.then273
  %124 = load i32, i32* %pos, align 4
  %125 = load i32, i32* %your_dragon.addr, align 4
  %call278 = call i32 @is_same_dragon(i32 %124, i32 %125)
  %tobool279 = icmp ne i32 %call278, 0
  br i1 %tobool279, label %if.then280, label %if.end282

if.then280:                                       ; preds = %if.end277
  %126 = load i32, i32* %yourlibs, align 4
  %dec281 = add nsw i32 %126, -1
  store i32 %dec281, i32* %yourlibs, align 4
  br label %if.end282

if.end282:                                        ; preds = %if.then280, %if.end277
  br label %if.end308

if.else:                                          ; preds = %land.lhs.true267, %lor.lhs.false261
  %127 = load i32, i32* %pos, align 4
  %idxprom283 = sext i32 %127 to i64
  %arrayidx284 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom283
  %128 = load i8, i8* %arrayidx284, align 1
  %conv285 = zext i8 %128 to i32
  %cmp286 = icmp eq i32 %conv285, 0
  br i1 %cmp286, label %if.then288, label %if.end307

if.then288:                                       ; preds = %if.else
  %129 = load i32, i32* %pos, align 4
  %130 = load i32, i32* %your_dragon.addr, align 4
  %call289 = call i32 @liberty_of_dragon(i32 %129, i32 %130)
  %tobool290 = icmp ne i32 %call289, 0
  br i1 %tobool290, label %if.then291, label %if.else300

if.then291:                                       ; preds = %if.then288
  %131 = load i32, i32* %yourlibs, align 4
  %inc292 = add nsw i32 %131, 1
  store i32 %inc292, i32* %yourlibs, align 4
  %132 = load i32, i32* %pos, align 4
  %133 = load i32, i32* %my_dragon.addr, align 4
  %call293 = call i32 @liberty_of_dragon(i32 %132, i32 %133)
  %tobool294 = icmp ne i32 %call293, 0
  br i1 %tobool294, label %if.then295, label %if.else298

if.then295:                                       ; preds = %if.then291
  %134 = load i32, i32* %commonlibs, align 4
  %inc296 = add nsw i32 %134, 1
  store i32 %inc296, i32* %commonlibs, align 4
  %135 = load i32, i32* %mylibs, align 4
  %inc297 = add nsw i32 %135, 1
  store i32 %inc297, i32* %mylibs, align 4
  %136 = load i32, i32* %pos, align 4
  store i32 %136, i32* %commonlib, align 4
  br label %if.end299

if.else298:                                       ; preds = %if.then291
  %137 = load i32, i32* %pos, align 4
  store i32 %137, i32* %yourlib, align 4
  br label %if.end299

if.end299:                                        ; preds = %if.else298, %if.then295
  br label %if.end306

if.else300:                                       ; preds = %if.then288
  %138 = load i32, i32* %pos, align 4
  %139 = load i32, i32* %my_dragon.addr, align 4
  %call301 = call i32 @liberty_of_dragon(i32 %138, i32 %139)
  %tobool302 = icmp ne i32 %call301, 0
  br i1 %tobool302, label %if.then303, label %if.end305

if.then303:                                       ; preds = %if.else300
  %140 = load i32, i32* %mylibs, align 4
  %inc304 = add nsw i32 %140, 1
  store i32 %inc304, i32* %mylibs, align 4
  br label %if.end305

if.end305:                                        ; preds = %if.then303, %if.else300
  br label %if.end306

if.end306:                                        ; preds = %if.end305, %if.end299
  br label %if.end307

if.end307:                                        ; preds = %if.end306, %if.else
  br label %if.end308

if.end308:                                        ; preds = %if.end307, %if.end282
  br label %for.inc309

for.inc309:                                       ; preds = %if.end308, %if.then254
  %141 = load i32, i32* %pos, align 4
  %inc310 = add nsw i32 %141, 1
  store i32 %inc310, i32* %pos, align 4
  br label %for.cond245

for.end311:                                       ; preds = %for.cond245
  %142 = load i32, i32* %my_dragon.addr, align 4
  %idxprom312 = sext i32 %142 to i64
  %arrayidx313 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom312
  %owl_status314 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx313, i32 0, i32 7
  %143 = load i32, i32* %owl_status314, align 4
  %cmp315 = icmp eq i32 %143, 2
  br i1 %cmp315, label %land.lhs.true317, label %if.end331

land.lhs.true317:                                 ; preds = %for.end311
  %144 = load i32, i32* %my_dragon.addr, align 4
  %idxprom318 = sext i32 %144 to i64
  %arrayidx319 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom318
  %owl_attack_point320 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx319, i32 0, i32 8
  %145 = load i32, i32* %owl_attack_point320, align 4
  %cmp321 = icmp ne i32 %145, 0
  br i1 %cmp321, label %land.lhs.true323, label %if.end331

land.lhs.true323:                                 ; preds = %land.lhs.true317
  %146 = load i32, i32* %my_dragon.addr, align 4
  %idxprom324 = sext i32 %146 to i64
  %arrayidx325 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom324
  %owl_attack_point326 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx325, i32 0, i32 8
  %147 = load i32, i32* %owl_attack_point326, align 4
  %148 = load i32, i32* %my_dragon.addr, align 4
  %call327 = call i32 @liberty_of_string(i32 %147, i32 %148)
  %tobool328 = icmp ne i32 %call327, 0
  br i1 %tobool328, label %if.end331, label %if.then329

if.then329:                                       ; preds = %land.lhs.true323
  %149 = load i32, i32* %mylibs, align 4
  %inc330 = add nsw i32 %149, 1
  store i32 %inc330, i32* %mylibs, align 4
  br label %if.end331

if.end331:                                        ; preds = %if.then329, %land.lhs.true323, %land.lhs.true317, %for.end311
  %150 = load i32, i32* %your_dragon.addr, align 4
  %idxprom332 = sext i32 %150 to i64
  %arrayidx333 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom332
  %owl_status334 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx333, i32 0, i32 7
  %151 = load i32, i32* %owl_status334, align 4
  %cmp335 = icmp eq i32 %151, 2
  br i1 %cmp335, label %land.lhs.true337, label %if.end351

land.lhs.true337:                                 ; preds = %if.end331
  %152 = load i32, i32* %your_dragon.addr, align 4
  %idxprom338 = sext i32 %152 to i64
  %arrayidx339 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom338
  %owl_attack_point340 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx339, i32 0, i32 8
  %153 = load i32, i32* %owl_attack_point340, align 4
  %cmp341 = icmp ne i32 %153, 0
  br i1 %cmp341, label %land.lhs.true343, label %if.end351

land.lhs.true343:                                 ; preds = %land.lhs.true337
  %154 = load i32, i32* %your_dragon.addr, align 4
  %idxprom344 = sext i32 %154 to i64
  %arrayidx345 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom344
  %owl_attack_point346 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx345, i32 0, i32 8
  %155 = load i32, i32* %owl_attack_point346, align 4
  %156 = load i32, i32* %your_dragon.addr, align 4
  %call347 = call i32 @liberty_of_string(i32 %155, i32 %156)
  %tobool348 = icmp ne i32 %call347, 0
  br i1 %tobool348, label %if.end351, label %if.then349

if.then349:                                       ; preds = %land.lhs.true343
  %157 = load i32, i32* %yourlibs, align 4
  %inc350 = add nsw i32 %157, 1
  store i32 %inc350, i32* %yourlibs, align 4
  br label %if.end351

if.end351:                                        ; preds = %if.then349, %land.lhs.true343, %land.lhs.true337, %if.end331
  %158 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %159 = load i32, i32* %my_dragon.addr, align 4
  %idxprom352 = sext i32 %159 to i64
  %arrayidx353 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom352
  %id354 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx353, i32 0, i32 1
  %160 = load i32, i32* %id354, align 4
  %idxprom355 = sext i32 %160 to i64
  %arrayidx356 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %158, i64 %idxprom355
  %genus = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx356, i32 0, i32 10
  %call357 = call i32 @min_eyes(%struct.eyevalue* %genus)
  %cmp358 = icmp eq i32 %call357, 0
  br i1 %cmp358, label %land.lhs.true360, label %if.end435

land.lhs.true360:                                 ; preds = %if.end351
  %161 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %162 = load i32, i32* %your_dragon.addr, align 4
  %idxprom361 = sext i32 %162 to i64
  %arrayidx362 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom361
  %id363 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx362, i32 0, i32 1
  %163 = load i32, i32* %id363, align 4
  %idxprom364 = sext i32 %163 to i64
  %arrayidx365 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %161, i64 %idxprom364
  %genus366 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx365, i32 0, i32 10
  %call367 = call i32 @min_eyes(%struct.eyevalue* %genus366)
  %cmp368 = icmp eq i32 %call367, 0
  br i1 %cmp368, label %if.then370, label %if.end435

if.then370:                                       ; preds = %land.lhs.true360
  %164 = load i32, i32* %commonlibs, align 4
  %cmp371 = icmp eq i32 %164, 0
  br i1 %cmp371, label %if.then373, label %if.else385

if.then373:                                       ; preds = %if.then370
  %165 = load i32, i32* %mylibs, align 4
  %166 = load i32, i32* %yourlibs, align 4
  %cmp374 = icmp sgt i32 %165, %166
  br i1 %cmp374, label %if.then376, label %if.else377

if.then376:                                       ; preds = %if.then373
  store i32 1, i32* %my_status, align 4
  store i32 0, i32* %your_status, align 4
  %167 = load i32, i32* %mylibs, align 4
  %168 = load i32, i32* %yourlibs, align 4
  %sub = sub nsw i32 %167, %168
  store i32 %sub, i32* %margin_of_safety, align 4
  br label %if.end384

if.else377:                                       ; preds = %if.then373
  %169 = load i32, i32* %mylibs, align 4
  %170 = load i32, i32* %yourlibs, align 4
  %cmp378 = icmp slt i32 %169, %170
  br i1 %cmp378, label %if.then380, label %if.else382

if.then380:                                       ; preds = %if.else377
  store i32 0, i32* %my_status, align 4
  store i32 1, i32* %your_status, align 4
  %171 = load i32, i32* %yourlibs, align 4
  %172 = load i32, i32* %mylibs, align 4
  %sub381 = sub nsw i32 %171, %172
  store i32 %sub381, i32* %margin_of_safety, align 4
  br label %if.end383

if.else382:                                       ; preds = %if.else377
  store i32 2, i32* %my_status, align 4
  store i32 2, i32* %your_status, align 4
  store i32 0, i32* %margin_of_safety, align 4
  br label %if.end383

if.end383:                                        ; preds = %if.else382, %if.then380
  br label %if.end384

if.end384:                                        ; preds = %if.end383, %if.then376
  br label %if.end434

if.else385:                                       ; preds = %if.then370
  %173 = load i32, i32* %mylibs, align 4
  %174 = load i32, i32* %yourlibs, align 4
  %175 = load i32, i32* %commonlibs, align 4
  %add = add nsw i32 %174, %175
  %sub386 = sub nsw i32 %add, 1
  %cmp387 = icmp eq i32 %173, %sub386
  br i1 %cmp387, label %if.then389, label %if.else395

if.then389:                                       ; preds = %if.else385
  %176 = load i32, i32* %mylibs, align 4
  %cmp390 = icmp eq i32 %176, 0
  br i1 %cmp390, label %if.then392, label %if.else393

if.then392:                                       ; preds = %if.then389
  store i32 2, i32* %my_status, align 4
  store i32 2, i32* %your_status, align 4
  store i32 0, i32* %margin_of_safety, align 4
  br label %if.end394

if.else393:                                       ; preds = %if.then389
  store i32 1, i32* %my_status, align 4
  store i32 2, i32* %your_status, align 4
  store i32 0, i32* %margin_of_safety, align 4
  br label %if.end394

if.end394:                                        ; preds = %if.else393, %if.then392
  br label %if.end433

if.else395:                                       ; preds = %if.else385
  %177 = load i32, i32* %mylibs, align 4
  %178 = load i32, i32* %yourlibs, align 4
  %179 = load i32, i32* %commonlibs, align 4
  %add396 = add nsw i32 %178, %179
  %sub397 = sub nsw i32 %add396, 1
  %cmp398 = icmp slt i32 %177, %sub397
  br i1 %cmp398, label %land.lhs.true400, label %if.else406

land.lhs.true400:                                 ; preds = %if.else395
  %180 = load i32, i32* %yourlibs, align 4
  %181 = load i32, i32* %mylibs, align 4
  %182 = load i32, i32* %commonlibs, align 4
  %add401 = add nsw i32 %181, %182
  %sub402 = sub nsw i32 %add401, 1
  %cmp403 = icmp slt i32 %180, %sub402
  br i1 %cmp403, label %if.then405, label %if.else406

if.then405:                                       ; preds = %land.lhs.true400
  store i32 1, i32* %my_status, align 4
  store i32 1, i32* %your_status, align 4
  store i32 1000, i32* %margin_of_safety, align 4
  br label %if.end432

if.else406:                                       ; preds = %land.lhs.true400, %if.else395
  %183 = load i32, i32* %commonlibs, align 4
  %cmp407 = icmp sgt i32 %183, 0
  br i1 %cmp407, label %land.lhs.true409, label %if.else420

land.lhs.true409:                                 ; preds = %if.else406
  %184 = load i32, i32* %yourlibs, align 4
  %185 = load i32, i32* %mylibs, align 4
  %186 = load i32, i32* %commonlibs, align 4
  %add410 = add nsw i32 %185, %186
  %sub411 = sub nsw i32 %add410, 1
  %cmp412 = icmp eq i32 %184, %sub411
  br i1 %cmp412, label %if.then414, label %if.else420

if.then414:                                       ; preds = %land.lhs.true409
  %187 = load i32, i32* %yourlibs, align 4
  %cmp415 = icmp eq i32 %187, 0
  br i1 %cmp415, label %if.then417, label %if.else418

if.then417:                                       ; preds = %if.then414
  store i32 2, i32* %my_status, align 4
  store i32 2, i32* %your_status, align 4
  store i32 0, i32* %margin_of_safety, align 4
  br label %if.end419

if.else418:                                       ; preds = %if.then414
  store i32 2, i32* %my_status, align 4
  store i32 1, i32* %your_status, align 4
  store i32 0, i32* %margin_of_safety, align 4
  br label %if.end419

if.end419:                                        ; preds = %if.else418, %if.then417
  br label %if.end431

if.else420:                                       ; preds = %land.lhs.true409, %if.else406
  %188 = load i32, i32* %commonlibs, align 4
  %cmp421 = icmp sgt i32 %188, 0
  br i1 %cmp421, label %land.lhs.true423, label %if.end430

land.lhs.true423:                                 ; preds = %if.else420
  %189 = load i32, i32* %yourlibs, align 4
  %190 = load i32, i32* %mylibs, align 4
  %191 = load i32, i32* %commonlibs, align 4
  %add424 = add nsw i32 %190, %191
  %cmp425 = icmp sgt i32 %189, %add424
  br i1 %cmp425, label %if.then427, label %if.end430

if.then427:                                       ; preds = %land.lhs.true423
  store i32 0, i32* %my_status, align 4
  store i32 1, i32* %your_status, align 4
  %192 = load i32, i32* %yourlibs, align 4
  %193 = load i32, i32* %mylibs, align 4
  %sub428 = sub nsw i32 %192, %193
  %194 = load i32, i32* %commonlibs, align 4
  %sub429 = sub nsw i32 %sub428, %194
  store i32 %sub429, i32* %margin_of_safety, align 4
  br label %if.end430

if.end430:                                        ; preds = %if.then427, %land.lhs.true423, %if.else420
  br label %if.end431

if.end431:                                        ; preds = %if.end430, %if.end419
  br label %if.end432

if.end432:                                        ; preds = %if.end431, %if.then405
  br label %if.end433

if.end433:                                        ; preds = %if.end432, %if.end394
  br label %if.end434

if.end434:                                        ; preds = %if.end433, %if.end384
  br label %if.end435

if.end435:                                        ; preds = %if.end434, %land.lhs.true360, %if.end351
  %195 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %196 = load i32, i32* %my_dragon.addr, align 4
  %idxprom436 = sext i32 %196 to i64
  %arrayidx437 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom436
  %id438 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx437, i32 0, i32 1
  %197 = load i32, i32* %id438, align 4
  %idxprom439 = sext i32 %197 to i64
  %arrayidx440 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %195, i64 %idxprom439
  %genus441 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx440, i32 0, i32 10
  %call442 = call i32 @min_eyes(%struct.eyevalue* %genus441)
  %cmp443 = icmp sgt i32 %call442, 0
  br i1 %cmp443, label %land.lhs.true445, label %if.end510

land.lhs.true445:                                 ; preds = %if.end435
  %198 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %199 = load i32, i32* %your_dragon.addr, align 4
  %idxprom446 = sext i32 %199 to i64
  %arrayidx447 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom446
  %id448 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx447, i32 0, i32 1
  %200 = load i32, i32* %id448, align 4
  %idxprom449 = sext i32 %200 to i64
  %arrayidx450 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %198, i64 %idxprom449
  %genus451 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx450, i32 0, i32 10
  %call452 = call i32 @min_eyes(%struct.eyevalue* %genus451)
  %cmp453 = icmp sgt i32 %call452, 0
  br i1 %cmp453, label %if.then455, label %if.end510

if.then455:                                       ; preds = %land.lhs.true445
  %201 = load i32, i32* %mylibs, align 4
  %202 = load i32, i32* %yourlibs, align 4
  %203 = load i32, i32* %commonlibs, align 4
  %add456 = add nsw i32 %202, %203
  %cmp457 = icmp sgt i32 %201, %add456
  br i1 %cmp457, label %if.then459, label %if.else462

if.then459:                                       ; preds = %if.then455
  store i32 1, i32* %my_status, align 4
  store i32 0, i32* %your_status, align 4
  %204 = load i32, i32* %mylibs, align 4
  %205 = load i32, i32* %yourlibs, align 4
  %sub460 = sub nsw i32 %204, %205
  %206 = load i32, i32* %commonlibs, align 4
  %sub461 = sub nsw i32 %sub460, %206
  store i32 %sub461, i32* %margin_of_safety, align 4
  br label %if.end509

if.else462:                                       ; preds = %if.then455
  %207 = load i32, i32* %yourlibs, align 4
  %208 = load i32, i32* %mylibs, align 4
  %209 = load i32, i32* %commonlibs, align 4
  %add463 = add nsw i32 %208, %209
  %cmp464 = icmp sgt i32 %207, %add463
  br i1 %cmp464, label %if.then466, label %if.else469

if.then466:                                       ; preds = %if.else462
  store i32 0, i32* %my_status, align 4
  store i32 1, i32* %your_status, align 4
  %210 = load i32, i32* %yourlibs, align 4
  %211 = load i32, i32* %mylibs, align 4
  %sub467 = sub nsw i32 %210, %211
  %212 = load i32, i32* %commonlibs, align 4
  %sub468 = sub nsw i32 %sub467, %212
  store i32 %sub468, i32* %margin_of_safety, align 4
  br label %if.end508

if.else469:                                       ; preds = %if.else462
  %213 = load i32, i32* %commonlibs, align 4
  %cmp470 = icmp eq i32 %213, 0
  br i1 %cmp470, label %land.lhs.true472, label %if.else476

land.lhs.true472:                                 ; preds = %if.else469
  %214 = load i32, i32* %mylibs, align 4
  %215 = load i32, i32* %yourlibs, align 4
  %cmp473 = icmp eq i32 %214, %215
  br i1 %cmp473, label %if.then475, label %if.else476

if.then475:                                       ; preds = %land.lhs.true472
  store i32 2, i32* %my_status, align 4
  store i32 2, i32* %your_status, align 4
  store i32 0, i32* %margin_of_safety, align 4
  br label %if.end507

if.else476:                                       ; preds = %land.lhs.true472, %if.else469
  %216 = load i32, i32* %commonlibs, align 4
  %cmp477 = icmp sgt i32 %216, 0
  br i1 %cmp477, label %land.lhs.true479, label %if.else484

land.lhs.true479:                                 ; preds = %if.else476
  %217 = load i32, i32* %mylibs, align 4
  %218 = load i32, i32* %commonlibs, align 4
  %219 = load i32, i32* %yourlibs, align 4
  %add480 = add nsw i32 %218, %219
  %cmp481 = icmp eq i32 %217, %add480
  br i1 %cmp481, label %if.then483, label %if.else484

if.then483:                                       ; preds = %land.lhs.true479
  store i32 1, i32* %my_status, align 4
  store i32 2, i32* %your_status, align 4
  store i32 0, i32* %margin_of_safety, align 4
  br label %if.end506

if.else484:                                       ; preds = %land.lhs.true479, %if.else476
  %220 = load i32, i32* %commonlibs, align 4
  %cmp485 = icmp sgt i32 %220, 0
  br i1 %cmp485, label %land.lhs.true487, label %if.else496

land.lhs.true487:                                 ; preds = %if.else484
  %221 = load i32, i32* %mylibs, align 4
  %222 = load i32, i32* %commonlibs, align 4
  %223 = load i32, i32* %yourlibs, align 4
  %add488 = add nsw i32 %222, %223
  %cmp489 = icmp slt i32 %221, %add488
  br i1 %cmp489, label %land.lhs.true491, label %if.else496

land.lhs.true491:                                 ; preds = %land.lhs.true487
  %224 = load i32, i32* %yourlibs, align 4
  %225 = load i32, i32* %commonlibs, align 4
  %226 = load i32, i32* %mylibs, align 4
  %add492 = add nsw i32 %225, %226
  %cmp493 = icmp slt i32 %224, %add492
  br i1 %cmp493, label %if.then495, label %if.else496

if.then495:                                       ; preds = %land.lhs.true491
  store i32 1, i32* %my_status, align 4
  store i32 1, i32* %your_status, align 4
  store i32 1000, i32* %margin_of_safety, align 4
  br label %if.end505

if.else496:                                       ; preds = %land.lhs.true491, %land.lhs.true487, %if.else484
  %227 = load i32, i32* %commonlibs, align 4
  %cmp497 = icmp sgt i32 %227, 0
  br i1 %cmp497, label %land.lhs.true499, label %if.end504

land.lhs.true499:                                 ; preds = %if.else496
  %228 = load i32, i32* %yourlibs, align 4
  %229 = load i32, i32* %commonlibs, align 4
  %230 = load i32, i32* %mylibs, align 4
  %add500 = add nsw i32 %229, %230
  %cmp501 = icmp eq i32 %228, %add500
  br i1 %cmp501, label %if.then503, label %if.end504

if.then503:                                       ; preds = %land.lhs.true499
  store i32 2, i32* %my_status, align 4
  store i32 1, i32* %your_status, align 4
  store i32 0, i32* %margin_of_safety, align 4
  br label %if.end504

if.end504:                                        ; preds = %if.then503, %land.lhs.true499, %if.else496
  br label %if.end505

if.end505:                                        ; preds = %if.end504, %if.then495
  br label %if.end506

if.end506:                                        ; preds = %if.end505, %if.then483
  br label %if.end507

if.end507:                                        ; preds = %if.end506, %if.then475
  br label %if.end508

if.end508:                                        ; preds = %if.end507, %if.then466
  br label %if.end509

if.end509:                                        ; preds = %if.end508, %if.then459
  br label %if.end510

if.end510:                                        ; preds = %if.end509, %land.lhs.true445, %if.end435
  %231 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %232 = load i32, i32* %my_dragon.addr, align 4
  %idxprom511 = sext i32 %232 to i64
  %arrayidx512 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom511
  %id513 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx512, i32 0, i32 1
  %233 = load i32, i32* %id513, align 4
  %idxprom514 = sext i32 %233 to i64
  %arrayidx515 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %231, i64 %idxprom514
  %genus516 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx515, i32 0, i32 10
  %call517 = call i32 @min_eyes(%struct.eyevalue* %genus516)
  %cmp518 = icmp sgt i32 %call517, 0
  br i1 %cmp518, label %land.lhs.true520, label %if.end552

land.lhs.true520:                                 ; preds = %if.end510
  %234 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %235 = load i32, i32* %your_dragon.addr, align 4
  %idxprom521 = sext i32 %235 to i64
  %arrayidx522 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom521
  %id523 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx522, i32 0, i32 1
  %236 = load i32, i32* %id523, align 4
  %idxprom524 = sext i32 %236 to i64
  %arrayidx525 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %234, i64 %idxprom524
  %genus526 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx525, i32 0, i32 10
  %call527 = call i32 @min_eyes(%struct.eyevalue* %genus526)
  %cmp528 = icmp eq i32 %call527, 0
  br i1 %cmp528, label %if.then530, label %if.end552

if.then530:                                       ; preds = %land.lhs.true520
  %237 = load i32, i32* %mylibs, align 4
  %238 = load i32, i32* %commonlibs, align 4
  %239 = load i32, i32* %yourlibs, align 4
  %add531 = add nsw i32 %238, %239
  %cmp532 = icmp sgt i32 %237, %add531
  br i1 %cmp532, label %if.then534, label %if.else537

if.then534:                                       ; preds = %if.then530
  store i32 1, i32* %my_status, align 4
  store i32 0, i32* %your_status, align 4
  %240 = load i32, i32* %mylibs, align 4
  %241 = load i32, i32* %commonlibs, align 4
  %sub535 = sub nsw i32 %240, %241
  %242 = load i32, i32* %yourlibs, align 4
  %sub536 = sub nsw i32 %sub535, %242
  store i32 %sub536, i32* %margin_of_safety, align 4
  br label %if.end551

if.else537:                                       ; preds = %if.then530
  %243 = load i32, i32* %mylibs, align 4
  %244 = load i32, i32* %commonlibs, align 4
  %add538 = add nsw i32 %243, %244
  %245 = load i32, i32* %yourlibs, align 4
  %cmp539 = icmp eq i32 %add538, %245
  br i1 %cmp539, label %if.then541, label %if.else542

if.then541:                                       ; preds = %if.else537
  store i32 2, i32* %my_status, align 4
  store i32 2, i32* %your_status, align 4
  br label %if.end550

if.else542:                                       ; preds = %if.else537
  %246 = load i32, i32* %mylibs, align 4
  %247 = load i32, i32* %commonlibs, align 4
  %add543 = add nsw i32 %246, %247
  %248 = load i32, i32* %yourlibs, align 4
  %cmp544 = icmp slt i32 %add543, %248
  br i1 %cmp544, label %if.then546, label %if.end549

if.then546:                                       ; preds = %if.else542
  store i32 0, i32* %my_status, align 4
  store i32 1, i32* %your_status, align 4
  %249 = load i32, i32* %mylibs, align 4
  %250 = load i32, i32* %commonlibs, align 4
  %add547 = add nsw i32 %249, %250
  %251 = load i32, i32* %yourlibs, align 4
  %sub548 = sub nsw i32 %add547, %251
  store i32 %sub548, i32* %margin_of_safety, align 4
  br label %if.end549

if.end549:                                        ; preds = %if.then546, %if.else542
  br label %if.end550

if.end550:                                        ; preds = %if.end549, %if.then541
  br label %if.end551

if.end551:                                        ; preds = %if.end550, %if.then534
  br label %if.end552

if.end552:                                        ; preds = %if.end551, %land.lhs.true520, %if.end510
  %252 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %253 = load i32, i32* %my_dragon.addr, align 4
  %idxprom553 = sext i32 %253 to i64
  %arrayidx554 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom553
  %id555 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx554, i32 0, i32 1
  %254 = load i32, i32* %id555, align 4
  %idxprom556 = sext i32 %254 to i64
  %arrayidx557 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %252, i64 %idxprom556
  %genus558 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx557, i32 0, i32 10
  %call559 = call i32 @min_eyes(%struct.eyevalue* %genus558)
  %cmp560 = icmp eq i32 %call559, 0
  br i1 %cmp560, label %land.lhs.true562, label %if.end594

land.lhs.true562:                                 ; preds = %if.end552
  %255 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %256 = load i32, i32* %your_dragon.addr, align 4
  %idxprom563 = sext i32 %256 to i64
  %arrayidx564 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom563
  %id565 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx564, i32 0, i32 1
  %257 = load i32, i32* %id565, align 4
  %idxprom566 = sext i32 %257 to i64
  %arrayidx567 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %255, i64 %idxprom566
  %genus568 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx567, i32 0, i32 10
  %call569 = call i32 @min_eyes(%struct.eyevalue* %genus568)
  %cmp570 = icmp sgt i32 %call569, 0
  br i1 %cmp570, label %if.then572, label %if.end594

if.then572:                                       ; preds = %land.lhs.true562
  %258 = load i32, i32* %yourlibs, align 4
  %259 = load i32, i32* %commonlibs, align 4
  %add573 = add nsw i32 %258, %259
  %260 = load i32, i32* %mylibs, align 4
  %cmp574 = icmp sgt i32 %add573, %260
  br i1 %cmp574, label %if.then576, label %if.else579

if.then576:                                       ; preds = %if.then572
  store i32 0, i32* %my_status, align 4
  store i32 1, i32* %your_status, align 4
  %261 = load i32, i32* %yourlibs, align 4
  %262 = load i32, i32* %commonlibs, align 4
  %add577 = add nsw i32 %261, %262
  %263 = load i32, i32* %mylibs, align 4
  %sub578 = sub nsw i32 %add577, %263
  store i32 %sub578, i32* %margin_of_safety, align 4
  br label %if.end593

if.else579:                                       ; preds = %if.then572
  %264 = load i32, i32* %yourlibs, align 4
  %265 = load i32, i32* %commonlibs, align 4
  %add580 = add nsw i32 %264, %265
  %266 = load i32, i32* %mylibs, align 4
  %cmp581 = icmp eq i32 %add580, %266
  br i1 %cmp581, label %if.then583, label %if.else584

if.then583:                                       ; preds = %if.else579
  store i32 2, i32* %my_status, align 4
  store i32 2, i32* %your_status, align 4
  store i32 0, i32* %margin_of_safety, align 4
  br label %if.end592

if.else584:                                       ; preds = %if.else579
  %267 = load i32, i32* %yourlibs, align 4
  %268 = load i32, i32* %commonlibs, align 4
  %add585 = add nsw i32 %267, %268
  %269 = load i32, i32* %mylibs, align 4
  %cmp586 = icmp sgt i32 %add585, %269
  br i1 %cmp586, label %if.then588, label %if.end591

if.then588:                                       ; preds = %if.else584
  store i32 0, i32* %my_status, align 4
  store i32 1, i32* %your_status, align 4
  %270 = load i32, i32* %yourlibs, align 4
  %271 = load i32, i32* %mylibs, align 4
  %sub589 = sub nsw i32 %270, %271
  %272 = load i32, i32* %commonlibs, align 4
  %sub590 = sub nsw i32 %sub589, %272
  store i32 %sub590, i32* %margin_of_safety, align 4
  br label %if.end591

if.end591:                                        ; preds = %if.then588, %if.else584
  br label %if.end592

if.end592:                                        ; preds = %if.end591, %if.then583
  br label %if.end593

if.end593:                                        ; preds = %if.end592, %if.then576
  br label %if.end594

if.end594:                                        ; preds = %if.end593, %land.lhs.true562, %if.end552
  %273 = load i32, i32* %my_dragon.addr, align 4
  %idxprom595 = sext i32 %273 to i64
  %arrayidx596 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom595
  %owl_status597 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx596, i32 0, i32 7
  %274 = load i32, i32* %owl_status597, align 4
  %cmp598 = icmp ne i32 %274, 2
  br i1 %cmp598, label %if.then600, label %if.end615

if.then600:                                       ; preds = %if.end594
  %275 = load i32, i32* %my_status, align 4
  %cmp601 = icmp eq i32 %275, 1
  br i1 %cmp601, label %if.then603, label %if.else604

if.then603:                                       ; preds = %if.then600
  %276 = load i32, i32* %my_dragon.addr, align 4
  call void @update_status(i32 %276, i32 1, i32 7)
  br label %if.end614

if.else604:                                       ; preds = %if.then600
  %277 = load i32, i32* %my_status, align 4
  %cmp605 = icmp eq i32 %277, 2
  br i1 %cmp605, label %if.then607, label %if.else608

if.then607:                                       ; preds = %if.else604
  %278 = load i32, i32* %my_dragon.addr, align 4
  call void @update_status(i32 %278, i32 2, i32 2)
  br label %if.end613

if.else608:                                       ; preds = %if.else604
  %279 = load i32, i32* %my_status, align 4
  %cmp609 = icmp eq i32 %279, 0
  br i1 %cmp609, label %if.then611, label %if.end612

if.then611:                                       ; preds = %if.else608
  %280 = load i32, i32* %my_dragon.addr, align 4
  call void @update_status(i32 %280, i32 0, i32 0)
  br label %if.end612

if.end612:                                        ; preds = %if.then611, %if.else608
  br label %if.end613

if.end613:                                        ; preds = %if.end612, %if.then607
  br label %if.end614

if.end614:                                        ; preds = %if.end613, %if.then603
  br label %if.end615

if.end615:                                        ; preds = %if.end614, %if.end594
  %281 = load i32, i32* %your_status, align 4
  %cmp616 = icmp eq i32 %281, 1
  br i1 %cmp616, label %if.then618, label %if.else619

if.then618:                                       ; preds = %if.end615
  %282 = load i32, i32* %your_dragon.addr, align 4
  call void @update_status(i32 %282, i32 1, i32 7)
  br label %if.end629

if.else619:                                       ; preds = %if.end615
  %283 = load i32, i32* %your_status, align 4
  %cmp620 = icmp eq i32 %283, 2
  br i1 %cmp620, label %if.then622, label %if.else623

if.then622:                                       ; preds = %if.else619
  %284 = load i32, i32* %your_dragon.addr, align 4
  call void @update_status(i32 %284, i32 2, i32 2)
  br label %if.end628

if.else623:                                       ; preds = %if.else619
  %285 = load i32, i32* %your_status, align 4
  %cmp624 = icmp eq i32 %285, 0
  br i1 %cmp624, label %if.then626, label %if.end627

if.then626:                                       ; preds = %if.else623
  %286 = load i32, i32* %your_dragon.addr, align 4
  call void @update_status(i32 %286, i32 0, i32 0)
  br label %if.end627

if.end627:                                        ; preds = %if.then626, %if.else623
  br label %if.end628

if.end628:                                        ; preds = %if.end627, %if.then622
  br label %if.end629

if.end629:                                        ; preds = %if.end628, %if.then618
  %287 = load i32, i32* %my_status, align 4
  %cmp630 = icmp eq i32 %287, 2
  br i1 %cmp630, label %if.then635, label %lor.lhs.false632

lor.lhs.false632:                                 ; preds = %if.end629
  %288 = load i32, i32* %your_status, align 4
  %cmp633 = icmp eq i32 %288, 2
  br i1 %cmp633, label %if.then635, label %if.end754

if.then635:                                       ; preds = %lor.lhs.false632, %if.end629
  store i32 0, i32* %found_one, align 4
  %289 = load i32, i32* %my_dragon.addr, align 4
  %idxprom636 = sext i32 %289 to i64
  %arrayidx637 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom636
  %owl_status638 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx637, i32 0, i32 7
  %290 = load i32, i32* %owl_status638, align 4
  %cmp639 = icmp eq i32 %290, 2
  br i1 %cmp639, label %land.lhs.true641, label %if.else651

land.lhs.true641:                                 ; preds = %if.then635
  %291 = load i32, i32* %my_dragon.addr, align 4
  %idxprom642 = sext i32 %291 to i64
  %arrayidx643 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom642
  %owl_defense_point644 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx643, i32 0, i32 12
  %292 = load i32, i32* %owl_defense_point644, align 4
  %cmp645 = icmp ne i32 %292, 0
  br i1 %cmp645, label %if.then647, label %if.else651

if.then647:                                       ; preds = %land.lhs.true641
  %293 = load i32, i32* %my_dragon.addr, align 4
  %idxprom648 = sext i32 %293 to i64
  %arrayidx649 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom648
  %owl_defense_point650 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx649, i32 0, i32 12
  %294 = load i32, i32* %owl_defense_point650, align 4
  %295 = load i32, i32* %my_dragon.addr, align 4
  %296 = load i32, i32* %your_dragon.addr, align 4
  %297 = load i32, i32* %my_status, align 4
  %298 = load i32, i32* %your_status, align 4
  %299 = load i32, i32* %margin_of_safety, align 4
  call void @add_appropriate_semeai_moves(i32 %294, i32 %295, i32 %296, i32 %297, i32 %298, i32 %299)
  br label %if.end753

if.else651:                                       ; preds = %land.lhs.true641, %if.then635
  %300 = load i32, i32* %your_dragon.addr, align 4
  %idxprom652 = sext i32 %300 to i64
  %arrayidx653 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom652
  %owl_status654 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx653, i32 0, i32 7
  %301 = load i32, i32* %owl_status654, align 4
  %cmp655 = icmp eq i32 %301, 2
  br i1 %cmp655, label %land.lhs.true657, label %if.else667

land.lhs.true657:                                 ; preds = %if.else651
  %302 = load i32, i32* %your_dragon.addr, align 4
  %idxprom658 = sext i32 %302 to i64
  %arrayidx659 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom658
  %owl_attack_point660 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx659, i32 0, i32 8
  %303 = load i32, i32* %owl_attack_point660, align 4
  %cmp661 = icmp ne i32 %303, 0
  br i1 %cmp661, label %if.then663, label %if.else667

if.then663:                                       ; preds = %land.lhs.true657
  %304 = load i32, i32* %your_dragon.addr, align 4
  %idxprom664 = sext i32 %304 to i64
  %arrayidx665 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom664
  %owl_attack_point666 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx665, i32 0, i32 8
  %305 = load i32, i32* %owl_attack_point666, align 4
  %306 = load i32, i32* %my_dragon.addr, align 4
  %307 = load i32, i32* %your_dragon.addr, align 4
  %308 = load i32, i32* %my_status, align 4
  %309 = load i32, i32* %your_status, align 4
  %310 = load i32, i32* %margin_of_safety, align 4
  call void @add_appropriate_semeai_moves(i32 %305, i32 %306, i32 %307, i32 %308, i32 %309, i32 %310)
  br label %if.end752

if.else667:                                       ; preds = %land.lhs.true657, %if.else651
  %311 = load i32, i32* %commonlibs, align 4
  %cmp668 = icmp sgt i32 %311, 1
  br i1 %cmp668, label %if.then670, label %if.else703

if.then670:                                       ; preds = %if.else667
  %312 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %313 = load i32, i32* %my_dragon.addr, align 4
  %idxprom671 = sext i32 %313 to i64
  %arrayidx672 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom671
  %id673 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx672, i32 0, i32 1
  %314 = load i32, i32* %id673, align 4
  %idxprom674 = sext i32 %314 to i64
  %arrayidx675 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %312, i64 %idxprom674
  %genus676 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx675, i32 0, i32 10
  %call677 = call i32 @eye_move_urgency(%struct.eyevalue* %genus676)
  %cmp678 = icmp sgt i32 %call677, 0
  br i1 %cmp678, label %if.then680, label %if.end686

if.then680:                                       ; preds = %if.then670
  %315 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %316 = load i32, i32* %my_dragon.addr, align 4
  %idxprom681 = sext i32 %316 to i64
  %arrayidx682 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom681
  %id683 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx682, i32 0, i32 1
  %317 = load i32, i32* %id683, align 4
  %idxprom684 = sext i32 %317 to i64
  %arrayidx685 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %315, i64 %idxprom684
  %heye = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx685, i32 0, i32 11
  %318 = load i32, i32* %heye, align 4
  %319 = load i32, i32* %my_dragon.addr, align 4
  %320 = load i32, i32* %your_dragon.addr, align 4
  %321 = load i32, i32* %my_status, align 4
  %322 = load i32, i32* %your_status, align 4
  %323 = load i32, i32* %margin_of_safety, align 4
  call void @add_appropriate_semeai_moves(i32 %318, i32 %319, i32 %320, i32 %321, i32 %322, i32 %323)
  br label %if.end686

if.end686:                                        ; preds = %if.then680, %if.then670
  %324 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %325 = load i32, i32* %your_dragon.addr, align 4
  %idxprom687 = sext i32 %325 to i64
  %arrayidx688 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom687
  %id689 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx688, i32 0, i32 1
  %326 = load i32, i32* %id689, align 4
  %idxprom690 = sext i32 %326 to i64
  %arrayidx691 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %324, i64 %idxprom690
  %genus692 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx691, i32 0, i32 10
  %call693 = call i32 @eye_move_urgency(%struct.eyevalue* %genus692)
  %tobool694 = icmp ne i32 %call693, 0
  br i1 %tobool694, label %if.then695, label %if.end702

if.then695:                                       ; preds = %if.end686
  %327 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %328 = load i32, i32* %your_dragon.addr, align 4
  %idxprom696 = sext i32 %328 to i64
  %arrayidx697 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom696
  %id698 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx697, i32 0, i32 1
  %329 = load i32, i32* %id698, align 4
  %idxprom699 = sext i32 %329 to i64
  %arrayidx700 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %327, i64 %idxprom699
  %heye701 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx700, i32 0, i32 11
  %330 = load i32, i32* %heye701, align 4
  %331 = load i32, i32* %my_dragon.addr, align 4
  %332 = load i32, i32* %your_dragon.addr, align 4
  %333 = load i32, i32* %my_status, align 4
  %334 = load i32, i32* %your_status, align 4
  %335 = load i32, i32* %margin_of_safety, align 4
  call void @add_appropriate_semeai_moves(i32 %330, i32 %331, i32 %332, i32 %333, i32 %334, i32 %335)
  br label %if.end702

if.end702:                                        ; preds = %if.then695, %if.end686
  br label %if.end751

if.else703:                                       ; preds = %if.else667
  store i32 21, i32* %pos, align 4
  br label %for.cond704

for.cond704:                                      ; preds = %for.inc725, %if.else703
  %336 = load i32, i32* %pos, align 4
  %cmp705 = icmp slt i32 %336, 400
  br i1 %cmp705, label %for.body707, label %for.end727

for.body707:                                      ; preds = %for.cond704
  %337 = load i32, i32* %pos, align 4
  %idxprom708 = sext i32 %337 to i64
  %arrayidx709 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom708
  %338 = load i8, i8* %arrayidx709, align 1
  %conv710 = zext i8 %338 to i32
  %cmp711 = icmp ne i32 %conv710, 3
  br i1 %cmp711, label %if.end714, label %if.then713

if.then713:                                       ; preds = %for.body707
  br label %for.inc725

if.end714:                                        ; preds = %for.body707
  %339 = load i32, i32* %pos, align 4
  %340 = load i32, i32* %your_dragon.addr, align 4
  %call715 = call i32 @liberty_of_dragon(i32 %339, i32 %340)
  %tobool716 = icmp ne i32 %call715, 0
  br i1 %tobool716, label %land.lhs.true717, label %if.end724

land.lhs.true717:                                 ; preds = %if.end714
  %341 = load i32, i32* %pos, align 4
  %342 = load i32, i32* %my_dragon.addr, align 4
  %call718 = call i32 @liberty_of_dragon(i32 %341, i32 %342)
  %tobool719 = icmp ne i32 %call718, 0
  br i1 %tobool719, label %if.end724, label %land.lhs.true720

land.lhs.true720:                                 ; preds = %land.lhs.true717
  %343 = load i32, i32* %pos, align 4
  %344 = load i32, i32* %color, align 4
  %call721 = call i32 @safe_move(i32 %343, i32 %344)
  %tobool722 = icmp ne i32 %call721, 0
  br i1 %tobool722, label %if.then723, label %if.end724

if.then723:                                       ; preds = %land.lhs.true720
  %345 = load i32, i32* %pos, align 4
  %346 = load i32, i32* %my_dragon.addr, align 4
  %347 = load i32, i32* %your_dragon.addr, align 4
  %348 = load i32, i32* %my_status, align 4
  %349 = load i32, i32* %your_status, align 4
  %350 = load i32, i32* %margin_of_safety, align 4
  call void @add_appropriate_semeai_moves(i32 %345, i32 %346, i32 %347, i32 %348, i32 %349, i32 %350)
  store i32 1, i32* %found_one, align 4
  br label %if.end724

if.end724:                                        ; preds = %if.then723, %land.lhs.true720, %land.lhs.true717, %if.end714
  br label %for.inc725

for.inc725:                                       ; preds = %if.end724, %if.then713
  %351 = load i32, i32* %pos, align 4
  %inc726 = add nsw i32 %351, 1
  store i32 %inc726, i32* %pos, align 4
  br label %for.cond704

for.end727:                                       ; preds = %for.cond704
  %352 = load i32, i32* %found_one, align 4
  %tobool728 = icmp ne i32 %352, 0
  br i1 %tobool728, label %if.end750, label %if.then729

if.then729:                                       ; preds = %for.end727
  store i32 21, i32* %pos, align 4
  br label %for.cond730

for.cond730:                                      ; preds = %for.inc747, %if.then729
  %353 = load i32, i32* %pos, align 4
  %cmp731 = icmp slt i32 %353, 400
  br i1 %cmp731, label %for.body733, label %for.end749

for.body733:                                      ; preds = %for.cond730
  %354 = load i32, i32* %pos, align 4
  %idxprom734 = sext i32 %354 to i64
  %arrayidx735 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom734
  %355 = load i8, i8* %arrayidx735, align 1
  %conv736 = zext i8 %355 to i32
  %cmp737 = icmp ne i32 %conv736, 3
  br i1 %cmp737, label %land.lhs.true739, label %if.end746

land.lhs.true739:                                 ; preds = %for.body733
  %356 = load i32, i32* %pos, align 4
  %357 = load i32, i32* %your_dragon.addr, align 4
  %call740 = call i32 @liberty_of_dragon(i32 %356, i32 %357)
  %tobool741 = icmp ne i32 %call740, 0
  br i1 %tobool741, label %land.lhs.true742, label %if.end746

land.lhs.true742:                                 ; preds = %land.lhs.true739
  %358 = load i32, i32* %pos, align 4
  %359 = load i32, i32* %color, align 4
  %call743 = call i32 @safe_move(i32 %358, i32 %359)
  %tobool744 = icmp ne i32 %call743, 0
  br i1 %tobool744, label %if.then745, label %if.end746

if.then745:                                       ; preds = %land.lhs.true742
  %360 = load i32, i32* %pos, align 4
  %361 = load i32, i32* %my_dragon.addr, align 4
  %362 = load i32, i32* %your_dragon.addr, align 4
  %363 = load i32, i32* %my_status, align 4
  %364 = load i32, i32* %your_status, align 4
  %365 = load i32, i32* %margin_of_safety, align 4
  call void @add_appropriate_semeai_moves(i32 %360, i32 %361, i32 %362, i32 %363, i32 %364, i32 %365)
  br label %if.end746

if.end746:                                        ; preds = %if.then745, %land.lhs.true742, %land.lhs.true739, %for.body733
  br label %for.inc747

for.inc747:                                       ; preds = %if.end746
  %366 = load i32, i32* %pos, align 4
  %inc748 = add nsw i32 %366, 1
  store i32 %inc748, i32* %pos, align 4
  br label %for.cond730

for.end749:                                       ; preds = %for.cond730
  br label %if.end750

if.end750:                                        ; preds = %for.end749, %for.end727
  br label %if.end751

if.end751:                                        ; preds = %if.end750, %if.end702
  br label %if.end752

if.end752:                                        ; preds = %if.end751, %if.then663
  br label %if.end753

if.end753:                                        ; preds = %if.end752, %if.then647
  br label %if.end754

if.end754:                                        ; preds = %if.then15, %if.then69, %cond.end147, %cond.end210, %if.end753, %lor.lhs.false632
  ret void
}

; Function Attrs: noinline nounwind uwtable
define void @new_semeai(i32 %color) #0 {
entry:
  %color.addr = alloca i32, align 4
  %d1 = alloca i32, align 4
  %d2 = alloca i32, align 4
  %k = alloca i32, align 4
  %apos = alloca i32, align 4
  %bpos = alloca i32, align 4
  %other = alloca i32, align 4
  %best_result_a = alloca [10 x i32], align 16
  %best_result_b = alloca [10 x i32], align 16
  %worst_result_a = alloca [10 x i32], align 16
  %worst_result_b = alloca [10 x i32], align 16
  %a_best_status = alloca i32, align 4
  %b_worst_status = alloca i32, align 4
  %a_worst_status = alloca i32, align 4
  %b_best_status = alloca i32, align 4
  %move = alloca [10 x i32], align 16
  %a_status = alloca i32, align 4
  %b_status = alloca i32, align 4
  %pass = alloca i32, align 4
  %semeai_found = alloca i32, align 4
  %a_status259 = alloca i32, align 4
  %b_status260 = alloca i32, align 4
  store i32 %color, i32* %color.addr, align 4
  store i32 0, i32* %apos, align 4
  store i32 0, i32* %bpos, align 4
  %0 = load i32, i32* %color.addr, align 4
  %sub = sub nsw i32 3, %0
  store i32 %sub, i32* %other, align 4
  store i32 3, i32* %a_best_status, align 4
  store i32 3, i32* %b_worst_status, align 4
  store i32 3, i32* %a_worst_status, align 4
  store i32 3, i32* %b_best_status, align 4
  store i32 3, i32* %a_status, align 4
  store i32 3, i32* %b_status, align 4
  %1 = load i32, i32* @verbose, align 4
  %tobool = icmp ne i32 %1, 0
  br i1 %tobool, label %cond.false, label %cond.true

cond.true:                                        ; preds = %entry
  br label %cond.end

cond.false:                                       ; preds = %entry
  %2 = load i32, i32* %color.addr, align 4
  %call = call i8* @color_to_string(i32 %2)
  %call1 = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.1, i32 0, i32 0), i8* %call)
  br label %cond.end

cond.end:                                         ; preds = %cond.false, %cond.true
  store i32 0, i32* %d1, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc283, %cond.end
  %3 = load i32, i32* %d1, align 4
  %4 = load i32, i32* @number_of_dragons, align 4
  %cmp = icmp slt i32 %3, %4
  br i1 %cmp, label %for.body, label %for.end285

for.body:                                         ; preds = %for.cond
  store i32 0, i32* %semeai_found, align 4
  %5 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %6 = load i32, i32* %d1, align 4
  %idxprom = sext i32 %6 to i64
  %arrayidx = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %5, i64 %idxprom
  %origin = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx, i32 0, i32 0
  %7 = load i32, i32* %origin, align 4
  %idxprom2 = sext i32 %7 to i64
  %arrayidx3 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom2
  %color4 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx3, i32 0, i32 0
  %8 = load i32, i32* %color4, align 4
  %9 = load i32, i32* %color.addr, align 4
  %cmp5 = icmp ne i32 %8, %9
  br i1 %cmp5, label %if.then, label %lor.lhs.false

lor.lhs.false:                                    ; preds = %for.body
  %10 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %11 = load i32, i32* %d1, align 4
  %idxprom6 = sext i32 %11 to i64
  %arrayidx7 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %10, i64 %idxprom6
  %origin8 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx7, i32 0, i32 0
  %12 = load i32, i32* %origin8, align 4
  %idxprom9 = sext i32 %12 to i64
  %arrayidx10 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom9
  %status = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx10, i32 0, i32 16
  %13 = load i32, i32* %status, align 4
  %cmp11 = icmp ne i32 %13, 0
  br i1 %cmp11, label %land.lhs.true, label %if.end

land.lhs.true:                                    ; preds = %lor.lhs.false
  %14 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %15 = load i32, i32* %d1, align 4
  %idxprom12 = sext i32 %15 to i64
  %arrayidx13 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %14, i64 %idxprom12
  %origin14 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx13, i32 0, i32 0
  %16 = load i32, i32* %origin14, align 4
  %idxprom15 = sext i32 %16 to i64
  %arrayidx16 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom15
  %status17 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx16, i32 0, i32 16
  %17 = load i32, i32* %status17, align 4
  %cmp18 = icmp ne i32 %17, 2
  br i1 %cmp18, label %if.then, label %if.end

if.then:                                          ; preds = %land.lhs.true, %for.body
  br label %for.inc283

if.end:                                           ; preds = %land.lhs.true, %lor.lhs.false
  store i32 0, i32* %k, align 4
  br label %for.cond19

for.cond19:                                       ; preds = %for.inc, %if.end
  %18 = load i32, i32* %k, align 4
  %19 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %20 = load i32, i32* %d1, align 4
  %idxprom20 = sext i32 %20 to i64
  %arrayidx21 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %19, i64 %idxprom20
  %neighbors = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx21, i32 0, i32 2
  %21 = load i32, i32* %neighbors, align 4
  %cmp22 = icmp slt i32 %18, %21
  br i1 %cmp22, label %for.body23, label %for.end

for.body23:                                       ; preds = %for.cond19
  %22 = load i32, i32* %k, align 4
  %idxprom24 = sext i32 %22 to i64
  %arrayidx25 = getelementptr inbounds [10 x i32], [10 x i32]* %best_result_a, i64 0, i64 %idxprom24
  store i32 0, i32* %arrayidx25, align 4
  %23 = load i32, i32* %k, align 4
  %idxprom26 = sext i32 %23 to i64
  %arrayidx27 = getelementptr inbounds [10 x i32], [10 x i32]* %worst_result_b, i64 0, i64 %idxprom26
  store i32 1, i32* %arrayidx27, align 4
  %24 = load i32, i32* %k, align 4
  %idxprom28 = sext i32 %24 to i64
  %arrayidx29 = getelementptr inbounds [10 x i32], [10 x i32]* %move, i64 0, i64 %idxprom28
  store i32 0, i32* %arrayidx29, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body23
  %25 = load i32, i32* %k, align 4
  %inc = add nsw i32 %25, 1
  store i32 %inc, i32* %k, align 4
  br label %for.cond19

for.end:                                          ; preds = %for.cond19
  store i32 0, i32* %pass, align 4
  br label %for.cond30

for.cond30:                                       ; preds = %for.inc280, %for.end
  %26 = load i32, i32* %pass, align 4
  %cmp31 = icmp slt i32 %26, 2
  br i1 %cmp31, label %for.body32, label %for.end282

for.body32:                                       ; preds = %for.cond30
  store i32 0, i32* %k, align 4
  br label %for.cond33

for.cond33:                                       ; preds = %for.inc252, %for.body32
  %27 = load i32, i32* %k, align 4
  %28 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %29 = load i32, i32* %d1, align 4
  %idxprom34 = sext i32 %29 to i64
  %arrayidx35 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %28, i64 %idxprom34
  %neighbors36 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx35, i32 0, i32 2
  %30 = load i32, i32* %neighbors36, align 4
  %cmp37 = icmp slt i32 %27, %30
  br i1 %cmp37, label %for.body38, label %for.end254

for.body38:                                       ; preds = %for.cond33
  %31 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %32 = load i32, i32* %d1, align 4
  %idxprom39 = sext i32 %32 to i64
  %arrayidx40 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %31, i64 %idxprom39
  %adjacent = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx40, i32 0, i32 1
  %33 = load i32, i32* %k, align 4
  %idxprom41 = sext i32 %33 to i64
  %arrayidx42 = getelementptr inbounds [10 x i32], [10 x i32]* %adjacent, i64 0, i64 %idxprom41
  %34 = load i32, i32* %arrayidx42, align 4
  store i32 %34, i32* %d2, align 4
  %35 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %36 = load i32, i32* %d2, align 4
  %idxprom43 = sext i32 %36 to i64
  %arrayidx44 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %35, i64 %idxprom43
  %origin45 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx44, i32 0, i32 0
  %37 = load i32, i32* %origin45, align 4
  %idxprom46 = sext i32 %37 to i64
  %arrayidx47 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom46
  %color48 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx47, i32 0, i32 0
  %38 = load i32, i32* %color48, align 4
  %39 = load i32, i32* %other, align 4
  %cmp49 = icmp ne i32 %38, %39
  br i1 %cmp49, label %if.then66, label %lor.lhs.false50

lor.lhs.false50:                                  ; preds = %for.body38
  %40 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %41 = load i32, i32* %d2, align 4
  %idxprom51 = sext i32 %41 to i64
  %arrayidx52 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %40, i64 %idxprom51
  %origin53 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx52, i32 0, i32 0
  %42 = load i32, i32* %origin53, align 4
  %idxprom54 = sext i32 %42 to i64
  %arrayidx55 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom54
  %status56 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx55, i32 0, i32 16
  %43 = load i32, i32* %status56, align 4
  %cmp57 = icmp ne i32 %43, 0
  br i1 %cmp57, label %land.lhs.true58, label %if.end67

land.lhs.true58:                                  ; preds = %lor.lhs.false50
  %44 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %45 = load i32, i32* %d2, align 4
  %idxprom59 = sext i32 %45 to i64
  %arrayidx60 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %44, i64 %idxprom59
  %origin61 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx60, i32 0, i32 0
  %46 = load i32, i32* %origin61, align 4
  %idxprom62 = sext i32 %46 to i64
  %arrayidx63 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom62
  %status64 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx63, i32 0, i32 16
  %47 = load i32, i32* %status64, align 4
  %cmp65 = icmp ne i32 %47, 2
  br i1 %cmp65, label %if.then66, label %if.end67

if.then66:                                        ; preds = %land.lhs.true58, %for.body38
  br label %for.inc252

if.end67:                                         ; preds = %land.lhs.true58, %lor.lhs.false50
  %48 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %49 = load i32, i32* %d1, align 4
  %idxprom68 = sext i32 %49 to i64
  %arrayidx69 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %48, i64 %idxprom68
  %origin70 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx69, i32 0, i32 0
  %50 = load i32, i32* %origin70, align 4
  %idxprom71 = sext i32 %50 to i64
  %arrayidx72 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom71
  %origin73 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx72, i32 0, i32 2
  %51 = load i32, i32* %origin73, align 4
  store i32 %51, i32* %apos, align 4
  %52 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %53 = load i32, i32* %d2, align 4
  %idxprom74 = sext i32 %53 to i64
  %arrayidx75 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %52, i64 %idxprom74
  %origin76 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx75, i32 0, i32 0
  %54 = load i32, i32* %origin76, align 4
  %idxprom77 = sext i32 %54 to i64
  %arrayidx78 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom77
  %origin79 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx78, i32 0, i32 2
  %55 = load i32, i32* %origin79, align 4
  store i32 %55, i32* %bpos, align 4
  %56 = load i32, i32* %apos, align 4
  %idxprom80 = sext i32 %56 to i64
  %arrayidx81 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom80
  %inessential = getelementptr inbounds %struct.worm_data, %struct.worm_data* %arrayidx81, i32 0, i32 12
  %57 = load i32, i32* %inessential, align 4
  %tobool82 = icmp ne i32 %57, 0
  br i1 %tobool82, label %if.then102, label %lor.lhs.false83

lor.lhs.false83:                                  ; preds = %if.end67
  %58 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %59 = load i32, i32* %apos, align 4
  %idxprom84 = sext i32 %59 to i64
  %arrayidx85 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom84
  %id = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx85, i32 0, i32 1
  %60 = load i32, i32* %id, align 4
  %idxprom86 = sext i32 %60 to i64
  %arrayidx87 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %58, i64 %idxprom86
  %safety = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx87, i32 0, i32 6
  %61 = load i32, i32* %safety, align 4
  %cmp88 = icmp eq i32 %61, 5
  br i1 %cmp88, label %if.then102, label %lor.lhs.false89

lor.lhs.false89:                                  ; preds = %lor.lhs.false83
  %62 = load i32, i32* %bpos, align 4
  %idxprom90 = sext i32 %62 to i64
  %arrayidx91 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom90
  %inessential92 = getelementptr inbounds %struct.worm_data, %struct.worm_data* %arrayidx91, i32 0, i32 12
  %63 = load i32, i32* %inessential92, align 4
  %tobool93 = icmp ne i32 %63, 0
  br i1 %tobool93, label %if.then102, label %lor.lhs.false94

lor.lhs.false94:                                  ; preds = %lor.lhs.false89
  %64 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %65 = load i32, i32* %bpos, align 4
  %idxprom95 = sext i32 %65 to i64
  %arrayidx96 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom95
  %id97 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx96, i32 0, i32 1
  %66 = load i32, i32* %id97, align 4
  %idxprom98 = sext i32 %66 to i64
  %arrayidx99 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %64, i64 %idxprom98
  %safety100 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx99, i32 0, i32 6
  %67 = load i32, i32* %safety100, align 4
  %cmp101 = icmp eq i32 %67, 5
  br i1 %cmp101, label %if.then102, label %if.end103

if.then102:                                       ; preds = %lor.lhs.false94, %lor.lhs.false89, %lor.lhs.false83, %if.end67
  br label %for.inc252

if.end103:                                        ; preds = %lor.lhs.false94
  %68 = load i32, i32* %apos, align 4
  %idxprom104 = sext i32 %68 to i64
  %arrayidx105 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom104
  %size = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx105, i32 0, i32 3
  %69 = load i32, i32* %size, align 4
  %70 = load i32, i32* %apos, align 4
  %idxprom106 = sext i32 %70 to i64
  %arrayidx107 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom106
  %size108 = getelementptr inbounds %struct.worm_data, %struct.worm_data* %arrayidx107, i32 0, i32 1
  %71 = load i32, i32* %size108, align 4
  %cmp109 = icmp eq i32 %69, %71
  br i1 %cmp109, label %land.lhs.true110, label %if.end123

land.lhs.true110:                                 ; preds = %if.end103
  %72 = load i32, i32* %apos, align 4
  %idxprom111 = sext i32 %72 to i64
  %arrayidx112 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom111
  %attack_codes = getelementptr inbounds %struct.worm_data, %struct.worm_data* %arrayidx112, i32 0, i32 16
  %arrayidx113 = getelementptr inbounds [10 x i32], [10 x i32]* %attack_codes, i64 0, i64 0
  %73 = load i32, i32* %arrayidx113, align 4
  %cmp114 = icmp eq i32 %73, 5
  br i1 %cmp114, label %land.lhs.true115, label %if.end123

land.lhs.true115:                                 ; preds = %land.lhs.true110
  %74 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %75 = load i32, i32* %apos, align 4
  %idxprom116 = sext i32 %75 to i64
  %arrayidx117 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom116
  %id118 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx117, i32 0, i32 1
  %76 = load i32, i32* %id118, align 4
  %idxprom119 = sext i32 %76 to i64
  %arrayidx120 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %74, i64 %idxprom119
  %hostile_neighbors = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx120, i32 0, i32 3
  %77 = load i32, i32* %hostile_neighbors, align 4
  %cmp121 = icmp eq i32 %77, 1
  br i1 %cmp121, label %if.then122, label %if.end123

if.then122:                                       ; preds = %land.lhs.true115
  br label %for.inc252

if.end123:                                        ; preds = %land.lhs.true115, %land.lhs.true110, %if.end103
  %78 = load i32, i32* %bpos, align 4
  %idxprom124 = sext i32 %78 to i64
  %arrayidx125 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom124
  %size126 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx125, i32 0, i32 3
  %79 = load i32, i32* %size126, align 4
  %80 = load i32, i32* %bpos, align 4
  %idxprom127 = sext i32 %80 to i64
  %arrayidx128 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom127
  %size129 = getelementptr inbounds %struct.worm_data, %struct.worm_data* %arrayidx128, i32 0, i32 1
  %81 = load i32, i32* %size129, align 4
  %cmp130 = icmp eq i32 %79, %81
  br i1 %cmp130, label %land.lhs.true131, label %if.end146

land.lhs.true131:                                 ; preds = %if.end123
  %82 = load i32, i32* %bpos, align 4
  %idxprom132 = sext i32 %82 to i64
  %arrayidx133 = getelementptr inbounds [400 x %struct.worm_data], [400 x %struct.worm_data]* @worm, i64 0, i64 %idxprom132
  %attack_codes134 = getelementptr inbounds %struct.worm_data, %struct.worm_data* %arrayidx133, i32 0, i32 16
  %arrayidx135 = getelementptr inbounds [10 x i32], [10 x i32]* %attack_codes134, i64 0, i64 0
  %83 = load i32, i32* %arrayidx135, align 4
  %cmp136 = icmp eq i32 %83, 5
  br i1 %cmp136, label %land.lhs.true137, label %if.end146

land.lhs.true137:                                 ; preds = %land.lhs.true131
  %84 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %85 = load i32, i32* %bpos, align 4
  %idxprom138 = sext i32 %85 to i64
  %arrayidx139 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom138
  %id140 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx139, i32 0, i32 1
  %86 = load i32, i32* %id140, align 4
  %idxprom141 = sext i32 %86 to i64
  %arrayidx142 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %84, i64 %idxprom141
  %hostile_neighbors143 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx142, i32 0, i32 3
  %87 = load i32, i32* %hostile_neighbors143, align 4
  %cmp144 = icmp eq i32 %87, 1
  br i1 %cmp144, label %if.then145, label %if.end146

if.then145:                                       ; preds = %land.lhs.true137
  br label %for.inc252

if.end146:                                        ; preds = %land.lhs.true137, %land.lhs.true131, %if.end123
  %88 = load i32, i32* %apos, align 4
  %idxprom147 = sext i32 %88 to i64
  %arrayidx148 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom147
  %size149 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx148, i32 0, i32 3
  %89 = load i32, i32* %size149, align 4
  %cmp150 = icmp eq i32 %89, 1
  br i1 %cmp150, label %if.then156, label %lor.lhs.false151

lor.lhs.false151:                                 ; preds = %if.end146
  %90 = load i32, i32* %bpos, align 4
  %idxprom152 = sext i32 %90 to i64
  %arrayidx153 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom152
  %size154 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx153, i32 0, i32 3
  %91 = load i32, i32* %size154, align 4
  %cmp155 = icmp eq i32 %91, 1
  br i1 %cmp155, label %if.then156, label %if.end157

if.then156:                                       ; preds = %lor.lhs.false151, %if.end146
  br label %for.inc252

if.end157:                                        ; preds = %lor.lhs.false151
  store i32 1, i32* %semeai_found, align 4
  store i32 3, i32* %a_best_status, align 4
  store i32 3, i32* %b_best_status, align 4
  store i32 3, i32* %a_worst_status, align 4
  store i32 3, i32* %b_worst_status, align 4
  %92 = load i32, i32* %pass, align 4
  %cmp158 = icmp eq i32 %92, 0
  br i1 %cmp158, label %if.then159, label %if.else

if.then159:                                       ; preds = %if.end157
  %93 = load i32, i32* @debug, align 4
  %and = and i32 %93, 64
  %tobool160 = icmp ne i32 %and, 0
  br i1 %tobool160, label %cond.false162, label %cond.true161

cond.true161:                                     ; preds = %if.then159
  br label %cond.end164

cond.false162:                                    ; preds = %if.then159
  %94 = load i32, i32* %apos, align 4
  %95 = load i32, i32* %bpos, align 4
  %call163 = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.2, i32 0, i32 0), i32 %94, i32 %95)
  br label %cond.end164

cond.end164:                                      ; preds = %cond.false162, %cond.true161
  %96 = load i32, i32* %apos, align 4
  %97 = load i32, i32* %bpos, align 4
  %arraydecay = getelementptr inbounds [10 x i32], [10 x i32]* %best_result_a, i32 0, i32 0
  %98 = load i32, i32* %k, align 4
  %idx.ext = sext i32 %98 to i64
  %add.ptr = getelementptr inbounds i32, i32* %arraydecay, i64 %idx.ext
  %arraydecay165 = getelementptr inbounds [10 x i32], [10 x i32]* %worst_result_b, i32 0, i32 0
  %99 = load i32, i32* %k, align 4
  %idx.ext166 = sext i32 %99 to i64
  %add.ptr167 = getelementptr inbounds i32, i32* %arraydecay165, i64 %idx.ext166
  %arraydecay168 = getelementptr inbounds [10 x i32], [10 x i32]* %move, i32 0, i32 0
  %100 = load i32, i32* %k, align 4
  %idx.ext169 = sext i32 %100 to i64
  %add.ptr170 = getelementptr inbounds i32, i32* %arraydecay168, i64 %idx.ext169
  call void @owl_analyze_semeai(i32 %96, i32 %97, i32* %add.ptr, i32* %add.ptr167, i32* %add.ptr170, i32 1)
  %101 = load i32, i32* @debug, align 4
  %and171 = and i32 %101, 64
  %tobool172 = icmp ne i32 %and171, 0
  br i1 %tobool172, label %cond.false174, label %cond.true173

cond.true173:                                     ; preds = %cond.end164
  br label %cond.end184

cond.false174:                                    ; preds = %cond.end164
  %102 = load i32, i32* %k, align 4
  %idxprom175 = sext i32 %102 to i64
  %arrayidx176 = getelementptr inbounds [10 x i32], [10 x i32]* %best_result_a, i64 0, i64 %idxprom175
  %103 = load i32, i32* %arrayidx176, align 4
  %call177 = call i8* @safety_to_string(i32 %103)
  %104 = load i32, i32* %k, align 4
  %idxprom178 = sext i32 %104 to i64
  %arrayidx179 = getelementptr inbounds [10 x i32], [10 x i32]* %worst_result_b, i64 0, i64 %idxprom178
  %105 = load i32, i32* %arrayidx179, align 4
  %call180 = call i8* @safety_to_string(i32 %105)
  %106 = load i32, i32* %k, align 4
  %idxprom181 = sext i32 %106 to i64
  %arrayidx182 = getelementptr inbounds [10 x i32], [10 x i32]* %move, i64 0, i64 %idxprom181
  %107 = load i32, i32* %arrayidx182, align 4
  %call183 = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.3, i32 0, i32 0), i8* %call177, i8* %call180, i32 %107)
  br label %cond.end184

cond.end184:                                      ; preds = %cond.false174, %cond.true173
  %108 = load i32, i32* %a_best_status, align 4
  %cmp185 = icmp eq i32 %108, 0
  br i1 %cmp185, label %if.then194, label %lor.lhs.false186

lor.lhs.false186:                                 ; preds = %cond.end184
  %109 = load i32, i32* %a_best_status, align 4
  %cmp187 = icmp eq i32 %109, 3
  br i1 %cmp187, label %if.then194, label %lor.lhs.false188

lor.lhs.false188:                                 ; preds = %lor.lhs.false186
  %110 = load i32, i32* %a_best_status, align 4
  %cmp189 = icmp eq i32 %110, 7
  br i1 %cmp189, label %land.lhs.true190, label %if.end199

land.lhs.true190:                                 ; preds = %lor.lhs.false188
  %111 = load i32, i32* %k, align 4
  %idxprom191 = sext i32 %111 to i64
  %arrayidx192 = getelementptr inbounds [10 x i32], [10 x i32]* %best_result_a, i64 0, i64 %idxprom191
  %112 = load i32, i32* %arrayidx192, align 4
  %cmp193 = icmp eq i32 %112, 1
  br i1 %cmp193, label %if.then194, label %if.end199

if.then194:                                       ; preds = %land.lhs.true190, %lor.lhs.false186, %cond.end184
  %113 = load i32, i32* %k, align 4
  %idxprom195 = sext i32 %113 to i64
  %arrayidx196 = getelementptr inbounds [10 x i32], [10 x i32]* %best_result_a, i64 0, i64 %idxprom195
  %114 = load i32, i32* %arrayidx196, align 4
  store i32 %114, i32* %a_best_status, align 4
  %115 = load i32, i32* %k, align 4
  %idxprom197 = sext i32 %115 to i64
  %arrayidx198 = getelementptr inbounds [10 x i32], [10 x i32]* %worst_result_b, i64 0, i64 %idxprom197
  %116 = load i32, i32* %arrayidx198, align 4
  store i32 %116, i32* %b_worst_status, align 4
  br label %if.end199

if.end199:                                        ; preds = %if.then194, %land.lhs.true190, %lor.lhs.false188
  %117 = load i32, i32* %bpos, align 4
  %118 = load i32, i32* %apos, align 4
  %arraydecay200 = getelementptr inbounds [10 x i32], [10 x i32]* %best_result_b, i32 0, i32 0
  %119 = load i32, i32* %k, align 4
  %idx.ext201 = sext i32 %119 to i64
  %add.ptr202 = getelementptr inbounds i32, i32* %arraydecay200, i64 %idx.ext201
  %arraydecay203 = getelementptr inbounds [10 x i32], [10 x i32]* %worst_result_a, i32 0, i32 0
  %120 = load i32, i32* %k, align 4
  %idx.ext204 = sext i32 %120 to i64
  %add.ptr205 = getelementptr inbounds i32, i32* %arraydecay203, i64 %idx.ext204
  call void @owl_analyze_semeai(i32 %117, i32 %118, i32* %add.ptr202, i32* %add.ptr205, i32* null, i32 1)
  %121 = load i32, i32* @debug, align 4
  %and206 = and i32 %121, 64
  %tobool207 = icmp ne i32 %and206, 0
  br i1 %tobool207, label %cond.false209, label %cond.true208

cond.true208:                                     ; preds = %if.end199
  br label %cond.end217

cond.false209:                                    ; preds = %if.end199
  %122 = load i32, i32* %k, align 4
  %idxprom210 = sext i32 %122 to i64
  %arrayidx211 = getelementptr inbounds [10 x i32], [10 x i32]* %best_result_b, i64 0, i64 %idxprom210
  %123 = load i32, i32* %arrayidx211, align 4
  %call212 = call i8* @safety_to_string(i32 %123)
  %124 = load i32, i32* %k, align 4
  %idxprom213 = sext i32 %124 to i64
  %arrayidx214 = getelementptr inbounds [10 x i32], [10 x i32]* %worst_result_a, i64 0, i64 %idxprom213
  %125 = load i32, i32* %arrayidx214, align 4
  %call215 = call i8* @safety_to_string(i32 %125)
  %call216 = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.4, i32 0, i32 0), i8* %call212, i8* %call215)
  br label %cond.end217

cond.end217:                                      ; preds = %cond.false209, %cond.true208
  %126 = load i32, i32* %b_best_status, align 4
  %cmp218 = icmp eq i32 %126, 0
  br i1 %cmp218, label %if.then227, label %lor.lhs.false219

lor.lhs.false219:                                 ; preds = %cond.end217
  %127 = load i32, i32* %b_best_status, align 4
  %cmp220 = icmp eq i32 %127, 3
  br i1 %cmp220, label %if.then227, label %lor.lhs.false221

lor.lhs.false221:                                 ; preds = %lor.lhs.false219
  %128 = load i32, i32* %b_best_status, align 4
  %cmp222 = icmp eq i32 %128, 7
  br i1 %cmp222, label %land.lhs.true223, label %if.end232

land.lhs.true223:                                 ; preds = %lor.lhs.false221
  %129 = load i32, i32* %k, align 4
  %idxprom224 = sext i32 %129 to i64
  %arrayidx225 = getelementptr inbounds [10 x i32], [10 x i32]* %best_result_b, i64 0, i64 %idxprom224
  %130 = load i32, i32* %arrayidx225, align 4
  %cmp226 = icmp eq i32 %130, 1
  br i1 %cmp226, label %if.then227, label %if.end232

if.then227:                                       ; preds = %land.lhs.true223, %lor.lhs.false219, %cond.end217
  %131 = load i32, i32* %k, align 4
  %idxprom228 = sext i32 %131 to i64
  %arrayidx229 = getelementptr inbounds [10 x i32], [10 x i32]* %best_result_b, i64 0, i64 %idxprom228
  %132 = load i32, i32* %arrayidx229, align 4
  store i32 %132, i32* %b_best_status, align 4
  %133 = load i32, i32* %k, align 4
  %idxprom230 = sext i32 %133 to i64
  %arrayidx231 = getelementptr inbounds [10 x i32], [10 x i32]* %worst_result_a, i64 0, i64 %idxprom230
  %134 = load i32, i32* %arrayidx231, align 4
  store i32 %134, i32* %a_worst_status, align 4
  br label %if.end232

if.end232:                                        ; preds = %if.then227, %land.lhs.true223, %lor.lhs.false221
  br label %if.end251

if.else:                                          ; preds = %if.end157
  %135 = load i32, i32* %a_status, align 4
  %cmp233 = icmp eq i32 %135, 2
  br i1 %cmp233, label %land.lhs.true234, label %if.end241

land.lhs.true234:                                 ; preds = %if.else
  %136 = load i32, i32* %k, align 4
  %idxprom235 = sext i32 %136 to i64
  %arrayidx236 = getelementptr inbounds [10 x i32], [10 x i32]* %best_result_a, i64 0, i64 %idxprom235
  %137 = load i32, i32* %arrayidx236, align 4
  %cmp237 = icmp ne i32 %137, 0
  br i1 %cmp237, label %if.then238, label %if.end241

if.then238:                                       ; preds = %land.lhs.true234
  %138 = load i32, i32* %k, align 4
  %idxprom239 = sext i32 %138 to i64
  %arrayidx240 = getelementptr inbounds [10 x i32], [10 x i32]* %move, i64 0, i64 %idxprom239
  %139 = load i32, i32* %arrayidx240, align 4
  %140 = load i32, i32* %apos, align 4
  call void @add_owl_defense_move(i32 %139, i32 %140, i32 5)
  br label %if.end241

if.end241:                                        ; preds = %if.then238, %land.lhs.true234, %if.else
  %141 = load i32, i32* %b_status, align 4
  %cmp242 = icmp eq i32 %141, 2
  br i1 %cmp242, label %land.lhs.true243, label %if.end250

land.lhs.true243:                                 ; preds = %if.end241
  %142 = load i32, i32* %k, align 4
  %idxprom244 = sext i32 %142 to i64
  %arrayidx245 = getelementptr inbounds [10 x i32], [10 x i32]* %worst_result_b, i64 0, i64 %idxprom244
  %143 = load i32, i32* %arrayidx245, align 4
  %cmp246 = icmp eq i32 %143, 0
  br i1 %cmp246, label %if.then247, label %if.end250

if.then247:                                       ; preds = %land.lhs.true243
  %144 = load i32, i32* %k, align 4
  %idxprom248 = sext i32 %144 to i64
  %arrayidx249 = getelementptr inbounds [10 x i32], [10 x i32]* %move, i64 0, i64 %idxprom248
  %145 = load i32, i32* %arrayidx249, align 4
  %146 = load i32, i32* %bpos, align 4
  call void @add_owl_attack_move(i32 %145, i32 %146, i32 5)
  br label %if.end250

if.end250:                                        ; preds = %if.then247, %land.lhs.true243, %if.end241
  br label %if.end251

if.end251:                                        ; preds = %if.end250, %if.end232
  br label %for.inc252

for.inc252:                                       ; preds = %if.end251, %if.then156, %if.then145, %if.then122, %if.then102, %if.then66
  %147 = load i32, i32* %k, align 4
  %inc253 = add nsw i32 %147, 1
  store i32 %inc253, i32* %k, align 4
  br label %for.cond33

for.end254:                                       ; preds = %for.cond33
  %148 = load i32, i32* %pass, align 4
  %cmp255 = icmp eq i32 %148, 0
  br i1 %cmp255, label %land.lhs.true256, label %if.end279

land.lhs.true256:                                 ; preds = %for.end254
  %149 = load i32, i32* %semeai_found, align 4
  %tobool257 = icmp ne i32 %149, 0
  br i1 %tobool257, label %if.then258, label %if.end279

if.then258:                                       ; preds = %land.lhs.true256
  %150 = load i32, i32* %a_best_status, align 4
  %cmp261 = icmp ne i32 %150, 0
  br i1 %cmp261, label %land.lhs.true262, label %if.else265

land.lhs.true262:                                 ; preds = %if.then258
  %151 = load i32, i32* %a_worst_status, align 4
  %cmp263 = icmp eq i32 %151, 0
  br i1 %cmp263, label %if.then264, label %if.else265

if.then264:                                       ; preds = %land.lhs.true262
  store i32 2, i32* %a_status259, align 4
  br label %if.end266

if.else265:                                       ; preds = %land.lhs.true262, %if.then258
  %152 = load i32, i32* %a_worst_status, align 4
  store i32 %152, i32* %a_status259, align 4
  br label %if.end266

if.end266:                                        ; preds = %if.else265, %if.then264
  %153 = load i32, i32* %b_best_status, align 4
  %cmp267 = icmp ne i32 %153, 0
  br i1 %cmp267, label %land.lhs.true268, label %if.else271

land.lhs.true268:                                 ; preds = %if.end266
  %154 = load i32, i32* %b_worst_status, align 4
  %cmp269 = icmp eq i32 %154, 0
  br i1 %cmp269, label %if.then270, label %if.else271

if.then270:                                       ; preds = %land.lhs.true268
  store i32 2, i32* %b_status260, align 4
  br label %if.end272

if.else271:                                       ; preds = %land.lhs.true268, %if.end266
  %155 = load i32, i32* %b_worst_status, align 4
  store i32 %155, i32* %b_status260, align 4
  br label %if.end272

if.end272:                                        ; preds = %if.else271, %if.then270
  %156 = load i32, i32* %a_status259, align 4
  store i32 %156, i32* %a_status259, align 4
  %157 = load i32, i32* %b_status260, align 4
  store i32 %157, i32* %b_status260, align 4
  %158 = load i32, i32* %a_status259, align 4
  %cmp273 = icmp eq i32 %158, 7
  br i1 %cmp273, label %if.then274, label %if.end275

if.then274:                                       ; preds = %if.end272
  store i32 1, i32* %a_status259, align 4
  br label %if.end275

if.end275:                                        ; preds = %if.then274, %if.end272
  %159 = load i32, i32* %b_status260, align 4
  %cmp276 = icmp eq i32 %159, 7
  br i1 %cmp276, label %if.then277, label %if.end278

if.then277:                                       ; preds = %if.end275
  store i32 1, i32* %b_status260, align 4
  br label %if.end278

if.end278:                                        ; preds = %if.then277, %if.end275
  %160 = load i32, i32* %apos, align 4
  %161 = load i32, i32* %a_status259, align 4
  %162 = load i32, i32* %a_status259, align 4
  call void @update_status(i32 %160, i32 %161, i32 %162)
  %163 = load i32, i32* %bpos, align 4
  %164 = load i32, i32* %b_status260, align 4
  %165 = load i32, i32* %b_status260, align 4
  call void @update_status(i32 %163, i32 %164, i32 %165)
  br label %if.end279

if.end279:                                        ; preds = %if.end278, %land.lhs.true256, %for.end254
  br label %for.inc280

for.inc280:                                       ; preds = %if.end279
  %166 = load i32, i32* %pass, align 4
  %inc281 = add nsw i32 %166, 1
  store i32 %inc281, i32* %pass, align 4
  br label %for.cond30

for.end282:                                       ; preds = %for.cond30
  br label %for.inc283

for.inc283:                                       ; preds = %for.end282, %if.then
  %167 = load i32, i32* %d1, align 4
  %inc284 = add nsw i32 %167, 1
  store i32 %inc284, i32* %d1, align 4
  br label %for.cond

for.end285:                                       ; preds = %for.cond
  ret void
}

declare void @owl_analyze_semeai(i32, i32, i32*, i32*, i32*, i32) #1

declare i8* @safety_to_string(i32) #1

declare void @add_owl_defense_move(i32, i32, i32) #1

declare void @add_owl_attack_move(i32, i32, i32) #1

; Function Attrs: noinline nounwind uwtable
define internal void @update_status(i32 %dr, i32 %new_status, i32 %new_safety) #0 {
entry:
  %dr.addr = alloca i32, align 4
  %new_status.addr = alloca i32, align 4
  %new_safety.addr = alloca i32, align 4
  %pos = alloca i32, align 4
  store i32 %dr, i32* %dr.addr, align 4
  store i32 %new_status, i32* %new_status.addr, align 4
  store i32 %new_safety, i32* %new_safety.addr, align 4
  %0 = load i32, i32* %dr.addr, align 4
  %idxprom = sext i32 %0 to i64
  %arrayidx = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom
  %status = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx, i32 0, i32 16
  %1 = load i32, i32* %status, align 4
  %2 = load i32, i32* %new_status.addr, align 4
  %cmp = icmp ne i32 %1, %2
  br i1 %cmp, label %land.lhs.true, label %if.end29

land.lhs.true:                                    ; preds = %entry
  %3 = load i32, i32* %dr.addr, align 4
  %idxprom1 = sext i32 %3 to i64
  %arrayidx2 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom1
  %status3 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx2, i32 0, i32 16
  %4 = load i32, i32* %status3, align 4
  %cmp4 = icmp ne i32 %4, 2
  br i1 %cmp4, label %if.then, label %lor.lhs.false

lor.lhs.false:                                    ; preds = %land.lhs.true
  %5 = load i32, i32* %new_status.addr, align 4
  %cmp5 = icmp ne i32 %5, 0
  br i1 %cmp5, label %if.then, label %if.end29

if.then:                                          ; preds = %lor.lhs.false, %land.lhs.true
  %6 = load i32, i32* @debug, align 4
  %and = and i32 %6, 64
  %tobool = icmp ne i32 %and, 0
  br i1 %tobool, label %cond.false, label %cond.true

cond.true:                                        ; preds = %if.then
  br label %cond.end

cond.false:                                       ; preds = %if.then
  %7 = load i32, i32* %dr.addr, align 4
  %8 = load i32, i32* %dr.addr, align 4
  %idxprom6 = sext i32 %8 to i64
  %arrayidx7 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom6
  %status8 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx7, i32 0, i32 16
  %9 = load i32, i32* %status8, align 4
  %call = call i8* @status_to_string(i32 %9)
  %10 = load i32, i32* %new_status.addr, align 4
  %call9 = call i8* @status_to_string(i32 %10)
  %call10 = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.5, i32 0, i32 0), i32 %7, i8* %call, i8* %call9)
  br label %cond.end

cond.end:                                         ; preds = %cond.false, %cond.true
  store i32 21, i32* %pos, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %cond.end
  %11 = load i32, i32* %pos, align 4
  %cmp11 = icmp slt i32 %11, 400
  br i1 %cmp11, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %12 = load i32, i32* %pos, align 4
  %idxprom12 = sext i32 %12 to i64
  %arrayidx13 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom12
  %13 = load i8, i8* %arrayidx13, align 1
  %conv = zext i8 %13 to i32
  %cmp14 = icmp eq i32 %conv, 1
  br i1 %cmp14, label %land.lhs.true22, label %lor.lhs.false16

lor.lhs.false16:                                  ; preds = %for.body
  %14 = load i32, i32* %pos, align 4
  %idxprom17 = sext i32 %14 to i64
  %arrayidx18 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom17
  %15 = load i8, i8* %arrayidx18, align 1
  %conv19 = zext i8 %15 to i32
  %cmp20 = icmp eq i32 %conv19, 2
  br i1 %cmp20, label %land.lhs.true22, label %if.end

land.lhs.true22:                                  ; preds = %lor.lhs.false16, %for.body
  %16 = load i32, i32* %dr.addr, align 4
  %17 = load i32, i32* %pos, align 4
  %call23 = call i32 @is_same_dragon(i32 %16, i32 %17)
  %tobool24 = icmp ne i32 %call23, 0
  br i1 %tobool24, label %if.then25, label %if.end

if.then25:                                        ; preds = %land.lhs.true22
  %18 = load i32, i32* %new_status.addr, align 4
  %19 = load i32, i32* %pos, align 4
  %idxprom26 = sext i32 %19 to i64
  %arrayidx27 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom26
  %status28 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx27, i32 0, i32 16
  store i32 %18, i32* %status28, align 4
  br label %if.end

if.end:                                           ; preds = %if.then25, %land.lhs.true22, %lor.lhs.false16
  br label %for.inc

for.inc:                                          ; preds = %if.end
  %20 = load i32, i32* %pos, align 4
  %inc = add nsw i32 %20, 1
  store i32 %inc, i32* %pos, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  br label %if.end29

if.end29:                                         ; preds = %for.end, %lor.lhs.false, %entry
  %21 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %22 = load i32, i32* %dr.addr, align 4
  %idxprom30 = sext i32 %22 to i64
  %arrayidx31 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom30
  %id = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx31, i32 0, i32 1
  %23 = load i32, i32* %id, align 4
  %idxprom32 = sext i32 %23 to i64
  %arrayidx33 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %21, i64 %idxprom32
  %safety = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx33, i32 0, i32 6
  %24 = load i32, i32* %safety, align 4
  %25 = load i32, i32* %new_safety.addr, align 4
  %cmp34 = icmp ne i32 %24, %25
  br i1 %cmp34, label %land.lhs.true36, label %if.end69

land.lhs.true36:                                  ; preds = %if.end29
  %26 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %27 = load i32, i32* %dr.addr, align 4
  %idxprom37 = sext i32 %27 to i64
  %arrayidx38 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom37
  %id39 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx38, i32 0, i32 1
  %28 = load i32, i32* %id39, align 4
  %idxprom40 = sext i32 %28 to i64
  %arrayidx41 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %26, i64 %idxprom40
  %safety42 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx41, i32 0, i32 6
  %29 = load i32, i32* %safety42, align 4
  %cmp43 = icmp ne i32 %29, 2
  br i1 %cmp43, label %if.then48, label %lor.lhs.false45

lor.lhs.false45:                                  ; preds = %land.lhs.true36
  %30 = load i32, i32* %new_safety.addr, align 4
  %cmp46 = icmp ne i32 %30, 0
  br i1 %cmp46, label %if.then48, label %if.end69

if.then48:                                        ; preds = %lor.lhs.false45, %land.lhs.true36
  %31 = load i32, i32* @debug, align 4
  %and49 = and i32 %31, 64
  %tobool50 = icmp ne i32 %and49, 0
  br i1 %tobool50, label %cond.false52, label %cond.true51

cond.true51:                                      ; preds = %if.then48
  br label %cond.end62

cond.false52:                                     ; preds = %if.then48
  %32 = load i32, i32* %dr.addr, align 4
  %33 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %34 = load i32, i32* %dr.addr, align 4
  %idxprom53 = sext i32 %34 to i64
  %arrayidx54 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom53
  %id55 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx54, i32 0, i32 1
  %35 = load i32, i32* %id55, align 4
  %idxprom56 = sext i32 %35 to i64
  %arrayidx57 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %33, i64 %idxprom56
  %safety58 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx57, i32 0, i32 6
  %36 = load i32, i32* %safety58, align 4
  %call59 = call i8* @safety_to_string(i32 %36)
  %37 = load i32, i32* %new_safety.addr, align 4
  %call60 = call i8* @safety_to_string(i32 %37)
  %call61 = call i32 (i8*, ...) @gprintf(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.6, i32 0, i32 0), i32 %32, i8* %call59, i8* %call60)
  br label %cond.end62

cond.end62:                                       ; preds = %cond.false52, %cond.true51
  %38 = load i32, i32* %new_safety.addr, align 4
  %39 = load %struct.dragon_data2*, %struct.dragon_data2** @dragon2, align 8
  %40 = load i32, i32* %dr.addr, align 4
  %idxprom63 = sext i32 %40 to i64
  %arrayidx64 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom63
  %id65 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx64, i32 0, i32 1
  %41 = load i32, i32* %id65, align 4
  %idxprom66 = sext i32 %41 to i64
  %arrayidx67 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %39, i64 %idxprom66
  %safety68 = getelementptr inbounds %struct.dragon_data2, %struct.dragon_data2* %arrayidx67, i32 0, i32 6
  store i32 %38, i32* %safety68, align 4
  br label %if.end69

if.end69:                                         ; preds = %cond.end62, %lor.lhs.false45, %if.end29
  ret void
}

declare i8* @status_to_string(i32) #1

declare i32 @is_same_dragon(i32, i32) #1

declare i32 @owl_does_attack(i32, i32, i32*) #1

declare i32 @owl_does_defend(i32, i32, i32*) #1

declare i32 @chainlinks(i32, i32*) #1

declare i32 @owl_substantial(i32) #1

; Function Attrs: noinline nounwind uwtable
define internal i32 @liberty_of_dragon(i32 %pos, i32 %origin) #0 {
entry:
  %retval = alloca i32, align 4
  %pos.addr = alloca i32, align 4
  %origin.addr = alloca i32, align 4
  store i32 %pos, i32* %pos.addr, align 4
  store i32 %origin, i32* %origin.addr, align 4
  %0 = load i32, i32* %pos.addr, align 4
  %cmp = icmp eq i32 %0, 0
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4
  br label %return

if.end:                                           ; preds = %entry
  %1 = load i32, i32* %pos.addr, align 4
  %idxprom = sext i32 %1 to i64
  %arrayidx = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom
  %2 = load i8, i8* %arrayidx, align 1
  %conv = zext i8 %2 to i32
  %cmp1 = icmp ne i32 %conv, 0
  br i1 %cmp1, label %if.then3, label %if.end4

if.then3:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4
  br label %return

if.end4:                                          ; preds = %if.end
  %3 = load i32, i32* %pos.addr, align 4
  %add = add nsw i32 %3, 20
  %idxprom5 = sext i32 %add to i64
  %arrayidx6 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom5
  %4 = load i8, i8* %arrayidx6, align 1
  %conv7 = zext i8 %4 to i32
  %cmp8 = icmp ne i32 %conv7, 3
  br i1 %cmp8, label %land.lhs.true, label %lor.lhs.false

land.lhs.true:                                    ; preds = %if.end4
  %5 = load i32, i32* %pos.addr, align 4
  %add10 = add nsw i32 %5, 20
  %idxprom11 = sext i32 %add10 to i64
  %arrayidx12 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom11
  %origin13 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx12, i32 0, i32 2
  %6 = load i32, i32* %origin13, align 4
  %7 = load i32, i32* %origin.addr, align 4
  %cmp14 = icmp eq i32 %6, %7
  br i1 %cmp14, label %if.then56, label %lor.lhs.false

lor.lhs.false:                                    ; preds = %land.lhs.true, %if.end4
  %8 = load i32, i32* %pos.addr, align 4
  %sub = sub nsw i32 %8, 1
  %idxprom16 = sext i32 %sub to i64
  %arrayidx17 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom16
  %9 = load i8, i8* %arrayidx17, align 1
  %conv18 = zext i8 %9 to i32
  %cmp19 = icmp ne i32 %conv18, 3
  br i1 %cmp19, label %land.lhs.true21, label %lor.lhs.false28

land.lhs.true21:                                  ; preds = %lor.lhs.false
  %10 = load i32, i32* %pos.addr, align 4
  %sub22 = sub nsw i32 %10, 1
  %idxprom23 = sext i32 %sub22 to i64
  %arrayidx24 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom23
  %origin25 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx24, i32 0, i32 2
  %11 = load i32, i32* %origin25, align 4
  %12 = load i32, i32* %origin.addr, align 4
  %cmp26 = icmp eq i32 %11, %12
  br i1 %cmp26, label %if.then56, label %lor.lhs.false28

lor.lhs.false28:                                  ; preds = %land.lhs.true21, %lor.lhs.false
  %13 = load i32, i32* %pos.addr, align 4
  %sub29 = sub nsw i32 %13, 20
  %idxprom30 = sext i32 %sub29 to i64
  %arrayidx31 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom30
  %14 = load i8, i8* %arrayidx31, align 1
  %conv32 = zext i8 %14 to i32
  %cmp33 = icmp ne i32 %conv32, 3
  br i1 %cmp33, label %land.lhs.true35, label %lor.lhs.false42

land.lhs.true35:                                  ; preds = %lor.lhs.false28
  %15 = load i32, i32* %pos.addr, align 4
  %sub36 = sub nsw i32 %15, 20
  %idxprom37 = sext i32 %sub36 to i64
  %arrayidx38 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom37
  %origin39 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx38, i32 0, i32 2
  %16 = load i32, i32* %origin39, align 4
  %17 = load i32, i32* %origin.addr, align 4
  %cmp40 = icmp eq i32 %16, %17
  br i1 %cmp40, label %if.then56, label %lor.lhs.false42

lor.lhs.false42:                                  ; preds = %land.lhs.true35, %lor.lhs.false28
  %18 = load i32, i32* %pos.addr, align 4
  %add43 = add nsw i32 %18, 1
  %idxprom44 = sext i32 %add43 to i64
  %arrayidx45 = getelementptr inbounds [421 x i8], [421 x i8]* @board, i64 0, i64 %idxprom44
  %19 = load i8, i8* %arrayidx45, align 1
  %conv46 = zext i8 %19 to i32
  %cmp47 = icmp ne i32 %conv46, 3
  br i1 %cmp47, label %land.lhs.true49, label %if.end57

land.lhs.true49:                                  ; preds = %lor.lhs.false42
  %20 = load i32, i32* %pos.addr, align 4
  %add50 = add nsw i32 %20, 1
  %idxprom51 = sext i32 %add50 to i64
  %arrayidx52 = getelementptr inbounds [400 x %struct.dragon_data], [400 x %struct.dragon_data]* @dragon, i64 0, i64 %idxprom51
  %origin53 = getelementptr inbounds %struct.dragon_data, %struct.dragon_data* %arrayidx52, i32 0, i32 2
  %21 = load i32, i32* %origin53, align 4
  %22 = load i32, i32* %origin.addr, align 4
  %cmp54 = icmp eq i32 %21, %22
  br i1 %cmp54, label %if.then56, label %if.end57

if.then56:                                        ; preds = %land.lhs.true49, %land.lhs.true35, %land.lhs.true21, %land.lhs.true
  store i32 1, i32* %retval, align 4
  br label %return

if.end57:                                         ; preds = %land.lhs.true49, %lor.lhs.false42
  store i32 0, i32* %retval, align 4
  br label %return

return:                                           ; preds = %if.end57, %if.then56, %if.then3, %if.then
  %23 = load i32, i32* %retval, align 4
  ret i32 %23
}

declare i32 @liberty_of_string(i32, i32) #1

declare i32 @min_eyes(%struct.eyevalue*) #1

; Function Attrs: noinline nounwind uwtable
define internal void @add_appropriate_semeai_moves(i32 %move, i32 %my_dragon, i32 %your_dragon, i32 %my_status, i32 %your_status, i32 %margin_of_safety) #0 {
entry:
  %move.addr = alloca i32, align 4
  %my_dragon.addr = alloca i32, align 4
  %your_dragon.addr = alloca i32, align 4
  %my_status.addr = alloca i32, align 4
  %your_status.addr = alloca i32, align 4
  %margin_of_safety.addr = alloca i32, align 4
  store i32 %move, i32* %move.addr, align 4
  store i32 %my_dragon, i32* %my_dragon.addr, align 4
  store i32 %your_dragon, i32* %your_dragon.addr, align 4
  store i32 %my_status, i32* %my_status.addr, align 4
  store i32 %your_status, i32* %your_status.addr, align 4
  store i32 %margin_of_safety, i32* %margin_of_safety.addr, align 4
  %0 = load i32, i32* %my_status.addr, align 4
  %cmp = icmp eq i32 %0, 2
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %move.addr, align 4
  %2 = load i32, i32* %my_dragon.addr, align 4
  call void @add_semeai_move(i32 %1, i32 %2)
  br label %if.end3

if.else:                                          ; preds = %entry
  %3 = load i32, i32* %margin_of_safety.addr, align 4
  %cmp1 = icmp eq i32 %3, 1
  br i1 %cmp1, label %if.then2, label %if.end

if.then2:                                         ; preds = %if.else
  %4 = load i32, i32* %move.addr, align 4
  %5 = load i32, i32* %my_dragon.addr, align 4
  call void @add_semeai_threat(i32 %4, i32 %5)
  br label %if.end

if.end:                                           ; preds = %if.then2, %if.else
  br label %if.end3

if.end3:                                          ; preds = %if.end, %if.then
  %6 = load i32, i32* %your_status.addr, align 4
  %cmp4 = icmp eq i32 %6, 2
  br i1 %cmp4, label %if.then5, label %if.else6

if.then5:                                         ; preds = %if.end3
  %7 = load i32, i32* %move.addr, align 4
  %8 = load i32, i32* %your_dragon.addr, align 4
  call void @add_semeai_move(i32 %7, i32 %8)
  br label %if.end10

if.else6:                                         ; preds = %if.end3
  %9 = load i32, i32* %margin_of_safety.addr, align 4
  %cmp7 = icmp eq i32 %9, 1
  br i1 %cmp7, label %if.then8, label %if.end9

if.then8:                                         ; preds = %if.else6
  %10 = load i32, i32* %move.addr, align 4
  %11 = load i32, i32* %your_dragon.addr, align 4
  call void @add_semeai_threat(i32 %10, i32 %11)
  br label %if.end9

if.end9:                                          ; preds = %if.then8, %if.else6
  br label %if.end10

if.end10:                                         ; preds = %if.end9, %if.then5
  ret void
}

declare i32 @eye_move_urgency(%struct.eyevalue*) #1

declare i32 @safe_move(i32, i32) #1

declare void @add_semeai_move(i32, i32) #1

declare void @add_semeai_threat(i32, i32) #1

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 5.0.0 "}
