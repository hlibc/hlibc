#!/bin/sh

TOOLING="$(pwd)/usr"
LOGDIR="$(pwd)/logs" 

make clean 
./configure --prefix=${TOOLING} 
mkdir -p ${LOGDIR} 
printf "\ngrafmusl is logging to ${LOGDIR}/buildlog\n\n" 
# useless timer loop for visual display
count="0"
while [ 1 ] ; do printf "\r.. $count seconds"; sleep 1 ; count=$((count +1)); done & PID=$!

make -j4 > ${LOGDIR}/buildlog 2>&1

kill $PID

make install
echo "==========COMPILING TEST SUITE=============================="
make tests > ${LOGDIR}/testlog 

echo "============================================================"


echo "==========TEST SUITE START=================================="

./tests/pow_test

./tests/cat Makefile > ${LOGDIR}/diff1 2>${LOGDIR}/testerr

diff Makefile ${LOGDIR}/diff1 2>&1 > ${LOGDIR}/testerr && echo "The \`cat' utility successfully copied a file" || echo "cat util failed"

./control/malloc-driver musllibc > ${LOGDIR}/diff2 2>${LOGDIR}/testerr

./tests/malloc-driver musllibc > ${LOGDIR}/diff3 2>${LOGDIR}/testerr

diff ${LOGDIR}/diff2 ${LOGDIR}/diff3 2>&1 > ${LOGDIR}/testerr && echo "The \`malloc_driver' test utility successfully iterated through a dir and compared equal to its control method" || echo "malloc driver failed"

./control/popen-driver "du musllibc" >${LOGDIR}/diff2 2>${LOGDIR}/testerr

./tests/popen-driver "du musllibc" >${LOGDIR}/diff3 2>${LOGDIR}/testerr

diff ${LOGDIR}/diff2 ${LOGDIR}/diff3 2>&1 > ${LOGDIR}/testerr && echo "The \`popen_driver' test utility successfully ran \`du' on a directory and compared equal to its control method" || echo "popen driver failed"


./control/printf-driver >${LOGDIR}/diff2 2>${LOGDIR}/testerr

./tests/printf-driver >${LOGDIR}/diff3 2>${LOGDIR}/testerr

diff ${LOGDIR}/diff2 ${LOGDIR}/diff3 2>&1 > ${LOGDIR}/testerr && echo "The \`printf_driver' test utility successfully compared equal to its control method" || echo "printf driver had a float rounding error "
echo "============================================================"

echo "============================================================"
echo "   If all was successful the new compiler wrapper can be"
echo "   invoked as:"
echo "       ${TOOLING}/bin/gcc-wrap"
echo "============================================================"
