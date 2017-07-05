#!/bin/sh

./clean.sh

make distclean

./configure --prefix="./installation"

printf "\ngrafmusl is logging to buildlog\n"

make -j4 > buildlog 2>&1

make install

./installation/bin/musl-gcc tests/cat.c -o cat_dynamic

./installation/bin/musl-gcc tests/cat.c -o cat_static -static

./installation/bin/musl-gcc tests/pow_test.c -o pow_test -static -lm

./installation/bin/musl-gcc tests/malloc-driver.c -o malloc_driver -static -lm 

./installation/bin/musl-gcc tests/popen-driver.c -o popen_driver -static -lm 

./pow_test

./cat_static Makefile > diff1

diff Makefile diff1 && echo "The \`cat' utility successfully copied a file"

gcc tests/malloc-driver.c -o control_malloc_driver -static -lm

./control_malloc_driver src >diff2

./malloc_driver src >diff3

diff diff2 diff3 && echo "The \`malloc_driver' test utility successfully iterated through a dir cnd ompared equal to its control methode"

