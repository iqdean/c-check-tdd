CFLAGS=-Wall
#LIBS=-lcheck

test: romancalc.c main.c
	gcc $(CFLAGS) -o test romancalc.c main.c 

clean:
	-rm -f *.o
	-rm -f test

