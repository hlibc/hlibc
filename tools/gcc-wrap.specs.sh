# Gcc specs file to redirect linking options and handle crt stuffs (C run time)

# This file produces a gcc "specs" file which redirects gcc's linking options
# ergo allowing a different libc to be used without installing it.
# In the simplest case, something like: `gcc example.c libc.a crt*.o' would
# sort of work. But because the compiler needs a specific arrangement of
# crt1.o (start), crti.o (?) and crti.o (end) to mix with its own internal
# crtbeginS.o and crtendS.o we instead use the proper method for gcc which is
# again, the "gcc specs file". The POSIX shell HERE document below expands
# the specified locations of hlibc's crt files and creates the needed gcc
# specs file.
# For clang a different method is used and this file has no effect.


incdir=$1
libdir=$2
ldso=$3
cat <<EOF
%rename cpp_options old_cpp_options

*cpp_options:
-nostdinc -isystem $incdir %(old_cpp_options)

*cc1:
%(cc1_cpu) -nostdinc -isystem $incdir 

*link_libgcc:
-L$libdir

*libgcc:
libgcc.a%s %:if-exists(libgcc_eh.a%s)

*startfile:
$libdir/crt1.o $libdir/crti.o %{crtbeginS.o}

*endfile:
%{crtendS.o} $libdir/crtn.o

%rename link old_link

*link:
%(old_link) -dynamic-linker $ldso -nostdlib

*esp_link:


*esp_options:


*esp_cpp_options:


EOF
