#!/bin/sh

# Usage: ./build.sh control-compiler research-compiler


BASIC_TYPE="	stat-driver .
		lstat-driver .
		printf-zeropad
		printf-fieldpad
		printf-leftadj
		printf-pad-string
		printf-field
		snprintf-driver
		atoll-small
		strtoull-driver
		strtoll-driver
		fopen
		malloc-huge
		ctype
		malloc-unique-pointer
		getline-driver
		atoi
		atol
		atoll
		getenv-driver
		hcreate-driver
		printf-driver
		printf-driver-integers
		strstr-driver
		strstr-effectiveness2
		realloc-filetreewalk ../include
		popen-driver du ../include
		puts-driver
		strerror-driver
		pow_test
		getopt -ao arg path path
		getopt -a -o arg path path
		getopt -o arg -a path path
		getopt -a -o arg -- path path
		getopt -a -oarg path path
		getopt -aoarg path path
		strsep-driver
		index
		memmove
		time
		fwrite
		strchr-driver
"

COULD_FAIL="	environ
"

HBOX_TYPE="	gsh ./hbox/gsh.sh
"

RETVAL="0"

checkifempty()
{
	if [ ! -s "$1" ]
	then    printf "%s\n" "empty test file, something went wrong!!"
		printf "%s\n" "Returning failure for the entire test suite!!"
		echo "RETVAL=1" > retval
	fi
}

displaydiff()
{
	grep '^<' "${SUF}/testerr" | tail
	grep '^>' "${SUF}/testerr" | tail
}


cd hlibc-test
SUF="$(pwd)/logs/"
mkdir -p "${SUF}"

cp -r tests-comparative tests-comparative-research
cp -r tests-comparative tests-comparative-control

cp -r hbox hbox-research
cp -r hbox hbox-control

printf "==========COMPILING TESTS ===================================\n"
(
	cd tests-comparative-research
	CC="$2" make
)
(
	cd tests-comparative-control
	CC="$1" make
)
(
	cd hbox-research
	CC="$2" make
)
(
	cd hbox-control
	CC="$1" make
)
(
	cd tests-emperical
	CC="$2" make
)
printf "=============================================================\n"
printf "==========TEST RESULT START==================================\n"

echo "RETVAL=$RETVAL" > retval

printf "%s" "$BASIC_TYPE" | while read -r i
do	./tests-comparative-research/${i} > "${SUF}/diff2"	# don't quote ./tests/{i} or ./control/{i} 
	./tests-comparative-control/${i} > "${SUF}/diff3"	# so that they can be expanded as arguments
	checkifempty "${SUF}/diff2"
	if diff "${SUF}/diff2" "${SUF}/diff3" 2>&1 > "${SUF}/testerr"
	then	printf "%s\n" "\`${i}' compared equal to its control method"
	else	printf "%s\n" "##${i} failed to compare equal to its control method"
		echo "RETVAL=1" > retval
		displaydiff
	fi
done

printf "%s" "$HBOX_TYPE" | while read -r i
do	./hbox-research/${i} > "${SUF}/diff2"
	./hbox-control/${i} > "${SUF}/diff3"
	checkifempty "${SUF}/diff2"
	if diff "${SUF}/diff2" "${SUF}/diff3" 2>&1 > "${SUF}/testerr"
	then	printf "%s\n" "\`${i}' compared equal to its control method"
	else	printf "%s\n" "##${i} failed to compare equal to its control method"
		echo "RETVAL=1" > retval
		displaydiff
	fi
done

# some emperical tests
(
	./tests-emperical/stdio_strtol_cross_proof
	./tests-emperical/atexit
)

# libc-test-fork
(
	cd libc-test-fork
	CC="$2" make
	./testsuite
)

# GNU bc
[ -d bc-1.03 ] || {
        wget https://ftp.gnu.org/gnu/bc/bc-1.03.tar.gz
        tar -xf bc-1.03.tar.gz
}

echo "Building GNU bc-1.03 .."
(
        [ -d bc-1.03 ] && cd bc-1.03 && {
        sed 's/.*getopt.*//g' proto.h > bak # this is broken in bc-1.03
        mv bak proto.h

        CC="$2" ./configure >/dev/null 2>&1
        CC="$2" make > /dev/null 2>&1

        printf "\n"
        printf "1234567*1234567\n" | ./bc -l
        printf "should be 1524155677489 if bc-1.03 is working\n"
        pwd
        printf "\n\n"
        }
)

# get the error code after forks
. ./retval

echo "returning $RETVAL .. "

exit $RETVAL



