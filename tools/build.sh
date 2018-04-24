#!/bin/sh

BASIC_TYPE="	malloc-unique-pointer
		getline-driver
		atoi
		atol
		atoll
		environ
		getenv-driver
		hcreate-driver
		printf-driver
		printf-driver-integers
		strstr-driver
		strstr-effectiveness2
		malloc-driver /usr
		popen-driver du /usr
		puts-driver
		strerror-driver
		pow_test
"

TOOLING="$(pwd)/usr"
SUF="$(pwd)/logs"

checkifempty()
{
	if [ ! -s "$1" ]
	then    printf "%s\n" "empty test file, something went wrong!!"
	fi
}

make clean

CC="$2" ./configure --prefix="${TOOLING}" --enable-gcc-wrapper

mkdir -p "${SUF}"
mkdir -p control
mkdir -p posix-utils-control

for i in tests/*.c
do ln "$i" "control/$(basename "$i")"
done

for i in posix-utils/*.c
do ln "$i" "posix-utils-control/$(basename "$i")"
done

printf "automatic build is being logged to: ${SUF}/buildlog\n\n"
CC="$2" make -j4 > "${SUF}/buildlog"

make install

RETVAL="0"

printf "==========COMPILING TESTS ===================================\n"
make "$1" > "${SUF}/testlog"
printf "=============================================================\n"
printf "==========TEST RESULT START==================================\n"

printf "%s" "$BASIC_TYPE" | while read -r i
do	./tests/${i} > "${SUF}/diff2"	# don't quote ./tests/{i} or ./control/{i} 
	./control/${i} > "${SUF}/diff3"	# so that they can be expanded as arguments
	checkifempty "${SUF}/diff2"
	if diff "${SUF}/diff2" "${SUF}/diff3" 2>&1 > "${SUF}/testerr"
	then	printf "%s\n" "\`${i}' compared equal to its control method"
	else	printf "%s\n" "##${i} failed to compare equal to its control method"
		RETVAL="1"
	fi
done 

# unique tests that don't work as BASIC_TESTs
./control/popen-to-file "du /usr" "${SUF}/diff2" 2>"${SUF}/testerr"
./tests/popen-to-file "du /usr" "${SUF}/diff3" 2>"${SUF}/testerr"
checkifempty() "${SUF}/diff2"
if diff "${SUF}/diff2" "${SUF}/diff3" 2>&1 > "${SUF}/testerr"
then	printf "%s\n" "\`popen-to-file' test ran \`du' on a dir, output to a file and compared equal to its control method"
else	printf "%s\n" "##popen-to-file driver failed to output to a file" 
	RETVAL="1"
fi

dd if=/dev/urandom of="${SUF}/diff2" bs=1M count=50 2>"${SUF}/testerr"
./tests/printf-driver "${SUF}/diff2" "${SUF}/diff3" 2>"${SUF}/testerr"
checkifempty() "${SUF}/diff2"
if diff "${SUF}/diff2" "${SUF}/diff3" 2>&1 > "${SUF}/testerr"
then	printf "%s\n" "\`printf_driver' test utility successfully created and copied a large file of urandom data"
else	printf "%s\n" "##printf driver was unable to create and copy a large file of urandom data"
	RETVAL="1"
fi

dd if=/dev/urandom of="${SUF}/diff2" bs=1M count=1 2> "${SUF}/testerr"
cp "${SUF}/diff2" "${SUF}/diff3"
mv "${SUF}/diff2" "${SUF}/diff4"
./tests/rename-driver "${SUF}/diff3" "${SUF}/diff"5 2> "${SUF}/testerr"
checkifempty() "${SUF}/diff4"
if diff "${SUF}/diff4" "${SUF}/diff5" 2>&1 > "${SUF}/testerr"
then	printf "%s\n" "\`rename-driver' test utility successfully renamed a small file of urandom data"
else	printf "%s\n" "##rename-driver was unable to rename a small file of urandom data"
	RETVAL="1"
fi


./control/ftw-driver /tmp | sort > "${SUF}/diff2" 2> "${SUF}/testerr"
./tests/ftw-driver /tmp | sort > "${SUF}/diff3" 2> "${SUF}/testerr"
checkifempty() "${SUF}/diff2"
if diff "${SUF}/diff2" "${SUF}/diff3" 2>&1 > "${SUF}/testerr"
then	printf "%s\n" "\`ftw-driver compared equal to its control method"
else	printf "%s\n" "##ftw-driver failed to output to a file" 
	#RETVAL="1"
fi

./control/nftw-driver /tmp dmcp | sort > "${SUF}/diff2" 2> "${SUF}/testerr"
./tests/nftw-driver /tmp dmcp | sort > "${SUF}/diff3" 2> "${SUF}/testerr"
checkifempty() "${SUF}/diff2"
if diff "${SUF}/diff2" "${SUF}/diff3" 2>&1 > "${SUF}/testerr"
then	printf "%s\n" "\`nftw-driver compared equal to its control method"
else	printf "%s\n" "##nftw-driver failed to output to a file" 
	#RETVAL="1"
fi

for i in `seq 1 256`
do	printf "%s" "ABCD" >> "${SUF}/test.txt"
done
printf "%s" "EEEE" >> "${SUF}/test.txt"
./control/getline-driver "${SUF}/test.txt" > "${SUF}/diff2" 2> "${SUF}/testerr"
./tests/getline-driver "${SUF}/test.txt" > "${SUF}/diff3" 2> "${SUF}/testerr"
checkifempty() "${SUF}/diff2"
if diff "${SUF}/diff2" "${SUF}/diff3" 2>&1 > "${SUF}/testerr"
then	printf "%s\n" "\`getline-driver compared equal to its control method"
else	printf "%s\n" "##getline-driver failed to read lines from file" 
	#RETVAL="1"
fi

printf "============================================================\n"

exit "$RETVAL"
