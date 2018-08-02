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
