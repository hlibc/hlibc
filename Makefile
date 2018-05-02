# Use gmake
# Use config.mak to override any of the following variables.
# Do not make changes here.
#

exec_prefix = /usr/local
bindir = $(exec_prefix)/bin
prefix = /usr/local/hlibc
includedir = $(prefix)/include
libdir = $(prefix)/lib
syslibdir = /lib

SRCS = $(sort $(wildcard musllibc/*/*.c hlibc/*/*.c fdlibm/*/*.c))
OBJS = $(SRCS:.c=.o)
GENH = include/bits/alltypes.h
IMPH = musllibc/internal/libc.h

# test suite
GCC_WRAP = CC="$(prefix)/bin/gcc-wrap -D_GNU_SOURCE -static -fno-stack-protector -fPIC"
CLANG_WRAP = CC="$(prefix)/bin/clang-wrap -D_GNU_SOURCE -static -fno-stack-protector -fPIC"

LDFLAGS =
CPPFLAGS =
CFLAGS_C99FSE = -std=c99 -ffreestanding -nostdinc
CFLAGS_ALL = $(CFLAGS_C99FSE)
CFLAGS_ALL += -D_XOPEN_SOURCE=700 -I./musllibc/internal -I./include -I./arch/$(ARCH)
CFLAGS_ALL += $(CPPFLAGS) $(CFLAGS)
CFLAGS_ALL_STATIC = $(CFLAGS_ALL)
AR      = $(CROSS_COMPILE)ar
RANLIB  = $(CROSS_COMPILE)ranlib
ALL_INCLUDES = $(sort $(wildcard include/*.h include/*/*.h) $(GENH))
EMPTY_LIB_NAMES = m
EMPTY_LIBS = $(EMPTY_LIB_NAMES:%=lib/lib%.a)
CRT_LIBS = lib/crt1.o lib/crti.o lib/crtn.o
STATIC_LIBS = lib/libc.a
TOOL_LIBS = lib/gcc-wrap.specs  lib/gcc-wrap-uninstalled.specs
ALL_LIBS = $(CRT_LIBS) $(STATIC_LIBS) $(EMPTY_LIBS) $(TOOL_LIBS)
ALL_TOOLS = tools/gcc-wrap tools/gcc-wrap-uninstalled

-include config.mak

all: $(ALL_LIBS) $(ALL_TOOLS) $(ALL_TOOLS:tools/%=/lib)

install: $(ALL_LIBS:lib/%=$(DESTDIR)$(libdir)/%) $(ALL_INCLUDES:include/%=$(DESTDIR)$(includedir)/%) $(ALL_TOOLS:tools/%=$(DESTDIR)$(bindir)/%)
	-./tools/create_wrappers.sh $(prefix)
	-cp tools/clang-wrap $(DESTDIR)$(bindir)

clean:
	-$(RM) -f crt/*.o
	-$(RM) -f $(OBJS)
	-$(RM) -f $(LOBJS)
	-$(RM) -f $(ALL_LIBS) lib/*.[ao] lib/*.so
	-$(RM) -f $(ALL_TOOLS)
	-$(RM) -f $(GENH) 
	-$(RM) -rf include/bits
	-$(RM) -f config.mak
	-$(RM) -rf usr logs
	-$(RM) -f test_*
	-$(RM) -f tools/clang-wrap
	-$(RM) -r control
	-$(RM) -r posix-utils-control
	-$(MAKE) cleantest

cleantest:
	cd tests/ && make clean
	cd posix-utils/ && make clean

include/bits:
	@test "$(ARCH)" || echo "\n\tPlease set ARCH in config.mak before running make "
	@test "$(ARCH)" || echo "\tor use the ./configure script."
	@test "$(ARCH)" || { echo "\tRun 'make gcctest|clangtest' to invoke the test suite\n\n" ; exit 1 ; }
	cp -r arch/$(ARCH)/bits include/
	

include/bits/alltypes.h.sh: include/bits

include/bits/alltypes.h: include/bits/alltypes.h.sh
	sh $< > $@

%.o: $(ARCH)/%.c
	$(CC) $(CFLAGS_ALL_STATIC) -O2 -mpreferred-stack-boundary=3 -c -o $@ $<

%.o: $(ARCH)/%.s
	$(CC) $(CFLAGS_ALL_STATIC) -c -o $@ $<

%.o: %.c $(GENH) $(IMPH)
	$(CC) $(CFLAGS_ALL_STATIC) -c -o $@ $<

lib/libc.a: $(OBJS)
	$(RM) -f $@
	$(AR) rc $@ $(OBJS)
	$(RANLIB) $@

$(EMPTY_LIBS):
	$(RM) -f $@
	$(AR) rc $@

#ifeq ($(ARCH),aarch64)
#lib/%.o: crt/aarch64-internal/%.o
#	cp $< $@
#else
lib/%.o: crt/%.o
	cp $< $@
#endif

tools/gcc-wrap: config.mak
	printf '#!/bin/sh\nexec gcc -fno-stack-protector -static -D_GNU_SOURCE "$$@" -specs "%s/gcc-wrap.specs"\n' "$(libdir)" > $@
	chmod +x $@

tools/gcc-wrap-uninstalled: config.mak
	printf '#!/bin/sh\nexec gcc -fno-stack-protector -static -D_GNU_SOURCE "$$@" -specs "%s/gcc-wrap-uninstalled.specs"\n' "$(PWD)/lib/" > $@
	chmod +x $@

$(DESTDIR)$(bindir)/%: tools/%
	install -D $< $@

$(DESTDIR)$(libdir)/%: lib/%
	install -D -m 644 $< $@

$(DESTDIR)$(includedir)/%: include/%
	install -D -m 644 $< $@

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

.PHONY: all clean install tests control
