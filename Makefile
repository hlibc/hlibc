# Use gmake
# Use config.mak to override any of the following variables.
# Do not make changes here.
#

exec_prefix = /usr/local
bindir = $(exec_prefix)/bin

prefix = /usr/local/musl
includedir = $(prefix)/include
libdir = $(prefix)/lib
syslibdir = /lib

SRCS = $(sort $(wildcard musllibc/*/*.c hlibc/*/*.c fdlibm/*/*.c))
OBJS = $(SRCS:.c=.o)
LOBJS = $(OBJS:.o=.lo)
GENH = include/bits/alltypes.h
IMPH = musllibc/internal/pthread_impl.h musllibc/internal/libc.h

# test suite
GCC_WRAP = CC="$(prefix)/bin/gcc-wrap -D_GNU_SOURCE -static" 
CLANG_WRAP = CC="$(prefix)/bin/clang-wrap -D_GNU_SOURCE -static"
TEST_SRCS = $(sort $(wildcard tests/*.c) $(wildcard posix-utils/*.c) )
TEST_OBJ = $(TEST_SRCS:.c=) 
CONTROL_SRCS = $(sort $(wildcard control/*.c) $(wildcard posix-utils-control/*.c) )
CONTROL_OBJ = $(CONTROL_SRCS:.c=)

LDFLAGS = 
CPPFLAGS =
#CFLAGS = -Os -pipe
CFLAGS =
CFLAGS_C99FSE = -std=c99 -ffreestanding -nostdinc 

CFLAGS_ALL = $(CFLAGS_C99FSE)
CFLAGS_ALL += -D_XOPEN_SOURCE=700 -I./musllibc/internal -I./fdlibm/internal -I./include -I./arch/$(ARCH)
CFLAGS_ALL += $(CPPFLAGS) $(CFLAGS)
CFLAGS_ALL_STATIC = $(CFLAGS_ALL)
CFLAGS_ALL_SHARED = $(CFLAGS_ALL) -fPIC -DSHARED -O3

AR      = $(CROSS_COMPILE)ar
RANLIB  = $(CROSS_COMPILE)ranlib

ALL_INCLUDES = $(sort $(wildcard include/*.h include/*/*.h) $(GENH))

EMPTY_LIB_NAMES = m rt pthread crypt util xnet resolv dl
EMPTY_LIBS = $(EMPTY_LIB_NAMES:%=lib/lib%.a)
#CRT_LIBS = lib/crt1.o lib/Scrt1.o lib/crti.o lib/crtn.o
CRT_LIBS = lib/crt1.o lib/crti.o lib/crtn.o
STATIC_LIBS = lib/libc.a
SHARED_LIBS = lib/libc.so
TOOL_LIBS = lib/gcc-wrap.specs
ALL_LIBS = $(CRT_LIBS) $(STATIC_LIBS) $(SHARED_LIBS) $(EMPTY_LIBS) $(TOOL_LIBS)
ALL_TOOLS = tools/gcc-wrap

-include config.mak

LDSO_PATHNAME = $(syslibdir)/ld-musl-$(ARCH).so.1

all: $(ALL_LIBS) $(ALL_TOOLS)

install: $(ALL_LIBS:lib/%=$(DESTDIR)$(libdir)/%) $(ALL_INCLUDES:include/%=$(DESTDIR)$(includedir)/%) $(ALL_TOOLS:tools/%=$(DESTDIR)$(bindir)/%)
	-./tools/create_wrappers.sh
	-cp tools/clang-wrap $(DESTDIR)$(bindir)

clean:
	-$(RM) -f crt/*.o
	-$(RM) -f $(OBJS)
	-$(RM) -f $(LOBJS)
	-$(RM) -f $(ALL_LIBS) lib/*.[ao] lib/*.so
	-$(RM) -f $(ALL_TOOLS)
	-$(RM) -f $(GENH) 
	-$(RM) -f include/bits
	-$(RM) -f config.mak
	-$(RM) -rf usr logs
	-$(RM) -f test_*
	-$(RM) -f tools/clang-wrap
	-$(RM) -f $(TEST_OBJ) $(CONTROL_OBJ) 
	-$(RM) -r control
	-$(RM) -r posix-utils-control

include/bits:
	@test "$(ARCH)" || { echo "Please set ARCH in config.mak before running make. Or run 'make gcctest|clangtest' to invoke the test suite" ; exit 1 ; }
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
	$(RM) -f $@
	$(AR) rc $@ $(OBJS)
	$(RANLIB) $@

$(EMPTY_LIBS):
	$(RM) -f $@
	$(AR) rc $@

lib/%.o: crt/%.o
	cp $< $@

tools/gcc-wrap: config.mak
	printf '#!/bin/sh\nexec gcc -static -D_GNU_SOURCE "$$@" -specs "%s/gcc-wrap.specs"\n' "$(libdir)" > $@
	chmod +x $@

$(DESTDIR)$(bindir)/%: tools/%
	install -D $< $@

$(DESTDIR)$(libdir)/%.so: lib/%.so
	install -D -m 755 $< $@

$(DESTDIR)$(libdir)/%: lib/%
	install -D -m 644 $< $@

$(DESTDIR)$(includedir)/%: include/%
	install -D -m 644 $< $@

$(DESTDIR)$(syslibdir):
	install -d -m 755 $(DESTDIR)$(syslibdir)

lib/gcc-wrap.specs: tools/gcc-wrap.specs.sh config.mak
	sh $< "$(includedir)" "$(libdir)" "$(LDSO_PATHNAME)" > $@

$(DESTDIR)$(LDSO_PATHNAME): $(DESTDIR)$(syslibdir)
	ln -sf $(libdir)/libc.so $@ || true

testing: $(TEST_OBJ)

control: $(CONTROL_OBJ)

gcctests:
	$(MAKE) $(GCC_WRAP) testing
	CFLAGS="-static" LDLIBS="-lm" $(MAKE) control 2>/dev/null

clangtests:
	$(MAKE) $(CLANG_WRAP) testing
	LDLIBS="-lm" $(MAKE) control 2>/dev/null

gcctest:
	./tools/build.sh gcctests gcc

clangtest:
	./tools/build.sh clangtests clang

.PRECIOUS: $(CRT_LIBS:lib/%=crt/%)

.PHONY: all clean install tests control
