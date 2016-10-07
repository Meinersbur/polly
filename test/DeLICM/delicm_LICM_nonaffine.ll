; RUN: opt %loadPolly -polly-scops -analyze < %s
;
;    void func(int n, double A[static const restrict n], int m) {
;      for (int j = 0; j < n; j += 1) { /* parallel loop */
;        double red = A[j];
;        for (int i = 0; i < m; i += 1) /* reduction loop */
;          if (i*i == 0)
;            red += 4.2;
;        A[j] = red;
;    }

; Body is non-affine subregion
; Possible difficulties:
; - Can move through non-affine subregions?

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
  %i = phi i32 [0, %parallel.for], [%i.inc, %body], [%i.inc, %body.true]
  %phi = phi double [%ld, %parallel.for], [%phi, %body], [%add, %body.true]
  %i.cmp = icmp slt i32 %i, %m
  %i.inc = add nuw nsw i32 %i, 1
  br i1 %i.cmp, label %body, label %parallel.inc

body:
  %sqr = mul i32 %i, %i
  %cond = icmp eq i32 %sqr, 0
  br i1 %cond, label %body.true, label %reduction.for

body.true:
  %add = fadd double %phi, 4.2
  br label %reduction.for

parallel.inc:
  store double %phi, double* %arrayidx
  %j.inc = add nuw nsw i32 %j, 1
  br label %parallel.for

return:
  ret void
}


