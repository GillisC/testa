CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g -DTESTA_USE_COLOR

SRC_DIR     = src
EXAMPLES_DIR = examples
BUILD_DIR   = build

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
SRC_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

EXAMPLE_SRCS = $(wildcard $(EXAMPLES_DIR)/*.c)
EXAMPLE_BINS = $(patsubst $(EXAMPLES_DIR)/%.c, $(BUILD_DIR)/%, $(EXAMPLE_SRCS))

all: $(EXAMPLE_BINS)

# Build each example binary
$(BUILD_DIR)/%: $(EXAMPLES_DIR)/%.c $(SRC_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Compile src/*.c to build/*.o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build dir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

