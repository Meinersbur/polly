; RUN: clang -cc1 -Werror=implicit-int -emit-obj -O3 -mllvm -polly -mllvm -polly-enable-delicm %S/ludcmp-93306f.c 
 