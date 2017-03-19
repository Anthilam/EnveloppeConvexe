TARGET=vecset
TARGET2=convex
TARGET3=pilote

all: $(TARGET) $(TARGET2) $(TARGET3) clean

$(TARGET).o: $(TARGET).c
	gcc -c -Wall -std=c99 -g -o $(TARGET).o $(TARGET).c

$(TARGET): $(TARGET).o
	gcc -g -Wall -std=c99 -o $(TARGET) $(TARGET).o

$(TARGET2).o: $(TARGET2).c
	gcc -c -Wall -std=c99 -g -o $(TARGET2).o $(TARGET2).c

$(TARGET2): $(TARGET2).o $(TARGET).o
	gcc -g -Wall -std=c99 -o $(TARGET2) $(TARGET).o $(TARGET2).o

$(TARGET3).o: $(TARGET3).c
	gcc -c -Wall -std=c99 -g -o $(TARGET3).o  $(TARGET3).c

$(TARGET3): $(TARGET3).o
	gcc -g -Wall -std=c99 -o $(TARGET3) $(TARGET3).o

clean:
	rm -f *.o

mrproper: clean
	rm -f $(TARGET)
	rm -f $(TARGET2)
	rm -f $(TARGET3)
