; RUN: opt %loadPolly -polly-scops -analyze < %s | FileCheck %s
;
;    void func(int n, double A[static const restrict n], int m, int k) {
;      for (int j = 0; j < n; j += 1) { /* parallel loop */
;        A[k] = 2.1;
;        double red = A[j];
;        for (int i = 0; i < m; i += 1) /* reduction loop */
;          red += 4.2;
;        A[j] = red;
;        A[k] = 2.3;
;    }

; %arraidx possibly overwritten, but not in anything relevant for the reduction
; Possible difficulties:
; - Store of 2.1 might overwrite A[j] if order reversed in %parallel.for (distinguish the two cases)
; - Store of 2.3 might overwrite A[j]; distinguish from case where order is reversed in %parallel.inc

define void @func(i32 %n, double* noalias nonnull %A, i32 %m, i32 %k) {
entry:
  br label %parallel.for

parallel.for:
  %j = phi i32 [0, %entry], [%j.inc, %parallel.inc]
  %arrayidxk = getelementptr inbounds double, double* %A, i32 %k
  store double 2.1, double* %arrayidxk
  %arrayidx = getelementptr inbounds double, double* %A, i32 %j
  %ld = load double, double* %arrayidx
  %j.cmp = icmp slt i32 %j, %n
  br i1 %j.cmp, label %reduction.for, label %return

reduction.for:
  %i = phi i32 [0, %parallel.for], [%i.inc, %reduction.inc]
  %phi = phi double [%ld, %parallel.for], [%add, %reduction.inc]
  %i.cmp = icmp slt i32 %i, %m
  br i1 %i.cmp, label %body, label %parallel.inc

body:
  %add = fadd double %phi, 4.2
  br label %reduction.inc

reduction.inc:
  %i.inc = add nuw nsw i32 %i, 1
  br label %reduction.for

parallel.inc:
  store double %phi, double* %arrayidx
  store double 2.3, double* %arrayidxk
  %j.inc = add nuw nsw i32 %j, 1
  br label %parallel.for

return:
  ret void
}


