#
# Makefile for musl (requires GNU make)
#
# This is how simple every makefile should be...
# No, I take that back - actually most should be less than half this size.
#
# Use config.mak to override any of the following variables.
# Do not make changes here.
#

exec_prefix = /usr/local
bindir = $(exec_prefix)/bin

prefix = /usr/local/musl
includedir = $(prefix)/include
libdir = $(prefix)/lib
syslibdir = /lib

#SRCS = $(sort $(wildcard src/*/*.c))
SRCS = $(sort $(wildcard musllibc/*/*.c hlibc/*/*.c fdlibm/*/*.c))

# test suite
GCC_WRAP = CC="$(prefix)/bin/gcc-wrap -D_GNU_SOURCE -static -fno-stack-protector -fPIC"
CLANG_WRAP = CC="$(prefix)/bin/clang-wrap -D_GNU_SOURCE -static -fno-stack-protector -fPIC"

OBJS = $(SRCS:.c=.o)
LOBJS = $(OBJS:.o=.lo)
GENH = include/bits/alltypes.h
#IMPH = src/internal/stdio_impl.h src/internal/pthread_impl.h src/internal/libc.h
IMPH = musllibc/internal/libc.h
LDFLAGS = 
CPPFLAGS =
CFLAGS = -Os -pipe
CFLAGS_C99FSE = -std=c99 -ffreestanding -nostdinc 

CFLAGS_ALL = $(CFLAGS_C99FSE)
CFLAGS_ALL += -D_XOPEN_SOURCE=700 -I./src/internal -I./include -I./arch/$(ARCH)
CFLAGS_ALL += $(CPPFLAGS) $(CFLAGS)
CFLAGS_ALL_STATIC = $(CFLAGS_ALL)
CFLAGS_ALL_SHARED = $(CFLAGS_ALL) -fPIC -DSHARED -O3

AR      = $(CROSS_COMPILE)ar
RANLIB  = $(CROSS_COMPILE)ranlib

ALL_INCLUDES = $(sort $(wildcard include/*.h include/*/*.h) $(GENH))

EMPTY_LIB_NAMES = m rt pthread crypt util xnet resolv dl
EMPTY_LIBS = $(EMPTY_LIB_NAMES:%=lib/lib%.a)
CRT_LIBS = lib/crt1.o lib/Scrt1.o lib/crti.o lib/crtn.o
CRT_LIBS = lib/crt1.o lib/crti.o lib/crtn.o
STATIC_LIBS = lib/libc.a
SHARED_LIBS = lib/libc.so
#TOOL_LIBS = lib/musl-gcc.specs
ALL_LIBS = $(CRT_LIBS) $(STATIC_LIBS) $(SHARED_LIBS) $(EMPTY_LIBS) $(TOOL_LIBS)
#ALL_TOOLS = tools/musl-gcc
TOOL_LIBS = lib/gcc-wrap.specs  lib/gcc-wrap-uninstalled.specs

ALL_TOOLS = tools/gcc-wrap tools/gcc-wrap-uninstalled
LDSO_PATHNAME = $(syslibdir)/ld-musl-$(ARCH).so.1

-include config.mak

all: $(ALL_LIBS) $(ALL_TOOLS)

install: $(ALL_LIBS:lib/%=$(DESTDIR)$(libdir)/%) $(ALL_INCLUDES:include/%=$(DESTDIR)$(includedir)/%) $(ALL_TOOLS:tools/%=$(DESTDIR)$(bindir)/%) $(if $(SHARED_LIBS),$(DESTDIR)$(LDSO_PATHNAME),)

clean:
	rm -f crt/*.o
	rm -f $(OBJS)
	rm -f $(LOBJS)
	rm -f $(ALL_LIBS) lib/*.[ao] lib/*.so
	rm -f $(ALL_TOOLS)
	rm -f $(GENH) 
	rm -f include/bits

distclean: clean
	rm -f config.mak

include/bits:
	@test "$(ARCH)" || { echo "Please set ARCH in config.mak before running make." ; exit 1 ; }
	ln -sf ../arch/$(ARCH)/bits $@

include/bits/alltypes.h.sh: include/bits

include/bits/alltypes.h: include/bits/alltypes.h.sh
	sh $< > $@

%.o: $(ARCH)/%.s
	$(CC) $(CFLAGS_ALL_STATIC) -c -o $@ $<

%.o: %.c $(GENH) $(IMPH)
	$(CC) $(CFLAGS_ALL_STATIC) -c -o $@ $<

%.lo: $(ARCH)/%.s
	$(CC) $(CFLAGS_ALL_SHARED) -c -o $@ $<

%.lo: %.c $(GENH) $(IMPH)
	$(CC) $(CFLAGS_ALL_SHARED) -c -o $@ $<

lib/libc.so: $(LOBJS)
	$(CC) $(CFLAGS_ALL_SHARED) $(LDFLAGS) -nostdlib -shared \
	-Wl,-e,_start -Wl,-Bsymbolic-functions \
	-Wl,-soname=libc.so -o $@ $(LOBJS) -lgcc

lib/libc.a: $(OBJS)
	rm -f $@
	$(AR) rc $@ $(OBJS)
	$(RANLIB) $@

$(EMPTY_LIBS):
	rm -f $@
	$(AR) rc $@

lib/%.o: crt/%.o
	cp $< $@

tools/gcc-wrap: config.mak
	printf '#!/bin/sh\nexec gcc -fno-stack-protector -static -D_GNU_SOURCE "$$@" -specs "%s/gcc-wrap.specs"\n' "$(libdir)" > $@
	chmod +x $@

tools/gcc-wrap-uninstalled: config.mak
	printf '#!/bin/sh\nexec gcc -fno-stack-protector -static -D_GNU_SOURCE "$$@" -specs "%s/gcc-wrap-uninstalled.specs"\n' "$(PWD)/lib/" > $@
	chmod +x $@







$(DESTDIR)$(bindir)/%: tools/%
	install -D $< $@

$(DESTDIR)$(libdir)/%.so: lib/%.so
	install -D -m 755 $< $@

$(DESTDIR)$(libdir)/%: lib/%
	install -D -m 644 $< $@

$(DESTDIR)$(includedir)/%: include/%
	install -D -m 644 $< $@

$(DESTDIR)$(LDSO_PATHNAME): $(DESTDIR)$(syslibdir)
	ln -sf $(libdir)/libc.so $@ || true

$(DESTDIR)$(syslibdir):
	install -d -m 755 $(DESTDIR)$(syslibdir)
lib/gcc-wrap.specs: tools/gcc-wrap.specs.sh config.mak
	sh $< "$(includedir)" "$(libdir)"  > $@
lib/gcc-wrap-uninstalled.specs: tools/gcc-wrap.specs.sh config.mak
	sh $< "$(PWD)/include" "$(PWD)/lib/"  > $@

gcctests:
	cd posix-utils/ && $(GCC_WRAP) make
	cd posix-utils-control/ && make
	cd tests/ && $(GCC_WRAP) make
	cd control && make

clangtests:
	cd posix-utils/ && $(CLANG_WRAP) make
	cd posix-utils-control/ && make
	cd tests/ && $(CLANG_WRAP) make
	cd control && make

gcctest:
	./tools/build.sh gcctests gcc || exit 1

clangtest:
	./tools/build.sh clangtests clang || exit 1

.PRECIOUS: $(CRT_LIBS:lib/%=crt/%)

.PHONY: all clean install
