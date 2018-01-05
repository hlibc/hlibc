#!/bin/sh


BASIC_TYPE="	atoi \
		atol \
		atoll \
		environ \
		getenv-driver \
		hcreate-driver \
		printf-driver \
		printf-driver-integers \
		strstr-driver \
		strstr-effectiveness2 \
		strstr-effectiveness3
		
"

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
CC=clang make -j4 > ${SUF}/buildlog #2>&1
make install
printf "==========COMPILING TESTS ===================================\n"
make $1 > ${SUF}/testlog
printf "=============================================================\n"
printf "==========TEST RESULT START==================================\n"

for i in $BASIC_TYPE
do	
	"./tests/${i}" > "${SUF}/diff2"
	"./control/${i}" > "${SUF}/diff3"
	if [ ! -s "${SUF}/diff2" ]
	then	printf "%s\n" "empty test file, something went wrong!!"
	fi
	if diff "${SUF}/diff2" "${SUF}/diff3" 2>&1 > "${SUF}/testerr"
	then	printf "%s\n" "\`${i}' compared equal to its control method"
	else	printf "%s\n" "##${i} failed to compare equal to its control method"
	fi
done


