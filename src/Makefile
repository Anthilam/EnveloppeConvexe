-TARGET=vecset
-TARGET2=convex
-TARGET3=pilote
+CFLAGS=-c -Wall -std=c99 -g -o
 
-all: $(TARGET) $(TARGET2) $(TARGET3) clean
+all: pilote clean
 
-$(TARGET).o: $(TARGET).c
-	gcc -c -Wall -std=c99 -g -o $(TARGET).o $(TARGET).c
+pilote: pilote.o vecset.o convex.o
+	gcc -g -Wall -std=c99 -o pilote $^
 
-$(TARGET): $(TARGET).o
-	gcc -g -Wall -std=c99 -o $(TARGET) $(TARGET).o
+pilote.o: pilote.c convex.h vecset.h
+	gcc $(CFLAGS) pilote.o $<
 
-$(TARGET2).o: $(TARGET2).c
-	gcc -c -Wall -std=c99 -g -o $(TARGET2).o $(TARGET2).c
+vecset.o: vecset.c vecset.h
+	gcc $(CFLAGS) vecset.o vecset.c
 
-$(TARGET2): $(TARGET2).o $(TARGET).o
-	gcc -g -Wall -std=c99 -o $(TARGET2) $(TARGET).o $(TARGET2).o
-
-$(TARGET3).o: $(TARGET3).c
-	gcc -c -Wall -std=c99 -g -o $(TARGET3).o  $(TARGET3).c
-
-$(TARGET3): $(TARGET3).o
-	gcc -g -Wall -std=c99 -o $(TARGET3) $(TARGET3).o
+convex.o: convex.c vecset.h convex.h
+	gcc $(CFLAGS) convex.o convex.c
 
 clean:
 	rm -f *.o
 
 mrproper: clean
-	rm -f $(TARGET)
-	rm -f $(TARGET2)
-	rm -f $(TARGET3)
+	rm -f vecset
+	rm -f convex
+	rm -f pilote
