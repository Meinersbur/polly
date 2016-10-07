; RUN: opt %loadPolly -polly-scops -analyze < %s
;
;    void func(int n, double A[static const restrict n], int m) {
;      for (int j = 0; j < n; j += 1) { /* parallel loop */
;        double red = A[j];
;        for (int i = 0; i < m; i += 1) /* reduction loop */
;          red += 4.2;
;        A[j] = red;
;    }

; Nested reduction standard case; After LICM 
; Possible difficulties:
; - Put the store into %body or $reduction.inc
; - Replace %phi in %body with a load, knowing that after the store has been placed in %body or %reduction.inc, it contains %phi
; - Except the store, all instructions are "rematerializable", when applying the same logic to the loop-carried %phi, so the naive algorithm might try to move all instructions into %parallel.inc and remove the one in %body
; - There can be no mapped store added to parallel.for (for the %phi) because it is not postdominated by the store  

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
  %j.inc = add nuw nsw i32 %j, 1
  br label %parallel.for

return:
  ret void
}


