#!/bin/sh 

printf "%s\n" "#!/bin/sh" 
printf "%s\n" "clang -D_GNU_SOURCE $3 $4 -fno-stack-protector -static -nostdinc -isystem ${1}/include --sysroot ${1}/ \$@ "



