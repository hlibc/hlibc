CFLAGS += -Wall -Wextra -I./include/

SRCS = $(sort $(wildcard src/*.c))
OBJ = $(SRCS:.c=.o)

LIBNAME = m

STATLIB = lib$(LIBNAME).a 

LDLIBS += -L. -l$(LIBNAME)

all:

	$(MAKE) static

static: $(OBJ)

	$(MAKE) static_link

static_link:

	$(AR) -cvq $(STATLIB) $(OBJ)

create_test: $(TEST_OBJ)

cleanobj:

	$(RM) $(OBJ) $(OBJ) 

clean:
	$(MAKE) cleanobj
	$(RM) $(STATLIB)
	

