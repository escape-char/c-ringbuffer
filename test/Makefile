#compiler and flags
CC=gcc
CFLAGS=-c -Wall -W
LIBS=-lcheck

#objects, libraries, and main
OBJ=test_ringbuffer.o ringbuffer.o
LIB=../ringbuffer/ringbuffer.c
MAIN=test_ringbuffer.c


OUTPUT=testringbuffer #executable output

all: test_ringbuffer

test_ringbuffer: $(OBJ)
	$(CC) $(OBJ) -o $(OUTPUT) $(LIBS)
test_ringbuffer.o: $(MAIN)
	$(CC) $(CFLAGS) $(MAIN)
ringbuffer.o: $(LIB)
	$(CC) $(CFLAGS) $(LIB)
clean:
	rm -rf *.o $(OUTPUT)

.PHONY: clean all
