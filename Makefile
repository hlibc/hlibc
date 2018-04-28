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
LOBJS = $(OBJS:.o=.lo)
GENH = include/bits/alltypes.h
IMPH = musllibc/internal/libc.h

# test suite
GCC_WRAP = CC="$(prefix)/bin/gcc-wrap -D_GNU_SOURCE -static -fno-stack-protector"
CLANG_WRAP = CC="$(prefix)/bin/clang-wrap -D_GNU_SOURCE -static -fno-stack-protector"
TEST_SRCS = $(sort $(wildcard tests/*.c) $(wildcard posix-utils/*.c) )
TEST_OBJ = $(TEST_SRCS:.c=) 
CONTROL_SRCS = $(sort $(wildcard control/*.c) $(wildcard posix-utils-control/*.c) )
CONTROL_OBJ = $(CONTROL_SRCS:.c=)

LDFLAGS = 
CPPFLAGS =
#CFLAGS = -Os -pipe
CFLAGS = -Wall -Wextra
CFLAGS_C99FSE = -std=c99 -ffreestanding -nostdinc 

CFLAGS_ALL = $(CFLAGS_C99FSE)
CFLAGS_ALL += -D_XOPEN_SOURCE=700 -I./musllibc/internal -I./fdlibm/internal -I./include -I./arch/$(ARCH)
CFLAGS_ALL += $(CPPFLAGS) $(CFLAGS)
CFLAGS_ALL_STATIC = $(CFLAGS_ALL)

AR      = $(CROSS_COMPILE)ar
RANLIB  = $(CROSS_COMPILE)ranlib

ALL_INCLUDES = $(sort $(wildcard include/*.h include/*/*.h) $(GENH))

EMPTY_LIB_NAMES = m rt pthread crypt util xnet resolv dl ssp ssp_nonshared
EMPTY_LIBS = $(EMPTY_LIB_NAMES:%=lib/lib%.a)
CRT_LIBS = lib/crt1.o lib/crti.o lib/crtn.o
STATIC_LIBS = lib/libc.a
TOOL_LIBS = lib/gcc-wrap.specs
ALL_LIBS = $(CRT_LIBS) $(STATIC_LIBS) $(EMPTY_LIBS) $(TOOL_LIBS)
ALL_TOOLS = tools/gcc-wrap

-include config.mak

CFLAGS += -Wall -Wextra -fno-stack-protector

LDSO_PATHNAME = $(syslibdir)/ld-hlibc-$(ARCH).so.1

all: $(ALL_LIBS) $(ALL_TOOLS)

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
	printf '#!/bin/sh\nexec gcc -fno-stack-protector -static -D_GNU_SOURCE "$$@" -specs "%s/gcc-wrap.specs"\n' "$(libdir)" > $@
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
	LDFLAGS="" CFLAGS="" LDLIBS="" make CC="" LDFLAGS="" CFLAGS="-static" LDLIBS="-lm" $(GCC_WRAP) testing
	LDFLAGS="" CFLAGS="" LDLIBS="" make LDLIBS="-lm" control 2>/dev/null

clangtests:
	LDFLAGS="" CFLAGS="" LDLIBS="" make $(CLANG_WRAP) testing
	LDFLAGS="" CFLAGS="" LDLIBS="" make LDFLAGS="" CFLAGS="-static" LDLIBS="-lc -lm" control 2>/dev/null

gcctest:
	./tools/build.sh gcctests gcc || exit 1

clangtest:
	./tools/build.sh clangtests clang || exit 1

.PRECIOUS: $(CRT_LIBS:lib/%=crt/%)

.PHONY: all clean install tests control
