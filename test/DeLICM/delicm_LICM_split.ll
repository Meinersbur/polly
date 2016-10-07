; RUN: opt %loadPolly -polly-scops -analyze < %s
;
;    void func(int n, double A[static const restrict n], int m, double B[static const restrict m]) {
;      for (int j = 0; j < n; j += 1) { /* parallel loop */
;        double red = A[j];
;        for (int i = 0; i < m; i += 1) { /* reduction loop */
;          red += B[i]; /* assume B[i] non-rematerializable */
;          <split>
;          red += B[m-i]; /* assume B[m-i] non-rematerializable */
;        }
;        A[j] = red;
;    }

; Body is split into multiple blocks
; Some more complicated could between body and body.split might keep the block from being joind into one
; Possible difficulties:
; - Does body and body.split get their own stores?
; - If not, does a scalar dependency between them remain?

define void @func(i32 %n, double* noalias nonnull %A, i32 %m, double* noalias nonnull %B) {
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
  %phi = phi double [%ld, %parallel.for], [%add2, %reduction.inc]
  %i.cmp = icmp slt i32 %i, %m
  br i1 %i.cmp, label %body, label %parallel.inc

body:
  %arrayidxB1 = getelementptr inbounds double, double* %B, i32 %i
  %B1 = load double, double* %arrayidxB1  ; assume non-rematerializable
  %add1 = fadd double %phi, %B1
  br label %body.split

body.split:
  %minusi = sub nuw nsw i32 %m, %i
  %arrayidxB2 = getelementptr inbounds double, double* %B, i32 %minusi
  %B2 = load double, double* %arrayidxB2  ; assume non-rematerializable
  %add2 = fadd double %add1, %B2
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


