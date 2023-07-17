# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -std=c11

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Target executable
TARGET = $(BIN_DIR)/active-object-fsm

# Default target
all: $(TARGET)
	# The default target is to build the $(TARGET) executable

# Rule to build the target
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@
	# Build the $(TARGET) executable by linking the $(OBJS) object files
	# Create the $(BIN_DIR) directory if it doesn't exist

# Rule to compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	# Compile each source file to its corresponding object file in the $(BUILD_DIR)
	# Create the necessary subdirectories in the $(BUILD_DIR) if they don't exist

# Clean the build files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	# Remove the $(BUILD_DIR) and $(BIN_DIR) directories along with their contents

# Run the main executable
run: $(TARGET)
	$(TARGET)
	# Run the $(TARGET) executable	

# Phony targets
.PHONY: all clean
	# Mark the targets 'all' and 'clean' as phony targets
	# This ensures that the associated commands are executed even if a file with the same name exists
