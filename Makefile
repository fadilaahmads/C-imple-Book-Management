CC = gcc
CFLAGS = -Wall -Iinclude
SRC = main.c src/book.c src/ui.c
OBJ = $(SRC:.c=.o)
TARGET = bms

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ) src/*.o

.PHONY: clean
