# Compiler
CC = gcc

# Directories
SRC_DIR = ../src
TEST_DIR = ./
UNITY_DIR = ../libraries/Unity/src

# Source files and objects
SRCS = $(wildcard $(SRC_DIR)/**/*.c)
OBJS = $(SRCS:.c=.o)
UNITY_SRC = $(UNITY_DIR)/unity.c
TEST_SRCS = $(wildcard $(TEST_DIR)/**/*.test.c)
TEST_BINS = $(TEST_SRCS:.test.c=.test)   # This produces filenames like fsm/fsm.test.o

# Compiler Flags
CFLAGS = -I$(SRC_DIR) -I$(UNITY_DIR)

.PHONY: all clean tests

all: clean tests

tests: $(TEST_BINS)
	@for test in $(TEST_BINS); do \
		echo "Running $$test"; \
		./$$test; \
		echo; \
	done

%.test: %.test.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(UNITY_SRC) $< $(OBJS)

clean:
	rm -f $(OBJS) $(TEST_BINS)
