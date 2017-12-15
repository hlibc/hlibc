#!/bin/sh

TOOLING=$(pwd)/usr

SUF="$(pwd)/logs" 
make clean 
CC=clang ./configure --prefix=${TOOLING} 
mkdir -p ${SUF}
./tools/symlink_tests.sh
printf "The automatic build is being logged to: ${SUF}/buildlog \n\n"
CC=clang make -j4 > ${SUF}/buildlog 2>&1
make install
printf "==========COMPILING TESTS ===================================\n"
make clangtests > ${SUF}/testlog
printf "=============================================================\n"
printf "==========TEST RESULT START==================================\n" 
./tools/buildall.sh
