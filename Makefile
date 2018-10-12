SRCS = $(wildcard src/*.c src/*/*.c machine/crt/*.c)
ASRCS = $(wildcard machine/crt/$(ARCH)/*.s src/*/$(ARCH)/*.s)
OBJ = $(SRCS:.c=.o)

AOBJ = $(ASRCS:.s=.o)
CPPFLAGS =
FREESTANDING = -std=c99 -ffreestanding -nostdinc -nostdlib
CFLAGS = $(FREESTANDING)
CFLAGS += -D_XOPEN_SOURCE=700 -I./include
CFLAGS += $(CPPFLAGS)

WRAP_OPT = -fno-stack-protector -static -D_GNU_SOURCE

-include config.mak

all:
	cp -R machine/$(ARCH)/bits include/
	cp -R os/$(OPERATING_SYSTEM)/$(ARCH)/bits/* include/bits/
	cp -R os/$(OPERATING_SYSTEM)/$(ARCH)/operating_system.h include/bits/
	$(MAKE) static

install:
	-mkdir -p $(prefix)/bin $(prefix)/lib
	-cp -R include $(prefix)/
	-cp libc.a libm.a $(prefix)/lib/
	-cp machine/crt/*.o $(prefix)/lib/
	-./tools/gcc-wrap.specs.sh $(prefix)/include $(prefix)/lib $(prefix)/ > $(prefix)/lib/gcc-wrap.specs
	
	$(MAKE) create_compiler

static: $(OBJ) $(AOBJ)
	$(AR) -cvq libc.a $(OBJ) $(AOBJ)
	$(AR) rc libm.a

clean:
	$(RM) -rf $(OBJ) config.mak libc.a libm.a include/bits $(AOBJ)

cleanall:
	rm -rf system-root


create_compiler:
	printf '#!/bin/sh\n' > $(prefix)/bin/compiler
	printf 'printf "cc = "\n' >> $(prefix)/bin/compiler
	printf 'set -x\n' >> $(prefix)/bin/compiler
ifeq ($(CC_IS_CLANG),yes)
	printf 'clang $(WRAP_OPT) -nostdinc -isystem $(prefix)/include --sysroot $(prefix) "$$@" ' >>  $(prefix)/bin/compiler
else
	printf 'exec gcc $(DISABLE_PIE) $(WRAP_OPT) "$$@" -specs %s/gcc-wrap.specs\n' "$(libraries)" >> $(prefix)/bin/compiler
endif
	chmod +x $(prefix)/bin/compiler


test:
	-$(MAKE) -C system-root/hlibc-test/ clean
	-$(RM) -rf system-root/bin system-root/lib system-root/include
	./tools/build.sh $(CC) $(PWD)/system-root/

