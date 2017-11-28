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
TEST_SRCS = $(sort $(wildcard tests/*.c))
TEST_OBJ = $(TEST_SRCS:.c=) 
CONTROL_SRCS = $(sort $(wildcard control/*.c))
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
CRT_LIBS = lib/crt1.o lib/Scrt1.o lib/crti.o lib/crtn.o
STATIC_LIBS = lib/libc.a
SHARED_LIBS = lib/libc.so
ALL_LIBS = $(CRT_LIBS) $(STATIC_LIBS) $(SHARED_LIBS) $(EMPTY_LIBS)

LDSO_PATHNAME = $(syslibdir)/ld-musl-$(ARCH).so.1

-include config.mak

all: $(ALL_LIBS) $(ALL_TOOLS)

install: $(ALL_LIBS:lib/%=$(DESTDIR)$(libdir)/%) $(ALL_INCLUDES:include/%=$(DESTDIR)$(includedir)/%) $(if $(SHARED_LIBS),$(DESTDIR)$(LDSO_PATHNAME),)
	-mkdir $(DESTDIR)$(bindir)
	./tools/create_wrappers.sh
	cp tools/gcc-wrap $(DESTDIR)/$(prefix)/bin/
	cp tools/clang-wrap $(DESTDIR)/$(prefix)/bin/

clean:
	rm -f crt/*.o
	rm -f $(OBJS)
	rm -f $(LOBJS)
	rm -f $(ALL_LIBS) lib/*.[ao] lib/*.so
	rm -f $(ALL_TOOLS)
	rm -f $(GENH) 
	rm -f include/bits
	make clean_test
	rm -f config.mak
	rm -rf usr logs
	rm tools/clang-wrap
	rm tools/gcc-wrap
	$(MAKE) clean_test 
	

include/bits:
	@test "$(ARCH)" || { echo "Please set ARCH in config.mak before running make. Or run 'make test' to invoke the suite" ; exit 1 ; }
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

testing: $(TEST_OBJ)

control: $(CONTROL_OBJ)

tests:

	#$(MAKE) $(GCC_WRAP_D) testing
	#rm -rf $(TEST_OBJ)
	$(MAKE) $(GCC_WRAP) testing
	LDLIBS="-lm" $(MAKE) control 2>/dev/null

ctests:

	CC=clang $(MAKE) $(CLANG_WRAP) testing
	CC=clang LDLIBS="-lm" $(MAKE) control 2>/dev/null

clean_test:

	$(RM) $(TEST_OBJ) $(CONTROL_OBJ) 
	$(RM) -r control

test:

	./tools/build.sh

web:

	./.tx2html README

testclang:

	CC=clang ./tools/clangbuild.sh

.PRECIOUS: $(CRT_LIBS:lib/%=crt/%)

.PHONY: all clean install tests control
