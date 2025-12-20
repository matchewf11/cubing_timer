main.o: src/main.c
	gcc -c src/main.c
cli.o: src/cli/cli.c
	gcc -c src/cli/cli.c
scramble.o: src/scramble/scramble.c
	gcc -c src/scramble/scramble.c
all: main.o cli.o scramble.o
	gcc main.o cli.o scramble.o -o cubing_timer
clean:
	rm *.o cubing_timer
