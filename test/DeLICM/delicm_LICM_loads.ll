; RUN: opt %loadPolly -polly-scops -analyze < %s | FileCheck %s
;
;    void func(int n, double A[static const restrict n], int m, double B[static const restrict n], double C[static const restrict n]) {
;      for (int j = 0; j < n; j += 1) { /* parallel loop */
;        B[j] = A[j];
;        double red = A[j];
;        red += 5.1;
;        for (int i = 0; i < m; i += 1) /* reduction loop */
;          red += 4.2;
;        A[j] = red;
;        C[j] = A[j];
;    }

; Value of A[j] used, outside of reduction
; Possible difficulties:
; - Distinguish from case where uses of A[j] is between the reduction initial load and writeback.

define void @func(i32 %n, double* noalias nonnull %A, i32 %m, double* noalias nonnull %B, double* noalias nonnull %C) {
entry:
  br label %parallel.for

parallel.for:
  %j = phi i32 [0, %entry], [%j.inc, %parallel.inc]
  %arrayidx = getelementptr inbounds double, double* %A, i32 %j
  %arrayidxB = getelementptr inbounds double, double* %B, i32 %j
  %arrayidxC = getelementptr inbounds double, double* %C, i32 %j
  %ld = load double, double* %arrayidx
  %prep = fadd double %ld, 5.1
  store double %ld, double* %arrayidxB
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
  store double %phi, double* %arrayidxC
  %j.inc = add nuw nsw i32 %j, 1
  br label %parallel.for

return:
  ret void
}


