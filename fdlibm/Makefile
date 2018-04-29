CFLAGS += -Wall -Wextra -I./include/

OBJ = $(shell for i in src/*.c ; do printf "%s\n" $${i%.c}.o ; done )

LIBNAME = m

STATLIB = lib$(LIBNAME).a 

LDLIBS += -L. -l$(LIBNAME)

all:

	$(MAKE) static

static: $(OBJ)

	$(MAKE) static_link

static_link:

	$(AR) -cvq $(STATLIB) $(OBJ)

dynamic_link:

	$(CC) -shared -Wl,-soname,$(DYNLIB) -o $(DYNLIB) $(OBJ)

create_test: $(TEST_OBJ)

cleanobj:

	$(RM) $(OBJ) $(OBJ) 

clean:
	$(MAKE) cleanobj
	$(RM) $(STATLIB)
	

