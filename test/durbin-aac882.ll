; RUN: clang -cc1 -triple x86_64-unknown-linux-gnu -emit-obj -disable-free -main-file-name durbin.c -mrelocation-model static -mthread-model posix -fmath-errno -masm-verbose -mconstructor-aliases -munwind-tables -fuse-init-array -target-cpu x86-64 -momit-leaf-frame-pointer -dwarf-column-info -debugger-tuning=gdb -coverage-notes-file /tmp/runtests-3rr14hja/build/SingleSource/Benchmarks/Polybench/linear-algebra/solvers/durbin/CMakeFiles/durbin.dir/durbin.c.gcno -D FP_ABSTOLERANCE=1e-5 -D NDEBUG -D NDEBUG -D POLYBENCH_DUMP_ARRAYS -O3 -Werror=date-time -w -ferror-limit 19 -fmessage-length 0 -fobjc-runtime=gcc -fdiagnostics-show-option -vectorize-loops -vectorize-slp -mllvm -polly -mllvm -polly-process-unprofitable -mllvm -polly-enable-delicm -mllvm -polly-dump-before -mllvm -polly-dump-after -x c %S/durbin-aac882.c
