#!/bin/sh

rm -rf installation buildlog cat_static cat_dynamic

make distclean

./configure --prefix="./installation"

printf "\ngrafmusl is logging to buildlog\n"

make -j4 > buildlog 2>&1

make install

./installation/bin/musl-gcc tests/cat.c -o cat_dynamic

./installation/bin/musl-gcc tests/cat.c -o cat_static -static



