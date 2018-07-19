# Usage: ./tools/build.sh gcc $(pwd)/system-root

# Build and install hlibc
make clean
CC="$1" ./configure --prefix="${2}" --enable-gcc-wrapper --disable-shared
CC="$1" make
make install

cd "${2}"

# retrieve and build hlibc-test (passing it two compilers(libc) to compare)
git clone https://git.hlibc.xyz/lab/hlibc-test.git
./hlibc-test/build.sh "${1}" "${2}/bin/${1}-wrap"

exit 0

