CC=gcc
CFLAGS=-Wall
AR=ar
RM=rm

LIB=libroman.a   # make libroman.a  - build a static library
LIBDEST=./
LIBSRC=romancalc.c  # *.c includes *.h
LIBOBJ=$(LIBSRC:.c=.o)

install: $(LIB)
	@echo lib Makefile - installing $(LIB)
	@install -m 444 $(LIB) $(LIBDEST)

$(LIB): $(LIBOBJ) 
	@echo lib Makefile - archiving $(LIB)
	@$(AR) rcs $(LIB) $(LIBOBJ)        # ar --help for rcs

.c.o:
	@echo lib Makefile - compiling $<
	@$(CC) $(CFLAGS) -c $< -o $@

test-static: main.o
	@echo building test prog using libroman.a
	gcc -static main.c -L. -lroman -o test-static

clean:
	@echo lib Makefile - cleaning *.o *.a
	@$(RM) -f *.o *.a
