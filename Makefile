ERRORS=-Wall -Wextra -Wshadow -Wcast-qual -Wcast-align -Wconversion -Wreturn-type -Wformat
FLAGS=-ansi -pedantic

all: clean build

build:
	gcc $(FLAGS) -O3 src/*c -o bin/schedule_maker

debug: clean
	gcc $(FLAGS) $(ERRORS) -g *c

clean:
	rm -f a.out
