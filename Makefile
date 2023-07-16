CC=gcc
CFLAGS=-g # Flag for implicit rules. Turn on debug info
# DEPS = queue/queue.h
# OBJ = queue/queue.o 

# %.o: %.c $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)

# queue: $(OBJ)
# 	$(CC) -o $@ $^ $(CFLAGS)

main: main.c
	cc main.c -o main

clean:
	rm -f main	

