#!/bin/sh


printf "%s\n" "#!/bin/sh" >tools/clang-wrap

printf "%s\n" "clang -D_GNU_SOURCE $3 $4 -fno-stack-protector -static -nostdinc -isystem ${1}/include --sysroot ${1}/ \$@ " >> tools/clang-wrap

chmod +x tools/clang-wrap
