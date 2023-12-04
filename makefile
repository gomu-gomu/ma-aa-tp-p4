CC := gcc
CFLAGS := -Wall -Wextra -g
SRC_DIR := src
BUILD_DIR := build
TARGET := $(BUILD_DIR)/main

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

.PHONY: all clean run

all: clean $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) ./test/**/*.bmp ./test/**/*.bin ./test/**/main_*

run: $(TARGET)
	$(TARGET) $(MAKECMDGOALS)