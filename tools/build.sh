#!/bin/sh

TOOLING=$(pwd)/usr

SUF="$(pwd)/logs" 
make clean 
CC=$2 ./configure --prefix=${TOOLING} --enable-gcc-wrapper
mkdir -p ${SUF}
mkdir -p control
mkdir -p posix-utils-control
for i in tests/*.c
do ln $i control/$(basename $i)
done

for i in posix-utils/*.c posix-utils/*.h
do ln $i posix-utils-control/$(basename $i)
done
printf "automatic build is being logged to: ${SUF}/buildlog \n\n"
CC=clang make -j4 > ${SUF}/buildlog 2>&1
make install
printf "==========COMPILING TESTS ===================================\n"
make $1 > ${SUF}/testlog
printf "=============================================================\n"
printf "==========TEST RESULT START==================================\n"

./tests/pow_test 

./tests/puts-driver > ${SUF}/diff2 2>${SUF}/testerr
./control/puts-driver > ${SUF}/diff3 2>${SUF}/testerr
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "\`puts-driver' test compared equal to its control method" || \
echo "##puts-driver test failed" 

./tests/strerror-driver > ${SUF}/diff2 2>${SUF}/testerr
./control/strerror-driver > ${SUF}/diff3 2>${SUF}/testerr
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "\`strerror-driver' test compared equal to its control method" || \
echo "##strerror-driver test failed" 


./tests/atoi > ${SUF}/diff2 2>${SUF}/testerr
./control/atoi > ${SUF}/diff3 2>${SUF}/testerr
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "\`atoi' test compared equal to its control method" || \
echo "##atoi test failed" 


./tests/atol > ${SUF}/diff2 2>${SUF}/testerr
./control/atol > ${SUF}/diff3 2>${SUF}/testerr
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "\`atol' test compared equal to its control method" || \
echo "##atol test failed" 


./tests/atoll > ${SUF}/diff2 2>${SUF}/testerr
./control/atoll > ${SUF}/diff3 2>${SUF}/testerr
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "\`atoll' test compared equal to its control method" || \
echo "##atoll test failed" 

#./tests/strlcpy > ${SUF}/diff2 2>${SUF}/testerr
#./control/strlcpy > ${SUF}/diff3 2>${SUF}/testerr
#diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
#echo "\`strlcpy' test compared equal to its control method" || \
#echo "##strlcpy test failed" 

#./tests/strlcat > ${SUF}/diff2 2>${SUF}/testerr
#./control/strlcat > ${SUF}/diff3 2>${SUF}/testerr
#diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
#echo "\`strlcat' test compared equal to its control method" || \
#echo "##strlcat test failed" 

./tests/cat Makefile > ${SUF}/diff1 2>${SUF}/testerr 
diff Makefile ${SUF}/diff1 2>&1 > ${SUF}/testerr && \
echo "\`cat' utility successfully copied a file" || \
echo "##cat util failed" 

./control/malloc-driver /usr > ${SUF}/diff2 2>${SUF}/testerr 
./tests/malloc-driver /usr > ${SUF}/diff3 2>${SUF}/testerr 
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "\`malloc_driver' test utility successfully iterated through a dir and compared equal to its control method" || \
echo "##malloc driver failed" 

./control/popen-driver "du /usr" >${SUF}/diff2 2>${SUF}/testerr 
./tests/popen-driver "du /usr" >${SUF}/diff3 2>${SUF}/testerr 
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "\`popen_driver' test utility successfully ran \`du' on a directory and compared equal to its control method" || \
echo "##popen driver failed" 

#fix float rounding and add this back
./control/printf-driver >${SUF}/diff2 2>${SUF}/testerr 
./tests/printf-driver >${SUF}/diff3 2>${SUF}/testerr 
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "\`printf_driver' test utility successfully compared equal to its control method" || \
echo "printf driver had a float rounding error "

./tests/printf-driver Makefile ${SUF}/testfile
diff Makefile ${SUF}/testfile 2>&1 > ${SUF}/testerr && \
echo "\`printf_driver' test utility successfully created and copied a file" || \
echo "##printf driver was unable to create and copy a file"

./control/popen-to-file "du /usr" ${SUF}/diff2 2>${SUF}/testerr
./tests/popen-to-file "du /usr" ${SUF}/diff3 2>${SUF}/testerr
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "\`popen-to-file' test utility successfully ran \`du' on a directory, output to a file and compared equal to its control method" || \
echo "##popen-to-file driver failed to output to a file" 

dd if=/dev/urandom of=${SUF}/diff2 bs=1M count=50 2>${SUF}/testerr
./tests/printf-driver ${SUF}/diff2 ${SUF}/diff3 2>${SUF}/testerr
diff Makefile ${SUF}/testfile 2>&1 > ${SUF}/testerr && \
echo "\`printf_driver' test utility successfully created and copied a large file of urandom data" || \
echo "##printf driver was unable to create and copy a large file of urandom data"

#./tests/strsep-driver > ${SUF}/diff2 2>${SUF}/testerr
#./control/strsep-driver > ${SUF}/diff3 2>${SUF}testerr
#diff ${SUF}/diff2 ${SUF}/diff3 2>${SUF}/testerr && \
#echo "\`strsep_driver' test compared equal to its control method" || \
#echo "##strsep driver test failed"

./tests/printf-driver-integers > ${SUF}/diff2
./control/printf-driver-integers > ${SUF}/diff3
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "\`printf-driver-integers' compared equal to its control method" || \
echo "##printf-driver-integers failed to compare equal to its control method"

./tests/hcreate-driver > ${SUF}/diff2
./control/hcreate-driver > ${SUF}/diff3
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "\`hcreate-driver' compared equal to its control method" || \
echo "##hcreate-driver failed to compare equal to its control method"

./tests/getenv-driver > ${SUF}/diff2
./control/getenv-driver > ${SUF}/diff3
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "\`getenv-driver' compared equal to its control method" || \
echo "##getenv-driver failed to compare equal to its control method"

./tests/strstr-driver > ${SUF}/diff2
./control/strstr-driver > ${SUF}/diff3
diff ${SUF}/diff2 ${SUF}/diff3 2>&1 > ${SUF}/testerr && \
echo "\`strstr-driver' compared equal to its control method" || \
echo "##strstr-driver failed to compare equal to its control method"

printf "============================================================\n"

