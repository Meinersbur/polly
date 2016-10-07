; RUN: opt %loadPolly -polly-scops -analyze < %s
;
;    void func(int n, double A[static const restrict n], int m) {
;      for (int j = 0; j < n; j += 1) { /* parallel loop */
;        double red = A[j];
;        for (int i1 = 0; i1 < m; i1 += 1) /* reduction loop */
;          red += 4.2;
;        for (int i2 = 0; i2 < m; i2 += 1) /* reduction loop */
;          red += 5.3;
;        A[j] = red;
;    }

; Two reductions executed sequentially 
; Possible difficulties:
; - Two loop-carrying phis that can use the same %arrayidx

define void @func(i32 %n, double* noalias nonnull %A, i32 %m) {
entry:
  br label %parallel.for

parallel.for:
  %j = phi i32 [0, %entry], [%j.inc, %parallel.inc]
  %arrayidx = getelementptr inbounds double, double* %A, i32 %j
  %ld = load double, double* %arrayidx
  %j.cmp = icmp slt i32 %j, %n
  br i1 %j.cmp, label %reduction1.for, label %return

reduction1.for:
  %i1 = phi i32 [0, %parallel.for], [%i1.inc, %reduction1.inc]
  %phi1 = phi double [%ld, %parallel.for], [%add1, %reduction1.inc]
  %i1.cmp = icmp slt i32 %i1, %m
  br i1 %i1.cmp, label %body1, label %reduction2.for

body1:
  %add1 = fadd double %phi1, 4.2
  br label %reduction1.inc

reduction1.inc:
  %i1.inc = add nuw nsw i32 %i1, 1
  br label %reduction1.for

reduction2.for:
  %i2 = phi i32 [0, %reduction1.for], [%i2.inc, %reduction2.inc]
  %phi2 = phi double [%phi1, %reduction1.for], [%add2, %reduction2.inc]
  %i2.cmp = icmp slt i32 %i2, %m
  br i1 %i2.cmp, label %body2, label %parallel.inc

body2:
  %add2 = fadd double %phi2, 5.3
  br label %reduction2.inc

reduction2.inc:
  %i2.inc = add nuw nsw i32 %i2, 1
  br label %reduction2.for

parallel.inc:
  store double %phi2, double* %arrayidx
  %j.inc = add nuw nsw i32 %j, 1
  br label %parallel.for

return:
  ret void
}


