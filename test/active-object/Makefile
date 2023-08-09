#TODO fix it

CC = gcc
CFLAGS = -I../../libraries/Unity/src/ -I../../src/active-object/
SRC_FILES = active-object.c unity.c active-object.test.c
OUT_FILE = test_active_object

all:
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(OUT_FILE)

test: all
	./$(OUT_FILE)
