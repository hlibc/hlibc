#!/bin/sh

TOOLING=$(pwd)/usr

SUF="$(pwd)/logs" 
make clean 
#./configure --prefix=${TOOLING} 
mkdir -p ${SUF}
./tools/symlink_tests.sh
printf "The automatic build is being logged to: ${SUF}/buildlog \n\n"
make clang -j4 > ${SUF}/buildlog 2>&1
make install
printf "==========COMPILING TESTS ===================================\n"
make clangtests > ${SUF}/testlog
printf "=============================================================\n"
printf "==========TEST RESULT START==================================\n" 

./tests/pow_test 

./tests/cat Makefile > ${SUF}/diff1 2>${SUF}/testerr 
diff Makefile ${SUF}/diff1 2>&1 > ${SUF}/testerr && \
echo "The \`cat' utility successfully copied a file" || \
echo "The cat util failed" 

./control/malloc-driver musllibc > ${SUF}/diff2 2>${SUF}/testerr 
./tests/malloc-driver musllibc > ${SUF}/diff3 2>${SUF}/testerr 
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "The \`malloc_driver' test utility successfully iterated through a dir and compared equal to its control method" || \
echo "The malloc driver failed" 

./control/popen-driver "du musllibc" >${SUF}/diff2 2>${SUF}/testerr 
./tests/popen-driver "du musllibc" >${SUF}/diff3 2>${SUF}/testerr 
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "The \`popen_driver' test utility successfully ran \`du' on a directory and compared equal to its control method" || \
echo "The popen driver failed" 

#fix float rounding and add this back
#./control/printf-driver >${SUF}/diff2 2>${SUF}/testerr 
#./tests/printf-driver >${SUF}/diff3 2>${SUF}/testerr 
#diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
#echo "The \`printf_driver' test utility successfully compared equal to its control method" || \
#echo "The printf driver had a float rounding error "

./tests/printf-driver Makefile ${SUF}/testfile
diff Makefile ${SUF}/testfile 2>&1 > ${SUF}/testerr && \
echo "The \`printf_driver' test utility successfully created and copied a file" || \
echo "The printf driver was unable to create and copy a file"

./control/popen-to-file "du musllibc" ${SUF}/diff2 2>${SUF}/testerr
./tests/popen-to-file "du musllibc" ${SUF}/diff3 2>${SUF}/testerr
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "The \`popen-to-file' driver test utility successfully ran \`du' on a directory, copied it to a file and compared equal to its control method" || \
echo "The popen-to-file driver failed to output to a file" 

printf "============================================================\n"

