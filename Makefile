CC=c99
CFLAGS=-g -O0 -Wall -Wextra -pedantic

SRC := $(wildcard src/*.c)
TEST := $(wildcard src/test/*.c) $(filter-out src/main.c, $(SRC))

all: setup sched-gen test

setup:
	mkdir -p bin

sched-gen: $(patsubst %.c, %.o, $(SRC))
	$(CC) $^ -o bin/sched-gen

test: $(patsubst %.c, %.o, $(TEST))
	$(CC) $^ -o bin/sched-gen-test

%.o: %.c
	$(CC) $(CFLAGS) -c $*.c -o $*.o

clean:
	rm src/*.o src/test/*.o
