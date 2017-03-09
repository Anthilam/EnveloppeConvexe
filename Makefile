TARGET=convexe
all: ($TARGET)
($TARGET): ($TARGET).o 
	gcc -g -o ($TARGET) ($TARGET).o
	
($TARGET).o: ($TARGET).c 
	gcc -c -Wall -g -o ($TARGET).o ($TARGET).c

clean:
	rm -f *.o
mrproper: clean
	rm -f ($TARGET)


