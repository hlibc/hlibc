#!/bin/sh

rm -rf installation buildlog cat_static cat_dynamic pow_test malloc_driver

make distclean

./configure --prefix="./installation"

printf "\ngrafmusl is logging to buildlog\n"

make -j4 > buildlog 2>&1

make install

./installation/bin/musl-gcc tests/cat.c -o cat_dynamic

./installation/bin/musl-gcc tests/cat.c -o cat_static -static

./installation/bin/musl-gcc tests/pow_test.c -o pow_test -static -lm

./installation/bin/musl-gcc tests/malloc-driver.c -o malloc_driver -static -lm 

./pow_test

