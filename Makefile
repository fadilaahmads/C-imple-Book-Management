# Define the compiler and the flags
CC = gcc
CFLAGS = -Wall

# Target to be created
TARGET = bms

# Rule to build the target
$(TARGET): main.o
	$(CC) -o $(TARGET) main.o

# Rule to build the object file
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# Rule to clean up generated files
clean:
	rm -f $(TARGET) main.o

