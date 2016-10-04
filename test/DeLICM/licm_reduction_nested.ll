; RUN: opt %loadPolly -basicaa -loop-rotate -indvars       -polly-prepare -polly-scops -analyze < %s | FileCheck %s
; RUN: opt %loadPolly -basicaa -loop-rotate -indvars -licm -polly-prepare -polly-scops -analyze < %s | FileCheck %s
;
; XFAIL: *
;
; Even ScopDetection fails here after LICM because of PHI in exit node.
;
;    void foo(unsigned long *restrict A, unsigned long *restrict B,
;             unsigned long j) {
;      for (unsigned long i = 0; i < 100; i++)
;        for (unsigned long k = 0; k < 100; k++)
;          A[j] += B[i + k];
;    }
;
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"

define void @foo(i64* noalias %A, i64* noalias %B, i64 %j) {
entry:
  br label %for.cond

for.cond:                                         ; preds = %for.inc.6, %entry
  %i.0 = phi i64 [ 0, %entry ], [ %inc7, %for.inc.6 ]
  %exitcond1 = icmp ne i64 %i.0, 100
  br i1 %exitcond1, label %for.body, label %for.end.8

for.body:                                         ; preds = %for.cond
  br label %for.cond.1

for.cond.1:                                       ; preds = %for.inc, %for.body
  %k.0 = phi i64 [ 0, %for.body ], [ %inc, %for.inc ]
  %exitcond = icmp ne i64 %k.0, 100
  br i1 %exitcond, label %for.body.3, label %for.end

for.body.3:                                       ; preds = %for.cond.1
  %add = add nuw nsw i64 %i.0, %k.0
  %arrayidx = getelementptr inbounds i64, i64* %B, i64 %add
  %tmp = load i64, i64* %arrayidx, align 8
  %arrayidx4 = getelementptr inbounds i64, i64* %A, i64 %j
  %tmp2 = load i64, i64* %arrayidx4, align 8
  %add5 = add i64 %tmp2, %tmp
  store i64 %add5, i64* %arrayidx4, align 8
  br label %for.inc

for.inc:                                          ; preds = %for.body.3
  %inc = add nuw nsw i64 %k.0, 1
  br label %for.cond.1

for.end:                                          ; preds = %for.cond.1
  br label %for.inc.6

for.inc.6:                                        ; preds = %for.end
  %inc7 = add nuw nsw i64 %i.0, 1
  br label %for.cond

for.end.8:                                        ; preds = %for.cond
  ret void
}


; CHECK:      Printing analysis 'Basic Alias Analysis (stateless AA impl)' for function 'foo':
; CHECK-NEXT: Pass::print not implemented for pass: 'Basic Alias Analysis (stateless AA impl)'!
; CHECK-NEXT: Printing analysis 'Rotate Loops':
; CHECK-NEXT: Pass::print not implemented for pass: 'Rotate Loops'!
; CHECK-NEXT: Printing analysis 'Induction Variable Simplification':
; CHECK-NEXT: Pass::print not implemented for pass: 'Induction Variable Simplification'!
; CHECK-NEXT: Printing analysis 'Rotate Loops':
; CHECK-NEXT: Pass::print not implemented for pass: 'Rotate Loops'!
; CHECK-NEXT: Printing analysis 'Induction Variable Simplification':
; CHECK-NEXT: Pass::print not implemented for pass: 'Induction Variable Simplification'!
; CHECK-NEXT: Printing analysis 'Polly - Prepare code for polly' for function 'foo':
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'for.body.3 => for.end' in function 'foo':
; CHECK-NEXT: Invalid Scop!
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'for.body => for.end.8' in function 'foo':
; CHECK-NEXT:     Function: foo
; CHECK-NEXT:     Region: %for.body---%for.end.8
; CHECK-NEXT:     Max Loop Depth:  2
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
; CHECK-NEXT:         i64 MemRef_B[*]; // Element size 8
; CHECK-NEXT:         i64 MemRef_A[*]; // Element size 8
; CHECK-NEXT:     }
; CHECK-NEXT:     Arrays (Bounds as pw_affs) {
; CHECK-NEXT:         i64 MemRef_B[*]; // Element size 8
; CHECK-NEXT:         i64 MemRef_A[*]; // Element size 8
; CHECK-NEXT:     }
; CHECK-NEXT:     Alias Groups (0):
; CHECK-NEXT:         n/a
; CHECK-NEXT:     Statements {
; CHECK-NEXT:         Stmt_for_body_3
; CHECK-NEXT:             Domain :=
; CHECK-NEXT:                 [j] -> { Stmt_for_body_3[i0, i1] : 0 <= i0 <= 99 and 0 <= i1 <= 99 };
; CHECK-NEXT:             Schedule :=
; CHECK-NEXT:                 [j] -> { Stmt_for_body_3[i0, i1] -> [i0, i1] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 [j] -> { Stmt_for_body_3[i0, i1] -> MemRef_B[i0 + i1] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: +] [Scalar: 0]
; CHECK-NEXT:                 [j] -> { Stmt_for_body_3[i0, i1] -> MemRef_A[j] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: +] [Scalar: 0]
; CHECK-NEXT:                 [j] -> { Stmt_for_body_3[i0, i1] -> MemRef_A[j] };
; CHECK-NEXT:     }
; CHECK-NEXT: Printing analysis 'Polly - Create polyhedral description of Scops' for region: 'entry => <Function Return>' in function 'foo':
; CHECK-NEXT: Invalid Scop!
