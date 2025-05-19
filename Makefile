CC = gcc
CFLAGS = -Wall -Wextra -I.
LDFLAGS = 
SRC = main.c game.c cli-lib/screen.c cli-lib/keyboard.c cli-lib/timer.c
OBJ = $(SRC:.c=.o)
TARGET = projeto-pif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run