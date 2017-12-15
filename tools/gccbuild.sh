#!/bin/sh

TOOLING=$(pwd)/usr

SUF="$(pwd)/logs" 
make clean 
./configure --prefix=${TOOLING} --enable-gcc-wrapper
mkdir -p ${SUF}
./tools/symlink_tests.sh
printf "The automatic build is being logged to: ${SUF}/buildlog \n\n"
make -j4 > ${SUF}/buildlog 2>&1
make install
printf "==========COMPILING TESTS ===================================\n"
make gcctests > ${SUF}/testlog
printf "=============================================================\n"
printf "==========TEST RESULT START==================================\n" 
./tools/buildall.sh
