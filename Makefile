exec_prefix = /usr/local
bindir = $(exec_prefix)/bin
prefix = /usr/local/hlibc
includedir = $(prefix)/include
libdir = $(prefix)/lib
syslibdir = /lib

SRCS = $(sort $(wildcard src/*/*.c))
OBJS = $(SRCS:.c=.o)
GENH = include/bits/alltypes.h

# test suite
GCC_WRAP = CC="$(prefix)/bin/gcc-wrap"
CLANG_WRAP = CC="$(prefix)/bin/clang-wrap"

LDFLAGS =
CPPFLAGS =
CFLAGS_C99FSE = -std=c99 -ffreestanding -nostdinc
CFLAGS_ALL = $(CFLAGS_C99FSE)
CFLAGS_ALL += -D_XOPEN_SOURCE=700 -I./include -I./arch/$(ARCH)
CFLAGS_ALL += $(CPPFLAGS) $(CFLAGS)
CFLAGS_ALL_STATIC = $(CFLAGS_ALL)
AR = $(CROSS_COMPILE)ar
RANLIB = $(CROSS_COMPILE)ranlib
ALL_INCLUDES = $(sort $(wildcard include/*.h include/*/*.h) $(GENH))
EMPTY_LIB_NAMES = m
EMPTY_LIBS = $(EMPTY_LIB_NAMES:%=lib/lib%.a)
CRT_LIBS = lib/crt1.o lib/crti.o lib/crtn.o
STATIC_LIBS = lib/libc.a
TOOL_LIBS = lib/gcc-wrap.specs
ALL_LIBS = $(CRT_LIBS) $(STATIC_LIBS) $(EMPTY_LIBS) $(TOOL_LIBS)
ALL_TOOLS = tools/gcc-wrap

-include config.mak

all: $(ALL_LIBS) $(ALL_TOOLS) $(ALL_TOOLS:tools/%=/lib)

install: $(ALL_LIBS:lib/%=$(DESTDIR)$(libdir)/%) $(ALL_INCLUDES:include/%=$(DESTDIR)$(includedir)/%) $(ALL_TOOLS:tools/%=$(DESTDIR)$(bindir)/%)
	-./tools/create_wrappers.sh $(prefix) $(libdir) > $(DESTDIR)/$(bindir)/clang-wrap
	-chmod +x $(DESTDIR)/$(bindir)/clang-wrap

clean:
	-$(RM) -f crt/*.o
	-$(RM) -f $(OBJS)
	-$(RM) -f $(LOBJS)
	-$(RM) -f $(ALL_LIBS) lib/*.[ao]
	-$(RM) -f $(ALL_TOOLS)
	-$(RM) -f $(GENH) 
	-$(RM) -rf include/bits
	-$(RM) -f config.mak
	-$(RM) -rf usr logs
	-$(RM) -f tools/clang-wrap
	-$(MAKE) -C system-root/hlibc-test/

cleanall:
	-rm -rf system-root

include/bits:
	@test "$(ARCH)" || echo "\n\tPlease set ARCH in config.mak before running make "
	@test "$(ARCH)" || echo "\tor use the ./configure script."
	@test "$(ARCH)" || { echo "\tRun 'make gcctest|clangtest' to invoke the test suite\n\n" ; exit 1 ; }
	cp -r arch/$(ARCH)/bits include/

include/bits/alltypes.h.sh: include/bits

include/bits/alltypes.h: include/bits/alltypes.h.sh
	sh $< > $@

%.o: $(ARCH)/%.c
	$(CC) $(CFLAGS_ALL_STATIC) -c -o $@ $<

%.o: $(ARCH)/%.s
	$(CC) $(CFLAGS_ALL_STATIC) -c -o $@ $<

%.o: %.c $(GENH)
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
	printf '#!/bin/sh\nexec gcc $(STACK_PROTECTOR) -fno-stack-protector -static -D_GNU_SOURCE "$$@" -specs "%s/gcc-wrap.specs"\n' "$(libdir)" > $@
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

gcctest:
	./tools/build.sh gcc $(PWD)/system-root/

clangtest:
	./tools/build.sh clang $(PWD)/system-root/

release:
	./tools/.release


.PRECIOUS: $(CRT_LIBS:lib/%=crt/%)

.PHONY: all clean install

