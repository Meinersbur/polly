; RUN: opt %loadPolly -basicaa -licm -polly-flatten-schedule -polly-delicm -analyze < %s | FileCheck %s
; 
; dgemm kernel
; C := alpha*A*B + beta*C
; C[ni][nj]
; A[ni][nk]
; B[nk][nj]

target datalayout = "e-m:x-p:32:32-i64:64-f80:32-n8:16:32-a:0:32-S32"

define void @gemm(i32 %ni, i32 %nj, i32 %nk, double %alpha, double %beta, double* noalias nonnull %C, double* noalias nonnull %A, double* noalias nonnull %B) {
entry:
  br label %ni.for

ni.for:
  %i = phi i32 [0, %entry], [%i.inc, %ni.inc]
  %i.cmp = icmp slt i32 %i, 3 ; %ni
  br i1 %i.cmp, label %nj.for, label %ni.exit

  nj.for:
    %j = phi i32 [0, %ni.for], [%j.inc, %nj.inc]
    %j.cmp = icmp slt i32 %j, 3 ; %nj
    br i1 %j.cmp, label %nj_beta, label %nj.exit
  
    nj_beta:
     %c_stride = mul nsw i32 %i, 3; %nj
     %c_idx_i = getelementptr inbounds double, double* %C, i32 %c_stride
     %c_idx_ij = getelementptr inbounds double, double* %c_idx_i, i32 %j
 
     ; C[i][j] *= beta
     ;%c = load double, double* %c_idx_ij
     ;%c_beta = fmul double %c, %beta
     ;store double %c_beta, double* %c_idx_ij
     
     ;%c_init = load double, double* %c_idx_ij
     br label %nk.for
  
    nk.for:
      ;%c = phi double [%c_init, %nj_beta], [%beta_c_alpha_a_b, %nk.inc]
      %k = phi i32 [0, %nj_beta], [%k.inc, %nk.inc]
      %k.cmp = icmp slt i32 %k, 3 ; %nk
      br i1 %k.cmp, label %nk_alpha, label %nk.exit
    
      nk_alpha:
        %a_stride = mul nsw i32 %i, 3; %nk
        %a_idx_i = getelementptr inbounds double, double* %A, i32 %a_stride
        %a_idx_ik = getelementptr inbounds double, double* %a_idx_i, i32 %k
  
        %b_stride = mul nsw i32 %k, 3; %nj
        %b_idx_k = getelementptr inbounds double, double* %B, i32 %b_stride
        %b_idx_kj = getelementptr inbounds double, double* %b_idx_k, i32 %j
  
        ; C[i][j] += alpha * A[i][k] * B[k][j]
        %a = load double, double* %a_idx_ik
        %b = load double, double* %b_idx_kj
        %beta_c = load double, double* %c_idx_ij

        %alpha_a = fmul double %a, %alpha
        %alpha_a_b = fmul double %alpha_a, %b
        %beta_c_alpha_a_b = fadd double %beta_c, %alpha_a_b
        
        store double %beta_c_alpha_a_b, double* %c_idx_ij
        
        br label %nk.inc
      
    nk.inc:
      %k.inc = add nuw nsw i32 %k, 1
      br label %nk.for
    
    nk.exit:
      ; store double %c, double* %c_idx_ij
      br label %nj.inc
  
  nj.inc:
    %j.inc = add nuw nsw i32 %j, 1
    br label %nj.for
      
  nj.exit:
    br label %ni.inc
      
ni.inc:
  %i.inc = add nuw nsw i32 %i, 1
  br label %ni.for

ni.exit:
  br label %return

return:
  ret void
}


; [0] Stmt_nj_beta[0, 0]
; [1] Stmt_nk_alpha[0,0,0]
;     (2) %c1 
; [2] Stmt_nk_inc[0,0,0]
;     (3) %beta_c_alpha_a_b
; [3] Stmt_nk_alpha[0,0,1]


; CHECK:      Schedule after flattening {
; CHECK-NEXT:     { Stmt_nk_alpha[i0, i1, i2] -> [9i0 + 3i1 + i2] }
; CHECK-NEXT: }
; CHECK:      Original zone:
; CHECK-NEXT:     Lifetime: { [MemRef_C[i0] -> [i1{{\]\]}} -> [Stmt_nk_alpha[o0, i0 - 3o0, 2] -> Val_double__beta_c_alpha_a_b[{{\]\]}} : i1 >= 4 + 3i0 and 0 <= o0 <= 2 and -2 + i0 <= 3o0 <= i0; [MemRef_C[i0] -> [i1{{\]\]}} -> [Stmt_nk_alpha[o0, i0 - 3o0, -1 - 3i0 + i1] -> Val_double__beta_c_alpha_a_b[{{\]\]}} : 3i0 < i1 <= 3 + 3i0 and 0 <= o0 <= 2 and -2 + i0 <= 3o0 <= i0 }
; CHECK-NEXT:     Written : { [MemRef_C[i0] -> [i1{{\]\]}} -> [Stmt_nk_alpha[o0, i0 - 3o0, -3i0 + i1] -> Val_double__beta_c_alpha_a_b[{{\]\]}} : 3i0 <= i1 <= 2 + 3i0 and 0 <= o0 <= 2 and -2 + i0 <= 3o0 <= i0 }
; CHECK:      Mapped scalars {
; CHECK-NEXT: }
; CHECK:      Cleanups {
; CHECK-NEXT: }
; CHECK:      After zone:
; CHECK-NEXT:     Lifetime: { [MemRef_C[i0] -> [i1{{\]\]}} -> [Stmt_nk_alpha[o0, i0 - 3o0, 2] -> Val_double__beta_c_alpha_a_b[{{\]\]}} : i1 >= 4 + 3i0 and 0 <= o0 <= 2 and -2 + i0 <= 3o0 <= i0; [MemRef_C[i0] -> [i1{{\]\]}} -> [Stmt_nk_alpha[o0, i0 - 3o0, -1 - 3i0 + i1] -> Val_double__beta_c_alpha_a_b[{{\]\]}} : 3i0 < i1 <= 3 + 3i0 and 0 <= o0 <= 2 and -2 + i0 <= 3o0 <= i0 }
; CHECK-NEXT:     Written : { [MemRef_C[i0] -> [i1{{\]\]}} -> [Stmt_nk_alpha[o0, i0 - 3o0, -3i0 + i1] -> Val_double__beta_c_alpha_a_b[{{\]\]}} : 3i0 <= i1 <= 2 + 3i0 and 0 <= o0 <= 2 and -2 + i0 <= 3o0 <= i0 }
; CHECK:      After Statements {
; CHECK-NEXT:     Stmt_nk_alpha
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_nk_alpha[i0, i1, i2] -> MemRef_A[3i0 + i2] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_nk_alpha[i0, i1, i2] -> MemRef_B[i1 + 3i2] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_nk_alpha[i0, i1, i2] -> MemRef_C[3i0 + i1] };
; CHECK-NEXT:             ReadAccess :=    [Reduction Type: NONE] [Scalar: 1]
; CHECK-NEXT:                 { Stmt_nk_alpha[i0, i1, i2] -> MemRef_alpha[] };
; CHECK-NEXT:             MustWriteAccess :=    [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:                 { Stmt_nk_alpha[i0, i1, i2] -> MemRef_C[3i0 + i1] };
; CHECK-NEXT: }
