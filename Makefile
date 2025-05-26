CC = gcc
CFLAGS = -Wall -g
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TARGET = $(BUILD_DIR)/corrida_texto

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ # <-- Aqui estava o problema principal: $^ são os objetos .o

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

run: all
	./$(TARGET)

.PHONY: debug
debug:
	@echo "SRCDIR: $(SRCDIR)"
	@echo "SRC_DIR: $(SRC_DIR)" # Parece que você usou SRC_DIR, vamos verificar
	@echo "BUILD_DIR: $(BUILD_DIR)"
	@echo "INC_DIR: $(INC_DIR)"
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"
	@echo "TARGET: $(TARGET)"
