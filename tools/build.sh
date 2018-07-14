# Usage: ./tools/build.sh gcc $(pwd)/usr

# Build and install hlibc
make clean
CC="$1" ./configure --prefix="${2}" --enable-gcc-wrapper --disable-shared
CC="$1" make
make install

mkdir tests
cd tests

# retrieve and build hlibc-test (passing it two compilers(libc) to compare)
git clone https://git.hlibc.xyz/lab/hlibc-test.git
./hlibc-test/build.sh $1 ${2}/bin/${1}-wrap


# GNU bc
[ -d bc-1.03 ] || {
	wget https://ftp.gnu.org/gnu/bc/bc-1.03.tar.gz 
	tar -xf bc-1.03.tar.gz 
}

echo "Building GNU bc-1.03 .."
(
	cd bc-1.03
	sed 's/.*getopt.*//g' proto.h > bak # this is broken in bc-1.03
	mv bak proto.h

	CC=${2}/bin/${1}-wrap ./configure >/dev/null 2>&1
	CC=${2}/bin/${1}-wrap make > /dev/null 2>&1

	printf "\n"
	printf "1234567*1234567\n" | ./bc -l
	printf "should be 1524155677489 if bc-1.03 is working\n"
	printf "\n\n"
)



