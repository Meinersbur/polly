; RUN: opt %loadPolly -polly-scops -analyze < %s | FileCheck %s
;
;    void func(int n, double A[static const restrict n], int m) {
;      for (int j = 0; j < n; j += 1) { /* parallel loop */
;        double red = A[j];
;        for (int i = 0; i < m; i += 1) /* reduction loop */
;          for (int k = 0; k < m; k += 1) /* reduction loop */
;            red += 4.2;
;        A[j] = red;
;    }

; Two nested loop-carried phis able to reuse the same %arrayidx
; Possible difficulties:
; - Identify that both phis can use the same %arrayidx as scratch space
; - Needs edge-level writes

define void @func(i32 %n, double* noalias nonnull %A, i32 %m) {
entry:
  br label %parallel.for

parallel.for:
  %j = phi i32 [0, %entry], [%j.inc, %parallel.inc]
  %arrayidx = getelementptr inbounds double, double* %A, i32 %j
  %ld = load double, double* %arrayidx
  %j.cmp = icmp slt i32 %j, %n
  br i1 %j.cmp, label %reduction_outer.for, label %return

reduction_outer.for:
  %i_outer = phi i32 [0, %parallel.for], [%i_outer.inc, %reduction_outer.inc]
  %phi_outer = phi double [%ld, %parallel.for], [%phi_inner, %reduction_outer.inc]
  %i_outer.cmp = icmp slt i32 %i_outer, %m
  br i1 %i_outer.cmp, label %reduction_inner.for, label %parallel.inc

reduction_inner.for:
  %i_inner = phi i32 [0, %reduction_outer.for], [%i_inner.inc, %reduction_inner.inc]
  %phi_inner = phi double [%ld, %reduction_outer.for], [%add, %reduction_inner.inc]
  %i_inner.cmp = icmp slt i32 %i_inner, %m
  br i1 %i_inner.cmp, label %body, label %reduction_outer.inc

body:
  %add = fadd double %phi_inner, 4.2
  br label %reduction_inner.inc

reduction_inner.inc:
  %i_inner.inc = add nuw nsw i32 %i_inner, 1
  br label %reduction_inner.for

reduction_outer.inc:
  %i_outer.inc = add nuw nsw i32 %i_outer, 1
  br label %reduction_outer.for

parallel.inc:
  store double %phi_outer, double* %arrayidx
  %j.inc = add nuw nsw i32 %j, 1
  br label %parallel.for

return:
  ret void
}


