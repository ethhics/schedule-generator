CC       = gcc
ERRORS   = -Wall -Wextra -Wshadow -Wcast-qual -Wcast-align -Wconversion -Wreturn-type -Wformat
FLAGS    = -ansi -pedantic
TESTS   := $(wildcard src/test/*c)
SOURCES := $(wildcard src/*c)
EXEC     = bin/schedule_generator

all: clean build

build:
	$(CC) $(FLAGS) -O3 $(SOURCES) -o $(EXEC)

debug: clean
	$(CC) $(FLAGS) $(ERRORS) -g $(SOURCES) -o $(EXEC)

test: clean $(TESTS:src/test/%.c=bin/%)

bin/%: src/test/%.c
	$(CC) $(FLAGS) $(ERRORS) -g $(filter-out src/main.c, $(SOURCES)) $< -o $@ 

clean:
	rm -f bin/*
