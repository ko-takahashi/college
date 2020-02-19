CC = g++
CFLAGS = -c
TARGET = xed

all: $(TARGET)

$(TARGET): main.o xed.o Opcode.o
	$(CC) main.o xed.o Opcode.o -o $(TARGET)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

xed.o: xed.cpp
	$(CC) $(CFLAGS) xed.cpp

Opcode.o: Opcode.cpp
	$(CC) $(CFLAGS) Opcode.cpp

clean:
	rm -f core *.o $(TARGET)
