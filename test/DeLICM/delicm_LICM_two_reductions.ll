; RUN: opt %loadPolly -polly-scops -analyze < %s | FileCheck %s
;
;    void func(int n, double A[static const restrict n], int m) {
;      for (int j = 0; j < n; j += 1) { /* parallel loop */
;        double red1 = A[j];
;        double red2 = 0.0;
;        for (int i = 0; i < m; i += 1) { /* reduction loop */
;          red1 += 4.2;
;          red2 += 2.4;
;        }
;        A[j] = red1 + red2;
;    }

; Two reductions in the same loop 
; Possible difficulties:
; - Cannot use same %arraryidx for same loop-carried phi; must identify situation and choose one.
; - If doing global analysis first, must somehow mark already used %arrayidx to avoid use by other reduction
; - If transforming while doing analysis, analysis for second phi must work on updated MemoryAccesses

define void @func(i32 %n, double* noalias nonnull %A, i32 %m) {
entry:
  br label %parallel.for

parallel.for:
  %j = phi i32 [0, %entry], [%j.inc, %parallel.inc]
  %arrayidx = getelementptr inbounds double, double* %A, i32 %j
  %ld = load double, double* %arrayidx
  %j.cmp = icmp slt i32 %j, %n
  br i1 %j.cmp, label %reduction.for, label %return

reduction.for:
  %i = phi i32 [0, %parallel.for], [%i.inc, %reduction.inc]
  %phi1 = phi double [%ld, %parallel.for], [%add1, %reduction.inc]
  %phi2 = phi double [0.0, %parallel.for], [%add2, %reduction.inc]
  %i.cmp = icmp slt i32 %i, %m
  br i1 %i.cmp, label %body, label %parallel.inc

body:
  %add1 = fadd double %phi1, 4.2
  %add2 = fadd double %phi2, 2.4
  br label %reduction.inc

reduction.inc:
  %i.inc = add nuw nsw i32 %i, 1
  br label %reduction.for

parallel.inc:
  %sum = fadd double %phi1, %phi2
  store double %sum, double* %arrayidx
  %j.inc = add nuw nsw i32 %j, 1
  br label %parallel.for

return:
  ret void
}


