#!/bin/sh

TOOLING="./installation/"

./clean.sh

./configure --prefix=${TOOLING}

printf "\ngrafmusl is logging to buildlog\n\n"

make -j4 > buildlog 2>&1

make install

${TOOLING}/bin/musl-gcc tests/cat.c -o cat_dynamic

${TOOLING}/bin/musl-gcc tests/cat.c -o cat_static -static

${TOOLING}/bin/musl-gcc tests/pow_test.c -o pow_test -static -lm

${TOOLING}/bin/musl-gcc tests/malloc-driver.c -o malloc_driver -static -lm 

${TOOLING}/bin/musl-gcc tests/popen-driver.c -o popen_driver -static -lm 

gcc tests/malloc-driver.c -o control_malloc_driver -static -lm

echo "==========TEST SUITE START=================================="

./pow_test

./cat_static Makefile > diff1 2>testerr

diff Makefile diff1 2>&1 > testerr && echo "The \`cat' utility successfully copied a file" || echo "cat util failed"

./control_malloc_driver src >diff2 2>testerr

./malloc_driver src >diff3 2>testerr

diff diff2 diff3 2>&1 > testerr && echo "The \`malloc_driver' test utility successfully iterated through a dir and compared equal to its control method" || echo "malloc driver failed"

echo "============================================================"
