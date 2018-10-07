# hlibc makefile

binaries = $(exec_prefix)/bin
prefix = /usr/local/hlibc
includes = $(prefix)/include
libraries = $(prefix)/lib
syslibraries = /lib

SRCS = $(sort $(wildcard src/*/*.c))
OBJS = $(SRCS:.c=.o)
GENH = include/bits/alltypes.h

CPPFLAGS =
FREESTANDING = -std=c99 -ffreestanding -nostdinc
CFLAGS_STATIC = $(FREESTANDING)
CFLAGS_STATIC += -D_XOPEN_SOURCE=700 -I./include -I./arch/$(ARCH) -I./os/$(OPERATING_SYSTEM)/$(ARCH)
CFLAGS_STATIC += $(CPPFLAGS) $(CFLAGS)

AR = ar
RANLIB = ranlib
ALL_INCLUDES = $(sort $(wildcard include/*.h include/*/*.h) $(GENH))
CRT_LIBS = lib/crt1.o lib/crti.o lib/crtn.o
TOOL_LIBS = lib/gcc-wrap.specs
EMPTY_LIBS = lib/libm.a
STATIC_LIBS = lib/libc.a

ALL_LIBS = $(CRT_LIBS) $(STATIC_LIBS) $(EMPTY_LIBS) $(TOOL_LIBS)
ALL_TOOLS = tools/compiler

-include config.mak

WRAP_OPT = -fno-stack-protector -static -D_GNU_SOURCE

all: $(ALL_LIBS) $(ALL_TOOLS) $(ALL_TOOLS:tools/%=/lib)

install: $(ALL_LIBS:lib/%=$(DESTDIR)$(libraries)/%) $(ALL_INCLUDES:include/%=$(DESTDIR)$(includes)/%) $(ALL_TOOLS:tools/%=$(DESTDIR)$(binaries)/%)

clean:
	-$(RM) -f crt/*.o
	-$(RM) -f $(OBJS)
	-$(RM) -f $(ALL_LIBS) lib/*.[ao]
	-$(RM) -f $(ALL_TOOLS)
	-$(RM) -f $(GENH) 
	-$(RM) -rf include/bits
	-$(RM) -f config.mak

cleanall:
	-rm -rf system-root

include/bits:
	@test "$(ARCH)" || echo "\n\tPlease run ./configure first\n"
	@test "$(ARCH)" || echo "\tOr use 'make test' to invoke the test suite\n"
	@test "$(ARCH)" || exit 1
	mkdir -p include/bits/
	cp -r arch/$(ARCH)/bits/* include/bits/
	cp -r os/$(OPERATING_SYSTEM)/$(ARCH)/bits/* include/bits/

include/bits/alltypes.h.sh: include/bits

include/bits/alltypes.h: include/bits/alltypes.h.sh
	sh $< > $@

%.o: $(ARCH)/%.s
	$(CC) $(CFLAGS_STATIC) -c -o $@ $<

%.o: %.c $(GENH)
	$(CC) $(CFLAGS_STATIC) -c -o $@ $<

lib/libc.a: $(OBJS)
	$(RM) -f $@
	$(AR) rc $@ $(OBJS)
	$(RANLIB) $@

$(EMPTY_LIBS):
	$(RM) -f $@
	$(AR) rc $@

lib/%.o: crt/%.o
	cp $< $@

tools/compiler: config.mak
	printf '#!/bin/sh\n' > $@
	printf 'printf "cc = "\n' >> $@
	printf 'set -x\n' >> $@
ifeq ($(CC_IS_CLANG),yes)
	printf 'clang $(WRAP_OPT) -nostdinc -isystem $(prefix)/include --sysroot $(prefix) "$$@" ' >> $@
else
	printf 'exec gcc $(DISABLE_PIE) $(WRAP_OPT) "$$@" -specs %s/gcc-wrap.specs\n' "$(libraries)" >> $@
endif
	chmod +x $@

$(DESTDIR)$(binaries)/%: tools/%
	mkdir -p $(prefix)/bin
	cp -a $< $@

$(DESTDIR)$(libraries)/%: lib/%
	mkdir -p $(prefix)/lib
	cp -a $< $@

$(DESTDIR)$(includes)/%: include/%
	cp -a include $(prefix)

$(DESTDIR)$(syslibraries):
	install -d -m 755 $(DESTDIR)$(syslibraries)

lib/gcc-wrap.specs: tools/gcc-wrap.specs.sh config.mak
	sh $< "$(includes)" "$(libraries)"  > $@

test:
	-$(MAKE) -C system-root/hlibc-test/ clean
	-$(RM) -rf system-root/bin system-root/lib system-root/include
	./tools/build.sh $(CC) $(PWD)/system-root/

release:
	./tools/.release

.PRECIOUS: $(CRT_LIBS:lib/%=crt/%)

.PHONY: all clean install

