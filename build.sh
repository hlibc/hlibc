#!/bin/sh

TOOLING="$(pwd)/usr"
LOGDIR="$(pwd)/logs" 

make clean 
./configure --prefix=${TOOLING} 
mkdir -p ${LOGDIR}
./tools/symlink_tests.sh
printf "\nSo as not to destroy ssh connections automatic builds are logged \n\n"
printf "Logging to ..  ${LOGDIR}/buildlog \n\n"
make -j4 > ${LOGDIR}/buildlog 2>&1
make install
printf "==========COMPILING TEST SUITE==============================\n"
make tests > ${LOGDIR}/testlog
printf "============================================================\n"
printf "==========TEST SUITE START==================================\n"

./tests/pow_test

./tests/cat Makefile > ${LOGDIR}/diff1 2>${LOGDIR}/testerr

diff Makefile ${LOGDIR}/diff1 2>&1 > ${LOGDIR}/testerr && echo "The \`cat' utility successfully copied a file" || echo "The cat util failed"

./control/malloc-driver musllibc > ${LOGDIR}/diff2 2>${LOGDIR}/testerr

./tests/malloc-driver musllibc > ${LOGDIR}/diff3 2>${LOGDIR}/testerr

diff ${LOGDIR}/diff2 ${LOGDIR}/diff3 2>&1 > ${LOGDIR}/testerr && echo "The \`malloc_driver' test utility successfully iterated through a dir and compared equal to its control method" || echo "The malloc driver failed"

./control/popen-driver "du musllibc" >${LOGDIR}/diff2 2>${LOGDIR}/testerr

./tests/popen-driver "du musllibc" >${LOGDIR}/diff3 2>${LOGDIR}/testerr

diff ${LOGDIR}/diff2 ${LOGDIR}/diff3 2>&1 > ${LOGDIR}/testerr && echo "The \`popen_driver' test utility successfully ran \`du' on a directory and compared equal to its control method" || echo "The popen driver failed"


./control/printf-driver >${LOGDIR}/diff2 2>${LOGDIR}/testerr

./tests/printf-driver >${LOGDIR}/diff3 2>${LOGDIR}/testerr

diff ${LOGDIR}/diff2 ${LOGDIR}/diff3 2>&1 > ${LOGDIR}/testerr && echo "The \`printf_driver' test utility successfully compared equal to its control method" || echo "The printf driver had a float rounding error "
printf "============================================================\n"

printf "============================================================\n"
printf "   If all was successful the new compiler wrapper can be\n"
printf "   invoked as:\n"
printf "       ${TOOLING}/bin/gcc-wrap\n"
printf "============================================================\n"
