TARGET=vecset.c
TARGET2=pilote.c
TARGET3=convex.c
all: $(TARGET) $(TARGET2) $(TARGET3)

$(TARGET): $(TARGET).o 
	gcc -g -std=c99 -o $(TARGET) $(TARGET).o

$(TARGET2): $(TARGET2).o
	gcc -g -std=c99 -o $(TARGET2) $(TARGET2).o

$(TARGET3): $(TARGET3).o
	gcc -g -std=c99 -o $(TARGET3) $(TARGET3).o



$(TARGET).o: $(TARGET).c 
	gcc -c -Wall -std=c99 -g -o $(TARGET).o $(TARGET).c

$(TARGET2).o: $(TARGE2).c 
	gcc -c -Wall -std=c99 -g -o $(TARGET2).o $(TARGET2).c

$(TARGET3).o: $(TARGET3).c 
	gcc -c -Wall -std=c99 -g -o $(TARGET3).o $(TARGET3).c


clean:
	rm -f *.o

mrproper: clean
	rm -f $(TARGET)
	rm -f $(TARGET2)
	rm -f $(TARGET3)

