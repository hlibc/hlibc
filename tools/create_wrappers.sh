#!/bin/sh

printf "%s\n" "#!/bin/sh" >tools/gcc-wrap-new.sh

printf "%s\n" "gcc -D_GNU_SOURCE -nostdinc -nostdlib -I$(pwd)/include \$@ $(pwd)/lib/Scrt1.o $(pwd)/lib/libc.a  " >> tools/gcc-wrap-new.sh

printf "%s\n" "#!/bin/sh" >tools/clang-wrap-new.sh

# Adding _GNU_SOURCE to clang produces tons of errors
printf "%s\n" "clang -nostdinc -nostdlib -I$(pwd)/include \$@ $(pwd)/lib/Scrt1.o $(pwd)/lib/libc.a  " >> tools/clang-wrap-new.sh

chmod +x tools/gcc-wrap-new.sh
chmod +x tools/clang-wrap-new.sh
