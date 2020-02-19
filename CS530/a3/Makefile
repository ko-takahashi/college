CC = gcc
CFLAGS = -c
TARGET = exp

all: $(TARGET)

$(TARGET): exp.o
	$(CC) exp.o -o $(TARGET)

exp.o: exp.c
	$(CC) $(CFLAGS) exp.c

clean:
	rm -f core *.0 $(TARGET)