; RUN: opt %loadPolly -basicaa -sroa -instcombine -simplifycfg -tailcallopt \
; RUN:    -simplifycfg -reassociate -loop-rotate -instcombine -indvars \
; RUN:    -polly-prepare -polly-delicm -analyze < %s \
; RUN:    \
; RUN:     | FileCheck %s --check-prefix=NOLICM
;
; RUN: opt %loadPolly -basicaa -sroa -instcombine -simplifycfg -tailcallopt \
; RUN:    -simplifycfg -reassociate -loop-rotate -instcombine -indvars -licm \
; RUN:    -polly-prepare -polly-delicm -analyze < %s \
; RUN:    \
; RUN:     | FileCheck %s --check-prefix=LICM
;
;    void foo(int n, float A[static const restrict n], float x) {
;      //      (0)
;      for (int i = 0; i < 5; i += 1) {
;        for (int j = 0; j < n; j += 1) {
;          x = 7; // (1)
;        }
;        A[0] = x; // (3)
;      }
;      // (4)
;    }



target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"

define void @foo(i32 %n, float* noalias nonnull %A, float %x) {
entry:
  %n.addr = alloca i32, align 4
  %A.addr = alloca float*, align 8
  %x.addr = alloca float, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  store i32 %n, i32* %n.addr, align 4
  store float* %A, float** %A.addr, align 8
  store float %x, float* %x.addr, align 4
  %tmp = load i32, i32* %n.addr, align 4
  %tmp1 = zext i32 %tmp to i64
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc.4, %entry
  %tmp2 = load i32, i32* %i, align 4
  %cmp = icmp slt i32 %tmp2, 5
  br i1 %cmp, label %for.body, label %for.end.6

for.body:                                         ; preds = %for.cond
  store i32 0, i32* %j, align 4
  br label %for.cond.1

for.cond.1:                                       ; preds = %for.inc, %for.body
  %tmp3 = load i32, i32* %j, align 4
  %tmp4 = load i32, i32* %n.addr, align 4
  %cmp2 = icmp slt i32 %tmp3, %tmp4
  br i1 %cmp2, label %for.body.3, label %for.end

for.body.3:                                       ; preds = %for.cond.1
  store float 7.000000e+00, float* %x.addr, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body.3
  %tmp5 = load i32, i32* %j, align 4
  %add = add nsw i32 %tmp5, 1
  store i32 %add, i32* %j, align 4
  br label %for.cond.1

for.end:                                          ; preds = %for.cond.1
  %tmp6 = load float, float* %x.addr, align 4
  %tmp7 = load float*, float** %A.addr, align 8
  %arrayidx = getelementptr inbounds float, float* %tmp7, i64 0
  store float %tmp6, float* %arrayidx, align 4
  br label %for.inc.4

for.inc.4:                                        ; preds = %for.end
  %tmp8 = load i32, i32* %i, align 4
  %add5 = add nsw i32 %tmp8, 1
  store i32 %add5, i32* %i, align 4
  br label %for.cond

for.end.6:                                        ; preds = %for.cond
  ret void
}

; CHECK: Statements {
; CHECK:     Stmt_for_end
; CHECK: }


; NOLICM:      Original zone:
; NOLICM-NEXT:     Lifetime: [n] -> { [MemRef_A[0] -> [i1, i2, i3{{\]\]}} -> [Stmt_for_end[4] -> Val_x_addr_1_lcssa[{{\]\]}} : i1 >= 5; [MemRef_A[0] -> [4, i2, i3{{\]\]}} -> [Stmt_for_end[4] -> Val_x_addr_1_lcssa[{{\]\]}} : i2 >= 3; [MemRef_A[0] -> [4, 2, i3{{\]\]}} -> [Stmt_for_end[4] -> Val_x_addr_1_lcssa[{{\]\]}} : i3 > 0; [MemRef_A[0] -> [i1, i2, i3{{\]\]}} -> Undef[] : i1 <= 4 and (i1 <= 3 or (i1 >= 0 and i2 <= 1)); [MemRef_A[0] -> [i1, 2, i3{{\]\]}} -> Undef[] : 0 <= i1 <= 4 and i3 <= 0 } + Unknown
; NOLICM-NEXT:     Written : [n] -> { [MemRef_A[0] -> [i1, 2, 0{{\]\]}} -> [Stmt_for_end[i1] -> Val_x_addr_1_lcssa[{{\]\]}} : 0 <= i1 <= 4 }
; NOLICM:      Mapped scalars {
; NOLICM-NEXT: }
; NOLICM:      After zone:
; NOLICM-NEXT:     Lifetime: [n] -> { [MemRef_A[0] -> [i1, i2, i3{{\]\]}} -> [Stmt_for_end[4] -> Val_x_addr_1_lcssa[{{\]\]}} : i1 >= 5; [MemRef_A[0] -> [4, i2, i3{{\]\]}} -> [Stmt_for_end[4] -> Val_x_addr_1_lcssa[{{\]\]}} : i2 >= 3; [MemRef_A[0] -> [4, 2, i3{{\]\]}} -> [Stmt_for_end[4] -> Val_x_addr_1_lcssa[{{\]\]}} : i3 > 0; [MemRef_A[0] -> [i1, i2, i3{{\]\]}} -> Undef[] : i1 <= 4 and (i1 <= 3 or (i1 >= 0 and i2 <= 1)); [MemRef_A[0] -> [i1, 2, i3{{\]\]}} -> Undef[] : 0 <= i1 <= 4 and i3 <= 0 } + Unknown
; NOLICM-NEXT:     Written : [n] -> { [MemRef_A[0] -> [i1, 2, 0{{\]\]}} -> [Stmt_for_end[i1] -> Val_x_addr_1_lcssa[{{\]\]}} : 0 <= i1 <= 4 }
; NOLICM:      After Statements {
; NOLICM-NEXT:     Stmt_for_cond_1_preheader
; NOLICM-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; NOLICM-NEXT:                 [n] -> { Stmt_for_cond_1_preheader[i0] -> MemRef_x_addr_04__phi[] };
; NOLICM-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; NOLICM-NEXT:                 [n] -> { Stmt_for_cond_1_preheader[i0] -> MemRef_x_addr_1__phi[] };
; NOLICM-NEXT:     Stmt_for_cond_1
; NOLICM-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; NOLICM-NEXT:                 [n] -> { Stmt_for_cond_1[i0, i1] -> MemRef_x_addr_1__phi[] };
; NOLICM-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; NOLICM-NEXT:                 [n] -> { Stmt_for_cond_1[i0, i1] -> MemRef_x_addr_1__phi[] };
; NOLICM-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; NOLICM-NEXT:                 [n] -> { Stmt_for_cond_1[i0, i1] -> MemRef_x_addr_1_lcssa__phi[] };
; NOLICM-NEXT:     Stmt_for_end
; NOLICM-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; NOLICM-NEXT:                 [n] -> { Stmt_for_end[i0] -> MemRef_x_addr_04__phi[] };
; NOLICM-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; NOLICM-NEXT:                 [n] -> { Stmt_for_end[i0] -> MemRef_x_addr_1_lcssa__phi[] };
; NOLICM-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; NOLICM-NEXT:                 [n] -> { Stmt_for_end[i0] -> MemRef_A[0] };
; NOLICM-NEXT: }

; LICM:      Original zone:
; LICM-NEXT:     Lifetime: [n] -> {  } + Unknown
; LICM-NEXT:     Written : [n] -> {  }
; LICM:      Mapped scalars {
; LICM-NEXT: }
; LICM:      After zone:
; LICM-NEXT:     Lifetime: [n] -> {  } + Unknown
; LICM-NEXT:     Written : [n] -> {  }
; LICM:      After Statements {
; LICM-NEXT:     Stmt_for_cond_1_preheader
; LICM-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; LICM-NEXT:                 [n] -> { Stmt_for_cond_1_preheader[i0] -> MemRef_x_addr_04__phi[] };
; LICM-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; LICM-NEXT:                 [n] -> { Stmt_for_cond_1_preheader[i0] -> MemRef_x_addr_1__phi[] };
; LICM-NEXT:     Stmt_for_cond_1
; LICM-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; LICM-NEXT:                 [n] -> { Stmt_for_cond_1[i0, i1] -> MemRef_x_addr_1__phi[] };
; LICM-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; LICM-NEXT:                 [n] -> { Stmt_for_cond_1[i0, i1] -> MemRef_x_addr_1__phi[] };
; LICM-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; LICM-NEXT:                 [n] -> { Stmt_for_cond_1[i0, i1] -> MemRef_x_addr_1_lcssa__phi[] };
; LICM-NEXT:     Stmt_for_end
; LICM-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; LICM-NEXT:                 [n] -> { Stmt_for_end[i0] -> MemRef_x_addr_04__phi[] };
; LICM-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; LICM-NEXT:                 [n] -> { Stmt_for_end[i0] -> MemRef_x_addr_1_lcssa__phi[] };
; LICM-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 1]
; LICM-NEXT:                 [n] -> { Stmt_for_end[i0] -> MemRef_x_addr_1_lcssa[] };
; LICM-NEXT: }
