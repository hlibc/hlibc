# mini build system for fdlibm.
# This is not the build system that hlibc uses for the code here.
# The mini-build system and its include/ are for the purposes of
# allowing for a standalone implementation that can be compiled by
# any libc... even one that is already polluted with the Sum fdlibm
# namespace. The names of some internal fdlibm functions and macros 
# have been renamed in order to make this possible.

CFLAGS += -Wall -Wextra -I./include/
SRCS = $(sort $(wildcard src/*.c))
OBJ = $(SRCS:.c=.o)
LIBNAME = m
STATLIB = lib$(LIBNAME).a
LDLIBS += -L. -l$(LIBNAME)

all:
	$(MAKE) static

static: $(OBJ)
	$(AR) -cvq $(STATLIB) $(OBJ)

clean:
	$(RM) $(STATLIB) $(OBJ)


