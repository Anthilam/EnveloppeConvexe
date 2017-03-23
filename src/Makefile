CFLAGS=-c -Wall -std=c99 -g -o
MATH=-lm

all: pilote clean

pilote: pilote.o vecset.o convex.o
	gcc -g -Wall -std=c99 -o pilote $^ $(MATH)

pilote.o: pilote.c convex.h vecset.h
	gcc $(CFLAGS) pilote.o $< $(MATH)

vecset.o: vecset.c vecset.h
	gcc $(CFLAGS) vecset.o vecset.c $(MATH)

convex.o: convex.c vecset.h convex.h
	gcc $(CFLAGS) convex.o convex.c $(MATH)

clean:
	rm -f *.o

mrproper: clean
	rm -f vecset
	rm -f convex
	rm -f pilote
