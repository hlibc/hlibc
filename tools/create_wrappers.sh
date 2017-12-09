#!/bin/sh

printf "%s\n" "#!/bin/sh" >tools/gcc-wrap

printf "%s\n" "gcc -D_GNU_SOURCE -static -nostdinc -nostdlib -I$(pwd)/include \$@ $(pwd)/lib/Scrt1.o $(pwd)/lib/libc.a  " >> tools/gcc-wrap

printf "%s\n" "#!/bin/sh" >tools/clang-wrap

printf "%s\n" "clang -D_GNU_SOURCE -static -nostdinc -nostdlib -I$(pwd)/include \$@ $(pwd)/lib/Scrt1.o $(pwd)/lib/libc.a  " >> tools/clang-wrap

chmod +x tools/gcc-wrap
chmod +x tools/clang-wrap
