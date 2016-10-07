; RUN: opt %loadPolly -basicaa -loop-rotate -indvars       -polly-prepare -polly-scops -analyze < %s | FileCheck %s --check-prefix=NOLICM
; RUN: opt %loadPolly -basicaa -loop-rotate -indvars -licm -polly-prepare -polly-scops -analyze < %s | FileCheck %s --check-prefix=LICM
;
; XFAIL: *
;
;    void foo(float *restrict A, float *restrict B, long j) {
;      for (long i = 0; i < 100; i++)
;        A[j] = B[i];
;    }
;
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"

define void @foo(float* noalias %A, float* noalias %B, i64 %j) {
entry:
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %i.0 = phi i64 [ 0, %entry ], [ %inc, %for.inc ]
  %exitcond = icmp ne i64 %i.0, 100
  br i1 %exitcond, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %arrayidx = getelementptr inbounds float, float* %B, i64 %i.0
  %tmp = bitcast float* %arrayidx to i32*
  %tmp1 = load i32, i32* %tmp, align 4
  %arrayidx1 = getelementptr inbounds float, float* %A, i64 %j
  %tmp2 = bitcast float* %arrayidx1 to i32*
  store i32 %tmp1, i32* %tmp2, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %inc = add nuw nsw i64 %i.0, 1
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret void
}

; CHECK:      Printing analysis 'Basic Alias Analysis (stateless AA impl)' for function 'foo':
; CHECK-NEXT: Pass::print not implemented for pass: 'Basic Alias Analysis (stateless AA impl)'!
; CHECK-NEXT: Printing analysis 'Rotate Loops':
; CHECK-NEXT: Pass::print not implemented for pass: 'Rotate Loops'!
; CHECK-NEXT: Printing analysis 'Induction Variable Simplification':
; CHECK-NEXT: Pass::print not implemented for pass: 'Induction Variable Simplification'!
; CHECK-NEXT: Printing analysis 'Polly - Prepare code for polly' for function 'foo':
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'for.body => for.end' in function 'foo':
; CHECK-NEXT:     Function: foo
; CHECK-NEXT:     Region: %for.body---%for.end
; CHECK-NEXT:     Max Loop Depth:  1
; CHECK-NEXT:     Invariant Accesses: {
; CHECK-NEXT:     }
; CHECK-NEXT:     Context:
; CHECK-NEXT:     [j] -> {  : -9223372036854775808 <= j <= 9223372036854775807 }
; CHECK-NEXT:     Assumed Context:
; CHECK-NEXT:     [j] -> {  :  }
; CHECK-NEXT:     Invalid Context:
; CHECK-NEXT:     [j] -> {  : 1 = 0 }
; CHECK-NEXT:     p0: %j
; CHECK-NEXT:     Arrays {
; CHECK-NEXT:         i32 MemRef_B[*]; // Element size 4
; CHECK-NEXT:         i32 MemRef_A[*]; // Element size 4
; CHECK-NEXT:     }
; CHECK-NEXT:     Arrays (Bounds as pw_affs) {
; CHECK-NEXT:         i32 MemRef_B[*]; // Element size 4
; CHECK-NEXT:         i32 MemRef_A[*]; // Element size 4
; CHECK-NEXT:     }
; CHECK-NEXT:     Alias Groups (0):
; CHECK-NEXT:         n/a
; CHECK-NEXT:     Statements {
; CHECK-NEXT:         Stmt_for_body
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [j] -> { Stmt_for_body[i0] : 0 <= i0 <= 99 };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [j] -> { Stmt_for_body[i0] -> [i0] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [j] -> { Stmt_for_body[i0] -> MemRef_B[i0] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [j] -> { Stmt_for_body[i0] -> MemRef_A[j] };
; CHECK-NEXT:     }
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'entry => <Function Return>' in function 'foo':
; CHECK-NEXT: Invalid Scop!
