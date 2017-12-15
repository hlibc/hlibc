#!/bin/sh

TOOLING=$(pwd)/usr

SUF="$(pwd)/logs"

./tests/pow_test 

./tests/puts-driver > ${SUF}/diff2 2>${SUF}/testerr
./control/puts-driver > ${SUF}/diff3 2>${SUF}/testerr
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "The \`puts-driver' test compared equal to its control method" || \
echo "The puts-driver test failed" 

./tests/strerror-driver > ${SUF}/diff2 2>${SUF}/testerr
./control/strerror-driver > ${SUF}/diff3 2>${SUF}/testerr
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "The \`strerror-driver' test compared equal to its control method" || \
echo "The strerror-driver test failed" 


./tests/atoi > ${SUF}/diff2 2>${SUF}/testerr
./control/atoi > ${SUF}/diff3 2>${SUF}/testerr
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "The \`atoi' test compared equal to its control method" || \
echo "The atoi test failed" 


./tests/atol > ${SUF}/diff2 2>${SUF}/testerr
./control/atol > ${SUF}/diff3 2>${SUF}/testerr
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "The \`atol' test compared equal to its control method" || \
echo "The atol test failed" 


./tests/atoll > ${SUF}/diff2 2>${SUF}/testerr
./control/atoll > ${SUF}/diff3 2>${SUF}/testerr
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "The \`atoll' test compared equal to its control method" || \
echo "The atoll test failed" 

./tests/cat Makefile > ${SUF}/diff1 2>${SUF}/testerr 
diff Makefile ${SUF}/diff1 2>&1 > ${SUF}/testerr && \
echo "The \`cat' utility successfully copied a file" || \
echo "The cat util failed" 

./control/malloc-driver /usr > ${SUF}/diff2 2>${SUF}/testerr 
./tests/malloc-driver /usr > ${SUF}/diff3 2>${SUF}/testerr 
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "The \`malloc_driver' test utility successfully iterated through a dir and compared equal to its control method" || \
echo "The malloc driver failed" 

./control/popen-driver "du /usr" >${SUF}/diff2 2>${SUF}/testerr 
./tests/popen-driver "du /usr" >${SUF}/diff3 2>${SUF}/testerr 
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

./control/popen-to-file "du /usr" ${SUF}/diff2 2>${SUF}/testerr
./tests/popen-to-file "du /usr" ${SUF}/diff3 2>${SUF}/testerr
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "The \`popen-to-file' driver test utility successfully ran \`du' on a directory, copied it to a file and compared equal to its control method" || \
echo "The popen-to-file driver failed to output to a file" 

printf "============================================================\n"

