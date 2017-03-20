CFLAGS=-c -Wall -std=c99 -g -o

all: pilote clean

pilote: pilote.o vecset.o convex.o
	gcc -g -Wall -std=c99 -o pilote $^

pilote.o: pilote.c convex.h vecset.h
	gcc $(CFLAGS) pilote.o $<

vecset.o: vecset.c vecset.h
	gcc $(CFLAGS) vecset.o vecset.c

convex.o: convex.c vecset.h convex.h
	gcc $(CFLAGS) convex.o convex.c

clean:
	rm -f *.o

mrproper: clean
	rm -f vecset
	rm -f convex
	rm -f pilote
