#! /bin/bash
set -e



OPT=
OPT="-mllvm -polly -mllvm -polly-process-unprofitable -mllvm -polly-only-func=hashlookup -mllvm -debug -mllvm -debug-only=polly-ast -v"

rm -f Broken.log Repair.log

compile()
{
set -e
COMEFROM=`pwd`
CFLAGS="$1"
OUTPUT="$2"
TEE=$3

rm -rf ${OUTPUT}
mkdir -p ${OUTPUT}
cd ${OUTPUT}

/home/meinersbur/build/llvm/release/bin/clang -DCOUNTBITS16 -DLASTBIT16 -DCOUNTMOVES_TABLE -DTWO_STAGE_GENERATION -DHASHCODEBITS=23 -I/tmp/llvm-lnt-zTs-sandbox/test-2015-11-12_15-35-18/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/include -I../../../include -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -DNDEBUG  -O3  -m64 -fomit-frame-pointer -c /home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi/display.c -o display.llvm.o

/home/meinersbur/build/llvm/release/bin/clang -DCOUNTBITS16 -DLASTBIT16 -DCOUNTMOVES_TABLE -DTWO_STAGE_GENERATION -DHASHCODEBITS=23 -I/tmp/llvm-lnt-zTs-sandbox/test-2015-11-12_15-35-18/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/include -I../../../include -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -DNDEBUG  -O3  -m64 -fomit-frame-pointer -c /home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi/does_x_win.c -o does_x_win.llvm.o

/home/meinersbur/build/llvm/release/bin/clang -DCOUNTBITS16 -DLASTBIT16 -DCOUNTMOVES_TABLE -DTWO_STAGE_GENERATION -DHASHCODEBITS=23 -I/tmp/llvm-lnt-zTs-sandbox/test-2015-11-12_15-35-18/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/include -I../../../include -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -DNDEBUG  -O3  -m64 -fomit-frame-pointer -c /home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi/hash.c -o hash.llvm.o $CFLAGS

/home/meinersbur/build/llvm/release/bin/clang -DCOUNTBITS16 -DLASTBIT16 -DCOUNTMOVES_TABLE -DTWO_STAGE_GENERATION -DHASHCODEBITS=23 -I/tmp/llvm-lnt-zTs-sandbox/test-2015-11-12_15-35-18/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/include -I../../../include -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -DNDEBUG  -O3  -m64 -fomit-frame-pointer -c /home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi/hashstore.c -o hashstore.llvm.o

/home/meinersbur/build/llvm/release/bin/clang -DCOUNTBITS16 -DLASTBIT16 -DCOUNTMOVES_TABLE -DTWO_STAGE_GENERATION -DHASHCODEBITS=23 -I/tmp/llvm-lnt-zTs-sandbox/test-2015-11-12_15-35-18/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/include -I../../../include -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -DNDEBUG  -O3  -m64 -fomit-frame-pointer -c /home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi/init.c -o init.llvm.o

/home/meinersbur/build/llvm/release/bin/clang -DCOUNTBITS16 -DLASTBIT16 -DCOUNTMOVES_TABLE -DTWO_STAGE_GENERATION -DHASHCODEBITS=23 -I/tmp/llvm-lnt-zTs-sandbox/test-2015-11-12_15-35-18/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/include -I../../../include -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -DNDEBUG  -O3  -m64 -fomit-frame-pointer -c /home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi/move_gen.c -o move_gen.llvm.o

/home/meinersbur/build/llvm/release/bin/clang -DCOUNTBITS16 -DLASTBIT16 -DCOUNTMOVES_TABLE -DTWO_STAGE_GENERATION -DHASHCODEBITS=23 -I/tmp/llvm-lnt-zTs-sandbox/test-2015-11-12_15-35-18/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/include -I../../../include -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -DNDEBUG  -O3  -m64 -fomit-frame-pointer -c /home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi/move_sort.c -o move_sort.llvm.o

/home/meinersbur/build/llvm/release/bin/clang -DCOUNTBITS16 -DLASTBIT16 -DCOUNTMOVES_TABLE -DTWO_STAGE_GENERATION -DHASHCODEBITS=23 -I/tmp/llvm-lnt-zTs-sandbox/test-2015-11-12_15-35-18/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/include -I../../../include -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -DNDEBUG  -O3  -m64 -fomit-frame-pointer -c /home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi/negamax.c -o negamax.llvm.o

/home/meinersbur/build/llvm/release/bin/clang -DCOUNTBITS16 -DLASTBIT16 -DCOUNTMOVES_TABLE -DTWO_STAGE_GENERATION -DHASHCODEBITS=23 -I/tmp/llvm-lnt-zTs-sandbox/test-2015-11-12_15-35-18/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/include -I../../../include -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -DNDEBUG  -O3  -m64 -fomit-frame-pointer -c /home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi/obsequi.c -o obsequi.llvm.o

/home/meinersbur/build/llvm/release/bin/clang -DCOUNTBITS16 -DLASTBIT16 -DCOUNTMOVES_TABLE -DTWO_STAGE_GENERATION -DHASHCODEBITS=23 -I/tmp/llvm-lnt-zTs-sandbox/test-2015-11-12_15-35-18/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/include -I../../../include -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -DNDEBUG  -O3  -m64 -fomit-frame-pointer -c /home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi/position_values.c -o position_values.llvm.o

/home/meinersbur/build/llvm/release/bin/clang -DCOUNTBITS16 -DLASTBIT16 -DCOUNTMOVES_TABLE -DTWO_STAGE_GENERATION -DHASHCODEBITS=23 -I/tmp/llvm-lnt-zTs-sandbox/test-2015-11-12_15-35-18/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/include -I../../../include -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -DNDEBUG  -O3  -m64 -fomit-frame-pointer -c /home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi/tables.c -o tables.llvm.o

/home/meinersbur/build/llvm/release/bin/clang -DCOUNTBITS16 -DLASTBIT16 -DCOUNTMOVES_TABLE -DTWO_STAGE_GENERATION -DHASHCODEBITS=23 -I/tmp/llvm-lnt-zTs-sandbox/test-2015-11-12_15-35-18/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/include -I../../../include -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -DNDEBUG  -O3  -m64 -fomit-frame-pointer -c /home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi/toggle_move.c -o toggle_move.llvm.o

/home/meinersbur/build/llvm/release/bin/clang -DCOUNTBITS16 -DLASTBIT16 -DCOUNTMOVES_TABLE -DTWO_STAGE_GENERATION -DHASHCODEBITS=23 -I/tmp/llvm-lnt-zTs-sandbox/test-2015-11-12_15-35-18/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/include -I../../../include -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -DNDEBUG  -O3  -m64 -fomit-frame-pointer -c /home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi/traits.c -o traits.llvm.o

/home/meinersbur/build/llvm/release/bin/clang -DCOUNTBITS16 -DLASTBIT16 -DCOUNTMOVES_TABLE -DTWO_STAGE_GENERATION -DHASHCODEBITS=23 -I/tmp/llvm-lnt-zTs-sandbox/test-2015-11-12_15-35-18/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi -I/home/meinersbur/src/llvm/projects/test-suite/include -I../../../include -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -DNDEBUG  -O3  -m64 -fomit-frame-pointer -c /home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi/utils.c -o utils.llvm.o

/home/meinersbur/build/llvm/release/bin/clang++ -o Obsequi.simple display.llvm.o does_x_win.llvm.o hash.llvm.o hashstore.llvm.o init.llvm.o move_gen.llvm.o move_sort.llvm.o negamax.llvm.o obsequi.llvm.o position_values.llvm.o tables.llvm.o toggle_move.llvm.o traits.llvm.o utils.llvm.o -lsupc++   -m64 -fomit-frame-pointer

./Obsequi.simple < /home/meinersbur/src/llvm/projects/test-suite/MultiSource/Applications/obsequi/input > out.log 2> err.log
echo "exit $?" >> out.log
cat out.log
cd $COMEFROM
}

(compile "" "Reference") 2>&1 | tee Reference.log
(compile "$OPT" "Broken") 2>&1 | tee Broken.log
#(compile "-DREPAIR $OPT" "Repair") 2>&1 | tee Repair.log

echo "Reference diff:"
diff Reference/out.log Obsequi.reference_output || echo "Reference has diverged"
echo

echo "Broken diff:"
diff Broken/out.log Obsequi.reference_output || echo "Broken has diverged"
echo

#echo "Repair diff:"
#diff Repair/out.log Obsequi.reference_output || echo "Repair has diverged"
#echo

FIRSTDIVLINE=`cmp Reference/err.log Broken/err.log  | awk '{print $NF}'`
STARTLINE=$(($FIRSTDIVLINE - 5))
tail Reference/err.log "-n+${STARTLINE}" > Reference/err-tail.log
tail Broken/err.log "-n+${STARTLINE}" > Broken/err-tail.log
diff --side-by-side Reference/err-tail.log Broken/err-tail.log | head -n60
