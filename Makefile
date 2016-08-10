CC=gcc
CFLAGS=-Wall -fPIC -I. -c   # add -g to include debug symbols

LIB=libroman.so     # make libroman.so  - build a shared library
LIBDEST=./
LIBSRC=romancalc.c  # *.c includes *.h
LIBOBJ=$(LIBSRC:.c=.o)

LDFLAGS=-shared -lc -Wl,-soname,$(LIB)

install: $(LIB)
	@echo romancalc - installing $(LIB)
	@install -m 444 $(LIB) $(LIBDEST)

# gcc -shared -lc -Wl,-soname,libroman.so -o libroman.so romancalc.o

$(LIB): $(LIBOBJ) 
	@echo romancalc - linking $(LIB)
	$(CC) $(LDFLAGS) -o $(LIB) $(LIBOBJ)

.c.o:
	@echo romancalc - compiling $<
	@$(CC) $(CFLAGS) $< -o $@

# Before running test-shared
#  set LD_LIBRARY_PATH = <path_to>/libroman.so
#  ex: $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
# OR cp/install libroman.so to /usr/lib dir
test-shared: main.o
	@echo build test prog to use libroman.so
	gcc main.c -L. -lroman -o test-shared

clean:
	@echo romancalc - cleaning *.o *.so test-shared test-add2romans test-add2romans.c
	@$(RM) -f *.o *.so test-shared test-add2romans test-add2romans.c

test-add2romans: test-add2romans.o
	gcc test-add2romans.c -L. -lroman -lcheck -o test-add2romans

test-add2romans.c: test-add2romans.check
	checkmk test-add2romans.check >test-add2romans.c
