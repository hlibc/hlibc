#!/bin/sh

printf "%s\n" "#!/bin/sh" >tools/clang-wrap

printf "%s\n" "clang -D_GNU_SOURCE -static -nostdinc -isystem $(pwd)/include  --sysroot $(pwd)/usr \$@ " >> tools/clang-wrap

chmod +x tools/clang-wrap
