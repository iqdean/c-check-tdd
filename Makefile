CFLAGS=-Wall
#LIBS=-lcheck

test: rc.c
	gcc $(CFLAGS) -o test rc.c

clean:
	-rm -f *.o
	-rm -f test

