; RUN: opt %loadPolly -polly-scops -analyze < %s
;
;    void func(int n, double A[static const restrict n], int m, int c) {
;      for (int j = 0; j < n; j += 1) { /* parallel loop */
;        double red = A[j];
;        if (c) {
;          for (int i = 0; i < m; i += 1) /* reduction loop */
;            red += 4.2;
;        else {
;          for (int i = 0; i < m; i += 1) /* reduction loop */
;            red *= 1.2;
;        }
;        A[j] = red;
;    }

; Nested reduction standard case
; After LICM 
; Possible difficulties:
; - Two independent loop-carried phis can reuse the same %arrayidx (to be distinguished from the case where it can't)

define void @func(i32 %n, double* noalias nonnull %A, i32 %m, i32 %c) {
entry:
  br label %parallel.for

parallel.for:
  %j = phi i32 [0, %entry], [%j.inc, %parallel.inc]
  %arrayidx = getelementptr inbounds double, double* %A, i32 %j
  %ld = load double, double* %arrayidx
  %j.cmp = icmp slt i32 %j, %n
  br i1 %j.cmp, label %condition, label %return

condition:
  %ccmp = icmp ne i32 %c, 0
  br i1 %ccmp, label %reduction1.for, label %reduction2.for

reduction1.for:
  %i1 = phi i32 [0, %condition], [%i1.inc, %reduction1.inc]
  %phi1 = phi double [%ld, %condition], [%add, %reduction1.inc]
  %i1.cmp = icmp slt i32 %i1, %m
  br i1 %i1.cmp, label %body1, label %parallel.inc

body1:
  %add = fadd double %phi1, 4.2
  br label %reduction1.inc

reduction1.inc:
  %i1.inc = add nuw nsw i32 %i1, 1
  br label %reduction1.for
  
reduction2.for:
  %i2 = phi i32 [0, %condition], [%i2.inc, %reduction2.inc]
  %phi2 = phi double [%ld, %condition], [%mul, %reduction2.inc]
  %i2.cmp = icmp slt i32 %i2, %m
  br i1 %i2.cmp, label %body2, label %parallel.inc

body2:
  %mul = fmul double %phi2, 1.2
  br label %reduction2.inc

reduction2.inc:
  %i2.inc = add nuw nsw i32 %i2, 1
  br label %reduction2.for

parallel.inc:
  %condphi = phi double [%phi1, %reduction1.for], [%phi2, %reduction2.for]
  store double %condphi, double* %arrayidx
  %j.inc = add nuw nsw i32 %j, 1
  br label %parallel.for

return:
  ret void
}


