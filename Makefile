# configure outputs to config.mak and this Makefile uses config.mak so
# changes here may be lost. use GNU make

RELENG ?= hlibc-0.1c
RELENG_MIR ?= http://www.csit.parkland.edu/~cgraff1/
RELENG_DIR ?= public_html
RELENG_SSH ?= cgraff1@shaula.csit.parkland.edu

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
GCC_WRAP = CC="$(prefix)/bin/gcc-wrap -D_GNU_SOURCE -static -fno-stack-protector"
CLANG_WRAP = CC="$(prefix)/bin/clang-wrap -D_GNU_SOURCE -static -fno-stack-protector"

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
	-./tools/create_wrappers.sh $(prefix) $(libdir)
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
	-$(RM) -r hbox-control
	-$(MAKE) cleantest

cleantest:
	cd tests/ && make clean
	cd hbox/ && make clean

include/bits:
	@test "$(ARCH)" || echo "\n\tPlease set ARCH in config.mak before running make "
	@test "$(ARCH)" || echo "\tor use the ./configure script."
	@test "$(ARCH)" || { echo "\tRun 'make gcctest|clangtest' to invoke the test suite\n\n" ; exit 1 ; }
	cp -r arch/$(ARCH)/bits include/
	

include/bits/alltypes.h.sh: include/bits

include/bits/alltypes.h: include/bits/alltypes.h.sh
	sh $< > $@

%.o: $(ARCH)/%.c
	$(CC) $(CFLAGS_ALL_STATIC) -O2 $(STACK_ALIGNMENT) -c -o $@ $<

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
	cd hbox && $(GCC_WRAP) make
	cd hbox-control/ && make
	cd tests/ && $(GCC_WRAP) make
	cd control && make

clangtests:
	cd hbox/ && $(CLANG_WRAP) make
	cd hbox-control/ && make
	cd tests/ && $(CLANG_WRAP) make
	cd control && make

gcctest:
	./tools/build.sh gcctests gcc

clangtest:
	./tools/build.sh clangtests clang

release:
	printf "\t%s\n" "$(RELENG_MIR)/$(RELENG).tar.gz" >> README
	./tools/text2html.sh README
	cd ../ && cp -r hlibc $(RELENG) 
	cd ../ && rm -rf $(RELENG)/.git
	cd ../ && tar -cf $(RELENG).tar.gz $(RELENG) 
	cd ../ && scp $(RELENG).tar.gz $(RELENG_SSH):$(RELENG_DIR)
	ssh $(RELENG_SSH) -f 'cd $(RELENG_DIR) && md5sum $(RELENG).tar.gz >> CHECKSUMS'
	git add README Makefile README.html
	git commit -m "release $(RELENG)"
	git push origin master

.PRECIOUS: $(CRT_LIBS:lib/%=crt/%)

.PHONY: all clean install tests control
