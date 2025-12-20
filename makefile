main.o: src/main.c
	gcc -c src/main.c
cli.o: src/cli/cli.c
	gcc -c src/cli/cli.c
all: main.o cli.o
	gcc main.o cli.o -o cubing_timer
clean:
	rm *.o cubing_timer
